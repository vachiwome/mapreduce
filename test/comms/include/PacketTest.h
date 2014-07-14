#ifndef PACKET_TEST_HH
#define PACKET_TEST_HH

#include <iostream>
#include <string>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <cppunit/TestCaller.h>


#include <cppunit/TestCaller.h>

#include "../../../comms/include/Packet.h"

using namespace std;

class PacketTest  {
	private:
		int packetSize;
		int packetType;
		char* buffer;
		Packet* packet;
		map<string, string> keyValuePairs;

	public:
		void setUp();

		void tearDown();

		void testCharArrToPacket();

		void testPacketToCharArr();

	  	static CppUnit::Test *suite();
};

#endif