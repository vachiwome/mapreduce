#ifndef WORKER_HH
#define WORKER_HH

#include <iostream>
#include <string>

using namespace std;

class Worker {
	
	private:

		int port;
		SocketManager sockManager;

	public:

		Worker(int port);

		void waitForMasterConn();

		void receiveTask();

		void performMapTask();

		void performReduceTask();

		void performTask();
		
		void updateMaster();

		void work();

};

#endif