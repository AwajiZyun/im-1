#include "stdafx.h"
#include "ListMenu.h"

CListMenu::CListMenu()
{

}

LRESULT CListMenu::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Close();
	bHandled = FALSE;
	return 0;
}

void CListMenu::Init(HWND hWndParent, POINT ptPos)
{
	m_hwnParent = hWndParent;
	Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

	m_pList = reinterpret_cast<CListUI*>(m_pm.FindControl(L"listMenu"));
	if (!m_pList) {
		MessageBox(nullptr, L"xml wrong", L"", 0);
	}
}

LRESULT CListMenu::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL    bHandled = TRUE;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
	}

	if (bHandled || m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CListMenu::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_ITEMSELECT) {
		if (0 == m_pList->GetCurSel()) {
			::PostMessage(m_hwnParent, WM_SHOW_FRIEND_INFO, 0, 0);
			Close();
		}
		else if (1 == m_pList->GetCurSel()) {
			::PostMessage(m_hwnParent, WM_DELETE_FRIEND, 0, 0);
			Close();
		}
		else {
			;
		}
	}
}