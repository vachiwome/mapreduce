#include <algorithm>

#include "../../comms/Packet.h"
#include "../Master.h"


using namespace std;

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

void Master::sendReduceTask(string hostname, int portno) {
	Packet* packet = createPacket(PacketType.REDUCE, kVPairs);
	workerContacts[hostname][portno].sendPacket(packet);	
}

void Master::distributeMapTasks() {

}

void Master::manageWorker(string hostname, int portno) {

}
