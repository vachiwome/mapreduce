#ifndef TASK_HH
#define TASK_HH

#include <iostream>
#include <map>

#include "../comms/include/Packet.h"

using namespace std;

class Task {

	private:
		map<string, string> keyValuePairs;

	public:
		virtual void initTaskFromPacket(Packet* packet) = 0;
		virtual void performTask() = 0;

}; 

#endif