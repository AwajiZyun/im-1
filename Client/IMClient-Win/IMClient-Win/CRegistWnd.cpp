#include "stdafx.h"
#include "CRegistWnd.h"
#include "NetWorker.h"
#include "jsoncpp\include\json.h"

HWND g_hWndRegist = nullptr;
extern CNetWorker* g_pNetWorker;
extern ST_ACCOUNT_INFO g_accountInfo;

#if 0
// Sys msg
LRESULT CRegistWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg) {
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:
		lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO:
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_ACTIVATE:
		bHandled = FALSE;	break;
	case WM_ACCOUNT_REGIST_RESPONSE:
		lRes = OnRegistResponse(wParam);	
		if (0 == lRes) {
			// Regist OK
			Close();
		}
		break;
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) {
		return lRes;
	}
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) {
		return lRes;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CRegistWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	g_hWndRegist = this->m_hWnd;

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(L"xml\\Regist.xml", (UINT)0, (UINT)0, &m_PaintManager);
	if (!pRoot) {
		MessageBox(NULL, L"UI failed", L"", 0);
		return 0;
	}
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);

	if (0 == InitControls()) {
		return 0;
	}

	MessageBox(nullptr, L"xml error", L"Error", MB_ICONEXCLAMATION);
	return -1;
}

LRESULT CRegistWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CRegistWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_PaintManager.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CRegistWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CRegistWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == SC_CLOSE) {
		Close();
		bHandled = TRUE;
		return 0;
	}
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);

	return lRes;
}
#endif

LRESULT CRegistWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	bHandled = true;

	switch (uMsg)
	{
	case WM_ACCOUNT_REGIST_RESPONSE:
		lRes = OnRegistResponse(uMsg, wParam, lParam, bHandled);
		if (0 == lRes) {
			Close();	// Regist OK, close dialog
		}
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = false;
	}

	return lRes;
}

// UI Msg
void CRegistWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose) {
			SendMessage(WM_CLOSE);
			return;
		}
		// Regist account
		else if (msg.pSender == m_pBtnRegist) {
			OnBtnRegist();
		}
	}
}

LRESULT CRegistWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (TIMER_ID_REGIST == wParam) {
		bHandled = true;
		::KillTimer(m_hWnd, TIMER_ID_REGIST);
		m_pBtnRegist->SetText(L"注册");
		m_pBtnRegist->SetEnabled(true);
		MessageBox(nullptr, L"连接服务器失败", L"错误", MB_ICONERROR);
	}
	else {
		bHandled = false;
	}
	return 0;
}

void CRegistWnd::InitWindow()
{
	g_hWndRegist = this->m_hWnd;

	if (0 == InitControls()) {
		return;
	}

	MessageBox(nullptr, L"xml error", L"Error", MB_ICONEXCLAMATION);
}

int CRegistWnd::InitControls()
{
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pBtnRegist = static_cast<CButtonUI*>(m_pm.FindControl(L"btnRegist"));

	m_pEditNickname = static_cast<CEditUI*>(m_pm.FindControl(L"editNickname"));
	m_pEditMail = static_cast<CEditUI*>(m_pm.FindControl(L"editMailAddr"));
	m_pEditPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPwd"));
	m_pEditPwdConfirm = static_cast<CEditUI*>(m_pm.FindControl(L"editPwdConfirm"));
	m_pCommboSex = static_cast<CComboUI*>(m_pm.FindControl(L"comboSex"));

	if (m_pBtnClose && m_pBtnRegist && m_pEditMail && m_pEditNickname && m_pEditPwd && m_pEditPwdConfirm && m_pCommboSex) {
		m_pEditNickname->SetFocus();
		return 0;
	}

	return -1;
}

// Server regist response handler
LRESULT CRegistWnd::OnRegistResponse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::KillTimer(m_hWnd, TIMER_ID_REGIST);
	m_pBtnRegist->SetEnabled(true);
	g_pNetWorker->Stop();
	int ret = -1;
	ST_DATA_HEAD* pStDataHead = reinterpret_cast<ST_DATA_HEAD*>(wParam);
	if (!pStDataHead) {
		MessageBox(nullptr, L"Bug", L"", 0);
		return -1;
	}
	char* pJsonString = reinterpret_cast<char*>(pStDataHead) + sizeof(ST_DATA_HEAD);
	WCHAR* pWJsonString = CUtility::Utf8ToUtf16(pJsonString);
	char* pAnsiJsonString = CUtility::Utf16ToGB(pWJsonString);
	cout << "OnRegistResponse:" << pAnsiJsonString << endl;
	// Parse json string
	Json::CharReaderBuilder builder;
	Json::CharReader * reader = builder.newCharReader();
	Json::Value root;
	string errors;
	bool bSuccess;
	string strCode;
	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)){
		if (!root["success"].isNull()){
			bSuccess = root["success"].asBool();
		}
		Json::Value valData = root["data"];
		if (!valData["code"].isNull()) {
			strCode = valData["code"].asString();
			cout << "code:" << strCode;
		}
		else {
			cout << "OnRegistResponse code null" << endl;
		}
	}
	delete[] reader;
	if (bSuccess) {
		ret = 0;
		WCHAR* wpMsg = CUtility::GBToUtf16((string("注册成功。您的登录账号为：") + strCode).data());
		MessageBox(nullptr, wpMsg, L"提示", MB_ICONINFORMATION);
		delete[] wpMsg;

		// Update current user info;
		WCHAR* wCode = CUtility::GBToUtf16(strCode.data());
		memcpy_s(g_accountInfo.ID, sizeof(g_accountInfo.ID), wCode, wcslen(wCode) * sizeof(WCHAR));
	}
	else {
		MessageBox(nullptr, L"注册失败", L"提示", MB_ICONERROR);
		ret = -2;
	}

	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

// Account regist button handler
LRESULT CRegistWnd::OnBtnRegist()
{
	if (!g_pNetWorker) {
		return -1;
	}

	m_pBtnRegist->SetEnabled(false);
	// Get regist info
	CDuiString email = m_pEditMail->GetText();
	CDuiString pwd = m_pEditPwd->GetText();
	CDuiString nickName = m_pEditNickname->GetText();
	CDuiString sex = m_pCommboSex->GetText();
	CDuiString pwdConfirm = m_pEditPwdConfirm->GetText();
	if (email == L"" || pwd == L"" || nickName == L"" || pwdConfirm == L"") {
		MessageBox(nullptr, L"邮箱、昵称、密码不能为空", L"提示", MB_ICONERROR);
		return -2;
	}
	if (pwdConfirm != pwd) {
		MessageBox(nullptr, L"两次输入密码不一致！", L"提示", MB_ICONERROR);
		return -2;
	}
	int nSex = 0;
	if (sex == L"男") {
		nSex = 0;
	}
	else if (sex == L"女") {
		nSex = 1;
	}
	else {
		nSex = 2;
	}

	// Send regist request
	g_pNetWorker->Start();
	int ret = g_pNetWorker->RegistAccount(email.GetData(), pwd.GetData(), nickName.GetData(), nSex);
	if (0 != ret) {
		MessageBox(nullptr, L"连接服务器失败！", L"提示", MB_ICONERROR);
		return -1;
	}

	// Save account info
	memcpy_s(g_accountInfo.nickName, sizeof(g_accountInfo.nickName), nickName.GetData(), nickName.GetLength() * sizeof(WCHAR));
	memcpy_s(g_accountInfo.email, sizeof(g_accountInfo.email), email.GetData(), email.GetLength() * sizeof(WCHAR));
	memcpy_s(g_accountInfo.pwd, sizeof(g_accountInfo.pwd), pwd.GetData(), pwd.GetLength() * sizeof(WCHAR));
	g_accountInfo.sex = nSex;

	::SetTimer(m_hWnd, TIMER_ID_REGIST, TIMER_ELAPSE_REGIST, nullptr);

	return 0;
}