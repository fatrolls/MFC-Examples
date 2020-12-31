#if !defined(AFX_CSHDIALOG_H__73AC6302_CCD6_11D1_8018_A601086D0638__INCLUDED_)
#define AFX_CSHDIALOG_H__73AC6302_CCD6_11D1_8018_A601086D0638__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSHDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSHDialog dialog
class CCSHDialog : public CDialog
{
// Construction
public:
	CCSHDialog();
	CCSHDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	CCSHDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);

// Implementation
protected:	
	virtual const DWORD* GetHelpIDs() = 0;

	// Generated message map functions
	//{{AFX_MSG(CCSHDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHDIALOG_H__73AC6302_CCD6_11D1_8018_A601086D0638__INCLUDED_)
