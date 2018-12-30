#pragma once
#include "NetWorker.h"

class CFriendInfoWnd : public WindowImplBase
{
protected:
	virtual ~CFriendInfoWnd() {};
public:
	CFriendInfoWnd(ST_ACCOUNT_INFO accountInfo);

	virtual LPCTSTR GetWindowClassName() const { return L"FriendInfoWnd"; }
	virtual CDuiString GetSkinFile() { return _T("xml\\FriendInfo.xml"); }
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
public:
	CControlUI* m_pCtlHeadImg;
	CButtonUI* m_pBtnClose;

	CEditUI* m_pEditNickName;
	CEditUI* m_pEditSex;
	CEditUI* m_pEditID;
	CEditUI* m_pEditEmail;

private:
	ST_ACCOUNT_INFO m_stAccountInfo;
};

