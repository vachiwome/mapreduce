#ifndef FILE_MANAGER_HH
#define FILE_MANAGER_HH

#include <iostream>
#include <map>

using namespace std;

class FileManager {
	public:
		void writeMapToFile(string filename, map<string, string> keyValuePairs);
		map<string, string> readMapFromFile(string filename);	
};

#endif