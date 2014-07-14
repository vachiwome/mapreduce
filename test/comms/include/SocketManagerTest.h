#ifndef SOCKET_MANAGER_TEST_HH
#define SOCKET_MANAGER_TEST_HH

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <cppunit/TestCaller.h>

#include "../../../comms/include/SocketManager.h"

using namespace std;

struct TestInfo {
	SocketManager* client;
	SocketManager* server;
	string hostname;
	int portno;
};

typedef struct TestInfo TestInfo;

void * listenAndAcceptWrapper(void* testInfo);

void* connectToHostWrapper(void* testInfo);

class SocketManagerTest  {

	private:

		TestInfo info;

		void connectClientToServer();

		void closeClientAndServer();

	public:
		void setUp();

		void tearDown();

		void testListenAndAccept();

		void testPacketSendAndReceive();

		static CppUnit::Test *suite();

};

#endif
