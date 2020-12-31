// ResizingPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ResizingPropSheet.h"

#include "OXLayoutManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define OX_OFFSET (7)

/////////////////////////////////////////////////////////////////////////////
// CResizingPropSheet

IMPLEMENT_DYNAMIC(CResizingPropSheet, CPropertySheet)

CResizingPropSheet::CResizingPropSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CResizingPropSheet::~CResizingPropSheet()
{
	if (m_pLayoutManager != NULL)
	{
		delete m_pLayoutManager;
		m_pLayoutManager = NULL;
	}
}


BEGIN_MESSAGE_MAP(CResizingPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CResizingPropSheet)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResizingPropSheet message handlers

int CResizingPropSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Remove standard Restore, Maximize & Minimize items out of system menu.
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		pSysMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	}
	
	// Make the window resizable
	ModifyStyle(NULL, WS_THICKFRAME);

	return 0;
}

BOOL CResizingPropSheet::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();
	
	if ((m_pLayoutManager = new COXLayoutManager(this)) != NULL)
	{
		// Setup constraints on the OK and Cancel buttons. 
		// 
		m_pLayoutManager->SetConstraint(IDCANCEL, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDCANCEL, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDOK, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDCANCEL);
		m_pLayoutManager->SetConstraint(IDOK, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);

		//
		// Setup constraint on the CTabControl: Size it on the Left, Right and Top with the Window,
		// and on the Bottom with the OK button.
		m_pLayoutManager->SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
		m_pLayoutManager->SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
		m_pLayoutManager->SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -OX_OFFSET, IDOK);
		m_pLayoutManager->SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_TOP, OX_LMT_SAME, OX_OFFSET);
		
		// Draw the layout with the new constraints
		// This is necessary when constraints are implemented and the window must be refreshed
		CRect rect;
		GetWindowRect(&rect);
		GetTabControl()->AdjustRect(FALSE,&rect);
		m_pLayoutManager->OnSize(rect.Width(), rect.Height());

		GetTabControl()->GetWindowRect(&m_rectPage);
		GetTabControl()->AdjustRect(FALSE,&m_rectPage);
		ScreenToClient(&m_rectPage);
		GetActivePage()->MoveWindow(&m_rectPage);

		m_pLayoutManager->RedrawLayout();
	}

	return TRUE;
}

void CResizingPropSheet::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_hWnd) && IsWindowVisible())
	{
		// When the parent window (The Property Sheet) is resized we need
		// to resize the size of the CTabCtrl that is contained within the
		// control.  The OK and Cancel buttons are resized by the Layout
		// Manager.
		
		m_pLayoutManager->OnSize(cx, cy);

		GetTabControl()->GetWindowRect(&m_rectPage);
		GetTabControl()->AdjustRect(FALSE, &m_rectPage);
		
		ScreenToClient(&m_rectPage);
		GetActivePage()->MoveWindow(&m_rectPage);
	}
}

BOOL CResizingPropSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	BOOL bResult = CPropertySheet::OnNotify(wParam, lParam, pResult);
	
	if (bResult)
	{
		NMHDR* pnmh = (LPNMHDR) lParam;

		// the sheet resizes the page whenever it is activated
		// so we need to resize it to what we want
		if (pnmh->code == TCN_SELCHANGE)
		{
			// user-defined message needs to be posted because page must
			// be resized after TCN_SELCHANGE has been processed
			GetActivePage()->MoveWindow(&m_rectPage);
		}
	}

    return bResult;
}

BOOL CResizingPropSheet::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_LAYOUTTYPE));
	ASSERT(cs.lpszClass);

	return CPropertySheet::PreCreateWindow(cs);
}
