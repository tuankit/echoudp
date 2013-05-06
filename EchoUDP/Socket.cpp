#include "StdAfx.h"
#include "Socket.h"

Socket::Socket(void)
{

	WSADATA wsaData;
	init = WSAStartup(0x202, &wsaData) == 0;

	m_socket = INVALID_SOCKET;

}

Socket::~Socket(void)
{

	WSACleanup();
}


bool Socket::Bind(const sockaddr_in * sa)
{
	return bind(m_socket,(const sockaddr *)sa,sizeof(sockaddr_in)) != SOCKET_ERROR;

}
bool Socket::Bind(SocketAddress &sa)
{
	return Bind(&sa.m_addr);
}


bool UDPSocket::Create( void )
{

	m_socket = socket(AF_INET,SOCK_DGRAM ,0 );
	return m_socket != INVALID_SOCKET;
}

int UDPSocket::SendTo( const char* buffer,int len, sockaddr_in *reciver )
{

	return sendto(m_socket,buffer,len,0,(const sockaddr *)reciver,sizeof(sockaddr));
}

int UDPSocket::SendTo( const char* buffer,int len, SocketAddress & address )
{

	return SendTo(buffer,len,&address.m_addr);
}

int UDPSocket::RecvFrom( char * buffer, int len, sockaddr_in *from )
{
	int fromlen = sizeof(sockaddr_in);
	return recvfrom( m_socket,buffer,len,0,(sockaddr *)from,&fromlen);
}

int UDPSocket::RecvFrom( char * buffer, int len, SocketAddress &from )
{
	return RecvFrom(buffer,len,&from.m_addr);

}

