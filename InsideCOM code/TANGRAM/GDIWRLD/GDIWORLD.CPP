///////////////////////////////////////////////////////////
//
//
// GdiWorld.cpp	- Implementation of the Gdi World component
//
//
//
#include <windows.h>
#include <math.h>
#include <comcat.h>	// Component Categories

// STL Headers 
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

#include "util.h"
#include "GdiWorld.h"

// MIDL generated header files
#include "Canvas_I.h" // For Interface Declarations.
#include "Model_I.h" 
#include "Visual_I.h"
#include "World_C.h" // For CLSID Declarations. 
#include "Canvas_C.h"

// Definition and Declaration of CATID_TangramWorldCategory 
#include <initguid.h>
#include "WorldCat.h" 

///////////////////////////////////////////////////////////
//
// Creation function used by CFactory.
//
HRESULT CGdiWorld::CreateInstance(	IUnknown* pOuterUnknown,
									CUnknown** ppNewComponent ) 
{
	if (pOuterUnknown != NULL)
	{
		// Don't allow aggregation. Just for the heck of it.
		return CLASS_E_NOAGGREGATION;
	}
	
	*ppNewComponent = new CGdiWorld(pOuterUnknown) ;
	return S_OK ;
}
///////////////////////////////////////////////////////////
//
//	SpecialReg -	Used to register and unregister the component
//						categories.
//
void CGdiWorld::SpecialReg(BOOL bRegister)
{
	// Create the standard COM Category Manager
	ICatRegister* pICatRegister = NULL ;
	HRESULT hr = ::CoCreateInstance(	CLSID_StdComponentCategoriesMgr,
										NULL, CLSCTX_ALL, IID_ICatRegister,
										(void**)&pICatRegister) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not create the ComCat component.", hr);
		return ;
	}

	// Fill in a Category Info structure.
	CATEGORYINFO CatInfo ;
	CatInfo.catid				= CATID_TangramWorldCategory ;
	CatInfo.lcid				= LOCALE_SYSTEM_DEFAULT ;
	wcscpy(CatInfo.szDescription, L"Tangram World Component Category" ) ;

	// Array of Categories
	int cIDs = 1 ;
	CATID IDs[1] ;
	IDs[0] = CATID_TangramWorldCategory ;

	// Register or Unregister
	if (bRegister)
	{
		// Register the component category.
		hr = pICatRegister->RegisterCategories(1, &CatInfo) ;
		ASSERT_HRESULT(hr) ; 

		// Register this component as a member of TangramWorldCategory
		hr = pICatRegister->RegisterClassImplCategories(	CLSID_TangramGdiWorld,
															cIDs, IDs ) ;
		ASSERT_HRESULT(hr) ; 
	}
	else
	{
		// Unregister the component from its categories.
		hr = pICatRegister->UnRegisterClassImplCategories(	CLSID_TangramGdiWorld,
															cIDs, IDs);
		ASSERT_HRESULT(hr) ; 

		// --- Check to see if there are other components in this category before we delete it. ---

		// Get the ICatInformation interface.
		ICatInformation* pICatInformation = NULL ;
		hr = pICatRegister->QueryInterface(IID_ICatInformation, (void**)&pICatInformation) ;
		ASSERT_HRESULT(hr) ;

		// Get the IEnumCLSID interface.
		IEnumCLSID* pIEnumCLSID = NULL ;
		hr = pICatInformation->EnumClassesOfCategories(cIDs, IDs, 0, NULL, &pIEnumCLSID) ;
		ASSERT_HRESULT(hr) ;
		
		// Get the next CLSID in the list.
		CLSID clsid ;
		hr = pIEnumCLSID->Next(1, &clsid, NULL) ;
		ASSERT_HRESULT(hr) ;

		// If hr is S_FALSE, there no components are in this category, so remove it.
		if (hr == S_FALSE) 
		{
			// Unregister the component category
			hr = pICatRegister->UnRegisterCategories(cIDs, IDs) ;
			ASSERT_HRESULT(hr) ; 
		}

		// CleanUp
		pIEnumCLSID->Release() ;
		pICatInformation->Release() ;
	}

	if (pICatRegister)
	{
		pICatRegister->Release() ;
	}
}

///////////////////////////////////////////////////////////
//
//	NondelegatingQueryInterface
//
HRESULT __stdcall 
CGdiWorld::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_ITangramWorld)
	{
		return FinishQI(static_cast<ITangramWorld*>(this), ppv) ;
	}
	else if (iid == IID_ITangramGdiWorld) 
	{
		return FinishQI(static_cast<ITangramGdiWorld*>(this), ppv) ;
	}
	else if (iid == IID_ITangramCanvas)
	{
		return FinishQI(m_pCanvas, ppv) ;
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
CGdiWorld::CGdiWorld(IUnknown* pOuterUnknown)
: CUnknown(pOuterUnknown),
	m_pCanvas(NULL),
	m_pCanvasUnknown(NULL)
{
	m_sizedScale.cx = m_sizedScale.cy = 1.0 ;
	m_ptdDeviceOrg.x = m_ptdDeviceOrg.y = 0.0 ;

	::SetRectEmpty(&m_rectUpdate) ;
}


///////////////////////////////////////////////////////////
//
//	Destructor
//
CGdiWorld::~CGdiWorld()
{
	CVisualList::iterator p ;
	for(p = m_VisualList.begin() ; p != m_VisualList.end() ; p++)
	{
		(*p)->Release() ;
	}

	// We already cleaned up the aggregated objects in FinalRelease.
	ASSERT(m_pCanvasUnknown == NULL) ;
	ASSERT(m_pCanvas == NULL) ;

}

///////////////////////////////////////////////////////////
//
//	FinalRelease -- Clean up the aggreated objects.
//
void CGdiWorld::FinalRelease()
{
	CUnknown::FinalRelease() ;

	// Release the ICanvas interface on the aggregated object.
	if (m_pCanvas != NULL)
	{
		// Add a reference back to the outer object.
		GetOuterUnknown()->AddRef() ;
		// Remove the reference on the inner and outer objects.
		m_pCanvas->Release() ;
		m_pCanvas = NULL ;
	}

	// Release our hold on the inner object.
	if (m_pCanvasUnknown != NULL)
	{
		m_pCanvasUnknown->Release() ;
		m_pCanvasUnknown = NULL ;
	}
}


///////////////////////////////////////////////////////////
//
//					ITangramWorld Implementation
//
///////////////////////////////////////////////////////////
//
//	Initialize
//
HRESULT CGdiWorld::Initialize(HWND hWnd, double modelWidth, double modelHeight)
{
	// Preconditions
	if (m_pCanvas != NULL) 
	{
		ASSERT(m_pCanvas == NULL) ;
		return E_FAIL ;
	}

	if ((hWnd == NULL) || (!::IsWindow(hWnd)) || 
		(modelWidth == 0.0) || (modelHeight == 0.0))
	{
		ASSERT(hWnd != NULL) ;
		ASSERT(::IsWindow(hWnd)) ;
		ASSERT( m_pCanvas != NULL) ;
		ASSERT( (modelWidth != 0.0) && (modelHeight != 0.0)) ;
		return E_INVALIDARG ; 
	}
	
	// ----- Aggreate the canvas object to handle Canvas messages ------

	// Create the canvas on which the world draws.
	HRESULT hr = ::CoCreateInstance(	CLSID_TangramCanvas, 
										GetOuterUnknown(), 
										CLSCTX_INPROC_SERVER,
										IID_IUnknown, (void**)&m_pCanvasUnknown) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not aggregate the canvas component.", hr) ;
		return E_FAIL ;
	}

	//------ Get the ITangramCanvas interface -----

	// Query for the ITangramCanvas interface.
	hr = m_pCanvasUnknown->QueryInterface(IID_ITangramCanvas, (void**)&m_pCanvas) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not get required interface from Canvas.", hr) ;
		m_pCanvas->Release() ;
		m_pCanvas = NULL ;
		return E_FAIL ;
	}

	// Release the AddRef placed on the outer object by the QI call above.
	GetOuterUnknown()->Release() ;

		// ----- Initialize the canvas component. -----
	RECT rectClient ;
	::GetClientRect(hWnd, &rectClient) ;

	int widthClient = rectClient.right - rectClient.left ;
	int heightClient = rectClient.bottom - rectClient.top ;
	hr = m_pCanvas->Initialize(hWnd, widthClient, heightClient) ;
	ASSERT_HRESULT(hr) ; 

	// ----- More Initializtion -----

	// Paint the background of the canvas black.
	AddUpdateRect(rectClient);
	Animate() ;

	//
	// Map the model world (modelWidth x modelHeight) 
	// (0,0) in the lower left corner to the physical screen (m_sizeDevice)
	// (0,0) in the upper left corner.
	// Always set up an isotropic world where 1 x model unit = 1 y model unit.
	//

	TangramSize2d sizedDevice ;
	sizedDevice.cx = static_cast<double>(widthClient) ;
	sizedDevice.cy = static_cast<double>(heightClient) ;

	m_sizedScale.cx = sizedDevice.cx / modelWidth;
	m_sizedScale.cy = sizedDevice.cy / modelHeight ;
	if (m_sizedScale.cx > m_sizedScale.cy)
	{
		m_sizedScale.cx = m_sizedScale.cy ;
		dModelUnits = modelHeight * 100000 ;
		dDeviceUnits = sizedDevice.cy ;
	}
	else
	{
		m_sizedScale.cy = m_sizedScale.cx ;
		dModelUnits = modelWidth * 100000 ;
		dDeviceUnits = sizedDevice.cx ;
	}
	m_sizedScale.cy = -m_sizedScale.cy ; // Negative scaling make Y axis point up.

	// Move origin to lower left corner of screen.
	m_ptdDeviceOrg.x = 0.0 ;
	m_ptdDeviceOrg.y = sizedDevice.cy ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// DeviceToModel -- Do not use with size parameters because addin the org...
//
HRESULT CGdiWorld::DeviceToModel(POINT ptIn, TangramPoint2d* pptdOut)
{
	if (!IsValidAddress(pptdOut, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	pptdOut->x = (static_cast<double>(ptIn.x) - m_ptdDeviceOrg.x) / m_sizedScale.cx ;
	pptdOut->y = (static_cast<double>(ptIn.y) - m_ptdDeviceOrg.y) / m_sizedScale.cy ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// VisualFromPoint - Finds the visual which contains POINT pt.
//							Returns the requested IID for the visual.
//	
//	Results:
//			S_OK	-	Found a Visual.
//			S_FALSE	-	No visual containing this point. 
//						*ppITangramVisual will be NULL.						
//
HRESULT CGdiWorld::VisualFromPoint(	POINT pt,
									REFIID iid, 
									IUnknown** ppITangramVisual) 
{
	// Preconditions.
	if (!IsValidInterfaceOutParam(ppITangramVisual))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Initialize out parameter.
	*ppITangramVisual = NULL ;

	// Search the list in reverse order because the
	// most recently selected and last painted object is
	// on the end.
	CVisualList::reverse_iterator ppVisual ;
	for(ppVisual = m_VisualList.rbegin() ; ppVisual != m_VisualList.rend() ; ppVisual++)
	{
		HRESULT hr = (*ppVisual)->IsPtIn(pt) ;
		ASSERT(SUCCEEDED(hr)) ;
		if (hr == S_OK) 
		{
			return (*ppVisual)->QueryInterface(iid, (void**)ppITangramVisual) ;
		}
	}
	return S_FALSE ;
}

///////////////////////////////////////////////////////////
//
// ITangramWorld::CreateVisualForModel Implementation
//
HRESULT CGdiWorld::CreateVisualForModel(ITangramModel* pModel)
{
	// Preconditions.
	if (!IsValidInterface(pModel))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Create the visual for this model.
	ITangramGdiVisual* pVisual = NULL ;
	HRESULT hr = ::CoCreateInstance(	CLSID_TangramGdiVisual,
										NULL,
										CLSCTX_INPROC_SERVER,
										IID_ITangramGdiVisual, 
										(void**)&pVisual) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not create visual for model.", hr) ;
		return  E_FAIL ;
	}

	// Initialize visual.
	hr = pVisual->Initialize(pModel, this) ; 
	ASSERT_HRESULT(hr) ;

	// Add visual to list.
	m_VisualList.push_back(pVisual) ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
//	SelectVisual 
//
HRESULT CGdiWorld::SelectVisual(ITangramVisual* pSelectedVisual, BOOL bSelect)
{
	// Precondition
	if (!IsValidInterface(pSelectedVisual))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Move the selected object to the end of the list so that it
	// will paint last.
	pSelectedVisual->SetSelected(bSelect) ;

	if (bSelect)
	{
		// Cycle through the array looking for pSelectedVisual.
		CVisualList::iterator ppV ;
		for(ppV = m_VisualList.begin() ; ppV != m_VisualList.end() ; ppV++)
		{
			// Must compare IUnknown pointers.
			if (::InterfacesAreOnSameComponent(*ppV, pSelectedVisual))
			{
				// Move to the back of the list.
				m_VisualList.push_back(*ppV) ;
				// Remove other entry.
				m_VisualList.erase(ppV) ; 

				return S_OK ;
			}
		}
		return E_FAIL;
	}
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	Animate
//
HRESULT CGdiWorld::Animate()
{
	HDC hdc = NULL ;
	HRESULT hr = m_pCanvas->GetHDC(&hdc) ;
	ASSERT_HRESULT(hr) ;
	ASSERT(hdc != NULL) ; 

	// Now we know the bounding rectangle of the changed area
	// The bounding rectangle can get big if pieces on the opposite side of the screen change.

	// Clip the area outside the update area. Some objects we will redraw are only partially in the
	// update region. Clip this region so they don't affect the areas outside.
	HRGN rgnClip = CreateRectRgnIndirect(&m_rectUpdate) ;
	::ExtSelectClipRgn(hdc, rgnClip, RGN_COPY) ;
	::DeleteObject(rgnClip) ;

	// Erase the update region.
	RECT rectFill ;
	CopyRect(&rectFill, &m_rectUpdate) ;
	rectFill.right++ ; // FillRect doesn't fill bottom and right edges.
	rectFill.bottom++ ; 
	::FillRect(hdc, &rectFill, (HBRUSH)::GetStockObject(BLACK_BRUSH)) ;

	// Who has been indirectly affected by the changes.
	CVisualList::iterator ppVisual ;
	for(ppVisual = m_VisualList.begin() ; ppVisual != m_VisualList.end() ; ppVisual++)
	{
		ITangramGdiVisual* pVisual = *ppVisual ;
		// See if visual overlaps the update area.
		RECT rectVisual ;
		hr = pVisual->GetBoundingRect(&rectVisual) ; 
		ASSERT_HRESULT(hr) ;

		RECT rectDummy ;
		if (::IntersectRect(&rectDummy, &m_rectUpdate, &rectVisual))
		{
			// Visual is in the update area. 
			hr = pVisual->DrawOn(m_pCanvas) ;
			ASSERT_HRESULT(hr) ;
		}
	}

	// Clipping region is no longer needed.
	::SelectClipRgn(hdc, NULL) ;

	// Move it to the screen.
	hr = m_pCanvas->Update(m_rectUpdate) ;
	ASSERT_HRESULT(hr) ;

	// Cleanup
	::SetRectEmpty(&m_rectUpdate) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//					ITangramGdiWorld
//
///////////////////////////////////////////////////////////
//
//	ModelToDevice 
//
HRESULT CGdiWorld::ModelToDevice(TangramPoint2d ptdIn, POINT* pptOut)
{
	//Precondition
	if (!IsValidAddress(pptOut, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	pptOut->x = static_cast<int>(floor(ptdIn.x * 100000 *  dDeviceUnits / dModelUnits + m_ptdDeviceOrg.x + 0.5)) ;
	pptOut->y = static_cast<int>(floor(ptdIn.y * 100000 * -dDeviceUnits / dModelUnits + m_ptdDeviceOrg.y + 0.5)) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	AddUpdateRect
//
HRESULT CGdiWorld::AddUpdateRect(RECT rectUpdate)
{	
	::UnionRect(&m_rectUpdate, &m_rectUpdate, &rectUpdate) ;

	return S_OK ;
}


