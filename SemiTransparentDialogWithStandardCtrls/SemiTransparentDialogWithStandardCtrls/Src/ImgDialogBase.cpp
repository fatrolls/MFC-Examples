// TransparentDialogBase.cpp : implementation file
//

#include "stdafx.h"
#include "./ImgDialogBase.h"
#include "./Utility.h"


// CImgDialogBase dialog
BEGIN_MESSAGE_MAP(CImgDialogBase, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CImgDialogBase, CDialog)

std::map<HWND, tagCtrlInfo>	CImgDialogBase::s_mpCtrl;

//-------------------------------------------------------------------------
// Function Name    :CImgDialogBase
// Parameter(s)     :UINT nIDD			The dialog IDD
//					:LPCTSTR lpszFile	The image file path
//					:CWnd* pParent		The parent wnd
// Create			:2007-4-28 16:26 Jerry.Wang
// Memo             :contructor
//-------------------------------------------------------------------------
CImgDialogBase::CImgDialogBase(  UINT nIDD
							   , LPCTSTR lpszFile
							   , CWnd* pParent /*=NULL*/)
	: CDialog( nIDD, pParent)
	, m_nWidth(0)
	, m_nHeigh(0)
	, m_pImage( new Image(lpszFile) )
	, m_hFakeWnd(NULL)
	, m_bEnableDrag(TRUE)
	, m_nAlpha(0)
	, m_bShown(FALSE)
	, m_bIsRefreshing(FALSE)
{
	VERIFY( CUtility::IsFileExist(lpszFile) );
	VERIFY( m_pImage != NULL );
	m_nWidth = m_pImage->GetWidth();
	m_nHeigh = m_pImage->GetHeight();

	m_strWndClassName.Format( _T("FakeWnd%X"), GetTickCount());
}

//-------------------------------------------------------------------------
// Function Name    :CImgDialogBase
// Parameter(s)     :LPCTSTR lpszFile	The image file path
//					:UINT nID			The dialog IDD
// Create			:2007-4-28 16:28 Jerry.Wang
// Memo             :contructor
//-------------------------------------------------------------------------
CImgDialogBase::CImgDialogBase(  UINT nIDD
							   , UINT nImgID
							   , LPCTSTR lpszType
							   , HINSTANCE hResourceModule
							   , CWnd* pParent /*=NULL*/)
   : CDialog( nIDD, pParent)
   , m_nWidth(0)
   , m_nHeigh(0)
   , m_pImage( CUtility::LoadImage( nImgID, lpszType, hResourceModule) )
   , m_hFakeWnd(NULL)
   , m_bEnableDrag(TRUE)
   , m_nAlpha(0)
   , m_bShown(FALSE)
   , m_bIsRefreshing(FALSE)
{
	VERIFY( m_pImage != NULL );
	m_nWidth = m_pImage->GetWidth();
	m_nHeigh = m_pImage->GetHeight();

	m_strWndClassName.Format( _T("FakeWnd%X"), GetTickCount());
}

CImgDialogBase::~CImgDialogBase()
{
	if( m_pImage )
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void CImgDialogBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


//-------------------------------------------------------------------------
// Function Name    :EnableDrag
// Parameter(s)     :BOOL bEnabled
// Return           :
// Create			:2007-5-8 11:42 Jerry.Wang
// Memo             :TRUE: the window is dragable; FALSE:not dragable
//-------------------------------------------------------------------------
void CImgDialogBase::EnableDrag(BOOL bEnabled)
{
	m_bEnableDrag = bEnabled;
}

//-------------------------------------------------------------------------
// Function Name    :OnLButtonDown
// Parameter(s)     :
// Return           :
// Create			:2007-5-7 18:52 Jerry.Wang
// Memo             :To make this dialog can be dragable
//-------------------------------------------------------------------------
void CImgDialogBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_bEnableDrag )
	{
		::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, 0xF012, 0);  
	}

	CDialog::OnLButtonDown(nFlags, point);
}




//-------------------------------------------------------------------------
// Function Name    :CreateFakeWnd
// Parameter(s)     :
// Return           :
// Create			:2007-5-7 18:50 Jerry.Wang
// Memo             :create the fake window
//-------------------------------------------------------------------------
void CImgDialogBase::CreateFakeWnd(void)
{
	DestoryFakeWnd();

	WNDCLASSEX wcex;

	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= ::DefWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= ::GetModuleHandle(NULL);
	wcex.hIcon			= NULL;
	wcex.hCursor		= ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= m_strWndClassName;
	wcex.hIconSm		= NULL;

	VERIFY( RegisterClassEx(&wcex) );

	CRect rc;
	GetWindowRect(rc);
	m_hFakeWnd = ::CreateWindowEx( WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LEFT
		, m_strWndClassName
		, NULL
		, WS_VISIBLE | WS_OVERLAPPED
		, rc.left
		, rc.top
		, rc.Width()
		, rc.Height()
		, GetSafeHwnd()
		, NULL
		, ::GetModuleHandle(NULL)
		, NULL
		);
	ASSERT( m_hFakeWnd != NULL );

}


//-------------------------------------------------------------------------
// Function Name    :DestoryFakeWnd
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 11:43 Jerry.Wang
// Memo             :Destory the fake wnd
//-------------------------------------------------------------------------
void CImgDialogBase::DestoryFakeWnd(void)
{
	if( m_hFakeWnd != NULL )
	{
		::DestroyWindow(m_hFakeWnd);
		m_hFakeWnd = NULL;

		::UnregisterClass( m_strWndClassName, ::GetModuleHandle(NULL) );
	}
}



BOOL CImgDialogBase::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the dialog style
	::SetWindowPos( GetSafeHwnd()
		, NULL
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, SWP_NOMOVE | SWP_NOZORDER
		);

	CreateFakeWnd();

	::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	BYTE bTran = 5;
	::SetLayeredWindowAttributes( m_hWnd, 0, bTran, LWA_ALPHA);

	HookControlUpdate(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}




//-------------------------------------------------------------------------
// Function Name    :DrawCtrl
// Parameter(s)     :
// Return           :
// Create			:2007-4-28 16:21 Jerry.Wang
// Memo             :Draw the child control
//-------------------------------------------------------------------------
void CImgDialogBase::DrawCtrl( Graphics & graphics, HDC hDC, HWND hWnd)
{
	if( !::IsWindow(hWnd) )
		return;

	RECT rc;
	::GetWindowRect( hWnd, &rc);
	ScreenToClient(&rc);

	HDC hdcMemory = ::CreateCompatibleDC(hDC);
	HBITMAP hBitmap = ::CreateCompatibleBitmap( hDC, rc.right - rc.left, rc.bottom - rc.top);
	HGDIOBJ hbmpOld = ::SelectObject( hdcMemory, hBitmap); 

	::SendMessage( hWnd, WM_PRINT, (WPARAM)hdcMemory, (LPARAM)PRF_NONCLIENT | PRF_CLIENT | PRF_CHILDREN | PRF_CHECKVISIBLE | PRF_ERASEBKGND | PRF_OWNED);

	Bitmap bitmap( hBitmap, NULL);
	graphics.DrawImage( &bitmap, rc.left, rc.top);

	::SelectObject( hdcMemory, hbmpOld); 
	::DeleteDC(hdcMemory);
	::DeleteObject(hBitmap); 
}


	
//-------------------------------------------------------------------------
// Function Name    :Refresh
// Parameter(s)     :
// Return           :
// Create			:2007-4-27 19:17 Jerry.Wang
// Memo             :update the windows display
//-------------------------------------------------------------------------
void CImgDialogBase::Refresh(void)
{
	if( m_bIsRefreshing )
		return;

	if( !IsWindow(m_hFakeWnd) )
		return;

	m_bIsRefreshing = TRUE;

	RECT rc;
	::GetWindowRect( m_hFakeWnd, &rc);
	POINT ptSrc = { 0, 0};
	POINT ptWinPos = { rc.left, rc.top};
	SIZE szWin = { m_nWidth, m_nHeigh };
	BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, m_nAlpha, AC_SRC_ALPHA };


	HDC hDC = ::GetDC(m_hFakeWnd);
	HDC hdcMemory = ::CreateCompatibleDC(hDC);

	BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
	int nBytesPerLine = ((m_nWidth * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
	stBmpInfoHeader.biWidth = m_nWidth;   
	stBmpInfoHeader.biHeight = m_nHeigh;   
	stBmpInfoHeader.biPlanes = 1;   
	stBmpInfoHeader.biBitCount = 32;   
	stBmpInfoHeader.biCompression = BI_RGB;   
	stBmpInfoHeader.biClrUsed = 0;   
	stBmpInfoHeader.biSizeImage = nBytesPerLine * m_nHeigh;   

	PVOID pvBits = NULL;   
	HBITMAP hbmpMem = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
	ASSERT(hbmpMem != NULL);
	memset( pvBits, 0, m_nWidth * 4 * m_nHeigh);
	if(hbmpMem)   
	{   
		HGDIOBJ hbmpOld = ::SelectObject( hdcMemory, hbmpMem); 
		Graphics graph(hdcMemory);
		
		graph.SetSmoothingMode(SmoothingModeNone);
		
		// Draw the background
		graph.DrawImage( m_pImage, 0, 0, m_nWidth, m_nHeigh);

		// On draw 
		OnDraw(graph);
		
		// Draw all the controls
		HWND hwndChild = ::GetWindow( GetSafeHwnd(), GW_CHILD);  
		while(hwndChild)   
		{
			DrawCtrl( graph, hDC, hwndChild);
			hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT);   
		}

		// draw the caret
		DrawCaret(graph);			
		
		::UpdateLayeredWindow( m_hFakeWnd
			, hDC
			, &ptWinPos
			, &szWin
			, hdcMemory
			, &ptSrc
			, 0
			, &stBlend
			, ULW_ALPHA
			);

		graph.ReleaseHDC(hdcMemory);
		::SelectObject( hdcMemory, hbmpOld);   
		::DeleteObject(hbmpMem); 
	}

	
	::DeleteDC(hdcMemory);
	::DeleteDC(hDC);

	m_bIsRefreshing = FALSE;
}

void CImgDialogBase::DrawCaret(Graphics & graph)
{
	CWnd * pWnd = GetFocus();
	if( pWnd == NULL ||
		!::IsWindow(pWnd->GetSafeHwnd()) )
	{
		return;
	}

	TCHAR tszBuf[MAX_PATH] = {'\0'};
	::GetClassName( pWnd->GetSafeHwnd(), tszBuf, MAX_PATH);
	CString strClassName(tszBuf);

	if( strClassName.CompareNoCase(_T("EDIT")) != 0 )
		return;

	CPoint pt = GetCaretPos();
	pWnd->ClientToScreen(&pt);
	ScreenToClient(&pt);

	Pen pen( Color::Black, 1.0f);
	graph.DrawLine( &pen, pt.x, pt.y, pt.x, pt.y + 13);
}


void CImgDialogBase::HookControlUpdate(HWND hWnd)
{
	tagCtrlInfo stCtrlInfo = {0};
	stCtrlInfo.pImgDlg = this;
	stCtrlInfo.pWndProc = (WNDPROC)::GetWindowLongPtr( hWnd, GWLP_WNDPROC);
	s_mpCtrl[hWnd] = stCtrlInfo;
	::SetWindowLongPtr( hWnd, GWLP_WNDPROC, (LONG_PTR)(&CImgDialogBase::CtrlWndProc) );

	HWND hChild = ::GetWindow( hWnd, GW_CHILD);  
	while(hChild)   
	{
		HookControlUpdate(hChild);
		hChild = ::GetWindow( hChild, GW_HWNDNEXT);   
	}
}

void CImgDialogBase::UnhookControlUpdate(HWND hWnd)
{
	if( !::IsWindow(hWnd) )
		return;

	std::map<HWND, tagCtrlInfo>::iterator iter;
	iter = s_mpCtrl.find(hWnd);
	if( iter != s_mpCtrl.end() )
		s_mpCtrl.erase(iter);

	HWND hChild = ::GetWindow( hWnd, GW_CHILD);  
	while(hChild)   
	{
		UnhookControlUpdate(hChild);
		hChild = ::GetWindow( hChild, GW_HWNDNEXT);   
	}
}

LRESULT CALLBACK CImgDialogBase::CtrlWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	std::map<HWND, tagCtrlInfo>::iterator iter;
	iter = s_mpCtrl.find(hWnd);
	if( iter == s_mpCtrl.end() )
		return ::DefWindowProc( hWnd, nMsg, wParam, lParam);

	LRESULT lResult = iter->second.pWndProc( hWnd, nMsg, wParam, lParam);
	switch (nMsg)
	{
		case WM_PAINT:
		case WM_CAPTURECHANGED:
		//case WM_NCPAINT:
		//case WM_CTLCOLOR:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSTATIC:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORSCROLLBAR:
			{
				iter->second.pImgDlg->Refresh();
				break;
			}

		default:
			break;
		}
	return lResult;
}


//-------------------------------------------------------------------------
// Function Name    :OnDraw
// Parameter(s)     :
// Return           :
// Create			:2007-5-7 18:52 Jerry.Wang
// Memo             :This function can be overridden in the child class
//-------------------------------------------------------------------------
void CImgDialogBase::OnDraw(Graphics & graphics)
{
}



//-------------------------------------------------------------------------
// Function Name    :OnEraseBkgnd
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 13:50 Jerry.Wang
// Memo             :Erase back ground with nothing
//-------------------------------------------------------------------------
BOOL CImgDialogBase::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}



//-------------------------------------------------------------------------
// Function Name    :OnMove
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 13:49 Jerry.Wang
// Memo             :When the dialog moved
//-------------------------------------------------------------------------
void CImgDialogBase::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	if( ::IsWindow(m_hFakeWnd) )
	{
		::SetWindowPos( m_hFakeWnd
			, NULL
			, x
			, y
			, 0
			, 0
			, SWP_NOZORDER | SWP_NOSIZE
			);
	}
}

//-------------------------------------------------------------------------
// Function Name    :OnSize
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 13:49 Jerry.Wang
// Memo             :When the dialog sized
//-------------------------------------------------------------------------
void CImgDialogBase::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( ::IsWindow(m_hFakeWnd) )
	{
		::SetWindowPos( m_hFakeWnd
			, NULL
			, 0
			, 0
			, cx
			, cy
			, SWP_NOZORDER | SWP_NOMOVE
			);	
	}	
}




//-------------------------------------------------------------------------
// Function Name    :OnShowWindow
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 13:49 Jerry.Wang
// Memo             :When the Visible is changed
//-------------------------------------------------------------------------
void CImgDialogBase::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	::ShowWindow( m_hFakeWnd, bShow ? SW_SHOWNA : SW_HIDE);

	if( !m_bShown )
	{
		m_bShown = TRUE;
		AfxBeginThread( (AFX_THREADPROC)ShowMotionThread, this);
	}
}





//-------------------------------------------------------------------------
// Function Name    :OnActivate
// Parameter(s)     :
// Return           :
// Create			:2007-5-8 13:50 Jerry.Wang
// Memo             :When activated, refresh the window, this is necessary
//-------------------------------------------------------------------------
void CImgDialogBase::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	if( nState == WA_ACTIVE )
	{
		Invalidate(TRUE);
	}
}

UINT __cdecl CImgDialogBase::ShowMotionThread( LPVOID pParam )
{
	CImgDialogBase * pThis = static_cast<CImgDialogBase*>(pParam);

	while (pThis->m_nAlpha < 255)
	{
		pThis->m_nAlpha += 30;
		if( pThis->m_nAlpha > 255 )
			pThis->m_nAlpha = 255;

		::SendMessage( pThis->GetSafeHwnd(), WM_PAINT, 0, 0);
		Sleep(20);
	}
	
	return 0;
}

void CImgDialogBase::OnCancel()
{
	DestoryFakeWnd();
	CDialog::OnCancel();
}

void CImgDialogBase::OnOK()
{
	DestoryFakeWnd();
	CDialog::OnOK();
}

void CImgDialogBase::OnClose()
{
	DestoryFakeWnd();
	CDialog::OnClose();
}

void CImgDialogBase::PostNcDestroy()
{
	UnhookControlUpdate(GetSafeHwnd());

	CDialog::PostNcDestroy();
}
