#pragma once
class CListMenu : public WindowImplBase
{
protected:
	virtual ~CListMenu() {};
	CDuiString  m_strXMLPath;
public:
	CListMenu();
	explicit CListMenu(LPCTSTR pszXMLPath) : m_strXMLPath(pszXMLPath) {}
	virtual LPCTSTR    GetWindowClassName()const { return _T("CDuiMenu "); }
	virtual CDuiString GetSkinFile() { return m_strXMLPath; }
	virtual void       OnFinalMessage(HWND hWnd) { delete this; }
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void    Notify(TNotifyUI& msg);

	void Init(HWND hWndParent, POINT ptPos);

private:
	CListUI* m_pList;
	HWND m_hwnParent;
};

