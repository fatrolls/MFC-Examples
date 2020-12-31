// MySliderControl.cpp : implementation file
//
//
// Copyright (C) 2002 by Nic Wilson
// All rights reserved
//
// This is free software.
// This code may be used in compiled form in any way you desire. This  
// file may be redistributed unmodified by any means PROVIDING it is   
// not sold for profit without the authors written consent, and   
// providing that this notice and the authors name and all copyright   
// notices remains intact. If the source code in this file is used in   
// any  commercial application then a statement along the lines of   
// "Portions Copyright © 2001-2002 Nic Wilson" must be included in   
// the startup banner, "About" box and printed documentation. An email   
// letting me know that you are using it would be nice.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Version: 1.0 //initial release 2001. 
// Release: 2.0 November 2002  Custom channels, and custom thumbs.
//       
// See Class Members.txt for an explanation of each member function.  

// FEATURES:
//
// Transparent background.
// Custom Transparent Channel
// Custom thumb with optional colours..
// CStatic objects can be auto sized.
// Derived from CSlider

// USAGE:

// Add the MySliderControl.cpp and MySliderControl.h files to your project using 
// "Insert Files into Project" function of Visual C++ or Studio.
// This can be accessed from the workspace by right clicking on the "Source 
// Files" and "Header Files" folders.
//
//
// Add one or more CSlider objects to your application.
//
// Add an  #include "MySliderControl.h" to your applications .h file.
// Add a variable of "Category:  Control",  "Variable Type: CMatrixStatic".
// If CMatrixStatic is does not appear then find your projects .CLW file and
// delete it.  Choose ClassWizard view and when prompted rebuild the CLW file 
// and include the MySliderControl files.  You will also need to select the correct
// dialog class for your dialog.  
// The other option is select the variable as a CSlider control variable then find
// alter its definition from CSliderControl to CMySliderControl.
//
// See the project example for a working demonstration.           
// -----------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MySliderControl.h"
#include "windows.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySliderControl

CMySliderControl::CMySliderControl()
{
	m_dcBk = NULL;
	m_crThumbColor = NULL;
	m_crThumbColorSelected = NULL;
	m_bRedraw = false;
}

CMySliderControl::~CMySliderControl()
{	
	::SelectObject(m_dcBk, m_bmpBkOld);
	::DeleteObject(m_bmpBk);
	::DeleteDC(m_dcBk);			
}


BEGIN_MESSAGE_MAP(CMySliderControl, CSliderCtrl)
	//{{AFX_MSG_MAP(CMySliderControl)
		ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
		ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySliderControl message handlers
//-------------------------------------------------------------------
//
void CMySliderControl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
//
// Description	:	Sent by the slider control to notify the parent window 
//					about drawing operations. This notification is sent in 
//					the form of a WM_NOTIFY message.
// Parameters	:	pNMHDR - a pointer to a NM_CUSTOMDRAW structure.
//					pResult - value depends on the current drawing state.
{
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC *pDC = CDC::FromHandle(lpcd->hdc);
	DWORD dwStyle = this->GetStyle();
	switch(lpcd->dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
		break;
		case CDDS_ITEMPREPAINT:
		{
			switch(lpcd->dwItemSpec)
			{
				case TBCD_TICS:
					*pResult = CDRF_DODEFAULT;
					break;
				case TBCD_THUMB:
					DrawThumb(pDC, lpcd);
					*pResult = CDRF_SKIPDEFAULT;
				break;
				case TBCD_CHANNEL:
					DrawChannel(pDC, lpcd);
					*pResult = CDRF_SKIPDEFAULT;
					break;
			}
			break;
		}
	}
}

void CMySliderControl::DrawChannel(CDC *pDC, LPNMCUSTOMDRAW lpcd)
{
	CClientDC clientDC(GetParent());
	CRect crect;
	CRect wrect;		
	GetClientRect(crect);
	GetWindowRect(wrect);
	GetParent()->ScreenToClient(wrect);
	if (m_dcBk == NULL)
	{
		m_dcBk = CreateCompatibleDC(clientDC.m_hDC);
		m_bmpBk = CreateCompatibleBitmap(clientDC.m_hDC, crect.Width(), crect.Height());
		m_bmpBkOld = (HBITMAP)::SelectObject(m_dcBk, m_bmpBk);
		::BitBlt(m_dcBk, 0, 0, crect.Width(), crect.Height(), clientDC.m_hDC, wrect.left, wrect.top, SRCCOPY);
	}
//	//This bit does the tics marks transparently.
//	//create a memory dc to hold a copy of the oldbitmap data that includes the tics,
//	//because when we add the background in we will lose the tic marks
	HDC hSaveHDC;
	HBITMAP hSaveBmp;
	int iWidth = crect.Width();
	int iHeight = crect.Height();
	hSaveHDC = ::CreateCompatibleDC(pDC->m_hDC);
	hSaveBmp = ::CreateCompatibleBitmap(hSaveHDC, iWidth, iHeight);
	HBITMAP hSaveCBmpOld = (HBITMAP)::SelectObject(hSaveHDC, hSaveBmp);			
	//set the colours for the monochrome mask bitmap
	COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(0,0,0));
	COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(255,255,255));		
	::BitBlt(hSaveHDC, 0, 0, iWidth, iHeight, pDC->m_hDC, crect.left, crect.top, SRCCOPY);
	::BitBlt(pDC->m_hDC, 0, 0, iWidth, iHeight, m_dcBk, 0, 0, SRCCOPY);
	::BitBlt(pDC->m_hDC, 0, 0, iWidth, iHeight, hSaveHDC, 0, 0, SRCAND);
	//restore and clean up
	::SetBkColor(pDC->m_hDC, crOldBack);
	::SetTextColor(pDC->m_hDC, crOldText);
	::SelectObject(hSaveHDC, hSaveCBmpOld);
	::DeleteObject(hSaveBmp);
	::DeleteDC(hSaveHDC);
	crect = lpcd->rc;
	if ((crect.bottom - crect.top) > (crect.right - crect.left))
		crect.InflateRect(1, 0, 1, 0);
	else								//is there a better way to know vert from horiz sliders??
		crect.InflateRect(0, 2, 0, 2);
	DrawEdge(pDC->m_hDC, &crect, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
}

void CMySliderControl::DrawThumb(CDC *pDC, LPNMCUSTOMDRAW lpcd)
{
	CRect crect;
	GetThumbRect(&crect);
	COLORREF col;
	if (lpcd->uItemState & CDIS_SELECTED)
		col = m_crThumbColorSelected;
	else
		col = m_crThumbColor;
	if (col == NULL && lpcd->uItemState & CDIS_SELECTED)
		col = GetSysColor(COLOR_3DHIGHLIGHT);
	else if (col == NULL && !(lpcd->uItemState & CDIS_SELECTED))
		col = GetSysColor(COLOR_3DFACE);
	HBRUSH hbrush = CreateSolidBrush(col);
    HBRUSH hbOld = (HBRUSH)SelectObject(pDC->m_hDC, hbrush);
    Ellipse(pDC->m_hDC, crect.left, crect.top, crect.right, crect.bottom);
    SelectObject(pDC->m_hDC, hbOld);
    DeleteObject(hbrush);
}

BOOL CMySliderControl::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}


void CMySliderControl::SetThumbColors(COLORREF face, COLORREF highlight)
{
	m_crThumbColor = face;
	m_crThumbColorSelected = highlight;
}

void CMySliderControl::DrawTransparent(BOOL bRepaint)
{
	if (m_dcBk != NULL && m_bmpBkOld != NULL)
	{
		::SelectObject(m_dcBk, m_bmpBkOld);
	}
	::DeleteObject(m_bmpBk);
	::DeleteDC(m_dcBk);
	m_dcBk = NULL;
	m_bmpBk = NULL;
	if (bRepaint == TRUE) 
	{
		Invalidate();
		EnableWindow(FALSE);
		EnableWindow(TRUE);
	}
} 

