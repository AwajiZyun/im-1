#pragma once
class CRegistWnd : public WindowImplBase
{
public:
	explicit CRegistWnd() {};

	virtual LPCTSTR GetWindowClassName() const { return L"RegistWnd"; }
	virtual CDuiString GetSkinFile() { return _T("xml\\regist.xml"); }
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//virtual UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	//virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	int InitControls();
	LRESULT OnBtnRegist();
	LRESULT OnRegistResponse(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	CButtonUI* m_pBtnClose;
	CButtonUI* m_pBtnRegist;

	CEditUI* m_pEditMail;
	CEditUI* m_pEditNickname;
	CEditUI* m_pEditPwd;
	CEditUI* m_pEditPwdConfirm;
	CComboUI* m_pCommboSex;
};

