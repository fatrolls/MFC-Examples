// ex08bView.h : interface of the CEx08bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX08BVIEW_H__13D86A41_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08BVIEW_H__13D86A41_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_

#include "webbrowser.h"	// Added by ClassView
class CEx08bView : public CView
{
private:
	static const char s_engineAltavista[];

protected: // create from serialization only
	CEx08bView();
	DECLARE_DYNCREATE(CEx08bView)

// Attributes
public:
	CEx08bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08bView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnBeforeNavigateExplorer1(LPCTSTR URL,
		long Flags, LPCTSTR TargetFrameName,
		VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel);
	afx_msg void OnTitleChangeExplorer2(LPCTSTR Text);
	DECLARE_EVENTSINK_MAP()

private:
	CWebBrowser m_target;
	CWebBrowser m_search;
};

#ifndef _DEBUG  // debug version in ex08bView.cpp
inline CEx08bDoc* CEx08bView::GetDocument()
   { return (CEx08bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08BVIEW_H__13D86A41_5BC8_11D0_8FD1_00C04FC2A0C2__INCLUDED_)
