// ex31cView.h : interface of the CEx31cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX31CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
#define AFX_EX31CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx31cCntrItem;

class CEx31cView : public CRichEditView
{
protected: // create from serialization only
	CEx31cView();
	DECLARE_DYNCREATE(CEx31cView)

// Attributes
public:
	CEx31cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx31cView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx31cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx31cView)

		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex31cView.cpp
inline CEx31cDoc* CEx31cView::GetDocument()
   { return (CEx31cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
