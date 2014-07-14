#ifndef SOCKET_MANAGER_HH
#define SOCKET_MANAGER_HH

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h> 
#include <netinet/in.h>

#include "Packet.h"

using namespace std;

class SocketManager {
	private:
		int fd;
		int send(char* buffer, int size);
		int receive(char* buffer);

	public:

		void listenAndAccept(int portno);

		void connectToHost(string hostname, int portno);

		Packet* receivePacket();

		void sendPacket(Packet* packet);

		void closeSocket();
};
#endif