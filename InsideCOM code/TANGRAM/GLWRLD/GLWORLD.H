#ifndef __CGLWorld_h__
#define __CGLWorld_h__
///////////////////////////////////////////////////////////
//
//
//	GLWorld.h - Header file for the OpenGL version of the World Component
//
//
#include "CUnknown.h"

#include "World_I.h"
#include "GLWrld_I.h" // ITangramGLWorld
#include "TanType.h"

///////////////////////////////////////////////////////////
//
//	Structures
//
typedef struct tagTangramPoint3d
{
	double x ;
	double y ;
	double z ;
} TangramPoint3d ;

///////////////////////////////////////////////////////////
//
//	CGLWorld
//
class CGLWorld :	public CUnknown,
					public ITangramGLWorld
{
public:	
	// Creation
	static HRESULT CreateInstance(IUnknown* pOuterUnknown,
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

	// ITangramGLWorld
	virtual HRESULT __stdcall ModelToDevice(TangramPoint2d ptIn, TangramPoint2d* pptOut);

	// Creation and Destruction
	CGLWorld(IUnknown* pOuterUnknown) ;
	virtual ~CGLWorld() ;

	// Notify derived classes that we are releasing.
	virtual void FinalRelease() ;

public:
	// OpenGL Support Functions
	BOOL GLResize(int cx, int cy) ;
	BOOL GLSetup() ;
	BOOL GLRender() ;

private:
	// Member Variables
	typedef std::list<ITangramGLVisual*> CVisualList;
	CVisualList m_VisualList ;

	// World Members
	HDC m_hdc ;

	// Aggregated Canvas Component
	ITangramCanvas* m_pCanvas ;
	IUnknown* m_pCanvasUnknown ;

	// Handle to the main window.
	HWND m_hMainWnd ;

	// OpenGL Support Code
	CGL* m_pGL ;

	// OpenGL Picking Support
	BOOL m_bPicking ;
	int Pick(POINT pt) ;

	// Coordinates of lowerleft and upper right of the window.
	TangramPoint3d m_ptLowerLeft ;
	TangramPoint3d m_ptUpperRight ;
};
#endif

