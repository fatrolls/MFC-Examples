// MemDC.cpp: implementation of the CMemDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemDC.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemDC::CMemDC()
{

}

CMemDC::CMemDC(HDC hdc,RECT rc)
{
	m_hDCold = hdc;
	m_hDCMem = CreateCompatibleDC(hdc);

//	GetClipBox(hdc,&m_rect);
	m_rect = rc;
	//
	// Create a bitmap big enough for our client rect
	//

	m_hBMMem = CreateCompatibleBitmap(hdc,
									m_rect.right-m_rect.left,
									m_rect.bottom-m_rect.top);

	//
	// Select the bitmap into the off-screen dc
	//

	m_hBMOld = (HBITMAP) SelectObject(m_hDCMem, m_hBMMem);
	SIZE sz;
    SetWindowExtEx(m_hDCMem,m_rect.left, m_rect.top,&sz);

}

CMemDC::~CMemDC()
{
	BitBlt(m_hDCold, 
		   m_rect.left, m_rect.top,
		   m_rect.right-m_rect.left,
		   m_rect.bottom-m_rect.top,
		   m_hDCMem,
		   0, 0,
		   SRCCOPY);

	//
	// Done with off screen bitmap and dc
	//

	SelectObject(m_hDCMem, m_hBMOld);
	DeleteObject(m_hBMMem);
	DeleteDC(m_hDCMem);

}
