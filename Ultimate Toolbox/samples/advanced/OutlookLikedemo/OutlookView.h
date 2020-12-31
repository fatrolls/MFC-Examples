// OutlookView.h : interface of the COutlookView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKVIEW_H__DA7AA830_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOKVIEW_H__DA7AA830_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COutlookDoc;

class COutlookView : public CView
{
protected: // create from serialization only
	COutlookView();
	DECLARE_DYNCREATE(COutlookView)

// Attributes
public:
	COutlookDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutlookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COXShortcutBar m_shb;
	CTreeCtrl m_tree;

	CImageList m_ilLarge;
	CImageList m_ilSmall;
	CImageList m_ilTree;
	CImageList m_ilTree2003;

// Generated message map functions
protected:
	afx_msg void OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnProperties();

	//{{AFX_MSG(COutlookView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSkinClassic();
	afx_msg void OnSkinOfficexp();
	afx_msg void OnSkinOffice2003();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutlookView.cpp
inline COutlookDoc* COutlookView::GetDocument()
   { return (COutlookDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKVIEW_H__DA7AA830_2C67_11D2_88E3_0080C859A484__INCLUDED_)
