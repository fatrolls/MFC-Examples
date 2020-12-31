// OutLookStyleView.h : interface of the COutLookStyleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKSTYLEVIEW_H__C50FD4FC_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_OUTLOOKSTYLEVIEW_H__C50FD4FC_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COutLookStyleView : public CView
{
protected: // create from serialization only
	COutLookStyleView();
	DECLARE_DYNCREATE(COutLookStyleView)

// Attributes
public:
	COutLookStyleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutLookStyleView)
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
	virtual ~COutLookStyleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutLookStyleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutLookStyleView.cpp
inline COutLookStyleDoc* COutLookStyleView::GetDocument()
   { return (COutLookStyleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKSTYLEVIEW_H__C50FD4FC_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
