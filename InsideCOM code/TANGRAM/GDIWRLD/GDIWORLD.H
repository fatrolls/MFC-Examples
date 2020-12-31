#ifndef __CGdiWorld_h__
#define __CGdiWorld_h__
///////////////////////////////////////////////////////////
//
//
//	GdiWorld.h - Header file for the Gdi version of the World Component
//
//

#include "CUnknown.h"

#include "World_I.h"
#include "TanType.h"

///////////////////////////////////////////////////////////
//
//	CGdiWorld
//
class CGdiWorld :	public CUnknown,
					public ITangramGdiWorld
{
public:	
	// Creation
	static HRESULT CreateInstance(	IUnknown* pOuterUnknown,
									CUnknown** ppNewComponent ) ;

	// Special Registration
	static void SpecialReg(BOOL bRegister) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;			

	// ITangramWorld Members
	virtual HRESULT __stdcall Initialize(HWND hwnd, double logicalCX, double logicalCY) ;
	virtual HRESULT __stdcall DeviceToModel(POINT ptIN, TangramPoint2d* pptOut) ;

	virtual HRESULT __stdcall VisualFromPoint(	POINT pt, 							
												REFIID iid, 
												IUnknown** ppITangramVisual) ;
	virtual HRESULT __stdcall CreateVisualForModel(ITangramModel* pModel) ;
	virtual HRESULT __stdcall SelectVisual(ITangramVisual* pSelectedVisual, BOOL bSelect) ;

	virtual HRESULT __stdcall Animate() ; 

	// ITangramGdiWorld
	virtual HRESULT __stdcall ModelToDevice(TangramPoint2d ptIn, POINT* pptOut);
	virtual HRESULT __stdcall AddUpdateRect(RECT rectUpdate) ;

	// Creation and Destruction
	CGdiWorld(IUnknown* pOuterUnknown) ;
	virtual ~CGdiWorld() ;

	// Notify derived classes that we are releasing.
	virtual void FinalRelease() ;

private:
	// Members
	typedef std::list<ITangramGdiVisual*> CVisualList;
	CVisualList m_VisualList ;

	// Coordinate Transform
	TangramSize2d m_sizedScale ;
	TangramPoint2d m_ptdDeviceOrg ;

	double dDeviceUnits ;
	double dModelUnits ;

	// Aggregated Canvas Component
	ITangramCanvas* m_pCanvas ;
	IUnknown* m_pCanvasUnknown ;

	// Update rectangle
	RECT m_rectUpdate ;
};
#endif

