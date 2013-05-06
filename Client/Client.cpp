// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\EchoUDP\Socket.h"



void ReadReply(void *p)
{
	UDPSocket  *s = (UDPSocket *)p;
	SocketAddress from;

	char buff[256];
	int len = 0;

	do{
		len = s->RecvFrom(buff,255,from);
		if(len != SOCKET_ERROR)
		{
			buff[len] = 0;
			printf("Read: %s\n",buff);
			printf("From: %s:%d",from.GetAddress(),from.GetPort());

		}
		else
		{
			//printf("Error RecvFrom: %d\n",s->ErrorCode());

		}

	}while(len != SOCKET_ERROR);
}



int main(int argc, char* argv[])
{

	UDPSocket  sok;
	SocketAddress server;

	server.SetPort(ECHO_PORT);
	server.SetAddress("127.0.0.1");


	if(sok.Create() && sok.Bind(server))
	{
		printf("Ok!\n");
	 	DWORD id;
		HANDLE h = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ReadReply,&sok,0,&id);
		Sleep(100);
		
		if(argc > 1 )
		{
			sok.SendTo(argv[1],strlen(argv[1]),server);
		}
		else
			sok.SendTo("Hello Room!",strlen("Hello Room!"),server);
		Sleep(20);

	}
	else
	{
		printf("Error : %d",sok.ErrorCode());
	}

	sok.Close();
	
	return 0;
}

