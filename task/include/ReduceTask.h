#ifndef REDUCE_TASK_HH
#define REDUCE_TASK_HH

#include <iostream>

#include "../comms/include/Packet.h"
#include "Task.h"

class ReduceTask : public Task {

	public:
		ReduceTask(Packet* packet);	
		map<string,string> performTask();
}

#endif