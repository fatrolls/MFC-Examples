#include <windows.h>
#include <stdlib.h>
#include <objbase.h>
#include <assert.h>

#include "Iface.h"
#include "Free.h"
#include "Cli-Free.h"
#include "Lock.h"

///////////////////////////////////////////////////////////
//
// Constructor
//
CClientFree::CClientFree() 
{
	// Interface pointer to object we manipulate
	m_pIX = NULL ;

	// Mutex to protect the above interface pointer
	m_hInterfaceMutex = CreateMutex(0, FALSE, 0) ;
	assert(m_hInterfaceMutex != NULL) ;
} 

///////////////////////////////////////////////////////////
//
// Destructor
//
CClientFree::~CClientFree()
{
	CSimpleLock Lock(m_hInterfaceMutex) ;

	if (m_pIX != NULL)
	{
		m_pIX->Release() ;
	}
}


///////////////////////////////////////////////////////////
//
// CreateTheComponent
//
HRESULT CClientFree::CreateComponentOnThread(const CLSID& clsid,
                                             const IID& iid,
                                             IUnknown** ppI) 
{

	HRESULT hr =
		::CoCreateInstance(clsid,
		                   NULL, 
		                   CLSCTX_INPROC_SERVER, 
		                   iid, 
		                   (void**)ppI) ;
	if (SUCCEEDED(hr))
	{
		// Query for the IX interface so we can use the component from the thread.
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
void CClientFree::WorkerFunction()
{
	CSimpleLock Lock(m_hInterfaceMutex) ;

	if (m_pIX)
	{
		m_pIX->Tick(1) ;
		m_pIX->Left() ;
	}
}

///////////////////////////////////////////////////////////
//
// ***** Worker Function for the second thread *****
//
void CClientFree2::WorkerFunction()
{
	CSimpleLock Lock(m_hInterfaceMutex) ;

	if (m_pIX)
	{
		m_pIX->Tick(-1) ;
		m_pIX->Right() ;
	}
}

///////////////////////////////////////////////////////////
//
// Share its interface pointer with another thread.
//
IX* CClientFree::ShareUnmarshaledInterfacePointer()
{
	CSimpleLock Lock(m_hInterfaceMutex) ;
	m_pIX->AddRef() ;
	return m_pIX ;
}

///////////////////////////////////////////////////////////
//
// Use the following interface pointer.
//
void CClientFree::UseUnmarshaledInterfacePointer(IX* pIX)
{
	CSimpleLock Lock(m_hInterfaceMutex) ;

	// Release the current pointer.
	if (m_pIX != NULL)
	{
		m_pIX->Release() ;
	}
	// Start using the new pointer.
	m_pIX = pIX ;
	m_pIX->AddRef() ;
}
