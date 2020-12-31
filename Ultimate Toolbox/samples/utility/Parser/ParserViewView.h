// ParserViewView.h : interface of the CParserViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERVIEWVIEW_H__8E0F0930_0728_11D3_A9F8_2EA565000000__INCLUDED_)
#define AFX_PARSERVIEWVIEW_H__8E0F0930_0728_11D3_A9F8_2EA565000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CParserViewView : public CView
{
protected: // create from serialization only
	CParserViewView();
	DECLARE_DYNCREATE(CParserViewView)

// Attributes
public:
	CParserViewDoc* GetDocument();

    CEditView *GetEditView()  { return (CEditView *) m_wndSplitter.GetPane(0,0); }
    CListView *GetListView()  { return (CListView*) m_wndSplitter.GetPane(1,0);  }

    CListCtrl* GetListCtrl()  { return (GetListView())? &(GetListView()->GetListCtrl()) : NULL; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParserViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CParserViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CSplitterWnd m_wndSplitter;

// Generated message map functions
protected:
	//{{AFX_MSG(CParserViewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ParserViewView.cpp
inline CParserViewDoc* CParserViewView::GetDocument()
   { return (CParserViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSERVIEWVIEW_H__8E0F0930_0728_11D3_A9F8_2EA565000000__INCLUDED_)
