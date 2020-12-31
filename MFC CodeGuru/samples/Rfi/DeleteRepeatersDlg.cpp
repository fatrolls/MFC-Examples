// DeleteRepeatersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rfi.h"
#include "DeleteRepeatersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteRepeatersDlg dialog


CDeleteRepeatersDlg::CDeleteRepeatersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteRepeatersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteRepeatersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bRecordsWereDeleted = FALSE;
}


void CDeleteRepeatersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteRepeatersDlg)
	DDX_Control(pDX, IDC_DELETE_REPEATER_LIST, m_lcRepeaterList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteRepeatersDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteRepeatersDlg)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_DELETE_REPEATER_LIST, OnColumnclickRepeaterList)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(NM_CLICK, IDC_DELETE_REPEATER_LIST, OnClickRepeaterList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteRepeatersDlg message handlers

BOOL CDeleteRepeatersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// set up the list control's icons
	m_lgImageList . Create ( 32, 32, FALSE, 2, 0 );
	m_smImageList . Create ( 16, 16, FALSE, 2, 0 );
	m_lgImageList . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_REPEATER ) ) );
	m_smImageList . Add ( ::LoadIcon ( AfxGetInstanceHandle (), MAKEINTRESOURCE ( IDI_REPEATER ) ) );
	m_lcRepeaterList . SetImageList ( &m_lgImageList, LVSIL_NORMAL );
	m_lcRepeaterList . SetImageList ( &m_smImageList, LVSIL_SMALL );
	
	// set up the list control's columns
	m_lcRepeaterList . InsertColumn ( 0, "ID", LVCFMT_CENTER, 60 );
	m_lcRepeaterList . InsertColumn ( 1, "Frequency", LVCFMT_LEFT, 65 );
	m_lcRepeaterList . InsertColumn ( 2, "Callsign", LVCFMT_LEFT, 65 );
	m_lcRepeaterList . InsertColumn ( 3, "Input", LVCFMT_LEFT, 55 );
	m_lcRepeaterList . InsertColumn ( 4, "City", LVCFMT_LEFT, 145 );
	m_lcRepeaterList . InsertColumn ( 5, "State", LVCFMT_LEFT, 100 );

	// the load may take a while, there is no splash screen for the user to look at, so let's
	// show the user interface element so they can look at that while the load is completing.
	ShowWindow ( SW_SHOW );

	// load the database contents into the list control
	LoadList ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// loads the main listbox with the contents of the database
void CDeleteRepeatersDlg::LoadList()
{
	char szBuffer [ 256 ];

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
	catch ( CDaoException* e ) { // catch database exceptions
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

	return;
}

// we will let the record set do all the work of sorting the main listbox
void CDeleteRepeatersDlg::OnColumnclickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult) 
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
void CDeleteRepeatersDlg::LoadSortList ( CString& strSortBy )
{
	// clear out the listbox
	m_lcRepeaterList . DeleteAllItems ();
	
	m_setComplete . m_strSort = strSortBy; // set the recordset's sort parameter
	LoadList (); // re-load the database contents

	// clear status field
	SetDlgItemText ( IDC_DELETE_STATUS, "" );
	return;
}

// deleting records from the database
void CDeleteRepeatersDlg::OnDelete() 
{
	CString strRecordIdQuery;
	int nItemIndex = -1;


	// if there's an element selected in the listbox
	if ( ( m_lcRepeaterList . GetNextItem ( -1, LVNI_SELECTED ) ) != -1 ) {
		try {
			// open the database
			if ( ! m_setComplete . IsOpen () )
				m_setComplete . Open ();
			// cycle through the selected listbox elements.
			while ( ( nItemIndex = m_lcRepeaterList . GetNextItem ( nItemIndex, LVNI_SELECTED ) ) != -1 ) {
				strRecordIdQuery =
					CString ( "[ID] = " ) +
					CString ( m_lcRepeaterList . GetItemText ( nItemIndex, 0 ) ); // put the ID into the query string
				if ( m_setComplete . FindFirst ( strRecordIdQuery ) ) { // looking for this ID in the database, ID is a unique 'autonumber'
					m_setComplete . Delete (); // delete the record
					m_setComplete . MoveFirst (); // move back to the first record
					m_bRecordsWereDeleted = TRUE; // make a note that we changed the database
					SetDlgItemText ( IDC_DELETE_STATUS, "Repeater Deleted From Database" ); // set the status field
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
		if ( m_bRecordsWereDeleted ) {
			LoadList (); // reload if necessary
		}
	}
	else { // there aren't any items selected in the list control
		AfxMessageBox ( "No repeaters selected", MB_ICONEXCLAMATION );
	}

	return;
}

// clear the status field if the user clicks the list control
void CDeleteRepeatersDlg::OnClickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetDlgItemText ( IDC_DELETE_STATUS, "" );
	
	*pResult = 0;
}
