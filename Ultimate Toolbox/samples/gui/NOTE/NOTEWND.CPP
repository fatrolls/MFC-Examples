// ShapeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "noteWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteWnd

CNoteWnd::CNoteWnd(CWnd *pParentWnd)
{
	ASSERT(pParentWnd != NULL);

	m_bTrackMove = FALSE;

	// Must use CreateEx for popup windows
	CWnd::CreateEx(0,AfxRegisterWndClass(0),_T(""),WS_POPUP|WS_VISIBLE,
					10,10,CXWIDTH,CYHEIGHT,
					pParentWnd->GetSafeHwnd(),0);

	// Build the sticky note polygon shape
	m_aPoints[0].x = 0;						// Top left	  
	m_aPoints[0].y = 0;
	m_aPoints[1].x = CXWIDTH;				// Top right
	m_aPoints[1].y = 0;
	m_aPoints[2].x = CXWIDTH;				// Lower right (fold)
	m_aPoints[2].y = CYHEIGHT-CYCORNER;
	m_aPoints[3].x = CXWIDTH-CXCORNER;		// Bottom right (fold)
	m_aPoints[3].y = CYHEIGHT;
	m_aPoints[4].x = 0;						// Bottom left
	m_aPoints[4].y = CYHEIGHT;
	m_nPoints = 5;
	
	// Use CShape to set the visible region
	SetPolyShape(m_aPoints,m_nPoints);

	// Create a sticky note font
	m_fontText.CreateFont(16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,FF_SWISS|VARIABLE_PITCH,NULL);

	// Center the window
	CenterWindow();
}

CNoteWnd::~CNoteWnd()
{
	// Destroy the window object
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CNoteWnd, CWnd)
	//{{AFX_MSG_MAP(CNoteWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNoteWnd message handlers

// Handle WM_LBUTTONDOWN Windows message
void CNoteWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	// Save the location in case we are dragging
	m_ptMouse = point;
	ClientToScreen(&point);
	m_ptLast = point;
}

// Handle WM_LBUTTONUP Windows message
void CNoteWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	// If we are dragging the window...
	if (m_bTrackMove)
	{
		// Reposition the window to where we dragged it
		m_bTrackMove = FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
	}
	else PostMessage(WM_CLOSE);  // Clicked but didn't move, close the window
}

// Handle WM_MOUSEMOVE Windows message
void CNoteWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// If we aren't dragging the window then check to see if the left
	// mouse button is down
	if(!m_bTrackMove && (nFlags & MK_LBUTTON))
	{
		// Yes...begin to move the window
		m_bTrackMove = TRUE;
		SetCapture();
		InvertTracker(m_ptLast);
	}

	// If we are moving...
	if (m_bTrackMove)
	{
		// Update the location of the tracking rectangle
		ClientToScreen(&point);
		InvertTracker(m_ptLast);
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else CWnd::OnMouseMove(nFlags,point);
}

// Utility routine to draw a tracking rectangle the size of the window
void CNoteWnd::InvertTracker(CPoint point)
{
	CRect rectFrame;
	GetWindowRect(&rectFrame);
	CDC dc;
	dc.Attach(::GetDC(NULL));

	// Draw reversed frame (this can add or remove the tracker)
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y, rectFrame.Width(),
			2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x+rectFrame.Width(), point.y-m_ptMouse.y,
			2, rectFrame.Height(), PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+rectFrame.Height(),
			rectFrame.Width()+2, 2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+2, 2,
			rectFrame.Height()-2, PATINVERT);
	::ReleaseDC(NULL,dc.Detach());
}

// Handles painting of note window
void CNoteWnd::OnPaint() 
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CBrush brNote(RGB(255,255,128));
	CBrush brCorner(RGB(128,128,0));
	CPen penFrame(PS_SOLID,2,RGB(0,0,0));
	CPen *pOldPen;
	CBrush *pOldBrush;
	CFont *pOldFont;
	COLORREF crOldText;
	int nOldMode;

	// Fill the note's background
	dc.FillRect(&rect,&brNote);

	pOldPen = (CPen *) dc.SelectObject(&penFrame);

	// Draw the left side and other sides of the note
	dc.MoveTo(rect.left,rect.top);
	dc.LineTo(rect.left,rect.bottom);
	dc.Polyline(m_aPoints,m_nPoints);

	// Calculate the location of the turned up corner
	POINT aPoints[3] = 
	{
		{rect.right-CXCORNER,rect.bottom},
		{rect.right-CXCORNER,rect.bottom-CYCORNER},
		{rect.right,rect.bottom-CYCORNER}
	};

	// Draw and shade the turned up corner
	pOldBrush = (CBrush *) dc.SelectObject(&brCorner);
	dc.Polygon(aPoints,3);

	// Paint some text on the note
	pOldFont = (CFont *) dc.SelectObject(&m_fontText);
	crOldText = dc.SetTextColor(RGB(0,0,0));
	nOldMode = dc.SetBkMode(TRANSPARENT);
	CRect rectText(rect.left+5,rect.top+20,rect.right-5,rect.bottom-20);
	dc.DrawText(_T("Hello.\n\nThis is my new sticky note Object.\n\nPress ESC to exit."),
						-1,rectText,DT_WORDBREAK|DT_NOPREFIX);

	// Restore everything
	dc.SelectObject(pOldFont);
	dc.SetBkMode(nOldMode);
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
}

// Handles WM_KEYDOWN Windows message
void CNoteWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Found ESCAPE key, get out
	if(nChar == VK_ESCAPE)
		SendMessage(WM_CLOSE);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
