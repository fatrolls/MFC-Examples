#include "StdCgi.h"
#include <conio.h>
//#include <process.h>
#include "..\ThreadManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// Global varaiabales for this module

//////////////////////////////////////////////////////////////////////////////
// Helper declarations for this module

UINT APIPRIVATE A_Thread_Function( PVOID pvThreadData )
{
	delete [] PCHAR( pvThreadData );
	for ( int iStep=0; iStep<1000000; iStep++ )
		;
	return( 1 );
}

//////////////////////////////////////////////////////////////////////////////
//
UINT APIPRIVATE Another_Thread_Function( PVOID pvThreadData )
{
	delete [] PCHAR( pvThreadData );
	CINT ciThreads = 10;

	for ( int iTest=0; iTest<ciThreads; iTest++ )
	{	// Check which load method to use
		char *pszData = new char[20];
		CThreadManager ThreadManager( &A_Thread_Function, (LPVOID)pszData );
		VERIFY_RETURN( ThreadManager.RunThread() );
	}
	return( 1 );
}

//////////////////////////////////////////////////////////////////////////////
//
void main( )
{
	ONLY_IN_DEBUG( afxDump.SetDepth( 1 ) );
	{	// Perform initialisation of the thread Manager
		char *pszData = new char[20];
		CThreadManager ThreadManager( &A_Thread_Function, (LPVOID)pszData );
		ThreadManager.RunThread();
	}
	CINT ciThreadFunctions = 10;

	for ( int iTest=0; iTest<ciThreadFunctions; iTest++ )
	{	// Check which load method to use
		char *pszData = new char[20];
		CThreadManager ThreadManager( &Another_Thread_Function, (LPVOID)pszData );
		VERIFY_RETURN( ThreadManager.RunThread() );
	}
//	Sleep( 1000 );
	// After this line the number of threads should be returned to the start point
//	StopThreadManager();
	puts( "Press any key to exit" );
	getche();
}		// End Main