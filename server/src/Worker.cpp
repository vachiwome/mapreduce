#include <iostream>
#include <string>

#include "Worker.h"

using namespace std;

Worker::Worker(int portno) {
	this->port
}

Worker::waitForMasterConn(){
     this->sockManager.listenAndAccept();
}

Worker::receiveTask() {
     this->sockManager.receive();
}


Worker::performMapTask() {
	//TODO
}

Worker::performReduceTask() {
	//TODO
}


Worker::updateMaster() {
	//TODO
}

Worker::performTask() {
	//TODO
}

Worker::work() {
	//TODO	
}


