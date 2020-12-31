#ifndef __CTangramGLVisual_H__
#define __CTangramGLVisual_H__
///////////////////////////////////////////////////////////
//
//
// GLVisl.h	-	Header file for CTangramGLVisual
//
//
///////////////////////////////////////////////////////////
//
//
#include "CUnknown.h"

#include "Visual_I.h" 
#include "GLVisl_I.h" // ITangramGLVisual
#include "Event_I.h"

interface IConnectionPoint ;

///////////////////////////////////////////////////////////
//
// CTangramGLVisual
//
class CTangramGLVisual :	public CUnknown, 
							public ITangramGLVisual,
							public ITangramModelEvent
{
public:
 	// Creation
	static HRESULT CreateInstance(IUnknown* pOuterUnknown,
											CUnknown** ppNewComponent ) ;

public:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;

	// ITangramVisual
	virtual HRESULT __stdcall GetModel(	const IID& iid, IUnknown** ppI) ;
	virtual HRESULT __stdcall SetSelected(BOOL bSelected) ;

	// ITangramModelEvent
	virtual HRESULT __stdcall OnModelChange() ;

	// ITangramGLVisual
	virtual HRESULT __stdcall Initialize(	ITangramModel* pModel, 
											ITangramGLWorld* pWorld) ;  	
	virtual HRESULT __stdcall DrawOn(ITangramCanvas* pCanvas) ;    

	// Creation and Destruction
	CTangramGLVisual(IUnknown* pOuterUnknown) ;
	virtual ~CTangramGLVisual() ;

// Members
private:
	// Event Sink support.
	IConnectionPoint* m_pIConnectionPoint ;
	DWORD m_dwCookie ;

	// Backpointer to parent World component.
	ITangramGLWorld* m_pWorld;

	// Pointer to associated model.
	ITangramModel* m_pModel ;

	// Array of vertices.
	TangramPoint2d* m_ptVertices ;
	long m_cVertices ;

	// Selection status.
	BOOL m_bSelected ;

	// Set to TRUE when the visual has been notified by the model.
	BOOL m_bFirstEvent;
};
#endif