// MenuView.h : interface of the CMenuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUVIEW_H__D7E0A2ED_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUVIEW_H__D7E0A2ED_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMenuView : public CView
{
protected: // create from serialization only
	CMenuView();
	DECLARE_DYNCREATE(CMenuView)

// Attributes
public:
	CMenuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMenuView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MenuView.cpp
inline CMenuDoc* CMenuView::GetDocument()
   { return (CMenuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUVIEW_H__D7E0A2ED_F772_11D0_9C9A_444553540000__INCLUDED_)
