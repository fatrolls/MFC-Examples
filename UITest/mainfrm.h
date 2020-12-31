// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__831E43DB_079A_49CB_9621_C7FAD9C63074__INCLUDED_)
#define AFX_MAINFRM_H__831E43DB_079A_49CB_9621_C7FAD9C63074__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

using namespace wtlx;

class CMainFrame : 
	public CMDIFrameWindowImpl<CMainFrame>, 
	public CMessageFilter, 
	public CIdleHandler,
	public CUIStates<CStyle, CText, CParts>,
	public CUIUpdate<CMainFrame, CUICommand<CMainFrame>, CUIToolBar<CMainFrame>, CUIWindowContainer<CMainFrame>,
		CUIReBar<CMainFrame>, CUIStatusBar<CMainFrame> >
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CMDIFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		HWND hWnd = MDIGetActive();
		if(hWnd != NULL)
			return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		UIUpdate();
		return FALSE;
	}

	BEGIN_MSG_MAP(CMainFrame)
		CHAIN_MSG_MAP(CUICommand<CMainFrame>)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MDI_CHILD_COMMANDS()
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_WINDOW_CASCADE, OnWindowCascade)
		COMMAND_ID_HANDLER(ID_WINDOW_TILE_HORZ, OnWindowTile)
		COMMAND_ID_HANDLER(ID_WINDOW_ARRANGE, OnWindowArrangeIcons)
		CHAIN_MSG_MAP(CMDIFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		HWND hWndToolBar1 = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE, ATL_IDW_TOOLBAR1);
		HWND hWndToolBar2 = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME1, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE, ATL_IDW_TOOLBAR2);

		CreateSimpleReBar();
		AddSimpleReBarBand(hWndToolBar1);
		AddSimpleReBarBand(hWndToolBar2);
		CreateSimpleStatusBar();

		CreateMDIClient();

		// adding UI windows
		UIAddToolBar(hWndToolBar1);
		UIAddToolBar(hWndToolBar2);
		UIAddReBar(m_hWndToolBar);
		UIAddStatusBar(m_hWndStatusBar);
		UIAddWindowContainer(m_hWnd);

		// Main frame's commands
		UIAddStyle(ID_VIEW_TOOLBAR, CStyle::Enable|CStyle::Visible|CStyle::Checked);
		UIAddStyle(ID_VIEW_STATUS_BAR, CStyle::Enable|CStyle::Visible|CStyle::Checked);

		// Context commands
		static INT parts[] = { 300, -1 };
		UIInitLocalParts(parts);

		UIAddLocalStyle(ID_FILE_SAVE, CStyle::Visible);
		UIAddLocalStyle(ID_FILE_SAVE_AS, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_CUT, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_COPY, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_PASTE, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_CLEAR, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_UNDO, CStyle::Visible);
		UIAddLocalStyle(ID_EDIT_SELECT_ALL, CStyle::Visible);
		UIAddLocalStyle(ATL_IDW_BAND2, CStyle::Enable);

#ifdef _MAP_
		UIAddLocalText(0, _T("Ready"));
#else // _MAP_
		UIAddLocalText(0, (LPCTSTR)ATL_IDS_IDLEMESSAGE);
#endif

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CChildFrame* pChild = new CChildFrame;
		pChild->m_view.SetUI(this, this, this);
		pChild->CreateEx(m_hWndClient);

		// TODO: add code to initialize document

		return 0;
	}

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		bool bVisible = !CWindow(m_hWndToolBar).IsWindowVisible();
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UISetVisible(ID_VIEW_TOOLBAR, bVisible);
		UIUpdate();
		UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		bool bVisible = !CWindow(m_hWndStatusBar).IsWindowVisible();
		UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		UISetVisible(ID_VIEW_STATUS_BAR, bVisible);
		UIUpdate();
		UpdateLayout();
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDICascade();
		return 0;
	}

	LRESULT OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDITile();
		return 0;
	}

	LRESULT OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		MDIIconArrange();
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__831E43DB_079A_49CB_9621_C7FAD9C63074__INCLUDED_)
