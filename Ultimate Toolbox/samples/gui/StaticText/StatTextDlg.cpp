// StatTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatText.h"
#include "StatTextDlg.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "AttrDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CStatTextDlg dialog

CStatTextDlg::CStatTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatTextDlg)
	m_nAngleValue = 0;
	m_nOrientValue = 0;
	m_nSpeedValue = 0;
	m_bScroll = FALSE;
	m_nDirValue = 0;
	m_nHorzAlignment = 1;
	m_nVertAlignment = 1;
	m_nBorderStyle = 4;
	m_nGraphicalMode = 0;
	m_nGapHeight = 0;
	m_nGapWidth = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStatTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatTextDlg)
	DDX_Control(pDX, IDC_STATIC_TEST, m_StaticText);
	DDX_Control(pDX, IDC_EDIT_GAP_WIDTH, m_ctlEditGapWidth);
	DDX_Control(pDX, IDC_EDIT_GAP_HEIGHT, m_ctlEditGapHeight);
	DDX_Control(pDX, IDC_SPIN_GAP_WIDTH, m_ctlSpinGapWidth);
	DDX_Control(pDX, IDC_SPIN_GAP_HEIGHT, m_ctlSpinGapHeight);
	DDX_Control(pDX, IDC_DIR_SPIN, m_DirSpin);
	DDX_Control(pDX, IDC_DIR_EDIT, m_DirEdit);
	DDX_Control(pDX, IDC_SPEED_SPIN, m_SpeedSpin);
	DDX_Control(pDX, IDC_SPEED_EDIT, m_SpeedEdit);
	DDX_Control(pDX, IDC_ORIENT_SPIN, m_OrientSpin);
	DDX_Control(pDX, IDC_ORIENT_EDIT, m_OrientEdit);
	DDX_Control(pDX, IDC_ANGLE_SPIN, m_AngleSpin);
	DDX_Control(pDX, IDC_ANGLE_EDIT, m_AngleEdit);
	DDX_Text(pDX, IDC_ANGLE_EDIT, m_nAngleValue);
	DDV_MinMaxInt(pDX, m_nAngleValue, -180, 180);
	DDX_Text(pDX, IDC_ORIENT_EDIT, m_nOrientValue);
	DDV_MinMaxInt(pDX, m_nOrientValue, -180, 180);
	DDX_Text(pDX, IDC_SPEED_EDIT, m_nSpeedValue);
	DDV_MinMaxInt(pDX, m_nSpeedValue, 0, 100);
	DDX_Check(pDX, IDC_SCROLL_CHECK, m_bScroll);
	DDX_Text(pDX, IDC_DIR_EDIT, m_nDirValue);
	DDV_MinMaxInt(pDX, m_nDirValue, -360, 360);
	DDX_Radio(pDX, IDC_RADIO_HORZ_LEFT, m_nHorzAlignment);
	DDX_Radio(pDX, IDC_RADIO_VERT_TOP, m_nVertAlignment);
	DDX_Radio(pDX, IDC_B_RAISED_RADIO, m_nBorderStyle);
	DDX_Radio(pDX, IDC_COMPAT_RADIO, m_nGraphicalMode);
	DDX_Text(pDX, IDC_EDIT_GAP_HEIGHT, m_nGapHeight);
	DDV_MinMaxInt(pDX, m_nGapHeight, 0, 100);
	DDX_Text(pDX, IDC_EDIT_GAP_WIDTH, m_nGapWidth);
	DDV_MinMaxInt(pDX, m_nGapWidth, 0, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatTextDlg, CDialog)
	//{{AFX_MSG_MAP(CStatTextDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ANGLE_EDIT, OnChangeAngleEdit)
	ON_EN_CHANGE(IDC_ORIENT_EDIT, OnChangeOrientEdit)
	ON_BN_CLICKED(IDC_ADVAN_RADIO, OnAdvanRadio)
	ON_BN_CLICKED(IDC_COMPAT_RADIO, OnCompatRadio)
	ON_EN_CHANGE(IDC_SPEED_EDIT, OnChangeSpeedEdit)
	ON_BN_CLICKED(IDC_SCROLL_CHECK, OnScrollCheck)
	ON_EN_CHANGE(IDC_DIR_EDIT, OnChangeDirEdit)
	ON_BN_CLICKED(IDC_ATTR_BUTTON, OnAttrButton)
	ON_BN_CLICKED(IDC_RESTORE_BUTTON, OnRestoreButton)
	ON_BN_CLICKED(IDC_B_RAISED_RADIO, OnBRaisedRadio)
	ON_BN_CLICKED(IDC_B_STATIC_RADIO, OnBStaticRadio)
	ON_BN_CLICKED(IDC_B_DOTTED_RADIO, OnBDottedRadio)
	ON_BN_CLICKED(IDC_B_NORMAL_RADIO, OnBNormalRadio)
	ON_BN_CLICKED(IDC_B_CLIENT_RADIO, OnBClientRadio)
	ON_BN_CLICKED(IDC_RADIO_HORZ_CENTER, OnRadioHorzCenter)
	ON_BN_CLICKED(IDC_RADIO_HORZ_LEFT, OnRadioHorzLeft)
	ON_BN_CLICKED(IDC_RADIO_HORZ_RIGHT, OnRadioHorzRight)
	ON_BN_CLICKED(IDC_RADIO_VERT_BOTTOM, OnRadioVertBottom)
	ON_BN_CLICKED(IDC_RADIO_VERT_CENTER, OnRadioVertCenter)
	ON_BN_CLICKED(IDC_RADIO_VERT_TOP, OnRadioVertTop)
	ON_EN_CHANGE(IDC_EDIT_GAP_HEIGHT, OnChangeEditGapHeight)
	ON_EN_CHANGE(IDC_EDIT_GAP_WIDTH, OnChangeEditGapWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatTextDlg message handlers

BOOL CStatTextDlg::OnInitDialog()
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

	// Set the Static Text window.
	LPTSTR	psText = _T("Static Text");
	int		/*nTextLeft = 10, nTextTop = 10,*/ nTextHeight = 30;
	m_StaticText.SetWindowText(psText);
	m_StaticText.SetTextColor(RGB(0, 0, 0));
	m_StaticText.SetBkColor(RGB(192, 192, 192));

	LOGFONT lf;
	if(m_StaticText.GetLogFont(&lf))
	{
		lf.lfHeight=nTextHeight;
		lf.lfWidth=0;
		lf.lfItalic=TRUE;
		lf.lfWeight=900;
		m_StaticText.SetLogFont(&lf);
	}
	m_StaticText.SetFontName(_T("Arial"));

	m_StaticText.SetEmboss();
	m_StaticText.SetClientEdge();
	m_StaticText.SetCharSet(ANSI_CHARSET,TRUE);

	// Set the String Angle (Escapement) spin.
	m_AngleSpin.SetBuddy(&m_AngleEdit);
	m_AngleSpin.SetRange(-180, 180);
	m_AngleSpin.SetPos(0);

	// Set the Character Angle (Orientation) spin.
	m_OrientSpin.SetBuddy(&m_OrientEdit);
	m_OrientSpin.SetRange(-180, 180);
	m_OrientSpin.SetPos(0);

	// Set the Speed spin.
	m_SpeedSpin.SetBuddy(&m_SpeedEdit);
	m_SpeedSpin.SetRange(0, 100);
	m_SpeedSpin.SetPos(0);

	// Set the Direction spin.
	m_DirSpin.SetBuddy(&m_DirEdit);
	m_DirSpin.SetRange(-360, 360);
	m_DirSpin.SetPos(0);

	// Set the GapSize spins.
	m_ctlSpinGapWidth.SetBuddy(&m_ctlEditGapWidth);
	m_ctlSpinGapWidth.SetRange(0, 100);
	m_ctlSpinGapWidth.SetPos(0);
	m_ctlSpinGapHeight.SetBuddy(&m_ctlEditGapHeight);
	m_ctlSpinGapHeight.SetRange(0, 100);
	m_ctlSpinGapHeight.SetPos(0);

	// Set other controls.
	CheckRadioButton(IDC_COMPAT_RADIO, IDC_ADVAN_RADIO, IDC_COMPAT_RADIO);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStatTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStatTextDlg::OnPaint() 
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
HCURSOR CStatTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStatTextDlg::OnChangeAngleEdit()
// Set the Escapement (string angle) value.
{
	if (!UpdateData(TRUE))
		return;
	m_StaticText.SetStringAngle(m_nAngleValue * 10, TRUE);
}

void CStatTextDlg::OnChangeOrientEdit()
// Set the Orientation (character angle) value.
{
	if (!UpdateData(TRUE))
		return;
	m_StaticText.SetCharAngle(m_nOrientValue * 10, TRUE);
}

void CStatTextDlg::OnChangeSpeedEdit()
// Set the Speed [of text scrolling] value.
{
	if (!UpdateData(TRUE))
		return;
	m_StaticText.SetScrollSpeed(m_nSpeedValue);
}

void CStatTextDlg::OnChangeDirEdit()
// Set the Direction [of text scrolling] value.
{
	if (!UpdateData(TRUE))
		return;

	m_StaticText.SetScrollDirection(m_nDirValue, TRUE);
}

void CStatTextDlg::OnAdvanRadio()
// Set graphics mode to "Advanced".
{
	m_StaticText.SetGraphicsMode(GM_ADVANCED, TRUE);
}

void CStatTextDlg::OnCompatRadio()
// Set graphics mode to "Compatible".
{
	m_StaticText.SetGraphicsMode(GM_COMPATIBLE, TRUE);
}

void CStatTextDlg::OnScrollCheck()
// Start/stop text scrolling.
{
	if (!UpdateData(TRUE))
		return;
	m_StaticText.StartScrolling(m_bScroll);
}

void CStatTextDlg::OnRestoreButton() 
// Restore scrolled text position.
{
	m_bScroll = FALSE;
	if (!UpdateData(TRUE))
		return;

	m_StaticText.StartScrolling(m_bScroll);
	m_StaticText.RestoreTextPos();
}

void CStatTextDlg::OnAttrButton()
// View the dialog box to set the text attributes.
{
	CAttrDialog dlgAttr;

	dlgAttr.m_sCaption = m_StaticText.GetText();
	dlgAttr.m_sFont = m_StaticText.GetFontName();
	dlgAttr.m_RedVal = GetRValue(m_StaticText.GetTextColor());
	dlgAttr.m_GreenVal = GetGValue(m_StaticText.GetTextColor());
	dlgAttr.m_BlueVal = GetBValue(m_StaticText.GetTextColor());
	dlgAttr.m_bkRedVal = GetRValue(m_StaticText.GetBkColor());
	dlgAttr.m_bkGreenVal = GetGValue(m_StaticText.GetBkColor());
	dlgAttr.m_bkBlueVal = GetBValue(m_StaticText.GetBkColor());
	dlgAttr.m_Height = m_StaticText.GetFontHeight();
	dlgAttr.m_Bold = m_StaticText.IsBold();
	dlgAttr.m_Italic = m_StaticText.IsItalic();
	dlgAttr.m_Under = m_StaticText.IsUnderlined();
	dlgAttr.m_Striked = m_StaticText.IsStrikedOut();
	dlgAttr.m_OffsetVal = m_StaticText.Get3Doffset();
	dlgAttr.m_nEllipseMode = m_StaticText.GetEllipseMode();
	dlgAttr.m_bEmboss = m_StaticText.GetEmboss();

	if ( dlgAttr.DoModal() == IDOK )
		{
		m_StaticText.SetWindowText(dlgAttr.m_sCaption);
	
		m_StaticText.SetTextColor(RGB(dlgAttr.m_RedVal, dlgAttr.m_GreenVal, dlgAttr.m_BlueVal));
		m_StaticText.SetBkColor(RGB(dlgAttr.m_bkRedVal, dlgAttr.m_bkGreenVal, dlgAttr.m_bkBlueVal));

		m_StaticText.SetFontName(dlgAttr.m_sFont);
		m_StaticText.SetFontHeight(dlgAttr.m_Height);
		m_StaticText.SetFontAttr(OX_BOLD_FONT, dlgAttr.m_Bold);
		m_StaticText.SetFontAttr(OX_ITALIC_FONT, dlgAttr.m_Italic);
		m_StaticText.SetFontAttr(OX_UNDERLINED_FONT, dlgAttr.m_Under);
		m_StaticText.SetFontAttr(OX_STRIKED_OUT_FONT, dlgAttr.m_Striked);

		m_StaticText.SetEllipseMode(dlgAttr.m_nEllipseMode);

		m_StaticText.Set3Doffset(dlgAttr.m_OffsetVal);
		m_StaticText.SetEmboss(dlgAttr.m_bEmboss, dlgAttr.m_bRaised, TRUE);
		}
}

void CStatTextDlg::OnBRaisedRadio() 
	{
	m_StaticText.SetRaisedEdge();
	}

void CStatTextDlg::OnBStaticRadio() 
	{
	m_StaticText.SetStaticEdge();
	}

void CStatTextDlg::OnBDottedRadio() 
	{
	m_StaticText.SetDottedEdge();
	}

void CStatTextDlg::OnBNormalRadio() 
	{
	m_StaticText.SetPlainBorder();
	}

void CStatTextDlg::OnBClientRadio() 
	{
	m_StaticText.SetClientEdge();
	}

void CStatTextDlg::OnRadioHorzCenter() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetHorzAlignment(OX_ALIGNHORZ_CENTER,TRUE);
}

void CStatTextDlg::OnRadioHorzLeft() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetHorzAlignment(OX_ALIGNHORZ_LEFT,TRUE);
}

void CStatTextDlg::OnRadioHorzRight() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetHorzAlignment(OX_ALIGNHORZ_RIGHT,TRUE);
}

void CStatTextDlg::OnRadioVertBottom() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetVertAlignment(OX_ALIGNVERT_BOTTOM,TRUE);
}

void CStatTextDlg::OnRadioVertCenter() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetVertAlignment(OX_ALIGNVERT_CENTER,TRUE);
}

void CStatTextDlg::OnRadioVertTop() 
{
	// TODO: Add your control notification handler code here
	m_StaticText.SetVertAlignment(OX_ALIGNVERT_TOP,TRUE);
}

void CStatTextDlg::OnChangeEditGapHeight() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		CSize szGapSize=m_StaticText.GetGapSize();
		szGapSize.cy=m_nGapHeight;
		m_StaticText.SetGapSize(szGapSize,TRUE);
	}
}

void CStatTextDlg::OnChangeEditGapWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		CSize szGapSize=m_StaticText.GetGapSize();
		szGapSize.cx=m_nGapWidth;
		m_StaticText.SetGapSize(szGapSize,TRUE);
	}

}
