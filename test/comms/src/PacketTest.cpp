#include <iostream>
#include <string>
#include <map>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "../../../comms/include/Packet.h"
#include "../include/PacketTest.h"

using namespace std;

void PacketTest::setUp() {
	keyValuePairs["key1"] = "value1";
	keyValuePairs["key2"] = "value2";
	keyValuePairs["key3"] = "value3";

	packetSize = (4*3) + (6*3) + 6 + 64;
	packetType = 0;
}

void PacketTest::tearDown() {
	delete buffer;
	delete packet;
}

void PacketTest::testCharArrToPacket() {
	//
}

void PacketTest::testPacketToCharArr() {
	char* buffer = packetToCharArr(packetSize, packetType, keyValuePairs);
	Packet* packet = charArrToPacket(buffer);
	map<string, string> newKeyValPairs = packet->keyValuePairs;
	CPPUNIT_ASSERT( newKeyValPairs.size() == keyValuePairs.size());
	map<string, string>::iterator it;
	for (it = newKeyValPairs.begin(); it != newKeyValPairs.end(); it++) {
		CPPUNIT_ASSERT(it->second == keyValuePairs[it->first]);
	}
}

CppUnit::Test* PacketTest::suite() {
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "PacketTest" );

	suiteOfTests->addTest( new CppUnit::TestCaller<PacketTest>( 
	                                "testCharArrToPacket", 
	                                &PacketTest::testCharArrToPacket ) );

	suiteOfTests->addTest( new CppUnit::TestCaller<PacketTest>(
	                               "testPacketToCharArr",
	                               &PacketTest::testPacketToCharArr ) );
	return suiteOfTests;
}
