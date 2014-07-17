#ifndef WORKER_HH
#define WORKER_HH

#include <iostream>
#include <string>


#include "../../file/include/FileManager.h"
#include "../../task/Task.h"

using namespace std;

class Worker {
	
	private:

		int port;
		SocketManager sockManager;
		FileManager fileManager;

	public:

		Worker(int port);

		void waitForMasterConn();

		Task receiveTask();

		void performTask(Task task);
		
		void updateMaster();

		void work();
};

#endif