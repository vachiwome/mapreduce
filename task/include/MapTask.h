#ifndef MAP_TASK_HH
#define MAP_TASK_HH

#include <iostream>

#include "../comms/include/Packet.h"
#include "Task.h"

class MapTask : public Task {
	public:
		void initTaskFromPacket();
		void performTask();	
}

#endif