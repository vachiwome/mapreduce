#ifndef TASK_HH
#define TASK_HH

#include <iostream>
#include <string>
#include <map>

#include "../comms/include/Packet.h"

using namespace std;

class Task {

	private:
		map<string, string> keyValuePairs;
		string filename;

	public:
		virtual map<string, string> perform() = 0;
		
		string getFilename() {
			return this->filename;
		}

		map<string, string> getKeyValuePairs() {
			return this->keyValuePairs;
		}

		void setFilename(string filename) {
			this->filename = filename;
		}
}; 

#endif





