// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SystemTrayDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WM_ICON_NOTIFY			WM_USER+10


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_POPUP_OPTION1, OnPopupOption1)
	ON_UPDATE_COMMAND_UI(ID_POPUP_OPTION1, OnUpdatePopupOption1)
	ON_COMMAND(ID_POPUP_OPTION2, OnPopupOption2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_Option1Enabled = TRUE;
}

CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the tray icon
	if (!m_TrayIcon.Create(this, WM_ICON_NOTIFY, _T("This is a Tray Icon"), 
						   NULL, IDR_POPUP_MENU))
		return -1;

	m_TrayIcon.SetStandardIcon(IDI_ASTERISK);
	
	return 0;
}

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	// Delegate all the work back to the default implementation in
	// CSystemTray.
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame/CSystemTray menu message handlers

void CMainFrame::OnPopupOption1() 
{
	MessageBox(_T("You chose Option 1"));	
}

void CMainFrame::OnUpdatePopupOption1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Option1Enabled);
}

void CMainFrame::OnPopupOption2() 
{
	m_Option1Enabled = !m_Option1Enabled;

	CString str;
	str.Format(_T("You chose option 2. Option 1 is now %s"), 
		m_Option1Enabled? _T("Enabled") : _T("Disabled"));

	MessageBox(str);
}
