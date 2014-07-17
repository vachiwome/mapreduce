#include <iostream>
#include <map>

#include "../../comms/include/Packet.h"
#include "../include/ReduceTask.h"

using namespace std;

void ReduceTask::ReduceTask(Packet* packet) {
	this->keyValuePairs = packet->keyValuePairs;
}

map<string, string> ReduceTask::perform() {
	return this->keyValuePairs;
}