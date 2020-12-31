#if !defined(AFX_DLGTEST_H__7D35F4B5_7531_11D1_8FA7_000000000000__INCLUDED_)
#define AFX_DLGTEST_H__7D35F4B5_7531_11D1_8FA7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgTest.h : header file
//

#include "CmdUIDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog

class CDlgTest : public CCmdUIDialog
{
// Construction
public:
	BOOL m_bDoIt;
	CDlgTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTest)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTest)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnUpdateButtonEdit(CCmdUI* pCmdUI);
	void OnUpdateButtonBrowse(CCmdUI* pCmdUI);
	void OnUpdateCheckExport(CCmdUI* pCmdUI);
	void OnUpdateCheckClone(CCmdUI* pCmdUI);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEST_H__7D35F4B5_7531_11D1_8FA7_000000000000__INCLUDED_)
