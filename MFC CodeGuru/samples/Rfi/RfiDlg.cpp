// RfiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rfi.h"

#include "AddRepeatersDlg.h"
#include "DeleteRepeatersDlg.h"
#include "EditRepeaterDlg.h"
#include "Splash1.h"

#include "RfiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_TRAYNOTIFY WM_USER + 100

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
// CRfiDlg dialog

CRfiDlg::CRfiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRfiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRfiDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRfiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRfiDlg)
	DDX_Control(pDX, IDC_REPEATER_LIST, m_lcRepeaterList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRfiDlg, CDialog)
	//{{AFX_MSG_MAP(CRfiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_REPEATERS, OnAddRepeaters)
	ON_BN_CLICKED(IDC_DELETE_REPEATERS, OnDeleteRepeaters)
	ON_NOTIFY(NM_DBLCLK, IDC_REPEATER_LIST, OnDblclkRepeaterList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_REPEATER_LIST, OnColumnclickRepeaterList)
	ON_BN_CLICKED(IDC_EXECUTE_QUERY, OnExecuteQuery)
	ON_BN_CLICKED(IDC_CLEAR_QUERY, OnClearQuery)
	ON_BN_CLICKED(IDC_EDIT_REPEATER, OnEditRepeater)
	ON_WM_CREATE()
	ON_COMMAND(IDC_SHOWMAIN, OnShowmain)
	ON_COMMAND(IDC_HIDEMAIN, OnHidemain)
	//}}AFX_MSG_MAP
	ON_MESSAGE ( WM_TRAYNOTIFY, OnTrayNotify ) // tray icon notification
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRfiDlg message handlers

BOOL CRfiDlg::OnInitDialog()
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

	// set up main list box image list
	m_lgImageList . Create ( 32, 32, FALSE, 2, 0 );
	m_smImageList . Create ( 16, 16, FALSE, 2, 0 );
	m_lgImageList . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_REPEATER ) ) );
	m_smImageList . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_REPEATER ) ) );
	m_lcRepeaterList . SetImageList ( &m_lgImageList, LVSIL_NORMAL );
	m_lcRepeaterList . SetImageList ( &m_smImageList, LVSIL_SMALL );
	
	// set up main list box columns
	m_lcRepeaterList . InsertColumn ( 0, "ID", LVCFMT_CENTER, 60 );
	m_lcRepeaterList . InsertColumn ( 1, "Frequency", LVCFMT_LEFT, 65 );
	m_lcRepeaterList . InsertColumn ( 2, "Callsign", LVCFMT_LEFT, 65 );
	m_lcRepeaterList . InsertColumn ( 3, "Input", LVCFMT_LEFT, 55 );
	m_lcRepeaterList . InsertColumn ( 4, "City", LVCFMT_LEFT, 145 );
	m_lcRepeaterList . InsertColumn ( 5, "State", LVCFMT_LEFT, 100 );

	// show the splash screen
	CSplashWnd::ShowSplashScreen ( this );

	// load the database contents into the list control
	LoadList ();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRfiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ( nID == SC_MINIMIZE )
	{
		OnHidemain (); // get into tray and don't leave task bar button
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRfiDlg::OnPaint() 
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
HCURSOR CRfiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// adding entries to database
void CRfiDlg::OnAddRepeaters() 
{
	CAddRepeatersDlg dlgAddRepeaters;

	// show "add" dialog
	dlgAddRepeaters . DoModal ();
	
	// find out if "add" dialog did any database updates
	if ( dlgAddRepeaters . RecordsWereAdded () )
		LoadList (); // if so, re-load list control from new database contents

	return;
}

// deleting entries from database
void CRfiDlg::OnDeleteRepeaters() 
{
	CDeleteRepeatersDlg dlgDeleteRepeaters;

	// show "delete" dialog
	dlgDeleteRepeaters . DoModal ();

	// find out if "delete" dialog did any database updates
	if ( dlgDeleteRepeaters . RecordsWereDeleted () )
		LoadList (); // if so, re-load list control from new database contents

	return;
}

// double-clicking main list box edits the selected entry
void CRfiDlg::OnDblclkRepeaterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// call the handler for editing existing database entries
	OnEditRepeater ();
	
	*pResult = 0;
}

// we will let the record set do all the work of sorting the main listbox
void CRfiDlg::OnColumnclickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	// sort based on column that was clicked
	switch ( pNMListView -> iSubItem ) {
		case 0:
			LoadSortList ( CString ( "[ID]" ) );
			break;
		case 1:
			LoadSortList ( CString ( "[Frequency]" ) );
			break;
		case 2:
			LoadSortList ( CString ( "[Callsign]" ) );
			break;
		case 3:
			LoadSortList ( CString ( "[Input]" ) );
			break;
		case 4:
			LoadSortList ( CString ( "[City]" ) );
			break;
		case 5:
			LoadSortList ( CString ( "[State]" ) );
			break;
		default:
			LoadSortList ( CString ( "" ) ); // default: no sort.
			break;
	}
	
	*pResult = 0;
}

// sorted database entries
void CRfiDlg::LoadSortList ( CString& strSortBy )
{
	// clear out the listbox
	m_lcRepeaterList . DeleteAllItems ();
	
	m_setComplete . m_strSort = strSortBy; // set the recordset's sort parameter
	LoadList (); // re-load the database contents

	return;
}

// load based on SQL filter query
void CRfiDlg::LoadFilterList ( CString& strFilterBy )
{
	// clear out the listbox
	m_lcRepeaterList . DeleteAllItems ();
	
	m_setComplete . m_strFilter = strFilterBy; // set the recordset's filter parameter
	LoadList (); // re-load the database contents

	return;
}

// loads the main listbox with the contents of the database
void CRfiDlg::LoadList()
{
	char szBuffer [ 256 ]; // idiot buffer needed by the runtime library calls

	// clear out the listbox
	m_lcRepeaterList . DeleteAllItems ();

	try {
		if ( ! m_setComplete . IsOpen () ) // if the recordset isn't already open...
			m_setComplete . Open (); // open it
		for ( int nListEntry = 0 ; ! m_setComplete . IsEOF () ; nListEntry ++ ) { // for each entry int the database...
			// make an entry in the listbox from the recordset contents
			m_lcRepeaterList . InsertItem ( nListEntry, LPCTSTR ( ltoa ( m_setComplete . m_lID, szBuffer, 10 ) ), 0 );
			m_lcRepeaterList . SetItemText ( nListEntry, 1, LPCTSTR ( m_setComplete . m_strFrequency ) );
			m_lcRepeaterList . SetItemText ( nListEntry, 2, LPCTSTR ( m_setComplete . m_strCallsign ) );
			m_lcRepeaterList . SetItemText ( nListEntry, 3, LPCTSTR ( m_setComplete . m_strInput ) );
			m_lcRepeaterList . SetItemText ( nListEntry, 4, LPCTSTR ( m_setComplete . m_strCity ) );
			m_lcRepeaterList . SetItemText ( nListEntry, 5, LPCTSTR ( m_setComplete . m_strState ) );
			m_setComplete . MoveNext (); // cause the recordset to retrieve the next record from the database for the next loop
		}
		m_setComplete . Close (); // done with the recordset
	}
	catch ( CDaoException* e ) { // catch exceptions thrown by the MFC DAO classes
		char szBuffer [ 256 ];
		CString strExceptDesc =
			CString ( "JET Database Engine Error:\n\n Error Code: " ) +
			CString ( ltoa ( e -> m_pErrorInfo -> m_lErrorCode, szBuffer, 10 ) ) +
			CString ( "\nDescription: " ) +
			CString ( e -> m_pErrorInfo -> m_strDescription );
		AfxMessageBox ( strExceptDesc, MB_ICONEXCLAMATION );
		m_setComplete . Close (); // at least try to close the recordset
		return;
	}

	return;
}

// build an SQL filter query string based on contents of main dialog's filter parameter edit boxes
// and droplist boxes.  Wildcards and Regular expression syntax is supported by the SQL "like" keyword
// upon which this query will be built.
void CRfiDlg::OnExecuteQuery() 
{
	CString strCallsignQuery = "", strFrequencyQuery = "", strCityQuery = "";
	CString strStateQuery = "", strInputQuery = "";
	CString strFilter = "";
	BOOL bFirstSQLOperand =	TRUE;

	// get the contents of the main dialog's query parameter entry elements.
	GetDlgItemText ( IDC_QUERY_CALLSIGN, strCallsignQuery );
	GetDlgItemText ( IDC_QUERY_FREQUENCY, strFrequencyQuery );
	GetDlgItemText ( IDC_QUERY_CITY, strCityQuery );
	if ( ( ( ( CComboBox* ) GetDlgItem ( IDC_QUERY_STATE ) ) -> GetCurSel () ) !=  CB_ERR )
		( ( CComboBox* ) GetDlgItem ( IDC_QUERY_STATE ) ) -> GetLBText (
			( ( CComboBox* ) GetDlgItem ( IDC_QUERY_STATE ) ) -> GetCurSel (),
			strStateQuery
		);
	if ( ( ( ( CComboBox* ) GetDlgItem ( IDC_QUERY_INPUT ) ) -> GetCurSel () ) !=  CB_ERR )
		( ( CComboBox* ) GetDlgItem ( IDC_QUERY_INPUT ) ) -> GetLBText (
			( ( CComboBox* ) GetDlgItem ( IDC_QUERY_INPUT ) ) -> GetCurSel (),
			strInputQuery
		);


	// the next 5 "if" statements determine the status of the 5 filter parameters (first parameter,
	// empty or not, etc), and build an SQL filter string that will be used in the recordset's "filter"
	// parameter upon loading the recordset from the database.  The filter string built here will only
	// consist of the WHERE clause of a valid SQL statement as per the requirements of the DAO recorset
	// filter query scheme (for more info on this, see: DAO, CDaoRecordset).  The resulting string will
	// look something like the following--based on user input:
	//
	//	"[Callsign] Like 'W1kzy' AND [Frequency] Like '147.*' AND [State] Like 'Massachusetts'"


	if ( ! strCallsignQuery . IsEmpty () ) {
		if ( bFirstSQLOperand ) {
			strFilter += CString ( "[Callsign] Like '" ) + strCallsignQuery + CString ( "'" );
			bFirstSQLOperand = FALSE;
		}
		else
			strFilter += CString ( " AND [Callsign] Like '" ) + strCallsignQuery + CString ( "'" );
	}
	
	if ( ! strFrequencyQuery . IsEmpty () ) {
		if ( bFirstSQLOperand ) {
			strFilter += CString ( "[Frequency] Like '" ) + strFrequencyQuery + CString ( "'" );
			bFirstSQLOperand = FALSE;
		}
		else
			strFilter += CString ( " AND [Frequency] Like '" ) + strFrequencyQuery + CString ( "'" );
	}
	
	if ( ! strCityQuery . IsEmpty () ) {
		if ( bFirstSQLOperand ) {
			strFilter += CString ( "[City] Like '" ) + strCityQuery + CString ( "'" );
			bFirstSQLOperand = FALSE;
		}
		else
			strFilter += CString ( " AND [City] Like '" ) + strCityQuery + CString ( "'" );
	}
	
	if ( ! strStateQuery . IsEmpty () ) {
		if ( bFirstSQLOperand ) {
			strFilter += CString ( "[State] Like '" ) + strStateQuery + CString ( "'" );
			bFirstSQLOperand = FALSE;
		}
		else
			strFilter += CString ( " AND [State] Like '" ) + strStateQuery + CString ( "'" );
	}
	
	if ( ! strInputQuery . IsEmpty () ) {
		if ( bFirstSQLOperand ) {
			strFilter += CString ( "[Input] Like '" ) + strInputQuery + CString ( "'" );
			bFirstSQLOperand = FALSE;
		}
		else
			strFilter += CString ( " AND [Input] Like '" ) + strInputQuery + CString ( "'" );
	}
	
	LoadFilterList ( strFilter ); // prep the recordset, and load the database contents into the listbox
}

// reset the contents of the listbox, clearing any query parameters
void CRfiDlg::OnClearQuery() 
{

	SetDlgItemText ( IDC_QUERY_CALLSIGN, "" );
	SetDlgItemText ( IDC_QUERY_CITY, "" );
	SetDlgItemText ( IDC_QUERY_FREQUENCY, "" );
	
	( ( CComboBox* ) ( GetDlgItem ( IDC_QUERY_STATE ) ) ) -> SetCurSel ( -1 );
	( ( CComboBox* ) ( GetDlgItem ( IDC_QUERY_INPUT ) ) ) -> SetCurSel ( -1 );

	LoadFilterList ( CString ( "" ) );

	return;
}

// editing an existing database entry
void CRfiDlg::OnEditRepeater() 
{
	CEditRepeaterDlg* pdlgEditRepeater;
	CString strRecordIdQuery;
	int nItemIndex = -1;
	BOOL bFieldsHaveChanged = FALSE;

	// if there's an element selected in the listbox
	if ( ( m_lcRepeaterList . GetNextItem ( -1, LVNI_SELECTED ) ) != -1 ) {
		try {
			// open the database
			if ( ! m_setComplete . IsOpen () )
				m_setComplete . Open ();
			// cycle through the selected listbox elements (there will only be one for this listbox, it is a single
			// selection only listbox) but for the sake of like-access between all listboxes in this app, and future
			// ease of extension, it will be done with a while loop.
			while ( ( nItemIndex = m_lcRepeaterList . GetNextItem ( nItemIndex, LVNI_SELECTED ) ) != -1 ) {
				strRecordIdQuery =
					CString ( "[ID] = " ) +
					CString ( m_lcRepeaterList . GetItemText ( nItemIndex, 0 ) ); // put the ID into the query string
				if ( m_setComplete . FindFirst ( strRecordIdQuery ) ) { // looking for this ID in the database, ID is a unique 'autonumber'
					// get an "edit" dialog and init the members
					pdlgEditRepeater = new CEditRepeaterDlg ( m_lcRepeaterList . GetItemText ( nItemIndex, 0 ) );
					pdlgEditRepeater -> SetCallsign ( m_setComplete . m_strCallsign );
					pdlgEditRepeater -> SetCity ( m_setComplete . m_strCity );
					pdlgEditRepeater -> SetFrequency ( m_setComplete . m_strFrequency );
					pdlgEditRepeater -> SetState ( m_setComplete . m_strState );
					pdlgEditRepeater -> SetInput ( m_setComplete . m_strInput );
					if ( pdlgEditRepeater -> DoModal () == IDOK ) { // show the dialog
						m_setComplete . Edit (); // begin the record edit
						m_setComplete . m_strCallsign = pdlgEditRepeater -> GetCallsign (); // change the recordset fields
						m_setComplete . m_strCity = pdlgEditRepeater -> GetCity ();
						m_setComplete . m_strFrequency = pdlgEditRepeater -> GetFrequency ();
						m_setComplete . m_strState = pdlgEditRepeater -> GetState ();
						m_setComplete . m_strInput = pdlgEditRepeater -> GetInput ();
						m_setComplete . Update (); // complete the edit by doing an update
						bFieldsHaveChanged = TRUE; // make a note that we have changed the database
					}
					delete pdlgEditRepeater; // get rid of the dialog
				}
				else {
					// if we EVER end up here, either the database is in the crapper, or I will have screwed up horribly--been known to happen from time to time :) ...
					// so let's cover our ass-ets just in case.
					AfxMessageBox ( "Internal failure\n\nCannot find selected repeater in database\nor database is corrupted", MB_ICONSTOP );
				}
			}
			m_setComplete . Close (); // close the database
		}
		catch ( CDaoException* e ) { // yeah, yeah, same comments as all the other "catch" blocks.
			char szBuffer [ 256 ];
			CString strExceptDesc =
				CString ( "JET Database Engine Error:\n\n Error Code: " ) +
				CString ( ltoa ( e -> m_pErrorInfo -> m_lErrorCode, szBuffer, 10 ) ) +
				CString ( "\nDescription: " ) +
				CString ( e -> m_pErrorInfo -> m_strDescription );
			AfxMessageBox ( strExceptDesc, MB_ICONEXCLAMATION );
			m_setComplete . Close ();
			return;
		}
		if ( bFieldsHaveChanged ) {
			LoadList (); // reload if necessary
		}
	}
	else { // there aren't any items selected in the list control
		AfxMessageBox ( "No repeater selected", MB_ICONEXCLAMATION );
	}
	
	return;
}

// this does some necessary setup with the tray icon object.
int CRfiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// assign a menu, icon, tooltip, and handler to the tray icon.
	if ( ! m_classTrayNotifyIcon . Create ( this, IDR_POPUP, "RFI - Repeater Frequency Index", AfxGetApp () -> LoadIcon ( IDI_TRAYICON ), WM_TRAYNOTIFY ) ) {
		AfxMessageBox ( "Failure Creating Tray Icon", MB_ICONSTOP );
		return -1;
	}
	
	return 0;
}

// pass the tray notification message to the tray icon object for handling.
LRESULT CRfiDlg::OnTrayNotify ( WPARAM wParam, LPARAM lParam ) {
  return m_classTrayNotifyIcon . OnTrayNotification ( wParam, lParam );
}

// show the main window.  the tray icon object shows the popup menu 'IDR_POPUP' which
// has a command for calling this handler
void CRfiDlg::OnShowmain() 
{
	ShowWindow ( SW_SHOW );
}

// show the main window.  the tray icon object shows the popup menu 'IDR_POPUP' which
// has a command for calling this handler
void CRfiDlg::OnHidemain() 
{
	ShowWindow ( SW_HIDE );
}

// if stuff like "check marks on the tray icon popup menu" were implemented, the code
// would be here.
void CRfiDlg::OnUpdateShowmain(CCmdUI* pCmdUI) 
{
}

// if stuff like "check marks on the tray icon popup menu" were implemented, the code
// would be here.
void CRfiDlg::OnUpdateHidemain(CCmdUI* pCmdUI) 
{
}
