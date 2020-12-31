//
// Client.cpp - client implementation
//
#include <iostream.h>
#include <objbase.h>

#include "Iface.h"

void trace(const char* msg) { cout << "Client: \t" << msg << endl ;}

//
// main function
//
int main()
{
	// Initialize COM Library
	CoInitialize(NULL) ;
	
	trace("Get interface IX from Component 1.") ;
	IX* pIX = NULL ; 
	HRESULT hr = ::CoCreateInstance(CLSID_Component1,
	                                NULL, 
	                                CLSCTX_INPROC_SERVER,
	                                IID_IX, 
	                                (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Succeeded creating component.") ;
		pIX->Fx() ;
		
		trace("Get interface IY from IX.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			trace("Succeeded getting interface IY from IX.") ;
			pIY->Fy() ;
			
			trace("Get interface IX from IY.") ;
			IX* pIX2 = NULL ;
			hr = pIY->QueryInterface(IID_IX, (void**)&pIX2);
			if (SUCCEEDED(hr))
			{
				trace("Succeeded getting interface IX from IY.") ;
				pIX2->Release() ;
			}
			else
			{
				trace("Error! Should have gotten interface IX.") ;
			}
			
			pIY->Release() ;
		}
		else
		{
			trace("Could not get interface IY.") ;
		}
		
		pIX->Release() ;
	}
	else
	{
		cout << "Could not create component: " << hex << hr << endl ;
	}
	
	// Uninitialize COM Library
	CoUninitialize() ;
	
	return 0 ;
}
