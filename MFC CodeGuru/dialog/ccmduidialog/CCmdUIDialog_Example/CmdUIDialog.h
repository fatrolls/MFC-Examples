#if !defined(AFX_CMDUIDIALOG_H__7D35F4B8_7531_11D1_8FA7_000000000000__INCLUDED_)
#define AFX_CMDUIDIALOG_H__7D35F4B8_7531_11D1_8FA7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CmdUIDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCmdUIDialog dialog

class CCmdUIDialog : public CDialog
{
// Construction
public:
	CCmdUIDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	CCmdUIDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CCmdUIDialog();

	BOOL ContinueModal();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdUIDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDUIDIALOG_H__7D35F4B8_7531_11D1_8FA7_000000000000__INCLUDED_)
