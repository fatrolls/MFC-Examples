//
// IUnknown.cpp
// To compile use: cl IUnknown.cpp UUID.lib
//
#include <iostream.h>
#include <objbase.h>

void trace(const char* msg) { cout << msg << endl ;}


// Interfaces
interface IX : IUnknown
{
	virtual void __stdcall Fx() = 0 ;
} ;

interface IY : IUnknown
{
	virtual void __stdcall Fy() = 0 ;
} ;

interface IZ : IUnknown
{
	virtual void __stdcall Fz() = 0 ;
} ;

// Forward references for GUIDs
extern const IID IID_IX ;
extern const IID IID_IY ;
extern const IID IID_IZ ;

//
// Component
//
class CA : public IX,
           public IY
{
	//IUnknown implementation
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;			
	virtual ULONG __stdcall AddRef() { return 0 ;}
	virtual ULONG __stdcall Release() { return 0 ;}

	// Interface IX implementation
	virtual void __stdcall Fx() { cout << "Fx" << endl ;}

	// Interface IY implementation
	virtual void __stdcall Fy() { cout << "Fy" << endl ;}
} ;

HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IUnknown)
	{
		trace("QueryInterface: Return pointer to IUnknown.") ;
		*ppv = static_cast<IX*>(this) ;
	}
	else if (iid == IID_IX)
	{
		trace("QueryInterface: Return pointer to IX.") ;
		*ppv = static_cast<IX*>(this) ;
	}
	else if (iid == IID_IY)
	{
		trace("QueryInterface: Return pointer to IY.") ;
		*ppv = static_cast<IY*>(this) ;
	}
	else
	{  	   
		trace("QueryInterface: Interface not supported.") ;
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ; // See Chapter 4.
	return S_OK ;
}

//
// Creation function
//
IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<IX*>(new CA) ;
	pI->AddRef() ;
	return pI ;
}

//
// IIDs
//
// {32bb8320-b41b-11cf-a6bb-0080c7b2d682}
static const IID IID_IX = 
	{0x32bb8320, 0xb41b, 0x11cf,
	{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}} ;

// {32bb8321-b41b-11cf-a6bb-0080c7b2d682}
static const IID IID_IY = 
	{0x32bb8321, 0xb41b, 0x11cf,
	{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}} ;

// {32bb8322-b41b-11cf-a6bb-0080c7b2d682}
static const IID IID_IZ = 
	{0x32bb8322, 0xb41b, 0x11cf,
	{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}} ;

//
// Client
//
int main()
{
	HRESULT hr ;

	trace("Client:         Get an IUnknown pointer.") ;
	IUnknown* pIUnknown = CreateInstance() ;

   
	trace("Client:         Get interface IX.") ;

	IX* pIX = NULL ; 
	hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Client:         Succeeded getting IX.") ;
		pIX->Fx() ;          // Use interface IX.
	}


	trace("Client:         Get interface IY.") ;

	IY* pIY = NULL ;
	hr = pIUnknown->QueryInterface(IID_IY, (void**)&pIY) ;
	if (SUCCEEDED(hr))
	{
		trace("Client:         Succeeded getting IY.") ;
		pIY->Fy() ;          // Use interface IY.
	}


	trace("Client:         Ask for an unsupported interface.") ;

	IZ* pIZ = NULL ;
	hr = pIUnknown->QueryInterface(IID_IZ, (void**)&pIZ) ;
	if (SUCCEEDED(hr))
	{
		trace("Client:         Succeeded in getting interface IZ.") ;
		pIZ->Fz() ;
	}
	else
	{
		trace("Client:         Could not get interface IZ.") ;
	}


	trace("Client:         Get interface IY from interface IX.") ;

	IY* pIYfromIX = NULL ;
	hr = pIX->QueryInterface(IID_IY, (void**)&pIYfromIX) ;
	if (SUCCEEDED(hr))
	{	
		trace("Client:         Succeeded getting IY.") ;
		pIYfromIX->Fy() ;
	}


	trace("Client:         Get interface IUnknown from IY.") ;

	IUnknown* pIUnknownFromIY = NULL ;
	hr = pIY->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromIY) ;
	if (SUCCEEDED(hr))
	{
		cout << "Are the IUnknown pointers equal?  " ;
		if (pIUnknownFromIY == pIUnknown)
		{
			cout << "Yes, pIUnknownFromIY == pIUnknown." << endl ;
		}
		else
		{
			cout << "No, pIUnknownFromIY != pIUnknown." << endl ;
		}
	}

	// Delete the component.
	delete pIUnknown ;

	return 0 ;
}
