// SpiderList.h : interface of the CSpiderList class
//
/////////////////////////////////////////////////////////////////////////////
#include <afxcview.h>

#if !defined SpiderList_H
#define SpiderList_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSpiderList : public CListView
{
protected: // create from serialization only
	CSpiderList();
	DECLARE_DYNCREATE(CSpiderList)

// Attributes
public:
	CSpiderDoc* GetDocument();
	static CSpiderList *GetView();

// Operations
public:
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiderList)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpiderList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpiderList)
	//}}AFX_MSG
	LRESULT OnUpDateURL(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpiderList.cpp
inline CSpiderDoc* CSpiderList::GetDocument()
   { return (CSpiderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 

