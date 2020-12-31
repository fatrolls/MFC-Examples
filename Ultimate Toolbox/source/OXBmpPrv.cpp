// ==========================================================================
// 							Class Implementation : COXBmpFileDialog
// ==========================================================================

// Source file : oxbmpprv.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "OXCommon.h"
#include "oxbmpprv.h"		// class specification
#include "path.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:


IMPLEMENT_DYNAMIC(COXBmpFileDialog, COXPreviewDialog)


COXBmpFileDialog::COXBmpFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
								   DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd)
	: COXPreviewDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
	{
	}

COXBmpFileDialog::~COXBmpFileDialog()
	{
	}

#ifndef WIN32
int COXBmpFileDialog::DoModal()
{
	ASSERT_VALID(this);
	ASSERT(CFileDialog::m_ofn.Flags & OFN_ENABLEHOOK);
	ASSERT(CFileDialog::m_ofn.lpfnHook != NULL); // can still be a user hook

	BOOL bResult;

	CFileDialog::m_ofn.hwndOwner = PreModal();
	if (m_bOpenFileDialog)
		bResult = ::GetOpenFileName(&(CFileDialog::m_ofn));
	else
		bResult = ::GetSaveFileName(&(CFileDialog::m_ofn));
	PostModal();

	return bResult ? IDOK : IDCANCEL;
}
#endif

// protected:

void COXBmpFileDialog::OnNewFileSelect(const CString& sFilename)
	{
	COXPathSpec	pathPreview(sFilename);
	
	if (!sFilename.IsEmpty() &&
		pathPreview.Exists() &&
		pathPreview.GetExtender().CompareNoCase(_T("bmp")) == 0)
		{
		m_dib.Read(pathPreview.GetPath());
		}
	else
		{
		m_dib.Empty();
		}
	}

void COXBmpFileDialog::OnPaintPreview(CDC* pDC, const CRect& paintRect)
{
	if (m_dib.IsEmpty())
	{
		// Paint space of dib with current selected brush 
#ifdef WIN32
		pDC->FillRect(paintRect, pDC->GetCurrentBrush());
#else        
		CBrush* pBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
		pDC->SelectObject(pBrush);   
		pDC->FillRect(paintRect, pBrush);
#endif		
		pDC->MoveTo(paintRect.left, paintRect.top);
		pDC->LineTo(paintRect.right, paintRect.bottom);
		pDC->MoveTo(paintRect.right, paintRect.top);
		pDC->LineTo(paintRect.left, paintRect.bottom);
	}
	else
	{
		CRect dibRect;
		CSize dibSize;
		dibSize = m_dib.GetSize();
		dibRect.SetRect(0,0, dibSize.cx, dibSize.cy);

		CPalette* pPalette = m_dib.GetPalette();
		if (pPalette != NULL)
		{
			CPalette* pOldPalette=pDC->SelectPalette(pPalette, FALSE);
			pDC->RealizePalette();                                    
			pDC->SelectPalette(pOldPalette, FALSE);
		}

		m_dib.Paint(pDC, paintRect, dibRect);
	}
}

void COXBmpFileDialog::OnDoRealizePalette(CWnd* pFocusWnd)
{
	UINT nColorsChanged = 0;

	CPalette* pPalette = m_dib.GetPalette();
	if (pPalette != NULL)
	{
		CClientDC appDC(this);

		// bForceBackground flag is FALSE only if pFocusWnd != this (this dialog)
		CPalette* oldPalette = appDC.SelectPalette(pPalette, pFocusWnd != this);
		if (oldPalette != NULL)
		{
			nColorsChanged = appDC.RealizePalette();
			appDC.SelectPalette(oldPalette, TRUE);
		}
		else
		{
			TRACE(_T("\tSelectPalette failed in COXBmpFileDialog::OnDoRealizePalette\n"));
			return;
		}
	}

	if (nColorsChanged != 0)
	{
		m_preview.Invalidate(FALSE);
	}
}


// private:

