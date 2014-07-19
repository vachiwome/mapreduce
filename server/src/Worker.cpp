#include <iostream>
#include <string>
#include <map>

#include <pthread.h>

#include "../../comms/include/Packet.h"
#include "../../task/include/Task.h"
#include "Worker.h"

using namespace std;

void * performTaskWrapper(void* task) {
	performTask(*((Task*) task));
}

Worker::Worker(int portno) {
	this->port
}

Worker::waitForMasterConn(){
     this->sockManager.listenAndAccept();
}

Task Worker::receiveTask() {
     return Task(this->sockManager.receive());
}

Worker::updateMaster(Task task) {
	map<string, string> response;
	response[task.getFilename()] = task.getFilename();
 	this->sockManager.sendPacket(createPacket(FINISHED, response));	
}

Worker::performTask(Task task) {
	map<string, string> results = task.perform();
	fileManager.writeMapToFile(task.getFilename(), task.getKeyValuePairs());
	updateMaster(task);
}

Worker::work() {
	workForMasterConn();
	int fileCount = 0;
	while (1) {
		Task task = receiveTask();
		task.setFilename("outputFile" + fileCount);
		pthread_t taskThread;
		if (pthread_create(&taskThread, &task, performTaskWrapper, &info)) {
			cout << "error creating thread" << endl;
			exit(1);
		}
	}
}


