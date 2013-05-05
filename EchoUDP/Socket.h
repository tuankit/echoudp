#pragma once



class SocketAddress {

public:	
	
	sockaddr_in  m_addr;

	
	SocketAddress (long address = INADDR_ANY , int port = 0)
	{
	
		memset((void*)&m_addr,0, sizeof(sockaddr_in));
		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr = htonl(address);
		m_addr.sin_port = htons(port);
	}


	SocketAddress(const char * address, int port = 0)
	{
		SocketAddress::SocketAddress(inet_addr(address),port);
	}

	void SetPort(int port)
	{
		m_addr.sin_port = htons(port);
	}
	void SetAddress(const char * address)
	{
		m_addr.sin_addr.s_addr = inet_addr(address);
	}
	const char * GetAddress()
	{
		return inet_ntoa(m_addr.sin_addr);
	}
	int GetPort()
	{
		return ntohs(m_addr.sin_port);
	}
};


class Socket
{

	bool init;

protected:
	SOCKET   m_socket;

public:

	virtual bool  Create(void) = 0; 

	bool Bind(const sockaddr_in * sa);
	bool Bind(SocketAddress &sa);

	int ErrorCode () { return WSAGetLastError(); }

	Socket(void);
	virtual ~Socket(void);
};




class UDPSocket : public Socket
{


public:


	int SendTo(const char* buffer,int len, sockaddr_in *reciver);
	int SendTo(const char* buffer,int len, SocketAddress & address);


	int RecvFrom(char * buffer, int len, sockaddr_in *from);
	int RecvFrom(char * buffer, int len, SocketAddress &from);

	virtual bool Create( void );

};
