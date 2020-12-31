//
// CListBoxEx.cpp	v1.0
//

#include "stdafx.h"
#include "listboxex.h"


//
// see Q66370 for more information
//

//////////////////////////////////////////////////////////////////////////////////
//
//override functions
//////////////////////////////////////////////////////////////////////////////////

int CListBoxEx::AddString(LPCTSTR lpszItem)
{

	LONG lStringExtent = GetExtentForString(lpszItem);
	if(GetHorizontalExtent() < lStringExtent)
		SetHorizontalExtent(lStringExtent);
		
	return CListBox::AddString(lpszItem);
}

int CListBoxEx::DeleteString( UINT nIndex )
{
	int nCountLeft = CListBox::DeleteString(nIndex);
	if(nCountLeft == LB_ERR)
		return LB_ERR;

	LONG lMaxExtent = GetExtentForEntireControl();
	SetHorizontalExtent(lMaxExtent);

	return nCountLeft;
}

int CListBoxEx::InsertString( int nIndex, LPCTSTR lpszItem )
{
	int nInsertPos = InsertString(nIndex, lpszItem);
	if(nInsertPos == LB_ERR)
		return LB_ERR;

	LONG lStringExtent = GetExtentForString(lpszItem);
	if(GetHorizontalExtent() < lStringExtent)
		SetHorizontalExtent(lStringExtent);

	return nInsertPos;
}

void CListBoxEx::ResetContent()
{
	SetHorizontalExtent(0);

	CListBox::ResetContent();

	return;
}

int CListBoxEx::Dir( UINT attr, LPCTSTR lpszWildCard )
{
	int nReturn = Dir( attr, lpszWildCard );

	if(nReturn == LB_ERR || nReturn == LB_ERRSPACE)
		return nReturn;

	LONG lMaxExtent = GetExtentForEntireControl();
	SetHorizontalExtent(lMaxExtent);

	return nReturn;
}


//////////////////////////////////////////////////////////////////////////////////
//
//helper functions
//////////////////////////////////////////////////////////////////////////////////

LONG CListBoxEx::GetExtentForString(LPCTSTR lpszItem)
{
	CDC* cdc = this->GetDC();
	CFont* font = this->GetFont();
	CFont* pOldFont;
	
    if (font)
	{
        pOldFont = cdc->SelectObject(font);

		TEXTMETRIC tm;
		cdc->GetTextMetrics(&tm);

		CSize size = cdc->GetTextExtent(lpszItem, lstrlen(lpszItem) );
		size.cx += tm.tmAveCharWidth;
    
		cdc->SelectObject(pOldFont);
		this->ReleaseDC(cdc);

		return (LONG) size.cx;
	}

	this->ReleaseDC(cdc);

	return 0L;
}

LONG CListBoxEx::GetExtentForEntireControl()
{
	CDC* cdc = this->GetDC();
	CFont* font = this->GetFont();
	CFont* pOldFont;
	
    if (font)
	{
        pOldFont = cdc->SelectObject(font);

		TEXTMETRIC tm;
		cdc->GetTextMetrics(&tm);
		CString sText;
		LONG max_cx = 0;

		for(int n = 0; n<=GetCount(); n++)
		{
			this->GetText(n, sText);
			if(sText == "")
				continue;

			CSize size = cdc->GetTextExtent(sText, sText.GetLength() );
			size.cx += tm.tmAveCharWidth;

			if(max_cx <= size.cx)
				max_cx = size.cx;
		}
    
		cdc->SelectObject(pOldFont);
		this->ReleaseDC(cdc);

		return max_cx;
	}

	this->ReleaseDC(cdc);

	return 0L;
}