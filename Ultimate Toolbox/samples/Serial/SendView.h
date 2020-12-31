#if !defined(AFX_SENDVIEW_H__26E6D944_0616_11D2_88B2_0080C859A484__INCLUDED_)
#define AFX_SENDVIEW_H__26E6D944_0616_11D2_88B2_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SendView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendView view

class CSerialDoc;

class CSendView : public CEditView
{
protected:
	CSendView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSendView)

// Attributes
public:
	CSerialDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSendView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_font;


// Generated message map functions
protected:
	//{{AFX_MSG(CSendView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SerialView.cpp
inline CSerialDoc* CSendView::GetDocument()
   { return (CSerialDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDVIEW_H__26E6D944_0616_11D2_88B2_0080C859A484__INCLUDED_)
