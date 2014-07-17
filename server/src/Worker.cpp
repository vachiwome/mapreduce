#include <iostream>
#include <string>

#include <pthread.h>

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

Worker::updateMaster() {
	//TODO
}

Worker::performTask(Task task) {
	map<string, string> results = task.perform();
	fileManager.writeMapToFile(task.getFilename(), task.getKeyValuePairs());
	updateMaster();
}

Worker::work() {
	workForMasterConn();
	while (1) {
		Task task = receiveTask();
		pthread_t taskThread;
		if (pthread_create(&taskThread, &task, performTaskWrapper, &info)) {
			cout << "error creating thread" << endl;
			exit(1);
		}
	}
}


