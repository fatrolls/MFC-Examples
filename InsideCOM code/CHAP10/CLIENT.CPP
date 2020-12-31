//
// Client.cpp - client implementation
//
#include <objbase.h>
#include <iostream.h>
#include <assert.h>

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
	     << "2) Local Server\r\n:" ;
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

	IX* pIX = NULL; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL, clsctx, 
	                              IID_IX, (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Successfully created component.") ;
		trace("Use interface IX.") ;
		wchar_t* szOut = NULL ;
		hr = pIX->FxStringIn(L"This is the test.") ;
		assert(SUCCEEDED(hr)) ;
		hr = pIX->FxStringOut(&szOut) ;
		assert(SUCCEEDED(hr)) ;

		// Display returned string.
		ostrstream sout ;
		sout << "FxStringOut returned a string:  "
		     << szOut
		     << ends ;
		trace(sout.str()) ;

		// Free the returned string.
		::CoTaskMemFree(szOut) ;

		trace("Get interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			// Send an array to the component. 
			long arrayIn[] = { 22, 44, 206, 76, 300, 500 } ;
			long sizeIn = sizeof(arrayIn) / sizeof(arrayIn[0]) ; 
			hr = pIY->FyArrayIn(sizeIn, arrayIn) ;
			assert(SUCCEEDED(hr)) ;

			// Get the array back from the component.

			// Get the size of the array.
			long sizeOut = 0 ;
			hr = pIY->FyCount(&sizeOut) ;
			assert(SUCCEEDED(hr)) ;

			// Allocate the array.
			long* arrayOut = new long[sizeOut] ;

			// Get the array.
			hr = pIY->FyArrayOut(&sizeOut, arrayOut) ;
			assert(SUCCEEDED(hr)) ;

			// Display the array returned from the function.
			ostrstream sout ;
			sout	<< "FyArray returned " 
			      << sizeOut
			      << " elements: " ;
			for (int i = 0 ; i < sizeOut ; i++)
			{
				sout << " " << arrayOut[i] ;
			}
			sout << "." << ends ;
			trace(sout.str()) ;

			// Cleanup
			trace("Release IY.") ;
			delete [] arrayOut ;

			pIY->Release() ;
		}
		else
		{
			trace("Could not get interface IY from IX.", hr) ;
		}

		trace("Get interface IZ.") ;
		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			// Pass a point to the component.
			Point3d ptIn ;
			ptIn.x = 3.14 ;
			ptIn.y = 2.81 ;
			ptIn.z = 9.8 ;
			hr = pIZ->FzStructIn(ptIn) ;
			assert(SUCCEEDED(hr)) ;

			// Get the point back from the component.
			Point3d ptOut ;
			hr = pIZ->FzStructOut(&ptOut) ;
			assert(SUCCEEDED(hr)) ;
			strstream sout ;
			sout << "FzStructOut returned ("
			     << ptOut.x << ", "
			     << ptOut.y << ", "
			     << ptOut.z << ")."
			     << ends ;
			trace(sout.str()) ;

			pIZ->Release() ;
		}
		else
		{
			trace("Could not get interface IZ from IX.", hr) ;
		}
		trace("Release IX.") ;
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
