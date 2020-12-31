#if !defined(AFX_GDIVIEW_H__1DC82DEC_1E20_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIVIEW_H__1DC82DEC_1E20_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIView : public CView
{
protected:
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

public:
	CGDIDoc* GetDocument();
	//{{AFX_VIRTUAL(CGDIView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CGDIDoc* CGDIView::GetDocument()
   { return (CGDIDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIVIEW_H__1DC82DEC_1E20_11D1_9C9A_444553540000__INCLUDED_)
