// RegExpressionView.h : interface of the CRegExpressionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEXPRESSIONVIEW_H__68584124_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
#define AFX_REGEXPRESSIONVIEW_H__68584124_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRegExpressionView : public CEditView
{
protected: // create from serialization only
	CRegExpressionView();
	DECLARE_DYNCREATE(CRegExpressionView)

// Attributes
public:
	CRegExpressionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegExpressionView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRegExpressionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRegExpressionView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RegExpressionView.cpp
inline CRegExpressionDoc* CRegExpressionView::GetDocument()
   { return (CRegExpressionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEXPRESSIONVIEW_H__68584124_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
