// ColorSelectorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorSelector.h"
#include "ColorSelectorDlg.h"

#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CColorSelectorDlg dialog

CColorSelectorDlg::CColorSelectorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CColorSelectorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorSelectorDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorSelectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorSelectorDlg)
	DDX_Control(pDX, IDC_STATIC_SAMPLECOLOR, m_ctlSampleColor);
	DDX_Control(pDX, IDC_SLIDER_RED, m_ctlSlideRed);
	DDX_Control(pDX, IDC_SLIDER_LUM, m_ctlSlideLum);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_ctlSlideGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_ctlSlideBlue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorSelectorDlg, CDialog)
//{{AFX_MSG_MAP(CColorSelectorDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_VSCROLL()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON_COPYVALUE, OnBtnCopyValueToClipboard)
//}}AFX_MSG_MAP
ON_MESSAGE( UWM_SPECTRUMWINDOWEVENT, OnSpectrumWindowEvent )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelectorDlg message handlers

BOOL CColorSelectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	// set up slider controls and add buddy windows
	
	m_ctlSlideRed.SetRange( 0, 255 );
	m_ctlSlideRed.SetPos( 128 );
	m_ctlSlideRed.SetBuddy( GetDlgItem( IDC_EDIT_RED ) );
	m_ctlSlideRed.SetPrimaryColor( RGB(227,91,91) );	// reddish 
	m_ctlSlideRed.SetTicFreq( 16 );
	m_ctlSlideRed.SetPageSize( 32 );
	
	m_ctlSlideGreen.SetRange( 0, 255 );
	m_ctlSlideGreen.SetPos( 128 );
	m_ctlSlideGreen.SetBuddy( GetDlgItem( IDC_EDIT_GREEN ) );
	m_ctlSlideGreen.SetPrimaryColor( RGB(91,227,91 ) );	// greenish
	m_ctlSlideGreen.SetTicFreq( 16 );
	m_ctlSlideGreen.SetPageSize( 32 );
	
	m_ctlSlideBlue.SetRange( 0, 255 );
	m_ctlSlideBlue.SetPos( 128 );
	m_ctlSlideBlue.SetBuddy( GetDlgItem( IDC_EDIT_BLUE ) );
	m_ctlSlideBlue.SetPrimaryColor( RGB(91,91,227 ) );	// blue-ish 
	m_ctlSlideBlue.SetTicFreq( 16 );
	m_ctlSlideBlue.SetPageSize( 32 );
	
	m_ctlSlideLum.SetRange( 0, 240 );
	m_ctlSlideLum.SetPos( 120 );
	m_ctlSlideLum.SetBuddy( GetDlgItem( IDC_EDIT_LUM ) );
	m_ctlSlideLum.SetPrimaryColor( RGB(192,192,192) );	// dark gray
	m_ctlSlideLum.SetTicFreq( 12 );
	m_ctlSlideLum.SetPageSize( 24 );
	
	
	
	// get spectrum window created and displayed
	// the spectrum will make fine adjustments of its own
	// size in its OnCreate handler, so as to make the spectrum
	// fit perfectly within its client area
	
	CWnd* pPlaceholder = GetDlgItem( IDC_PLACEHOLDER );
	CRect rc;
	pPlaceholder->GetClientRect( &rc );
	pPlaceholder->MapWindowPoints( this, &rc );
	
	m_wndSpectrum.Create( NULL, "Spectrum", WS_CHILD|WS_VISIBLE, rc, this, 0x1245 );
	
	// close placeholder window since it's no longer needed, and
	// post a "fake" scroll message to initialize the spectrum's display
	
	pPlaceholder->SendMessage( WM_CLOSE );
	PostMessage( WM_VSCROLL, 0L, (WPARAM)m_ctlSlideRed.m_hWnd );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorSelectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorSelectorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorSelectorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CColorSelectorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( pScrollBar )
	{
		CBuddiedSliderCtrl* pSlider = (CBuddiedSliderCtrl*)pScrollBar;
		pSlider->ReflectedScrollMessage();
	}
	
	// check if WM_SCROLL came from the luminance slider or one of the RGB sliders
	// if it was luminance, then re-set the RGB sliders to newly-selected luminance
	// else set the luminance to a value corresponding to the newly-selected RGB
	
	int r = 255 - m_ctlSlideRed.GetPos();
	int g = 255 - m_ctlSlideGreen.GetPos();
	int b = 255 - m_ctlSlideBlue.GetPos();
	int lum = 240 - m_ctlSlideLum.GetPos();
	
	WORD H, L, S;
	
	COLORREF cr;
	
	if ( pScrollBar->m_hWnd == m_ctlSlideLum.m_hWnd )
	{
		ColorRGBToHLS( RGB(r, g, b), &H, &L, &S );
		L = lum;
		cr = ColorHLSToRGB( H, L, S );	// new color based on H & S of RGB sliders, and lum of L slider
		
		m_ctlSlideRed.SetPos( 255 - GetRValue( cr ) );
		m_ctlSlideGreen.SetPos( 255 - GetGValue( cr ) );
		m_ctlSlideBlue.SetPos( 255 - GetBValue( cr ) );
	}
	else
	{
		ColorRGBToHLS( RGB(r, g, b), &H, &L, &S );
		cr = RGB( r, g, b );
		m_ctlSlideLum.SetPos( 240-L );
	}
	
	
	// set values to spectrum window and invalidate it
	
	m_wndSpectrum.m_iLum = L;
	m_wndSpectrum.m_crTargetColor = cr;
	m_wndSpectrum.Invalidate();
	
	
	// set background brush for the sample patch and write the name of the 
	// color into it.  We don't paint it; we simply invalidate and wait for
	// WM_CTLCOLORSTATIC to give it its background brush
	
	if ( m_brSampleColor.m_hObject )
		m_brSampleColor.DeleteObject();
	
	m_brSampleColor.CreateSolidBrush( cr );
	
	CString str;
	str.Format(" Similar to %s ", m_wndSpectrum.GetNameOfClosestColor( cr ) );
	m_ctlSampleColor.SetWindowText( str );
	m_ctlSampleColor.Invalidate();
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

HBRUSH CColorSelectorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// set background brush for the color patch sample
	
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	
	if ( nCtlColor==CTLCOLOR_STATIC &&
		pWnd==&m_ctlSampleColor )
	{
		hbr = (HBRUSH)m_brSampleColor;
	}
	
	return hbr;
}

void CColorSelectorDlg::OnBtnCopyValueToClipboard() 
{
	// copies the current color in the static window to the clipboard,
	// in a format suitable for programming
	
	int r = 255 - m_ctlSlideRed.GetPos();
	int g = 255 - m_ctlSlideGreen.GetPos();
	int b = 255 - m_ctlSlideBlue.GetPos();
	COLORREF cr = RGB( r, g, b );
	COLORREF crNamed;
	
	CString strValue;
	CString name = m_wndSpectrum.GetNameOfClosestColor( cr, &crNamed );
	strValue.Format( "RGB( %d, %d, %d );\t// similar to %s (whose exact value is RGB( %d, %d, %d )); "
		"COLORREF value is 0x%08X; web value is #%02X%02X%02X",
		r, g, b, name, 
		GetRValue( crNamed ), GetGValue( crNamed ), GetBValue( crNamed ),
		cr, r, g, b );
	
	if ( ::OpenClipboard(this->m_hWnd) )
	{
		::EmptyClipboard();
		
		HGLOBAL hClipboardData;
		hClipboardData = ::GlobalAlloc(GMEM_DDESHARE, strValue.GetLength()+1);
		
		char * pchData;
		pchData = (char*)::GlobalLock(hClipboardData);
		
		strcpy(pchData, LPCTSTR(strValue));
		
		::GlobalUnlock(hClipboardData);
		
		::SetClipboardData(CF_TEXT, hClipboardData);
		
		::CloseClipboard();
	}
	
}

afx_msg LRESULT CColorSelectorDlg::OnSpectrumWindowEvent(WPARAM wParam, LPARAM lParam)
{
	// handler for our customized message sent/posted from the spectrum window.
	// Right now, there's only one meaning to the message, but other meanings could
	// be encoded in the wParam and lParam values.
	// wParam = SWE_NEWFOCUSCOLOR means to alert ourselves that the user has dragged 
	//			the focus outline to a new color
	
	switch ( wParam )
	{
	case SWE_NEWFOCUSCOLOR:
		{
			// new focus color selected by user, so re-set the sliders
			// and re-paint the spectrum window
			
			COLORREF& cr = m_wndSpectrum.m_crCurrentFocusColor;
			
			m_ctlSlideRed.SetPos( 255 - GetRValue( cr ) );
			m_ctlSlideGreen.SetPos( 255 - GetGValue( cr ) );
			m_ctlSlideBlue.SetPos( 255 - GetBValue( cr ) );
			
			SendMessage( WM_VSCROLL, 0L, (WPARAM)m_ctlSlideRed.m_hWnd );
		}
		break;
		
	default:
		ASSERT( FALSE );	// shouldn't get here
	}
	
	return TRUE;
}
