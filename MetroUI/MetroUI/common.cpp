#include "common.h"



void ClientToScreen( HWND hWnd,RECT * lpRect )
{
	POINT pt = { lpRect->left,lpRect->top };
	ClientToScreen( hWnd,&pt );
	lpRect->left = pt.x;
	lpRect->top = pt.y;
	pt.x = lpRect->right;
	pt.y = lpRect->bottom;
	ClientToScreen( hWnd,&pt );
	lpRect->right = pt.x;
	lpRect->bottom = pt.y;
}

void ScreenToClient( HWND hWnd,RECT * lpRect )
{
	POINT pt = { lpRect->left,lpRect->top };
	ScreenToClient( hWnd,&pt );
	lpRect->left = pt.x;
	lpRect->top = pt.y;
	pt.x = lpRect->right;
	pt.y = lpRect->bottom;
	ScreenToClient( hWnd,&pt );
	lpRect->right = pt.x;
	lpRect->bottom = pt.y;
}

HRGN CreateStretchRgn( HRGN hSrcRgn, 
                       float xScale , 
                       float yScale , 
                       int xOffset , 
                       int yOffset )
{
	XFORM xForm;
	xForm.eDx = 0;
	xForm.eDy = 0;
	xForm.eM11 = xScale;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = yScale;
	HRGN hRgn = NULL ;
	
	DWORD dwCount = GetRegionData( hSrcRgn , 0 , NULL );
	BYTE* pRgnData =(BYTE*) malloc( dwCount );
	if( pRgnData )
	{
		dwCount = GetRegionData( hSrcRgn , dwCount , (RGNDATA*)pRgnData );
		hRgn = ExtCreateRegion( &xForm , dwCount , (RGNDATA*)pRgnData );
		free( pRgnData );

		if( hRgn )
		{
			OffsetRgn( hRgn , xOffset, yOffset );
			return hRgn;
		}
	}
	return NULL;
}

void GradientFillRect( HDC hDC, RECT & rect, COLORREF col_from, COLORREF col_to, bool vert_grad )
{
	TRIVERTEX        vert[2];
	GRADIENT_RECT    mesh;
	
	vert[0].x      = rect.left;
	vert[0].y      = rect.top;
	vert[0].Alpha  = 0x0000;
	vert[0].Blue   = GetBValue(col_from) << 8;
	vert[0].Green  = GetGValue(col_from) << 8;
	vert[0].Red    = GetRValue(col_from) << 8;
	
	vert[1].x      = rect.right;
	vert[1].y      = rect.bottom; 
	vert[1].Alpha  = 0x0000;
	vert[1].Blue   = GetBValue(col_to) << 8;
	vert[1].Green  = GetGValue(col_to) << 8;
	vert[1].Red    = GetRValue(col_to) << 8;
	
	mesh.UpperLeft  = 0;
	mesh.LowerRight = 1;

	GradientFill( hDC, vert, 2, &mesh, 1, vert_grad ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H );
}

BOOL ImageFromIDResource( unsigned char * lpResStreamName,unsigned int len,Gdiplus::Image * &pImg )
{
	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpResStreamName,len);
	IStream* pstm;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
	// load from stream
	pImg=Gdiplus::Image::FromStream(pstm);
	// free/release stuff
	pstm->Release();
	GlobalUnlock(m_hMem);
	return TRUE;
}
