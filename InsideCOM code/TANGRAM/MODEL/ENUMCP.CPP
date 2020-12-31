///////////////////////////////////////////////////////////
//
//
//	EnumCP.cpp - Implementation file for CEnumConnectionPoints
//
//
#include <windows.h>
#include <objbase.h>
#include <assert.h>

// Headers required by STL.
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

#include "EnumCP.h"

///////////////////////////////////////////////////////////
//
// Constructor --- Takes a single IConnectionPoint pointer
//
CEnumConnectionPoints::CEnumConnectionPoints(IConnectionPoint* pIConnectionPoint) 
:	CUnknown(NULL)
{
	// Make sure to AddRef the pointer.
	pIConnectionPoint->AddRef() ;	

	// Put the pointer into the list.
	m_list.push_back(pIConnectionPoint) ;

	// Initialize our cursor into the list.
	m_iter = m_list.begin() ;
}

///////////////////////////////////////////////////////////
//
// Constructor --- Takes a CConnectionPointList
//
CEnumConnectionPoints::CEnumConnectionPoints(CConnectionPointList& cplist) 
:	CUnknown(NULL)
{
	// Copy the CConnectionPointList AddRefing each interface pointer.
	CConnectionPointList::iterator p ; 
	for(p = cplist.begin() ; p != cplist.end() ; p++)
	{
		// Make sure to AddRef the pointer.
		(*p)->AddRef() ;	

		// Put the pointer into the list.
		m_list.push_back(*p) ;
	}

	// Initialize our cursor into the list.
	m_iter = m_list.begin() ;
}

///////////////////////////////////////////////////////////
//
// Copy Constructor
//
CEnumConnectionPoints::CEnumConnectionPoints(const CEnumConnectionPoints& X) 
:	CUnknown(NULL)
{
	// Copy the CConnectionPointList AddRefing each interface pointer.
	CConnectionPointList::iterator p ; //TODO const
	for(p = X.m_list.begin() ; p != X.m_list.end() ; p++)
	{
		// Make sure to AddRef the pointer.
		(*p)->AddRef() ;	

		// Put the pointer into the list.
		m_list.push_back(*p) ;
	}

	// Initialize our cursor into the list.
	m_iter = m_list.begin() ;
}


///////////////////////////////////////////////////////////
//
// Destructor
//
CEnumConnectionPoints::~CEnumConnectionPoints() 
{
	CConnectionPointList::iterator p ;
	for(p = m_list.begin() ; p != m_list.end() ; p++)
	{
		(*p)->Release() ;
		//TODO: Does the list delete itself?
	}
}


HRESULT __stdcall
CEnumConnectionPoints::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IEnumConnectionPoints)
	{
		return FinishQI(static_cast<IEnumConnectionPoints*>(this), ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}
///////////////////////////////////////////////////////////
//
//								IEnumConnections
//
///////////////////////////////////////////////////////////
//
// Next
//
HRESULT __stdcall 
CEnumConnectionPoints::Next(ULONG cConnections, IConnectionPoint** ppCP, ULONG* pFetched)
{
	if ((ppCP == NULL) || (pFetched == NULL && cConnections > 1))
	{
		return E_POINTER ;
	}
	
	ULONG count = 0 ;
	while ((m_iter != m_list.end()) && (count < cConnections))
	{
		// AddRef the sink pointer.
		(*m_iter)->AddRef() ;

		// Copy the connect data.
		*ppCP++ = *m_iter++ ;

		count++;
	}

	if (pFetched != NULL)
	{
		*pFetched = count ;
	}

	if (count < cConnections)
	{
		// Return S_FALSE if we cannot return cConnection elements.
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
CEnumConnectionPoints::Skip(ULONG celt)
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
CEnumConnectionPoints::Reset() 
{
	m_iter = m_list.begin() ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Clone
//
HRESULT __stdcall 
CEnumConnectionPoints::Clone(IEnumConnectionPoints** ppEnum) 
{
	if (ppEnum == NULL)
	{
		return E_POINTER ;
	}

	*ppEnum = new CEnumConnectionPoints(*this) ;

	return S_OK ;
}



