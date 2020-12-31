// TimeClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"		// main symbols

#include "TimeClockDlg.h"

#include <io.h>
#include <math.h>
#include "PrintPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT CTimeClockDlg::nAboutBoxCommandId = 0x0010;
const UINT CTimeClockDlg::nUpdateClockEvent = 7;
const DWORD CTimeClockDlg::m_dwDocID = 0x73f3da7;

/////////////////////////////////////////////////////////////////////////////
// CTimeClockDlg dialog

CTimeClockDlg::CTimeClockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeClockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeClockDlg)
	m_strHours = _T("");
	m_strMinutes = _T("");
	m_strSeconds = _T("");
	m_strDate = _T("");
	m_strTimeCardFilename = _T("");
	m_strName = _T("");
	m_strWeek = _T("");
	m_strVacation = _T("");
	m_strSick = _T("");
	m_strOther = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dwNumTimeCardEntries = 0;
	m_strTimeCardFilename = "";
	m_bHaveTimer = TRUE;
	m_time_tTotal = 0;
	m_time_tLast = 0;
	m_bHaveValidFile = TRUE;
	m_lpcstrCmdLine = NULL;
}

void CTimeClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeClockDlg)
	DDX_Control(pDX, IDC_TIMECARD, m_listctlTimeCard);
	DDX_Text(pDX, IDC_HOURS, m_strHours);
	DDX_Text(pDX, IDC_MINUTES, m_strMinutes);
	DDX_Text(pDX, IDC_SECONDS, m_strSeconds);
	DDX_Text(pDX, IDC_DAY, m_strDate);
	DDX_Text(pDX, IDC_TIMECARDFILE, m_strTimeCardFilename);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_WEEK, m_strWeek);
	DDX_Text(pDX, IDC_VACATION, m_strVacation);
	DDX_Text(pDX, IDC_SICK, m_strSick);
	DDX_Text(pDX, IDC_OTHER, m_strOther);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimeClockDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeClockDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PUNCHINOUT, OnPunchinout)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LOADTIMECARD, OnLoadtimecard)
	ON_BN_CLICKED(IDC_PRINTREPORT, OnPrintreport)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_DBLCLK, IDC_TIMECARD, OnDblclkTimecard)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeClockDlg message handlers

void CTimeClockDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID & 0xFFF0) == nAboutBoxCommandId)
	{
		CDialog dlg ( IDD_ABOUT );
		dlg . DoModal ();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

BOOL CTimeClockDlg::OnInitDialog()
{
	CString strTimeCardFilename;

	CDialog::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, nAboutBoxCommandId, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_ilLargeImages. Create ( 32, 32, FALSE, 2, 0 );
	m_ilSmallImages . Create ( 16, 16, FALSE, 2, 0 );

	m_ilLargeImages . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_IN ) ) );
	m_ilLargeImages . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_OUT ) ) );
	m_ilSmallImages . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_IN ) ) );
	m_ilSmallImages . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_OUT ) ) );
  
	m_listctlTimeCard . SetImageList ( &m_ilLargeImages, LVSIL_NORMAL );
	m_listctlTimeCard . SetImageList ( &m_ilSmallImages, LVSIL_SMALL );
	
	m_listctlTimeCard . InsertColumn ( 0, "!    Date", LVCFMT_LEFT, 100 );
	m_listctlTimeCard . InsertColumn ( 1, "Time", LVCFMT_LEFT, 75 );
	m_listctlTimeCard . InsertColumn ( 2, "Current Total", LVCFMT_LEFT, 85 );
	m_listctlTimeCard . InsertColumn ( 3, "Running Total", LVCFMT_LEFT, 85 );
	
	Reset ();

	// if the shell has passed a filename on the command line (passed here by the app object)
	// load that time card.
	if ( *m_lpcstrCmdLine ) {
		strTimeCardFilename = m_lpcstrCmdLine;
		if ( strTimeCardFilename . Find ( '\"' ) != -1 )
			strTimeCardFilename = strTimeCardFilename . Mid ( 1, strTimeCardFilename . GetLength () - 2 );
		LoadCard ( strTimeCardFilename );
	}
	
	// set the timer that we will use to update the system time displayed on the main dialog.
	if ( SetTimer ( nUpdateClockEvent, 1000, NULL ) != nUpdateClockEvent ) {
		AfxMessageBox ( "Cannot get system timer.  Time will not be shown.", MB_ICONEXCLAMATION );
		m_bHaveTimer = FALSE;
	}
	else
		UpdateClock (); // put some initial values in the clock display
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CTimeClockDlg::OnPaint() 
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
HCURSOR CTimeClockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTimeClockDlg::OnClose() 
{
	// if we had gotten a timer, kill it.
	if ( m_bHaveTimer )
		KillTimer ( nUpdateClockEvent );

	// if we have a timecard file loaded, save it.
	if ( ! m_strTimeCardFilename . IsEmpty () ) {
		CFile cfSettingsFile ( m_strTimeCardFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite );
		CArchive ar ( &cfSettingsFile, CArchive::store );
		Serialize ( ar );
	}
	
	CDialog::OnClose();
}

// the member 'm_dwDocID' is a const value used to identify our datafiles.
void CTimeClockDlg::Serialize(CArchive& ar) 
{
	DWORD dwDocID;

	if (ar.IsStoring())
	{	// storing code

		// get dialog field contents
		GetDlgItemText ( IDC_NAME, m_strName );
		GetDlgItemText ( IDC_WEEK, m_strWeek );
		GetDlgItemText ( IDC_VACATION, m_strVacation );
		GetDlgItemText ( IDC_SICK, m_strSick );
		GetDlgItemText ( IDC_OTHER, m_strOther );
		
		// save "Document ID" first, then the string data
		ar << m_dwDocID << m_strName << m_strWeek << m_strVacation << m_strSick << m_strOther;
		// save the time data
		m_listTimes . Serialize ( ar );
	}
	else
	{	// loading code
		ar >> dwDocID; // load in a DWORD
		if ( dwDocID == m_dwDocID ) { // check if that value matches our "Document ID"
			// load the string data
			ar >> m_strName >> m_strWeek >> m_strVacation >> m_strSick >> m_strOther;
			// load the time data
			m_listTimes . Serialize ( ar );
			
			// set up dialog field contents
			SetDlgItemText ( IDC_NAME, m_strName );
			SetDlgItemText ( IDC_WEEK, m_strWeek );
			SetDlgItemText ( IDC_VACATION, m_strVacation );
			SetDlgItemText ( IDC_SICK, m_strSick );
			SetDlgItemText ( IDC_OTHER, m_strOther );

			m_bHaveValidFile = TRUE;
		}
		else
			m_bHaveValidFile = FALSE; // our "Document ID" was not in the first DWORD, this is NOT our file.
	}
}

// set the clock display
void CTimeClockDlg::UpdateClock ()
{
	time_t time_tCurrentTime;
	char szBuffer [ 256 ];

	// get the system time
	time_tCurrentTime = time ( ( time_t* ) NULL );
	
	// make some strings
	strftime ( szBuffer, sizeof ( szBuffer ), "%a", localtime ( &time_tCurrentTime ) );
	m_strDate = szBuffer;
	strftime ( szBuffer, sizeof ( szBuffer ), "%H", localtime ( &time_tCurrentTime ) );
	m_strHours = szBuffer;
	strftime ( szBuffer, sizeof ( szBuffer ), "%M", localtime ( &time_tCurrentTime ) );
	m_strMinutes = szBuffer;
	strftime ( szBuffer, sizeof ( szBuffer ), "%S", localtime ( &time_tCurrentTime ) );
	m_strSeconds = szBuffer;

	// set the dialog fields
	( GetDlgItem ( IDC_DAY ) ) -> SetWindowText ( m_strDate );
	( GetDlgItem ( IDC_HOURS ) ) -> SetWindowText ( m_strHours );
	( GetDlgItem ( IDC_MINUTES ) ) -> SetWindowText ( m_strMinutes );
	( GetDlgItem ( IDC_SECONDS ) ) -> SetWindowText ( m_strSeconds );
}

// when our timer fires, updated the clock display
void CTimeClockDlg::OnTimer(UINT nIDEvent) 
{
	UpdateClock ();
	
	CDialog::OnTimer(nIDEvent);
}

// load a timecard file
BOOL CTimeClockDlg::LoadCard ( CString& strFileName )
{
	char szBuffer [ 256 ];

	// if we have one now, save it before loading new one
	if ( ! m_strTimeCardFilename . IsEmpty () ) {
		CFile cfSettingsFile ( m_strTimeCardFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite );
		CArchive ar ( &cfSettingsFile, CArchive::store );
		Serialize ( ar );
	}
	
	// reset the state of this object
	Reset ();
	
	// if the file does not exist, create a new one, and save it with empty values
	if ( access ( strFileName, 0 ) ) {
		sprintf ( szBuffer,	"Creating new TimeCard: %s", strFileName );
		AfxMessageBox ( szBuffer, MB_ICONINFORMATION );
		CFile cfSettingsFile ( strFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite );
		CArchive ar ( &cfSettingsFile, CArchive::store );
		Serialize ( ar );
	}

	// now open the file, and load it (may have just been created by the above code block)
	CFile cfSettingsFile ( strFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite );
	CArchive ar ( &cfSettingsFile, CArchive::load );
	Serialize ( ar );

	if ( m_bHaveValidFile ) { // if the file was a valid "TimeCard" file (see: CTimeClockDlg::Serialize())...

		// calculate the times and fill the list control 
		DoTimeListEntries ();

		// save the filename in the member, and set the filename dialog
		m_strTimeCardFilename = strFileName;
		SetDlgItemText ( IDC_TIMECARDFILE, m_strTimeCardFilename );

		return TRUE; // loading was successful
	}
	else { // the file was NOT a valid "TimeCard" file (see: CTimeClockDlg::Serialize())
		AfxMessageBox ( "That is not a TimeCard file", MB_ICONSTOP );
		Reset ();
		return FALSE;
	}
}

void CTimeClockDlg::OnLoadtimecard() 
{
	static char BASED_CODE szInputFilter[] = "TimeCard Files (*.tcd) | *.tcd | All Files (*.*) | *.* ||";
	CFileDialog wndInputFileDlg ( TRUE, NULL, "*.tcd", OFN_LONGNAMES | OFN_EXPLORER, szInputFilter );
	
	// show file dialog, and load TimeCard file selected (if one was) by user
	if ( wndInputFileDlg . DoModal () == IDOK )
		LoadCard ( wndInputFileDlg . GetPathName () );
	
}

// called when the "PUNCH IN/OUT" button is clicked
void CTimeClockDlg::OnPunchinout() 
{
	CString strButtonText, strDate, strTime, strCurrentTotal, strRunningTotal;
	char szBuffer [ 256 ];
	time_t time_tCurrentTime;

	// get the button text
	( GetDlgItem ( IDC_PUNCHINOUT ) ) -> GetWindowText ( strButtonText );

	// get the system time and make strings from it
	time_tCurrentTime = time ( ( time_t* ) NULL );
	strftime ( szBuffer, sizeof ( szBuffer ), "%a %m/%d/%y", localtime ( &time_tCurrentTime ) );
	strDate = szBuffer;
	strftime ( szBuffer, sizeof ( szBuffer ), "%H:%M:%S", localtime ( &time_tCurrentTime ) );
	strTime = szBuffer;

	if ( strButtonText == "PUNCH IN" ) { // Punching in....
		// insert the time/date into the list control
		m_listctlTimeCard . InsertItem ( m_dwNumTimeCardEntries, strDate, 0 );
		m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 1, LPCTSTR ( strTime ) );
		( GetDlgItem ( IDC_PUNCHINOUT ) ) -> SetWindowText ( "PUNCH OUT" ); // change the button text
	}
	else { // Punching out...
		// insert the time/date into the list control
		m_listctlTimeCard . InsertItem ( m_dwNumTimeCardEntries, strDate, 1 );
		m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 1, LPCTSTR ( strTime ) );
		( GetDlgItem ( IDC_PUNCHINOUT ) ) -> SetWindowText ( "PUNCH IN" ); // change the button text
	}

	// for every 2nd entry, compute the difference totals (e.g. running time total, etc)
	// and insert them into the right-most columns in the list control.
	if ( ( m_dwNumTimeCardEntries % 2 ) ) {
		GetEndTimes ( time_tCurrentTime, strCurrentTotal, strRunningTotal );
		m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 2, LPCTSTR ( strCurrentTotal ) );
		m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 3, LPCTSTR ( strRunningTotal ) );
	}
	m_time_tLast = time_tCurrentTime;  // save the current time, to be used in difference calculations for time accrual

	// make sure the time just entered into the list control is visible
	m_listctlTimeCard . EnsureVisible ( m_dwNumTimeCardEntries ++, TRUE );

	// add the time just entered to the list of times
	m_listTimes . AddTail ( time_tCurrentTime );

	// if there are at least 2 entries, enable the "PRINT" button
	if ( m_dwNumTimeCardEntries > 1 )
		( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( TRUE );
}

// Compute the difference totals (e.g. running time total, etc).
// The second is the smallest discrete unit we will compute.  If the difference in time is less
// than one second, the time string returned will represent zero time ("00:00:00").
void CTimeClockDlg::GetEndTimes ( time_t time_tCurrent, CString& strDaily, CString& strRunning )
{
	double dTimeDiff = 0.0, dHours = 0.0, dMinutes = 0.0, dSeconds = 0.0;
	char szBuffer [ 256 ];
	
	// intermediate total
	dTimeDiff = difftime ( time_tCurrent, m_time_tLast ); // the difference (current - last)
	if ( ( dHours = dTimeDiff / 3600.0 ) < 1.0 ) // less than one hour
		dHours = 0.0;
	if ( ( dMinutes = ( fmod ( dTimeDiff, 3600.0 ) ) / 60.0 ) < 1.0 ) // less than one minute
		dMinutes = 0.0;
	if ( ( dSeconds = fmod ( fmod ( dTimeDiff, 3600.0 ), 60.0 ) ) < 1.0 ) // less than one second
		dSeconds = 0.0;
	sprintf ( szBuffer, "%.2i:%.2i:%.2i", int ( dHours ), int ( dMinutes ), int ( dSeconds ) );
	strDaily = szBuffer;
	
	// running total
	dTimeDiff += double ( m_time_tTotal ); // add the previous running total to the current intermediate total
	m_time_tTotal = time_t ( dTimeDiff ); // update the running total
	if ( ( dHours = dTimeDiff / 3600.0 ) < 1.0 ) // less than one hour 
		dHours = 0.0;
	if ( ( dMinutes = ( fmod ( dTimeDiff, 3600.0 ) ) / 60.0 ) < 1.0 ) // less than one minute
		dMinutes = 0.0;
	if ( ( dSeconds = fmod ( fmod ( dTimeDiff, 3600.0 ), 60.0 ) ) < 1.0 ) // less than one second
		dSeconds = 0.0;
	sprintf ( szBuffer, "%.2i:%.2i:%.2i", int ( dHours ), int ( dMinutes ), int ( dSeconds ) );
	strRunning = szBuffer;
}

// used by the application object to pass in the command line arguments (if there were any)
void CTimeClockDlg::SetCmdLine ( LPCSTR lpcstrCmdLine )
{
	m_lpcstrCmdLine = lpcstrCmdLine;
}

// send time totals to printer
void CTimeClockDlg::OnPrintreport() 
{
	CPrintPropertiesDlg dlgPrnProp;
	CDC dc;
	CPrintDialog dlg ( FALSE );
	DOCINFO di;

	// temporarily gray the print button
	( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( FALSE );

	// compute each daily total for the printout
	dlgPrnProp . SetMonTotal ( GetTotalTimeFor ( CString ( "Mon" ) ) );
	dlgPrnProp . SetTueTotal ( GetTotalTimeFor ( CString ( "Tue" ) ) );
	dlgPrnProp . SetWedTotal ( GetTotalTimeFor ( CString ( "Wed" ) ) );
	dlgPrnProp . SetThuTotal ( GetTotalTimeFor ( CString ( "Thu" ) ) );
	dlgPrnProp . SetFriTotal ( GetTotalTimeFor ( CString ( "Fri" ) ) );
	dlgPrnProp . SetSatTotal ( GetTotalTimeFor ( CString ( "Sat" ) ) );
	dlgPrnProp . SetSunTotal ( GetTotalTimeFor ( CString ( "Sun" ) ) );

	if ( dlgPrnProp . DoModal () == IDOK ) { // user pressed OK...

		// save before printing
		if ( ! m_strTimeCardFilename . IsEmpty () ) {
			CFile cfSettingsFile ( m_strTimeCardFilename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite );
			CArchive ar ( &cfSettingsFile, CArchive::store );
			Serialize ( ar );
		}

		// prep the DOCINFO struct
		::ZeroMemory ( &di, sizeof ( DOCINFO ) );
		di . cbSize = sizeof ( DOCINFO );
		di . lpszDocName = LPCTSTR ( m_strTimeCardFilename );

		dlg . GetDefaults ();
		
		if ( dc . Attach ( dlg . GetPrinterDC () ) ) { // attatch the printer DC

			if ( dc . StartDoc ( &di ) > 0 ) { // Start the print job

				dc . StartPage (); // start the first page
				if ( DoOutputToDC ( dc, dlgPrnProp ) ) { // do all printing with this call

					if ( dc . EndPage () > 0 ) { // end the page
						dc . EndDoc (); // end the print job
						AfxMessageBox ( "Print Job Complete", MB_ICONINFORMATION );
					}
					else { // WINDOWS error printing
						dc . AbortDoc ();
						AfxMessageBox ( "Encountered Error While Printing\nPrint Job Aborted", MB_ICONEXCLAMATION );
					}

				}
				else { // APPLICATION error printing
					dc . AbortDoc ();
					AfxMessageBox ( "Encountered Error While Printing\nPrint Job Aborted", MB_ICONEXCLAMATION );
				}

			}
			else { // failure starting print job
				AfxMessageBox ( "Encountered Error While Attempting To Start Print Job\nPrint Job Aborted", MB_ICONEXCLAMATION );
			}

		}
		else { // failure attatching print DC
			AfxMessageBox ( "Encountered Error Attaching To Default Printer\nPrint Job Aborted", MB_ICONEXCLAMATION );
		}

	}

	// finished printing, re-enable print button
	( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( TRUE );
	return;
}

// WARNING: This is a HACK.  I was too lazy to implement print scaling and printer resolution.
// My printer is set to 600dpi res (oh well).  If yours isn't change this number, or do this method right.
//
// ItoD means "Inches to Dots" - printer units are in Dots.  This method changes INCHES to PRINTER DOTS.
int CTimeClockDlg::ItoD ( double dInches )
{
	double dResolution = 600.0, dScalingFactor = 1.0; // jeez this is SUCH a hack!

	return int ( dInches * dResolution * dScalingFactor );
}

// print workhorse.  this method does ALL printing.
//
// This method is heaven for people who love abstract object computation/processing using overloaded methods.
// Personally, this method was a pain in the ass to implement while maintaining complete abstraction.
BOOL CTimeClockDlg::DoOutputToDC ( CDC& dc, CPrintPropertiesDlg& dlgPrnProp )
{
	const int nNumDaysInWeek = 7; // number of boxes/days in the week
	const double dNumTopFields = 2.0; // number of fields ABOVE the "box array"
	const double dNumBottomFields = 3.0; // number of fields BELOW the "box array"
	int nIdx; // evil loop counter
	double dIdx; // offset counter (inches)
	double dBoxWidth = 1.0; // width of a box (inches).  for 5 boxes: use 1.5 for 'dBoxWidth'
	double dSmallBoxHeight = 0.25, dLargeBoxHeight = 1.5; // height of a box (inches)
	CPoint cpOrigin		( 100, 200 ); // upper left origin of the "box array"
	CSize csLargeBox	( ItoD ( dBoxWidth ), ItoD ( dLargeBoxHeight ) ); // dimensions of the large component of a box
	CSize csSmallBox	( ItoD ( dBoxWidth ), ItoD ( dSmallBoxHeight ) ); // dimensions of the small component of a box
	CSize csNameBox		( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumTopFields ), ItoD ( dSmallBoxHeight ) ); // dimensions of the "Name" field
	CSize csWeekBox		( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumTopFields ), ItoD ( dSmallBoxHeight ) ); // dimensions of the "Week" field
	CSize csVacationBox	( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), ItoD ( dSmallBoxHeight ) ); // dimensions of the "Vacation" field
	CSize csSickBox		( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), ItoD ( dSmallBoxHeight ) ); // dimensions of the "Sick" field
	CSize csOtherBox	( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), ItoD ( dSmallBoxHeight ) ); // dimensions of the "Other" field
	CString
		straWeekDay	[ nNumDaysInWeek ] = { // array of weekday header values
			"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
		},
		straWeekdayValue [ nNumDaysInWeek ] = { // array of weekday total time values (shown/modified on print properties dialog)
			dlgPrnProp . GetMonTotal (),
			dlgPrnProp . GetTueTotal (),
			dlgPrnProp . GetWedTotal (), 
			dlgPrnProp . GetThuTotal (), 
			dlgPrnProp . GetFriTotal (), 
			dlgPrnProp . GetSatTotal (), 
			dlgPrnProp . GetSunTotal () 
		};

	// The position of each element printed to the page is represented by an MFC CPoint/CSize/CRect object,
	// and is calculated using the arithmetic operators overloaded for those objects, and is offset from
	// 'cpOrigin'.  I don't have the time to explain each one of the computations/offsets computed below,
	// but a careful investigation will reveal all (for those who are remotely interested).

	// put the "Name" field on the page
	dc . DrawText ( 
		CString ( "Name: " ) + m_strName, 
		LPRECT (
			CRect ( 
				cpOrigin - CSize ( 0, ItoD ( 0.25 ) ), 
				csNameBox
			)
		), 
		DT_SINGLELINE | DT_LEFT | DT_VCENTER 
	);
	
	// put the "Week" field on the page
	dc . DrawText ( 
		CString ( "Week: " ) + m_strWeek, 
		LPRECT ( 
			CRect ( 
				cpOrigin - CSize ( 0, ItoD ( 0.25 ) ), 
				csWeekBox 
			) + 
				CSize ( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumTopFields ), 0 ) 
		), 
		DT_SINGLELINE | DT_RIGHT | DT_VCENTER 
	); 

	// draw all 7 boxes on the page along with weekday text headings (Mon, Tue, Wed...etc), and total times
	for ( nIdx = 0, dIdx = 0.0 ; nIdx < nNumDaysInWeek ; nIdx ++, dIdx += dBoxWidth ) {
		
		// put the daily box (large and small components) on the page
		dc . Rectangle ( LPCRECT ( CRect ( cpOrigin, csLargeBox ) + CSize ( ItoD ( dIdx ), 0 ) ) );
		dc . Rectangle ( LPCRECT ( CRect ( cpOrigin, csSmallBox ) + CSize ( ItoD ( dIdx ), 0 ) ) );
		
		// draw the weekday text heading inside the small box component
		dc . DrawText ( 
			straWeekDay [ nIdx ], 
			LPRECT ( 
				CRect ( 
					cpOrigin, 
					csSmallBox 
				) + 
					CSize ( ItoD ( dIdx ), 0 ) 
			), 
			DT_SINGLELINE | DT_CENTER | DT_VCENTER
		);

		// draw the total time for the weekday inside the large box component
		dc . DrawText ( 
			straWeekdayValue [ nIdx ], 
			LPRECT ( 
				CRect ( 
					cpOrigin, 
					csSmallBox 
				) + 
					CSize ( ItoD ( dIdx ), ItoD ( dSmallBoxHeight ) ) + 
					CSize ( 0, ItoD ( dSmallBoxHeight ) ) + 
					CSize ( 0, ItoD ( dSmallBoxHeight ) ) 
			), 
			DT_SINGLELINE | DT_CENTER | DT_VCENTER
		);  

	}

	// put the "Vacation" field on the page
	dc . DrawText ( 
		CString ( "Vacation: " ) + m_strVacation, 
		LPRECT ( 
			CRect ( 
				cpOrigin + CSize ( 0, ItoD ( dLargeBoxHeight ) ), 
				csVacationBox
			) 
		), 
		DT_SINGLELINE | DT_LEFT | DT_VCENTER
	);

	// put the "Sick" field on the page
	dc . DrawText ( 
		CString ( "    Sick: " ) + m_strSick, 
		LPRECT ( 
			CRect ( 
				cpOrigin + CSize ( 0, ItoD ( dLargeBoxHeight ) ), 
				csSickBox 
			) +
				CSize ( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), 0 )
		), 
		DT_SINGLELINE | DT_LEFT | DT_VCENTER 
	);

	// put the "Other" field on the page
	dc . DrawText ( 
		CString ( "   Other: " ) + m_strOther, 
		LPRECT ( 
			CRect ( 
				cpOrigin + CSize ( 0, ItoD ( dLargeBoxHeight ) ), 
				csOtherBox 
			) +
				CSize ( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), 0 ) + 
				CSize ( ItoD ( dBoxWidth * double ( nNumDaysInWeek ) / dNumBottomFields ), 0 ) 
		), 
		DT_SINGLELINE | DT_LEFT | DT_VCENTER 
	); 

	return TRUE;
}

// return the 00:00 (hh:mm) (SECONDS ROUNDED TO THE NEAREST HALF MINUTE) total time for any given day (monday thru sunday)
CString& CTimeClockDlg::GetTotalTimeFor ( CString& strCalcDay )
{
	CString strListDay;
	static CString strRunningTotal;
	char szBuffer [ 256 ];
	POSITION positionTimesListPos;
	time_t time_tCurrent, time_tLast = 0;
	double dTotal = 0.0;
	DWORD dwNumTimeCardEntries = 0;
	double dTimeDiff = 0.0, dHours = 0.0, dMinutes = 0.0, dSeconds = 0.0;

	// set the list iterator value 'positionTimesListPos' to the first element
	positionTimesListPos = m_listTimes . GetHeadPosition ();

	while ( positionTimesListPos ) { // while there are elements in the list...
		
		// get a time value, and convert it to a string
		time_tCurrent = m_listTimes . GetNext ( positionTimesListPos );
		strftime ( szBuffer, sizeof ( szBuffer ), "%a", localtime ( &time_tCurrent ) );
		strListDay = szBuffer;

		// if the day from the time value matches the day we are calculating for, increment the total
		if ( strListDay == strCalcDay ) {
			if ( ( dwNumTimeCardEntries % 2 ) )
				dTotal += difftime ( time_tCurrent, time_tLast );
			time_tLast = time_tCurrent;
			dwNumTimeCardEntries ++;
		}

	}

	if ( ( dHours = dTotal / 3600.0 ) < 1.0 ) // less than one hour
		dHours = 0.0;
	if ( ( dMinutes = ( fmod ( dTotal, 3600.0 ) ) / 60.0 ) < 1.0 ) // less than one minute
		dMinutes = 0.0;
	if ( ( dSeconds = fmod ( fmod ( dTotal, 3600.0 ), 60.0 ) ) < 1.0 ) // less than one second
		dSeconds = 0.0;

	( dSeconds > 30.0 ) ? // round to nearest half minute
		sprintf ( szBuffer, "%.2i:%.2i", int ( dHours ), int ( dMinutes + 1.0 ) ):
		sprintf ( szBuffer, "%.2i:%.2i", int ( dHours ), int ( dMinutes ) );
	
	strRunningTotal = szBuffer;

	return strRunningTotal;	
}

// called when a file is dropped on the dialog
void CTimeClockDlg::OnDropFiles(HDROP hDropInfo) 
{
	char szBuffer [ 256 ];

	if ( DragQueryFile ( hDropInfo, 0, szBuffer, 256 ) )
		LoadCard ( CString ( szBuffer ) );
	
	CDialog::OnDropFiles(hDropInfo);
}

// called to reset this object to a pristine state
void CTimeClockDlg::Reset()
{
	// clear counters, time values, containers, controls
	m_dwNumTimeCardEntries = 0;
	m_time_tTotal = 0;
	m_time_tLast = 0;
	m_listctlTimeCard . DeleteAllItems ();
	m_listTimes . RemoveAll ();

	// clear strings
	m_strTimeCardFilename = _T("");
	m_strName = _T("");
	m_strWeek = _T("");
	m_strVacation = _T("");
	m_strSick = _T("");
	m_strOther = _T("");

	// clear edit controls on dialog
	SetDlgItemText ( IDC_TIMECARDFILE, "" );
	SetDlgItemText ( IDC_NAME, "" );
	SetDlgItemText ( IDC_WEEK, "" );
	SetDlgItemText ( IDC_VACATION, "" );
	SetDlgItemText ( IDC_SICK, "" );
	SetDlgItemText ( IDC_OTHER, "" );

	// disable controls that have no business being enabled when there is no data
	( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_PUNCHINOUT ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_TIMECARD ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_NAME ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_WEEK ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_VACATION ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_SICK ) ) -> EnableWindow ( FALSE );
	( GetDlgItem ( IDC_OTHER ) ) -> EnableWindow ( FALSE );
}

// double-click on the list control, this method is responsible for UNDO'ing the last
// clock punch.  it removes the last item added to the "times list" container, and
// causes the list control contents, and object totals to be re-loaded and calculated
// based on the modified "times list"
void CTimeClockDlg::OnDblclkTimecard(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if ( m_dwNumTimeCardEntries && ( ! m_strTimeCardFilename . IsEmpty () ) ) {

		m_listTimes . RemoveTail (); // remove the last "time" added to the container

		// reset object state properties/controls that are "time list" dependent
		m_dwNumTimeCardEntries = 0;
		m_time_tTotal = 0;
		m_time_tLast = 0;
		m_listctlTimeCard . DeleteAllItems ();

		// re-calculate object state properties, reload the list control based on the new
		// contents of the "time list" container
		DoTimeListEntries ();
	}

	*pResult = 0;
}

void CTimeClockDlg::DoTimeListEntries ()
{
	CString strDate, strTime, strDailyTotal, strRunningTotal;
	char szBuffer [ 256 ];
	POSITION positionTimesListPos;
	time_t time_tCurrentTime;
	BOOL bIn = TRUE;

	// set the list iterator value 'positionTimesListPos' to the first element
	positionTimesListPos = m_listTimes . GetHeadPosition ();

	while ( positionTimesListPos ) { // while there are elements in the list...

		// get a time value, and convert it to a string
		time_tCurrentTime = m_listTimes . GetNext ( positionTimesListPos );
		strftime ( szBuffer, sizeof ( szBuffer ), "%a %m/%d/%y", localtime ( &time_tCurrentTime ) );
		strDate = szBuffer;
		strftime ( szBuffer, sizeof ( szBuffer ), "%H:%M:%S", localtime ( &time_tCurrentTime ) );
		strTime = szBuffer;

		if ( bIn ) { // the time is an IN time
			// insert an entry into the list control, and use an IN icon
			m_listctlTimeCard . InsertItem ( m_dwNumTimeCardEntries, strDate, 0 );
			m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 1, LPCTSTR ( strTime ) );
			bIn = FALSE; // keep track of whether we are IN or OUT
		}
		else { // the time is an OUT time
			// insert an entry into the list control, and use an OUT icon
			m_listctlTimeCard . InsertItem ( m_dwNumTimeCardEntries, strDate, 1 );
			m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 1, LPCTSTR ( strTime ) );
			bIn = TRUE; // keep track of whether we are IN or OUT
		}

		// for every 2nd entry, compute the difference totals (e.g. running time total, etc)
		// and insert them into the right-most columns in the list control.
		if ( ( m_dwNumTimeCardEntries % 2 ) ) {
			GetEndTimes ( time_tCurrentTime, strDailyTotal, strRunningTotal );
			m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 2, LPCTSTR ( strDailyTotal ) );
			m_listctlTimeCard . SetItemText ( m_dwNumTimeCardEntries, 3, LPCTSTR ( strRunningTotal ) );
		}
		m_time_tLast = time_tCurrentTime; // save the current time, to be used in difference calculations for time accrual
		m_dwNumTimeCardEntries ++; // accrue the total entries
	}

	// if the last entry was an even entry, we are OUT, if not we are IN, set the text on the "PUNCH IN/OUT" button accordingly
	( m_dwNumTimeCardEntries % 2 ) ?
		( GetDlgItem ( IDC_PUNCHINOUT ) ) -> SetWindowText ( "PUNCH OUT" ):
		( GetDlgItem ( IDC_PUNCHINOUT ) ) -> SetWindowText ( "PUNCH IN" );
	
	// if there are at least 2 entries, enable the "PRINT" button
	( m_dwNumTimeCardEntries > 1 ) ?
		( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( TRUE ):
		( GetDlgItem ( IDC_PRINTREPORT ) ) -> EnableWindow ( FALSE );
	
	// enable the "PUNCH IN/OUT" button, the list control, and edit controls
	( GetDlgItem ( IDC_PUNCHINOUT ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_TIMECARD ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_NAME ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_WEEK ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_VACATION ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_SICK ) ) -> EnableWindow ( TRUE );
	( GetDlgItem ( IDC_OTHER ) ) -> EnableWindow ( TRUE );

	return;
}
