// CreditsTestView.h : interface of the CCreditsTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREDITSTESTVIEW_H__E110A1AD_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
#define AFX_CREDITSTESTVIEW_H__E110A1AD_E319_11D1_9E4E_00A0245800CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCreditsTestView : public CView
{
protected: // create from serialization only
	CCreditsTestView();
	DECLARE_DYNCREATE(CCreditsTestView)

// Attributes
public:
	CCreditsTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditsTestView)
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
	virtual ~CCreditsTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCreditsTestView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CreditsTestView.cpp
inline CCreditsTestDoc* CCreditsTestView::GetDocument()
   { return (CCreditsTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITSTESTVIEW_H__E110A1AD_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
