// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__8E0F0932_0728_11D3_A9F8_2EA565000000__INCLUDED_)
#define AFX_LEFTVIEW_H__8E0F0932_0728_11D3_A9F8_2EA565000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParserViewDoc;

#include "ParserViewView.h"


class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CParserViewDoc* GetDocument();

    CParserViewView* m_pRightView;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
    void FillTree(HTREEITEM hParent, COXParserElement* pElement);
    LPCTSTR BriefText(LPCTSTR szText);
    void ExpandBranch(HTREEITEM hItem, UINT nCode);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    COXParser parser;
    int m_nCloseEmptyFolder;
    int m_nCloseFolder;
    int m_nOpenFolder;
    int m_nTextItem;
    int m_nAttribute;
    int m_nComment;
    int m_nMarkup;
    int m_nProcInstr;
    int m_nCData;

    CImageList m_Images;


// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExpandAll();
	afx_msg void OnCollapseAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CParserViewDoc* CLeftView::GetDocument()
   { return (CParserViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__8E0F0932_0728_11D3_A9F8_2EA565000000__INCLUDED_)
