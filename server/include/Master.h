#ifndef MASTER_HH
#define MASTER_HH

#include <iostream>
#include <vector>
#include <map>

#include "../../comms/SocketManager.h"
#include "../task/Task.h"

using namespace std;

struct addr {
	string hostname;
	int portno;
};

typedef addr addr;

class Master {
private:
	map<string, map<int, SocketManager>> workerContacts;
	map<Task, TaskState> taskStates;
	vector<addr> addresses;
	map<string, string> input;

	void connectToHost(string hostname, int port);

public:

	Master(map<string, int> workersAddr, map<string, string> input);

	void connectToWorkers();

	void sendMapTask(string hostname, int portno, map<string, string> kVPairs);

	void sendReduceTask(string hostname, int portno, map<string, string> kVPairs);

	void distributeMapTasks();

	void manageWorker(string hostname, int portno);

};

#endif