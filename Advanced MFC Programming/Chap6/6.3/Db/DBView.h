#if !defined(AFX_DBVIEW_H__6F1FA2E2_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBVIEW_H__6F1FA2E2_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDBView : public CView
{
protected:
	CDBView();
	DECLARE_DYNCREATE(CDBView)

public:
	CDBDoc* GetDocument();
	//{{AFX_VIRTUAL(CDBView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDBView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CDBDoc* CDBView::GetDocument()
   { return (CDBDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBVIEW_H__6F1FA2E2_130A_11D1_9C9A_444553540000__INCLUDED_)
