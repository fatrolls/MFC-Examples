// ex28aView.h : interface of the CEx28aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_)
#define AFX_EX28AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx28aView : public CScrollView
{
protected: // create from serialization only
	CEx28aView();
	DECLARE_DYNCREATE(CEx28aView)

// Attributes
public:
	CEx28aDoc* GetDocument();

private:
	CEx28aSet* m_pSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex28aView.cpp
inline CEx28aDoc* CEx28aView::GetDocument()
   { return (CEx28aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28AVIEW_H__4C4C2526_6EAD_11D0_8609_F283035DC070__INCLUDED_)
