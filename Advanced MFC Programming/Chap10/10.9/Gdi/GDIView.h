#if !defined(AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIView : public CScrollView
{
protected:
	BOOL m_bBitmapLoaded;
	CBitmap m_bmpBkd;
	CBitmap m_bmpDraw;
	CBitmap m_bmpMask;
	CBitmap m_bmpBS;
	CBitmap *m_pBmpOld;
	CBitmap *m_pBmpMaskOld;
	CBitmap *m_pBmpBSOld;
	CDC m_dcMem;
	CDC m_dcMemMask;
	CDC m_dcMemBS;
	CPalette *m_pPalOld;
	CPalette *m_pPalMaskOld;
	CPalette *m_pPalBSOld;
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

public:
	CGDIDoc* GetDocument();
	void LoadBitmap(HGLOBAL);
	void CleanUp();
	//{{AFX_VIRTUAL(CGDIView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGDIView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CGDIDoc* CGDIView::GetDocument()
   { return (CGDIDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIVIEW_H__A9BED22C_2386_11D1_9C9A_444553540000__INCLUDED_)
