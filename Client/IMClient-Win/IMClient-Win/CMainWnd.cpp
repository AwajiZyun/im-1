#include "stdafx.h"
#include "CMainWnd.h"
#include "ListMenu.h"
#include "NetWorker.h"
#include "CUsrInfoWnd.h"
#include "CFriendInfoWnd.h"
#include "jsoncpp\include\json.h"

extern CNetWorker* g_pNetWorker;
extern ST_ACCOUNT_INFO g_accountInfo;
HWND g_hWndMain = nullptr;
vector<ST_ACCOUNT_INFO> g_vecFriendList;

// UI Msg
void CMainWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose) {
			OnBtnCloseWindow();
		}
		else if (msg.pSender == m_pBtnMinimize) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if(msg.pSender == m_pBtnSetting){
			MessageBox(nullptr, L"Not ready", L"Info", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnSendMsg) {
			OnBtnSendMsg();
		}
		else if (msg.pSender == m_pBtnHead) {
			OnBtnUpdateAccount();
		}
		else if (msg.pSender == m_pBtnAddFriend) {
			OnBtnAddFriend();
		}
		else if (msg.pSender == m_pBtnFriendDlgCfg) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnFont) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnFace) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnScissors) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnShake) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnMicrophone) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnPhoto) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnFile) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
		else if (msg.pSender == m_pBtnHistoryMsg) {
			MessageBox(nullptr, L"Not ready", L"Information", MB_ICONINFORMATION);
		}
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMACTIVATE) {
		//OnFriendSelected();
	}
	else if (msg.sType == DUI_MSGTYPE_MENU) {
		if (msg.pSender == m_pListFriend) {
			OnMenu(msg);
		}
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMSELECT) {
		if (msg.pSender == m_pListFriend) {
			OnFriendSelected();
		}
	}
	else {
		// nothing
	}
}

#pragma region Sys message handler
#if 0
// Sys msg
LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_SEND_MESSAGE_REQUEST:
		lRes = OnSendMessageRequest(uMsg, wParam, lParam, bHandled); break;
	case WM_SEND_MESSAGE_RESPONSE:
		lRes = OnSendMessageResponse(wParam); break;
	case WM_ADD_FRIEND_RESPONSE:
		lRes = OnAddFriendResponse(wParam); break;
	case WM_UPDATE_FRIEND_LIST_RESPONSE:
		lRes = OnUpdateFriendListResponse(uMsg, wParam, lParam, bHandled); break;
	case WM_UPDATE_FRIEND_INFO_RESPONSE:
		lRes = OnUpdateFriendInfoResponse(wParam); break;
	case WM_ADD_FRIEND_PUSH:
		lRes = OnAddFriendPush(wParam); break;
	case WM_ONLINE_INFO_PUSH:
		lRes = OnOnlineInfoPush(wParam); break;
	case WM_SHOW_FRIEND_INFO:
		lRes = OnShowFriendInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_DELETE_FRIEND:
		lRes = OnDeleteFriend(uMsg, wParam, lParam, bHandled); break;
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

LRESULT CMainWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	g_hWndMain = m_hWnd;

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(L"xml\\MainWnd.xml", (UINT)0, (UINT)0, &m_PaintManager);
	if (!pRoot) {
		return 0;
	}
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);

	m_pBtnMinimize = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnMin"));
	m_pBtnClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnClose"));
	m_pBtnSetting = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnSetting"));
	m_pBtnSendMsg = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnSendMsg"));
	m_pEditMsg = static_cast<CRichEditUI*>(m_PaintManager.FindControl(L"richEdit"));
	m_pListDialog = static_cast<CListUI*>(m_PaintManager.FindControl(L"lstDialog"));
	m_pListFriend = static_cast<CListUI*>(m_PaintManager.FindControl(L"lstFriends"));
	m_pEditSearch = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editSearch"));
	m_pBtnHead = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnHeadImg"));
	m_pBtnAddFriend = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btnSearch"));
	if (!m_pBtnMinimize || !m_pBtnClose || !m_pBtnSetting || !m_pBtnSendMsg || !m_pEditMsg || !m_pListDialog 
		|| !m_pListFriend || !m_pEditSearch || !m_pBtnHead || !m_pBtnAddFriend) {
		return -1;
	}

	::SetTimer(m_hWnd, TIMER_ID_HEARTBEAT, TIMER_ELAPSE_HEARTBEAT, nullptr);
	// Send update friend list request
	if (NET_WORKER_STATE_CONNECTED == g_pNetWorker->GetCurState()) {
		g_pNetWorker->UpdateFriendList();
	}
	// Update head UI
	if (0 == g_accountInfo.sex) {
		m_pBtnHead->SetNormalImage(L"HeadMale.png");
		m_pBtnHead->SetHotImage(L"HeadMaleHot.png");
		m_pBtnHead->SetPushedImage(L"HeadMale.png");
	}
	else if (1 == g_accountInfo.sex) {
		m_pBtnHead->SetNormalImage(L"HeadFemale.png");
		m_pBtnHead->SetHotImage(L"HeadFemaleHot.png");
		m_pBtnHead->SetPushedImage(L"HeadFemale.png");
	}
	else {
		m_pBtnHead->SetNormalImage(L"Anonymous.png");
		m_pBtnHead->SetHotImage(L"AnonymousHot.png");
		m_pBtnHead->SetPushedImage(L"Anonymous.png");
	}

	return 0;
}

LRESULT CMainWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}

LRESULT CMainWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CMainWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CMainWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CMainWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CMainWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
void CMainWnd::InitWindow()
{
	g_hWndMain = m_hWnd;

	m_pBtnMinimize = static_cast<CButtonUI*>(m_pm.FindControl(L"btnMin"));
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pBtnSetting = static_cast<CButtonUI*>(m_pm.FindControl(L"btnSetting"));
	m_pBtnSendMsg = static_cast<CButtonUI*>(m_pm.FindControl(L"btnSendMsg"));
	m_pEditMsg = static_cast<CRichEditUI*>(m_pm.FindControl(L"richEdit"));
	m_pListDialog = static_cast<CListUI*>(m_pm.FindControl(L"lstDialog"));
	m_pListFriend = static_cast<CListUI*>(m_pm.FindControl(L"lstFriends"));
	m_pEditSearch = static_cast<CEditUI*>(m_pm.FindControl(L"editSearch"));
	m_pBtnHead = static_cast<CButtonUI*>(m_pm.FindControl(L"btnHeadImg"));
	m_pBtnAddFriend = static_cast<CButtonUI*>(m_pm.FindControl(L"btnSearch"));
	m_pLabelFriendName = static_cast<CLabelUI*>(m_pm.FindControl(L"labelFriendName"));
	m_pBtnFriendDlgCfg = static_cast<CButtonUI*>(m_pm.FindControl(L"btnFriendDlgCfg"));
	m_pBtnFont = static_cast<CButtonUI*>(m_pm.FindControl(L"btnFont"));
	m_pBtnFace = static_cast<CButtonUI*>(m_pm.FindControl(L"btnFace"));
	m_pBtnScissors = static_cast<CButtonUI*>(m_pm.FindControl(L"btnBtnScissors"));
	m_pBtnShake = static_cast<CButtonUI*>(m_pm.FindControl(L"btnShake"));
	m_pBtnMicrophone = static_cast<CButtonUI*>(m_pm.FindControl(L"btnMicrophone"));
	m_pBtnPhoto = static_cast<CButtonUI*>(m_pm.FindControl(L"btnPhoto"));
	m_pBtnFile = static_cast<CButtonUI*>(m_pm.FindControl(L"btnFile"));
	m_pBtnHistoryMsg = static_cast<CButtonUI*>(m_pm.FindControl(L"btnHistoryMsg"));
	if (!m_pBtnMinimize || !m_pBtnClose || !m_pBtnSetting || !m_pBtnSendMsg || !m_pEditMsg || !m_pListDialog
		|| !m_pListFriend || !m_pEditSearch || !m_pBtnHead || !m_pBtnAddFriend || !m_pLabelFriendName || !m_pBtnFriendDlgCfg
		|| !m_pBtnFont || !m_pBtnFace || !m_pBtnScissors || !m_pBtnShake || !m_pBtnMicrophone || !m_pBtnPhoto || !m_pBtnFile || !m_pBtnHistoryMsg) {
		return;
	}
	
	::SetTimer(m_hWnd, TIMER_ID_HEARTBEAT, TIMER_ELAPSE_HEARTBEAT, nullptr);
	// Send update friend list request
	if (NET_WORKER_STATE_CONNECTED == g_pNetWorker->GetCurState()) {
		g_pNetWorker->UpdateFriendList();
	}
	// Update head image 
	if (0 == g_accountInfo.sex) {
		m_pBtnHead->SetNormalImage(L"HeadMale.png");
		m_pBtnHead->SetHotImage(L"HeadMaleHot.png");
		m_pBtnHead->SetPushedImage(L"HeadMale.png");
	}
	else if (1 == g_accountInfo.sex) {
		m_pBtnHead->SetNormalImage(L"HeadFemale.png");
		m_pBtnHead->SetHotImage(L"HeadFemaleHot.png");
		m_pBtnHead->SetPushedImage(L"HeadFemale.png");
	}
	else {
		m_pBtnHead->SetNormalImage(L"Anonymous.png");
		m_pBtnHead->SetHotImage(L"AnonymousHot.png");
		m_pBtnHead->SetPushedImage(L"Anonymous.png");
	}
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;
	bHandled = TRUE;

	switch (uMsg) {
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:
		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_SEND_MESSAGE_REQUEST:
		lRes = OnSendMessageRequest(uMsg, wParam, lParam, bHandled); break;
	case WM_SEND_MESSAGE_RESPONSE:
		lRes = OnSendMessageResponse(wParam); break;
	case WM_ADD_FRIEND_RESPONSE:
		lRes = OnAddFriendResponse(wParam); break;
	case WM_UPDATE_FRIEND_LIST_RESPONSE:
		lRes = OnUpdateFriendListResponse(uMsg, wParam, lParam, bHandled); break;
	case WM_UPDATE_FRIEND_INFO_RESPONSE:
		lRes = OnUpdateFriendInfoResponse(wParam); break;
	case WM_ADD_FRIEND_PUSH:
		lRes = OnAddFriendPush(wParam); break;
	case WM_ONLINE_INFO_PUSH:
		lRes = OnOnlineInfoPush(wParam); break;
	case WM_SHOW_FRIEND_INFO:
		lRes = OnShowFriendInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_DELETE_FRIEND:
		lRes = OnDeleteFriend(uMsg, wParam, lParam, bHandled); break;
	case WM_TIMER:
		lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	return lRes;
}

LRESULT CMainWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}

LRESULT CMainWnd::OnTimer(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = false;
	switch ((ULONG)wParam)
	{
	case TIMER_ID_HEARTBEAT:
		bHandled = true;
		if (NET_WORKER_STATE_CONNECTED == g_pNetWorker->GetCurState()) {
			g_pNetWorker->SendHeartbeat();
		}
		break;
	default:
		break;
	}
	return 0;
}
#pragma endregion

/*
 * UI message handler
 */
// Stop network connection and close window
LRESULT CMainWnd::OnBtnCloseWindow()
{
	if (NET_WORKER_STATE_UNCONNECTED != g_pNetWorker->GetCurState()) {
		g_pNetWorker->Stop();
	}
	::KillTimer(m_hWnd, TIMER_ID_HEARTBEAT);
	SendMessage(WM_CLOSE);

	return 0;
}

LRESULT CMainWnd::OnBtnSendMsg()
{
	int ret = 0;
	if (!m_pEditMsg) {
		return -1;
	}

	// Send message to server
	CDuiString content = m_pEditMsg->GetText();
	if (content.IsEmpty()) {
		return -2;
	}
	if (NET_WORKER_STATE_CONNECTED != g_pNetWorker->GetCurState()) {
		MessageBox(nullptr, L"连接服务器失败", L"警告", MB_ICONWARNING);
		return -3;
	}
	ret = g_pNetWorker->SendFriendMessage(g_accountInfo.ID, m_strSelectedFriendID, content.GetData());

	// Save msg
	for (auto& friendInfo : g_vecFriendList) {
		if (0 == wcscmp(friendInfo.ID, m_strSelectedFriendID.data())) {
			ST_MESSAGE_INFO msgInfo = { 0 };
			::GetLocalTime(&msgInfo.timeStamp);
			msgInfo.fromServer = false;
			msgInfo.content = content;
			friendInfo.friendMsg.push_back(msgInfo);
			break;
		}
	}
	// Update UI
	WCHAR strTitle[64] = { 0 };
	SYSTEMTIME sysTime;
	::GetLocalTime(&sysTime);
	swprintf_s(strTitle, L"我：(%04d/%02d/%02d %02d:%02d:%02d)", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,
		sysTime.wMinute, sysTime.wSecond);

	CListContainerElementUI* pEle = new CListContainerElementUI();
	pEle->SetInset(RECT{ 10, 0, 0, 0 });
	CVerticalLayoutUI* pLayout = new CVerticalLayoutUI();
	CLabelUI* label1 = new CLabelUI();
	CLabelUI* label2 = new CLabelUI();
	label1->SetText(strTitle);
	label1->SetPadding(RECT{ 10,0,10,0 });
	label1->SetTextStyle(DT_RIGHT);
	label1->SetMinHeight(20);
	label1->SetFont(1);
	label1->SetTextColor(0xFF3B96FA);
	label2->SetText(content);
	label2->SetFont(1);
	label2->SetPadding(RECT{ 10,0,10,0 });
	label2->SetTextStyle(DT_RIGHT);
	pLayout->Add(label1);
	pLayout->Add(label2);
	pEle->Add(pLayout);
	m_pListDialog->Add(pEle);
	pEle->SetMaxHeight(60);	// TODO: Judging the content height

	m_pEditMsg->SetText(L"");

	return ret;
}

// Add friend button handler
LRESULT CMainWnd::OnBtnAddFriend()
{
	CDuiString strFriendID = m_pEditSearch->GetText();
	if (strFriendID.IsEmpty()) {
		return -1;
	}
	int ret = g_pNetWorker->AddFriend(strFriendID.GetData());
	if (0 == ret) {
		MessageBox(nullptr, L"已发送好友申请", L"提示", MB_ICONINFORMATION);
	}
	else {
		MessageBox(nullptr, L"未连接服务器", L"提示", MB_ICONINFORMATION);
	}
	return ret;
}

// Show update account information dialog
LRESULT CMainWnd::OnBtnUpdateAccount()
{
	CUsrInfoWnd usrInfoWnd;
	usrInfoWnd.Create(this->m_hWnd, L"UsrInfoWnd", UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_FRAME);
	usrInfoWnd.CenterWindow();
	usrInfoWnd.ShowModal();
	return 0;
}

// Friend list click handler
LRESULT CMainWnd::OnFriendSelected()
{
	if (!m_pListFriend || !m_pListDialog) {
		return -1;
	}
	int selectedIdx = m_pListFriend->GetCurSel();
	m_strSelectedFriendID = g_vecFriendList[selectedIdx].ID;
	m_pListDialog->RemoveAll();
	// Update msg list
	if (!g_vecFriendList[selectedIdx].friendMsg.empty()) {
		for (auto msgInfo : g_vecFriendList[selectedIdx].friendMsg) {
			WCHAR strTitle[64] = { 0 };
			swprintf_s(strTitle, L"%s：(%04d/%02d/%02d %02d:%02d:%02d)",
				msgInfo.fromServer ? g_vecFriendList[m_pListFriend->GetCurSel()].nickName : L"我",
				msgInfo.timeStamp.wYear, msgInfo.timeStamp.wMonth, msgInfo.timeStamp.wDay,
				msgInfo.timeStamp.wHour, msgInfo.timeStamp.wMinute, msgInfo.timeStamp.wSecond);

			CListContainerElementUI* pEle = new CListContainerElementUI();
			pEle->SetInset(RECT{ 10, 0, 0, 0 });
			CVerticalLayoutUI* pLayout = new CVerticalLayoutUI();
			CLabelUI* label1 = new CLabelUI();
			CLabelUI* label2 = new CLabelUI();
			label1->SetText(strTitle);
			label1->SetPadding(RECT{ 10,0,10,0 });
			label1->SetTextColor(0xFF3B96FA);
			label1->SetFont(1);
			label1->SetTextStyle(msgInfo.fromServer ? DT_LEFT : DT_RIGHT);
			label1->SetMinHeight(20);
			label2->SetText(msgInfo.content.data());
			label2->SetFont(1);
			label2->SetPadding(RECT{ 10,0,10,0 });
			label2->SetTextStyle(msgInfo.fromServer ? DT_LEFT : DT_RIGHT);
			pLayout->Add(label1);
			pLayout->Add(label2);
			pEle->Add(pLayout);
			m_pListDialog->Add(pEle);
			pEle->SetMaxHeight(60);	// TODO: Judging the content height
		}
	}
	
	// Update head icon
	CListContainerElementUI* pEleUI = reinterpret_cast<CListContainerElementUI*>(m_pListFriend->GetItemAt(selectedIdx));
	if (pEleUI) {
		CHorizontalLayoutUI* pLayout = reinterpret_cast<CHorizontalLayoutUI*>(pEleUI->GetItemAt(0));
		if (pLayout) {
			CContainerUI* pContainerHeadImg = reinterpret_cast<CContainerUI*>(pLayout->GetItemAt(0));
			if (pContainerHeadImg) {
				pContainerHeadImg->SetBkImage(CUtility::GetHeadImgName(
					g_vecFriendList[selectedIdx].sex, g_vecFriendList[selectedIdx].online).data());
			}
			CControlUI* pCtlMsgDot = reinterpret_cast<CControlUI*>(pLayout->GetItemAt(1));
			if (pCtlMsgDot) {
				pCtlMsgDot->SetBkImage(L"DotNoMsg.png");
			}
		}
	}

	// Update friend name label
	m_pLabelFriendName->SetText(g_vecFriendList[selectedIdx].nickName);
	m_pEditMsg->SetFocus();

	return 0;
}


/*
* Friend list right-click menu message handler
*/
// Show friend list right-click menu
LRESULT CMainWnd::OnMenu(TNotifyUI& msg)
{
	LRESULT ret = 0;

	if (msg.pSender == m_pListFriend) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		CListMenu *pMenu = new CListMenu(L"xml\\ListMenu.xml");
		pMenu->Init(*this, pt);
		pMenu->ShowWindow();
	}

	return ret;
}

// Show selected friend detail information
LRESULT CMainWnd::OnShowFriendInfo(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = true;
	ST_ACCOUNT_INFO accountInfo = { 0 };
	memcpy_s(&accountInfo, sizeof(accountInfo), &g_vecFriendList[m_pListFriend->GetCurSel()], sizeof(accountInfo));
	if (wstring(accountInfo.ID).empty()) {
		return -1;
	}
	CFriendInfoWnd* pFriendWnd = new CFriendInfoWnd(accountInfo);
	pFriendWnd->Create(m_hWnd, L"FriendInfoWnd", UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_FRAME);
	pFriendWnd->CenterWindow();
	pFriendWnd->ShowModal();

	return 0;
}

// Delete selected friend
LRESULT CMainWnd::OnDeleteFriend(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = true;
	WCHAR warning[128] = { 0 };
	swprintf_s(warning, L"删除好友%s(%s)？", g_vecFriendList[m_pListFriend->GetCurSel()].nickName,
		g_vecFriendList[m_pListFriend->GetCurSel()].ID);
	if (IDYES == MessageBox(nullptr, warning, L"警告", MB_ICONWARNING | MB_YESNOCANCEL)) {
		// TODO:
	}
	return 0;
}


/*
 * network message handler
 */
LRESULT CMainWnd::OnUpdateFriendListResponse(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
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

	CContainerUI* pCon = reinterpret_cast<CContainerUI*>(m_pm.FindControl(L"conTest"));
	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)) {
		if (!root["data"].isNull()) {
			g_vecFriendList.clear();
			m_pListFriend->RemoveAll();
			for (UINT idx = 0; idx < root["data"].size(); idx++) {
				Json::Value data = root["data"][idx];
				ST_ACCOUNT_INFO accountInfo = { 0 };
				WCHAR* wCode = CUtility::GBToUtf16(data["code"].asString().data());
				WCHAR* wEmail = CUtility::GBToUtf16(data["email"].asString().data());
				WCHAR* wNickname = CUtility::GBToUtf16(data["nickname"].asString().data());
				accountInfo.sex = data["sex"].asInt();
				accountInfo.online = data["online"].asInt();
				memcpy_s(accountInfo.ID, sizeof(accountInfo.ID), wCode, wcslen(wCode) * sizeof(WCHAR));
				memcpy_s(accountInfo.email, sizeof(accountInfo.email), wEmail, wcslen(wEmail) * sizeof(WCHAR));
				memcpy_s(accountInfo.nickName, sizeof(accountInfo.nickName), wNickname, wcslen(wNickname) * sizeof(WCHAR));
				delete[] wCode;
				delete[] wEmail;
				delete[] wNickname;
				// Update friends list and UI
				g_vecFriendList.push_back(accountInfo);
				CListContainerElementUI* pEle = new CListContainerElementUI();
				CHorizontalLayoutUI* pLayout = new CHorizontalLayoutUI();
				CContainerUI* pContainerHeadImg = new CContainerUI();
				CControlUI* pCtlMsgDot = new CControlUI();
				CLabelUI* pLabel = new CLabelUI();
				pLabel->SetText(accountInfo.nickName);
				pLabel->SetPadding(RECT{ 10, 0, 0, 0 });
				pLabel->SetFont(1);
				pContainerHeadImg->SetMaxWidth(35);
				pContainerHeadImg->SetMaxHeight(35);
				pContainerHeadImg->SetBkImage(CUtility::GetHeadImgName(accountInfo.sex, accountInfo.online).data());
				pCtlMsgDot->SetBkImage(L"DotNoMsg.png");
				pCtlMsgDot->SetFloat(true);
				pCtlMsgDot->SetFixedXY(SIZE{25, 0});
				pCtlMsgDot->SetFixedHeight(10);
				pCtlMsgDot->SetFixedWidth(10);
				pLayout->Add(pContainerHeadImg);
				pLayout->Add(pCtlMsgDot);
				pLayout->Add(pLabel);
				pEle->Add(pLayout);
				pEle->SetMaxHeight(40);
				pEle->SetInset(RECT{ 10, 0, 0, 0 });
				m_pListFriend->Add(pEle);
			}
			m_pListFriend->SelectItem(0, true);
		}
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

// Server message forwarding handler
LRESULT CMainWnd::OnSendMessageRequest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
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
	string friendCode, msg;
	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)) {
		if (!root["fromUser"].isNull()) {
			friendCode = root["fromUser"].asString();
		}
		if (!root["message"].isNull()) {
			msg = root["message"].asString();
		}
	}
	delete[] reader;

	WCHAR* wCode = CUtility::GBToUtf16(friendCode.data());
	WCHAR* wMsg = CUtility::GBToUtf16(msg.data());
	if (!g_vecFriendList.empty()) {
		// Save msg
		ST_MESSAGE_INFO msgInfo = { 0 };
		::GetLocalTime(&msgInfo.timeStamp);
		msgInfo.fromServer = true;
		msgInfo.content = wMsg;
		for (UINT idx = 0; idx < g_vecFriendList.size(); idx++) {
			if (0 == wcscmp(g_vecFriendList[idx].ID, wCode)) {
				g_vecFriendList[idx].friendMsg.push_back(msgInfo);
				// Update UI
				if (0 == wcscmp(g_vecFriendList[m_pListFriend->GetCurSel()].ID, wCode)) {
					WCHAR strTitle[64] = { 0 };
					swprintf_s(strTitle, L"%s：(%04d/%02d/%02d %02d:%02d:%02d)", g_vecFriendList[m_pListFriend->GetCurSel()].nickName,
						msgInfo.timeStamp.wYear, msgInfo.timeStamp.wMonth, msgInfo.timeStamp.wDay,
						msgInfo.timeStamp.wHour, msgInfo.timeStamp.wMinute, msgInfo.timeStamp.wSecond);

					CListContainerElementUI* pEle = new CListContainerElementUI();
					pEle->SetInset(RECT{ 10, 0, 0, 0 });
					CVerticalLayoutUI* pLayout = new CVerticalLayoutUI();
					CLabelUI* label1 = new CLabelUI();
					CLabelUI* label2 = new CLabelUI();
					label1->SetText(strTitle);
					label1->SetTextColor(0xFF3B96FA);
					label1->SetFont(1);
					label1->SetPadding(RECT{ 10,0,10,0 });
					label1->SetTextStyle(DT_LEFT);
					label1->SetMinHeight(20);
					label2->SetText(wMsg);
					label2->SetFont(1);
					label2->SetPadding(RECT{ 10,0,10,0 });
					label2->SetTextStyle(DT_LEFT);
					pLayout->Add(label1);
					pLayout->Add(label2);
					pEle->Add(pLayout);
					m_pListDialog->Add(pEle);
					pEle->SetMaxHeight(60);	// TODO: Judging the content height
				}
				else {
					// Update head icon
					CListContainerElementUI* pEleUI = reinterpret_cast<CListContainerElementUI*>(m_pListFriend->GetItemAt(idx));
					if (pEleUI) {
						CHorizontalLayoutUI* pLayout = reinterpret_cast<CHorizontalLayoutUI*>(pEleUI->GetItemAt(0));
						if (pLayout) {
							CContainerUI* pContainer = reinterpret_cast<CContainerUI*>(pLayout->GetItemAt(0));
							if (pContainer) {
								pContainer->SetBkImage(CUtility::GetHeadImgName(
									g_vecFriendList[idx].sex, g_vecFriendList[idx].online).data());
							}
							CControlUI* pCtrlMsgIcon = reinterpret_cast<CControlUI*>(pLayout->GetItemAt(1));
							if (pCtrlMsgIcon) {
								pCtrlMsgIcon->SetBkImage(L"DotMsg.png");
							}
						}
					}
				}
				break;
			}
		}

	}
	delete[] wMsg;
	delete[] wCode;

	return 0;
}

LRESULT CMainWnd::OnSendMessageResponse(WPARAM wParam)
{
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
		;	// OK as default
	}
	else {
		MessageBox(nullptr, L"好友离线中", L"错误", MB_ICONERROR);
	}

	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

LRESULT CMainWnd::OnAddFriendResponse(WPARAM wParam)
{
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
	if (bSuccess) {
		MessageBox(nullptr, L"添加好友成功", L"提示", MB_ICONINFORMATION);
		ST_ACCOUNT_INFO accountInfo = { 0 };
		Json::Value data = root["data"];
		if (!data["code"].isNull()) {
			WCHAR* wCode = CUtility::GBToUtf16(data["code"].asString().data());
			WCHAR* wEmail = CUtility::GBToUtf16(data["email"].asString().data());
			WCHAR* wNickname = CUtility::GBToUtf16(data["nickname"].asString().data());
			accountInfo.sex = data["sex"].asInt();
			memcpy_s(accountInfo.ID, sizeof(accountInfo.ID), wCode, wcslen(wCode));
			memcpy_s(accountInfo.email, sizeof(accountInfo.email), wCode, wcslen(wEmail));
			memcpy_s(accountInfo.nickName, sizeof(accountInfo.nickName), wCode, wcslen(wNickname));
			delete[] wCode;
			delete[] wEmail;
			delete[] wNickname;
			g_vecFriendList.push_back(accountInfo);
			// Update UI
			CListContainerElementUI* pEle = new CListContainerElementUI();
			CHorizontalLayoutUI* pLayout = new CHorizontalLayoutUI();
			CContainerUI* pContainerHeadImg = new CContainerUI();
			CControlUI* pCtlMsgDot = new CControlUI();
			CLabelUI* pLabel = new CLabelUI();
			pLabel->SetText(accountInfo.nickName);
			pLabel->SetPadding(RECT{ 10, 0, 0, 0 });
			pContainerHeadImg->SetMinWidth(30);
			pContainerHeadImg->SetMinHeight(30);
			pContainerHeadImg->SetBkImage(CUtility::GetHeadImgName(accountInfo.sex, accountInfo.online).data());
			pCtlMsgDot->SetBkImage(L"DotNoMsg.png");
			pCtlMsgDot->SetFloat(true);
			pCtlMsgDot->SetFixedXY(SIZE{ 25, 0 });
			pCtlMsgDot->SetFixedHeight(10);
			pCtlMsgDot->SetFixedWidth(10);
			pLayout->Add(pContainerHeadImg);
			pLayout->Add(pLabel);
			pEle->Add(pLayout);
			pEle->SetMaxHeight(40);
			pEle->SetInset(RECT{10, 0, 0, 0});
			m_pListFriend->Add(pEle);
		}
	}
	else {
		MessageBox(nullptr, L"添加好友失败", L"错误", MB_ICONERROR);
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

// Update friend info response handler
LRESULT CMainWnd::OnUpdateFriendInfoResponse(WPARAM wParam)
{
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
	if (bSuccess) {
		ST_ACCOUNT_INFO accountInfo = { 0 };
		Json::Value data = root["data"];
		if (!data["code"].isNull()) {
			WCHAR* wCode = CUtility::GBToUtf16(data["code"].asString().data());
			WCHAR* wEmail = CUtility::GBToUtf16(data["email"].asString().data());
			WCHAR* wNickname = CUtility::GBToUtf16(data["nickname"].asString().data());
			accountInfo.sex = data["sex"].asInt();
			accountInfo.online = data["online"].asInt();
			memcpy_s(accountInfo.ID, sizeof(accountInfo.ID), wCode, wcslen(wCode));
			memcpy_s(accountInfo.email, sizeof(accountInfo.email), wCode, wcslen(wEmail));
			memcpy_s(accountInfo.nickName, sizeof(accountInfo.nickName), wCode, wcslen(wNickname));
			delete[] wCode;
			delete[] wEmail;
			delete[] wNickname;
			// Update friend info
			if (!g_vecFriendList.empty()) {
				for (UINT idx = 0; idx < g_vecFriendList.size(); idx++) {
					if (0 == wcscmp(g_vecFriendList[idx].ID, accountInfo.ID)) {
						g_vecFriendList[idx] = accountInfo;
					}
				}
			}
		}
	}
	else {
		;
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

// Add friend pushing handler
LRESULT CMainWnd::OnAddFriendPush(WPARAM wParam)
{
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

	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)) {
		if (!root["code"].isNull()) {
			MessageBox(nullptr, L"已被添加为好友", L"提示", MB_ICONINFORMATION);
			ST_ACCOUNT_INFO accountInfo = { 0 };
			WCHAR* wCode = CUtility::GBToUtf16(root["code"].asString().data());
			WCHAR* wEmail = CUtility::GBToUtf16(root["email"].asString().data());
			WCHAR* wNickname = CUtility::GBToUtf16(root["nickname"].asString().data());
			accountInfo.sex = root["sex"].asInt();
			memcpy_s(accountInfo.ID, sizeof(accountInfo.ID), wCode, wcslen(wCode));
			memcpy_s(accountInfo.email, sizeof(accountInfo.email), wCode, wcslen(wEmail));
			memcpy_s(accountInfo.nickName, sizeof(accountInfo.nickName), wCode, wcslen(wNickname));
			delete[] wCode;
			delete[] wEmail;
			delete[] wNickname;
			g_vecFriendList.push_back(accountInfo);
			// Update UI
			CListContainerElementUI* pEle = new CListContainerElementUI();
			CHorizontalLayoutUI* pLayout = new CHorizontalLayoutUI();
			CContainerUI* pContainerHeadImg = new CContainerUI();
			CControlUI* pCtlMsgDot = new CControlUI();
			CLabelUI* pLabel = new CLabelUI();
			pLabel->SetText(accountInfo.nickName);
			pLabel->SetPadding(RECT{ 10, 0, 0, 0 });
			pContainerHeadImg->SetMinWidth(30);
			pContainerHeadImg->SetMinHeight(30);
			pContainerHeadImg->SetBkImage(CUtility::GetHeadImgName(accountInfo.sex, accountInfo.online).data());
			pCtlMsgDot->SetBkImage(L"DotNoMsg.png");
			pCtlMsgDot->SetFloat(true);
			pCtlMsgDot->SetFixedXY(SIZE{ 25, 0 });
			pCtlMsgDot->SetFixedHeight(10);
			pCtlMsgDot->SetFixedWidth(10);
			pLayout->Add(pContainerHeadImg);
			pLayout->Add(pCtlMsgDot);
			pLayout->Add(pLabel);
			pEle->Add(pLayout);
			pEle->SetMaxHeight(40);
			pEle->SetInset(RECT{ 10, 0, 0, 0 });
			m_pListFriend->Add(pEle);
		}
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}

// Friend online information pushing handler
LRESULT CMainWnd::OnOnlineInfoPush(WPARAM wParam)
{
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

	if (reader->parse(pAnsiJsonString, pAnsiJsonString + strlen(pAnsiJsonString), &root, &errors)) {
		if (!root["code"].isNull()) {
			WCHAR* wCode = CUtility::GBToUtf16(root["code"].asString().data());
			int online = root["online"].asInt();

			wcout << L"online info:" << wCode << L" " << online << endl;
			// Update friend online info
			if (!g_vecFriendList.empty()) {
				for (UINT idx = 0; idx < g_vecFriendList.size(); idx++) {
					if (0 == wcscmp(g_vecFriendList[idx].ID, wCode)) {
						g_vecFriendList[idx].online = online;
						cout << " vecFriend found" << endl;
					}
				}
			}
			// Update UI
			for (UINT idx2 = 0; idx2 < (UINT)m_pListFriend->GetCount(); idx2++) {
				CListContainerElementUI* pEleUI = reinterpret_cast<CListContainerElementUI*>(m_pListFriend->GetItemAt(idx2));
				if (pEleUI) {
					CHorizontalLayoutUI* pLayout = reinterpret_cast<CHorizontalLayoutUI*>(pEleUI->GetItemAt(0));
					if (pLayout) {
						CContainerUI* pContainer = reinterpret_cast<CContainerUI*>(pLayout->GetItemAt(0));
						if (pContainer) {
							pContainer->SetBkImage(CUtility::GetHeadImgName(
								g_vecFriendList[idx2].sex, g_vecFriendList[idx2].online).data());
						}
					}
				}
			}
			delete[] wCode;
		}
	}
	else {
		;
	}

	delete[] reader;
	delete[] pAnsiJsonString;
	delete[] pWJsonString;
	pJsonString = reinterpret_cast<char*>(pStDataHead);
	delete[] pJsonString;

	return ret;
}
