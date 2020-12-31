// MDITestView.h : interface of the CMDITestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDITESTVIEW_H__8765578F_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
#define AFX_MDITESTVIEW_H__8765578F_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMDITestView : public CView
{
protected: // create from serialization only
	CMDITestView();
	DECLARE_DYNCREATE(CMDITestView)

// Attributes
public:
	CMDITestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITestView)
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
	virtual ~CMDITestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDITestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MDITestView.cpp
inline CMDITestDoc* CMDITestView::GetDocument()
   { return (CMDITestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDITESTVIEW_H__8765578F_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
