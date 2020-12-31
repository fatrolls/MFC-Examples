#if !defined(AFX_SLOWVIEW_H__7137DCA0_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
#define AFX_SLOWVIEW_H__7137DCA0_B77C_11D1_AE72_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SlowView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSlowView view

class CSlowView : public CListView
{
protected:
	CSlowView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSlowView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlowView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSlowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSlowView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLOWVIEW_H__7137DCA0_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
