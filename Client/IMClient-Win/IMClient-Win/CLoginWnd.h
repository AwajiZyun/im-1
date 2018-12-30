#pragma once
class CLoginWnd : public WindowImplBase
{
public:
	explicit CLoginWnd();
	
	virtual LPCTSTR GetWindowClassName() const { return L"LoginWnd"; }
	virtual CDuiString GetSkinFile(){ return _T("xml\\login.xml");}
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual CDuiString GetSkinFolder() { return _T("skin"); }
	//virtual UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	//virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&  bHandled);
	
	LRESULT OnBtnLogin();
	LRESULT OnLoginResponse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL&  bHandled);
	LRESULT OnBtnRegist();

	LRESULT OnBtnSavePwd();
	LRESULT OnBtnAutoLogin();

	int InitControls();

private:
	CControlUI* m_pCtlHeadImg;
	CButtonUI* m_pBtnSetting;
	CButtonUI* m_pBtnMinimize;
	CButtonUI* m_pBtnClose;
	CButtonUI* m_pBtnLogin;

	CButtonUI* m_pBtnRegist;
	CButtonUI* m_pBtnForgetPwd;

	CEditUI* m_pEditUsrCode;
	CEditUI* m_pEditUsrPwd;

	COptionUI* m_pOptionSavePwd;
	COptionUI* m_pOptionAutoLogin;

	bool m_bExitProcess;
};

