// CVxOptPopup.cpp : implementation file
//


#include "hello.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CVxOptPopup


CVxOptPopup::CVxOptPopup(CPoint p, CVxOptPicker* pParentWnd, UINT nID/* = NULL */)
{

    m_pParent       = pParentWnd;

    Create(p, pParentWnd, nID);
}

CVxOptPopup::~CVxOptPopup()
{
    //m_Font.DeleteObject();
}

BOOL CVxOptPopup::Create(CPoint p, CVxOptPicker* pParentWnd, UINT nID)
                          
{
    ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));

    m_pParent  = pParentWnd;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0, (HBRUSH)GetStockObject(LTGRAY_BRUSH),0);
	
	// Remeber not to put WS_VISIBLE in the dwStyle, because 
	// when we create this window we don't want it to be visible
	// immediately. Only after we click in CVxOptPicker, it should
	// become visible
	if (!CWnd::CreateEx(0, szClassName, _T(""), WS_POPUP, 
                        p.x, p.y,
						(pParentWnd->m_Width + CONTROL_OFFSET)  *pParentWnd->m_Columns + CONTROL_OFFSET,
						(pParentWnd->m_Height + CONTROL_OFFSET) *pParentWnd->m_Rows    + CONTROL_OFFSET, 
                        pParentWnd->GetSafeHwnd(), 0, NULL))    
    return FALSE;

    // Set the window size
    SetWindowSize();

    // Create the tooltips
    //CreateToolTips();

    // Capture all mouse events for the life of this window
    //SetCapture();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CVxOptPopup, CWnd)
    //{{AFX_MSG_MAP(CVxOptPopup)
    ON_WM_NCDESTROY()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVxOptPopup message handlers

// For tooltips
BOOL CVxOptPopup::PreTranslateMessage(MSG* pMsg) 
{
    //m_ToolTip.RelayEvent(pMsg);
    return CWnd::PreTranslateMessage(pMsg);
}


// auto-deletion
void CVxOptPopup::OnNcDestroy() 
{
    CWnd::OnNcDestroy();
    delete this;
}

void CVxOptPopup::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

    CRect rect;
    GetClientRect(rect);
    dc.DrawEdge(rect, EDGE_RAISED, BF_RECT);
}

// End selection on LButtonUp
void CVxOptPopup::OnLButtonUp(UINT nFlags, CPoint point) 
{    
    CWnd::OnLButtonUp(nFlags, point);

    DWORD pos = GetMessagePos();
    point = CPoint(LOWORD(pos), HIWORD(pos));

	//EndSelection(this->GetDlgCtrlID());
	//ReleaseCapture();
	// We don't destroy the window, we just hide it
	m_pParent->m_PopupWndVisible	= 0 ;
	ShowWindow(SW_HIDE);

}

/////////////////////////////////////////////////////////////////////////////
// CVxOptPopup implementation

// Works out an appropriate size and position of this window
void CVxOptPopup::SetWindowSize()
{

 
    // Get the current window position, and set the new size
    CRect rect;
    GetWindowRect(rect);

	m_WindowRect = rect ;

    CSize ScreenSize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
    
	// Need to check it'll fit on screen: Too far right?
	if (m_WindowRect.right > ScreenSize.cx)
        m_WindowRect.OffsetRect(-(m_WindowRect.right - ScreenSize.cx), 0);

    // Too far left?
    if (m_WindowRect.left < 0)
        m_WindowRect.OffsetRect( -m_WindowRect.left, 0);

    // Bottom falling out of screen?
    if (m_WindowRect.bottom > ScreenSize.cy)
    {
        CRect ParentRect;
        m_pParent->GetWindowRect(ParentRect);
        m_WindowRect.OffsetRect(0, -(m_WindowRect.bottom - ScreenSize.cy));
    }

	// Top going out of screen ?
	if (m_WindowRect.top < 0)
    {
        CRect ParentRect;
        m_pParent->GetWindowRect(ParentRect);
        m_WindowRect.OffsetRect(0, -m_WindowRect.top);
    }

    // Set the window size and position
    MoveWindow(m_WindowRect, TRUE);

}
