#pragma once
class CUsrInfoWnd : public WindowImplBase
{
public:
	CUsrInfoWnd() {};

	virtual LPCTSTR GetWindowClassName() const { return L"UsrInfoWnd"; }
	virtual CDuiString GetSkinFile() { return _T("xml\\UsrInfo.xml"); }
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void OnFinalMessage(HWND hWnd);
	LRESULT CUsrInfoWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnBtnUpdateAccount();
	LRESULT OnUpdateAccountResponse(WPARAM wParam);
public:
	CButtonUI* m_pBtnHeadImg;
	CButtonUI* m_pBtnUpdate;
	CButtonUI* m_pBtnClose;
	
	CEditUI* m_pEditNickName;
	CComboUI* m_pComboSex;
	CEditUI* m_pEditEmail;
	CEditUI* m_pEditOldPwd;
	CEditUI* m_pEditNewPwd;
	CEditUI* m_pEditNewPwdConfirm;

private:
	ST_ACCOUNT_INFO m_stAccountInfo;
};

