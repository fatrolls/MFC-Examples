#if !defined(AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc;

class CGDIView : public CScrollView
{
protected:
	CBrush m_brGrid;
	CBitmap m_bmpDraw;
	CBitmap *m_pBmpOld;
	CDC m_dcMem;
	CPalette *m_pPalOld;
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

public:
	CGDIDoc* GetDocument();
	void LoadBitmap(HGLOBAL);
	void CleanUp();
	void UpdateScrollSizes();

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
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CGDIDoc* CGDIView::GetDocument()
   { return (CGDIDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_)
