///////////////////////////////////////////////////////////
//
//
// GdiVisl.cpp - Implementation file for the Gdi Visual Component
//
//
///////////////////////////////////////////////////////////
//
// Include Files
//
#include <windows.h>
#include <olectl.h>

// STL Interfaces
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

#include "util.h"
#include "GdiVisl.h"

// Interfaces
#include "Canvas_I.h"
#include "World_I.h"
#include "Model_I.h"

// Sub-Components.
#include "EventSink.h"

// Other
#include <math.h>

///////////////////////////////////////////////////////////
//
// Creation function used by CFactory.
//
HRESULT CTangramGdiVisual::CreateInstance(	IUnknown* pOuterUnknown,
											CUnknown** ppNewComponent ) 
{
	if (pOuterUnknown != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	
	*ppNewComponent = new CTangramGdiVisual(pOuterUnknown) ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	NondelegatingQueryInterface
//
HRESULT __stdcall
CTangramGdiVisual::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_ITangramVisual)
	{
		return FinishQI(static_cast<ITangramVisual*>(this), ppv) ;
	}
	else if (iid == IID_ITangramGdiVisual) 
	{
		return FinishQI(static_cast<ITangramGdiVisual*>(this), ppv) ;
	}
	else if (iid == IID_ITangramModelEvent) 
	{
		return FinishQI(static_cast<ITangramModelEvent*>(this), ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}

///////////////////////////////////////////////////////////
//
// Constructor
//
CTangramGdiVisual::CTangramGdiVisual(IUnknown* pOuterUnknown)
:	CUnknown(pOuterUnknown),
	m_pModel(NULL), 
	m_pGdiWorld(NULL),
	m_bSelected(FALSE),
	m_pIConnectionPoint(NULL),
	m_dwCookie(0)
{
}

///////////////////////////////////////////////////////////
//
// Destructor
//
CTangramGdiVisual::~CTangramGdiVisual()
{
	// Release the event source component.
	if (m_pIConnectionPoint != NULL)
	{
		// We no longer need to be enformed of events
		HRESULT hr = m_pIConnectionPoint->Unadvise(m_dwCookie) ;
		ASSERT_HRESULT(hr) ;

		m_pIConnectionPoint->Release() ;
	}

	// We keep a strong reference to the model.
	// Therefore, we need to release it here.
	m_pModel->Release() ;
	m_pModel = NULL ;

	// We maintain a weak reference to GdiWorld to avoid 
	// reference cycles. A weak reference means that we
	// do not AddRef or Release the pointer.
	//m_pGdiWorld->Release() ;
	//m_pGdiWorld = NULL ;


	// Delete the vertex array.
	if (m_ptVertices != NULL)
	{
		delete [] m_ptVertices ;
	}

}

///////////////////////////////////////////////////////////
//
//						ITangramVisual
//
///////////////////////////////////////////////////////////
//
// ITangramVisual::SetSelected Implementation.
//
HRESULT CTangramGdiVisual::SetSelected(BOOL bSelected)
{
	m_bSelected = bSelected ;

	// Add the boundary to the update region.
	RECT rectBounding;
	GetBoundingRect(&rectBounding) ;
	HRESULT hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	hr = m_pGdiWorld->Animate() ; 
	ASSERT_HRESULT(hr) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// ITangramGdiVisual::GetModel Implementation
//
HRESULT CTangramGdiVisual::GetModel(const IID& iid, IUnknown** ppI)
{
	if (!IsValidInterfaceOutParam(ppI))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

   return m_pModel->QueryInterface(iid, (void**)ppI)  ;
}
///////////////////////////////////////////////////////////
//
//						ITangramGdiVisual
//
///////////////////////////////////////////////////////////
//
// ITangramGdiVisual::Initialize Implementation
//
HRESULT CTangramGdiVisual::Initialize(ITangramModel* pModel, ITangramGdiWorld* pWorld)
{
	if (!IsValidInterface(pModel) || !IsValidInterface(pWorld))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	if (m_pModel != NULL || m_pGdiWorld != NULL)
	{
		// Cannot re-initialize.
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Keep a strong reference to the model.
	m_pModel = pModel ;
	m_pModel->AddRef() ;

	// To avoid a cyclical reference count, we have a weak reference to GdiWorld.
	// Therefore, we do not AddRef this pointer.
	m_pGdiWorld = pWorld ;

	// Get the number of vertices in the model.
	HRESULT hr = m_pModel->GetNumberOfVertices(&m_cVertices) ;
	ASSERT_HRESULT(hr) ;

	// Create an array to hold the vertices.
	m_ptVertices = new POINT[m_cVertices] ;

	//	----- Set up event sync ----- 
	// Create a sink object. 
	ITangramModelEvent* pITangramModelEvent = new CTangramModelEventSink(this) ; 

	// Get the connection point container.
	IConnectionPointContainer* pContainer = NULL ;
	hr = pModel->QueryInterface(IID_IConnectionPointContainer, (void**)&pContainer) ;
	ASSERT_HRESULT(hr) ;

	// Get our desired connection point. Cache the pointer so we don't have to get it again.
	hr = pContainer->FindConnectionPoint(IID_ITangramModelEvent, &m_pIConnectionPoint) ;
	pContainer->Release() ;
	ASSERT_HRESULT(hr) ;

	// Ask the visual to advise us of any changes.
	hr = m_pIConnectionPoint->Advise(pITangramModelEvent, &m_dwCookie) ;
	ASSERT_HRESULT(hr) ;

	// We don't need to keep a reference to the sink.
	pITangramModelEvent->Release() ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// ITangramGdiVisual::DrawOn Implementation
//
HRESULT CTangramGdiVisual::DrawOn(ITangramCanvas* pCanvas)
{
	// Preconditions.
	if (!IsValidInterface(pCanvas))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Get a device context to draw on from the canvas.
	HDC hDC ;
	HRESULT hr = pCanvas->GetHDC(&hDC) ;
	ASSERT_HRESULT(hr) ;

	// Make a pen.
	HPEN hPen = ::CreatePen(PS_SOLID, 1, m_bSelected ? RGB(255,0,0) : RGB(128,128,128)) ;       
	HPEN hOldPen = ::SelectObject(hDC, hPen) ;

	// Make a brush.
	HBRUSH hOldBrush = ::SelectObject(hDC, ::GetStockObject(m_bSelected ? NULL_BRUSH : LTGRAY_BRUSH)) ;

	// Draw the polygon.
	::Polygon(hDC, m_ptVertices, m_cVertices) ;

	// CleanUp
	::SelectObject(hDC, hOldPen) ;
	::SelectObject(hDC, hOldBrush) ;

	::DeleteObject(hPen) ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// ITangramGdiVisual::IsPtIn Implementation
//
HRESULT CTangramGdiVisual::IsPtIn(POINT pt)
{
	ASSERT( m_ptVertices != NULL) ;
	ASSERT( m_cVertices != 0) ;

	// Create a region.
	HRGN hrgnPolygon = ::CreatePolygonRgn(m_ptVertices, m_cVertices, ALTERNATE) ;

	// Is point in region?
	BOOL bResult = ::PtInRegion(hrgnPolygon, pt.x, pt.y) ;

	// Cleanup
	::DeleteObject(hrgnPolygon) ;

	// Return the results.
	return (bResult) ? S_OK : S_FALSE ;
}

///////////////////////////////////////////////////////////
//
// ITangramGdiVisual::GetBoundingRect
//
// Results:
//			S_FALSE	-	If the boundary doesn't make sense. 
//
HRESULT CTangramGdiVisual::GetBoundingRect(RECT* pBoundingRect)
{
	if (!IsValidAddress(pBoundingRect, sizeof(RECT), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	HRESULT hr = S_OK ;
	// Create a region.
	HRGN hrgnPolygon = ::CreatePolygonRgn(m_ptVertices, m_cVertices, ALTERNATE) ;

	// Get the bounding box for the region.
	RECT rect ;
	int bRgnType = ::GetRgnBox(hrgnPolygon, &rect) ;
	if (bRgnType == NULLREGION || bRgnType == ERROR)
	{
		::SetRectEmpty(pBoundingRect) ;
		hr = S_FALSE ;
	}
	else
	{
		// Add room for the pen width boundary.
		pBoundingRect->top    = rect.top    - 2 ;
		pBoundingRect->bottom = rect.bottom + 2 ;
		pBoundingRect->left   = rect.left   - 2 ;
		pBoundingRect->right  = rect.right  + 2 ;
	}

	// Cleanup
	::DeleteObject(hrgnPolygon) ;

	return hr ;
}
///////////////////////////////////////////////////////////
//
//					ITangramModelEvent
//
///////////////////////////////////////////////////////////
//
// ITangramModelEvent::OnModelChange
//
HRESULT __stdcall CTangramGdiVisual::OnModelChange()
{
	// Get Current Bounding Rectangle
	RECT rectBounding;
	GetBoundingRect(&rectBounding) ;
	HRESULT hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	// Get the new vertices.
	SyncToModel() ;

	// Get New Bounding Rectangle
	GetBoundingRect(&rectBounding) ;
	hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	hr = m_pGdiWorld->Animate() ; 
	ASSERT_HRESULT(hr) ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
//					Helper Functions
//
///////////////////////////////////////////////////////////
//
//
//
void CTangramGdiVisual::SyncToModel() 
{
	// Create an array to hold the new vertices.
	TangramPoint2d* pointds = new TangramPoint2d[m_cVertices] ;

	// Get the vertices from the model.
	HRESULT hr = m_pModel->GetVertices(m_cVertices, pointds) ;
	ASSERT_HRESULT(hr) ;

	// Convert the vertices to our coordinates.
	for (int i = 0 ; i < m_cVertices ; i++)
	{
		hr = m_pGdiWorld->ModelToDevice(pointds[i], &m_ptVertices[i]) ;
		ASSERT_HRESULT(hr) ;
	}

	// Cleanup.
	delete [] pointds;
}




