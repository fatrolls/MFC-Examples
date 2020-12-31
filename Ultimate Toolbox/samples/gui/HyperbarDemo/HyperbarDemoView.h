// HyperbarDemoView.h : interface of the CHyperbarDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HYPERBARDEMOVIEW_H__C7F27172_1BE2_4A2C_81D0_A8F6672AAD04__INCLUDED_)
#define AFX_HYPERBARDEMOVIEW_H__C7F27172_1BE2_4A2C_81D0_A8F6672AAD04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHyperbarDemoView : public CView
{
protected: // create from serialization only
	CHyperbarDemoView();
	DECLARE_DYNCREATE(CHyperbarDemoView)

// Attributes
public:
	CHyperbarDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperbarDemoView)
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
	virtual ~CHyperbarDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHyperbarDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HyperbarDemoView.cpp
inline CHyperbarDemoDoc* CHyperbarDemoView::GetDocument()
   { return (CHyperbarDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERBARDEMOVIEW_H__C7F27172_1BE2_4A2C_81D0_A8F6672AAD04__INCLUDED_)
