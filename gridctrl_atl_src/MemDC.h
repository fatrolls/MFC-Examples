// MemDC.h: interface for the CMemDC class.
//
//////////////////////////////////////////////////////////////////////
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#if !defined(AFX_MEMDC_H__7B529FB3_CAC0_11D3_994E_006097FEBF00__INCLUDED_)
#define AFX_MEMDC_H__7B529FB3_CAC0_11D3_994E_006097FEBF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemDC 
{
public:
	CMemDC();

	CMemDC(HDC hdc,RECT rc)
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

	virtual ~CMemDC()
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

    HDC GetDC() {return m_hDCMem;}
private:
	HDC m_hDCold,m_hDCMem;
	HBITMAP m_hBMMem, m_hBMOld;
	RECT m_rect;
};

#endif // !defined(AFX_MEMDC_H__7B529FB3_CAC0_11D3_994E_006097FEBF00__INCLUDED_)
