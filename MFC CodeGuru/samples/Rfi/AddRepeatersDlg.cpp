// AddRepeatersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rfi.h"
#include "AddRepeatersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddRepeatersDlg dialog


CAddRepeatersDlg::CAddRepeatersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddRepeatersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddRepeatersDlg)
	//}}AFX_DATA_INIT
	m_bRecordsWereAdded = FALSE;
}


void CAddRepeatersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRepeatersDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRepeatersDlg, CDialog)
	//{{AFX_MSG_MAP(CAddRepeatersDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_EN_CHANGE(IDC_ADD_CALLSIGN, OnChangeCallsign)
	ON_EN_CHANGE(IDC_ADD_CITY, OnChangeCity)
	ON_EN_CHANGE(IDC_ADD_FREQUENCY, OnChangeFrequency)
	ON_CBN_SELCHANGE(IDC_ADD_INPUT, OnSelchangeInput)
	ON_CBN_SELCHANGE(IDC_ADD_STATE, OnSelchangeState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddRepeatersDlg message handlers

BOOL CAddRepeatersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// add a record to the database
void CAddRepeatersDlg::OnAdd() 
{
	CString strCallsign = "", strFrequency = "", strCity = "";
	CString strState = "", strInput = "";

	// get the contents of the dialog's record parameter entry elements.
	GetDlgItemText ( IDC_ADD_CALLSIGN, strCallsign );
	GetDlgItemText ( IDC_ADD_FREQUENCY, strFrequency );
	GetDlgItemText ( IDC_ADD_CITY, strCity );
	if ( ( ( ( CComboBox* ) GetDlgItem ( IDC_ADD_STATE ) ) -> GetCurSel () ) !=  CB_ERR )
		( ( CComboBox* ) GetDlgItem ( IDC_ADD_STATE ) ) -> GetLBText (
			( ( CComboBox* ) GetDlgItem ( IDC_ADD_STATE ) ) -> GetCurSel (),
			strState
		);
	if ( ( ( ( CComboBox* ) GetDlgItem ( IDC_ADD_INPUT ) ) -> GetCurSel () ) !=  CB_ERR )
		( ( CComboBox* ) GetDlgItem ( IDC_ADD_INPUT ) ) -> GetLBText (
			( ( CComboBox* ) GetDlgItem ( IDC_ADD_INPUT ) ) -> GetCurSel (),
			strInput
		);

	// all fields MUST contain a value
	if ( strCallsign . IsEmpty () ) {
		AfxMessageBox ( "You must supply a \"Callsign\"", MB_ICONEXCLAMATION );
		return;
	}
	if ( strFrequency . IsEmpty () ) {
		AfxMessageBox ( "You must supply a \"Frequency\"", MB_ICONEXCLAMATION );
		return;
	}
	if ( strCity . IsEmpty () ) {
		AfxMessageBox ( "You must supply a \"City\"", MB_ICONEXCLAMATION );
		return;
	}
	if ( strState . IsEmpty () ) {
		AfxMessageBox ( "You must choose a \"State\"", MB_ICONEXCLAMATION );
		return;
	}
	if ( strInput . IsEmpty () ) {
		AfxMessageBox ( "You must choose an \"Input\"", MB_ICONEXCLAMATION );
		return;
	}

	try {
		if ( ! m_setComplete . IsOpen () ) // if the recordset isn't already open..
			m_setComplete . Open (); // open it
		m_setComplete . AddNew (); // begin the add

		m_setComplete . m_strCallsign = strCallsign; // change the recordset members
		m_setComplete . m_strFrequency = strFrequency;
		m_setComplete . m_strCity = strCity;
		m_setComplete . m_strState = strState;
		m_setComplete . m_strInput = strInput;

		m_setComplete . Update (); // complete the add by doing an update
		m_setComplete . Close (); // close the recordset
	
		m_bRecordsWereAdded = TRUE; // make a note that we changed the database
	}
	catch ( CDaoException* e ) { // catch DAO exceptions
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

	// after the user "adds" a record, re-set the form for another "add"
	OnReset ();
	// set the status field
	SetDlgItemText ( IDC_ADD_STATUS, "Repeater Added To Database" );

	return;
}

// the user hit the "reset form" button, undo all changes the user made, and revert
// all values to their un-changed state.
void CAddRepeatersDlg::OnReset() 
{
	// empty the edit controls
	SetDlgItemText ( IDC_ADD_CALLSIGN, "" );
	SetDlgItemText ( IDC_ADD_CITY, "" );
	SetDlgItemText ( IDC_ADD_FREQUENCY, "" );
	
	// empty the "state" droplist
	( ( CComboBox* ) ( GetDlgItem ( IDC_ADD_STATE ) ) ) -> SetCurSel ( -1 );

	// empty the "input" droplist
	( ( CComboBox* ) ( GetDlgItem ( IDC_ADD_INPUT ) ) ) -> SetCurSel ( -1 );

	// disable the "add" button (nothing to add)
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( FALSE );
	
	// set the status field
	SetDlgItemText ( IDC_ADD_STATUS, "Form Reset" );
   
	return;
}

// clear the status field on changes to the dialog controls
void CAddRepeatersDlg::OnChangeCallsign() 
{
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_ADD_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CAddRepeatersDlg::OnChangeCity() 
{
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_ADD_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CAddRepeatersDlg::OnChangeFrequency() 
{
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_ADD_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CAddRepeatersDlg::OnSelchangeInput() 
{
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_ADD_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CAddRepeatersDlg::OnSelchangeState() 
{
	( GetDlgItem ( IDC_ADD ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_ADD_STATUS, "" );
}
