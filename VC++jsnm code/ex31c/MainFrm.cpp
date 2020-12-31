// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <afxpriv.h> // for AfxSetWindowText
#include "ex31c.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
		ON_MESSAGE(WM_SENDTEXT, OnSendText)
		//}}AFX_MSG_MAP
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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
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
void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// the ISAPI filter needs to find this window by name
	// just display the app name without the file name
	TRACE("CFrameWnd::OnUpdateFrameTitle\n");
	AfxSetWindowText(m_hWnd, AfxGetApp()->m_pszAppName);
}

LONG CMainFrame::OnSendText(UINT wParam, LONG lParam)
{
	TRACE("CMainFrame::OnSendText\n");
	LPVOID lpvFile = ::MapViewOfFile((HANDLE) lParam, FILE_MAP_READ, 0, 0, 
		0);
	GetActiveView()->SendMessage(EM_SETSEL, (WPARAM) 999999, 1000000);
	GetActiveView()->SendMessage(EM_REPLACESEL, (WPARAM) 0, 
		(LPARAM) lpvFile);
	::UnmapViewOfFile(lpvFile);
	::CloseHandle((HANDLE) lParam);

	return 0;
}
