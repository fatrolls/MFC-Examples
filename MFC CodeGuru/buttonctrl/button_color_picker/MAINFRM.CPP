// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "btncolor.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
		ID_SEPARATOR,	// Color Button
		ID_SEPARATOR,
		ID_SEPARATOR,	// Bitmap Button
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

#define IDC_BTNCOLOR	1000
#define IDC_BTNBITMAP	1001

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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetButtonInfo(8, IDC_BTNCOLOR, TBBS_SEPARATOR, 48 );
	m_wndToolBar.SetButtonInfo(10, IDC_BTNBITMAP, TBBS_SEPARATOR, 48 );
	
	m_wndToolBar.SetButtonInfo(9, ID_SEPARATOR, TBBS_SEPARATOR, 12 );
	m_wndToolBar.SetButtonInfo(11, ID_SEPARATOR, TBBS_SEPARATOR, 12 );
	CRect rect;
	m_wndToolBar.GetItemRect(8, &rect);

	CString sText = ""; 
	char buffer[5];
	for (int i = 0; i < 72; i++)
		sText += "Color " + CString(itoa(i, buffer, 10)) + ((i < 71)? ";" : "");

	m_colorBtn.Create(rect, CSize(8, 6), CSize(16, 15), &m_wndToolBar, IDC_BTNCOLOR);
//	If you want the text for each color use this line 
//	m_colorBtn.Create(rect, CSize(8, 6), CSize(16, 15), &m_wndToolBar, IDC_BTNCOLOR, sText);

	sText.LoadString(IDS_STRINGCHART);	
	m_wndToolBar.GetItemRect(10, &rect);
	m_bitmapBtn.Create(rect, CSize(4, 4), IDB_CHART, 14, &m_wndToolBar, IDC_BTNBITMAP, sText);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
