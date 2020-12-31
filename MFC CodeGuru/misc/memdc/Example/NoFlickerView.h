// NoFlickerView.h : interface of the CNoFlickerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOFLICKERVIEW_H__62D4188D_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_)
#define AFX_NOFLICKERVIEW_H__62D4188D_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CNoFlickerView : public CView
{
protected: // create from serialization only
	CNoFlickerView();
	DECLARE_DYNCREATE(CNoFlickerView)

// Attributes
public:
	CNoFlickerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoFlickerView)
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
	virtual ~CNoFlickerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNoFlickerView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NoFlickerView.cpp
inline CNoFlickerDoc* CNoFlickerView::GetDocument()
   { return (CNoFlickerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOFLICKERVIEW_H__62D4188D_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_)
