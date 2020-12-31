// DateTimePickerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DateTimePicker.h"
#include "DateTimePickerDlg.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateTimePickerDlg dialog

CDateTimePickerDlg::CDateTimePickerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDateTimePickerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateTimePickerDlg)
	m_nFirstDay = -1;
	m_nDimension = -1;
	m_nScrollRate = 0;
	m_bCanParse = FALSE;
	m_bShowNone = FALSE;
	m_bUpDown = FALSE;
	m_nFormat = -1;
	m_bRightAlign = FALSE;
	m_bNotoday = FALSE;
	m_bNotodaycircle = FALSE;
	m_bWeeknumbers = FALSE;
	m_sMonthCalFontName = _T("");
	m_nDateFormat = -1;
	m_nTimeFormat = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_clrTrailingText=RGB(0,0,0);
	m_clrTitleText=RGB(0,0,0);
	m_clrTitleBk=RGB(0,0,0);
	m_clrText=RGB(0,0,0);
	m_clrMonthBk=RGB(0,0,0);
	m_clrBk=RGB(0,0,0);
}

void CDateTimePickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateTimePickerDlg)
	DDX_Control(pDX, IDC_COMBO_TIMEFORMAT, m_cmbTimeFormat);
	DDX_Control(pDX, IDC_COMBO_DATEFORMAT, m_cmbDateFormat);
	DDX_Control(pDX, IDC_STATIC_CALFONT, m_ctlMonthCalFontName);
	DDX_Control(pDX, IDC_COMBO_FIRSTDAY, m_cmbFirstDay);
	DDX_Control(pDX, IDC_COMBO_DIMENSION, m_cmbDimension);
	DDX_Control(pDX, IDC_BUTTON_CLRTRAILINGTEXT, m_btnClrTrailingText);
	DDX_Control(pDX, IDC_BUTTON_CLRTITLETEXT, m_btnClrTitleText);
	DDX_Control(pDX, IDC_BUTTON_CLRTITLEBK, m_btnClrTitleBk);
	DDX_Control(pDX, IDC_BUTTON_CLRTEXT, m_btnClrText);
	DDX_Control(pDX, IDC_BUTTON_CLRMONTHBK, m_btnClrMonthBk);
	DDX_Control(pDX, IDC_BUTTON_CLRBK, m_btnClrBk);
	DDX_CBIndex(pDX, IDC_COMBO_FIRSTDAY, m_nFirstDay);
	DDX_CBIndex(pDX, IDC_COMBO_DIMENSION, m_nDimension);
	DDX_Text(pDX, IDC_EDIT_SCROLLRATE, m_nScrollRate);
	DDX_Check(pDX, IDC_CHECK_CANPARSE, m_bCanParse);
	DDX_Check(pDX, IDC_CHECK_SHOWNONE, m_bShowNone);
	DDX_Check(pDX, IDC_CHECK_UPDOWN, m_bUpDown);
	DDX_Radio(pDX, IDC_RADIO_TIMEFORMAT, m_nFormat);
	DDX_Check(pDX, IDC_CHECK_RIGHTALIGN, m_bRightAlign);
	DDX_Check(pDX, IDC_CHECK_NOTODAY, m_bNotoday);
	DDX_Check(pDX, IDC_CHECK_NOTODAYCIRCLE, m_bNotodaycircle);
	DDX_Check(pDX, IDC_CHECK_WEEKNUMBERS, m_bWeeknumbers);
	DDX_Text(pDX, IDC_STATIC_CALFONT, m_sMonthCalFontName);
	DDX_CBIndex(pDX, IDC_COMBO_DATEFORMAT, m_nDateFormat);
	DDX_CBIndex(pDX, IDC_COMBO_TIMEFORMAT, m_nTimeFormat);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTRAILINGTEXT, m_clrTrailingText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTITLETEXT, m_clrTitleText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTITLEBK, m_clrTitleBk);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTEXT, m_clrText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRMONTHBK, m_clrMonthBk);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRBK, m_clrBk);
}

BEGIN_MESSAGE_MAP(CDateTimePickerDlg, CDialog)
	//{{AFX_MSG_MAP(CDateTimePickerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CANPARSE, OnCheckCanparse)
	ON_BN_CLICKED(IDC_CHECK_SHOWNONE, OnCheckShownone)
	ON_BN_CLICKED(IDC_CHECK_UPDOWN, OnCheckUpdown)
	ON_BN_CLICKED(IDC_RADIO_LONGDATEFORMAT, OnRadioFormat)
	ON_BN_CLICKED(IDC_CHECK_RIGHTALIGN, OnCheckRightalign)
	ON_BN_CLICKED(IDC_BUTTON_CALFONT, OnButtonCalfont)
	ON_CBN_SELCHANGE(IDC_COMBO_DATEFORMAT, OnSelchangeComboDateformat)
	ON_BN_CLICKED(IDC_RADIO_SHORTDATEFORMAT, OnRadioFormat)
	ON_BN_CLICKED(IDC_RADIO_TIMEFORMAT, OnRadioFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMEFORMAT, OnSelchangeComboTimeformat)
	//}}AFX_MSG_MAP
	ON_NOTIFY(DTN_DROPDOWN ,IDC_DATETIMEPICKER, OnDTDropDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimePickerDlg message handlers

BOOL CDateTimePickerDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	// populate combo boxes
	//
	m_cmbDimension.AddString(_T("One month"));
	m_cmbDimension.AddString(_T("2x1 months"));
	m_cmbDimension.AddString(_T("1x2 months"));
	m_cmbDimension.AddString(_T("2x2 months"));

	m_nDimension=0;


	m_cmbFirstDay.AddString(_T("Monday"));
	m_cmbFirstDay.AddString(_T("Tuesday"));
	m_cmbFirstDay.AddString(_T("Wednesday"));
	m_cmbFirstDay.AddString(_T("Thursday"));
	m_cmbFirstDay.AddString(_T("Friday"));
	m_cmbFirstDay.AddString(_T("Saturday"));
	m_cmbFirstDay.AddString(_T("Sunday"));

	m_nFirstDay=6;

	m_cmbDateFormat.AddString(_T("Default"));
	m_cmbDateFormat.AddString(_T("ddd''d' 'MMM' 'yy"));
	m_cmbDateFormat.AddString(_T("dddd' 'dd' 'MMMM' 'yyy"));
	m_cmbDateFormat.AddString(_T("MM'/'dd'/'yyy' 'hh':'mm' 'tt"));

	m_nDateFormat=0;

	m_cmbTimeFormat.AddString(_T("Default"));
	m_cmbTimeFormat.AddString(_T("h':'m' 't"));
	m_cmbTimeFormat.AddString(_T("HH':'mm"));
	m_cmbTimeFormat.AddString(_T("hh':'mm' 'tt' 'MM'/'dd'/'yyy"));

	m_nTimeFormat=0;
	/////////////////////////////

	// month calendar settings
	//
	m_nScrollRate=1;
	m_bNotoday = FALSE;
	m_bNotodaycircle = FALSE;
	m_bWeeknumbers = FALSE;
	/////////////////////////////

	// enable tooltips for color picker buttons
	//
	m_btnClrTrailingText.SetToolTip(TRUE);
	m_btnClrTitleText.SetToolTip(TRUE);
	m_btnClrTitleBk.SetToolTip(TRUE);
	m_btnClrText.SetToolTip(TRUE);
	m_btnClrMonthBk.SetToolTip(TRUE);
	m_btnClrBk.SetToolTip(TRUE);
	/////////////////////////////

	// create date time picker control
	//
	CWnd *pFrame=GetDlgItem(IDC_DATETIMEPICKER);
	CRect rcWnd;
	pFrame->GetWindowRect(rcWnd);
	DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_TABSTOP;
	pFrame->DestroyWindow(); //pFrame was just a placeholder anyway.
	ScreenToClient(rcWnd);
	VERIFY(m_ctlDateTimePicker.Create(dwStyle,rcWnd,this,IDC_DATETIMEPICKER));

	GetVars();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDateTimePickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDateTimePickerDlg::OnPaint() 
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
HCURSOR CDateTimePickerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDateTimePickerDlg::GetVars()
{
	DWORD dwStyle=m_ctlDateTimePicker.GetStyle();

	m_bCanParse=(dwStyle&DTS_APPCANPARSE)!=0 ? TRUE : FALSE;
	m_bShowNone=(dwStyle&DTS_SHOWNONE)!=0 ? TRUE : FALSE;
	m_bUpDown=(dwStyle&DTS_UPDOWN)!=0 ? TRUE : FALSE;
	m_bRightAlign=(dwStyle&DTS_RIGHTALIGN)!=0 ? TRUE : FALSE;

	if((dwStyle&DTS_TIMEFORMAT)!=0)
		m_nFormat=0;
	else if((dwStyle&DTS_SHORTDATEFORMAT)!=0)
		m_nFormat=1;
	else if((dwStyle&DTS_LONGDATEFORMAT)!=0)
		m_nFormat=2;
	else
		m_nFormat=1;

	m_clrTrailingText=m_ctlDateTimePicker.GetMonthCalColor(MCSC_TRAILINGTEXT);
	m_clrTitleText=m_ctlDateTimePicker.GetMonthCalColor(MCSC_TITLETEXT);
	m_clrTitleBk=m_ctlDateTimePicker.GetMonthCalColor(MCSC_TITLEBK);
	m_clrText=m_ctlDateTimePicker.GetMonthCalColor(MCSC_TEXT);
	m_clrMonthBk=m_ctlDateTimePicker.GetMonthCalColor(MCSC_MONTHBK);
	m_clrBk=m_ctlDateTimePicker.GetMonthCalColor(MCSC_BACKGROUND);

	// font
	//
	CFont* pFont=m_ctlDateTimePicker.GetMonthCalFont();
	if(pFont==NULL)
		pFont=m_ctlDateTimePicker.GetFont();
	VERIFY(pFont->GetLogFont(&m_lfMonthCal));

	m_sMonthCalFontName.Format(_T("%d pt, %s"),
		(ConvertLogUnitToPoint(m_lfMonthCal.lfHeight)+5)/10,
		m_lfMonthCal.lfFaceName);
	m_ctlMonthCalFontName.SetTextLogFont(&m_lfMonthCal);
	m_ctlMonthCalFontName.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	/////////////////////////////

	VERIFY(UpdateData(FALSE));
}


void CDateTimePickerDlg::SetMonthCalColors()
{
	if(!UpdateData(TRUE))
		return;

	m_ctlDateTimePicker.SetMonthCalColor(MCSC_TRAILINGTEXT,m_clrTrailingText);
	m_ctlDateTimePicker.SetMonthCalColor(MCSC_TITLETEXT,m_clrTitleText);
	m_ctlDateTimePicker.SetMonthCalColor(MCSC_TITLEBK,m_clrTitleBk);
	m_ctlDateTimePicker.SetMonthCalColor(MCSC_TEXT,m_clrText);
	m_ctlDateTimePicker.SetMonthCalColor(MCSC_MONTHBK,m_clrMonthBk);
	m_ctlDateTimePicker.SetMonthCalColor(MCSC_BACKGROUND,m_clrBk);
}


void CDateTimePickerDlg::OnCheckCanparse() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_bCanParse)
		RecreateDateTimePicker(DTS_APPCANPARSE,0);
	else
		RecreateDateTimePicker(0,DTS_APPCANPARSE);

}

void CDateTimePickerDlg::OnCheckShownone() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_bShowNone)
		RecreateDateTimePicker(DTS_SHOWNONE,0);
	else
		RecreateDateTimePicker(0,DTS_SHOWNONE);
}

void CDateTimePickerDlg::OnCheckUpdown() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_bUpDown)
		RecreateDateTimePicker(DTS_UPDOWN,0);
	else
		RecreateDateTimePicker(0,DTS_UPDOWN);
}

void CDateTimePickerDlg::OnCheckRightalign() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_bRightAlign)
		m_ctlDateTimePicker.ModifyStyle(0,DTS_RIGHTALIGN,SWP_NOSIZE);
	else
		m_ctlDateTimePicker.ModifyStyle(DTS_RIGHTALIGN,0);
}

void CDateTimePickerDlg::OnRadioFormat() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	DWORD dwAddStyle=0;
	DWORD dwRemoveStyle=0;

	switch(m_nFormat)
	{
	case 0:
		dwAddStyle=DTS_TIMEFORMAT;
		dwRemoveStyle=DTS_SHORTDATEFORMAT|DTS_LONGDATEFORMAT;
		break;
	case 1:
		dwAddStyle=DTS_SHORTDATEFORMAT;
		dwRemoveStyle=DTS_TIMEFORMAT|DTS_LONGDATEFORMAT;
		break;
	case 2:
		dwAddStyle=DTS_LONGDATEFORMAT;
		dwRemoveStyle=DTS_SHORTDATEFORMAT|DTS_TIMEFORMAT;
		break;
	}
	
	//remove previous format style
	m_ctlDateTimePicker.ModifyStyle(dwRemoveStyle,0);
	//set this style
	m_ctlDateTimePicker.ModifyStyle(0,dwAddStyle,SWP_NOSIZE);

	if(m_nFormat!=0)
		SetDateFormat();
	else
		SetTimeFormat();
}

BOOL CDateTimePickerDlg::RecreateDateTimePicker(DWORD dwAddStyle, DWORD dwRemoveStyle)
{
	CRect rc;
	m_ctlDateTimePicker.GetWindowRect(rc);
	long lStyle = ::GetWindowLong(m_ctlDateTimePicker.m_hWnd,GWL_STYLE);
	lStyle |= dwAddStyle;
	lStyle &= ~dwRemoveStyle;
	m_ctlDateTimePicker.DestroyWindow();
	ScreenToClient(rc);
	
	if(m_ctlDateTimePicker.Create(lStyle,rc,this,IDC_DATETIMEPICKER))
	{
		if(m_nFormat!=0)
			SetDateFormat();
		else
			SetTimeFormat();
		return TRUE;
	}
	else
		return FALSE;
}

void CDateTimePickerDlg::OnDTDropDown(NMHDR *pHdr, LRESULT *pRes)
{
	UNREFERENCED_PARAMETER(pHdr);

	VERIFY(UpdateData(TRUE));

	SetMonthCalColors();

	static CFont font;
	if((HFONT)font!=NULL)
		font.DeleteObject();
	VERIFY(font.CreateFontIndirect(&m_lfMonthCal));
	m_ctlDateTimePicker.SetMonthCalFont(&font,FALSE);

	COXMonthCalCtrl* pCtlMonthCal=m_ctlDateTimePicker.GetMonthCalCtrl();
	ASSERT(pCtlMonthCal);

	if(m_bNotoday)
		pCtlMonthCal->ModifyStyle(0,MCS_NOTODAY);
	else
		pCtlMonthCal->ModifyStyle(MCS_NOTODAY,0);
#if (_WIN32_IE >= 0x0400)
	if(m_bNotodaycircle)
		pCtlMonthCal->ModifyStyle(0,MCS_NOTODAYCIRCLE);
	else
		pCtlMonthCal->ModifyStyle(MCS_NOTODAYCIRCLE,0);
#endif
	if(m_bWeeknumbers)
		pCtlMonthCal->ModifyStyle(0,MCS_WEEKNUMBERS);
	else
		pCtlMonthCal->ModifyStyle(MCS_WEEKNUMBERS,0);

	pCtlMonthCal->SetMonthDelta(m_nScrollRate);
	pCtlMonthCal->SetFirstDayOfWeek(m_nFirstDay);

	switch(m_nDimension)
	{
	case 0:
		pCtlMonthCal->SetCtrlDimension(1,1);
		break;
	case 1:
		pCtlMonthCal->SetCtrlDimension(2,1);
		break;
	case 2:
		pCtlMonthCal->SetCtrlDimension(1,2);
		break;
	case 3:
		pCtlMonthCal->SetCtrlDimension(2,2);
		break;
	default:
		ASSERT(FALSE);
	}

	pCtlMonthCal->EnableToolTips(TRUE);

	*pRes=0;
}



void CDateTimePickerDlg::OnButtonCalfont() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	// Use font common dialog
	CFontDialog fontDlg(&m_lfMonthCal);
	if(fontDlg.DoModal()==IDOK)
	{
		fontDlg.GetCurrentFont(&m_lfMonthCal);
		m_sMonthCalFontName.Format(_T("%d pt, %s"),(fontDlg.GetSize()+5)/10,
			m_lfMonthCal.lfFaceName);
		m_ctlMonthCalFontName.SetTextLogFont(&m_lfMonthCal);
		UpdateData(FALSE);
	}
}


void CDateTimePickerDlg::OnSelchangeComboDateformat() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_nFormat!=0)
		SetDateFormat();
}

void CDateTimePickerDlg::OnSelchangeComboTimeformat() 
{
	// TODO: Add your control notification handler code here
	
	VERIFY(UpdateData(TRUE));

	if(m_nFormat==0)
		SetTimeFormat();
}

void CDateTimePickerDlg::SetDateFormat()
{
	if(m_nDateFormat==0)
		m_ctlDateTimePicker.SetFormat(NULL);
	else
	{
		CString sFormat;
		m_cmbDateFormat.GetLBText(m_nDateFormat,sFormat);
		m_ctlDateTimePicker.SetFormat(sFormat);
	}
}

void CDateTimePickerDlg::SetTimeFormat()
{
	if(m_nTimeFormat==0)
		m_ctlDateTimePicker.SetFormat(NULL);
	else
	{
		CString sFormat;
		m_cmbTimeFormat.GetLBText(m_nTimeFormat,sFormat);
		m_ctlDateTimePicker.SetFormat(sFormat);
	}
}

int CDateTimePickerDlg::ConvertPointToLogUnit(const int nPointSize, CDC* pDC/*=NULL*/)
{
	HDC hDC;
	if (pDC!=NULL)
	{
		ASSERT_VALID(pDC);
		ASSERT(pDC->m_hAttribDC != NULL);
		hDC=pDC->m_hAttribDC;
	}
	else
		hDC=::GetDC(NULL);

	// convert nPointSize to logical units based on pDC
	POINT pt;
	pt.y=::GetDeviceCaps(hDC,LOGPIXELSY)*nPointSize;
	pt.y/=720;    // 72 points/inch, 10 decipoints/point
	::DPtoLP(hDC,&pt,1);
	POINT ptOrg = {0,0};
	::DPtoLP(hDC,&ptOrg,1);

	if(pDC==NULL)
		::ReleaseDC(NULL,hDC);

	return -abs(pt.y-ptOrg.y);
}

int CDateTimePickerDlg::ConvertLogUnitToPoint(const int nLogUnitSize, CDC* pDC/*=NULL*/)
{
	HDC hDC;
	if (pDC!=NULL)
	{
		ASSERT_VALID(pDC);
		ASSERT(pDC->m_hAttribDC != NULL);
		hDC=pDC->m_hAttribDC;
	}
	else
		hDC=::GetDC(NULL);

	POINT ptOrg={0,0};
	::DPtoLP(hDC,&ptOrg,1);
	POINT pt={0,0};

	pt.y=abs(nLogUnitSize)+ptOrg.y;
	::LPtoDP(hDC,&pt,1);
	pt.y*=720;    // 72 points/inch, 10 decipoints/point
	
	int nPointSize=(pt.y)/(::GetDeviceCaps(hDC,LOGPIXELSY));

	if (pDC==NULL)
		::ReleaseDC(NULL,hDC);

	return nPointSize;
}

