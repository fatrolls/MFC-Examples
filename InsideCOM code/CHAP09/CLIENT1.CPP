//
// Client1.cpp - Client implementation without smart pointers
//
#include <iostream.h>
#include <objbase.h>

#include "Iface.h"
#include "Util.h"   // Traces with labels for our output

static inline void trace(const char* msg)
	{ Util::Trace("Client 1", msg, S_OK) ;} 
static inline void trace(const char* msg, HRESULT hr)
	{ Util::Trace("Client 1", msg, hr) ;}

int main()
{
	// Initialize COM Library
	CoInitialize(NULL) ;

	trace("Create Component 1") ;
	IX* pIX = NULL ; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL,
	                              CLSCTX_INPROC_SERVER,
	                              IID_IX,
	                              (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Succeeded creating component.") ;
		pIX->Fx() ;

		trace("Get interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			pIY->Fy() ;

			trace("Get interface IX from IY.") ;
			IX* pIX2 = NULL ;
			hr = pIY->QueryInterface(IID_IX, (void**)&pIX2) ;
			if (SUCCEEDED(hr))
			{
				pIX2->Fx() ;
				pIX2->Release();
			}
			else
			{
				trace("Could not get interface IX from IY.", hr) ;
			}
			pIY->Release() ;
		}

		trace("Get interface IZ.") ;
		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			pIZ->Fz() ;

			trace("Get interface IX from IZ.") ;
			IX* pIX2 = NULL ;
			hr = pIZ->QueryInterface(IID_IX, (void**)&pIX2) ;
			if (SUCCEEDED(hr))
			{
				pIX2->Fx() ;
				pIX2->Release() ;
			}
			else
			{
				trace("Could not get interface IX from IZ.", hr) ;
			}
			pIZ->Release() ;
		}
		pIX->Release() ;
	}
	else
	{
		trace("Could not create component.", hr) ;
	}

	// Uninitialize COM Library
	CoUninitialize() ;

	return 0 ;
}
