// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__10814F93_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
#define AFX_LEFTVIEW_H__10814F93_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxtempl.h"

#include "OXShellFolderTree.h"


const UINT IDC_FOLDERTREE=1000;

class CFileExplorerDoc;

class CLeftView : public CView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFileExplorerDoc* GetDocument();

	COXShellFolderTree m_folderTree;

	CArray<LPITEMIDLIST,LPITEMIDLIST> m_arrHistory;
	int m_nCurrentItemInHistory;

	// flag that defines if right pane list control wiil be repopulated
	// when new folder in the tree is selected
	BOOL m_bPopulateList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnSelectFolder(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnEditDelete();
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void OnUpdate(CCmdUI* pCmdUI, UINT nID);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFileExplorerDoc* CLeftView::GetDocument()
   { return (CFileExplorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__10814F93_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
