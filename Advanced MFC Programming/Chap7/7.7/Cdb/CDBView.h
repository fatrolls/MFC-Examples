#if !defined(AFX_CDBVIEW_H__2D7EBBEC_0A8A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CDBVIEW_H__2D7EBBEC_0A8A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CCDBView : public CView
{
protected:
	CCDBView();
	DECLARE_DYNCREATE(CCDBView)

public:
	CCDBDoc* GetDocument();
	//{{AFX_VIRTUAL(CCDBView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CCDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CCDBView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CCDBDoc* CCDBView::GetDocument()
   { return (CCDBDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CDBVIEW_H__2D7EBBEC_0A8A_11D1_9C9A_444553540000__INCLUDED_)
