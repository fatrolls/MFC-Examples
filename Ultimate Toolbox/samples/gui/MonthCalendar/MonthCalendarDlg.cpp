// MonthCalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MonthCalendar.h"
#include "MonthCalendarDlg.h"

#include "UTSampleAbout.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonthCalendarDlg dialog

CMonthCalendarDlg::CMonthCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonthCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonthCalendarDlg)
	m_bBoldHolidays = FALSE;
	m_bDayState = FALSE;
	m_bMultiselect = FALSE;
	m_bNotoday = FALSE;
	m_bNotodaycircle = FALSE;
	m_bWeeknumbers = FALSE;
	m_nMaxSel = 0;
	m_nScrollRate = 0;
	m_nFirstDay = -1;
	m_nDimension = -1;
	m_sSelection = _T("");
	m_sRangeFrom = _T("");
	m_sRangeTo = _T("");
	m_bInfoTip = FALSE;
	m_sFontName = _T("");
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

void CMonthCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonthCalendarDlg)
	DDX_Control(pDX, IDC_STATIC_FONTNAME, m_ctlFontName);
	DDX_Control(pDX, IDC_COMBO_FIRSTDAY, m_cmbFirstDay);
	DDX_Control(pDX, IDC_COMBO_DIMENSION, m_cmbDimension);
	DDX_Control(pDX, IDC_BUTTON_CLRTRAILINGTEXT, m_btnClrTrailingText);
	DDX_Control(pDX, IDC_BUTTON_CLRTITLETEXT, m_btnClrTitleText);
	DDX_Control(pDX, IDC_BUTTON_CLRTITLEBK, m_btnClrTitleBk);
	DDX_Control(pDX, IDC_BUTTON_CLRTEXT, m_btnClrText);
	DDX_Control(pDX, IDC_BUTTON_CLRMONTHBK, m_btnClrMonthBk);
	DDX_Control(pDX, IDC_BUTTON_CLRBK, m_btnClrBk);
	DDX_Check(pDX, IDC_CHECK_BOLDHOLIDAYS, m_bBoldHolidays);
	DDX_Check(pDX, IDC_CHECK_DAYSTATE, m_bDayState);
	DDX_Check(pDX, IDC_CHECK_MULTISELECT, m_bMultiselect);
	DDX_Check(pDX, IDC_CHECK_NOTODAY, m_bNotoday);
	DDX_Check(pDX, IDC_CHECK_NOTODAYCIRCLE, m_bNotodaycircle);
	DDX_Check(pDX, IDC_CHECK_WEEKNUMBERS, m_bWeeknumbers);
	DDX_Text(pDX, IDC_EDIT_MAXSEL, m_nMaxSel);
	DDX_Text(pDX, IDC_EDIT_SCROLLRATE, m_nScrollRate);
	DDX_CBIndex(pDX, IDC_COMBO_FIRSTDAY, m_nFirstDay);
	DDX_CBIndex(pDX, IDC_COMBO_DIMENSION, m_nDimension);
	DDX_Text(pDX, IDC_SELECTION, m_sSelection);
	DDX_Text(pDX, IDC_RANGEFROM, m_sRangeFrom);
	DDX_Text(pDX, IDC_RANGETO, m_sRangeTo);
	DDX_Check(pDX, IDC_CHECK_INFOTIP, m_bInfoTip);
	DDX_Text(pDX, IDC_STATIC_FONTNAME, m_sFontName);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTRAILINGTEXT, m_clrTrailingText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTITLETEXT, m_clrTitleText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTITLEBK, m_clrTitleBk);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRTEXT, m_clrText);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRMONTHBK, m_clrMonthBk);
	DDX_ColorPicker(pDX, IDC_BUTTON_CLRBK, m_clrBk);
}

BEGIN_MESSAGE_MAP(CMonthCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CMonthCalendarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	ON_BN_CLICKED(IDC_BUTTON_FONTNAME, OnButtonFontname)
	//}}AFX_MSG_MAP
	ON_NOTIFY(MCN_SELCHANGE,IDC_MONTHCAL,OnSelChange)
	ON_NOTIFY(MCN_SELECT,IDC_MONTHCAL,OnSelect)
	ON_NOTIFY(MCN_GETDAYSTATE,IDC_MONTHCAL,OnGetDayState)
	ON_NOTIFY(OXMCN_GETDAYSTATE,IDC_MONTHCAL,OnOXGetDayState)
	ON_NOTIFY(OXMCN_GETINFOTIP,IDC_MONTHCAL,OnOXGetInfoTip)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonthCalendarDlg message handlers

BOOL CMonthCalendarDlg::OnInitDialog()
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

	m_cmbFirstDay.AddString(_T("Monday"));
	m_cmbFirstDay.AddString(_T("Tuesday"));
	m_cmbFirstDay.AddString(_T("Wendsday"));
	m_cmbFirstDay.AddString(_T("Thursday"));
	m_cmbFirstDay.AddString(_T("Friday"));
	m_cmbFirstDay.AddString(_T("Saturday"));
	m_cmbFirstDay.AddString(_T("Sunday"));
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

	// create calendar control
	//
	CWnd *pFrame=GetDlgItem(IDC_MONTHCAL);
	CRect rcWnd;
	pFrame->GetWindowRect(rcWnd);
	pFrame->DestroyWindow(); //pFrame was just a placeholder anyway.
	ScreenToClient(rcWnd);
	m_ctlMonthCal.Create(WS_CHILD|WS_VISIBLE,rcWnd.TopLeft(),this,IDC_MONTHCAL,
		OXMCS_BOLDHOLIDAYS|OXMCS_INFOTIP,2,2);

	HOLIDAYS holidays;

	holidays.nMonth=-1;
	holidays.nYear=-1;
	holidays.arrWeekDays.AddTail(SATURDAY);
	holidays.arrWeekDays.AddTail(SUNDAY);
	m_ctlMonthCal.SetHolidays(&holidays);

	holidays.Reset();
	holidays.nMonth=7;
	holidays.nYear=-1;
	holidays.arrMonthDays.AddTail(FIRST);
	m_ctlMonthCal.SetHolidays(&holidays);
	/////////////////////////////

	CFont* pFont=m_ctlMonthCal.GetFont();
	ASSERT(pFont);
	VERIFY(pFont->GetLogFont(&m_lfText));
	m_lfText.lfWeight=FW_NORMAL;

	m_sFontName.Format(_T("%d pt, %s"),(ConvertLogUnitToPoint(m_lfText.lfHeight)+5)/10,
		m_lfText.lfFaceName);
	m_ctlFontName.SetTextLogFont(&m_lfText);
	m_ctlFontName.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));

	GetVars();
	SetVars();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMonthCalendarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMonthCalendarDlg::OnPaint() 
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
HCURSOR CMonthCalendarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMonthCalendarDlg::OnApply() 
{
	// TODO: Add your control notification handler code here
	
	SetVars();
}

void CMonthCalendarDlg::OnRestore() 
{
	// TODO: Add your control notification handler code here
	
	GetVars();
}

void CMonthCalendarDlg::GetVars()
{
	DWORD dwCalStyle=m_ctlMonthCal.GetMonthCalStyle();
	DWORD dwStyle=m_ctlMonthCal.GetStyle();

	m_bBoldHolidays=(dwCalStyle&OXMCS_BOLDHOLIDAYS)!=0 ? TRUE : FALSE;
	m_bInfoTip=(dwCalStyle&OXMCS_INFOTIP)!=0 ? TRUE : FALSE;

	m_bDayState=(dwStyle&MCS_DAYSTATE)!=0 ? TRUE : FALSE;
	m_bMultiselect=(dwStyle&MCS_MULTISELECT)!=0 ? TRUE : FALSE;
	m_bNotoday=(dwStyle&MCS_NOTODAY)!=0 ? TRUE : FALSE;
#if (_WIN32_IE >= 0x0400)
	m_bNotodaycircle=(dwStyle&MCS_NOTODAYCIRCLE)!=0 ? TRUE : FALSE;
#else
	m_bNotodaycircle=FALSE;
#endif
	m_bWeeknumbers=(dwStyle&MCS_WEEKNUMBERS)!=0 ? TRUE : FALSE;

	m_nMaxSel=m_ctlMonthCal.GetMaxSelCount();
	m_nScrollRate=m_ctlMonthCal.GetMonthDelta();
	m_nFirstDay=m_ctlMonthCal.GetFirstDayOfWeek();

	CSize szMonthFitCount;
	VERIFY(m_ctlMonthCal.GetMonthFitCount(szMonthFitCount));
	switch(szMonthFitCount.cx*szMonthFitCount.cy)
	{
	case 1:
		m_nDimension=0;
		break;
	case 2:
		if(szMonthFitCount.cy==1)
			m_nDimension=1;
		else
			m_nDimension=2;
		break;
	case 4:
		m_nDimension=3;
		break;
	default:
		ASSERT(FALSE);
	}

	m_clrTrailingText=m_ctlMonthCal.GetTrailingTextColor();
	m_clrTitleText=m_ctlMonthCal.GetTitleTextColor();
	m_clrTitleBk=m_ctlMonthCal.GetTitleBkColor();
	m_clrText=m_ctlMonthCal.GetTextColor();
	m_clrMonthBk=m_ctlMonthCal.GetMonthBkColor();
	m_clrBk=m_ctlMonthCal.GetBkColor();

	GetLatestSelInfo();

	UpdateData(FALSE);
}


void CMonthCalendarDlg::GetLatestSelInfo()
{
	if((m_ctlMonthCal.GetStyle()&MCS_MULTISELECT)!=0)
	{
		m_sSelection.Empty();
		
		COleDateTime ctmin, ctmax;
		m_ctlMonthCal.GetSelRange(ctmin,ctmax);
		m_sRangeFrom.Format(_T("%02d/%02d/%4d"),ctmin.GetMonth(),
			ctmin.GetDay(),ctmin.GetYear());
		m_sRangeTo.Format(_T("%02d/%02d/%4d"),ctmax.GetMonth(),
			ctmax.GetDay(),ctmax.GetYear());
	}
	else
	{
		COleDateTime ct;
		m_ctlMonthCal.GetCurSel(ct);
		m_sSelection.Format(_T("%02d/%02d/%4d"),ct.GetMonth(),ct.GetDay(),ct.GetYear());
		
		m_sRangeFrom.Empty();
		m_sRangeTo.Empty();
	}
}


void CMonthCalendarDlg::SetVars()
{
	if(!UpdateData(TRUE))
		return;

	if((((m_ctlMonthCal.GetStyle()&MCS_MULTISELECT)!=0)!=m_bMultiselect) || 
		(((m_ctlMonthCal.GetStyle()&MCS_DAYSTATE)!=0)!=m_bDayState) ||
		(((m_ctlMonthCal.GetMonthCalStyle()&OXMCS_BOLDHOLIDAYS)!=0)!=m_bBoldHolidays))
	{
		// recreate calendar control
		//
		CWnd *pFrame=GetDlgItem(IDC_MONTHCAL);
		CRect rcWnd;
		pFrame->GetWindowRect(rcWnd);
		pFrame->DestroyWindow(); 
		ScreenToClient(rcWnd);
		m_ctlMonthCal.Create(WS_CHILD|WS_VISIBLE|(m_bMultiselect ? MCS_MULTISELECT : 0)|
			(m_bDayState ? MCS_DAYSTATE : 0),rcWnd.TopLeft(),this,IDC_MONTHCAL,
			(m_bBoldHolidays ? OXMCS_BOLDHOLIDAYS : 0));
		/////////////////////////////
	}

	if(m_bInfoTip)
		m_ctlMonthCal.SetMonthCalStyle(m_ctlMonthCal.GetMonthCalStyle()|
			OXMCS_INFOTIP);
	else
		m_ctlMonthCal.SetMonthCalStyle(m_ctlMonthCal.GetMonthCalStyle()&
			~(OXMCS_INFOTIP));

	if(m_bNotoday)
		m_ctlMonthCal.ModifyStyle(0,MCS_NOTODAY);
	else
		m_ctlMonthCal.ModifyStyle(MCS_NOTODAY,0);
#if (_WIN32_IE >= 0x0400)
	if(m_bNotodaycircle)
		m_ctlMonthCal.ModifyStyle(0,MCS_NOTODAYCIRCLE);
	else
		m_ctlMonthCal.ModifyStyle(MCS_NOTODAYCIRCLE,0);
#endif
	if(m_bWeeknumbers)
		m_ctlMonthCal.ModifyStyle(0,MCS_WEEKNUMBERS);
	else
		m_ctlMonthCal.ModifyStyle(MCS_WEEKNUMBERS,0);

	m_ctlMonthCal.SetMaxSelCount(m_nMaxSel);
	m_ctlMonthCal.SetMonthDelta(m_nScrollRate);
	m_ctlMonthCal.SetFirstDayOfWeek(m_nFirstDay);

	m_ctlMonthCal.SetTrailingTextColor(m_clrTrailingText);
	m_ctlMonthCal.SetTitleTextColor(m_clrTitleText);
	m_ctlMonthCal.SetTitleBkColor(m_clrTitleBk);
	m_ctlMonthCal.SetTextColor(m_clrText);
	m_ctlMonthCal.SetMonthBkColor(m_clrMonthBk);
	m_ctlMonthCal.SetBkColor(m_clrBk);

	static CFont font;
	if((HFONT)font!=NULL)
		font.DeleteObject();
	VERIFY(font.CreateFontIndirect(&m_lfText));
	m_ctlMonthCal.SetFont(&font);

	CSize szMargin(4,4);
	switch(m_nDimension)
	{
	case 0:
		m_ctlMonthCal.SetCtrlDimension(1,1,szMargin);
		break;
	case 1:
		m_ctlMonthCal.SetCtrlDimension(2,1,szMargin);
		break;
	case 2:
		m_ctlMonthCal.SetCtrlDimension(1,2,szMargin);
		break;
	case 3:
		m_ctlMonthCal.SetCtrlDimension(2,2,szMargin);
		break;
	default:
		ASSERT(FALSE);
	}
}

//Notification handlers for notifications from the COXMonthCalCtrl
void CMonthCalendarDlg::OnGetDayState(NMHDR *pHdr, LRESULT *pRes)
{
	NMDAYSTATE *pds = (NMDAYSTATE*)pHdr;
	//this function just bolds the first four days of every visible
	//month.
	for(int i=0;i<pds->cDayState;i++)
		BOLDDAY(pds->prgDayState[i],15);
	*pRes=0;
}

void CMonthCalendarDlg::OnOXGetDayState(NMHDR *pHdr, LRESULT *pRes)
{
	UNREFERENCED_PARAMETER(pHdr);
//	LPOXNMDAYSTATE pds = (LPOXNMDAYSTATE)pHdr;
	*pRes=0;
}

void CMonthCalendarDlg::OnOXGetInfoTip(NMHDR *pHdr, LRESULT *pRes)
{
	LPOXNMMCINFOTIP pInfoTip = (LPOXNMMCINFOTIP)pHdr;

	CString sText=_T("");

	if(pInfoTip->pMCHitTest->uHit==MCHT_TITLEBTNNEXT)
		sText=_T("Button next");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_TITLEBTNPREV)
		sText=_T("Button previous");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_TITLEMONTH)
		sText=_T("Month name");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_TITLEYEAR)
		sText=_T("Year");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_TITLEBK)
		sText=_T("Title background");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_NOWHERE)
		sText=_T("Nowhere");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARBK)
		sText=_T("Calendar background");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARDAY)
		sText=_T("Week day");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARWEEKNUM)
		sText=_T("Week number");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARDATENEXT)
		sText=_T("Date from next month");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARDATEPREV)
		sText=_T("Date from previous month");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_CALENDARDATE)
		sText=_T("Date from current month");
	else if(pInfoTip->pMCHitTest->uHit==MCHT_TODAYLINK)
		sText=_T("Today link");

	UTBStr::tcsncpy(pInfoTip->szText,countof(pInfoTip->szText), 
		sText.GetBuffer(sText.GetLength()), countof(pInfoTip->szText));
	sText.ReleaseBuffer();

	*pRes=0;
}

void CMonthCalendarDlg::OnSelect(NMHDR *pHdr, LRESULT *pRes)
{
	UNREFERENCED_PARAMETER(pHdr);

	GetLatestSelInfo();
	GetDlgItem(IDC_SELECTION)->SetWindowText(m_sSelection);

	*pRes=0;
}

void CMonthCalendarDlg::OnSelChange(NMHDR *pHdr, LRESULT *pRes)
{
	UNREFERENCED_PARAMETER(pHdr);

	GetLatestSelInfo();
	GetDlgItem(IDC_RANGEFROM)->SetWindowText(m_sRangeFrom);
	GetDlgItem(IDC_RANGETO)->SetWindowText(m_sRangeTo);

	*pRes=0;
}


void CMonthCalendarDlg::OnButtonFontname() 
{
	// TODO: Add your control notification handler code here
	
	// Use font common dialog
	CFontDialog fontDlg(&m_lfText);
	if(fontDlg.DoModal()==IDOK)
	{
		fontDlg.GetCurrentFont(&m_lfText);
		m_sFontName.Format(_T("%d pt, %s"),fontDlg.GetSize()/10,m_lfText.lfFaceName);
		m_ctlFontName.SetTextLogFont(&m_lfText);
		UpdateData(FALSE);
	}
}

int CMonthCalendarDlg::ConvertPointToLogUnit(const int nPointSize, CDC* pDC/*=NULL*/)
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

int CMonthCalendarDlg::ConvertLogUnitToPoint(const int nLogUnitSize, CDC* pDC/*=NULL*/)
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

