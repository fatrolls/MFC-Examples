#ifndef __SPECFILEDLG_H__
#define __SPECFILEDLG_H__

// SpecFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpecialFileDialog dialog

class CSpecialFileDialog : public CFileDialog
{
public:
	CString m_strFilename;
	BOOL m_bDeleteAll;

// Construction
public:
	CSpecialFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

// Dialog Data
	//{{AFX_DATA(CSpecialFileDialog)
	enum { IDD = IDD_FILESPECIAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecialFileDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpecialFileDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __SPECFILEDLG_H__
