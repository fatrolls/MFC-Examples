/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker.cpp : implementation file
//
//

#include "hello.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker

CVxOptPicker::CVxOptPicker(int width, int height, int rows, int columns)
{

	m_CurText			= "M";
	m_CurBitmap			= 0;
	m_CurButton			= NULL ;


	m_PopupWnd			= NULL ;
	m_PopupWndVisible	= 0 ;

	m_Width				= width; // default
	m_Height			= height;
	m_Rows				= rows;
	m_Columns			= columns;

}

CVxOptPicker::~CVxOptPicker()
{
	ASSERT(m_PopupWnd);

	/* We don't need this loop since in real dialog, buttons WILL get deleted
        CWnd *childWnd;
        childWnd = (CWnd *)m_PopupWnd->GetWindow(GW_CHILD);
        while(childWnd != NULL)
        {
                TRACE("Hmmm somebody created a control and did not add\
                           it to the control array. This mesg. is coming out\
                           from CVxDialog::OnClose() function call.");
                delete(childWnd);
                childWnd = (CWnd *)m_PopupWnd->GetWindow(GW_CHILD);
        }
	*/
	m_PopupWnd->DestroyWindow();
}

BEGIN_MESSAGE_MAP(CVxOptPicker, CButton)
    //{{AFX_MSG_MAP(CVxOptPicker)
    ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_CONTROL_REFLECT(WM_ACTIVATE, OnKillFocus)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker message handlers

void CVxOptPicker::OnKillFocus( )
{
	CPoint point ;
    DWORD pos = GetMessagePos();
    point = CPoint(LOWORD(pos), HIWORD(pos));

	CRect pickerRect, popupRect ;
	this->GetWindowRect(pickerRect);
	ASSERT(m_PopupWnd);
	m_PopupWnd->GetWindowRect(popupRect);

	// Check to see if the point is outside of Picker and Popup
	// window rectangles. If it is then hide the popup window
    if ( !(pickerRect.PtInRect(point)) && !(popupRect.PtInRect(point)))
		m_PopupWnd->ShowWindow(SW_HIDE);
}
	

int CVxOptPicker::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CButton::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetWindowSize();    // resize appropriately
	
	// Here we don't need to worry about the position of the window
	// since we going to relocate it before it is shown anyways.
	m_PopupWnd = new CVxOptPopup(CPoint(0,0), this, 10);

	return 0;
}

// On mouse click, create and show a CVxOptPopup window for colour selection
BOOL CVxOptPicker::OnClicked()
{
	
	// If already visible then close the popup window
	if(m_PopupWndVisible == 1)
	{
		m_PopupWndVisible = 0 ;
		m_PopupWnd->ShowWindow(SW_HIDE);
		//ReleaseCapture();
	}
	else
	{
		CRect rect, popupRect, curButRect ;
		// Lets get window rect for the picker button
		GetWindowRect(rect);
		// I always like to assert on my variables
		ASSERT(m_PopupWnd);
		// Lets get the popup window rect. We need to know the Width, Height
		m_PopupWnd->GetWindowRect(popupRect);
		
		if(m_CurButton == NULL)
		{
			// First move the window at the bottom of the Picker(sucker!) button
			m_PopupWnd->MoveWindow(rect.left, rect.top, popupRect.Width(), popupRect.Height(), TRUE);
		}
		else
		{
			m_CurButton->GetWindowRect(curButRect);
			m_PopupWnd->ScreenToClient(curButRect);
			m_PopupWnd->MoveWindow(rect.left - curButRect.left + CONTROL_OFFSET, 
								   rect.top - curButRect.top + CONTROL_OFFSET, 
								   popupRect.Width(), popupRect.Height(), TRUE);
		}
		// Now lets relocate again in case window has gone outside the screen
		m_PopupWnd->SetWindowSize();
		// Now that we have repositioned it correctly, we are ready to rock'n'roll
		m_PopupWndVisible	= 1 ; // Set the visible flag to true
		m_PopupWnd->ShowWindow(SW_SHOW);
		//m_PopupWnd->SetCapture();
	}
    // Docs say I should return FALSE to stop the parent also getting the message.
    // HA! What a joke.
    return TRUE;
}

void CVxOptPicker::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct != NULL);
    
    CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rect = lpDrawItemStruct->rcItem;
    UINT state = lpDrawItemStruct->itemState;
    DWORD dwStyle = GetStyle();

    CSize Margins(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Draw arrow
    pDC->FillSolidRect(m_ArrowRect, ::GetSysColor(COLOR_3DFACE));
    pDC->DrawEdge(m_ArrowRect, EDGE_RAISED, BF_RECT);

    int nArrowTop = m_ArrowRect.top + m_ArrowRect.Height()/2;
    int nArrowBottom = m_ArrowRect.bottom - 1 - 2*Margins.cx;
    int nArrowHeight = nArrowBottom - nArrowTop + 1;
    int nAdjust = (m_ArrowRect.Height() - 4*Margins.cy - nArrowHeight)/2;

    CPoint p[4];
    //p[0] = CPoint(m_ArrowRect.left + m_ArrowRect.Width()/2, nArrowBottom - nAdjust);
    //p[1] = CPoint(m_ArrowRect.left + 2*Margins.cy, nArrowTop - nAdjust); 
    //p[2] = CPoint(m_ArrowRect.right - 2*Margins.cy-1, nArrowTop - nAdjust); 
    //p[3] = p[0];

	// If you want rectangle then use following pts
	// 1  2
	// 4  3
    
	p[0] = CPoint(m_ArrowRect.left+m_ArrowRect.Width()/2-CONTROL_OFFSET, 
				  m_ArrowRect.top+m_ArrowRect.Height()/2-3*CONTROL_OFFSET/4);
    p[1] = CPoint(m_ArrowRect.left+m_ArrowRect.Width()/2+CONTROL_OFFSET, 
				  m_ArrowRect.top+m_ArrowRect.Height()/2-3*CONTROL_OFFSET/4);
    p[2] = CPoint(m_ArrowRect.left+m_ArrowRect.Width()/2+CONTROL_OFFSET, 
				  m_ArrowRect.top+m_ArrowRect.Height()/2+3*CONTROL_OFFSET/4);
    p[3] = CPoint(m_ArrowRect.left+m_ArrowRect.Width()/2-CONTROL_OFFSET, 
				  m_ArrowRect.top+m_ArrowRect.Height()/2+3*CONTROL_OFFSET/4);
	
    pDC->SelectStockObject(BLACK_BRUSH);
    pDC->SelectStockObject(BLACK_PEN);
    pDC->Polygon(p, 4);

    pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);

    // Must reduce the size of the "client" area of the button due to edge thickness.
    rect.DeflateRect(Margins.cx, Margins.cy);

    // Fill remaining area with colour
    rect.right -= m_ArrowRect.Width();


	if(m_CurBitmap == 0)
	{
		rect.InflateRect(-2,-2);
		pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
		pDC->DrawText(this->m_CurText, rect,  DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	}
	else
	{

		HBITMAP hBitmap =(HBITMAP) LoadImage (AfxGetInstanceHandle(),
						MAKEINTRESOURCE (m_CurBitmap), IMAGE_BITMAP,
						0,0,LR_DEFAULTCOLOR|LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS );
		
		//GetClientRect (rect);
		CDC memdc;
		CBitmap bmp;
		CBitmap *poldbmp;
		bmp.Attach (hBitmap);
		BITMAP bitmap;
		bmp.GetBitmap (&bitmap);
		memdc.CreateCompatibleDC( pDC );
		// Select the bitmap into the DC
		poldbmp = (CBitmap *) memdc.SelectObject( &bmp );
		// Copy (BitBlt) bitmap from memory DC to screen DC
		// I want it to look like a proper button hence
		pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
		rect.InflateRect(-4,-4);
		pDC -> StretchBlt( rect.left,rect.top,
						   rect.right-rect.left, 
						   rect.bottom -rect.top, &memdc,0,0,
						   bitmap.bmWidth,bitmap.bmHeight, SRCCOPY );
		//pDC -> BitBlt( rect.left,rect.top,
		//				   rect.right-rect.left, 
		//				   rect.bottom -rect.top, &memdc,0,0,
		//				   SRCCOPY );
		memdc.SelectObject( poldbmp );
	}

    //pDC->FillSolidRect(rect, m_crColour);
    
    // Draw focus rect
    if (state & ODS_FOCUS) 
    {
        rect.DeflateRect(1,1);
        pDC->DrawFocusRect(rect);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker overrides

void CVxOptPicker::PreSubclassWindow() 
{
    ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn
    CButton::PreSubclassWindow();
    SetWindowSize();                     // resize appropriately
}

/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker implementation

void CVxOptPicker::SetWindowSize()
{
    // Get size dimensions of edges
    CSize MarginSize(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Get size of dropdown arrow
    int nArrowWidth = max(::GetSystemMetrics(SM_CXHTHUMB), 10*MarginSize.cx);
    int nArrowHeight = max(::GetSystemMetrics(SM_CYVTHUMB), 5*MarginSize.cy);
    CSize ArrowSize(max(nArrowWidth, nArrowHeight), max(nArrowWidth, nArrowHeight));

    // Make sure arrow size is an odd number (just looks neater)
    if (ArrowSize.cx%1 == 0) { ArrowSize.cx++; ArrowSize.cy++; }

    // ArrowSize.cx = ArrowSize.cy = 41; - for testing.

    // Get window size
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    // Set window size at least as wide as 2 arrows, and as high as arrow + margins
    int nWidth = max(rect.Width(), 2*ArrowSize.cx + 2*MarginSize.cx);
    //MoveWindow(rect.left, rect.top, /*nWidth*/50+2*ArrowSize.cx, /*ArrowSize.cy+2*MarginSize.cy*/50, TRUE);
    MoveWindow(rect.left, rect.top, 
		       m_Width + 2*CONTROL_OFFSET + ArrowSize.cx, 
			   m_Height + 2*CONTROL_OFFSET, 
			   TRUE);

    // Get the new coords of this window
    GetWindowRect(rect);
    ScreenToClient(rect);

    // Get the rect where the arrow goes, and convert to client coords.
    m_ArrowRect.SetRect(rect.right - ArrowSize.cx - MarginSize.cx, 
                        rect.top + MarginSize.cy, rect.right - MarginSize.cx,
                        rect.bottom - MarginSize.cy);
}
