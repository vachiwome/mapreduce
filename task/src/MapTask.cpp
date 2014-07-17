#include <iostream>
#include <map>

#include "../../comms/include/Packet.h"
#include "../include/MapTask.h"

using namespace std;

void MapTask::MapTask(Packet* packet) {
	this->keyValuePairs = packet->keyValuePairs;
}

map<string, string> MapTask::perform() {
	// TODO
	return this->keyValuePairs;
}