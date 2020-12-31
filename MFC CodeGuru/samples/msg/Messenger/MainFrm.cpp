// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Messenger.h"

#include "MainFrm.h"
#include "MessengerTree.h"
#include "MessengerList.h"
#include "MessengerEdit.h"

#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CStealthFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CStealthFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_UPDATE_COMMAND_UI(ID_SEND_BUTTON, OnUpdateSendButton)
	ON_COMMAND(ID_SEND_BUTTON, OnSendButton)
	ON_COMMAND(ID_TOOLS_PROPERTIESDIALOG, OnToolsPropertiesdialog)
	ON_COMMAND(ID_TOOLS_PROPERTIESSHEET, OnToolsPropertiesSheet)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAY_ICON_NOTIFY,OnTrayNotification)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStealthFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	// Eliminate Unnecessary Flashing
    DWORD dwStyle = ::GetClassLong (m_hWnd, GCL_STYLE);
    ::SetClassLong (m_hWnd, GCL_STYLE, dwStyle & ~(CS_HREDRAW | CS_VREDRAW));


	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// assign texts to the buttons
	m_wndToolBar.SetSizes(CSize(42,40), CSize(16,15));
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_EDIT_CUT), "Cut");
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_EDIT_COPY), "Copy");
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_EDIT_PASTE), "Paste");

//	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_COMBO_BUTTON), "Enter text");
	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_SEND_BUTTON), "Send");

	m_wndToolBar.SetButtonText(m_wndToolBar.CommandToIndex(ID_APP_ABOUT), "About");


	// create an additional CComboBox-control on the toolbar
	DWORD dwComboStyle = WS_VSCROLL|CBS_AUTOHSCROLL|CBS_DROPDOWN|CBS_HASSTRINGS|WS_TABSTOP;
	m_wndToolBar.CreateCombo(dwComboStyle,&m_wndToolBarCombo,ID_COMBO_BUTTON,150,150);

 	// install/load cool menus
	UINT pToolBarId [] = 
	{
		IDR_MAINFRAME,
		IDR_LIST,
	};


	m_ctlMenuManager.Install(this);
	m_ctlMenuManager.LoadToolbars((const UINT*)pToolBarId,_countof(pToolBarId));
	m_ctlMenuManager.m_bAutoAccel = FALSE;
	m_ctlMenuManager.SetCheckmarkBitmap(IDB_SMILE1, IDB_SMILE);

	// implement tray icon
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ctlTrayIcon.Create(this,WM_TRAY_ICON_NOTIFY,"Messenger",hIcon,IDR_TRAY_MENU);


	// implement custom caption
	m_ctlCaptionManager.Install(this, 0);
	m_ctlCaptionManager.TitleText(&m_strTitle);


	return 0;
}

BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// create a splitter with 2 row, 1 columns
	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitterEdit.CreateStatic(&m_wndSplitter, 2, 1,
		WS_CHILD | WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0,1)))    // <- where triks
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitterEdit.CreateView(0, 0,
		RUNTIME_CLASS(CMessengerList), CSize(200, 250), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitterEdit.CreateView(1, 0,
		RUNTIME_CLASS(CMessengerEdit), CSize(100, 100), pContext))
	{
		TRACE0("Failed to create grid pane\n");
		return FALSE;
	}

	
	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(200, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));
	return TRUE;	
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CStealthFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CStealthFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam,LPARAM lParam)
{
//	TRACE("WPARAM %i,LPARAM %i\n",wParam,lParam);
	switch(LOWORD(lParam))
	{
	case WM_LBUTTONUP:
		ShowWindow(SW_SHOW);
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
		break;
	}

	return m_ctlTrayIcon.OnTrayNotification(wParam,lParam);

}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStealthFrame::OnSysCommand(nID, lParam);
	switch(nID)
	{
	case SC_MINIMIZE:
		ShowWindow(SW_HIDE);
		break;
	}
}

void CMainFrame::OnUpdateSendButton(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CString str = GetMessageText();

	pCmdUI->Enable(!str.IsEmpty());
}

CString CMainFrame::GetMessageText()
{
	CString str;
	m_wndToolBarCombo.GetWindowText(str);

	return str;
}

void CMainFrame::AddMessageText() 
{
	// TODO: Add your command handler code here

	m_wndToolBarCombo.AddString(GetMessageText());
	
}

void CMainFrame::OnSendButton() 
{
	// TODO: Add your command handler code here
	AddMessageText();

	m_wndSplitter.GetPane(0,0)->SendMessage(WM_COMMAND,ID_TOOLS_SENDMESSAGE);
}

void CMainFrame::OnToolsPropertiesdialog() 
{
	// TODO: Add your command handler code here
//	CTPropertiesDlg<CDialog> dlg(IDD_PROPERTIES_DIALOG);
//	CTPropertiesDlg dlg(IDD_PROPERTIES_DIALOG);
	CPropDlg<CDialog> dlg;


	dlg.DoModal();
	
}

void CMainFrame::OnToolsPropertiesSheet() 
{
	// TODO: Add your command handler code here
	CPropertySheet sheet;
	CPropDlg<CPropertyPage> dlg(IDD_PROPERTIES_PAGE);
	CTPropertiesDlg<CPropertyPage> page(IDD_PROPERTIES_PAGE);
	

	sheet.AddPage(&dlg);
	sheet.AddPage(&page);

	sheet.DoModal();
}

