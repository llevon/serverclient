/*
	UDP Client routine
*/
#include <thread>
#include "UDPSocket.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

void sizer(int n)
{
	if (n == 0)
	cout << "Wrong Input" << endl;
}

int main(int argc, char* argv[])
{
//	SOCKET s;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	unsigned short srv_port = 0;
	char srv_ip_addr[40];
	memset(srv_ip_addr, 0, 40);

	//create socket
	UDPSocket client_sock;

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;

	//si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	if (1 == argc)
	{
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
	}
	else if (2 == argc)
	{
//		si_other.sin_port = htons(PORT);
//		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		si_other.sin_port = htons(atoi(argv[1]));
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		printf("2: argv[0]: Server - addr=%s , port=%d\n", SERVER, atoi(argv[1]));
	}
	else
	{
		si_other.sin_port = htons( atoi(argv[2]) );
		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
	}
	string buff;
	//start communication  lifecircle
	cout << "Input your login" << endl;
	while (1)
	{
		gets_s(message, BUFLEN);
		//send the message
		thread functorTest(sizer, strlen(message));
		functorTest.join();

		client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other, slen);

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
	
		//try to receive some data, this is a blocking call

		    memset(buf, '\0', BUFLEN);
			client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
			
			
			if (buf[0] == 'B')
			{
				while (1)
				{
					gets_s(message, BUFLEN);
					client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other, slen);
					memset(buf, '\0', BUFLEN);
					client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
					cout << "server: " << buf << endl;
				}
			}
			
		
	}

	return 0;
}
