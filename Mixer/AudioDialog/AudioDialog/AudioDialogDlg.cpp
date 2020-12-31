// -----------------------------------------------------------------------------
// AudioDialogDlg.cpp : implementation file
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "AudioDialog.h"
#include "AudioDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Displacement between control groups
#define	CONTROL_GROUP_OFFSET	105

// Arbitrary start of control ID's for dynamically created controls 
#define IDC_CTRL_ID_START	  6000
// Max ID value for dynamically created controls 6 controls/group, 64 groups 
#define IDC_CTRL_ID_END		  IDC_CTRL_ID_START + 6*64	

// -----------------------------------------------------------------------------
// CAboutDlg dialog used for App About
// -----------------------------------------------------------------------------
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

// -----------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// CAudioDialogDlg dialog
// -----------------------------------------------------------------------------
CAudioDialogDlg::CAudioDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mMixerCount = 0 ;
	mhMixer = NULL ;
	mpCMixer = NULL ;
	mpMixerDlg = NULL ;
	mpDestinationsDlg = NULL ;
	mpConnectionDlg = NULL ;
	mpControlsDlg = NULL ;	
	mpMixerInfo = NULL ;
	mpControlGroup = NULL ;
	mnGroupHorzOffset = CONTROL_GROUP_OFFSET ;
	mnNextResourceID  = IDC_CTRL_ID_START ;
}

// -----------------------------------------------------------------------------
CAudioDialogDlg::~CAudioDialogDlg()
{
	if( mpMixerDlg ) 		delete [] mpMixerDlg ;
	if( mpDestinationsDlg ) delete [] mpDestinationsDlg ;
	if( mpConnectionDlg )	delete [] mpConnectionDlg ;
	if( mpControlsDlg ) 	delete [] mpControlsDlg ;
	if( mpCMixer ) 			delete [] mpCMixer ;
	if( mpControlGroup )	delete [] mpControlGroup ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// -----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAudioDialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_MIXER_SELECT_COMBO, &CAudioDialogDlg::OnCbnSelchangeMixerSelectCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_DEST, &CAudioDialogDlg::OnCbnSelchangeComboDest)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTROL, &CAudioDialogDlg::OnCbnSelchangeComboConnectionControl)
	ON_CBN_SELCHANGE(IDC_COMBO_DEST_CONTROL, &CAudioDialogDlg::OnCbnSelchangeComboDestControl)
	ON_CBN_SELCHANGE(IDC_COMBO__CONNECTION_CONTROL, &CAudioDialogDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_MIXER_BUTTON, &CAudioDialogDlg::OnBnClickedMixerButton)
	ON_BN_CLICKED(IDC_DEST_BUTTON, &CAudioDialogDlg::OnBnClickedDestButton)
	ON_BN_CLICKED(IDC_DEST_CTRL_BUTTON, &CAudioDialogDlg::OnBnClickedDestCtrlButton)
	ON_BN_CLICKED(IDC_CONNECTION_BUTTON, &CAudioDialogDlg::OnBnClickedConnectionButton)
	ON_BN_CLICKED(IDC_CONN_CTRL_BUTTON, &CAudioDialogDlg::OnBnClickedConnCtrlButton)

	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChange )	// Mixer message
	ON_MESSAGE( MM_MIXM_LINE_CHANGE, OnMixerLineChange )		// Mixer message
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CTRL_ID_START, IDC_CTRL_ID_END, OnCheckBoxClicked)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CAudioDialogDlg message handlers

// -----------------------------------------------------------------------------
BOOL CAudioDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	unsigned int n1 ;
	CString s1 ;
	MIXERCAPS mixerCaps ;
	CRect cr ;
	CStatic* destCs ;
	LOGFONT logFont;

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
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetClientRect( cr ) ;
	SCROLLINFO scrollInfo ;
	GetScrollInfo( SB_HORZ , &scrollInfo, SIF_ALL ) ; 
	scrollInfo.nMin = cr.left ;
	scrollInfo.nMax = cr.right ;
	scrollInfo.nPage = (cr.right-cr.left)/4 ;
	scrollInfo.nPos = 0 ;
	SetScrollInfo( SB_HORZ , &scrollInfo ) ; 
	mnScrollPos = 0 ;
	mnScrollThumbWidth = scrollInfo.nPage ;
	mnScrollMax = scrollInfo.nMax ;

	// Set destination label static control text font to bold
	destCs = (CStatic*)GetDlgItem( IDC_DEST_LABEL_STATIC ) ;
	destCs->GetFont()->GetLogFont(&logFont);
	logFont.lfWeight = FW_BOLD;
	mFont.CreateFontIndirect(&logFont);
	destCs->SetFont(&mFont);

	// Populate mixer dropdown with ID strings 
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	for( n1=0 ; n1<mMixerCount  ; n1++ )
	{
		mpCMixer[n1].GetMixerCaps( &mixerCaps )  ;
		pMixerCombo->InsertString( n1, mixerCaps.szPname ) ;
	}
	pMixerCombo->SetCurSel( 0 ) ;
	OnCbnSelchangeMixerSelectCombo() ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// -----------------------------------------------------------------------------
int CAudioDialogDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	unsigned int mixerIndex ;

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	mMixerCount = mixerGetNumDevs();
	mpCMixer = new CMixer[mMixerCount] ;

	if( mpCMixer )
	{
		for( mixerIndex=0 ; mixerIndex<mMixerCount  ; mixerIndex++ )
		{
			mpCMixer[mixerIndex].Init( mixerIndex, GetSafeHwnd() ) ;
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------
// Create an array of control groups for the selected mixer and destination. 
// A control group consists of balance, volume, and mute controls. A group 
// is created for the destination and each connection associated with the 
// destination. If there are no controls for a destination or connection, no 
// group is created. 
// -----------------------------------------------------------------------------
void CAudioDialogDlg::CreateCtrlArray( int mixerIndex, int destIndex )
{
	if( mpControlGroup )
		delete [] mpControlGroup ;

	mnNextResourceID = IDC_CTRL_ID_START ;
	mpControlGroup = new CControlGroup ;
	mpControlGroup->CreateControls( &mpCMixer[mixerIndex], destIndex, this, 
						mnGroupHorzOffset, 0, mnNextResourceID++ ) ;
}

// -----------------------------------------------------------------------------
// A new mixer has been selected in the Combo Box, update other combos. 
void CAudioDialogDlg::OnCbnSelchangeMixerSelectCombo()
{
	int n1 ;
	CString s1 ;
	CComboBox* pCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	unsigned int mixerIndex = pCombo->GetCurSel() ;
	MIXERCAPS mixerCaps ;

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	SetWindowText( mixerCaps.szPname ) ;

	HideDataDialogs() ;
	UpdateMixerInfoDialog() ;

	pCombo = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;	// Destination combo
	pCombo->ResetContent() ;
	n1 = 0 ;
	do {
		s1.Format( _T("%d"), n1 ) ;
		pCombo->InsertString( n1++, s1 ) ;
	} while( n1<mpCMixer[mixerIndex].GetDestinationCount() ) ;
	pCombo->SetCurSel( 0 ) ;

	OnCbnSelchangeComboDest() ;
}

// -----------------------------------------------------------------------------
// A new destination has been selected from the destination combo box.
void CAudioDialogDlg::OnCbnSelchangeComboDest()
{
	CComboBox* pCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	unsigned int mixerIndex = pCombo->GetCurSel() ;
	pCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	unsigned int destIndex = pCombo->GetCurSel() ;
	int n1 = 0 ;
	int nCount = 0 ;
	CString s1 ;
	CButton* pcButton ;

	CreateCtrlArray( mixerIndex, destIndex ) ;	

	if( mpDestinationsDlg )
	{
		n1 = mpDestinationsDlg->IsWindowVisible() ;
		UpdateDestInfoDialog() ;
	}

	HideDataDialogs() ;

	if( n1 )
		mpDestinationsDlg->ShowWindow( SW_SHOW ) ;

	// Update dest controls, connection, and connection control combo boxes
	nCount = mpCMixer[mixerIndex].GetDestinationControlCount(destIndex) ;
	pCombo = (CComboBox*)GetDlgItem( IDC_COMBO_DEST_CONTROL ) ;
	pCombo->ResetContent() ;
	pcButton = (CButton*)GetDlgItem(IDC_DEST_CTRL_BUTTON) ;
	if( nCount <= 0 )					// If there are no dest controls, 
	{
		pCombo->EnableWindow(FALSE) ;	// disable dest controls combo box.
		pcButton->EnableWindow(FALSE) ;	// Disable the show info button 
	}
	else								// Else, populate the combo box.
	{
		pCombo->EnableWindow(TRUE) ;
		pcButton->EnableWindow(TRUE) ;
		n1 = 0 ;
		do {
			s1.Format( _T("%d"), n1 ) ;
			pCombo->InsertString( n1++, s1 ) ;
		} while( n1<nCount ) ;
		pCombo->SetCurSel( 0 ) ;
	}

	// Connections combo box
	nCount = mpCMixer[mixerIndex].GetConnectionCount(destIndex) ; 
	pCombo = (CComboBox* )GetDlgItem( IDC_COMBO_CONTROL ) ;
	pCombo->ResetContent() ;
	pcButton = (CButton*)GetDlgItem(IDC_CONNECTION_BUTTON) ;
	if( nCount <= 0 )					// If there are no connections, 
	{
		pCombo->EnableWindow(FALSE) ;	// disable connection combo box.
		pcButton->EnableWindow(FALSE) ;	// Disable the show info button 
	}
	else								// Else, populate the combo box.
	{
		pcButton->EnableWindow(TRUE) ;
		pCombo->EnableWindow(TRUE) ;
		n1 = 0 ;
		do {
			s1.Format( _T("%d"), n1 ) ;
			pCombo->InsertString( n1++, s1 ) ;
		} while( n1<nCount ) ;
		pCombo->SetCurSel( 0 ) ;
	}

	// Connection controls combo box
	nCount = mpCMixer[mixerIndex].GetConnectionControlCount(destIndex,0) ; 
	pCombo = (CComboBox* )GetDlgItem( IDC_COMBO__CONNECTION_CONTROL ) ;
	pCombo->ResetContent() ;
	pcButton = (CButton*)GetDlgItem(IDC_CONN_CTRL_BUTTON) ;
	if( nCount <= 0 )					// If there are no connection controls, 
	{
		pCombo->EnableWindow(FALSE) ;	// disable connection controls combo box.
		pcButton->EnableWindow(FALSE) ;	// Disable the show info button 
	}
	else								// Else, populate the combo box.
	{
		pcButton->EnableWindow(TRUE) ;
		pCombo->EnableWindow(TRUE) ;
		n1 = 0 ;
		do {
			s1.Format( _T("%d"), n1 ) ;
			pCombo->InsertString( n1++, s1 ) ;
		} while( n1<nCount ) ;
		pCombo->SetCurSel( 0 ) ;
	}
}

// -----------------------------------------------------------------------------
// A new destination control has been selected from the destination control combo box.
void CAudioDialogDlg::OnCbnSelchangeComboDestControl()
{
	if( mpControlsDlg )	// Hide the control dialog box
		mpControlsDlg->ShowWindow( SW_HIDE ) ;
}

// ----------------------------------------------------------------------------- 
// A new connection has been selected from the connection combo box
void CAudioDialogDlg::OnCbnSelchangeComboConnectionControl()
{
	if( mpControlsDlg )	
		mpControlsDlg->ShowWindow( SW_HIDE ) ;	// Hide the control dialog 

	// Update the connection control combo box
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	CComboBox* pDestCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	CComboBox* pConnCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_CONTROL ) ;	
	CComboBox* pCtrlCombo  = (CComboBox* )GetDlgItem( IDC_COMBO__CONNECTION_CONTROL ) ;

	unsigned int mixerIndex	= pMixerCombo->GetCurSel() ;
	unsigned int destIndex	= pDestCombo->GetCurSel()  ;
	unsigned int connIndex	= pConnCombo->GetCurSel()  ;
	int nCtrlCount = 0 ;

	// Refresh connection control dropdown 
	nCtrlCount = mpCMixer[mixerIndex].GetConnectionControlCount( destIndex, connIndex ) ;
	pCtrlCombo->ResetContent() ;
	CString s1 ;
	int n1 = 0 ;
	do 
	{
		s1.Format( _T("%d"), n1 ) ;
		pCtrlCombo->InsertString( n1, s1 ) ;
		n1++ ;
	} while( n1<nCtrlCount ) ;
	pCtrlCombo->SetCurSel( 0 ) ;

	// Update the connection info dialog 
	UpdateConnectionInfoDialog() ;
}

// -----------------------------------------------------------------------------
//  A new connection control has been selected from the connection control combo box.
void CAudioDialogDlg::OnCbnSelchangeCombo()
{
	if( mpControlsDlg )	
		mpControlsDlg->ShowWindow( SW_HIDE ) ;	// Hide the control dialog box
}

// -----------------------------------------------------------------------------
// There will be one message for each open mixer assuming the CALLBACK_WINDOW 
// option was set in the mixerOpen call. For example, if there are three mixers 
// opened this way, there will be three messages received, regardless of which 
// mixer control changed. It is not possible to directly determine which mixer 
// generated the message, but the (LPARAM) dwControlID value will be correct. 
// If necessary, each mixer.dwControlID can be checked for a changed state to 
// determine which mixer generated the control change message. 
// -----------------------------------------------------------------------------
long CAudioDialogDlg::OnMixerControlChange( WPARAM wParam, LPARAM lParam )
{
	mpControlGroup->UpdateWinControlState( (unsigned int)lParam ) ;
	return 0 ;
}

// -----------------------------------------------------------------------------
// Note that a MM_MIXM_LINE_CHANGE event occurs when a line is muted. Since the 
// line has a control, the control event also occurs. Monitoring the line change 
// event seems like a duplicaiton of effort so ignore the line change event 
// message for now. 
// -----------------------------------------------------------------------------
long CAudioDialogDlg::OnMixerLineChange( WPARAM wParam, LPARAM lParam )
{
	return 0 ;
}

// -----------------------------------------------------------------------------
// Display MIXERCAPS structure data for the selected mixer.
void CAudioDialogDlg::OnBnClickedMixerButton()	// IDC_MIXER_BUTTON
{
	UpdateMixerInfoDialog() ;
	mpMixerDlg->ShowWindow(TRUE) ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::UpdateMixerInfoDialog()
{
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	unsigned int mixerIndex = pMixerCombo->GetCurSel() ;
	CString s1 ;
	MIXERCAPS mixerCaps ;

	if( !mpMixerDlg )
	{
		mpMixerDlg = new CMixerCapsDlg ;
		mpMixerDlg->Create(IDD_MIXER_CAPS_DIALOG) ;
	}

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	mpMixerDlg->SetDisplayValues( &mixerCaps ) ;
	s1.Format( _T("Mixer %d - %s"), mixerIndex, mixerCaps.szPname ) ;
	mpMixerDlg->SetWindowText( s1 ) ;
}

// -----------------------------------------------------------------------------
// Display MIXERLINE structure data for the selected mixer destination.
void CAudioDialogDlg::OnBnClickedDestButton()	// IDC_DEST_BUTTON
{
	UpdateDestInfoDialog() ;
	mpDestinationsDlg->ShowWindow(TRUE) ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::UpdateDestInfoDialog()
{
	CComboBox* pDestCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	CComboBox* pSelCombo   = (CComboBox* )GetDlgItem( IDC_COMBO_CONTROL ) ;
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;

	unsigned int mixerIndex	= pMixerCombo->GetCurSel() ;
	unsigned int nDestCount		= pDestCombo->GetCurSel()  ;
	CString s1 ;
	MIXERCAPS mixerCaps ;
	MIXERLINE mixerLine ;

	unsigned int destIndex = pDestCombo->GetCurSel() ;

	// Display the destination MIXERLINE data dialog
	if( !mpDestinationsDlg )
	{	
		mpDestinationsDlg = new CDestinationsDialog ;
		mpDestinationsDlg->Create(IDD_DESTINATIONS_DIALOG) ;
	}

	mpCMixer[mixerIndex].GetDestInfo( destIndex, &mixerLine ) ;
	mpDestinationsDlg->SetDisplayValues( &mixerLine ) ;

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	s1.Format( _T("Mixer %d - %s, destination %d"), mixerIndex, 
				CString(mixerCaps.szPname), destIndex ) ;
	mpDestinationsDlg->SetTitle( s1 ) ;
}

// -----------------------------------------------------------------------------
// Display MIXERCONTROL structure data for the selected mixer destination control.
void CAudioDialogDlg::OnBnClickedDestCtrlButton()	// IDC_DEST_CTRL_BUTTON
{
	UpdateDestControlInfoDialog() ;
	mpControlsDlg->ShowWindow( SW_SHOW ) ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::UpdateDestControlInfoDialog() 
{
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	CComboBox* pDestCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	CComboBox* pCtrlCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST_CONTROL ) ;

	unsigned int mixerIndex	= pMixerCombo->GetCurSel() ;
	unsigned int destIndex		= pDestCombo->GetCurSel()  ;
	unsigned int ctrlIndex		= pCtrlCombo->GetCurSel()  ;
	int nRet ;
	CString s1 ;
	MIXERCAPS mixerCaps ;
	MIXERCONTROL mixerControl ;

	// Update the control MIXERCONTROL data dialog
	if( !mpControlsDlg )
	{	
		mpControlsDlg = new CControlsDialog ;
		mpControlsDlg->Create(IDD_CONTROLS_DIALOG) ;
	}

	nRet = mpCMixer[mixerIndex].GetDestControlMetrics( destIndex,ctrlIndex, 
														&mixerControl ) ;
	if( nRet < 0 )
		return ;

	mpControlsDlg->SetDisplayValues( &mixerControl ) ;

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	s1.Format( _T("Mixer %d - %s, destination %d, control %d"), mixerIndex, 
						CString(mixerCaps.szPname), destIndex, ctrlIndex ) ;
	mpControlsDlg->SetTitle( s1 ) ;
}

// -----------------------------------------------------------------------------
// Display MIXERLINE structure data for the selected mixer destination connection.
void CAudioDialogDlg::OnBnClickedConnectionButton()	// IDC_CONNECTION_BUTTON
{
	UpdateConnectionInfoDialog() ;
	mpConnectionDlg->ShowWindow( SW_SHOW ) ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::UpdateConnectionInfoDialog()
{
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	CComboBox* pDestCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	CComboBox* pConnCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_CONTROL ) ;	

	unsigned int mixerIndex	= pMixerCombo->GetCurSel() ;
	unsigned int destIndex		= pDestCombo->GetCurSel()  ;
	unsigned int connIndex		= pConnCombo->GetCurSel()  ;
	CString s1 ;
	MIXERCAPS mixerCaps ;
	MIXERLINE mixerLine ;

	// Update the connection MIXERLINE data dialog
	if( !mpConnectionDlg )
	{	
		mpConnectionDlg = new CDestinationsDialog ;
		mpConnectionDlg->Create(IDD_DESTINATIONS_DIALOG) ;
	}

	mpCMixer[mixerIndex].GetConnectionInfo( destIndex, connIndex, &mixerLine ) ;
	mpConnectionDlg->SetDisplayValues( &mixerLine ) ;

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	s1.Format( _T("Mixer %d - %s, destination %d, connection %d"), mixerIndex, 
				CString(mixerCaps.szPname), destIndex, connIndex ) ;
	mpConnectionDlg->SetTitle( s1 ) ;
}

// -----------------------------------------------------------------------------
// Display MIXERCONTROL structure data for the selected mixer destination 
// connection control.
void CAudioDialogDlg::OnBnClickedConnCtrlButton()	// IDC_CONN_CTRL_BUTTON
{
	UpdateConnectionControlInfoDialog() ;
	mpControlsDlg->ShowWindow( SW_SHOW ) ;
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::UpdateConnectionControlInfoDialog()
{
	CComboBox* pMixerCombo = (CComboBox* )GetDlgItem( IDC_MIXER_SELECT_COMBO ) ;
	CComboBox* pDestCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_DEST ) ;
	CComboBox* pConnCombo  = (CComboBox* )GetDlgItem( IDC_COMBO_CONTROL ) ;	
	CComboBox* pCtrlCombo  = (CComboBox* )GetDlgItem( IDC_COMBO__CONNECTION_CONTROL ) ;

	unsigned int mixerIndex	= pMixerCombo->GetCurSel() ;
	unsigned int destIndex	= pDestCombo->GetCurSel()  ;
	unsigned int connIndex	= pConnCombo->GetCurSel()  ;
	unsigned int ctrlIndex	= pCtrlCombo->GetCurSel()  ;
	CString s1 ;
	MIXERCAPS mixerCaps ;
	MIXERCONTROL mixerControl ;

	// Update the control MIXERCONTROL data dialog
	if( !mpControlsDlg )
	{	
		mpControlsDlg = new CControlsDialog ;
		mpControlsDlg->Create(IDD_CONTROLS_DIALOG) ;
	}

	mpCMixer[mixerIndex].GetConnectionControlMetrics( destIndex, connIndex, 
													ctrlIndex, &mixerControl ) ;
	mpControlsDlg->SetDisplayValues( &mixerControl ) ;

	mpCMixer[mixerIndex].GetMixerCaps( &mixerCaps )  ;
	s1.Format( _T("Mixer %d - %s, destination %d, connection %d, control %d"), 
		mixerIndex, CString(mixerCaps.szPname), destIndex, connIndex, ctrlIndex ) ;
	mpControlsDlg->SetTitle( s1 ) ;
}

// -----------------------------------------------------------------------------
// Hide data dialogs
void CAudioDialogDlg::HideDataDialogs(void)
{
	if( mpDestinationsDlg )	// Destination data dialog
		mpDestinationsDlg->ShowWindow( SW_HIDE ) ;

	if( mpConnectionDlg )	// Connection data dialog
		mpConnectionDlg->ShowWindow( SW_HIDE ) ;

	if( mpControlsDlg )		// Control data dialog
		mpControlsDlg->ShowWindow( SW_HIDE ) ;
}

// -----------------------------------------------------------------------------
// Event message handler for messages spawned by dynamically created check boxes. 
void CAudioDialogDlg::OnCheckBoxClicked(unsigned int nCtrlID)
{
	// Update the associated mixer control
	mpControlGroup->UpdateMixerControlState( nCtrlID ) ;
}

// -----------------------------------------------------------------------------
// Horizontal slider or scroll bar message handler. 
void CAudioDialogDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{	
	int nDelta ;
	int nCtrlID ;

	// If it's a horizontal slider control that sent the message, it's a 
	if( pScrollBar )
	{
		// dynamically created slider, update it's associated mixer control
		nCtrlID = pScrollBar->GetDlgCtrlID() ;
		mpControlGroup->UpdateMixerControlState( nCtrlID ) ;
	}
	else	// Else this message is from the window's scroll bar, scroll the window
	{
		nDelta = 0 ;
		switch( nSBCode ) 
		{
		case SB_THUMBPOSITION:
			nDelta = nPos - mnScrollPos ;
			break ;

		case SB_LINELEFT:	// Left scroll arrow clicked, scrolls left by one unit.
		case SB_PAGELEFT:	// Click to left of thumb
			if( mnScrollPos <= 0 )
				break ;
			nDelta = -( min( 100, mnScrollPos ) ) ;
			break ;

		case SB_LINERIGHT:	// Right scroll arrow clicked, scrolls right by one unit.
		case SB_PAGERIGHT:	// Click to the right of the thumb
			if( mnScrollPos >= mnScrollMax - mnScrollThumbWidth )
				break ;
			nDelta = ( min( 100, mnScrollMax - mnScrollThumbWidth - mnScrollPos ) ) ;
			break ;
		} ;
		mnScrollPos += nDelta ;
		SetScrollPos( SB_HORZ, mnScrollPos, TRUE ) ;
		ScrollWindow( -nDelta, 0 ) ;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

// -----------------------------------------------------------------------------
// Vertical slider or scroll bar message handler. 
// -----------------------------------------------------------------------------
void CAudioDialogDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Get ID of the vertical slider control that sent the message
	int nCtrlID = pScrollBar->GetDlgCtrlID() ;

	// Update the associated mixer control
	mpControlGroup->UpdateMixerControlState( nCtrlID ) ;

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// -----------------------------------------------------------------------------
void CAudioDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// -----------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
// -----------------------------------------------------------------------------
void CAudioDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// -----------------------------------------------------------------------------
// The system calls this function to obtain the cursor to display while the user 
// drags the minimized window.
HCURSOR CAudioDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// -----------------------------------------------------------------------------
