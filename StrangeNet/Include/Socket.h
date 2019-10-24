#pragma once

// 소켓프로그래밍 -> IOCP 프로그래밍 공부
// 오늘은 소켓 프로그래밍 공부하자

#include "Util.h"

//64bit Unicode TCP/ IOCP 소켓
#ifdef _WIN64
// WSA소켓쓰려면 WinSock2.h 써야하고 winsocket과 winsock2와 충돌남
#include <WinSock2.h>
#include <windows.h>

#else
#endif

enum class SocketType
{
	TCP = 0,
	UDP
};

class CSocket
{
	SOCKET	m_hSocketHandle;

public:
	CSocket(SocketType eType);
	CSocket(SOCKET hSocketHandle);
	~CSocket();

public:
	//sockaddr_in : socket address, internet style.
	/*
	struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
	};
	*/
	void BindAnyPort();
	void Bind(const sockaddr_in& ipv4Endpoint);
	void Connect(const sockaddr_in& ipv4Endpoint);

	int Send(const char* data, int length);
	void Close();
	void Listen();

	int Accept(CSocket& acceptSocket, std::string& errorText);
	int Receive();
};

// winsock2.h
#pragma comment(lib, "ws2_32.lib");