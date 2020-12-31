// ex10cView.h : interface of the CEx10cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10CVIEW_H__1A050A1F_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10CVIEW_H__1A050A1F_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#include "CDIB.H"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx10cView : public CScrollView
{
protected: // create from serialization only
	CEx10cView();
	DECLARE_DYNCREATE(CEx10cView)

// Attributes
public:
	CEx10cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10cView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDib m_dibFile;
	CDib m_dibResource;
};

#ifndef _DEBUG  // debug version in ex10cView.cpp
inline CEx10cDoc* CEx10cView::GetDocument()
   { return (CEx10cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10CVIEW_H__1A050A1F_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
