#if !defined(AFX_TESTDRAGEDITDLG_H__871E3CD7_6359_11D1_8251_444553540000__INCLUDED_)
#define AFX_TESTDRAGEDITDLG_H__871E3CD7_6359_11D1_8251_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestDragEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDragEditDlg dialog
#include "CDragEdit.h"

class CTestDragEditDlg : public CDialog
{
// Construction
public:
	CTestDragEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDragEditDlg)
	enum { IDD = IDD_DRAGEDIT };
	CDragEdit	m_edit2;
	CDragEdit	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDragEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDragEditDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDRAGEDITDLG_H__871E3CD7_6359_11D1_8251_444553540000__INCLUDED_)
