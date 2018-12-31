#include "stdafx.h"
#include "CFriendInfoWnd.h"


CFriendInfoWnd::CFriendInfoWnd(ST_ACCOUNT_INFO accountInfo)
	: m_stAccountInfo(accountInfo)
{
}

void CFriendInfoWnd::InitWindow()
{
	m_pBtnClose = reinterpret_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pCtlHeadImg = reinterpret_cast<CControlUI*>(m_pm.FindControl(L"ctlHeadImg"));
	m_pEditID = reinterpret_cast<CEditUI*>(m_pm.FindControl(L"editID"));
	m_pEditNickName = reinterpret_cast<CEditUI*>(m_pm.FindControl(L"editNickname"));
	m_pEditSex = reinterpret_cast<CEditUI*>(m_pm.FindControl(L"editSex"));
	m_pEditEmail = reinterpret_cast<CEditUI*>(m_pm.FindControl(L"editEmail"));
	if (!m_pBtnClose || !m_pCtlHeadImg || !m_pEditEmail || !m_pEditID || !m_pEditSex || !m_pEditNickName) {
		return;
	}
	m_pEditNickName->SetText(m_stAccountInfo.nickName);
	m_pEditID->SetText(m_stAccountInfo.ID);
	m_pEditSex->SetText(0 == m_stAccountInfo.sex ? L"ÄÐ" :
		1 == m_stAccountInfo.sex ? L"Å®" : L"ÆäËû");
	m_pEditEmail->SetText(m_stAccountInfo.email);
}

// UI Msg
void CFriendInfoWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose) {
			Close();
		}
	}
}

void CFriendInfoWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}