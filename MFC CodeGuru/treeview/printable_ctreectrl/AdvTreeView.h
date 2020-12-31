//  ---------------------------------------------------------
//
//      ( C )     Copyright C - Channel Eng. AG 1998
//      Use or copying of all or any part of the document,
//      except as permitted by the License Agreement is
//      prohibited.
//
//      Author  : Michael Wild, 5063  C - Channel Eng. AG
//
//      Purpose : 
//      This File contains the class CAdvancedTreeView
// 
//      Creation date: April 28, 1998
//
//  ---------------------------------------------------------

#if !defined(AFX_TESTVIEW_H__26090B10_8B26_11D1_8E51_0000F877728F__INCLUDED_)
#define AFX_TESTVIEW_H__26090B10_8B26_11D1_8E51_0000F877728F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AdvTreeCtrl.h"

class CAdvancedTreeView : public CFormView
{
protected: // create from serialization only
	CAdvancedTreeView();
	DECLARE_DYNCREATE(CAdvancedTreeView)

public:
	//{{AFX_DATA(CAdvancedTreeView)
	enum { IDD = IDD_TEST_FORM };
	CAdvancedTreeCtrl	m_wndTree;
	//}}AFX_DATA

private:
    BOOL  m_bFirstTime;

public:
	CPrintTreeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedTreeView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAdvancedTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAdvancedTreeView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#ifndef _DEBUG  // debug version in testView.cpp
inline CPrintTreeDoc  * CAdvancedTreeView::GetDocument()
   { return (CPrintTreeDoc  *)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__26090B10_8B26_11D1_8E51_0000F877728F__INCLUDED_)
