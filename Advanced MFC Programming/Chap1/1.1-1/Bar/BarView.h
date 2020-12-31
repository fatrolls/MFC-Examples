#if !defined(AFX_BARVIEW_H__C0A99CF9_ED67_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_BARVIEW_H__C0A99CF9_ED67_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CBarView : public CView
{
protected:
	CBarView();
	DECLARE_DYNCREATE(CBarView)

public:
	CBarDoc* GetDocument();
	//{{AFX_VIRTUAL(CBarView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CBarView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CBarDoc* CBarView::GetDocument()
   { return (CBarDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BARVIEW_H__C0A99CF9_ED67_11D0_9C9A_444553540000__INCLUDED_)
