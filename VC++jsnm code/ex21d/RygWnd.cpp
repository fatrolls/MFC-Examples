// RygWnd.cpp : implementation file
//

#include "stdafx.h"
#include "RygWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK AFX_EXPORT
	RygWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CWnd* pWnd;

	pWnd = CWnd::FromHandlePermanent(hWnd);
	if (pWnd == NULL) {
		// Assume that client created a CRygWnd window
		pWnd = new CRygWnd();
		pWnd->Attach(hWnd);
	}
	ASSERT(pWnd->m_hWnd == hWnd);
	ASSERT(pWnd == CWnd::FromHandlePermanent(hWnd));
	LRESULT lResult = AfxCallWndProc(pWnd, hWnd, message,
	                                 wParam, lParam);
	return lResult;
}

/////////////////////////////////////////////////////////////////////////////
// CRygWnd

// static data members
CRect  CRygWnd::s_rect(-500, 1000, 500, -1000); // outer rectangle
CPoint CRygWnd::s_point(300, 300); // rounded corners
CRect  CRygWnd::s_rColor[] = {CRect(-250, 800, 250, 300),
                              CRect(-250, 250, 250, -250),
                              CRect(-250, -300, 250, -800)};
CBrush CRygWnd::s_bColor[] = {RGB(192, 192, 192),
                              RGB(0xFF, 0x00, 0x00),
                              RGB(0xFF, 0xFF, 0x00),
                              RGB(0x00, 0xFF, 0x00)};

BOOL CRygWnd::RegisterWndClass(HINSTANCE hInstance) // static member
                                                    //  function
{
	WNDCLASS wc;
	wc.lpszClassName = "RYG"; // matches class name in client
	wc.hInstance = hInstance;
	wc.lpfnWndProc = RygWndProc;
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH) ::GetStockObject(LTGRAY_BRUSH);
	wc.style = CS_GLOBALCLASS;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	return (::RegisterClass(&wc) != 0);
}

/////////////////////////////////////////////////////////////////////////////

CRygWnd::CRygWnd()
{
	m_nState = 0;
	TRACE("CRygWnd constructor\n");
}

CRygWnd::~CRygWnd()
{
	TRACE("CRygWnd destructor\n");
}


BEGIN_MESSAGE_MAP(CRygWnd, CWnd)
	//{{AFX_MSG_MAP(CRygWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(RYG_SETSTATE, OnSetState)
	ON_MESSAGE(RYG_GETSTATE, OnGetState)
END_MESSAGE_MAP()

void CRygWnd::SetMapping(CDC* pDC)
{
	CRect clientRect;
	GetClientRect(clientRect);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(1000, 2000);
	pDC->SetViewportExt(clientRect.right, -clientRect.bottom);
	pDC->SetViewportOrg(clientRect.right / 2, clientRect.bottom / 2);
}

void CRygWnd::UpdateColor(CDC* pDC, int n)
{
	if (m_nState == n + 1) {
		pDC->SelectObject(&s_bColor[n+1]);
	}
	else {
		pDC->SelectObject(&s_bColor[0]);
	}
	pDC->Ellipse(s_rColor[n]);
}

/////////////////////////////////////////////////////////////////////////////
// CRygWnd message handlers

void CRygWnd::OnPaint() 
{
	int i;
	CPaintDC dc(this); // device context for painting
	SetMapping(&dc);
	dc.SelectStockObject(DKGRAY_BRUSH);
	dc.RoundRect(s_rect, s_point);
	for (i = 0; i < 3; i++) {
		UpdateColor(&dc, i);
	}

}

void CRygWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Notification code is HIWORD of wParam, 0 in this case
	GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID(),
		(LONG) GetSafeHwnd()); // 0
}

void CRygWnd::PostNcDestroy() 
{
	TRACE("CRygWnd::PostNcDestroy\n");
	delete this; // CWnd::PostNcDestroy does nothing
}

LRESULT CRygWnd::OnSetState(WPARAM wParam, LPARAM lParam)
{
	TRACE("CRygWnd::SetState, wParam = %d\n", wParam);
	m_nState = (int) wParam;
	Invalidate(FALSE);
	return 0L;
}

LRESULT CRygWnd::OnGetState(WPARAM wParam, LPARAM lParam)
{
	TRACE("CRygWnd::GetState\n");
	return m_nState;
}
