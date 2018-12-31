#pragma once
#include <iostream>
#include <WinSock2.h>
#include <ws2bth.h>
#include <vector>
#include <process.h>
#include <ws2tcpip.h>
#include <Initguid.h>

#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::vector;

#define SOCKET_RECV_RETRY_SLEEP		(20)

enum {
	SOCKET_TCP = 0,
	SOCKET_UDP = 1,
	SOCKET_BTH = 2
};

enum {
	SOCKET_RECV = 0,
	SOCKET_SEND = 1
};

enum {
	WORK_MODE_SERVER = 0,
	WORK_MODE_CLIENT = 1
};

class CSocketAPI
{
public:
	CSocketAPI();
	~CSocketAPI();

protected:
	int StartUp();
	int CleanUp();

protected:
	int InitSocket(SOCKET& sock, int socketType);
	int BindSocket(SOCKET& sock, int socketType, USHORT port);
	int ConnectSocket(SOCKET& sock, int socketType, WCHAR* addr, USHORT port, int timeout);
	int AcceptSocket(SOCKET& sock, SOCKET& remoteSock);
	int ListenSocket(SOCKET& sock, int backLog);
	int BthSetService(SOCKET& sock);
	int EnableBlocking(SOCKET& sock, bool bBlock);
	int SetSocketTimeout(SOCKET& sock, int type, int timeout);
	static UINT WINAPI ThreadAccept(LPVOID param);

public:
	int StartServerSocket(USHORT port, int maxClientCnt, int socketType);
	int StartClientSocket(WCHAR* addr, USHORT port, int timeout, int socketType);
	int SendMsg(UINT sockIdx, char* sendBuf, int totalSendSize);
	int SendMsg(char* sendBuf, int totalSendSize);
	int SendMsg(sockaddr_in* remoteSockAddr, char* sendBuf, int sendSize);
	int RecvMsg(UINT sockIdx, char* recvBuf, int& recvSize, int maxRetryCnt);
	int RecvMsg(char* recvBuf, int& recvSize, int maxRetryCnt);
	int RecvMsg(sockaddr_in* remoteSockAddr, char* recvBuf, int& recvSize, int timeOut);
	int CloseSocket();

private:
	CRITICAL_SECTION m_csSend;
	CSADDR_INFO* m_pCSAddrInfo;
	WSAQUERYSET m_wsaQuerySet;

protected:
	SOCKET m_sockListen;
	SOCKET m_sockLocal;
	vector<SOCKET*> m_vecpSockRemote;
	vector<SOCKADDR_IN*> m_vecpSockAddr;
	UINT m_nMaxClient;
	UINT m_nWorkMode;
	UINT m_nSocketType;
	HANDLE m_hAcceptThread;
};