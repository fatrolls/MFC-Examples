#ifndef __TEXTDIALOG_H__
#define __TEXTDIALOG_H__

// TextDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDialog dialog

class CTextDialog : public CDialog
{
// Construction
public:
	CTextDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextDialog)
	enum { IDD = IDD_TEXTDIALOG };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __TEXTDIALOG_H__
