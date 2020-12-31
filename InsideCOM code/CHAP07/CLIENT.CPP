//
// Client.cpp - client implementation
//
#include <iostream.h>
#include <objbase.h>

#include "Iface.h"

void trace(const char* msg) { cout << "Client: \t\t" << msg << endl ;}

//
// main function
//
int main()
{
	// Initialize COM Library
	CoInitialize(NULL) ;

	trace("Call CoCreateInstance to create") ;
	trace("  component and get interface IX.") ;
	IX* pIX = NULL ; 
	HRESULT hr = ::CoCreateInstance(CLSID_Component1,
	                                NULL, 
	                                CLSCTX_INPROC_SERVER,
	                                IID_IX, 
	                                (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Succeeded getting IX.") ;
		pIX->Fx() ;          // Use interface IX.

		trace("Ask for interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			trace("Succeeded getting IY.") ;
			pIY->Fy() ;       // Use interface IY.
			pIY->Release() ;
			trace("Release IY interface.") ;
		}
		else
		{
			trace("Could not get interface IY.") ;
		}

		trace("Ask for interface IZ.") ;

		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			trace("Succeeded in getting interface IZ.") ;
			pIZ->Fz() ;
			pIZ->Release() ;
			trace("Release IZ interface.") ;
		}
		else
		{
			trace("Could not get interface IZ.") ;
		}

		trace("Release IX interface.") ;
		pIX->Release() ;
	}
	else
	{
		cout << "Client: \t\tCould not create component. hr = "
		     << hex << hr << endl ;    
	}

	// Uninitialize COM Library
	CoUninitialize() ;

	return 0 ;
}
