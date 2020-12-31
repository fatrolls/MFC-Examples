// CSHView.h : interface of the CCSHView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSHVIEW_H__73AC62E0_CCD6_11D1_8018_A601086D0638__INCLUDED_)
#define AFX_CSHVIEW_H__73AC62E0_CCD6_11D1_8018_A601086D0638__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCSHView : public CFormView
{
	static const DWORD m_nHelpIDs[];
protected: // create from serialization only
	CCSHView();
	DECLARE_DYNCREATE(CCSHView)

public:
	//{{AFX_DATA(CCSHView)
	enum{ IDD = IDD_CSH_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CCSHDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSHView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCSHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCSHView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnButtonSampleDlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CSHView.cpp
inline CCSHDoc* CCSHView::GetDocument()
   { return (CCSHDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHVIEW_H__73AC62E0_CCD6_11D1_8018_A601086D0638__INCLUDED_)
