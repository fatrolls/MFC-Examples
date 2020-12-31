// FindDialog.h : header file
//

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include "XEditPrompt.h"
//#include "XHtmlTree.h"

/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog

class CFindDialog : public CDialog
{
// Construction
public:
	CFindDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindDialog)
	enum { IDD = IDD_FIND_DLG };
	CXEditPrompt	m_edtFind;
	int				m_nFindStart;
	int				m_nFindDir;
	CString			m_strFind;
	BOOL			m_bCheck;
	//}}AFX_DATA
	CRect			m_rect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //FINDDIALOG_H
