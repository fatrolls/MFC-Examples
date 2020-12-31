// HyperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapButtonDemo.h"
#include "HyperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHyperDlg dialog


CHyperDlg::CHyperDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHyperDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CHyperDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	}


void CHyperDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHyperDlg)
	DDX_Control(pDX, IDC_BUTTON_3, m_wndButton3);
	DDX_Control(pDX, IDC_BUTTON_2, m_wndButton2);
	DDX_Control(pDX, IDC_BUTTON_1, m_wndButton1);
	DDX_Control(pDX, IDC_SPACE, m_wndSpace);
	//}}AFX_DATA_MAP
	}


BEGIN_MESSAGE_MAP(CHyperDlg, CDialog)
	//{{AFX_MSG_MAP(CHyperDlg)
	ON_WM_PAINT()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_RBUTTONDOWN()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperDlg message handlers

BOOL CHyperDlg::OnInitDialog() 
	{
	CDialog::OnInitDialog();
	
	// Build image for the background
	// ... Get the bitmap data
	LPCTSTR lpszBitmapResource = MAKEINTRESOURCE(IDB_SPACE);
	HINSTANCE hInstance = NULL;
	HRSRC hResourceInfoBlock = NULL;
	HGLOBAL hBitmapGlobal = NULL;
	HGLOBAL hBitmapCopy = NULL;
	DWORD nResourceSize = 0;
	LPBITMAPINFOHEADER  pCopyBitmapInfoHeader = NULL;

	hInstance = AfxFindResourceHandle(lpszBitmapResource, RT_BITMAP);
	hResourceInfoBlock = ::FindResource(hInstance, lpszBitmapResource, RT_BITMAP);
	hBitmapGlobal = ::LoadResource(hInstance, hResourceInfoBlock);
	if (hBitmapGlobal == NULL)
		{
		TRACE0("CHyperDlg::OnInitDialog : Failed to load bitmap resource, failing\n");
		return FALSE;
		}

	nResourceSize = ::SizeofResource(hInstance, hResourceInfoBlock);
	ASSERT(sizeof(BITMAPINFOHEADER) <= nResourceSize);

	// Memory may be read only, make a copy 
	void* pOldBitmapInfoHeader = (LPBITMAPINFOHEADER)::LockResource(hBitmapGlobal);
	hBitmapCopy = ::GlobalAlloc(GMEM_MOVEABLE, nResourceSize);
	pCopyBitmapInfoHeader = (LPBITMAPINFOHEADER)::GlobalLock(hBitmapCopy);
	ASSERT(pCopyBitmapInfoHeader != NULL);
	::CopyMemory(pCopyBitmapInfoHeader, pOldBitmapInfoHeader, nResourceSize);

	m_space = (HDIB)hBitmapCopy;

	::UnlockResource(hBitmapGlobal);
	if ((::GlobalUnlock(hBitmapCopy) == 0) && (::GetLastError() == NO_ERROR))
		VERIFY(::GlobalFree(hBitmapCopy) == NULL);

	// ... Get the top left
	m_wndSpace.GetWindowRect(m_spaceRect);
	ScreenToClient(m_spaceRect);
	
	// Initialize the bitmap buttons
	m_wndButton1.LoadBitmap(IDB_SUN, TRUE, RGB(255, 0, 255));
	m_wndButton1.SetTrackLook(TRUE);
	m_wndButton1.SetHyperLook(TRUE);
	m_wndButton1.SetToolTip(TRUE);

	m_wndButton2.LoadBitmap(IDB_SUN, TRUE, RGB(255, 0, 255));
	m_wndButton2.SetTrackLook(TRUE);
	m_wndButton2.SetHyperLook(TRUE);
	m_wndButton2.SetToolTip(TRUE);

	m_wndButton3.LoadBitmap(IDB_SUN, TRUE, RGB(255, 0, 255));
	m_wndButton3.SetTrackLook(TRUE);
	m_wndButton3.SetHyperLook(TRUE);
	m_wndButton3.SetToolTip(TRUE);
	m_wndButton3.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
	}

void CHyperDlg::OnPaint() 
	{
	CPaintDC dc(this);

	// First let the base class draw everyhting
	DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, NULL);

	// Then we draw the traffic light
	if (!m_space.IsEmpty())
		m_space.Paint(&dc, m_spaceRect, CRect(CPoint(0,0), m_spaceRect.Size()));
	}

BOOL CHyperDlg::OnQueryNewPalette() 
	{
	if (!m_space.IsEmpty())
		{
        CDC* pDC = GetDC();
        pDC->SelectPalette(m_space.GetPalette(), FALSE);
        UINT nEntries = pDC->RealizePalette();
        ReleaseDC(pDC);
        if (nEntries != 0) 
			{
            // Some colors changed, so we need to do a repaint.
            Invalidate();
			}
	    }

	return CDialog::OnQueryNewPalette();
	}

void CHyperDlg::OnPaletteChanged(CWnd* pFocusWnd) 
	{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	// ... Check whether the change was caused by us
    if (pFocusWnd != this) 
		// ... Realize our palette
        OnQueryNewPalette();
	}

void CHyperDlg::OnRButtonDown(UINT nFlags, CPoint point) 
	{
	m_wndButton1.RegrabBackground();
	
	CDialog::OnRButtonDown(nFlags, point);
	}

void CHyperDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
	{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// Realize the palette if we are the new foreground window
	// (This window may become the active window of the thread without
	//  being the foreground window)
	if ((((nState & WA_ACTIVE) == WA_ACTIVE) || ((nState & WA_CLICKACTIVE) == WA_CLICKACTIVE)) &&
		GetForegroundWindow() == this)
		{
		// ... Realize our palette when we have become active
		OnQueryNewPalette();
		}
	}

