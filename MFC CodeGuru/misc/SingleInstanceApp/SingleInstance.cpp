// SingleInstance.cpp : Defines the functions for the CSingleInstance class
//

#include "stdafx.h"
#include "SingleInstance.h"

/////////////////////////////////////////////////////////////////////////////
// CSingleInstance
//

CSingleInstance::CSingleInstance()
{
	// Set our default values
	m_hMutex = NULL;
}

CSingleInstance::~CSingleInstance()
{
	if ( m_hMutex != NULL ) {
		ReleaseMutex( m_hMutex );
	}
}

BOOL CSingleInstance::Create( UINT nID )
{
	CString strFullString;

	// Create our class name string
	if ( strFullString.LoadString( nID ) ) {
		// Extract the first sub-string
		AfxExtractSubString( m_strClassName, strFullString, 0 );
	}

	// Add the word 'Class' to the end
	m_strClassName += _T(" Class");

	// Create the mutex
	m_hMutex = CreateMutex( NULL, FALSE, m_strClassName );
	// Check for errors
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
		// Reset our mutext handle (just in case)
		m_hMutex = NULL;
		// The mutex already exists, which means an instance is already
		// running. Find the app and pop it up
		HWND hWnd = FindWindowEx( NULL, NULL, m_strClassName, NULL );
		if ( hWnd != NULL ) {
			ShowWindow( hWnd, SW_RESTORE );
			BringWindowToTop( hWnd );
			SetForegroundWindow( hWnd );
		}
		// Return failure
		return FALSE;
	}

	// Register the unique window class name so others can find it.
	WNDCLASS wndcls;    memset(&wndcls, 0, sizeof(WNDCLASS));
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = AfxWndProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hIcon = LoadIcon( wndcls.hInstance, MAKEINTRESOURCE( nID ) );//or AFX_IDI_STD_FRAME; 
	wndcls.hCursor = LoadCursor( wndcls.hInstance, IDC_ARROW );
	wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wndcls.lpszMenuName = NULL;//You may need to fix this
	wndcls.lpszClassName = m_strClassName; // my class name
	// Register name, exit if it fails
	if(!AfxRegisterClass(&wndcls)) {
		AfxMessageBox( _T("Failed to register window class!"), MB_ICONSTOP | MB_OK );
		return FALSE;
	}

	// Return success
	return TRUE;
}

CString CSingleInstance::GetClassName( void ) const
{
	return m_strClassName;
}
