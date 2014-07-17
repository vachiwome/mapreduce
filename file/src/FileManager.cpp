#include <iostream>
#include <fstream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/FileManager.h"

void FileManager::writeMapToFile(string filename, map<string, string> keyValuePairs) {
	ofstream out(filename.c_str());
	if (out.is_open()){
		map<string, string>::iterator it;
		for (it = keyValuePairs.begin(); it != keyValuePairs.end(); it++) {
			out << it->first << endl;
			out << it->second << endl;
		}
	    out.close();
	} else {
		cout << "could not open file : " << filename << endl;
	}
}

map<string,string> FileManager::readMapFromFile(string filename) {
	ifstream infile(filename.c_str());
	if (infile.is_open()) {
		map<string,string> kVPairs;
		string key, value;
		while (getline(infile, key)) {
			getline(infile, value);
			kVPairs[key] = value;
		}
		infile.close();
		return kVPairs;
	} else {
		cout << "could not open file : " << filename << endl;
		exit(1);
	}
}