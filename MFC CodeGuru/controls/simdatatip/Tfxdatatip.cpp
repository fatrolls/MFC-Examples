/*
* Configuration control preamble *********************************************
*
* PROJECT:          C++ Library
*
* TITLE:            Data Tip window (aka. enhanced Tooltips)
* FILENAME:         tfxdatatip.cpp
*
* CREATED:          10 April 1997
* ORIGINATOR:       S.A.J. Wilson
*
*                   (c) Copyright 1997
*                       Technisoft Ltd.
*
******************************************************************************
*                              ISSUE HISTORY                                                               
*
* 10-APR-1997       SAJW
* Issue 0.1         Created 
*
* 18-APR-1997       SAJW
* Issue 1.0         First release
*
******************************************************************************
*/
#include "stdafx.h"
#include "tfxdatatip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// define the offset above cursor
static const CPoint _defOffset(10, 5);

// border area around the text
static const short _border = 2;

// define the active border for data tips
static const short _horizontal  = 2;
static const short _vertical    = 2;

// class data members
BOOL  TFXDataTip::_registered = FALSE;
short TFXDataTip::_delay = 500;
short TFXDataTip::_count = 0;

// GDI objects used for drawing operations in module
static CFont   _font;
static CBrush* _brush = NULL;

// hook information
HHOOK TFXDataTip::_hookProc = NULL;
TFXDataTip* TFXDataTip::_current = NULL;


// special destructor object for clearing up GDI objects
struct _brush_destructor
{
    ~_brush_destructor( )
    {
        delete _brush;
        _brush = NULL;
    }
};
static const _brush_destructor _destroyer;

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             RegisterWnd
*
* DESCRIPTION:      This method registers the window class used by the DataTip
*                   windows. This must be called after the class background
*                   brush has been constructed.
*
* PARAMETERS:       none
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::RegisterWnd( )
{
    // check for prior registration
    if (_registered) return;

    // initialise the basic information before registration
    HINSTANCE hInst = AfxGetInstanceHandle( );

    // initialise the window class information
	WNDCLASS wndcls;
	wndcls.style         = CS_SAVEBITS | CS_DBLCLKS;
    wndcls.lpfnWndProc   = ::DefWindowProc;
	wndcls.cbClsExtra    = 0;
    wndcls.cbWndExtra    = 0;
	wndcls.hInstance     = hInst;
	wndcls.hIcon         = NULL;
    wndcls.hCursor       = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.hbrBackground = *_brush;
	wndcls.lpszMenuName  = NULL;
	wndcls.lpszClassName = "TFXDataTip";

    // register the window class
    if (!AfxRegisterClass(&wndcls))
		AfxThrowResourceException();

    _registered = TRUE;
}

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             Initialise
*
* DESCRIPTION:      This method initialise the DataTip class. It creates the
*                   default font used for DataTips, the brush used to paint
*                   windows background, and registers the window class. 
*
*                   If there is currently no hook procedure instaklled for
*                   the class it alos installs a keyboard hook procedure.
*
* PARAMETERS:       none
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::Initialise( )
{
    if (_font.GetSafeHandle( ) == NULL)
    {
        // create the default tip font
        LOGFONT lFont;
        GetObject(GetStockObject(ANSI_VAR_FONT), sizeof lFont, &lFont);
        _font.CreateFontIndirect(&lFont);

        // create the other GDI objects
        _brush = new CBrush(::GetSysColor(COLOR_INFOBK));
    }

    // register the window class
    RegisterWnd( );

    // install the keyboard hook procedure
    if (_hookProc == NULL)
    {
        _hookProc = ::SetWindowsHookEx(WH_KEYBOARD, 
                                       (HOOKPROC)KeyboardHookCallback,
                                       NULL,
                                       ::GetCurrentThreadId( ));
    }
}

/*
* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             KeyboardHookCallback
*
* DESCRIPTION:      This method provides the keyboard hook callback procedure.
*                   If there is currently an active DataTip then when a key 
*                   is pressed it will hide the tip, before passing on the
*                   message to the next procedure in the hook chain.
*
* PARAMETERS:       code                                        [input]
*                   message wParam                              [input]
*                   message lParam                              [input]
*
* RETURN TYPE:      LRESULT
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
LRESULT CALLBACK TFXDataTip::KeyboardHookCallback(int code, WPARAM wParam, LPARAM lParam)
{
    // if keypress has occured then hide any visible data tips
    if (code >= 0)
    {
        if (_current != NULL)
        {
            _current->Hide( );
        }
    }

    // chain to the next hook procedure
    return ::CallNextHookEx(_hookProc, code, wParam, lParam);
}


/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             constructor
*
* DESCRIPTION:      This method contructs a DataTip object. IT calls the class
*                   intialisation procedure before initialising the object
*                   data members. Finally it increments the object count for
*                   the class.
*
* PARAMETERS:       none
*
* RETURN TYPE:      not allowed
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
TFXDataTip::TFXDataTip()
{
    Initialise( );
    m_ready  = FALSE;
    m_timer  = 0;
    m_origin = CPoint(0, 0);
    m_offset = _defOffset;
    m_on     = FALSE;

    // incrment the object count
    _count++;
}

/*
* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             destructor
*
* DESCRIPTION:      This method destructs the DataTip object, decrementing the
*                   class object count. If this is the last object to be
*                   destroyed then the hook procedure is removed.
*
* PARAMETERS:       none allowed
*
* RETURN TYPE:      not allowed
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
* dd-mmm-yyyy       ANO     ...
*
******************************************************************************
*/
TFXDataTip::~TFXDataTip()
{
    _count--;
    if ( (_count == 0) && (_hookProc != NULL) )
    {
        ::UnhookWindowsHookEx(_hookProc);
        _hookProc = NULL;
    }
}

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             Create
*
* DESCRIPTION:      This method creates the DataTip window. This is an
*                   instantiation of the pre-registered TFXDataTip window
*                   class. If the creation is successful then the method
*                   returns TRUE.
*
* PARAMETERS:       parent window                               [input]
*
* RETURN TYPE:      BOOL
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
BOOL TFXDataTip::Create(CWnd* pParentWnd) 
{
    m_parent = pParentWnd;
	m_ready = CWnd::CreateEx(WS_EX_LEFT | WS_EX_TOOLWINDOW,
                             "TFXDataTip", 
                             NULL,
                             WS_POPUP | WS_BORDER | WS_CLIPSIBLINGS, 
                             0, 0, 10, 10,
                             pParentWnd->m_hWnd, 
                             NULL);

    return m_ready;
}

/*
* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             Hide
*
* DESCRIPTION:      This method hides the DataTip window, killing the 
*                   associated timer, and releasing the mouse capture. The
*                   class active pointer is set to NULL.
*
* PARAMETERS:       none
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::Hide( )
{
    if (!m_ready) return;
    ShowWindow(SW_HIDE);
    KillTimer(m_timer);
    ::ReleaseCapture( );

    // reset the current tip window
    _current = NULL;
}

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             Set
*
* DESCRIPTION:      This method sets the values to be used for a DataTip,
*                   at the same restarting the delay timer if the provided
*                   location is within the parent window's borders.
*
* PARAMETERS:       point to display tip                        [input]
*                   text for tip                                [input]
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::Set(CPoint point, const CString& tip)
{
    // check whether tips are turned on
    if (!m_on) return;

    // determine whether the point is in the parent window
    CRect rect;
    m_parent->GetClientRect(&rect);
    if (rect.PtInRect(point))
    {
        // change data tip if position has changed
        m_parent->ClientToScreen(&point);
        if (point != m_origin)
        {
            m_tip    = tip;
            m_origin = point;

            // re-start the timer
            KillTimer(m_timer);
            m_timer = SetTimer(1010, _delay, NULL);
        }
    }
}
    
/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             Display
*
* DESCRIPTION:      This method displays the DataTip window. If there is a
*                   currently active DataTip this is hidden before the tip
*                   size is calculated and the tip positioned at the 
*                   specified offset from the mouse pointer location.
*
* PARAMETERS:       none
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::Display( )
{
    if (!m_ready) return;

    // hide any other currently visible data tips
    if (_current != NULL)
    {
        _current->Hide( );
    }

    // determine the size of the data tip text 
    // in order to size the window correctly
    CClientDC dc(this);
    dc.SelectObject(&_font);
    CSize size = dc.GetTextExtent(m_tip);

    // capture the mouse in order to be able to 
    // determine when to hide the window
    SetCapture( );

    // determine the window size and position
    // displayed above and centered on the origin
    CRect wndRect(m_origin.x, 
                  m_origin.y, 
                  m_origin.x + size.cx, 
                  m_origin.y + size.cy); 

    // adjust window for offset and borders
    wndRect.InflateRect(2 * _border, _border);
    wndRect.OffsetRect(m_offset);

    // update window position and display
    SetWindowPos(&wndTop, 
                 wndRect.left,
                 wndRect.top,
                 wndRect.Width( ), 
                 wndRect.Height( ), 
                 SWP_SHOWWINDOW | SWP_NOACTIVATE);

    // define the active area around the cursor position
    m_captureRect = CRect(m_origin.x - _horizontal, 
                          m_origin.y - _vertical,
                          m_origin.x + _horizontal,
                          m_origin.y + _vertical);

    // set the current data tip window
    _current = this;
}

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             DestroyWindow
*
* DESCRIPTION:      This method ensures that when the window is destroyed the
*                   tip timer is also destroyed.
*
* PARAMETERS:       none
*
* RETURN TYPE:      BOOL
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
BOOL TFXDataTip::DestroyWindow() 
{
    KillTimer(m_timer);
	return CWnd::DestroyWindow();
}


/*
* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             PreTranslateMessage
*
* DESCRIPTION:      This method is called by MFC giving the tip chance to 
*                   hide itself if the user presses one of the mouse buttons.
*
* PARAMETERS:       message                                     [input]
*
* RETURN TYPE:      BOOL
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
BOOL TFXDataTip::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
    {
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_CANCELMODE:
            Hide( );
            break;
    }

	return CWnd::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(TFXDataTip, CWnd)
	//{{AFX_MSG_MAP(TFXDataTip)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             OnPaint
*
* DESCRIPTION:      This method handles the WM_PAINT message. It paints the
*                   tip text into the tip window area.
*
* PARAMETERS:       none
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

    CRect rect;
    GetClientRect(&rect);

    // initialise the device context for drawing
    CFont* pOldFont = dc.SelectObject(&_font);
    dc.SetBkColor(::GetSysColor(COLOR_INFOBK));
    dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));

    // draw the data tip
    dc.SetTextAlign(TA_TOP | TA_CENTER);
    dc.TextOut((rect.Width( ) / 2), (_border / 2), m_tip);

    // restore the device context
    dc.SelectObject(pOldFont);
}

/*

* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             OnMouseMove
*
* DESCRIPTION:      This method determines whether the mouse has moved outside
*                   of the capture rectangle and if so hides the tip window.
*
* PARAMETERS:       mouse flags                                 [input]
*                   mouse location                              [input]
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

    // determine if a mouse button has been pressed or
    // we have moved outside of the active capture area
    ClientToScreen(&point);
    if (!m_captureRect.PtInRect(point))
    {
        Hide( );
    }
}

/*
* Method preamble ************************************************************
*
* CLASS:            TFXDataTip
* NAME:             OnTimer
*
* DESCRIPTION:      This method handles the WM_TIMER message. Provided the 
*                   mouse has not moved from its original location set when
*                   the tip was initialised then the tip is displayed at
*                   this location.
*
* PARAMETERS:       event ID                                    [input]
*
* RETURN TYPE:      void
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
******************************************************************************
*/
void TFXDataTip::OnTimer(UINT nIDEvent) 
{
    KillTimer(m_timer);

    // make sure that cursor hasn't moved before displaying the data tip
    CPoint point;
    if (::GetCursorPos(&point))
    {
        if (point == m_origin)
        {
            Display( );
        }
    }
}

