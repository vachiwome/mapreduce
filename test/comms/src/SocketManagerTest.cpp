#include <iostream>
#include <string>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "../../../comms/include/SocketManager.h"
#include "../../../comms/include/Packet.h"
#include "../include/SocketManagerTest.h"

using namespace std;


void * listenAndAcceptWrapper(void* testInfo) {
	TestInfo* info = (TestInfo*) testInfo;
	info->server->listenAndAccept(info->portno);
	return NULL;
}

void* connectToHostWrapper(void* testInfo) {
	TestInfo* info = (TestInfo*) testInfo;
	info->client->connectToHost(info->hostname, info->portno);
	return NULL;
}

void SocketManagerTest::connectClientToServer() { 
	pthread_t server, client;
	if (pthread_create(&server, NULL, listenAndAcceptWrapper, &info)) {
		fprintf(stderr, "Error creating thread\n");
		exit(1);
	}
	if (pthread_create(&client, NULL, connectToHostWrapper, &info)) {
		fprintf(stderr, "Error creating thread\n");
		exit(1);
	}
  	if(pthread_join(server, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		exit(2);
	}
  	if(pthread_join(client, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		exit(2);
	}

}

void SocketManagerTest::closeClientAndServer() {
	info.server->closeSocket();
		info.client->closeSocket();
}

void SocketManagerTest::setUp() {
	info.server = new SocketManager();
	info.client = new SocketManager();
	info.hostname = "localhost";
	info.portno = 4445;
}

void SocketManagerTest::tearDown() {
	delete info.server;
	delete info.client;
}

void SocketManagerTest::testListenAndAccept() {
	// connectClientToServer();
	// closeClientAndServer();
}

void SocketManagerTest::testPacketSendAndReceive() {
	connectClientToServer();
	Packet* packet = new Packet();
	packet->packetSize = 100;
	packet->packetType = 0;
	map<string, string> kVPairs;
	kVPairs["key1"] = "value1";
	kVPairs["key2"] = "value2";
	kVPairs["key3"] = "value3";
	packet->keyValuePairs = kVPairs;

	info.client->sendPacket(packet);
	Packet* recvPacket = info.server->receivePacket();

	map<string, string> newKVPairs = recvPacket->keyValuePairs;
	map<string, string>::iterator it;
	for (it = newKVPairs.begin(); it != newKVPairs.end(); it++) {
		CPPUNIT_ASSERT(it->second == kVPairs[it->first]);
	}
	closeClientAndServer();
}

CppUnit::Test* SocketManagerTest::suite() {
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "SocketManagerTest" );

	suiteOfTests->addTest( new CppUnit::TestCaller<SocketManagerTest>( 
	                                "testListenAndAccept", 
	                                &SocketManagerTest::testListenAndAccept ) );

	suiteOfTests->addTest( new CppUnit::TestCaller<SocketManagerTest>(
	                               "testPacketSendAndReceive",
	                               &SocketManagerTest::testPacketSendAndReceive ) );
	return suiteOfTests;
}
