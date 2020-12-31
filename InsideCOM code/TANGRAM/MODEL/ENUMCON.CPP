///////////////////////////////////////////////////////////
//
//
// EnumCon.cpp - Implementation of CEnumConnections
//
//
#include <windows.h>
#include <olectl.h>
#include <assert.h>

#include "EnumCon.h"

///////////////////////////////////////////////////////////
//
// Constructor
//
CEnumConnections::CEnumConnections(CConnectDataList& ConnectData) 
:	CUnknown(NULL)
{
	// Copy the CConnectDataList AddRefing each interface pointer.
	CConnectDataList::iterator p ; 
	for(p = ConnectData.begin() ; p != ConnectData.end() ; p++)
	{
		// Copy the data into a temp structure
		CONNECTDATA cd ;
		cd.dwCookie = p->dwCookie ;
		cd.pUnk = p->pUnk ;

		// Make sure to AddRef the pointer.
		cd.pUnk->AddRef() ;	

		m_list.push_back(cd) ;
	}

	m_iter = m_list.begin() ;
}

///////////////////////////////////////////////////////////
//
// Copy Constructor
//
CEnumConnections::CEnumConnections(const CEnumConnections& X) 
:	CUnknown(NULL)
{
	// Copy the CConnectDataList AddRefing each interface pointer.
	CConnectDataList::iterator p ; //TODO const
	for(p = X.m_list.begin() ; p != X.m_list.end() ; p++)
	{
		CONNECTDATA cd ;
		cd.dwCookie = p->dwCookie ;
		cd.pUnk = p->pUnk ;
		cd.pUnk->AddRef() ;

		m_list.push_back(cd) ;
	}

	m_iter = m_list.begin() ;
}


///////////////////////////////////////////////////////////
//
// Destructor
//
CEnumConnections::~CEnumConnections() 
{
	CConnectDataList::iterator p ;
	for(p = m_list.begin() ; p != m_list.end() ; p++)
	{
		p->pUnk->Release() ;
	}
}


HRESULT __stdcall
CEnumConnections::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IEnumConnections)
	{
		return FinishQI(static_cast<IEnumConnections*>(this), ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}
///////////////////////////////////////////////////////////
//
//					IEnumConnections
//
///////////////////////////////////////////////////////////
//
// Next
//
HRESULT __stdcall 
CEnumConnections::Next(ULONG celt, CONNECTDATA* pelt, ULONG* pceltFetched)
{
	if ((pelt == NULL) || (pceltFetched == NULL && celt > 1))
	{
		return E_POINTER ;
	}
	
	ULONG count = 0 ;
	while ((m_iter != m_list.end()) && (count < celt))
	{
		// AddRef the sink pointer.
		m_iter->pUnk->AddRef() ;

		// Copy the connect data.
		*pelt++ = *m_iter++ ;

		count++;
	}

	if (pceltFetched != NULL)
	{
		*pceltFetched = count ;
	}

	if (count < celt)
	{
		// Return S_FALSE if we cannot return celt elements.
		return S_FALSE ;
	}
	else
	{
		return S_OK ;
	}
}

///////////////////////////////////////////////////////////
//
// Skip
//
HRESULT __stdcall 
CEnumConnections::Skip(ULONG celt)
{
	ULONG count = 0 ;
	while ((m_iter != m_list.end()) && (count < celt))
	{
		m_iter++ ;
		count++ ;
	}

	if (count < celt)
	{
		// Return S_FALSE if we cannot return celt elements.
		return S_FALSE ;
	}
	else
	{
		return S_OK ;
	}
}

///////////////////////////////////////////////////////////
//
// Reset
//
HRESULT __stdcall 
CEnumConnections::Reset() 
{
	m_iter = m_list.begin() ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Clone
//
HRESULT __stdcall 
CEnumConnections::Clone(IEnumConnections** ppEnum) 
{
	if (ppEnum == NULL)
	{
		return E_POINTER ;
	}

	*ppEnum = new CEnumConnections(*this) ;

	return S_OK ;
}

