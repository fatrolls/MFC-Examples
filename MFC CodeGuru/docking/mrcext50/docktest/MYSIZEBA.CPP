// mysizeba.cpp : implementation file
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:36  $

#include "stdafx.h"
#include "docktest.h"
#include "mysizeba.h"

#define ID_PopupMessage			2000

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxBar
BEGIN_MESSAGE_MAP(CMyBitmapButton, CMRCBitmapButton)
	//{{AFX_MSG_MAP(CMyBitmapButton)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMyBitmapButton, CMRCBitmapButton);

BOOL CMyBitmapButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	//return CControlBar::OnEraseBkgnd(pDC);
	//return CMRCSizeControlBar::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxBar
//
// This is a sizeable contorl bar that has a list box and a button on it.
// It is designed to be created dynamically ie you can have more than one 
// of them.

IMPLEMENT_DYNAMIC(CMyListBoxBar, CMRCSizeControlBar);

CMyListBoxBar::CMyListBoxBar() 
		: CMRCSizeControlBar( SZBARF_STDMOUSECLICKS | SZBARF_ALLOW_MDI_FLOAT)
{
}

CMyListBoxBar::~CMyListBoxBar()
{
}



BEGIN_MESSAGE_MAP(CMyListBoxBar, CMRCSizeControlBar)
	//{{AFX_MSG_MAP(CMyListBoxBar)
	ON_WM_CREATE()
	ON_COMMAND(ID_PopupMessage, PopupMessage)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyListBoxBar message handlers


//-------------------------------------------------------------------
void CMyListBoxBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	CRect rect(0, 0, cx, cy);		// rectangle for client area
	
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	
	// shrink rectangle if we're docked
	if (IsProbablyFloating())
		rect.InflateRect(-2, -2);		// shrink for border when floating
	else
		rect.InflateRect(-4, -4);

	// position the button at the top right of the window
	CRect ButtonRect;
	m_Button.GetWindowRect(&ButtonRect);
	rect.right -=  ButtonRect.Width();
	m_Button.SetWindowPos(NULL, rect.right, rect.top, 0, 0,
							SWP_NOZORDER | SWP_NOSIZE);

	// fill the rest of the window with the list box..
	rect.right -= 4;		// leave a bit of space.
	m_ListBox.MoveWindow(&rect);

}


//-------------------------------------------------------------------
int CMyListBoxBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (CMRCSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	
	// Register a class for the list box without CS_VREDRAW, CS_HREDRAW
	WNDCLASS wc;
	VERIFY(GetClassInfo(AfxGetInstanceHandle(), _T("LISTBOX"), &wc)); 	
	wc.style &= ~(CS_VREDRAW | CS_HREDRAW);
	wc.lpszClassName = "_MF_LISTBOX";
	VERIFY(AfxRegisterClass(&wc));
	
	// create a list box to fill the client area with. Use CreateEx to add the
	// WS_EX_CLIENTEDGE style. 
	if (!m_ListBox.CreateEx(WS_EX_CLIENTEDGE,
                 			_T("_MF_LISTBOX"),
                 			NULL,
     						WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL
	 								| LBS_HASSTRINGS | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT, 
	             			rect.left,
                 			rect.top,
      						rect.Width(),
							rect.Height(),
                 			GetSafeHwnd(),
                 			0,
                 			NULL))
	{
		TRACE("Failed to create list box\n");
		return -1;
	}
	
	m_ListBox.SetHorizontalExtent(200);
	
	// add some strings to the list box - makes it a bit more interesting
	for (int i = 0; i < 10; i++)
	{
		char msg[100];
		sprintf(msg, "Line %d", i);
		m_ListBox.AddString(msg);
	}

	CRect ButtonRect(0, 0, 32, 32);		// dimensions of the button
	
	if (!m_Button.Create(BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 
						ButtonRect, this, ID_PopupMessage))
	{
		TRACE("Failed to create push button\n");
		return -1;
	}	
	m_Button.LoadBitmap(IDB_BITMAP1);
	return 0;					
}


void CMyListBoxBar::PopupMessage()
// command handler for the bitmap button. The point of this is to illustrate that
// unlike c
{
	int nSel = m_ListBox.GetCurSel();
	CString strMsg;
	if (nSel == -1)
		strMsg == "Nothing in the list box is selected";
	else
		strMsg.Format("Listbox item %d was selected", nSel);
	AfxMessageBox(strMsg);
}

void CMyListBoxBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// disable docking.
	CMRCSizeControlBar::OnRButtonUp(nFlags, point);

	/*if (m_bAllowDocking)
	{
		EnableDocking(NULL);	// disable docking.
		CMRCMDIFrameWndSizeDock * pMain = (CMRCMDIFrameWndSizeDock *) AfxGetMainWnd();
		pMain->FloatControlBar(this, CPoint(0,0));
		m_bAllowDocking = FALSE;
	}
	else
	{
		EnableDocking(CBRS_ALIGN_ANY);
		m_bAllowDocking = TRUE;
	} */
	
}


BOOL CMyListBoxBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CMRCSizeControlBar::PreCreateWindow(cs);
}


BOOL CMyListBoxBar::Create(CWnd * pParentWnd)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return CMRCSizeControlBar::Create(strWndClass,
									   "size bar",
									   WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPCHILDREN,
									   CFrameWnd::rectDefault,
									   pParentWnd, ID_LISTBOXBAR);
}



