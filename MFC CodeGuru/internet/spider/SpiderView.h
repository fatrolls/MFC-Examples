// SpiderView.h : interface of the CSpiderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPIDERVIEW_H__26AC102E_E049_11D1_8F58_B6D09489096E__INCLUDED_)
#define AFX_SPIDERVIEW_H__26AC102E_E049_11D1_8F58_B6D09489096E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSpiderView : public CEditView
{
protected: // create from serialization only
	CSpiderView();
	DECLARE_DYNCREATE(CSpiderView)

// Attributes
public:
	CSpiderDoc* GetDocument();
	static CSpiderView *GetView();
	BOOL UpdateString (LPCTSTR lpString);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiderView)
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
	virtual ~CSpiderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpiderView)
	afx_msg void OnToolsShowurls();
	afx_msg void OnToolsStripHTML();
	afx_msg void OnToolsStripText();
	afx_msg void OnToolsEmailAddress();
	//}}AFX_MSG
	LRESULT OnUpDateURL(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpiderView.cpp
inline CSpiderDoc* CSpiderView::GetDocument()
   { return (CSpiderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIDERVIEW_H__26AC102E_E049_11D1_8F58_B6D09489096E__INCLUDED_)
