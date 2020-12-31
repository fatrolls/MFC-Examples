// HtmlClockView.h : interface of the CHtmlClockView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLCLOCKVIEW_H__D39825ED_99C0_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_HTMLCLOCKVIEW_H__D39825ED_99C0_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHtmlClockView : public CHtmlView
{
protected: // create from serialization only
	CHtmlClockView();
	DECLARE_DYNCREATE(CHtmlClockView)

// Attributes
public:
	CHtmlClockDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlClockView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnTitleChange(LPCTSTR lpszText);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlClockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlClockView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HtmlClockView.cpp
inline CHtmlClockDoc* CHtmlClockView::GetDocument()
   { return (CHtmlClockDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLCLOCKVIEW_H__D39825ED_99C0_11D2_8E53_006008A82731__INCLUDED_)
