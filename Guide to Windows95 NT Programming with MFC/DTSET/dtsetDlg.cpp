// datentryDlg.cpp : implementation file
//

////////////////////////////////////// Includes ///////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "dtsetDlg.h"


////////////////////////////////////// Macros /////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////// Implementation //////////////////////////
BEGIN_MESSAGE_MAP(CDTSetDlg, CDialog)
	//{{AFX_MSG_MAP(CDTSetDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_CDATE_FORMAT, OnChangeCDateFormat)
	ON_EN_CHANGE(IDC_CLDATE_FORMAT, OnChangeCLDateFormat)
	ON_EN_CHANGE(IDC_CLTIMEOFDAY_FORMAT, OnChangeCLTimeOfDayFormat)
	ON_EN_CHANGE(IDC_CLTIMESPAN_FORMAT, OnChangeCLTimeSpanFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CDTSetDlg::CDTSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDTSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDTSetDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_JulianEnd = CDate(1582, 10, 4);
  m_GregorianBegin = CDate(1582, 10, 15);
  m_BeginDayOfWeek = CDate::MONDAY;
}

void CDTSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTSetDlg)
	//}}AFX_DATA_MAP
  DDX_CDateControl(pDX, IDC_JULIAN_DATE, m_ctrlJulianEnd, DT_ONLYVALID);
  DDX_CDateControl(pDX, IDC_GREGORIAN_DATE, m_ctrlGregorianBegin, DT_ONLYVALID);
  DDX_CDate(pDX, m_ctrlJulianEnd, m_JulianEnd);
  DDX_CDate(pDX, m_ctrlGregorianBegin, m_GregorianBegin);
  DDV_GreaterThanCDate(pDX, m_GregorianBegin, m_JulianEnd);

  DDX_Text(pDX, IDC_CDATE_FORMAT, m_sCDateFormat);
  DDX_Text(pDX, IDC_CLDATE_FORMAT, m_sCLDateFormat);
  DDX_Text(pDX, IDC_CLTIMESPAN_FORMAT, m_sCLTimeSpanFormat);
  DDX_Text(pDX, IDC_CLTIMEOFDAY_FORMAT, m_sCLTimeOfDayFormat);


  if (pDX->m_bSaveAndValidate)
  {
    DDX_CBIndex(pDX, IDC_BEGINDAYOFWEEK, m_BeginDayOfWeek);
    m_BeginDayOfWeek++;
  }
  else
  {
    int nIndex = m_BeginDayOfWeek-1;
    DDX_CBIndex(pDX, IDC_BEGINDAYOFWEEK, nIndex);
  }
}

BOOL CDTSetDlg::OnInitDialog()
{
  //Add Day of Week strings to combo box
  CComboBox* pDayOfWeekCtrl = (CComboBox*) GetDlgItem(IDC_BEGINDAYOFWEEK);
  int nIndex;
  for (WORD i = CDate::SUNDAY; i<=CDate::SATURDAY; i++)
    nIndex = pDayOfWeekCtrl->InsertString(i - CDate::SUNDAY, CDate::GetFullStringDayOfWeek(i));

	CDialog::OnInitDialog();

	// Set the icon for this dialog.
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

  //refresh the example statics
  OnChangeCDateFormat();
  OnChangeCLDateFormat();
  OnChangeCLTimeOfDayFormat();
  OnChangeCLTimeSpanFormat();

	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CDTSetDlg::OnPaint() 
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
HCURSOR CDTSetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDTSetDlg::OnChangeCDateFormat() 
{
	CString sText;
  GetDlgItemText(IDC_CDATE_FORMAT, sText);
  CString& sEg = (CDate::CurrentDate()).Format(sText);
  SetDlgItemText(IDC_CDATE_EG, sEg);
}

void CDTSetDlg::OnChangeCLDateFormat() 
{
	CString sText;
  GetDlgItemText(IDC_CLDATE_FORMAT, sText);
  CString& sEg = (CLDate::CurrentTime(LOCAL)).Format(sText);
  SetDlgItemText(IDC_CLDATE_EG, sEg);
}

void CDTSetDlg::OnChangeCLTimeOfDayFormat() 
{
	CString sText;
  GetDlgItemText(IDC_CLTIMEOFDAY_FORMAT, sText);
  CString& sEg = (CLTimeOfDay::CurrentTimeOfDay(LOCAL)).Format(sText);
  SetDlgItemText(IDC_CLTIMEOFDAY_EG, sEg);
}

void CDTSetDlg::OnChangeCLTimeSpanFormat() 
{
	CString sText;
  GetDlgItemText(IDC_CLTIMESPAN_FORMAT, sText);
  CString& sEg = (CLTimeSpan(1, 2, 3, 4, 5)).Format(sText);
  SetDlgItemText(IDC_CLTIMESPAN_EG, sEg);
}


void CDTSetDlg::LoadSettings()
{
  // Read the current state from the registry
  // Try opening the registry key:
  // HKEY_CURRENT_USER\Control Panel\DTime
  HKEY hcpl;
  if (RegOpenKeyEx(HKEY_CURRENT_USER,
                   _T("Control Panel"),
                   0,
                   KEY_QUERY_VALUE,
                   &hcpl) == ERROR_SUCCESS) 
  {
    HKEY happ;
    if (RegOpenKeyEx(hcpl,
                     _T("DTime"),
                     0,
                     KEY_QUERY_VALUE,
                     &happ) == ERROR_SUCCESS) 
    {
      // Yes we are installed

      //First the begining day of week
      DWORD dwType = 0;
      DWORD dwSize = sizeof(m_BeginDayOfWeek);
      RegQueryValueEx(happ,
                      _T("BeginDayOfWeek"),
                      NULL,
                      &dwType,
                      (BYTE*)&m_BeginDayOfWeek,
                      &dwSize);


      //the day part of the julian end date
      dwType = 0;
      DWORD Day;
      dwSize = sizeof(DWORD);
      RegQueryValueEx(happ,
                      _T("JulianEndDay"),
                      NULL,
                      &dwType,
                      (BYTE*)&Day,
                      &dwSize);

      //the month part of the julian end date
      dwType = 0;
      DWORD Month;
      dwSize = sizeof(DWORD);
      RegQueryValueEx(happ,
                      _T("JulianEndMonth"),
                      NULL,
                      &dwType,
                      (BYTE*)&Month,
                      &dwSize);

      //the year part of the julian end date
      dwType = 0;
      LONG Year;
      dwSize = sizeof(LONG);
      RegQueryValueEx(happ,
                      _T("JulianEndYear"),
                      NULL,
                      &dwType,
                      (BYTE*)&Year,
                      &dwSize);

      m_JulianEnd = CDate(Year, (WORD) Month, (WORD) Day);



      //the day part of the gregorian begin date
      dwType = 0;
      dwSize = sizeof(DWORD);
      RegQueryValueEx(happ,
                      _T("GregorianBeginDay"),
                      NULL,
                      &dwType,
                      (BYTE*)&Day,
                      &dwSize);

      //the month part of the gregorian begin date
      dwType = 0;
      dwSize = sizeof(DWORD);
      RegQueryValueEx(happ,
                      _T("GregorianBeginMonth"),
                      NULL,
                      &dwType,
                      (BYTE*)&Month,
                      &dwSize);

      //the year part of the gregorian begin date
      dwType = 0;
      dwSize = sizeof(LONG);
      RegQueryValueEx(happ,
                      _T("GregorianBeginYear"),
                      NULL,
                      &dwType,
                      (BYTE*)&Year,
                      &dwSize);

      m_GregorianBegin = CDate(Year, (WORD) Month, (WORD) Day);




      //the default CDate format string
      dwSize = 1024;
      LPTSTR pBuf = m_sCDateFormat.GetBufferSetLength(dwSize);
      RegQueryValueEx(happ,
                      _T("CDateDefaultFormat"),
                      NULL,
                      &dwType,
                      (BYTE*)pBuf,
                      &dwSize);
      m_sCDateFormat.ReleaseBuffer();

      //the default CLDate format string
      dwSize = 1024;
      pBuf = m_sCLDateFormat.GetBufferSetLength(dwSize);
      RegQueryValueEx(happ,
                      _T("CLDateDefaultFormat"),
                      NULL,
                      &dwType,
                      (BYTE*)pBuf,
                      &dwSize);
      m_sCLDateFormat.ReleaseBuffer();

      //the default CLTimeSpan format string
      dwSize = 1024;
      pBuf = m_sCLTimeSpanFormat.GetBufferSetLength(dwSize);
      RegQueryValueEx(happ,
                      _T("CLTimeSpanDefaultFormat"),
                      NULL,
                      &dwType,
                      (BYTE*)pBuf,
                      &dwSize);
      m_sCLTimeSpanFormat.ReleaseBuffer();

      //the default CLTimeOfDay format string
      dwSize = 1024;
      pBuf = m_sCLTimeOfDayFormat.GetBufferSetLength(dwSize);
      RegQueryValueEx(happ,
                      _T("CLTimeOfDayDefaultFormat"),
                      NULL,
                      &dwType,
                      (BYTE*)pBuf,
                      &dwSize);
      m_sCLTimeOfDayFormat.ReleaseBuffer();

      RegCloseKey(happ);
    }
    RegCloseKey(hcpl);
  }
}

void CDTSetDlg::SaveSettings()
{
  // Update the registry
  // Try creating/opening the registry key
  HKEY hcpl;

  if (RegOpenKeyEx(HKEY_CURRENT_USER,
                   _T("Control Panel"),
                   0,
                   KEY_WRITE,
                   &hcpl) == ERROR_SUCCESS) 
  {
    HKEY happ;
    DWORD dwDisp;
    if (RegCreateKeyEx(hcpl,
                       _T("DTime"),
                       0,
                       _T(""),
                       REG_OPTION_NON_VOLATILE,
                       KEY_WRITE,
                       NULL,
                       &happ,
                       &dwDisp) == ERROR_SUCCESS) 
    {

      // Set the begining day of week
      RegSetValueEx(happ,
                    _T("BeginDayOfWeek"),
                    0,
                    REG_DWORD,
                    (BYTE*)&m_BeginDayOfWeek,
                    sizeof(m_BeginDayOfWeek));

      // Set the day part of the end of julian
      DWORD Day = (DWORD) m_JulianEnd.GetDay();
      RegSetValueEx(happ,
                    _T("JulianEndDay"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Day,
                    sizeof(DWORD));

      // Set the month part of the end of julian
      DWORD Month = (DWORD) m_JulianEnd.GetMonth();
      RegSetValueEx(happ,
                    _T("JulianEndMonth"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Month,
                    sizeof(DWORD));

      // Set the year part of the end of julian
      LONG Year = m_JulianEnd.GetYear();
      RegSetValueEx(happ,
                    _T("JulianEndYear"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Year,
                    sizeof(LONG));

      // Set the day part of the begin of gregorian
      Day = (DWORD) m_GregorianBegin.GetDay();
      RegSetValueEx(happ,
                    _T("GregorianBeginDay"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Day,
                    sizeof(DWORD));

      // Set the month part of the begin of gregorian
      Month = (DWORD) m_GregorianBegin.GetMonth();
      RegSetValueEx(happ,
                    _T("GregorianBeginMonth"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Month,
                    sizeof(DWORD));

      // Set the year part of the begin of gregorian
      Year = m_GregorianBegin.GetYear();
      RegSetValueEx(happ,
                    _T("GregorianBeginYear"),
                    0,
                    REG_DWORD,
                    (BYTE*)&Year,
                    sizeof(LONG));


      // Set the default CDate Format string
      RegSetValueEx(happ,
                    _T("CDateDefaultFormat"),
                    0,
                    REG_SZ,
                    (BYTE*) m_sCDateFormat.GetBuffer(m_sCDateFormat.GetLength()),
                    sizeof(TCHAR) * (m_sCDateFormat.GetLength() + 1));
      m_sCDateFormat.ReleaseBuffer();

      // Set the default CLDate Format string
      RegSetValueEx(happ,
                    _T("CLDateDefaultFormat"),
                    0,
                    REG_SZ,
                    (BYTE*) m_sCLDateFormat.GetBuffer(m_sCLDateFormat.GetLength()),
                    sizeof(TCHAR) * (m_sCLDateFormat.GetLength() + 1));
      m_sCLDateFormat.ReleaseBuffer();

      // Set the default CLTimeSpan Format string
      RegSetValueEx(happ,
                    _T("CLTimeSpanDefaultFormat"),
                    0,
                    REG_SZ,
                    (BYTE*) m_sCLTimeSpanFormat.GetBuffer(m_sCLTimeSpanFormat.GetLength()),
                    sizeof(TCHAR) * (m_sCLTimeSpanFormat.GetLength() + 1));
      m_sCLTimeSpanFormat.ReleaseBuffer();

      // Set the default CLTimeOfDay Format string
      RegSetValueEx(happ,
                    _T("CLTimeOfDayDefaultFormat"),
                    0,
                    REG_SZ,
                    (BYTE*) m_sCLTimeOfDayFormat.GetBuffer(m_sCLTimeOfDayFormat.GetLength()),
                    sizeof(TCHAR) * (m_sCLTimeOfDayFormat.GetLength() + 1));
      m_sCLTimeOfDayFormat.ReleaseBuffer();

      // Finished with keys
      RegCloseKey(happ);
    }
    RegCloseKey(hcpl);
  }
}