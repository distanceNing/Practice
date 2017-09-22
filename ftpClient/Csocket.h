#pragma once
#ifndef _CSCOKET

#ifdef _WIN32

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
typedef int socklen_t;

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef unsigned int SOCKET;
typedef unsigned int UINT;
typedef const char* LPCSTR;
typedef char* LPSTR;
#define SOCKET_ERROR -1
unsigned int GetLastError();

#endif 

class Csocket
{
private:
	SOCKET sock;
public:
	
	Csocket();
	~Csocket();
	bool CreatSocket(int af = AF_INET, int type = SOCK_STREAM, int prot = 0);
	int Receive(void *buffer, int buflen);
	bool Sendto(const void *message,const char* toIP,const UINT &toPort);
	int ReceiveFrom(void *buffer, int buflen, char* fromIP, UINT &fromPort);
	bool Listen(int backlog=5);
	bool Accept(Csocket &socka, char* fromIP, UINT  &fromPort);
	size_t Send(void* message, int buflen);
	bool GetPeerName(char* peerIP, UINT &peerPort);
	bool Connect(const char* conIP, UINT &conPort);
	bool CloseSocket();
};
#endif // !_CSCOKET
