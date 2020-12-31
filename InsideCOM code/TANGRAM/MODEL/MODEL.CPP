///////////////////////////////////////////////////////////
//
//
//	Model.cpp - Implementation file for the TangramModel component
//
//
#include <windows.h>
#include <olectl.h>

// Headers required by STL.
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

// Utilities
#include "util.h"

// Our header file.
#include "Model.h"

// Interface and component definition generated from IDL
#include "Event_I.h"		// Definitions of IID_ITangramModelEvent
#include "CntPoint.h"		// ConnectionPoint Component
#include "EnumCP.h"			// ConnectionPoint Enumerator

// Other include files
#include "math.h"

// For Registration Only
#include <oleauto.h> 
#include <Model_C.h> 

///////////////////////////////////////////////////////////
//
// Constants
//
static const double PI = 3.141592654;


///////////////////////////////////////////////////////////
//
// Creation function used by CFactory.
//
HRESULT CTangramModel::CreateInstance(	IUnknown* pOuterUnknown,
										CUnknown** ppNewComponent ) 
{
	if (pOuterUnknown != NULL)
	{
		// Don't allow aggregation. Just for the heck of it.
		return CLASS_E_NOAGGREGATION;
	}
	
	*ppNewComponent = new CTangramModel(pOuterUnknown) ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	NondelegatingQueryInterface
//
HRESULT __stdcall 
CTangramModel::NondelegatingQueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_ITangramModel)
	{
		return FinishQI(static_cast<ITangramModel*>(this), ppv) ;
	}
	else if (iid == IID_ITangramTransform) 
	{
		return FinishQI(static_cast<ITangramTransform*>(this), ppv) ;
	}
	else if (iid == IID_IConnectionPointContainer)
	{
		return FinishQI(static_cast<IConnectionPointContainer*>(this), ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}

///////////////////////////////////////////////////////////
//
//	Constructor
//
CTangramModel::CTangramModel(IUnknown* pOuterUnknown)
: CUnknown(pOuterUnknown),
	m_pVertices(NULL),
	m_pTransformVertices(NULL),
	m_cVertices(0),
	m_dDegrees(0.0),		// Zero Degrees
	m_cosDegrees(1.0),		// cos(0) = 1.0
	m_sinDegrees(0.0),		// sin(0) = 0.0
	m_pConnectionPoint(NULL) 
{
	m_ptdTranslate.x = 0.0 ;
	m_ptdTranslate.y = 0.0 ;

	// Create the connection point object. 
	// CTangramModel treats CConnectionPoint as a C++ object and not like a COM object.
	// Everyone else deals with CConnectionPoint through COM interfaces.
	m_pConnectionPoint = new CConnectionPoint(this, &IID_ITangramModelEvent) ;
}

///////////////////////////////////////////////////////////
//
// Destructor
//
CTangramModel::~CTangramModel()
{
	if (m_pVertices != NULL) 
	{
		delete [] m_pVertices ;
	}

	if (m_pTransformVertices != NULL) 
	{
		delete [] m_pTransformVertices ;
	}

	// Delete the connection point object
	if (m_pConnectionPoint != NULL)
	{
		// CTangramModel treads m_pConnectionPoint as a C++ object.
		delete m_pConnectionPoint ;
	}
}

///////////////////////////////////////////////////////////
//
//						ITangramModel Interface 
//
///////////////////////////////////////////////////////////
//
//	GetNumberOfVertices
//
HRESULT CTangramModel::GetNumberOfVertices(long* pcVertices)
{
	// Preconditions.
	if (IsValidAddress(pcVertices, sizeof(long), TRUE))
	{
		*pcVertices = m_cVertices ;
		return S_OK ;
	}
	else
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}
}

///////////////////////////////////////////////////////////
//
//	GetVertices
//
HRESULT CTangramModel::GetVertices(long cVertices, TangramPoint2d* points)
{
	// Preconditions
	if (cVertices < m_cVertices)
	{
		ASSERT(0) ;
		return E_OUTOFMEMORY ;
	}

	if (cVertices < 1)
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}

	if (!IsValidAddress(points, sizeof(TangramPoint2d)*cVertices, TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	if (m_pVertices == NULL || m_cVertices < 1)
	{
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Now we can do the actual work.

	// Apply the transform before returning the vertices.
	applyTransform() ;
	for(long i = 0 ; i < m_cVertices ; i++)
	{
		points[i] = m_pTransformVertices[i] ;
	}
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// SetVetices
//
HRESULT CTangramModel::SetVertices(long cVertices, TangramPoint2d* points)
{
	// Preconditions
	if (cVertices < 1)
	{
		ASSERT(0) ;
		return E_INVALIDARG ;
	}

	if (!IsValidAddress(points, sizeof(TangramPoint2d)*cVertices, FALSE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Delete existing arrays.
	delete [] m_pVertices ;
	delete [] m_pTransformVertices ;

	// Create new arrays.
	m_cVertices = cVertices ;
	m_pVertices = new TangramPoint2d[m_cVertices] ;
	m_pTransformVertices = new TangramPoint2d[m_cVertices] ;
	
	// Initialize array.
	for(long i = 0 ; i < m_cVertices ; i++)
	{
		m_pVertices[i] = points[i] ;
	}

	// Signal that model has changed.
	FireEvent() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//					ITransform Interface
//
///////////////////////////////////////////////////////////
//
// Translate
//
HRESULT CTangramModel::Translate(double x, double y)
{
	m_ptdTranslate.x = x ;
	m_ptdTranslate.y = y ;

	FireEvent() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// GetRotation
//
HRESULT CTangramModel::GetRotation(double* pRotation)
{
	// Preconditions.
	if (!IsValidAddress(pRotation, sizeof(double), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER;
	}

	// Return value in degrees. May be negative.
	*pRotation = m_dDegrees;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Rotate the model.
//
HRESULT CTangramModel::Rotate(double dDegrees)
{
	m_dDegrees = dDegrees ;

	double dRads= fmod(dDegrees,360.0)*PI/180.0;
	m_cosDegrees = cos(dRads) ;
	m_sinDegrees = sin(dRads) ;

	FireEvent() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// GetTranslation
//
HRESULT CTangramModel::GetTranslation(TangramPoint2d* ppoint)
{
	// Preconditions.
	if (!IsValidAddress(ppoint, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	ppoint->x = m_ptdTranslate.x ;
	ppoint->y = m_ptdTranslate.y ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
//						IConnectionPointContainer
//
///////////////////////////////////////////////////////////
//
// EnumConnectionPoints
//
HRESULT CTangramModel::EnumConnectionPoints(IEnumConnectionPoints **ppEnum) 
{
	// Preconditions.
	if (!IsValidInterfaceOutParam(ppEnum))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Construct the enumerator object.
	IEnumConnectionPoints* pEnum = new CEnumConnectionPoints(m_pConnectionPoint) ;

	// The contructor AddRefs for us.
	*ppEnum = pEnum ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// FindConnectionPoint
//
HRESULT CTangramModel::FindConnectionPoint(REFIID riid, IConnectionPoint **ppCP)
{
	// Preconditions.
	if (!IsValidInterfaceOutParam(ppCP))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Model only supports a single connection point.
	if (riid != IID_ITangramModelEvent)
	{
		ASSERT(0) ;
		*ppCP = NULL ;
		return  CONNECT_E_NOCONNECTION ;
	}

	if (m_pConnectionPoint == NULL)
	{
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Get the interface point to the connection point object.
	IConnectionPoint* pIConnectionPoint = m_pConnectionPoint ;

	// AddRef the interface.
	pIConnectionPoint->AddRef() ; 

	// Return the interface to the client.
	*ppCP = pIConnectionPoint ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//						Helper Functions
//
///////////////////////////////////////////////////////////
//
// FireEvent
//
void CTangramModel::FireEvent()
{
	// Get the connection enummerator
	IEnumConnections* pEnum = NULL ;
	HRESULT hr = m_pConnectionPoint->EnumConnections(&pEnum) ;
	ASSERT_HRESULT(hr) ;

	CONNECTDATA cd ;
	while((hr = pEnum->Next(1, &cd, NULL)) == S_OK)
	{
		ASSERT_HRESULT(hr) ;

		// Get ITangramModelEvent interface pointer.
		ITangramModelEvent* pITangramModelEvent= NULL ;
		hr = cd.pUnk->QueryInterface(IID_ITangramModelEvent, (void**)&pITangramModelEvent) ;
		ASSERT_HRESULT(hr) ;

		// Fire the event.
		pITangramModelEvent->OnModelChange() ;

		// Release event interface.
		pITangramModelEvent->Release() ;
		
		// Release connect data pointer
		cd.pUnk->Release() ;
	}
	ASSERT_HRESULT(hr) ;

	// Release enummerator.
	pEnum->Release() ;
}

///////////////////////////////////////////////////////////
//
// applyTransform Helper function.
//
void CTangramModel::applyTransform()
{
	if (m_dDegrees == 0.0)
	{
		// Optimization for unrotated polygon.
		for(long i = 0 ; i < m_cVertices; i++)
		{
			m_pTransformVertices[i].x = m_pVertices[i].x + m_ptdTranslate.x ;
			m_pTransformVertices[i].y = m_pVertices[i].y + m_ptdTranslate.y ;
		}
	}
	else
	{
		for(long i = 0 ; i < m_cVertices; i++)
		{
			m_pTransformVertices[i].x = m_pVertices[i].x*m_cosDegrees - m_pVertices[i].y*m_sinDegrees + m_ptdTranslate.x ;
			m_pTransformVertices[i].y = m_pVertices[i].x*m_sinDegrees + m_pVertices[i].y*m_cosDegrees + m_ptdTranslate.y ;
		}
	}
}
