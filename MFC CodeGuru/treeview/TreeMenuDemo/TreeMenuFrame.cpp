//************************************************************************
//
// Filename	:	TreeMenuFrame.cpp
// Author	:	Rainer Pfitzner	
// Date		:	08.may.1998
// Purpose	:	A class similar IE 4's left side pane (Favorites, Channels...): 
//				Combines a button, some bevels and a CTreeView derived class
//              called CTreeMenu. Easy usage on Dialog Templates and in Views
// Copyright (c) 1998 raip systems. All rights reserved
//
//************************************************************************


#include "stdafx.h"
#include "TreeMenuFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "sizecbar.h"

#define BTNX		16
#define BTNY		12
#define BORDER		 2
#define IDC_TREEMENUFRAME	1119


class CSizingControlBar;
/////////////////////////////////////////////////////////////////////////////
// CFlatBtn
CFlatBtn::CFlatBtn()
{
	m_clrText		= GetSysColor (COLOR_BTNTEXT);
	m_clrFace		= GetSysColor (COLOR_BTNFACE);
	m_clrHotText	= RGB(0,0,255);
	m_bLBtnDown		= FALSE;
	strText			= _T("x");
}

CFlatBtn::~CFlatBtn()
{

}

BEGIN_MESSAGE_MAP(CFlatBtn, CButton)
	//{{AFX_MSG_MAP(CFlatBtn)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFlatBtn message handlers

void CFlatBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	SetTimer (1,10,NULL);
	CButton::OnMouseMove(nFlags, point);
}

void CFlatBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLBtnDown= TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CFlatBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLBtnDown= FALSE;

 	CButton::OnLButtonUp(nFlags, point);
}

void CFlatBtn::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{	
	ASSERT(lpDIS != NULL);	
	CDC* pDC = GetDC();
	
	m_rect.CopyRect(&lpDIS->rcItem);	

	UINT state = lpDIS->itemState;
    if ( (state & ODS_SELECTED) )
		pDC->Draw3dRect (m_rect,GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
    else
		pDC->Draw3dRect (m_rect,m_clrFace, m_clrFace);

	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( m_clrText );

	if (state & ODS_DISABLED)
	{
		CBrush grayBrush;
		grayBrush.CreateSolidBrush (GetSysColor(COLOR_GRAYTEXT));
		pDC->GrayString (&grayBrush,NULL,(LPARAM)((LPCSTR)strText),-1,m_rect.left, m_rect.top,m_rect.Width(),m_rect.Height());
	}
	else 
		pDC->DrawText(strText, m_rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);



}

void CFlatBtn::OnTimer(UINT nIDEvent)
{
	POINT pt;
	static BOOL pPainted = FALSE;
	GetCursorPos(&pt);
	CRect rect;
	GetWindowRect (rect);

	CDC *pDC = GetDC ();
	
	if (m_bLBtnDown)
	{
		KillTimer (1);

		if (pPainted)
			InvalidateRect (NULL);

		pPainted = FALSE;
		return;
	}
	if (!rect.PtInRect (pt))
	{
		KillTimer (1);
	
		if (pPainted)
			InvalidateRect (NULL);
		pPainted = FALSE;

		return;
	}
	else
	{
		if (pPainted)
			return;
		else
			pPainted = TRUE;
		
		GetClientRect(rect);
		pDC->FillSolidRect(rect, m_clrFace);
		pDC->SetTextColor(m_clrHotText);
		pDC->DrawText(strText, m_rect, DT_LEFT|DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		pDC->Draw3dRect(rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

		ReleaseDC (pDC);
	}	
	CButton::OnTimer(nIDEvent);
}




//////////////////////////////////////
//  CDragCaption

IMPLEMENT_DYNAMIC(CDragCaption, CStatic)

BEGIN_MESSAGE_MAP(CDragCaption, CStatic)
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

///////////////////
//
CDragCaption::CDragCaption(LPCTSTR lpText, BOOL bDeleteOnDestroy)
{
	m_color = RGB(0,0,255);				// hot color
	m_bDeleteOnDestroy = bDeleteOnDestroy;	// delete object with window?
}

UINT CDragCaption::OnNcHitTest(CPoint point)
{
	return HTCLIENT;
}

HBRUSH CDragCaption::CtlColor(CDC* pDC, UINT nCtlColor)
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);
	DWORD dwStyle = GetStyle();
	
	HBRUSH hbr = NULL;
	if ((dwStyle & 0xFF) <= SS_RIGHT) {

		// this is a text control: set up font and colors
		if (!(HFONT)m_font) {
			// first time init: create font
			LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
		//	lf.lfUnderline = TRUE;
		//	lf.lfWeight = FW_BOLD;
		//	lf.lfItalic = TRUE;
			m_font.CreateFontIndirect(&lf);
		}

		// use underline font and visited/unvisited colors
		pDC->SelectObject(&m_font);
	//	pDC->SetTextColor(m_color);
		pDC->SetBkMode(TRANSPARENT);

		// return hollow brush to preserve parent background color
		hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	}
	return hbr;
}

/////////////////
// Handle mouse click: StartTracking
void CDragCaption::OnLButtonDown(UINT nFlags, CPoint point)
{
	// send TMFN_HIDE to parent and handle there
	CWnd* pParent = GetParent();
	ASSERT_VALID(pParent);
	if (pParent != NULL)
		pParent->SendMessage(TMFN_CAPTIONDRAG);
	
}

void CDragCaption::PostNcDestroy()
{
	if (m_bDeleteOnDestroy)
		delete this;
}




/////////////////////////////////////////////////////////////////////////////
// CTreeMenuFrame

IMPLEMENT_DYNCREATE(CTreeMenuFrame, CWnd)

CTreeMenuFrame::CTreeMenuFrame()
{
	RegisterClass();
	bSideBevels = FALSE;
	bFrameBevel = FALSE;
}

CTreeMenuFrame::~CTreeMenuFrame()
{
}


BEGIN_MESSAGE_MAP(CTreeMenuFrame, CWnd)
	//{{AFX_MSG_MAP(CTreeMenuFrame)
	ON_WM_SIZE()
	ON_COMMAND(IDC_BTN_HIDE, OnButtonHide)
	//}}AFX_MSG_MAP
	ON_MESSAGE(TMFN_CAPTIONDRAG, OnCaptionDrag)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeMenuFrame message handlers


void CTreeMenuFrame::RegisterClass()
{
	WNDCLASSEX	wc;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfoEx(hInst, TREEMENUCTRL_CLASSNAME, &wc)))
    {
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS|CS_VREDRAW|CS_HREDRAW|CS_CLASSDC; //CS_GLOBALCLASS|CS_BYTEALIGNCLIENT;
		wc.lpfnWndProc = ::DefWindowProc;				// Message processing code
		wc.cbClsExtra = 0;								// No extra bytes needed
		wc.cbWndExtra = 0;								// No DLGWINDOWEXTRA needed
		wc.hInstance = hInst;							// Instance handle
		wc.hIcon = NULL;								// No icon
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);		// Use Arrow cursor 
		wc.hbrBackground = NULL;						// (HBRUSH) (COLOR_3DFACE+1);
		wc.lpszMenuName = NULL;							// No menus
		wc.lpszClassName = TREEMENUCTRL_CLASSNAME;		// Class name
		wc.hIconSm = NULL;								// No Icon associated to the class
	}

	if (!::RegisterClassEx(&wc))					// If registration failed, subsequent dialogs will fail
	{
	//	ASSERT(FALSE);
	}
}

BOOL CTreeMenuFrame::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwStyle)
{
    ASSERT(pParentWnd->GetSafeHwnd());

    if (!CWnd::Create(TREEMENUCTRL_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID)) 
        return FALSE;

	Initialize();
	return TRUE;
}

BOOL CTreeMenuFrame::SubclassDlgItem(UINT nID, CWnd* parent)
{
	if (!CWnd::SubclassDlgItem(nID, parent)) 
		return FALSE;

	Initialize();

	return TRUE;
}

void CTreeMenuFrame::Initialize()
{
	// creates all the objects in frame -
	// caption, tree, button

	CRect rc;

	if (bSideBevels || !bFrameBevel)
	{
		if (!m_stcBevelLeft.Create("", WS_VISIBLE|SS_ETCHEDHORZ,
									rc, this, IDC_BEVELL ))
		{
			return;
		}

		if (!m_stcBevelRight.Create("", WS_VISIBLE|SS_ETCHEDHORZ,
									rc, this, IDC_BEVELR ))
		{
			return;
		}
	}

	if (!bSideBevels || bFrameBevel)
	{
		if (!m_stcBevel.Create("", WS_VISIBLE|SS_ETCHEDFRAME,
									rc, this, IDC_BEVEL ))
		{
			return;
		}

	}

	if (!m_stcLine.Create("", WS_VISIBLE|SS_ETCHEDHORZ,
								rc, this, IDC_LINE ))
	{
		return;
	}
	
	// create the caption
	if (!m_stcCaption.Create("Tree Menu", WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,
								rc, this, IDC_CAPTION ))
	{
		return;
	}

	// create the button
	if (!m_btn.Create("x", WS_VISIBLE|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
							rc, this, IDC_BTN_HIDE))
	{
		return;
	}

	// a nicer font
	NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_captionFont.CreateFontIndirect(&(ncm.lfMessageFont));

	m_stcCaption.SetFont(&m_captionFont);


	if (!m_tree.Create(WS_VISIBLE|WS_CHILD|TVS_TRACKSELECT|TVS_FULLROWSELECT|TVS_HASBUTTONS|TVS_EDITLABELS/*TVS_NOSCROLL*/,
						   rc, this, IDC_TREEMENUFRAME))
	{
		return;
	}

	// and a tooltip for the hide button
	m_ToolTip.Create(this);	
    m_ToolTip.AddTool(&m_btn, _T("Hide"));
	m_ToolTip.AddTool(&m_stcCaption, _T("Drag caption to dock anywhere"));

	CalcLayout();  // Yes, we want align to parent
}

void CTreeMenuFrame::CalcLayout(BOOL bParent)
{
	CRect rcWnd, rcLine, rcBtn, rcBevel, rcBevelLeft, rcBevelRight;
	
	if ( bParent)
	{
		CWnd* pwnd = GetParent();
		ASSERT(pwnd);
		pwnd->GetClientRect(&rcWnd);
	}
	else
		GetClientRect(&rcWnd);

//	rcWnd.SetRect(rcWnd.left, rcWnd.top+1, rcWnd.right, rcWnd.bottom-2);
	CRect rcCaption;
	
	int iCpt = ::GetSystemMetrics(SM_CYMENU);

	if (bSideBevels && ! bFrameBevel)
	{
		rcBevelLeft.SetRect(rcWnd.left, rcWnd.top, rcWnd.left+2, rcWnd.bottom);
		m_stcBevelLeft.MoveWindow(rcBevelLeft);

		rcBevelRight.SetRect(rcWnd.right-2, rcWnd.top, rcWnd.right, rcWnd.bottom);
		m_stcBevelRight.MoveWindow(rcBevelRight);
	}

	if (!bSideBevels && bFrameBevel)
	{
		rcBevel.SetRect(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom);
		m_stcBevel.MoveWindow(rcBevel);
	}

	rcLine.SetRect(rcWnd.left+1, rcWnd.top+iCpt+2*BORDER, rcWnd.right, rcWnd.top+iCpt+3*BORDER);
	m_stcLine.MoveWindow(rcLine);
	
	rcCaption.SetRect(rcWnd.left+BORDER, rcWnd.top+BORDER, rcWnd.right-BTNX-4*BORDER, rcWnd.top+iCpt+2*BORDER);
	m_stcCaption.MoveWindow(rcCaption);

	rcBtn.SetRect(rcWnd.right-BTNX-4*BORDER, rcWnd.top+2*BORDER, rcWnd.right-2*BORDER, rcCaption.bottom-BORDER);
	m_btn.MoveWindow(rcBtn);

	CRect rcTree;
	rcTree.left = rcWnd.left+BORDER;
	rcTree.top = rcCaption.bottom+BORDER;
	rcTree.right = rcWnd.right-BORDER;
	rcTree.bottom = rcWnd.bottom-2*BORDER;

	m_tree.MoveWindow(rcTree);

}

BOOL CTreeMenuFrame::PreTranslateMessage(MSG* pMsg) 
{
    m_ToolTip.RelayEvent(pMsg);
    return CWnd::PreTranslateMessage(pMsg);
}

void CTreeMenuFrame::OnButtonHide()
{
	Hide();
}

void CTreeMenuFrame::OnCaptionDrag()
{
	// send TMFN_CAPTIONDRAG to parent and handle there
	CWnd* pParent = GetParent();
	ASSERT_VALID(pParent);
	if (pParent != NULL)
		pParent->SendMessage(TMFN_CAPTIONDRAG);
}


void CTreeMenuFrame::OnSize(UINT nType, int cx, int cy) 
{
//    if (::IsWindow(GetSafeHwnd())) 
//        SetFocus();

    CWnd::OnSize(nType, cx, cy);
}

// Hide(FALSE) let show the control again
void CTreeMenuFrame::Hide(BOOL hide /*TRUE*/)
{
	// send TMFN_HIDE to parent and handle there
	CWnd* pParent = GetParent();
	ASSERT_VALID(pParent);
	if (pParent != NULL)
		pParent->SendMessage(TMFN_HIDE);
}








