// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <string>
#include <iostream>
#include "duilib\UIlib.h"
#include <fstream>
#include "Utility.h"

using namespace DuiLib;
using std::wstring;
using std::string;

#pragma comment(lib, "duilib\\DuiLib.lib")


// Window messages define
#define WM_ACCOUNT_REGIST_RESPONSE		(WM_APP + 40)
#define WM_ACCOUNT_LOGIN_RESPONSE		(WM_APP + 41)
#define WM_ACCOUNT_UPDATE_RESPONSE		(WM_APP + 42)
#define WM_SEND_MESSAGE_RESPONSE		(WM_APP + 43)
#define WM_ADD_FRIEND_RESPONSE			(WM_APP + 44)
#define WM_UPDATE_FRIEND_LIST_RESPONSE	(WM_APP + 45)
#define WM_UPDATE_FRIEND_INFO_RESPONSE	(WM_APP + 46)
#define WM_ADD_FRIEND_PUSH				(WM_APP + 47)
#define WM_ONLINE_INFO_PUSH				(WM_APP + 48)
#define WM_SEND_MESSAGE_REQUEST			(WM_APP + 49)
#define WM_DELETE_FRIEND_RESPONSE		(WM_APP + 50)
#define WM_DELETE_FRIEND_PUSH			(WM_APP + 51)
#define WM_UPDATE_FRIEND_INFO_PUSH		(WM_APP + 52)

// menu message
#define WM_SHOW_FRIEND_INFO				(WM_APP + 100)
#define WM_DELETE_FRIEND				(WM_APP + 101)

// Window timer
#define TIMER_ID_HEARTBEAT				(10000)
#define TIMER_ELAPSE_HEARTBEAT			(3 * 1000)
#define TIMER_ID_LOGIN					(10001)
#define TIMER_ELAPSE_LOGIN				(3 * 1000)
#define TIMER_ID_REGIST					(10002)
#define TIMER_ELAPSE_REGIST				(3 * 1000)
#define TIMER_ID_UPDATE_ACCOUNT			(10003)
#define TIMER_ELAPSE_UPDATE_ACCOUNT		(3 * 1000)
//#define TIMER_ID_UPDATE_FRIEND_INFO		(10004)
//#define TIMER_ELAPSE_UPDATE_FRIEND_INFO		(3 * 1000)

// Config file
#define CFG_PUBLIC_CFG_FILE			L".\\UsrData\\Public\\config.ini"
#define CFG_PUBLIC_APP_NAME			L"PUBLIC"
#define CFG_PUBLIC_KEY_SAVE_PWD		L"SavePassword"
#define CFG_PUBLIC_KEY_AUTO_LOGIN	L"AutoLogin"
#define CFG_PUBLIC_KEY_ACCOUNT_ID	L"AccountID"
#define CFG_PUBLIC_KEY_ACCOUNT_SEX	L"AccountSex"


