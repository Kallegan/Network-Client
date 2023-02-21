#include <stdio.h>
#include <WinSock2.h> //used for open sockets on operative system.

int main()
{
	//version 2.2,
	WSADATA wsa_data; //data struct
	WSAStartup(MAKEWORD(2, 2), &wsa_data); //initialize winsock lib.

	//printf("Enter port: ");
	unsigned short port = 49;
	//scanf_s("%hu", &port); //%hu = reads half unsigned (unsigned short).

	//an unsiged int that acts as a handle to the socket.
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //internet commuicating using pct protocol. 

	if (sock == INVALID_SOCKET)
	{
		printf("FAIELD TO CREATE SOCKET!\n");
		return 1;
	}
	//local host.
	unsigned char ip_bytes[] = { 192, 168, 50, 2 }; //treats as if its a int in memory by converting and de-referensing. 
	unsigned int ip = *(unsigned int*)ip_bytes;

	sockaddr_in conn_addr; //handles ipv4 socket adressing.
	conn_addr.sin_family = AF_INET;
	conn_addr.sin_addr.s_addr = ip;

	//windows uses small endian while the internet uses big endian, so we have to convert.
	conn_addr.sin_port = htons(port); //host to network short(port)

	int connect_result = connect(sock, (sockaddr*)&conn_addr, sizeof(conn_addr));

	if (connect_result)
	{
		printf("CONNECTION FAILED! Error: %d\n", WSAGetLastError());
	}

	while (true)
	{
		char send_buffer[1024];
		gets_s(send_buffer, 1024);//secure read to avoid reading more than biffer size.

		send(sock, send_buffer, strlen(send_buffer), 0); //send to server
	}
}