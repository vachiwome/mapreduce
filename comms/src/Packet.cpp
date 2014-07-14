#include <iostream>
#include <string>
#include <map>

#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#include "../include/Packet.h"

using namespace std;


Packet* createPacket(int pcktType, map<string, string> keyValuePairs) {
	Packet* packet = new Packet();
	packet->packetType = pcktType;
	int pcktSize = 64;
	map<string, string>::iterator it;
	for (it = keyValuePairs.begin(); it != keyValuePairs.end(); it++) {
		pcktSize += it->first.size() + it->second.size() + 2;
	}
	packet->packetSize = pcktSize;
	return packet;
}

Packet* charArrToPacket(char* buffer) {
	Packet* packet = new Packet();
	packet->packetSize = ntohl(*((int*) buffer));
	packet->packetType = ntohl(*((int*) (buffer + 32)));

	map<string, string> keyValuePairs;
	int offset = 64;
	while (offset < packet->packetSize) {
		int valueIndex = offset + strlen(buffer + offset) + 1;
		string value = string(buffer + valueIndex);
		keyValuePairs[string(buffer+offset)] = value;
		offset = valueIndex + value.length() + 1;
	}

	packet->keyValuePairs = keyValuePairs;
	return packet;
}

char* packetToCharArr(int packetSize, int packetType, map<string, string> keyValuePairs) {
	char* buffer = new char[packetSize];
	*((int*) buffer) = htonl(packetSize);
	*((int*) (buffer + 32)) = htonl(packetType);

	map<string, string>::iterator it;
	int offset = 64;
	for (it = keyValuePairs.begin(); it != keyValuePairs.end(); it++) {
		strcpy(buffer + offset, it->first.c_str());
		offset += (1 + it->first.length());

		strcpy(buffer + offset, it->second.c_str());
		offset += (1 + it->second.length());
	}

	return buffer;
}
