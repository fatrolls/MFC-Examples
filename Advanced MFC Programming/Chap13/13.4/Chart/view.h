#if !defined(AFX_VIEW_H__093F7924_3414_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_VIEW_H__093F7924_3414_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CChartView : public CView
{
protected:
	CChartView();
	DECLARE_DYNCREATE(CChartView)

public:
	CChartDoc* GetDocument();
	//{{AFX_VIRTUAL(CChartView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CChartView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CChartDoc* CChartView::GetDocument()
   { return (CChartDoc*)m_pDocument; }
#endif

class CPieView : public CView
{
protected:
	CPieView();
	DECLARE_DYNCREATE(CPieView)

public:
	CPoint CPieView::GetPoint(CRect, int);
	//{{AFX_VIRTUAL(CPieView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

protected:
	virtual ~CPieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CPieView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_VIEW_H__093F7924_3414_11D1_9C9A_444553540000__INCLUDED_)
