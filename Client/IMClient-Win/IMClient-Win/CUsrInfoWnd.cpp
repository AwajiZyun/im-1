#include "stdafx.h"
#include "CUsrInfoWnd.h"
#include "NetWorker.h"
#include "jsoncpp\include\json.h"

extern CNetWorker* g_pNetWorker;
extern ST_ACCOUNT_INFO g_accountInfo;
HWND g_hWndAccountUpdate = nullptr;

// UI Msg
void CUsrInfoWnd::Notify(TNotifyUI& msg)
{
	// button click
	if (msg.sType == DUI_MSGTYPE_CLICK) {
		if (msg.pSender == m_pBtnClose) {
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

	m_pBtnHeadImg = static_cast<CButtonUI*>(m_pm.FindControl(L"btnUsrImg"));
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(L"btnClose"));
	m_pBtnUpdate = static_cast<CButtonUI*>(m_pm.FindControl(L"btnUpdate"));
	m_pEditNickName = static_cast<CEditUI*>(m_pm.FindControl(L"editNickname"));
	m_pEditEmail = static_cast<CEditUI*>(m_pm.FindControl(L"editEmail"));
	m_pComboSex = static_cast<CComboUI*>(m_pm.FindControl(L"comboSex"));
	m_pEditOldPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPwdOld"));
	m_pEditNewPwd = static_cast<CEditUI*>(m_pm.FindControl(L"editPwd"));
	m_pEditNewPwdConfirm = static_cast<CEditUI*>(m_pm.FindControl(L"editPwdConfirm"));

	if (m_pBtnHeadImg && m_pBtnClose && m_pBtnUpdate && m_pEditNickName && m_pComboSex &&
		m_pEditOldPwd && m_pEditNewPwd && m_pEditNewPwdConfirm && m_pEditEmail) {
		m_pBtnHeadImg->SetBkImage(0 == g_accountInfo.sex ? L"HeadMale.png" :
			(1 == g_accountInfo.sex ? L"HeadFemale.png" : L"Anonymous.png"));
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
	if (strNewPwdConfirm.IsEmpty() || strNewPwd.IsEmpty() || strOldPwd.IsEmpty()) {
		MessageBox(nullptr, L"密码不能为空", L"提示", MB_ICONINFORMATION);
		return -2;
	}
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
	// save new account information
	memcpy_s(m_stAccountInfo.nickName, sizeof(m_stAccountInfo.nickName), strNickName.GetData(), strNickName.GetLength() * sizeof(WCHAR));
	memcpy_s(m_stAccountInfo.pwd, sizeof(m_stAccountInfo.pwd), strNewPwd.GetData(), strNewPwd.GetLength() * sizeof(WCHAR));
	m_stAccountInfo.sex = nSex;

	return ret;
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
		memcpy_s(g_accountInfo.nickName, sizeof(g_accountInfo.nickName), m_stAccountInfo.nickName, sizeof(m_stAccountInfo.nickName));
		memcpy_s(g_accountInfo.pwd, sizeof(g_accountInfo.pwd), m_stAccountInfo.pwd, sizeof(m_stAccountInfo.pwd));
		g_accountInfo.sex = m_stAccountInfo.sex;
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
