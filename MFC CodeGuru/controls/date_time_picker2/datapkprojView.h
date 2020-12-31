// datapkprojView.h : interface of the CDatapkprojView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPKPROJVIEW_H__D7484F51_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
#define AFX_DATAPKPROJVIEW_H__D7484F51_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDatapkprojView : public CView
{
protected: // create from serialization only
	CDatapkprojView();
	DECLARE_DYNCREATE(CDatapkprojView)
// Attributes
public:
	CDatapkprojDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatapkprojView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatapkprojView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatapkprojView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in datapkprojView.cpp
inline CDatapkprojDoc* CDatapkprojView::GetDocument()
   { return (CDatapkprojDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPKPROJVIEW_H__D7484F51_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
