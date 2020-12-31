//
// Client2.cpp - Client implementation with smart pointers
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"   // Traces with labels for our output
#include "Ptr.h"    // Smart pointer classes

static inline void trace(const char* msg)
	{ Util::Trace("Client 2", msg, S_OK) ;} 
static inline void trace(const char* msg, HRESULT hr)
	{ Util::Trace("Client 2", msg, hr) ;}

void Think() 
{
	trace("Create Component 1.") ;
	IPtr<IX, &IID_IX> spIX ; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL,
	                              CLSCTX_INPROC_SERVER, 
	                              spIX.iid(),
	                              (void**)&spIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Succeeded creating component.") ;
		spIX->Fx() ;

		trace("Get interface IY.") ;
		IPtr<IY, &IID_IY> spIY ;
		spIY = spIX ;		// Use Assignment.
		if (spIY)
		{
			spIY->Fy() ;

			trace("Get interface IX from IY.") ;
			IPtr<IX, &IID_IX> spIX2(spIY) ; // Use Constructor.
			if (!spIX2)
			{
				trace("Could not get interface IX from IY.") ;
			}
			else
			{
				spIX2->Fx() ;
			}
		}

		trace("Get interface IZ.") ;
		IPtr<IZ, &IID_IZ> spIZ ;
		spIZ = spIX ;
		if (spIZ)
		{
			spIZ->Fz() ;

			trace("Get interface IX from IZ.") ;
			IPtr<IX, &IID_IX> spIX2(spIZ) ;
			if (!spIX2)
			{
				trace("Could not get interface IX from IZ.") ;
			}
			else
			{
				spIX2->Fx() ;
			}
		}
	}
	else
	{
		trace("Could not create component.", hr) ;
	}

}

int main()
{
	// Initialize COM Library.
	CoInitialize(NULL) ;

	// Exercise the smart pointers.
	Think() ;

	// Uninitialize COM Library.
	CoUninitialize() ;

	return 0 ;
}
