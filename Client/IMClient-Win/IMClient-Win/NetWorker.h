#pragma once
#include "SocketsAPI.h"
#include <deque>
using std::deque;

enum {
	NET_WORKER_STATE_UNCONNECTED = 0,
	NET_WORKER_STATE_CONNECTING = 1,
	NET_WORKER_STATE_CONNECTED = 2
};

typedef struct ST_DATA_HEAD_T
{
	unsigned char magic[3];		// Magic:0x5A 0x48 0x48
	unsigned char resv1;
	long totalLen;				// msg total length in bytes
	unsigned short msgType;
	unsigned char resv2[6];
}ST_DATA_HEAD;

typedef struct ST_SEND_DATA_T
{
	char* pSendBuf;
	unsigned char resv[3];
	ULONG bufSize;
}ST_SEND_DATA;

// Structure
typedef struct ST_MESSAGE_INFO_T
{
	SYSTEMTIME timeStamp;
	wstring content;
	bool fromServer;
	UCHAR resv[3];
}ST_MESSAGE_INFO;

typedef struct ST_ACCOUNT_INFO_T
{
	WCHAR ID[32];
	WCHAR email[32];
	WCHAR pwd[64];
	WCHAR nickName[32];
	UINT sex;
	UINT online;
	wstring draftMsg;
	vector<ST_MESSAGE_INFO> friendMsg;
	bool deleted;
	char resv[3];
}ST_ACCOUNT_INFO;

enum {
	// Client->Server
	NET_MSG_TYPE_ACCOUNT_REGIST_REQUEST = 0x0000,
	NET_MSG_TYPE_ACCOUNT_LOGIN_REQUEST = 0x0001,
	NET_MSG_TYPE_ACCOUNT_UPDATE_REQUEST = 0x0002,
	NET_MSG_TYPE_SEND_MESSAGE_REQUEST = 0x0010,
	NET_MSG_TYPE_ADD_FRIEND_REQUEST = 0x0021,
	NET_MSG_TYPE_UPDATE_FRIEND_LIST_REQUEST = 0x0022,
	NET_MSG_TYPE_UPDATE_FRIEND_INFO_REQUEST = 0x0023,
	NET_MSG_TYPE_DELETE_FRIEND_REQUEST = 0x0024,

	NET_MSG_TYPE_HEARTBEAT_REQUEST = 0x00F0,

	// Server->Client
	NET_MSG_TYPE_ACCOUNT_REGIST_RESPONSE = 0x1000,
	NET_MSG_TYPE_ACCOUNT_LOGIN_RESPONSE = 0x1001,
	NET_MSG_TYPE_ACCOUNT_UPDATE_RESPONSE = 0x1002,
	NET_MSG_TYPE_SEND_MESSAGE_RESPONSE = 0x1010,
	NET_MSG_TYPE_ADD_FRIEND_RESPONSE = 0x1021,
	NET_MSG_TYPE_UPDATE_FRIEND_LIST_RESPOSE = 0x1022,
	NET_MSG_TYPE_UPDATE_FRIEND_INFO_RESPONSE = 0x1023,
	NET_MSG_TYPE_DELETE_FRIEND_RESPONSE = 0x1025,

	NET_MSG_TYPE_ADD_FRIEND_PUSH = 0x1024,
	NET_MSG_TYPE_ONLINE_INFO_PUSH = 0x1030,
	NET_MSG_TYPE_DELETE_FRIEND_PUSH = 0x1032,

	NET_MSG_TYPE_HEARTBEAT_RESPONSE = 0x10F0
};

class CNetWorker : public CSocketAPI
{
public:
	CNetWorker();
	~CNetWorker();

	int Start();
	int Stop();
	int GetCurState() { return m_nCurState; };
	int HeartbeatCheck(bool bStart);

	int RegistAccount(wstring email, wstring pwd, wstring nickName, int sex);
	int LoginAccount(wstring code, wstring pwd);
	int UpdateAccount(wstring oldPassword, wstring pwd, wstring nickName, int sex);
	int SendFriendMessage(wstring myCode, wstring FriendCode, wstring msg);
	int AddFriend(wstring code);
	int UpdateFriendList();
	int UpdateFriendInfo(wstring code);
	int DelFriend(wstring code);

	int SendHeartbeat();
protected:
	UINT m_nHeartbeatCnt;
	int RecvMsg(char*& recvBuf, int& bufLen);

private:
	static UINT WINAPI ThreadRecvResponse(LPVOID param);
	static UINT WINAPI ThreadSendRequest(LPVOID param);

private:
	bool m_bStopThread;
	int m_nCurState;
	HANDLE m_hThreadRecv, m_hThreadSend;
	CRITICAL_SECTION m_csSendQueue;
	deque<ST_SEND_DATA> m_queSendData;
};