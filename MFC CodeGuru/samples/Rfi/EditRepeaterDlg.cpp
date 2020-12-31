// EditRepeaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rfi.h"
#include "EditRepeaterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditRepeaterDlg dialog


CEditRepeaterDlg::CEditRepeaterDlg(CString& strRecordId, CWnd* pParent /*=NULL*/)
	: CDialog(CEditRepeaterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditRepeaterDlg)
	m_strCallsign = _T("");
	m_strCity = _T("");
	m_strFrequency = _T("");
	//}}AFX_DATA_INIT
	m_strState = _T("");
	m_strInput = _T("");
	m_strSavedState = _T("");
	m_strSavedInput = _T("");
	m_strRecordId = strRecordId;
}


void CEditRepeaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditRepeaterDlg)
	DDX_Control(pDX, IDC_EDIT_STATE, m_cbState);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_cbInput);
	DDX_Text(pDX, IDC_EDIT_CALLSIGN, m_strCallsign);
	DDV_MaxChars(pDX, m_strCallsign, 255);
	DDX_Text(pDX, IDC_EDIT_CITY, m_strCity);
	DDV_MaxChars(pDX, m_strCity, 255);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_strFrequency);
	DDV_MaxChars(pDX, m_strFrequency, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditRepeaterDlg, CDialog)
	//{{AFX_MSG_MAP(CEditRepeaterDlg)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_EN_CHANGE(IDC_EDIT_CALLSIGN, OnChangeEditCallsign)
	ON_EN_CHANGE(IDC_EDIT_CITY, OnChangeEditCity)
	ON_EN_CHANGE(IDC_EDIT_FREQUENCY, OnChangeEditFrequency)
	ON_CBN_SELCHANGE(IDC_EDIT_INPUT, OnSelchangeEditInput)
	ON_CBN_SELCHANGE(IDC_EDIT_STATE, OnSelchangeEditState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditRepeaterDlg message handlers

// the user hit the "reset form" button, undo all changes the user made, and revert
// all values to their un-changed state.
void CEditRepeaterDlg::OnReset() 
{
	// revert the edit controls
	SetDlgItemText ( IDC_EDIT_CALLSIGN, m_strCallsign );
	SetDlgItemText ( IDC_EDIT_CITY, m_strCity );
	SetDlgItemText ( IDC_EDIT_FREQUENCY, m_strFrequency );
	
	// revert the "state" droplist
	( m_cbState . FindStringExact ( 0, m_strSavedState ) == CB_ERR ) ?
		( ( CComboBox* ) ( GetDlgItem ( IDC_EDIT_STATE ) ) ) -> SetCurSel ( -1 ):
		( ( CComboBox* ) ( GetDlgItem ( IDC_EDIT_STATE ) ) ) -> SetCurSel ( m_cbState . FindStringExact ( 0, m_strSavedState ) );
	
	// revert the "input" droplist
	( m_cbInput . FindStringExact ( 0, m_strSavedInput ) == CB_ERR ) ?
		( ( CComboBox* ) ( GetDlgItem ( IDC_EDIT_INPUT ) ) ) -> SetCurSel ( -1 ):
		( ( CComboBox* ) ( GetDlgItem ( IDC_EDIT_INPUT ) ) ) -> SetCurSel ( m_cbInput . FindStringExact ( 0, m_strSavedInput ) );

	// disable the "update" button (nothing to update)
	( GetDlgItem ( IDOK ) ) -> EnableWindow ( FALSE );
	
	// set the status field
	SetDlgItemText ( IDC_EDIT_STATUS, "Form Reset" );
  
	return;
}

// clear the status field on changes to the dialog controls
void CEditRepeaterDlg::OnChangeEditCallsign() 
{
	( GetDlgItem ( IDOK ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_EDIT_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CEditRepeaterDlg::OnChangeEditCity() 
{
	( GetDlgItem ( IDOK ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_EDIT_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CEditRepeaterDlg::OnChangeEditFrequency() 
{
	( GetDlgItem ( IDOK ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_EDIT_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CEditRepeaterDlg::OnSelchangeEditInput() 
{
	if ( ( m_cbInput . GetCurSel () ) !=  CB_ERR )
		m_cbInput . GetLBText ( m_cbInput . GetCurSel (), m_strInput );

	( GetDlgItem ( IDOK ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_EDIT_STATUS, "" );
}

// clear the status field on changes to the dialog controls
void CEditRepeaterDlg::OnSelchangeEditState() 
{
	if ( ( m_cbState . GetCurSel () ) !=  CB_ERR )
		m_cbState . GetLBText ( m_cbState . GetCurSel (), m_strState );

	( GetDlgItem ( IDOK ) ) -> EnableWindow ( TRUE );
	SetDlgItemText ( IDC_EDIT_STATUS, "" );
}

// initial setup
BOOL CEditRepeaterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// initialize controls that DDX doesn't do right (like droplists)
	( m_cbState . FindStringExact ( 0, m_strState ) == CB_ERR ) ?
		m_cbState . SetCurSel ( -1 ):
		m_cbState . SetCurSel ( m_cbState . FindStringExact ( 0, m_strState ) );
	( m_cbInput . FindStringExact ( 0, m_strInput ) == CB_ERR ) ?
		m_cbInput . SetCurSel ( -1 ):
		m_cbInput . SetCurSel ( m_cbInput . FindStringExact ( 0, m_strInput ) );

	// save the values for the listboxes in case the user wants to undo.
	m_strSavedState = m_strState;
	m_strSavedInput = m_strInput;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
