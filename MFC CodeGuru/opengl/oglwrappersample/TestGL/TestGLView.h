// TestGLView.h : interface of the CTestGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTestGLView : public CGLEnabledView
{
protected: // create from serialization only
	CTestGLView();
	DECLARE_DYNCREATE(CTestGLView)

// Attributes
public:
	CTestGLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGLView)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnCreateGL();
	void OnDrawGL();
	virtual ~CTestGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestGLView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHelpOglinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;
};

#ifndef _DEBUG  // debug version in TestGLView.cpp
inline CTestGLDoc* CTestGLView::GetDocument()
   { return (CTestGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
