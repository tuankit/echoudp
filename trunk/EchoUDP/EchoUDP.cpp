// EchoUDP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Socket.h"



void EChoServer ()
{

	SocketAddress sa;

	sa.SetPort(7000);


	UDPSocket  s;
	s.Create();



}







int _tmain(int argc, _TCHAR* argv[])
{
	EChoServer();
	return 0;
}

