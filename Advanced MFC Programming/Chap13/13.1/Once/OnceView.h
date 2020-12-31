#if !defined(AFX_ONCEVIEW_H__21AF860E_30FF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_ONCEVIEW_H__21AF860E_30FF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class COnceView : public CView
{
protected:
	COnceView();
	DECLARE_DYNCREATE(COnceView)

public:
	COnceDoc* GetDocument();
	//{{AFX_VIRTUAL(COnceView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~COnceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(COnceView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline COnceDoc* COnceView::GetDocument()
   { return (COnceDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ONCEVIEW_H__21AF860E_30FF_11D1_9C9A_444553540000__INCLUDED_)
