#ifndef __CCanvas_h__
#define __CCanvas_h__

///////////////////////////////////////////////////////////
//
//
//	Canvas.h - Header file for canvas component implementation.
//
//
//
#include "CUnknown.h"
#include "Canvas_I.h"

///////////////////////////////////////////////////////////
//
//	CCanvas
//
class CCanvas :	public CUnknown,
						public ITangramCanvas 
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

	// ICanvas
	virtual HRESULT __stdcall Initialize(HWND hWnd, long cx, long cy) ;//Initialize can be called multiple times.
	virtual HRESULT __stdcall Paint(HDC hdcDest, RECT rectUpdate) ;
	virtual HRESULT __stdcall Update(RECT rectUpdate);
	virtual HRESULT __stdcall GetHDC(HDC* phdc ) ; 
	virtual HRESULT __stdcall SetPalette(HPALETTE hPal); 
	virtual HRESULT __stdcall OnQueryNewPalette(HWND hWndReceived) ;

	// Construction and Destruction.
	CCanvas(IUnknown* pOuterUnknown) ;
	~CCanvas() ;

//Helper Functions   
private:
	// Cleanup state for a new initialization.
	void destroy() ; 	

//Member Variables
private:
	// Handle to window associated with this Canvas.
	HWND m_hWnd ; 

	// Handle to dib section.
	HBITMAP m_hbmp ;

	// Handle to old bitmap.
	HBITMAP m_hbmOld ;

	// Pointer to the bits.
	void* m_pBits ;		

	// Size of the canvas.
	SIZE m_sizeDIB ;

	// Handle to the device memory context for the dib section.
	HDC m_hdc ;

	// Handle to the palette used by the dib section.
	HPALETTE m_hPal;
};
#endif // __CCanvas_h__
