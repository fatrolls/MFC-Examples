// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "ThemedLayerWnd.h"
#include "BitmapEdit.h"
#include "CustomButton.h"
#include "CustomFont.h"

class CMainDlg :	public CThemedLayerWnd<CMainDlg>,
					public CUpdateUI<CMainDlg>,
					public CMessageFilter,
					public CIdleHandler
{
private:
	CBitmapEdit		m_UserName;
	CBitmapEdit		m_Password;
	CCustomButton	m_btnGo;
	CCustomFont		m_Font;

	void DoPaint(Graphics& g)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		Rect rc(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());

		SolidBrush br(Color::Orange);
		g.FillRectangle(&br, rc);
	}
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateChildWindows();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		//MESSAGE_HANDLER(WM_PAINT, OnPaint)
		//MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_BTN_GO, OnGo)
		CHAIN_MSG_MAP(CThemedLayerWnd<CMainDlg>)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);

		m_Font.SetFont(_T("Î¢ÈíÑÅºÚ"), -20, FW_NORMAL);

		m_UserName.Create(m_hWnd, IDC_USER_NAME);
		m_UserName.LoadBackGroundImage(IDB_USER_NAME, IDB_USER_NAME_HOT);
		CRect rcClient;
		m_UserName.GetClientRect(rcClient);
		rcClient.DeflateRect(35, 3, 3, 3);
		m_UserName.DeflateEditRect(rcClient);
		m_UserName.SetFont(m_Font.GetCurFont()->m_hFont);
		m_UserName.SetWindowText(_T("Ming"));
		
		m_Password.Create(m_hWnd, IDC_PASSWORD);
		m_Password.LoadBackGroundImage(IDB_PASSWORD, IDB_PASSWORD_HOT);
		m_Password.DeflateEditRect(rcClient);
		m_Password.SetPasswordStyle();
		m_Password.SetFont(m_Font.GetCurFont()->m_hFont);
		m_Password.SetFocus();
		m_Password.SetWindowText(_T("12345"));

		CRect rc(0, 0, 138, 40);
		m_btnGo.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, 0, IDC_BTN_GO);
		m_btnGo.SetThemeParent(m_hWnd);
		m_btnGo.LoadBitmap(IDB_BTN_GO, 3);
		m_btnGo.SetImages(0, 2, 1, 2);

		return TRUE;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (m_UserName.m_hWnd)
		{
			CRect rcClient;
			GetClientRect(&rcClient);

			CRect rcUserName;
			m_UserName.GetClientRect(&rcUserName);
			rcUserName.MoveToXY(25, 75);
			m_UserName.MoveWindow(rcUserName);

			CRect rcPwd;
			m_Password.GetClientRect(&rcPwd);
			rcPwd.MoveToX(rcUserName.left);
			rcPwd.MoveToY(rcUserName.bottom + 20);
			m_Password.MoveWindow(rcPwd);

			CRect rcBtnGo;
			m_btnGo.GetClientRect(&rcBtnGo);
			rcBtnGo.MoveToX(rcPwd.left);
			rcBtnGo.MoveToY(rcPwd.bottom + 20);
			m_btnGo.MoveWindow(rcBtnGo);
		}

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		return 0;
	}


	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnGo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ShowWindow(SW_MINIMIZE);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
};
