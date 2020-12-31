// HexView.h : interface of the CHexView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXVIEW_H__3A83FE00_A3E6_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_HEXVIEW_H__3A83FE00_A3E6_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHexView : public CScrollView
{
protected: // create from serialization only
	CHexView();
	DECLARE_DYNCREATE(CHexView)

// Attributes
public:
	CHexDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void FormatLine(CHexDoc* pDoc, UINT nLine, CString& string);
	void PrintPageHeader(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber);
	void PrintPage(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber);
	UINT m_cxWidth;
	UINT m_cxOffset;
	UINT m_nLinesPerPage;
	UINT m_nLinesTotal;
	UINT m_cyPrinter;
	UINT m_cyScreen;
	CFont m_fontPrinter;
	CFont m_fontScreen;
	//{{AFX_MSG(CHexView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HexView.cpp
inline CHexDoc* CHexView::GetDocument()
   { return (CHexDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXVIEW_H__3A83FE00_A3E6_11D2_8E53_006008A82731__INCLUDED_)
