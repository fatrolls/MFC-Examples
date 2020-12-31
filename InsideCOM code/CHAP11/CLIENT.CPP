//
// Client.cpp - Client implementation
//   This client connects to the IX dual interface
//   through the vtbl.
//
#include <objbase.h>
#include <iostream.h>

#include "Util.h"
#include "Iface.h"

static inline void trace(char* msg)
	{ Util::Trace("Client", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Client", msg, hr) ;}

int main()
{
	cout << "To which server do you want to connect?\r\n"
	     << "1) In-proc Server\r\n" 
	     << "2) Local Server.\r\n:" ;
	int i = 0 ;
	cin >> i ;

	DWORD clsctx ;
	if (i == 1)
	{
		clsctx = CLSCTX_INPROC_SERVER ;		
		trace("Attempt to create in-proc component.") ;
	}
	else
	{
		clsctx = CLSCTX_LOCAL_SERVER ;		
		trace("Attempt to create local component.") ;
	}

	// Initialize COM Library
	CoInitialize(NULL) ;

	IX* pIX = NULL ; 
	HRESULT hr = CoCreateInstance(CLSID_Component,
	                              NULL,
	                              clsctx, 
	                              IID_IX,
	                              (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Successfully created component.") ;
		trace("Use interface IX.") ;
		wchar_t* wszIn = L"This is the test." ;
		BSTR bstrIn ;
		bstrIn = ::SysAllocString(wszIn) ; 
		pIX->FxStringIn(bstrIn) ; 
		::SysFreeString(bstrIn) ;

		BSTR bstrOut ; //@dual
		pIX->FxStringOut(&bstrOut ) ;

		// Display returned string.
		ostrstream sout ;
		sout << "FxStringOut returned a string:  "
		     << bstrOut 
		     << ends;
		trace(sout.str()) ;
		::SysFreeString(bstrOut ) ;

		trace("Release IX.") ;
		pIX->Release() ;
	}
	else
	{
		trace("Could not create component.", hr);
	}

	// Uninitialize COM Library
	CoUninitialize() ;

	return 0 ;
}
