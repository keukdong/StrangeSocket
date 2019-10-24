#include "Socket.h"

// endpoint adrress 초기화용
#include <Ws2tcpip.h>

CSocket::CSocket(SocketType eType)
{
	// TCP와 UDP의 차이점이다.
	// TCP는 데이터 스트림이고(쪼개고 합치는게 가능)
	// UDP는 데이터 그램으로 메세지 형식
	
	// overlapped I/O를 쓰려면 socket()말고 WSASocket을 써야한다.
	switch (eType)
	{
	case SocketType::TCP:
		m_hSocketHandle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		break;
	case SocketType::UDP:
		m_hSocketHandle = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	}
}

CSocket::CSocket(SOCKET hSocketHandle)
{
	m_hSocketHandle = hSocketHandle;
}

CSocket::~CSocket()
{
}


void CSocket::BindAnyPort()
{
	/*
	IPv4 Socket address, Internet style

	typedef struct sockaddr_in{
    ADDRESS_FAMILY sin_family;
    USHORT sin_port;
    IN_ADDR sin_addr;		// 네트워크 주소 
    CHAR sin_zero[8];
	} SOCKADDR_IN, *PSOCKADDR_IN;
	*/

	/*
	typedef struct sockaddr {
    ADDRESS_FAMILY sa_family;           // Address family.
    CHAR sa_data[14];                   // Up to 14 bytes of direct address.
	} SOCKADDR, *PSOCKADDR, FAR *LPSOCKADDR;	
	*/
	sockaddr_in ipv4address;
	// 초기화 안하면 bind fail
	memset(&ipv4address, 0, sizeof(ipv4address));
	ipv4address.sin_family = AF_INET;
	//ipv4address.sin_addr.S_un.S_un_b;
	inet_pton(AF_INET, "127.0.0.1", &ipv4address.sin_addr);

	// 내 포트 아무데나랑 묶어준다
	if (bind(m_hSocketHandle, (sockaddr*)&ipv4address, sizeof(ipv4address)) < 0)
	{
		throw std::exception("bind fail");
	}
}

void CSocket::Bind(const sockaddr_in& ipv4Endpoint)
{
	if (bind(m_hSocketHandle, (sockaddr*)&ipv4Endpoint, sizeof(ipv4Endpoint)) < 0)
	{
		throw std::exception("bind fail");
	}
}

void CSocket::Connect(const sockaddr_in& ipv4Endpoint)
{
	// input으로 받아온 종단점과 연결한다.
	if (connect(m_hSocketHandle, (sockaddr*)& ipv4Endpoint, sizeof(ipv4Endpoint)) < 0)
	{
		throw std::exception("connect fail");
	}
}

int CSocket::Send(const char* data, int length)
{
	send(m_hSocketHandle, data, length, 0);
	return 0;
}

void CSocket::Close()
{
	closesocket(m_hSocketHandle);
}

void CSocket::Listen()
{
	listen(m_hSocketHandle, 5000);
}

int CSocket::Accept(CSocket& acceptSocket, std::string& errorText)
{
	return 0;
}

int CSocket::Receive()
{
	return 0;
}
