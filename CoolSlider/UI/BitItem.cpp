
#include "StdAfx.h"
#include "BitItem.h"

CBitItem::CBitItem(UINT nResID, int cx, int cy, int nMode/* = CBitItem::kBitReadMode*/)
  : m_nMode(nMode),
	m_nItemNums(0),
	m_nItemWidth(cx),
	m_nItemHeight(cy),
	m_nDir(kBitHorizon),
	m_Offset(0, 0)
{
	//
	// 1.0 Check the input value is validate...
	BOOL	bRet = FALSE;
	ASSERT( nResID > 0 );
	//
	// 2.0 Create the Read Memory DC...
	bRet = m_ReadBit.LoadBitmap(nResID);
	ASSERT( bRet );
	BITMAP	bit = {0};
	m_ReadBit.GetBitmap(&bit);
	bRet = m_ReadDC.CreateCompatibleDC(NULL);
	ASSERT( bRet );
	m_ReadDC.SelectObject(&m_ReadBit);
	//
	// 3.0 Create the Write Memory DC by input mode...
	if( m_nMode == kBitWriteMode )
	{
		bRet = m_WriteBit.LoadBitmap(nResID);
		ASSERT( bRet );
		bRet = m_WriteDC.CreateCompatibleDC(NULL);
		ASSERT( bRet );
		m_WriteDC.SelectObject(&m_WriteBit);
	}
	//
	// 4.0 Calculate the Sub-Item Direction, Number, Width, Height...
	memset(&m_Bitmap, 0, sizeof(BITMAP));
	m_ReadBit.GetBitmap(&m_Bitmap);
	ASSERT( m_Bitmap.bmWidth > 0 && m_Bitmap.bmHeight > 0 );

	m_nDir = (m_Bitmap.bmWidth >= m_Bitmap.bmHeight) ? kBitHorizon : kBitVertical;
	m_nItemWidth  = ( m_nItemWidth <= 0 ) ? m_Bitmap.bmWidth : m_nItemWidth;
	m_nItemHeight = ( m_nItemHeight <= 0 ) ? m_Bitmap.bmHeight : m_nItemHeight;
	m_nItemNums   = ( m_nDir == kBitHorizon ) ? m_Bitmap.bmWidth/m_nItemWidth : m_Bitmap.bmHeight/m_nItemHeight;
	
	ASSERT( m_nItemHeight > 0 );
	ASSERT( m_nItemWidth > 0 );
	ASSERT( m_nItemNums > 0 );
}

CBitItem::~CBitItem()
{
	( m_ReadDC.m_hDC != NULL ) ? m_ReadDC.DeleteDC() : NULL;
	( m_WriteDC.m_hDC != NULL ) ? m_WriteDC.DeleteDC() : NULL;
	( m_ReadBit.m_hObject != NULL ) ? m_ReadBit.DeleteObject() : NULL;
	( m_WriteBit.m_hObject != NULL ) ? m_WriteBit.DeleteObject() : NULL;
}
//
// Copy hole DC by input value...
BOOL CBitItem::CopyHoleDC(CDC * lpDesDC, int x, int y, int cx, int cy, 
						  int xSrc/* = 0*/, int ySrc/* = 0*/,
						  BOOL bStretch/* = FALSE*/, BOOL bMiddle/* = FALSE*/)
{
	CDC * lpSrcDC  = (m_nMode == kBitReadMode) ? &m_ReadDC : &m_WriteDC;
	if( lpDesDC == NULL || lpSrcDC == NULL )
		return FALSE;
	ASSERT( m_nItemWidth > 0 );
	ASSERT( m_nItemHeight > 0 );
	
	int nWidth  = (cx == 0) ? m_Bitmap.bmWidth : cx;
	int nHeight = (cy == 0) ? m_Bitmap.bmHeight : cy;

	if( bMiddle )
	{
		x = (nWidth >= m_Bitmap.bmWidth) ? (nWidth - m_Bitmap.bmWidth)/2 : 0;
		y = (nHeight >= m_Bitmap.bmHeight) ? (nHeight - m_Bitmap.bmHeight)/2 : 0;
	}
	if( bStretch )
	{
		lpDesDC->SetStretchBltMode(COLORONCOLOR);
		nWidth  = x > 0 ? m_Bitmap.bmWidth : nWidth;
		nHeight = y > 0 ? m_Bitmap.bmHeight : nHeight;
	}
	return (( bStretch ) ? lpDesDC->StretchBlt(x, y, nWidth, nHeight, lpSrcDC, xSrc, ySrc, m_Bitmap.bmWidth, m_Bitmap.bmHeight, SRCCOPY) : lpDesDC->BitBlt(x, y, nWidth, nHeight, lpSrcDC, xSrc, ySrc, SRCCOPY));
}
//
// Copy hole DC by input RECT object...
BOOL CBitItem::CopyHoleDC(CDC * lpDesDC, LPRECT lpRect, int xSrc/* = 0*/, int ySrc/* = 0*/,
						  BOOL bStretch/* = FALSE*/, BOOL bMiddle/* = FALSE*/)
{
	if( lpRect == NULL )
		return FALSE;
	ASSERT( lpRect != NULL );

	return this->CopyHoleDC(lpDesDC, lpRect->left, lpRect->top,
							lpRect->right - lpRect->left,
							lpRect->bottom - lpRect->top,
							xSrc, ySrc, bStretch, bMiddle);
}
//
// Only for Write-Mode item...
BOOL CBitItem::RecoverDirtyDC()
{
	//
	// 1.0 Check the mode...
	if( m_nMode != kBitWriteMode )
		return FALSE;
	ASSERT( m_nMode == kBitWriteMode );
	//
	// 2.0 Copy hole ReadDC to WriteDC...
	return m_WriteDC.BitBlt(0, 0, m_Bitmap.bmWidth,	m_Bitmap.bmHeight, &m_ReadDC, 0, 0, SRCCOPY);
}
//
// Get Item rectangle by input item index...
BOOL CBitItem::GetRectByIndex(LPRECT lpRect, int nIndex,
							  BOOL bSrc/* = TRUE*/,
							  POINT * lpOff/* = NULL*/)
{
	//
	// 1.0 Check the input value is validate...
	if( lpRect == NULL || nIndex >= m_nItemNums )
		return FALSE;
	ASSERT( lpRect != NULL );
	ASSERT( nIndex >= 0 );
	//
	// 2.0 Calculate the rectangle...
	lpRect->left   = (m_nDir == kBitHorizon) ? nIndex * m_nItemWidth : 0;
	lpRect->top	   = (m_nDir == kBitVertical) ? nIndex * m_nItemHeight : 0;

	lpRect->left  += (bSrc ? 0 : ((lpOff != NULL) ? lpOff->x : m_Offset.x));
	lpRect->top   += (bSrc ? 0 : ((lpOff != NULL) ? lpOff->y : m_Offset.y));
	
	lpRect->right  = lpRect->left + m_nItemWidth;
	lpRect->bottom = lpRect->top + m_nItemHeight;
	return TRUE;
}
//
// Check the input point is in first bititem's rectangle...
BOOL CBitItem::IsInBitItem(CPoint & pt, POINT * lpOff/* = NULL*/)
{
	CRect	rcRect;
	this->GetRectByIndex(rcRect, 0, FALSE, lpOff);
	return rcRect.PtInRect(pt);
}
//
// Write the item information by input index form source BitItem object...
BOOL CBitItem::WriteItemIndex(CBitItem * lpSrcBit, int nSrcIndex)
{
	//
	// 1.0 Check the input vaule is validate...
	if( lpSrcBit == NULL || nSrcIndex < 0 )
		return FALSE;
	ASSERT( m_nMode == kBitWriteMode );
	ASSERT( lpSrcBit->GetBitMode() == kBitReadMode );
	//
	// 2.0 Get the Source Rectangle by input index...
	RECT	rcSrc	= {0, 0, 0, 0};
	RECT	rcDes	= {0, 0, 0, 0};
	CDC	 *	lpSrcDC = lpSrcBit->GetReadDC();
	if( !lpSrcBit->GetRectByIndex(&rcSrc, nSrcIndex) )
		return FALSE;
	ASSERT( lpSrcDC != NULL );
	//
	// 3.0 Get the Destination rectangle by input index...
	rcDes.left   = (m_nDir == kBitHorizon) ? nSrcIndex * lpSrcBit->GetItemWidth() : 0;
	rcDes.top	 = (m_nDir == kBitVertical) ? nSrcIndex * lpSrcBit->GetItemHeight() : 0;
	rcDes.right  = lpSrcBit->GetItemWidth();
	rcDes.bottom = lpSrcBit->GetItemHeight();
	//
	// 4.0 Write the sub-item in current BitItem object...
	return m_WriteDC.BitBlt(rcDes.left, rcDes.top, rcDes.right, rcDes.bottom,
							lpSrcDC, rcSrc.left, rcSrc.top, SRCCOPY);
}

BOOL CBitItem::CopyItemIndex(CDC * lpDesDC, int nIndex,
							 BOOL bSrc/* = TRUE*/,
							 POINT * lpOff /* = NULL*/)
{
	ASSERT( nIndex < m_nItemNums );
	ASSERT( lpDesDC != NULL );
	if( lpDesDC == NULL || nIndex >= m_nItemNums )
		return FALSE;
	RECT rcSrc	= {0, 0, 0, 0};
	if( !this->GetRectByIndex(&rcSrc, nIndex) )
		return FALSE;

	return lpDesDC->BitBlt( (bSrc ? rcSrc.left : 0) + ((lpOff != NULL) ? lpOff->x : m_Offset.x),
							(bSrc ? rcSrc.top : 0) + ((lpOff != NULL) ? lpOff->y : m_Offset.y),
							rcSrc.right - rcSrc.left, rcSrc.bottom - rcSrc.top, 
							&m_ReadDC, rcSrc.left, rcSrc.top, SRCCOPY);
}

void CBitItem::GetRectPos(LPRECT lpRect, POINT * lpOff/* = NULL*/)
{
	ASSERT( lpRect != NULL );
	lpRect->left   = (lpOff != NULL) ? lpOff->x : m_Offset.x;
	lpRect->top	   = (lpOff != NULL) ? lpOff->y : m_Offset.y;
	lpRect->right  = ((lpOff != NULL) ? lpOff->x : m_Offset.x) + m_Bitmap.bmWidth;
	lpRect->bottom = ((lpOff != NULL) ? lpOff->y : m_Offset.y) + m_Bitmap.bmHeight;
}
