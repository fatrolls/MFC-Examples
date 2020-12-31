//
// Util.cpp
//   - Common utilities for printing out messages
//
#include <objbase.h>
#include <stdlib.h>
#include <iostream.h>
#include <assert.h>

#include "Util.h"

namespace Util
{
//
// Print out a message with a label.
//
void Trace(char* szLabel, const char* szText, HRESULT hr)
{
	cout << szLabel
	     << ": \t"
	     << szText 
	     << endl ;

	if (FAILED(hr))
	{
		ErrorMessage(hr) ;
	}

}

//
// Print out the COM/OLE error string for an HRESULT.
//
void ErrorMessage(HRESULT hr)
{
	void* pMsgBuf ;
 
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &pMsgBuf,
		0,
		NULL) ;

	cout << "Error (" << hex << hr << "):  " 
	     << (LPTSTR)pMsgBuf << endl ;

	// Free the buffer.
	LocalFree(pMsgBuf) ;

}

} ; // End Namespace Util
