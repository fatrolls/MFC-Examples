#include "StdAfx.h"
#include "DragCaption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CDragCaption::g_colorUnvisited = RGB(0,0,255);		 // blue
COLORREF CDragCaption::g_colorVisited   = RGB(128,0,128);		 // purple


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
	m_color = g_colorUnvisited;				// not visited yet
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
			lf.lfUnderline = TRUE;
			m_font.CreateFontIndirect(&lf);
		}

		// use underline font and visited/unvisited colors
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_color);
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

	StartTracking();
	CWnd::OnLButtonDown(nFlags, point);
	
}

void CDragCaption::PostNcDestroy()
{
	if (m_bDeleteOnDestroy)
		delete this;
}
