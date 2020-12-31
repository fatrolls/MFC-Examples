// ex03aView.h : interface of the CEx03aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX03AVIEW_H__86D4CCC1_5F86_11D0_8FD2_00C04FC2A0C2__INCLUDED_)
#define AFX_EX03AVIEW_H__86D4CCC1_5F86_11D0_8FD2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx03aView : public CView
{
protected: // create from serialization only
	CEx03aView();
	DECLARE_DYNCREATE(CEx03aView)

// Attributes
public:
	CEx03aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx03aView)
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
	virtual ~CEx03aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx03aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex03aView.cpp
inline CEx03aDoc* CEx03aView::GetDocument()
   { return (CEx03aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX03AVIEW_H__86D4CCC1_5F86_11D0_8FD2_00C04FC2A0C2__INCLUDED_)
