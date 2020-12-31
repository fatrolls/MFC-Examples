// ex10dView.h : interface of the CEx10dView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10DVIEW_H__8F460CF3_6688_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10DVIEW_H__8F460CF3_6688_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx10dView : public CView
{
protected: // create from serialization only
	CEx10dView();
	DECLARE_DYNCREATE(CEx10dView)

// Attributes
public:
	CEx10dDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10dView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10dView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex10dView.cpp
inline CEx10dDoc* CEx10dView::GetDocument()
   { return (CEx10dDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10DVIEW_H__8F460CF3_6688_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
