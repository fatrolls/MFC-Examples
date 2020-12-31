// MdiExView.h : interface of the CMdiExView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIEXVIEW_H__250DE49F_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
#define AFX_MDIEXVIEW_H__250DE49F_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMdiExView : public CView
{
protected: // create from serialization only
	CMdiExView();
	DECLARE_DYNCREATE(CMdiExView)

// Attributes
public:
	CMdiExDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiExView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMdiExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMdiExView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MdiExView.cpp
inline CMdiExDoc* CMdiExView::GetDocument()
   { return (CMdiExDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIEXVIEW_H__250DE49F_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
