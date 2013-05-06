// EchoUDP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Socket.h"




void EChoServer ()
{

	UDPSocket  sok;
	SocketAddress local,from;

	local.SetPort(ECHO_PORT);


	if(!sok.Create())
	{
		printf("Error: Create socket failed!");
		return;
	}

	if(!sok.Bind(local))
	{
		printf("Error: Bind socket failed! ADDR: %s, PORT: %d , Error: %d",local.GetAddress(),local.GetPort(),sok.ErrorCode());
		return;
	}


	char buff[256];
	int len = 255;

	do 
	{
		
		len =  sok.RecvFrom(buff,255,from);

		if(len != SOCKET_ERROR)
		{

			buff[len] = 0;
			printf("Server: %s\n",buff);
			printf("From: %s:%d",from.GetAddress(),from.GetPort());

		}
		else
		{
			printf("Error RecvFrom: %d\n",sok.ErrorCode());

		}

	} while (len != SOCKET_ERROR);

	sok.Close();

}



int _tmain(int argc, _TCHAR* argv[])
{
	EChoServer();
	return 0;
}

