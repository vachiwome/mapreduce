#include <iostream>
#include <algorithm>
#include <map>

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../comms/Packet.h"
#include "../Master.h"


using namespace std;

Master::Master(map<string, string> input, map<string, int> workersAddr) {
	this->input = input;
	map<string, int>::iterator it;
	for (it = workersAddr.begin(); it != workersAddr.end(); it++) {
		addr address;
		address.hostname = it->first;
		address.portno = it->second;
		this->addresses.push_back(address);
	}
}

void Master::connectToHost(string hostname, int portno) {
	if (workerContacts.find(hostname) == workerContacts.end()) {
		map<int, SocketManager> sockMap;
		workerContacts[hostname] = sockMap;
	}
	SocketManager sockManager = SocketManager();
	workerContacts[hostname][portno] = sockManager;
}

void Master::connectToWorkers() {
	vector<addr>::iterator it;
	for (it = addresses.begin(); it != addresses.end(); it++) {
		connectToHost(it->hostname, it->portno); 
	}
}


void Master::sendMapTask(string hostname, int portno, map<string, string> kVPairs) {
	Packet* packet = createPacket(PacketType.MAP, kVPairs);
	workerContacts[hostname][portno].sendPacket(packet);
}

void Master::assignTask(int startInput, int endInput, string hostname, int portno) {
	map<string, string> workerInput;
	map<string, string>::iterator it = this->input.end();
	int pairIndex = 1;
	while (it != this->input.end()) {
		if (pairIndex >= startInput && pairIndex < endInput) {
			workerInput[it->first]  = [it->second];
		} 
		else if (pairIndex >= endInput) {
			break;
		}
		pairIndex++;
		it++;
	}
	sendMapTask(hostname, portno, workerInput);
}

void Master::sendReduceTask(string hostname, int portno, map<string, string> kVPairs) {
	Packet* packet = createPacket(PacketType.REDUCE, kVPairs);
	workerContacts[hostname][portno].sendPacket(packet);	
}

void Master::processResponsePacket(Packet* packet) {
	map<string, string> responseMap = packet->keyValuePairs;
	map<string, string>::iterator it;
	cout << "received a response from a worker" << endl;
	for (it = responseMap.begin(); it != responseMap.end(); it++) {
		cout << it->first << " => " << it->second << endl;
	}

	// send reduce task
}


void Master::manageWorker(string hostname, int portno) {
	SocketManager sockManager = workerContacts[hostname][portno];
	processResponsePacket(sockManager.receivePacket());
}

void* manageWorkerWrapper(void* a) {
	addr* address = (addr*) a;
	manageWorker(address->hostname, address->portno);
	return NULL;
}

void Master::distributeMapTasks() {
	int inputSize = input.size();
	int workers = addresses.size();
	int unitSize = inputSize / workers;

	int startIndex = 1;
	while (startIndex < (inputSize - unitSize)) {
		addr address = workersAddr[startIndex];
		assignTask(startIndex, startIndex + unitSize, address.hostname, address.portno);
		pthread_t workerManager;
		if (pthread_create(&workerManager, NULL, manageWorkerWrapper, &addr)) {
			fprintf(stderr, "Error creating thread\n");
			exit(1);
		}
		startIndex += unitSize;
	}
}

void Master::work() {
	connectToWorkers();
	distributeMapTasks();
}



