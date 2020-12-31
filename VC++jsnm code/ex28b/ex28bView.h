// ex28bView.h : interface of the CEx28bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28BVIEW_H__E38A6DC3_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
#define AFX_EX28BVIEW_H__E38A6DC3_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx28bSet;

class CEx28bView : public CRecordView
{
protected: // create from serialization only
	CEx28bView();
	DECLARE_DYNCREATE(CEx28bView)

public:
	//{{AFX_DATA(CEx28bView)
	enum { IDD = IDD_EX28B_FORM };
	CEx28bSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CEx28bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28bView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnMove(UINT nIDMoveCommand);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28bView)
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordClearfields();
	afx_msg void OnRecordDelete();
	afx_msg void OnRecordUpdate();
	afx_msg void OnUpdateRecordUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex28bView.cpp
inline CEx28bDoc* CEx28bView::GetDocument()
   { return (CEx28bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28BVIEW_H__E38A6DC3_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
