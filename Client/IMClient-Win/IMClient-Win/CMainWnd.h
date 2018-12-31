#pragma once
class CMainWnd : public WindowImplBase
{
public:
	CMainWnd() {};
	
	virtual LPCTSTR GetWindowClassName() const { return L"MainWnd"; }
	virtual CDuiString GetSkinFile() { return _T("xml\\MainWnd.xml"); }
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	//virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	LRESULT OnSendMessageRequest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSendMessageResponse(WPARAM wParam);
	LRESULT OnAddFriendResponse(WPARAM wParam);
	LRESULT OnUpdateFriendListResponse(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUpdateFriendInfoResponse(WPARAM wParam);
	LRESULT OnAddFriendPush(WPARAM wParam);  
	LRESULT OnOnlineInfoPush(WPARAM wParam);
	LRESULT OnShowFriendInfo(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDeleteFriend(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMSg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnFriendSelected();
	LRESULT OnBtnCloseWindow();
	LRESULT OnBtnSendMsg();
	LRESULT OnBtnAddFriend();
	LRESULT OnBtnUpdateAccount();
	LRESULT OnMenu(TNotifyUI& msg);
public:
	CButtonUI* m_pBtnClose;
	CButtonUI* m_pBtnMinimize;
	CButtonUI* m_pBtnSetting;
	CButtonUI* m_pBtnSendMsg;
	CButtonUI* m_pBtnHead;
	CButtonUI* m_pBtnAddFriend;

	CEditUI* m_pEditSearch;
	CRichEditUI* m_pEditMsg;
	CListUI* m_pListDialog, *m_pListFriend;
	CLabelUI* m_pLabelFriendName;

	CButtonUI* m_pBtnFriendDlgCfg;
	CButtonUI* m_pBtnFont;
	CButtonUI* m_pBtnFace;
	CButtonUI* m_pBtnScissors;
	CButtonUI* m_pBtnShake;
	CButtonUI* m_pBtnMicrophone;
	CButtonUI* m_pBtnPhoto;
	CButtonUI* m_pBtnFile;
	CButtonUI* m_pBtnHistoryMsg;

	wstring m_strSelectedFriendID;
};

