#ifndef MAP_TASK_HH
#define MAP_TASK_HH

#include <iostream>
#include <map>

#include "../comms/include/Packet.h"
#include "Task.h"

using namespace std;

class MapTask : public Task {

	public:
		MapTask(Packet* packet);
		map<string, string> performTask();	
}

#endif