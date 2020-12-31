// ex26cView.h : interface of the CEx26cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26CVIEW_H__4EBFDD7D_5F7D_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26CVIEW_H__4EBFDD7D_5F7D_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx26cView : public CView
{
protected: // create from serialization only
	CEx26cView();
	DECLARE_DYNCREATE(CEx26cView)

// Attributes
public:
	CEx26cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26cView)
	afx_msg void OnStorageRead();
	afx_msg void OnStorageWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex26cView.cpp
inline CEx26cDoc* CEx26cView::GetDocument()
   { return (CEx26cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26CVIEW_H__4EBFDD7D_5F7D_11D0_848F_00400526305B__INCLUDED_)
