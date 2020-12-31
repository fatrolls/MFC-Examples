#include <windows.h>
#include "NTService.h"

#ifndef _CONSOLE
	#include <stdlib.h>		// for declaration of __argv and __argc
#endif


class CSampleService : public CNTService {
	// the service control manager (SCM) starts "Run()" in a
	// different thread than "Stop()", so we need something
	// for syncronization. This sample uses an "Event". You
	// might use other syncronization methods too (mutexes
	// or whatever you like).
	HANDLE	m_hStop;

	public:
		// construct a new service.
		// The first parameter to the baseclass' constructor is the
		// name of the service. This appears in the event-log for
		// instance. The second parameter is the display name, thus
		// what you can read in the "Services" control panel applet.
		// If you ommit the second parameter, then it defaults to be
		// equal to the first one.
		CSampleService()
			: CNTService(TEXT("SampleService"), TEXT("Very Simple Service"))
			, m_hStop(0)
		{
		}


		// We have to implement at least these two methods:
		virtual void	Run(DWORD, LPTSTR *);
		virtual void	Stop();
};


// ignore parameters in this sample service
void CSampleService :: Run(DWORD, LPTSTR *) {
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
		::MessageBox(0, TEXT("Hi, here is your very first NT-service"), TEXT("SampleService"), MB_OK);
		::Sleep( 10000 );
	}

	if( m_hStop )
		::CloseHandle(m_hStop);
}


void CSampleService :: Stop() {
	// report to the SCM that we're about to stop
	// Note that the service might Sleep(), so we have to tell
	// the SCM
	//	"The next operation may take me up to 11 seconds. Please be patient."
	ReportStatus(SERVICE_STOP_PENDING, 11000);

	if( m_hStop )
		::SetEvent(m_hStop);
}


#ifdef _CONSOLE
	int main( int argc, char ** argv ) {
#else
	int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	// non of the arguments is used when running on Win95
	int argc = __argc;
	char ** argv = __argv;
#endif	// _CONSOLE

	// create the service-object
	CSampleService serv;
	
	// RegisterService() checks the parameterlist for predefined switches
	// (such as -d or -i etc.; see NTService.h for possible switches) and
	// starts the services functionality.
	// You can use the return value from "RegisterService()"
	// as your exit-code.
	return serv.RegisterService(argc, argv);
}
