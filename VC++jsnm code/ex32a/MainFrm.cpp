// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex32a.h"

#include "urlthread.h"
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
	ON_WM_CREATE()
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

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndDialogBar.Create(this, IDD_DIALOGBAR, CBRS_TOP, 0xE810))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}
	m_wndDialogBar.SetDlgItemText(IDC_URL, g_strURL);
	// attach the color bitmaps to the dialog bar buttons
	m_bitmapGreen.LoadBitmap(IDB_GREEN);
	HBITMAP hBitmap = (HBITMAP) m_bitmapGreen.GetSafeHandle();
	((CButton*) m_wndDialogBar.GetDlgItem(IDC_START))->SetBitmap(hBitmap);
	m_bitmapRed.LoadBitmap(IDB_RED);
	hBitmap = (HBITMAP) m_bitmapRed.GetSafeHandle();
	((CButton*) m_wndDialogBar.GetDlgItem(IDC_STOP))->SetBitmap(hBitmap);

	return 0;
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
