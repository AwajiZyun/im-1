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
	//virtual UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	//virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	

	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	////LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnBtnUpdateAccount();
	LRESULT OnUpdateAccountResponse(WPARAM wParam);
public:
	CButtonUI* m_pBtnUpdate;
	CButtonUI* m_pBtnClose;
	CButtonUI* m_pBtnClose2;
	
	CEditUI* m_pEditNickName;
	CComboUI* m_pComboSex;
	CEditUI* m_pEditEmail;
	CEditUI* m_pEditOldPwd;
	CEditUI* m_pEditNewPwd;
	CEditUI* m_pEditNewPwdConfirm;
};

