// BCGToolbarMenuButton.h: interface for the CBCGToolbarMenuButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARMENUBUTTON_H__B715CF84_CA00_11D1_A647_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARMENUBUTTON_H__B715CF84_CA00_11D1_A647_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGToolbarButton.h"

class AFX_EXT_CLASS CBCGToolbarMenuButton : public CBCGToolbarButton  
{
	DECLARE_SERIAL(CBCGToolbarMenuButton)

public:
	CBCGToolbarMenuButton();
	CBCGToolbarMenuButton (UINT uiID, UINT uiMenuResID, int iImage, LPCTSTR lpszText = NULL,
								BOOL bUserButton = FALSE);
	virtual ~CBCGToolbarMenuButton();

// Overrides:
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual void Serialize (CArchive& ar);
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE);
	virtual int  OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd);

// Attributes:
public:
	UINT				m_uiMenuResId;

protected:
	static CImageList	m_Images;
	static CSize		m_sizeImageArrow;
};

#endif // !defined(AFX_BCGTOOLBARMENUBUTTON_H__B715CF84_CA00_11D1_A647_00A0C93A70EC__INCLUDED_)
