
// BitmapButtonDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "BitmapButtonDemo.h"
#include "BitmapButtonDemoDlg.h"
#include "HyperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonDemoDlg dialog

CBitmapButtonDemoDlg::CBitmapButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapButtonDemoDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CBitmapButtonDemoDlg)
	m_bDisabled1 = FALSE;
	m_bTrackLook1 = FALSE;
	m_bTrackLook1x = TRUE;
	m_bAction1 = FALSE;
	m_nAlignment = -1;
	m_bAutoResize1 = TRUE;
	m_sText1 = _T("");
	m_bText1x = FALSE;
	m_sToolTipText1 = _T("");
	m_bToolTip = TRUE;
	m_bDisabled1X = FALSE;
	m_bPseudoDisable = FALSE;
	m_bHyperLook = FALSE;
	m_nStyle = -1;
	m_sHeader = _T("");
	m_bMultiline = FALSE;
	//}}AFX_DATA_INIT
	nState=0;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CBitmapButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapButtonDemoDlg)
	DDX_Control(pDX, IDCANCEL, m_wndButtonAnimated);
	DDX_Control(pDX, IDC_NEW, m_wndNew);
	DDX_Control(pDX, IDC_BUTTON_12, m_wndButton12);
	DDX_Control(pDX, IDC_BUTTON_11, m_wndButton11);
	DDX_Control(pDX, IDC_BUTTON_10, m_wndButton10);
	DDX_Control(pDX, IDC_BUTTON_1, m_wndButton1);
	DDX_Check(pDX, IDC_DISABLED_1, m_bDisabled1);
	DDX_Check(pDX, IDC_TRACK_LOOK_1, m_bTrackLook1);
	DDX_Check(pDX, IDC_TRACK_LOOK_1X, m_bTrackLook1x);
	DDX_Check(pDX, IDC_ACTION_1, m_bAction1);
	DDX_Radio(pDX, IDC_LEFT_TOP, m_nAlignment);
	DDX_Check(pDX, IDC_AUTO_RESIZE_1, m_bAutoResize1);
	DDX_Text(pDX, IDC_TEXT_1, m_sText1);
	DDX_Check(pDX, IDC_TEXT_1X, m_bText1x);
	DDX_Text(pDX, IDC_TOOLTIP_1, m_sToolTipText1);
	DDX_Check(pDX, IDC_TOOLTIP, m_bToolTip);
	DDX_Check(pDX, IDC_DISABLED_1X, m_bDisabled1X);
	DDX_Check(pDX, IDC_PSEUDO_DISABLE, m_bPseudoDisable);
	DDX_Check(pDX, IDC_HYPER_LOOK, m_bHyperLook);
	DDX_Radio(pDX, IDC_RADIO_NORMAL, m_nStyle);
	DDX_Text(pDX, IDC_STATIC_HEADER, m_sHeader);
	DDX_Check(pDX, IDC_MULTILINE, m_bMultiline);
	//}}AFX_DATA_MAP
	DDX_Toggle(pDX, IDC_BUTTON_1, nState);
	}

BEGIN_MESSAGE_MAP(CBitmapButtonDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CBitmapButtonDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DISABLED_1, OnDisabled1)
	ON_BN_CLICKED(IDC_TRACK_LOOK_1X, OnTrackLook1x)
	ON_BN_CLICKED(IDC_TRACK_LOOK_1, OnTrackLook1)
	ON_WM_PALETTECHANGED()
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_LEFT_BOTTOM, OnAlignment)
	ON_BN_CLICKED(IDC_AUTO_RESIZE_1, OnAutoResize1)
	ON_BN_CLICKED(IDC_SET_TEXT, OnSetText)
	ON_BN_CLICKED(IDC_TEXT_1X, OnText1x)
	ON_BN_CLICKED(IDC_FONT_1, OnFont1)
	ON_BN_CLICKED(IDC_SET_TOOLTIP, OnSetTooltip)
	ON_BN_CLICKED(IDC_TOOLTIP, OnTooltip)
	ON_BN_CLICKED(IDC_DISABLED_1X, OnDisabled1x)
	ON_BN_CLICKED(IDC_HYPER, OnHyper)
	ON_BN_CLICKED(IDC_PSEUDO_DISABLE, OnPseudoDisable)
	ON_BN_CLICKED(IDC_HYPER_LOOK, OnHyperLook)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, OnRadioNormal)
	ON_BN_CLICKED(IDC_RADIO_DROPDOWN, OnRadioDropdown)
	ON_BN_CLICKED(IDC_RADIO_RIGHTDROPDOWN, OnRadioRightdropdown)
	ON_BN_CLICKED(IDC_RADIO_TOGGLE, OnRadioToggle)
	ON_BN_CLICKED(IDC_RADIO_NOARROWDROPDOWN, OnRadioNoarrowdropdown)
	ON_BN_CLICKED(IDC_RADIO_TOGGLETHREESTATE, OnRadioTogglethreestate)
	ON_BN_CLICKED(IDC_ACTION_1, OnAction1)
	ON_BN_CLICKED(IDC_LEFT_TOP, OnAlignment)
	ON_BN_CLICKED(IDC_LEFT_VCENTER, OnAlignment)
	ON_BN_CLICKED(IDC_RIGHT_BOTTOM, OnAlignment)
	ON_BN_CLICKED(IDC_RIGHT_TOP, OnAlignment)
	ON_BN_CLICKED(IDC_RIGHT_VCENTER, OnAlignment)
	ON_BN_CLICKED(IDC_CENTER_BOTTOM, OnAlignment)
	ON_BN_CLICKED(IDC_CENTER_TOP, OnAlignment)
	ON_BN_CLICKED(IDC_CENTER_VCENTER, OnAlignment)
	ON_BN_CLICKED(IDC_MULTILINE, OnMultiline)
	//}}AFX_MSG_MAP
	ON_NOTIFY(OXBBN_DROPDOWN,IDC_BUTTON_1,OnDropDownButton1)
	ON_NOTIFY(OXBBN_TOGGLE,IDC_BUTTON_1,OnToggleButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonDemoDlg message handlers

BOOL CBitmapButtonDemoDlg::OnInitDialog()
	{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
		{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
// Set button resources
	m_originalSize1 = m_wndButton1.GetButtonSize();
//	m_wndButton1.SetInnerFocusOffset(CPoint(-4,-2));
	VERIFY(m_wndButton1.LoadBitmap(IDB_SUN, m_bAutoResize1, RGB(255,0,255)));
//	VERIFY(m_wndButton1.LoadIcon(IDI_TOOL_ICON_2, m_bAutoResize1,16,16));
	m_wndButton1.SetText(_T("&Bitmap Button"));
	m_wndButton1.SetVerticalAlignment(BS_VCENTER);
	m_wndButton1.SetHorizontalAlignment(BS_LEFT);
	m_nAlignment = 3;
	nState=1;
//	m_wndButton1.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNRIGHT);
	m_wndButton1.SetStyleEx(OXBB_EX_TOGGLE|OXBB_EX_TOGGLE3STATE);
	m_nStyle = 5;
	m_bMultiline = (m_wndButton1.GetStyle()&BS_MULTILINE)==BS_MULTILINE;
	if(m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_sText1 = m_wndButton1.GetText();
	m_sToolTipText1 = m_wndButton1.GetToolTipText();
	m_sHeader=_T("Owner Draw");

	VERIFY(m_wndButton10.LoadBitmap(IDB_TOOL_BITMAP_1, TRUE, RGB(255, 0, 255)));
	VERIFY(m_wndButton11.LoadIcon(IDI_TOOL_ICON_2, TRUE));
	VERIFY(m_wndButton12.LoadBitmap(IDB_TOOL_BITMAP_3, TRUE, RGB(255, 0, 255)));

	m_wndButton10.SetToolTip(TRUE);
	m_wndButton11.SetToolTip(TRUE);
	m_wndButton12.SetToolTip(TRUE);
	m_wndButton1.SetToolTip(TRUE);


	m_wndButtonAnimated.LoadAvi(IDR_AVI_TEST);
	m_wndButtonAnimated.SetToolTip(TRUE);
//	m_wndButtonAnimated.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNRIGHT);
//	m_wndButtonAnimated.SetText(_T("Animated"));
	m_wndButtonAnimated.SizeToContent();

	// Set row of buttons next to each other
	PositionButtonRow();

	m_wndButton10.SetTrackLook(TRUE);
	m_wndButton11.SetTrackLook(TRUE);
	m_wndButton12.SetTrackLook(TRUE);
	m_wndButton1.SetTrackLook(TRUE);

	CFont* pFont = m_wndNew.GetFont();
	if (pFont != NULL)
		{
		LOGFONT logFont;
		::ZeroMemory(&logFont, sizeof(logFont));
		pFont->GetLogFont(&logFont);
		logFont.lfHeight = (logFont.lfHeight * 3) / 2;
		logFont.lfWidth = 0;
		// ... Bold
		logFont.lfWeight = 700; 
		logFont.lfItalic = TRUE;
		m_largeFont.CreateFontIndirect(&logFont);
		m_wndNew.SetFont(&m_largeFont);
		}

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
	}

void CBitmapButtonDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
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

void CBitmapButtonDemoDlg::OnPaint() 
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
HCURSOR CBitmapButtonDemoDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CBitmapButtonDemoDlg::OnDisabled1() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.EnableWindow(!m_bDisabled1);
	}

void CBitmapButtonDemoDlg::OnTrackLook1x() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton10.SetTrackLook(m_bTrackLook1x);
	m_wndButton11.SetTrackLook(m_bTrackLook1x);
	m_wndButton12.SetTrackLook(m_bTrackLook1x);
	}

void CBitmapButtonDemoDlg::OnTrackLook1() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetTrackLook(m_bTrackLook1);
	}

void CBitmapButtonDemoDlg::OnPaletteChanged(CWnd* pFocusWnd) 
	{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	}


void CBitmapButtonDemoDlg::OnButton1() 
	{
	if (!UpdateData(TRUE))
		return;

	if (m_bAction1 && !m_wndButton1.IsToggleButton() && !m_wndButton1.IsDropDownButton())
		AfxMessageBox(IDS_ACTION_1, MB_ICONINFORMATION | MB_OK);

	UpdateData(FALSE);

	}

void CBitmapButtonDemoDlg::OnAlignment() 
	{
	if (!UpdateData(TRUE))
		return;

	DWORD nHorizontalAlignment = (DWORD)-1;
	DWORD nVerticalAlignment = (DWORD)-1;

	if ((m_nAlignment == 0) || (m_nAlignment == 1) || (m_nAlignment == 2))
		nVerticalAlignment = BS_TOP;
	if ((m_nAlignment == 3) || (m_nAlignment == 4) || (m_nAlignment == 5))
		nVerticalAlignment = BS_VCENTER;
	if ((m_nAlignment == 6) || (m_nAlignment == 7) || (m_nAlignment == 8))
		nVerticalAlignment = BS_BOTTOM;

	if ((m_nAlignment == 0) || (m_nAlignment == 3) || (m_nAlignment == 6))
		nHorizontalAlignment = BS_LEFT;
	if ((m_nAlignment == 1) || (m_nAlignment == 4) || (m_nAlignment == 7))
		nHorizontalAlignment = BS_CENTER;
	if ((m_nAlignment == 2) || (m_nAlignment == 5) || (m_nAlignment == 8))
		nHorizontalAlignment = BS_RIGHT;

	ASSERT(nHorizontalAlignment != (DWORD)-1);
	ASSERT(nVerticalAlignment != (DWORD)-1);

	DWORD nOldVerticalAlignment=m_wndButton1.GetVerticalAlignment();

	m_wndButton1.SetVerticalAlignment(nVerticalAlignment);
	m_wndButton1.SetHorizontalAlignment(nHorizontalAlignment);

	if(m_bAutoResize1 && (nOldVerticalAlignment==BS_VCENTER || 
		nVerticalAlignment==BS_VCENTER))
		{
		m_wndButton1.SizeToContent();
		}
	}

void CBitmapButtonDemoDlg::OnAutoResize1() 
	{
	if (!UpdateData(TRUE))
		return;

	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	else
		{
		// ... Get old position
		CRect rect;
		m_wndButton1.GetWindowRect(rect);
		ScreenToClient(rect);
		// ... Move
		m_wndButton1.SetWindowPos(NULL, -1, -1, m_originalSize1.cx, m_originalSize1.cy,
			SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE);
		// ... Invalidate old and new position
		InvalidateRect(rect);
		m_wndButton1.Invalidate();
		}
	}

void CBitmapButtonDemoDlg::OnSetText() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetText(m_sText1);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	}

void CBitmapButtonDemoDlg::OnText1x() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton10.SetText(m_bText1x ? _T("&One") : _T(""));
	m_wndButton11.SetText(m_bText1x ? _T("&Two") : _T(""));
	m_wndButton12.SetText(m_bText1x ? _T("T&hree") : _T(""));

	PositionButtonRow();
	}

void CBitmapButtonDemoDlg::PositionButtonRow()
	{
	// First resize them
	m_wndButton10.SizeToContent();
	m_wndButton11.SizeToContent();
	m_wndButton12.SizeToContent();

	CRect rect;
	CSize size;
	CSize largestSize(0, 0);

	m_wndButton10.GetWindowRect(rect);
	largestSize = rect.Size();
	
	m_wndButton11.GetWindowRect(rect);
	size = rect.Size();
	if (largestSize.cx < size.cx)
		largestSize.cx = size.cx;
	if (largestSize.cy < size.cy)
		largestSize.cy = size.cy;

	m_wndButton12.GetWindowRect(rect);
	size = rect.Size();
	if (largestSize.cx < size.cx)
		largestSize.cx = size.cx;
	if (largestSize.cy < size.cy)
		largestSize.cy = size.cy;


	// The reposition them (next to each other)
	CRect firstRect;
	CRect secondRect;

	m_wndButton10.GetWindowRect(secondRect);
	ScreenToClient(secondRect);
	secondRect.right = secondRect.left + largestSize.cx;
	secondRect.bottom = secondRect.top + largestSize.cy;
	m_wndButton10.MoveWindow(secondRect);

	m_wndButton10.GetWindowRect(firstRect);
	m_wndButton11.GetWindowRect(secondRect);
	secondRect = secondRect - CPoint(secondRect.left - firstRect.right, secondRect.top - firstRect.top);
	ScreenToClient(secondRect);
	secondRect.right = secondRect.left + largestSize.cx;
	secondRect.bottom = secondRect.top + largestSize.cy;
	m_wndButton11.MoveWindow(secondRect);

	m_wndButton11.GetWindowRect(firstRect);
	m_wndButton12.GetWindowRect(secondRect);
	secondRect = secondRect - CPoint(secondRect.left - firstRect.right, secondRect.top - firstRect.top);
	ScreenToClient(secondRect);
	secondRect.right = secondRect.left + largestSize.cx;
	secondRect.bottom = secondRect.top + largestSize.cy;
	m_wndButton12.MoveWindow(secondRect);
	}


void CBitmapButtonDemoDlg::OnFont1() 
	{
	CFont* pTextFont = m_wndButton1.GetFont();
	ASSERT(pTextFont != NULL);
	LOGFONT logFont;
	pTextFont->GetLogFont(&logFont);

	CFontDialog fontDlg(&logFont);
	fontDlg.m_cf.rgbColors = m_wndButton1.GetTextColor();
	if (fontDlg.DoModal() == IDOK)
		{
		CFont newTextFont;
		// ... CFontDialog::GetCurrentFont() ASSERTs without reason if m_hWnd == NULL,
		//	   so we use m_cf.lpLogFont directly
		VERIFY(newTextFont.CreateFontIndirect(fontDlg.m_cf.lpLogFont));
		// ... SetTextFont() will keep a copy
		m_wndButton1.SetTextFont(&newTextFont);
		m_wndButton1.SetTextColor(fontDlg.GetColor());

		if (m_bAutoResize1)
			m_wndButton1.SizeToContent();
		}
	}

void CBitmapButtonDemoDlg::OnSetTooltip() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetToolTipText(m_sToolTipText1);
	}

void CBitmapButtonDemoDlg::OnTooltip() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetToolTip(m_bToolTip);
	}

void CBitmapButtonDemoDlg::OnDisabled1x() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton10.EnableWindow(!m_bDisabled1X);
	m_wndButton11.EnableWindow(!m_bDisabled1X);
	m_wndButton12.EnableWindow(!m_bDisabled1X);
	}

void CBitmapButtonDemoDlg::OnHyper() 
	{
	CHyperDlg dlg;
	dlg.DoModal();
	}

void CBitmapButtonDemoDlg::OnPseudoDisable() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetPseudoDisableMode(m_bPseudoDisable);
	}

void CBitmapButtonDemoDlg::OnHyperLook() 
	{
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetHyperLook(m_bHyperLook);
	m_bPseudoDisable = m_wndButton1.GetPseudoDisableMode();
	UpdateData(FALSE);
	}

void CBitmapButtonDemoDlg::OnRadioNormal() 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(0);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnRadioDropdown() 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(OXBB_EX_DROPDOWN);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnRadioRightdropdown() 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNRIGHT);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnRadioToggle() 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(OXBB_EX_TOGGLE);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnRadioNoarrowdropdown() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNNOARROW);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnRadioTogglethreestate() 
{
	// TODO: Add your control notification handler code here
	if (!UpdateData(TRUE))
		return;

	m_wndButton1.SetStyleEx(OXBB_EX_TOGGLE|OXBB_EX_TOGGLE3STATE);
	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	m_wndButton1.SetStateEx(m_wndButton1.GetStateEx()&
		~(OXBB_STATE_CHECKED|OXBB_STATE_INDETERMINATE));
	m_wndButton1.RedrawWindow();
	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnDropDownButton1(NMHDR * pNotifyStruct, LRESULT * result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if (m_bAction1)
		AfxMessageBox(IDS_ACTION_1, MB_ICONINFORMATION | MB_OK);

	*result=0;
}

void CBitmapButtonDemoDlg::OnToggleButton1(NMHDR * pNotifyStruct, LRESULT * result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if (!UpdateData(TRUE))
		return;

	if (m_bAction1)
	{
		if(nState==2)
		{
			m_sHeader=_T("Owner Draw - Indeterminate");
		}
		else if(nState==1)
		{
			m_sHeader=_T("Owner Draw - On");
		}
		else if(nState==0)
		{
			m_sHeader=_T("Owner Draw - Off");
		}
		else
		{
			m_sHeader=_T("Owner Draw");
		}
	}

	UpdateData(FALSE);


	*result=0;
}

void CBitmapButtonDemoDlg::OnAction1() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	m_sHeader=_T("Owner Draw");
	UpdateData(FALSE);
}

void CBitmapButtonDemoDlg::OnMultiline() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	if(m_bMultiline)
		m_wndButton1.ModifyStyle(0,BS_MULTILINE);
	else
		m_wndButton1.ModifyStyle(BS_MULTILINE,0);

	if (m_bAutoResize1)
		m_wndButton1.SizeToContent();
	else
		m_wndButton1.Invalidate();
}

