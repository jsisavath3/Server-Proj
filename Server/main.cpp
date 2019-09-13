#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
#define PORT "38000"


using namespace std;

int main() {
	WSADATA wsaData;
	
	//initialization
	int startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	//address information
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	SOCKET listener = socket(AF_INET, SOCK_STREAM, AI_PASSIVE);


	return 0;

}