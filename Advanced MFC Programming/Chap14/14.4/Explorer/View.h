#if !defined(AFX_VIEW_H__D1AB534C_4563_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_VIEW_H__D1AB534C_4563_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include <afxcview.h>

class CExplorerView : public CListView
{
protected:
	CExplorerView();
	DECLARE_DYNCREATE(CExplorerView)

public:
	CExplorerDoc* GetDocument();
	//{{AFX_VIRTUAL(CExplorerView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CExplorerView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CExplorerDoc* CExplorerView::GetDocument()
   { return (CExplorerDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_VIEW_H__D1AB534C_4563_11D1_9C9A_444553540000__INCLUDED_)
