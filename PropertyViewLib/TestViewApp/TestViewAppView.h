#ifndef AFX_EVIEWPROP_H__A1DF0EDE_F483_484F_9D94_367E44F60409__INCLUDED_
#define AFX_EVIEWPROP_H__A1DF0EDE_F483_484F_9D94_367E44F60409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CTestViewAppDoc;

#include "EPropView.h"

class CTestViewAppView : public EPropView
{
protected:
	CTestViewAppView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestViewAppView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewAppView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestViewAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CTestViewAppDoc* GetDoc()
	{
		return (CTestViewAppDoc*)GetDocument();
	}

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestViewAppView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVIEWPROP_H__A1DF0EDE_F483_484F_9D94_367E44F60409__INCLUDED_)
