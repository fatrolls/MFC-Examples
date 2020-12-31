#include <windows.h> 
#include <stdlib.h>
#include <objbase.h>
#include <assert.h>

#include "Iface.h"
#include "Apart.h"
#include "Cli-Apt.h"

///////////////////////////////////////////////////////////
//
// Constructor
//
CClientApartment::CClientApartment() 
{
	m_pIX = NULL ;
} 

///////////////////////////////////////////////////////////
//
// Destructor
//
CClientApartment::~CClientApartment()
{
	if (m_pIX != NULL)
	{
		m_pIX->Release() ;
	}
}


///////////////////////////////////////////////////////////
//
// CreateTheComponent
//
HRESULT CClientApartment::CreateComponentOnThread(const CLSID& clsid,
                                                  const IID& iid,
                                                  IUnknown** ppI) 
{
	HRESULT hr = ::CoCreateInstance(clsid,
	                                NULL, 
	                                CLSCTX_INPROC_SERVER, 
	                                iid, 
	                                (void**)ppI) ;
	if (SUCCEEDED(hr))
	{
		// Query for the IX interface to use in WorkerFunction.
		hr = (*ppI)->QueryInterface(IID_IX, (void**)&m_pIX) ;
		if (FAILED(hr))
		{
			// If we can't use it, don't let anybody use it.
			(*ppI)->Release() ;
			return E_FAIL ;
		}
		
	}
	
	return hr ;
}

///////////////////////////////////////////////////////////
//
// WorkerFunction - This function is called by the worker thread.
//
void CClientApartment::WorkerFunction()
{
	if (m_pIX)
	{
		m_pIX->Tick() ;
	}
}
