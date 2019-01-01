#include "stdafx.h"
#include "CUsrInfoWnd.h"
#include "NetWorker.h"
#include "jsoncpp\include\json.h"

extern CNetWorker* g_pNetWorker;
extern ST_ACCOUNT_INFO g_accountInfo;
HWND g_hWndAccountUpdate = nullptr;


// Sys msg
#if 0
LRESULT CUsrInfoWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg) {
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:
		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
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
	case WM_ACCOUNT_UPDATE_RESPONSE:
		lRes = OnUpdateAccountResponse(wParam);
		break;
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
LRESULT CUsrInfoWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(L"xml\\UsrInfo.xml", (UINT)0, (UINT)0, &m_PaintManager);
	if (!pRoot) {
		MessageBox(NULL, L"UI failed", L"", 0);
		return 0;
	}
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);
	g_hWndAccountUpdate = m_hWnd;

	if (0 == InitControls()) {
		return 0;
	}

	MessageBox(nullptr, L"xml error", L"Error", MB_ICONERROR);
	return -1;
}

LRESULT CUsrInfoWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CUsrInfoWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CUsrInfoWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CUsrInfoWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CUsrInfoWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CUsrInfoWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CUsrInfoWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);

	return lRes;
}
#endif

// UI Msg
void CUsrInfoWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose || 
			msg.pSender == m_pBtnClose2) {
			Close();
		}
		else if (msg.pSender == m_pBtnUpdate) {
			OnBtnUpdateAccount();
		}
	}
}

void CUsrInfoWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	//delete this;
}

void CUsrInfoWnd::InitWindow()
{
	g_hWndAccountUpdate = m_hWnd;

	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pBtnClose2 = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose2"));
	m_pBtnUpdate = static_cast<CButtonUI*>(m_pm.FindControl(L"btnUpdate"));
	m_pEditNickName = static_cast<CEditUI*>(m_pm.FindControl(L"editNickname"));
	m_pEditEmail = static_cast<CEditUI*>(m_pm.FindControl(L"editEmail"));
	m_pComboSex = static_cast<CComboUI*>(m_pm.FindControl(L"comboSex"));
	m_pEditOldPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPwdOld"));
	m_pEditNewPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPwd"));
	m_pEditNewPwdConfirm = static_cast<CEditUI*>(m_pm.FindControl(L"editPwdConfirm"));

	if (m_pBtnClose && m_pBtnClose2 && m_pBtnUpdate && m_pEditNickName && m_pComboSex &&
		m_pEditOldPwd && m_pEditNewPwd && m_pEditNewPwdConfirm && m_pEditEmail) {
		m_pEditNickName->SetText(g_accountInfo.nickName);
		m_pComboSex->SelectItem(g_accountInfo.sex);
		m_pEditEmail->SetText(g_accountInfo.email);
		return;
	}

	MessageBox(nullptr, L"xml error", L"Error", MB_ICONERROR);
}

LRESULT CUsrInfoWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	bHandled = TRUE;

	switch (uMsg) {
	case WM_ACCOUNT_UPDATE_RESPONSE:
		lRes = OnUpdateAccountResponse(wParam);	break;
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}

	return lRes;
}

LRESULT CUsrInfoWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (TIMER_ID_UPDATE_ACCOUNT == wParam) {
		bHandled = true;
		::KillTimer(m_hWnd, TIMER_ID_UPDATE_ACCOUNT);
		MessageBox(nullptr, L"服务器响应超时", L"错误", MB_ICONERROR);
	}
	else {
		bHandled = false;
	}
	return 0;
}

// Receive update account response handle
LRESULT CUsrInfoWnd::OnUpdateAccountResponse(WPARAM wParam)
{
	::KillTimer(m_hWnd, TIMER_ID_UPDATE_ACCOUNT);
	int ret = 0;
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
	delete[] reader;
	if (bSuccess) {
		MessageBox(nullptr, L"保存成功", L"提示", MB_ICONINFORMATION);
		Close();
	}
	else {
		MessageBox(nullptr, L"保存失败，请检查密码", L"错误", MB_ICONERROR);
		ret = -2;
	}
	m_pBtnUpdate->SetEnabled(true);

	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;
	return ret;
}

// Send update account information requset
LRESULT CUsrInfoWnd::OnBtnUpdateAccount()
{
	int ret = 0;
	if (NET_WORKER_STATE_CONNECTED != g_pNetWorker->GetCurState()) {
		MessageBox(nullptr, L"未连接服务器", L"提示", MB_ICONINFORMATION);
		return -1;
	}
	
	CDuiString strNickName = m_pEditNickName->GetText();
	CDuiString strSex = m_pComboSex->GetText();
	CDuiString strOldPwd = m_pEditOldPwd->GetText();
	CDuiString strNewPwd = m_pEditNewPwd->GetText();
	CDuiString strNewPwdConfirm = m_pEditNewPwdConfirm->GetText();
	if (strNewPwdConfirm != strNewPwd) {
		MessageBox(nullptr, L"两次输入密码不一致", L"提示", MB_ICONINFORMATION);
		return -2;
	}
	int nSex = 0;
	if (strSex == L"男") {
		nSex = 0;
	}
	else if (strSex == L"女") {
		nSex = 1;
	}
	else {
		nSex = 2;
	}
	ret = g_pNetWorker->UpdateAccount(strOldPwd.GetData(), strNewPwd.GetData(), strNickName.GetData(), nSex);
	m_pBtnUpdate->SetEnabled(false);
	::SetTimer(m_hWnd, TIMER_ID_UPDATE_ACCOUNT, TIMER_ELAPSE_UPDATE_ACCOUNT, nullptr);

	return ret;
}