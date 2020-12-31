// ServiceApp.cpp: implementation of the CServiceApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceApp.h"


CServiceApp theApp;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServiceApp::CServiceApp()
	: CNTService(TEXT("MFCSampleService"), TEXT("Simple Service Using MFC"))
	, m_hStop(0)
{
}

CServiceApp::~CServiceApp()
{
}


BOOL CServiceApp :: InitInstance() {
	RegisterService(__argc, __argv);
	return FALSE;
}


void CServiceApp :: Run( DWORD, LPTSTR *) {		// args not used in this small example
	// report to the SCM that we're about to start
	ReportStatus(SERVICE_START_PENDING);
	
	m_hStop = ::CreateEvent(0, TRUE, FALSE, 0);

	// You might do some more initialization here.
	// Parameter processing for instance ...
	
	// report SERVICE_RUNNING immediately before you enter the main-loop
	// DON'T FORGET THIS!
	ReportStatus(SERVICE_RUNNING);

	// enter main-loop
	// If the Stop() method sets the event, then we will break out of
	// this loop.
	while( ::WaitForSingleObject(m_hStop, 10) != WAIT_OBJECT_0 ) {
		// popup a small message box every 10 seconds
		::MessageBox(0, TEXT("Hi, here is your very first MFC based NT-service"), TEXT("MFC SampleService"), MB_OK);
		::Sleep( 10000 );
	}

	if( m_hStop )
		::CloseHandle(m_hStop);
}


void CServiceApp :: Stop() {
	// report to the SCM that we're about to stop
	// Note that the service might Sleep(), so we have to tell
	// the SCM
	//	"The next operation may take me up to 11 seconds. Please be patient."
	ReportStatus(SERVICE_STOP_PENDING, 11000);

	if( m_hStop )
		::SetEvent(m_hStop);
}
