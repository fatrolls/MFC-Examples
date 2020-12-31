// CustToolBarTestView.h : interface of the CCustToolBarTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTTOOLBARTESTVIEW_H__761D39E6_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_CUSTTOOLBARTESTVIEW_H__761D39E6_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCustToolBarTestView : public CView
{
protected: // create from serialization only
	CCustToolBarTestView();
	DECLARE_DYNCREATE(CCustToolBarTestView)

// Attributes
public:
	CCustToolBarTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustToolBarTestView)
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
	virtual ~CCustToolBarTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustToolBarTestView)
	afx_msg void OnUserTool1();
	afx_msg void OnUserTool2();
	afx_msg void OnUserTool3();
	afx_msg void OnUpdateUserTool3(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CustToolBarTestView.cpp
inline CCustToolBarTestDoc* CCustToolBarTestView::GetDocument()
   { return (CCustToolBarTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTTOOLBARTESTVIEW_H__761D39E6_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
