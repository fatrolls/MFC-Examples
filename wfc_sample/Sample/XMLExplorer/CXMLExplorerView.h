// CXMLExplorerView.h : interface of the CXMLExplorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CXMLEXPLORERVIEW_H__41D52536_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
#define AFX_CXMLEXPLORERVIEW_H__41D52536_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXMLExplorerView : public CView
{
protected: // create from serialization only
	CXMLExplorerView();
	DECLARE_DYNCREATE(CXMLExplorerView)

// Attributes
public:
	CXMLExplorerDocument* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLExplorerView)
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
	virtual ~CXMLExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXMLExplorerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CXMLExplorerView.cpp
inline CXMLExplorerDocument* CXMLExplorerView::GetDocument()
   { return (CXMLExplorerDocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXMLEXPLORERVIEW_H__41D52536_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
