// GDIView.h : interface of the CGDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGDIView : public CScrollView
{
protected:
	BOOL m_bBitmapLoaded;
	CBitmap m_bmpDraw;
	CBitmap *m_pBmpOld;
	CDC m_dcMem;
	CPalette *m_pPalOld;
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

// Attributes
public:
	CGDIDoc* GetDocument();
	void LoadBitmap(HGLOBAL);
	void CleanUp();
	HBITMAP CreateGrayedBitmap(CBitmap *);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGDIView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDIView.cpp
inline CGDIDoc* CGDIView::GetDocument()
   { return (CGDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_)
