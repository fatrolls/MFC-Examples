#if !defined(AFX_HELPVIEW_H__79855C2C_4C51_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_HELPVIEW_H__79855C2C_4C51_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CHelpView : public CView
{
protected:
	CHelpView();
	DECLARE_DYNCREATE(CHelpView)

public:
	CHelpDoc* GetDocument();
	//{{AFX_VIRTUAL(CHelpView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CHelpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CHelpView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CHelpDoc* CHelpView::GetDocument()
   { return (CHelpDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HELPVIEW_H__79855C2C_4C51_11D1_9C9A_444553540000__INCLUDED_)
