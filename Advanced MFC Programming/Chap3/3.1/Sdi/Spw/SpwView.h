#if !defined(AFX_SPWVIEW_H__D3F202AD_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWVIEW_H__D3F202AD_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CSpwView : public CView
{
protected:
	CSpwView();
	DECLARE_DYNCREATE(CSpwView)

public:
	CSpwDoc* GetDocument();
	//{{AFX_VIRTUAL(CSpwView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CSpwView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CSpwView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CSpwDoc* CSpwView::GetDocument()
   { return (CSpwDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SPWVIEW_H__D3F202AD_FC3A_11D0_9C9A_444553540000__INCLUDED_)
