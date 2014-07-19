#ifndef PACKET_HH
#define PACKET_HH

#include <iostream>
#include <string>
#include <map>

#include <arpa/inet.h>

#define MAX_PACKET_SIZE 1024

using namespace std;

struct Packet {
	int packetSize;
	int packetType;
	map<string, string> keyValuePairs;
};

typedef struct Packet Packet;

enum PacketType {
	MAP,
	REDUCE,
	FINISHED
};

Packet* charArrToPacket(char* buffer);

char* packetToCharArr(int packetSize, int packetType, map<string, string> keyValuePairs);

Packet* createPacket(int packetType, map<string, string> keyValuePairs);

#endif
