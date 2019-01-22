#include "stdafx.h"
#include "NetWorker.h"
#include "jsoncpp/include/json.h"

extern HWND g_hWndRegist;
extern HWND g_hWndLogin;
extern HWND g_hWndMain;
extern HWND g_hWndAccountUpdate;

CNetWorker::CNetWorker()
	: m_nHeartbeatCnt(0)
	, m_nCurState(NET_WORKER_STATE_UNCONNECTED)
{
	::InitializeCriticalSection(&m_csSendQueue);
}

CNetWorker::~CNetWorker()
{
	::DeleteCriticalSection(&m_csSendQueue);
}

// Start network thread
int CNetWorker::Start()
{
	if (NET_WORKER_STATE_UNCONNECTED != m_nCurState) {
		return 0;
	}
	m_bStopThread = false;
	m_hThreadRecv = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, ThreadRecvResponse, this, 0, nullptr));
	Sleep(10);
	m_hThreadSend = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, ThreadSendRequest, this, 0, nullptr));
	
	if (m_hThreadRecv && m_hThreadSend) {
		return 0;
	}
	else {
		return -1;
	}
}

// Stop network thread and close sockets
int CNetWorker::Stop()
{
	cout << "NetWorker stop start" << endl;

	m_nCurState = NET_WORKER_STATE_UNCONNECTED;
	m_bStopThread = true;
	if (NET_WORKER_STATE_UNCONNECTED != m_nCurState) {
		CloseSocket();
	}
	::WaitForSingleObject(m_hThreadRecv, INFINITE);
	::CloseHandle(m_hThreadRecv);
	::WaitForSingleObject(m_hThreadSend, INFINITE);
	::CloseHandle(m_hThreadSend);

	cout << "NetWorker stop fin" << endl;

	return 0;
}

// Receive server response
UINT WINAPI CNetWorker::ThreadRecvResponse(LPVOID param)
{
	cout << "ThreadRecvResponse Start" << endl;

	CNetWorker* pNetWorker = static_cast<CNetWorker*>(param);
	if (!pNetWorker) {
		cout << "ThreadRecvResponse Error Fin" << endl;
		return 0;
	}
	int ret = 0;

	while (!pNetWorker->m_bStopThread) {
		// Waiting for server response
		if (NET_WORKER_STATE_CONNECTED == pNetWorker->m_nCurState) {
			char* pRecv = nullptr;		// Deleted by message handler
			int recvLen = 0;
			ret = pNetWorker->RecvMsg(pRecv, recvLen);
			if (0 == ret) {
				// Distributing windows messages
				ST_DATA_HEAD* pDataHead = reinterpret_cast<ST_DATA_HEAD*>(pRecv);
				if (!pRecv) {
					MessageBox(nullptr, L"NULL!", L"", 0);
				}
				switch (pDataHead->msgType) {
				case NET_MSG_TYPE_ACCOUNT_REGIST_RESPONSE:
					cout << "case Account regist respose" << endl;
					::PostMessage(g_hWndRegist, WM_ACCOUNT_REGIST_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_ACCOUNT_LOGIN_RESPONSE:
					cout << "case Account login response" << endl;
					::PostMessage(g_hWndLogin, WM_ACCOUNT_LOGIN_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_ACCOUNT_UPDATE_RESPONSE:
					cout << "case Account update response" << endl;
					::PostMessage(g_hWndAccountUpdate, WM_ACCOUNT_UPDATE_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_ADD_FRIEND_RESPONSE:
					cout << "case Add friend response" << endl;
					::PostMessage(g_hWndMain, WM_ADD_FRIEND_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_ADD_FRIEND_PUSH:
					cout << "case Update friend list push" << endl;
					::PostMessage(g_hWndMain, WM_ADD_FRIEND_PUSH, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_UPDATE_FRIEND_LIST_RESPOSE:
					cout << "case Update friend list response" << endl;
					::PostMessage(g_hWndMain, WM_UPDATE_FRIEND_LIST_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_UPDATE_FRIEND_INFO_RESPONSE:
					cout << "case Update friend info response" << endl;
					::PostMessage(g_hWndMain, WM_UPDATE_FRIEND_INFO_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_DELETE_FRIEND_RESPONSE:
					cout << "case Delete friend response" << endl;
					::PostMessage(g_hWndMain, WM_DELETE_FRIEND_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_SEND_MESSAGE_REQUEST:
					cout << "case Send message request" << endl;
					::PostMessage(g_hWndMain, WM_SEND_MESSAGE_REQUEST, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_SEND_MESSAGE_RESPONSE:
					cout << "case Send message response" << endl;
					::PostMessage(g_hWndMain, WM_SEND_MESSAGE_RESPONSE, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_ONLINE_INFO_PUSH:
					cout << "case Online info push" << endl;
					::PostMessage(g_hWndMain, WM_ONLINE_INFO_PUSH, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_DELETE_FRIEND_PUSH:
					cout << "case Online info push" << endl;
					::PostMessage(g_hWndMain, WM_DELETE_FRIEND_PUSH, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_UPDATE_FRIEND_INFO_PUSH:
					cout << "case Update friend info push" << endl;
					::PostMessage(g_hWndMain, WM_UPDATE_FRIEND_INFO_PUSH, reinterpret_cast<WPARAM>(pRecv), 0);
					break;
				case NET_MSG_TYPE_HEARTBEAT_RESPONSE:
					pNetWorker->m_nHeartbeatCnt = 0;
					break;
				default:
					cout << "case Error:" << pDataHead->msgType << endl;
					break;
				}
			}
			else if(-3 == ret){
				// No data at present
			}
			else {
				// Network error
				cout << "Close socket" << endl;
				pNetWorker->CloseSocket();
				pNetWorker->m_nCurState = NET_WORKER_STATE_UNCONNECTED;
			}
		}
		Sleep(20);
	}

	cout << "ThreadRecvResponse Fin" << endl; 
	return 0;
}

// Connect server and send local network request
UINT WINAPI CNetWorker::ThreadSendRequest(LPVOID param)
{
	cout << "ThreadSendRequest Start" << endl;
	CNetWorker* pNetWorker = static_cast<CNetWorker*>(param);
	if (!pNetWorker) {
		cout << "ThreadSendRequest Error Fin" << endl;
		return 0;
	}
	WCHAR wIPAddr[32] = { 0 };
	const int MAX_RETRY_CNT = 6;
	int port = 0;
	int ret = 0;
	while (!pNetWorker->m_bStopThread) {
		// Try to connect Server
		if (NET_WORKER_STATE_UNCONNECTED == pNetWorker->m_nCurState) {
			pNetWorker->m_nCurState = NET_WORKER_STATE_CONNECTING;
			::GetPrivateProfileStringW(L"ServerCFG", L"IPAddr", L"127.0.0.1", wIPAddr, sizeof(wIPAddr), L".\\IMClient.ini");
			port = ::GetPrivateProfileIntW(L"ServerCFG", L"Port", 60000, L".\\IMClient.ini");
			ret = pNetWorker->StartClientSocket(wIPAddr, port, 6 * 1000, SOCKET_TCP);
			if (0 != ret) {
				pNetWorker->m_nCurState = NET_WORKER_STATE_UNCONNECTED;
				pNetWorker->CloseSocket();
			}
			else {
				wcout << "Connect server OK" << std::endl;
				pNetWorker->m_nCurState = NET_WORKER_STATE_CONNECTED;
			}
		}

		// Dealing with network requests
		if (NET_WORKER_STATE_CONNECTED == pNetWorker->m_nCurState) {
			while (!pNetWorker->m_queSendData.empty()) {
				::EnterCriticalSection(&pNetWorker->m_csSendQueue);
				ST_SEND_DATA stData = pNetWorker->m_queSendData.at(0);
				// Send request
				int ret = 0;
				
				int retryCnt = 0;
				while (NET_WORKER_STATE_CONNECTED != pNetWorker->GetCurState()) {
					Sleep(500);
					if (MAX_RETRY_CNT == retryCnt++) {
						break;
					}
				}
				ret = pNetWorker->SendMsg(stData.pSendBuf, stData.bufSize);
				delete[] stData.pSendBuf;
				pNetWorker->m_queSendData.pop_front();
				::LeaveCriticalSection(&pNetWorker->m_csSendQueue);
			}
		}
		Sleep(20);
	}

	cout << "ThreadSendRequest Fin" << endl;
	return 0;
}

// Regist account with email, password, nickname and sex
int CNetWorker::RegistAccount(wstring email, wstring pwd, wstring nickName, int sex)
{
	wstring tmp = CUtility::RSAEncrypt(pwd);
	// Create json data
	wstring sendData = 
		wstring(L"{ \"email\": \"") + email + wstring(L"\",") +
		wstring(L"  \"nickname\": \"") + nickName + wstring(L"\",") +
		wstring(L"  \"sex\": ") + std::to_wstring(sex) + wstring(L",") + 
		wstring(L"  \"password\": \"") + tmp + wstring(L"\"}");
	std::wcout << "RegistAccount send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_ACCOUNT_REGIST_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	::EnterCriticalSection(&m_csSendQueue);
	ST_SEND_DATA stData = { 0 };
	stData.bufSize = totalLen;
	stData.pSendBuf = pSendBuffer;
	m_queSendData.push_back(stData);
	::LeaveCriticalSection(&m_csSendQueue);

	delete[] pUtf8Data;

	return 0;
}

// Login account with email(userID)  and password
int CNetWorker::LoginAccount(wstring code, wstring pwd)
{
	// Create json data
	wstring sendData =
		wstring(L"{ \"code\": \"") + code + wstring(L"\",") +
		wstring(L"  \"password\": \"") + CUtility::RSAEncrypt(pwd) + wstring(L"\"}");
	std::wcout << "LoginAccount send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_ACCOUNT_LOGIN_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	::EnterCriticalSection(&m_csSendQueue);
	ST_SEND_DATA stData = { 0 };
	stData.bufSize = totalLen;
	stData.pSendBuf = pSendBuffer;
	m_queSendData.push_back(stData);
	::LeaveCriticalSection(&m_csSendQueue);

	delete[] pUtf8Data;

	return 0;
}

// Update account info
int CNetWorker::UpdateAccount(wstring oldPassword, wstring pwd, wstring nickName, int sex)
{
	// Create json data
	wstring sendData =
		wstring(L"{\"oldPassword\":\"") + CUtility::RSAEncrypt(oldPassword) + wstring(L"\",") +
		wstring(L"  \"nickname\":\"") + nickName + wstring(L"\",") +
		wstring(L"  \"sex\":") + std::to_wstring(sex) + wstring(L",") +
		wstring(L"  \"newPassword\":\"") + CUtility::RSAEncrypt(pwd) + wstring(L"\"}");
	std::wcout << "UpdateAccount send data: " << sendData << std::endl;
	
	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_ACCOUNT_UPDATE_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Send messages to specified friend
int CNetWorker::SendFriendMessage(wstring myCode, wstring friendCode, wstring msg)
{
	// Create json data
	wstring sendData =
		wstring(L"{ \"fromUser\": \"") + myCode + wstring(L"\",") +
		wstring(L"  \"toUser\": \"") + friendCode + wstring(L"\",") +
		wstring(L"  \"message\": \"") + msg + wstring(L"\"}");
	std::wcout << "SendFriendMessage send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_SEND_MESSAGE_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Add a friend by userID or email
int CNetWorker::AddFriend(wstring code)
{
	// Create json data
	wstring sendData =
		wstring(L"{\"symbol\":\"") + code + wstring(L"\"}");
	std::wcout << "AddFriend send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_ADD_FRIEND_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Update friend list information
int CNetWorker::UpdateFriendList()
{
	// Create json data
	wstring sendData =
		wstring(L"{}");
	std::wcout << "UpdateFriendList send data: " << sendData << std::endl;
	

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_UPDATE_FRIEND_LIST_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Update specified friend information
int CNetWorker::UpdateFriendInfo(wstring code)
{
	// Create json data
	wstring sendData =
		wstring(L"{ \"code\": \"") + code + wstring(L"\"}");
	std::wcout << "UpdateFriendInfo send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_UPDATE_FRIEND_INFO_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Send deleting friend request
int CNetWorker::DelFriend(wstring code)
{
	// Create json data
	wstring sendData =
		wstring(L"{ \"code\": \"") + code + wstring(L"\"}");
	std::wcout << "DelFriend send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_DELETE_FRIEND_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Send heartbeat data
int CNetWorker::SendHeartbeat()
{
	// Create json data
	wstring sendData =
		wstring(L"{") + wstring(L"}");
	//std::wcout << "SendHeartbeat send data: " << sendData << std::endl;

	// UTF-16 -> UTF-8
	char* pUtf8Data = CUtility::Utf16ToUtf8(sendData.data());

	// Create send buffer
	int totalLen = sizeof(ST_DATA_HEAD) + strlen(pUtf8Data);
	ST_DATA_HEAD stDataHead = { 0 };
	stDataHead.magic[0] = 0x5A;
	stDataHead.magic[1] = 0x48;
	stDataHead.magic[2] = 0x48;
	stDataHead.totalLen = htonl(strlen(pUtf8Data));
	stDataHead.msgType = htons(NET_MSG_TYPE_HEARTBEAT_REQUEST);
	char* pSendBuffer = new char[totalLen];
	memset(pSendBuffer, 0, totalLen);
	memcpy_s(pSendBuffer, totalLen, &stDataHead, sizeof(stDataHead));
	memcpy_s(pSendBuffer + sizeof(stDataHead), totalLen - sizeof(stDataHead), pUtf8Data, strlen(pUtf8Data));

	// Send request
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED == GetCurState()) {
		ret = SendMsg(pSendBuffer, totalLen);
	}
	else {
		return -1;
	}

	//delete[] pUtf8Data;
	delete[] pSendBuffer;

	return ret;
}

// Receive tcp socket data
int CNetWorker::RecvMsg(char*& recvBuf, int& bufLen)
{
	if (INVALID_SOCKET == m_sockLocal) {
		return -1;
	}

	int ret = 0;
	char* pRecv = nullptr;
	int retryCnt = 0;

	// recv data head
	ST_DATA_HEAD stDataHead = { 0 };
	pRecv = reinterpret_cast<char*>(&stDataHead);
	while (pRecv - reinterpret_cast<char*>(&stDataHead) < sizeof(stDataHead)) {
		int recvCnt = ::recv(m_sockLocal, pRecv, 
			sizeof(stDataHead) - (pRecv - reinterpret_cast<char*>(&stDataHead)), 0);
		if (0 == recvCnt) {
			ret = -1;
			cout << "recv cutdown" << endl;
			break;
		}
		else if (SOCKET_ERROR == recvCnt) {
			int errCode = ::WSAGetLastError();
			if (WSAEWOULDBLOCK != errCode) {
				cout << "recv error:" << errCode << endl;
				ret = -2;
			}
			else {
				ret = -3;	// no data at present
			}
			break;
		}
		// recv ok
		pRecv += recvCnt;
	}

	if (0 == ret) {
		stDataHead.msgType = ntohs(stDataHead.msgType);
		stDataHead.totalLen = ntohl(stDataHead.totalLen);
		// recv msg data
		recvBuf = new char[sizeof(stDataHead) + stDataHead.totalLen];	// delete by caller
		memcpy_s(recvBuf, sizeof(stDataHead), &stDataHead, sizeof(stDataHead));
		pRecv = recvBuf + sizeof(stDataHead);
		while (pRecv - recvBuf - sizeof(stDataHead) < (ULONG)stDataHead.totalLen) {
			int recvCnt = ::recv(m_sockLocal, pRecv,
				stDataHead.totalLen - (pRecv - recvBuf - sizeof(stDataHead)), 0);
			if (0 == recvCnt) {
				ret = -1;
				cout << "recv cutdown" << endl;
				break;
			}
			else if (SOCKET_ERROR == recvCnt) {
				int errCode = ::WSAGetLastError();
				if (WSAEWOULDBLOCK != errCode) {
					cout << "recv error:" << errCode << endl;
					ret = -2;
				}
				else {
					ret = -3;	// no data at present
				}
				break;
			}
			// recv ok
			pRecv += recvCnt;
		}

		bufLen = sizeof(stDataHead) + stDataHead.totalLen;
		char log[128] = { 0 };
		sprintf_s(log, "recv data fin: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X   %02X %02X\n",
			(UCHAR)recvBuf[0], (UCHAR)recvBuf[1], (UCHAR)recvBuf[2], (UCHAR)recvBuf[3], (UCHAR)recvBuf[4], (UCHAR)recvBuf[5], (UCHAR)recvBuf[6], (UCHAR)recvBuf[7],
			(UCHAR)recvBuf[8], (UCHAR)recvBuf[9], (UCHAR)recvBuf[10], (UCHAR)recvBuf[11], (UCHAR)recvBuf[12], (UCHAR)recvBuf[13], (UCHAR)recvBuf[14], (UCHAR)recvBuf[15],
			(UCHAR)recvBuf[16], (UCHAR)recvBuf[17]);
		if (0xF0 == (UCHAR)recvBuf[8] && 0x10 == (UCHAR)recvBuf[9]) {
			;	// skip hearbeat
		}
		else {
			printf(log);
		}
	}
	
	return ret;
}

int CNetWorker::HeartbeatCheck(bool bStart)
{
	int ret = 0;
	if (bStart) {
		if (NET_WORKER_STATE_CONNECTED == m_nCurState) {
			::SetTimer(g_hWndMain, TIMER_ID_HEARTBEAT, TIMER_ELAPSE_HEARTBEAT, nullptr);
		}
		else {
			ret = -1;
		}
	}
	else {
		::KillTimer(g_hWndMain, TIMER_ID_HEARTBEAT);
	}
	return ret;
}
