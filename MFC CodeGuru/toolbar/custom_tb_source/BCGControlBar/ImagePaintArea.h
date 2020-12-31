#if !defined(AFX_IMAGEPAINTAREA_H__07E27537_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
#define AFX_IMAGEPAINTAREA_H__07E27537_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImagePaintArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImagePaintArea window

class CImagePaintArea : public CButton
{
// Construction
public:
	CImagePaintArea();

// Attributes
public:
	COLORREF	m_rgbColor;
	CRect		m_rectParentPreviewArea;

protected:
	CDC			m_memDC;
	CSize		m_sizeImage;
	CBitmap*	m_pBitmap;

// Operations
public:
	void SetBitmap (CBitmap* pBitmap);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagePaintArea)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImagePaintArea();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImagePaintArea)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	//}}AFX_MSG

	virtual void DrawItem (LPDRAWITEMSTRUCT lpDIS);
	void DrawPixel (POINT point);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPAINTAREA_H__07E27537_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
