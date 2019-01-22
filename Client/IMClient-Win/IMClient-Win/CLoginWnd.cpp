#include "stdafx.h"
#include "CLoginWnd.h"
#include "CRegistWnd.h"
#include "CMainWnd.h"
#include "NetWorker.h"
#include "jsoncpp\include\json.h"

HWND g_hWndLogin = nullptr;
CNetWorker* g_pNetWorker = nullptr;
ST_ACCOUNT_INFO g_accountInfo = { 0 };

CLoginWnd::CLoginWnd()
	: m_bExitProcess(true)
{
}

// Sys msg
LRESULT CLoginWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	bHandled = true;

	switch (uMsg) 
	{
	case WM_ACCOUNT_LOGIN_RESPONSE:
		lRes = OnLoginResponse(uMsg, wParam, lParam, bHandled);	break;
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = false;
	}

	return lRes;
}

// UI Msg
void CLoginWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose) {
			SendMessage(WM_CLOSE);
			return;
		}
		else if (msg.pSender == m_pBtnMinimize) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pBtnSetting) {
			MessageBox(nullptr, L"IM Demo Ver0.1.1 alpha\nCopyright(C) 2018", L"Setting", 0);
			return;
		}
		else if (msg.pSender == m_pBtnRegist) {
			OnBtnRegist();
			return;
		}
		else if (msg.pSender == m_pBtnForgetPwd) {
			MessageBox(nullptr, L"你不会重新注册么?", L"忘记密码", 0);
			return;
		}
		else if (msg.pSender == m_pBtnLogin) {
			OnBtnLogin();
		}
	}
	else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {
		if (msg.pSender == m_pOptionSavePwd) {
			OnBtnSavePwd();
		}
		else if (msg.pSender == m_pOptionAutoLogin) {
			OnBtnAutoLogin();
		}
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMSELECT) {
		OnComboUsrNameSelected();
	}
	else {
		// nothing
	}
	__super::Notify(msg);
}

void CLoginWnd::InitWindow()
{
	g_hWndLogin = this->m_hWnd;

	// Prepare network 
	if (!g_pNetWorker) {
		g_pNetWorker = new(std::nothrow) CNetWorker();
		if (!g_pNetWorker) {
			MessageBox(nullptr, L"new failed", L"Error", MB_ICONERROR);
			return;
		}
	}

	if (0 == InitControls()) {
		return;
	}

	MessageBox(nullptr, L"login xml error", L"Error", MB_ICONERROR);
}

LRESULT CLoginWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CLoginWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bExitProcess) {
		::PostQuitMessage(0L);
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CLoginWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (TIMER_ID_LOGIN == wParam) {
		bHandled = true;
		::KillTimer(m_hWnd, TIMER_ID_LOGIN);
		g_pNetWorker->Stop();
		m_pBtnLogin->SetText(L"登录");
		m_pBtnLogin->SetEnabled(true);
		MessageBox(nullptr, L"连接服务器失败", L"错误", MB_ICONERROR);
	}
	else {
		bHandled = false;
	}
	return 0;
}

int CLoginWnd::InitControls()
{
	m_pCtlHeadImg = static_cast<CControlUI*>(m_pm.FindControl(L"ctlHeadImg"));
	m_pBtnSetting = static_cast<CButtonUI*>(m_pm.FindControl(L"btnSetting"));
	m_pBtnMinimize = static_cast<CButtonUI*>(m_pm.FindControl(L"btnMin"));
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pBtnLogin = static_cast<CButtonUI*>(m_pm.FindControl(L"btnLogin"));
	m_pBtnRegist = static_cast<CButtonUI*>(m_pm.FindControl(L"btnRegist"));
	m_pBtnForgetPwd = static_cast<CButtonUI*>(m_pm.FindControl(L"btnForgetPwd"));
	m_pEditUsrCode = static_cast<CEditUI*>(m_pm.FindControl(L"editUsrName"));
	m_pEditUsrPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPassword"));
	m_pOptionSavePwd = static_cast<COptionUI*>(m_pm.FindControl(L"optionSavePwd"));
	m_pOptionAutoLogin = static_cast<COptionUI*>(m_pm.FindControl(L"optionAutoLogin"));
	m_pComboUsrName = static_cast<CComboUI*>(m_pm.FindControl(L"comboUsrName"));

	if (m_pBtnSetting && m_pBtnMinimize && m_pBtnClose && m_pBtnLogin && m_pBtnRegist && m_pBtnForgetPwd &&
		m_pEditUsrCode && m_pEditUsrPwd && m_pOptionSavePwd && m_pOptionAutoLogin && m_pCtlHeadImg && m_pComboUsrName) {
		// load xml data
		if (0 == CUtility::GetXmlUsrInfo(L".\\UsrData\\Public\\usrInfo.xml", m_vecLoginUsrInfo)) {
			for (auto info : m_vecLoginUsrInfo) {
				CListLabelElementUI* pLabel = new CListLabelElementUI();
				pLabel->SetText(info.ID);
				m_pComboUsrName->Add(pLabel);
			}
		}

		if (1 == ::GetPrivateProfileIntW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_SAVE_PWD, 0, CFG_PUBLIC_CFG_FILE)) {
			WCHAR wUsrID[32] = { 0 };
			::GetPrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_ACCOUNT_ID, L"", wUsrID, sizeof(wUsrID), CFG_PUBLIC_CFG_FILE);
			int sex = ::GetPrivateProfileInt(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_ACCOUNT_SEX, 0, CFG_PUBLIC_CFG_FILE);
			if (!m_vecLoginUsrInfo.empty()) {
				for (UINT idx = 0; idx < m_vecLoginUsrInfo.size(); idx++) {
					if (0 == wcscmp(wUsrID, m_vecLoginUsrInfo[idx].ID)) {
						m_pComboUsrName->SelectItem(idx);
						break;
					}
				}
			}

			m_pOptionSavePwd->Selected(true, false);
			if (0 == sex) {
				m_pCtlHeadImg->SetBkImage(L"HeadMale.png");
			}
			else if (1 == sex) {
				m_pCtlHeadImg->SetBkImage(L"HeadFemale.png");
			}
			else {
				m_pCtlHeadImg->SetBkImage(L"Anonymous.png");
			}
		}
		if (1 == ::GetPrivateProfileIntW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_AUTO_LOGIN, 0, CFG_PUBLIC_CFG_FILE)) {
			m_pOptionAutoLogin->Selected(true, false);
			OnBtnLogin();
		}
		m_pEditUsrCode->SetFocus();
		return 0;
	}
	else {
		return -1;
	}
}

// Send login request
LRESULT CLoginWnd::OnBtnLogin()
{
	int ret = 0;
	CDuiString usrName = m_pEditUsrCode->GetText();
	CDuiString usrPwd = m_pEditUsrPwd->GetText();
	if (usrName.IsEmpty() || usrPwd.IsEmpty()) {
		MessageBox(nullptr, L"账户名和密码不能为空", L"提示", MB_ICONINFORMATION);
		ret = -1;
	}
	else {
		m_pBtnLogin->SetEnabled(false);
		// Save ID
		if (1 == ::GetPrivateProfileIntW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_SAVE_PWD, 0, CFG_PUBLIC_CFG_FILE)) {
			::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_ACCOUNT_ID, usrName, CFG_PUBLIC_CFG_FILE);
		}
		else {
			::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_ACCOUNT_ID, L"", CFG_PUBLIC_CFG_FILE);
		}

		m_pBtnLogin->SetText(L"登录中...");
		g_pNetWorker->Start();
		ret = g_pNetWorker->LoginAccount(usrName.GetData(), usrPwd.GetData());
		::SetTimer(m_hWnd, TIMER_ID_LOGIN, TIMER_ELAPSE_LOGIN, nullptr);
		if(0 != ret){
			MessageBox(nullptr, L"服务器连接失败", L"提示", MB_ICONINFORMATION);
			ret = -2;
		}

		// Write xml
		ST_ACCOUNT_INFO stAccountInfo = { 0 };
		memcpy_s(stAccountInfo.ID, sizeof(stAccountInfo.ID), usrName, wcslen(usrName) * sizeof(WCHAR));
		memcpy_s(stAccountInfo.pwd, sizeof(stAccountInfo.pwd), usrPwd, wcslen(usrPwd) * sizeof(WCHAR));
		ret = CUtility::WriteXmlUsrInfo(L".\\UsrData\\Public\\usrInfo.xml", stAccountInfo);
	}

	return ret;
} 

LRESULT CLoginWnd::OnBtnRegist()
{
	CRegistWnd registWnd;
	registWnd.Create(this->m_hWnd, L"RegistWnd", UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_FRAME);
	registWnd.CenterWindow();
	registWnd.ShowModal();

	if (!wstring(g_accountInfo.ID).empty()) {
		m_pEditUsrCode->SetText(g_accountInfo.ID);
		m_pEditUsrPwd->SetText(g_accountInfo.pwd);
	}

	return 0;
}

LRESULT CLoginWnd::OnBtnSavePwd()
{
	if (m_pOptionSavePwd->IsSelected()) {
		::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_SAVE_PWD, L"1", CFG_PUBLIC_CFG_FILE);
	}
	else {
		::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_SAVE_PWD, L"0", CFG_PUBLIC_CFG_FILE);
		m_pOptionAutoLogin->Selected(false);
	}
	return 0;
}

LRESULT CLoginWnd::OnBtnAutoLogin()
{
	if (m_pOptionAutoLogin->IsSelected()) {
		::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_AUTO_LOGIN, L"1", CFG_PUBLIC_CFG_FILE);
		m_pOptionSavePwd->Selected(true);
	}
	else {
		::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_AUTO_LOGIN, L"0", CFG_PUBLIC_CFG_FILE);
	}
	return 0;
}

LRESULT CLoginWnd::OnComboUsrNameSelected()
{
	if (!m_pComboUsrName || !m_pEditUsrCode) {
		return -1;
	}
	// Load account ID
	m_pEditUsrCode->SetText(m_pComboUsrName->GetText());
	if (1 == ::GetPrivateProfileIntW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_SAVE_PWD, 0, CFG_PUBLIC_CFG_FILE)) {
		// Load account password
		m_pEditUsrPwd->SetText(m_vecLoginUsrInfo[m_pComboUsrName->GetCurSel()].pwd);
	}
	return 0;
}

// Server login response handler
LRESULT CLoginWnd::OnLoginResponse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int ret = 0;
	::KillTimer(m_hWnd, TIMER_ID_LOGIN);
	m_pBtnLogin->SetEnabled(true);
	ST_DATA_HEAD* pStDataHead = reinterpret_cast<ST_DATA_HEAD*>(wParam);
	if (!pStDataHead) {
		return -1;
	}
	char* pJsonString = reinterpret_cast<char*>(pStDataHead) + sizeof(ST_DATA_HEAD);
	WCHAR* pWJsonString = CUtility::Utf8ToUtf16(pJsonString);
	char* pAnsiJsonString = CUtility::Utf16ToGB(pWJsonString);
	// Parse json string
	Json::CharReaderBuilder builder;
	Json::CharReader * reader = builder.newCharReader();
	Json::Value root;
	string errors;
	bool bSuccess;
	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)) {
		if (!root["success"].isNull()) {
			bSuccess = root["success"].asBool();
		}
	}
	if (bSuccess) {
		// Save local account information
		Json::Value data = root["data"];
		if (!data["code"].isNull()) {
			WCHAR* wCode = CUtility::GBToUtf16(data["code"].asString().data());
			WCHAR* wEmail = CUtility::GBToUtf16(data["email"].asString().data());
			WCHAR* wNickname = CUtility::GBToUtf16(data["nickname"].asString().data());
			g_accountInfo.sex = data["sex"].asInt();
			memcpy_s(g_accountInfo.ID, sizeof(g_accountInfo.ID), wCode, wcslen(wCode) * sizeof(WCHAR));
			memcpy_s(g_accountInfo.email, sizeof(g_accountInfo.email), wEmail, wcslen(wEmail) * sizeof(WCHAR));
			memcpy_s(g_accountInfo.nickName, sizeof(g_accountInfo.nickName), wNickname, wcslen(wNickname) * sizeof(WCHAR));

			WCHAR savePath[MAX_PATH] = { 0 };
			swprintf_s(savePath, L"UsrData\\Accounts\\%s", g_accountInfo.ID);
			::CreateDirectory(savePath, nullptr);
			swprintf_s(savePath, L"UsrData\\Accounts\\%s\\usrInfo.dat", g_accountInfo.ID);
			ofstream out;
			out.open(savePath, std::ios::binary);
			if (out.is_open()) {
				out.write(reinterpret_cast<char*>(&g_accountInfo), sizeof(g_accountInfo));
				out.close();
			}
			// Save public account info
			WCHAR strSex[4] = { 0 };
			_itow_s(g_accountInfo.sex, strSex, 10);
			::WritePrivateProfileStringW(CFG_PUBLIC_APP_NAME, CFG_PUBLIC_KEY_ACCOUNT_SEX, strSex, CFG_PUBLIC_CFG_FILE);

			delete[] wCode;
			delete[] wEmail;
			delete[] wNickname;
		}

		// Create main dialog
		CMainWnd* pMainWnd = new CMainWnd();
		pMainWnd->Create(nullptr, L"MainWnd", UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_FRAME);
		pMainWnd->CenterWindow();
		pMainWnd->ShowWindow();

		m_bExitProcess = false;
		::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
	else {
		g_pNetWorker->Stop();
		MessageBox(nullptr, L"登录失败", L"错误", MB_ICONERROR);
		m_pBtnLogin->SetText(L"登录");
		ret = -2;
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}
