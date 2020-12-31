#ifndef __CTangramGDIVisual_H__
#define __CTangramGDIVisual_H__
///////////////////////////////////////////////////////////
//
//
//	GdiVisl.h - Header file for CTangramGDIVisual
//
//

// Base class
#include "CUnknown.h"

// Interfaces
#include "Visual_I.h" 
#include "Event_I.h" 

// Forwards
interface IConnectionPoint ;

///////////////////////////////////////////////////////////
//
//	CTangramGdiVisual
//
class CTangramGdiVisual :	public CUnknown, 
									public ITangramGdiVisual,
									public ITangramModelEvent
{
public:	
	// Creation
	static HRESULT CreateInstance(IUnknown* pOuterUnknown,
											CUnknown** ppNewComponent ) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;

	// ITangramVisual
	virtual HRESULT __stdcall GetModel(	const IID& iid, IUnknown** ppI) ;
	virtual HRESULT __stdcall SetSelected(BOOL bSelected) ;

	// ITangramGdiVisual
	virtual HRESULT __stdcall Initialize(ITangramModel* pModel, ITangramGdiWorld* pWorld) ;
	virtual HRESULT __stdcall IsPtIn(POINT pt) ;
	virtual HRESULT __stdcall GetBoundingRect(RECT* pBoundingRect) ;
	virtual HRESULT __stdcall DrawOn(ITangramCanvas* pCanvas) ;    
	
	// ITangramModelEvent
	virtual HRESULT __stdcall OnModelChange() ;

	// Helper function
	void SyncToModel() ;

	// Creation and Destruction
	CTangramGdiVisual(IUnknown* pOuterUnknown) ;
	virtual ~CTangramGdiVisual() ;

// Member Variables
private:
	// Event Sink support.
	IConnectionPoint* m_pIConnectionPoint ;
	DWORD m_dwCookie ;

	// Backpointer to parent World component.
	ITangramGdiWorld* m_pGdiWorld ;

	// Pointer to associated model.
	ITangramModel* m_pModel ;

	// Array of vertices.
	POINT* m_ptVertices ;
	long m_cVertices ;

	// Selection status.
	BOOL m_bSelected ;
};

#endif

