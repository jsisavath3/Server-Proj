#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")


using namespace std;


int main() {
	WSADATA wsaData;

	//initialization
	int startup = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
		
	//address information
	sockaddr_in hints;
	hints.sin_family = AF_INET;
	hints.sin_port = htons(38000);
	hints.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listener, (sockaddr*)& hints, sizeof(hints));
	listen(listener, SOMAXCONN);


	//array with multiple clients
	fd_set master;
	FD_ZERO(&master);

	FD_SET(listener, &master);

	bool running = true;
	char host[NI_MAXHOST];
	while (running) {
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		for (int i = 0; i < socketCount; i++) {
			SOCKET soc = copy.fd_array[i];
			if (soc == listener) {
				SOCKET newClient = accept(listener, nullptr, nullptr);
				FD_SET(newClient, &master);
				string welcome = "Welcome \n";
				send(newClient, welcome.c_str(), welcome.size() + 1, 0);
				inet_ntop(AF_INET, &hints.sin_addr, host, NI_MAXHOST);
				cout << "connected" << endl; 
			}
			else {
				char buff[4096];
				ZeroMemory(buff, 4096);
				int receivedBytes = recv(soc, buff, 4096, 0);
				if (receivedBytes <= 0) {
					closesocket(soc);
					FD_CLR(soc, &master);
				}
				else {
					for (int i = 0; i < master.fd_count; i++) {
						SOCKET sendSoc = master.fd_array[i];
						if (sendSoc != listener && sendSoc != soc) {
							ostringstream ss;
							ss << buff << endl;
							string output = ss.str();
							send(sendSoc, output.c_str(), output.size() + 1, 0);
						}

						
					}
				}
			}
		}
	}
	FD_CLR(listener, &master);
	closesocket(listener);
	WSACleanup();

	system("pause");
	return 0;
}
