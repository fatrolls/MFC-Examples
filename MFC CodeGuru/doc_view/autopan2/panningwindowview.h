// PanningWindowView.h : interface of the CPanningWindowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANNINGWINDOWVIEW_H__675D4661_02AF_11D2_B5CF_000000000000__INCLUDED_)
#define AFX_PANNINGWINDOWVIEW_H__675D4661_02AF_11D2_B5CF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPanningWindowView : public CScrollView
{
protected: // create from serialization only
	CPanningWindowView();
	DECLARE_DYNCREATE(CPanningWindowView)

// Attributes
public:
	CPanningWindowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanningWindowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPanningWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPanningWindowView)
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	LRESULT OnOriginWindowUpdate(WPARAM , LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PanningWindowView.cpp
inline CPanningWindowDoc* CPanningWindowView::GetDocument()
   { return (CPanningWindowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANNINGWINDOWVIEW_H__675D4661_02AF_11D2_B5CF_000000000000__INCLUDED_)
