// ex12aView.h : interface of the CEx12aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12AVIEW_H__4AF8BADF_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12AVIEW_H__4AF8BADF_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_

#include "Property.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx12aView : public CView
{
protected: // create from serialization only
	CEx12aView();
	DECLARE_DYNCREATE(CEx12aView)

// Attributes
public:
	CEx12aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CRichEditCtrl m_rich;
	virtual ~CEx12aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12aView)
	afx_msg void OnTransferGetData();
	afx_msg void OnTransferStoreData();
	afx_msg void OnUpdateTransferStoreData(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFormatDefault();
	afx_msg void OnFormatSelection();
	afx_msg void OnUpdateFormatSelection(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnUserApply(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bDefault; // TRUE default format, FALSE selection
	CFontSheet m_sh;
	void Format(CHARFORMAT& cf);
};

#ifndef _DEBUG  // debug version in ex12aView.cpp
inline CEx12aDoc* CEx12aView::GetDocument()
   { return (CEx12aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12AVIEW_H__4AF8BADF_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
