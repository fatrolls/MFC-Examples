// DriverMoverDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DriverMover.h"
#include "DriverMoverDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverMoverDialog dialog

CDriverMoverDialog::CDriverMoverDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDriverMoverDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDriverMoverDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverMoverDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDriverMoverDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDriverMoverDialog, CDialog)
	//{{AFX_MSG_MAP(CDriverMoverDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COPY_FILE, OnCopyFileToDebugEE)
	ON_BN_CLICKED(IDC_REBOOT_DEBUGEE, OnRebootDebugEE)
	ON_BN_CLICKED(IDC_START_DRIVER, OnStartDriver)
	ON_BN_CLICKED(IDC_STOP_DRIVER, OnStopDriver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverMoverDialog message handlers

BOOL CDriverMoverDialog::OnInitDialog()
{
   WFCTRACEINIT( TEXT( "CDriverMoverDialog::OnInitDialog()" ) );

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

   CRegistry registry;

   registry.Connect( HKEY_CURRENT_USER );

   CString value;

   if ( registry.Open( TEXT( "SOFTWARE\\DriverMover" ), (CRegistry::CreatePermissions)( CRegistry::permissionRead | CRegistry::permissionSetValue | CRegistry::permissionWrite ) ) != FALSE )
   {
      registry.Create( TEXT( "SOFTWARE\\DriverMover" ) );

      if ( registry.GetValue( TEXT( "DriverName" ), value ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't read DriverName" ) );
      }

      CWnd * edit_control = GetDlgItem( IDC_DRIVER_NAME );
      edit_control->SetWindowText( value );

      registry.GetValue( TEXT( "LocalFilename" ), value );
      edit_control = GetDlgItem( IDC_LOCAL_FILE_NAME );
      edit_control->SetWindowText( value );

      registry.GetValue( TEXT( "MachineName" ),   value );
      edit_control = GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );
      edit_control->SetWindowText( value );
   }
   else if ( registry.Create( TEXT( "SOFTWARE\\DriverMover" ) ) != FALSE )
   {
      WFCTRACE( TEXT( "Creating..." ) );
      registry.SetValue( TEXT( "DriverName" ),    value );
      registry.SetValue( TEXT( "LocalFilename" ), value );
      registry.SetValue( TEXT( "MachineName" ),   value );
   }
   else
   {
      WFCTRACE( TEXT( "Crap." ) );
   }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDriverMoverDialog::OnPaint() 
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
HCURSOR CDriverMoverDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDriverMoverDialog::OnCancel() 
{
   WFCTRACEINIT( TEXT( "CDriverMoverDialog::OnCancel()" ) );
   WFCTRACELEVELON( 31 );

   CRegistry registry;

   CString value;

   registry.Connect( HKEY_CURRENT_USER );

   if ( registry.Open( TEXT( "SOFTWARE\\DriverMover" ), (CRegistry::CreatePermissions)( CRegistry::permissionRead | CRegistry::permissionSetValue | CRegistry::permissionWrite ) ) != FALSE )
   {
      CWnd * edit_control = GetDlgItem( IDC_DRIVER_NAME );
      edit_control->GetWindowText( value );

      if ( registry.SetValue( TEXT( "DriverName" ), value ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't write DriverName" ) );
      }

      edit_control = GetDlgItem( IDC_LOCAL_FILE_NAME );
      edit_control->GetWindowText( value );
      registry.SetValue( TEXT( "LocalFilename" ), value );

      edit_control = GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );
      edit_control->GetWindowText( value );
      registry.SetValue( TEXT( "MachineName" ), value );
   }
   else
   {
      WFCTRACE( TEXT( "Can't write to registry" ) );
   }
	
	CDialog::OnCancel();
}

void CDriverMoverDialog::OnCopyFileToDebugEE() 
{
   WFCTRACEINIT( TEXT( "CDriverMoverDialog::OnCopyFileToDebugEE()" ) );

	// TODO: Add your control notification handler code here
	
   CString machine_name;

   CWnd * computer_name_edit_control =  GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );
   computer_name_edit_control->GetWindowText( machine_name );

   CString destination_filename;

   if ( machine_name.GetLength() > 1 )
   {
      if ( machine_name.GetAt( 0 ) != TEXT( '\\' ) )
      {
         destination_filename = TEXT( "\\\\" );
      }
   }

   destination_filename += machine_name;
   destination_filename += TEXT( "\\admin$\\system32\\drivers\\" );

   // Now get the local filename

   CString local_filename;

   computer_name_edit_control = GetDlgItem( IDC_LOCAL_FILE_NAME );
   computer_name_edit_control->GetWindowText( local_filename );

   CString driver_filename;

   if ( local_filename.ReverseFind( TEXT( '\\' ) ) != (-1) )
   {
      driver_filename = local_filename.Right( local_filename.GetLength() - ( local_filename.ReverseFind( TEXT( '\\' ) ) + 1 ) );
   }
   else
   {
      driver_filename = local_filename;
   }

   WFCTRACEVAL( TEXT( "driver_filename " ), driver_filename );

   destination_filename += driver_filename;

   WFCTRACEVAL( TEXT( "destination_filename " ), destination_filename );

   if ( CopyFile( local_filename, destination_filename, FALSE ) == FALSE )
   {
      MessageBox( TEXT( "Can't copy file." ) );
   }
}

void CDriverMoverDialog::OnRebootDebugEE() 
{
	// TODO: Add your control notification handler code here
	
   CString machine_name;

   CWnd * computer_name_edit_control =  GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );
   computer_name_edit_control->GetWindowText( machine_name );

   CNetwork machine;

   machine.Open( machine_name );

   if ( machine.Shutdown( TRUE, TRUE, NULL, 0 ) == FALSE )
   {
      MessageBox( TEXT( "Can't shutdown" ) );
   }
}

void CDriverMoverDialog::OnStartDriver() 
{
   WFCTRACEINIT( TEXT( "CDriverMoverDialog::OnStartDriver()" ) );

	// TODO: Add your control notification handler code here

   CWnd * computer_name_edit_control =  GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );

   CString machine_name;

   computer_name_edit_control->GetWindowText( machine_name );

   CServiceControlManager manager;

   if ( manager.Open( SERVICE_START, NULL, machine_name ) == FALSE )
   {
      MessageBox( TEXT( "Can't open service control manager" ) );
      return;
   }

   CString driver_name;

   computer_name_edit_control = GetDlgItem( IDC_DRIVER_NAME );

   computer_name_edit_control->GetWindowText( driver_name );

   if ( manager.Start( driver_name ) == FALSE )
   {
      MessageBox( TEXT( "Can't start driver" ) );
   }  
   else
   {
      MessageBox( TEXT( "Started." ) );
   }
}

void CDriverMoverDialog::OnStopDriver() 
{
	// TODO: Add your control notification handler code here
	
   CString machine_name;

   CWnd * computer_name_edit_control =  GetDlgItem( IDC_DEBUGEE_MACHINE_NAME );
   computer_name_edit_control->GetWindowText( machine_name );

   CServiceControlManager manager;

   if ( manager.Open( SERVICE_STOP, NULL, machine_name ) == FALSE )
   {
      MessageBox( TEXT( "Can't open service control manager" ) );
      return;
   }

   CString driver_name;

   computer_name_edit_control = GetDlgItem( IDC_DRIVER_NAME );

   computer_name_edit_control->GetWindowText( driver_name );

   if ( manager.Stop( driver_name ) == FALSE )
   {
      MessageBox( TEXT( "Can't stop driver" ) );
   }
   else
   {
      MessageBox( TEXT( "Stopped." ) );
   }
}

void CDriverMoverDialog::OnOK() 
{
   GetNextDlgTabItem( GetFocus() )->SetFocus();
}
