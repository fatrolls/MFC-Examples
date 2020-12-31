// ex26aView.h : interface of the CEx26aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26AVIEW_H__BE454451_5F51_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26AVIEW_H__BE454451_5F51_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx26aView : public CView
{
protected: // create from serialization only
	CEx26aView();
	DECLARE_DYNCREATE(CEx26aView)

// Attributes
public:
	CEx26aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26aView)
	afx_msg void OnStorageRead();
	afx_msg void OnStorageWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex26aView.cpp
inline CEx26aDoc* CEx26aView::GetDocument()
   { return (CEx26aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26AVIEW_H__BE454451_5F51_11D0_848F_00400526305B__INCLUDED_)
