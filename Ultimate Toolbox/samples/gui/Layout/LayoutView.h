// LayoutView.h : interface of the CLayoutView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTVIEW_H__7D955F32_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
#define AFX_LAYOUTVIEW_H__7D955F32_0A9F_11D2_88B8_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COXLayoutManager;

class CLayoutView : public CFormView
{
protected: // create from serialization only
	CLayoutView();
	DECLARE_DYNCREATE(CLayoutView)

public:
	//{{AFX_DATA(CLayoutView)
	enum { IDD = IDD_LAYOUT_FORM };
	CTreeCtrl	m_tree;
	CSliderCtrl	m_slider;
	CProgressCtrl	m_progress;
	CListBox	m_list;
	CEdit	m_edit;
	CComboBox	m_combo;
	//}}AFX_DATA

// Attributes
public:
	CLayoutDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayoutView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLayoutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COXLayoutManager* m_pLayoutManager;

// Generated message map functions
protected:
	//{{AFX_MSG(CLayoutView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LayoutView.cpp
inline CLayoutDoc* CLayoutView::GetDocument()
   { return (CLayoutDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYOUTVIEW_H__7D955F32_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
