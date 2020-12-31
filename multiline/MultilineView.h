// MultilineView.h : interface of the CMultilineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILINEVIEW_H__3050964E_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_MULTILINEVIEW_H__3050964E_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListCtrlEx.h"

class CMultilineView : public CFormView
{
protected: // create from serialization only
	CMultilineView();
	DECLARE_DYNCREATE(CMultilineView)

public:
	CListCtrlEx			m_ListCtrl ;


public:
	//{{AFX_DATA(CMultilineView)
	enum { IDD = IDD_MULTILINE_FORM };
	//}}AFX_DATA

// Attributes
public:
	CMultilineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultilineView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultilineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultilineView)
	afx_msg void OnPopulate();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MultilineView.cpp
inline CMultilineDoc* CMultilineView::GetDocument()
   { return (CMultilineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILINEVIEW_H__3050964E_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
