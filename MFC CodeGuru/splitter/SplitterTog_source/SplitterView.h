// SplitterView.h : interface of the CSplitterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERVIEW_H__C5E7581E_BD1F_11D1_A748_00C04FA3325E__INCLUDED_)
#define AFX_SPLITTERVIEW_H__C5E7581E_BD1F_11D1_A748_00C04FA3325E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSplitterView : public CView
{
protected: // create from serialization only
	CSplitterView();
	DECLARE_DYNCREATE(CSplitterView)

// Attributes
public:
	CSplitterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterView)
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
	virtual ~CSplitterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SplitterView.cpp
inline CSplitterDoc* CSplitterView::GetDocument()
   { return (CSplitterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERVIEW_H__C5E7581E_BD1F_11D1_A748_00C04FA3325E__INCLUDED_)
