// mysizeba.cpp : implementation file
//
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "docktest.h"
#include "mysizeba.h"
#include "UTBStrOp.h"

#define ID_PopupMessage			2000

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBoxBar
//
// This is a sizeable contorl bar that has a list box and a button on it.
// It is designed to be created dynamically ie you can have more than one 
// of them.

IMPLEMENT_DYNAMIC(CMyListBoxBar, COXSizeControlBar);

CMyListBoxBar::CMyListBoxBar() 
		: COXSizeControlBar( SZBARF_STDMOUSECLICKS/* | SZBARF_ALLOW_MDI_FLOAT*/)
{
}

CMyListBoxBar::~CMyListBoxBar()
{
}



BEGIN_MESSAGE_MAP(CMyListBoxBar, COXSizeControlBar)
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
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

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
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	
	// Register a class for the list box without CS_VREDRAW, CS_HREDRAW
	WNDCLASS wc;
	VERIFY(GetClassInfo(AfxGetInstanceHandle(), _T("LISTBOX"), &wc)); 	
	wc.style &= ~(CS_VREDRAW | CS_HREDRAW);
	wc.lpszClassName = _T("_MF_LISTBOX");
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
		TRACE0("Failed to create list box\n");
		return -1;
	}
	
	m_ListBox.SetHorizontalExtent(200);
	
	// add some strings to the list box - makes it a bit more interesting
	for (int i = 0; i < 10; i++)
	{
		TCHAR msg[100];
		UTBStr::stprintf(msg, 100, _T("Line %d"), i);
		m_ListBox.AddString(msg);
	}

	CRect ButtonRect(0, 0, 32, 32);		// dimensions of the button
	if (!m_Button.Create(_T("Test"), BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, 
						ButtonRect, this, ID_PopupMessage))
		{
		TRACE0("Failed to create push button\n");
		return -1;
		}

	if (!m_Button.LoadBitmaps(_T("BITMAPBUTU")))
		{
		TRACE0("Failed to load bitmap for button\n");
		return -1;
		}

	return 0;					
}


void CMyListBoxBar::PopupMessage()
// command handler for the bitmap button. The point of this is to illustrate that
// unlike c
{
	int nSel = m_ListBox.GetCurSel();
	CString strMsg;
	if (nSel == -1)
		strMsg = _T("Nothing in the list box is selected");
	else
		strMsg.Format(_T("Listbox item %d was selected"), nSel);
	AfxMessageBox(strMsg);
}

void CMyListBoxBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// disable docking.
	COXSizeControlBar::OnRButtonUp(nFlags, point);

	
}


BOOL CMyListBoxBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	return COXSizeControlBar::PreCreateWindow(cs);
}


BOOL CMyListBoxBar::Create(CWnd * pParentWnd, const CString& sTitle/*=_T("size bar")*/,
						   const UINT nID/*=ID_LISTBOXBAR*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPCHILDREN,
		CFrameWnd::rectDefault, pParentWnd, nID);
}



