// UNCListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUNCListDlg dialog

#include "OXIteratorUNC.h"

class CUNCListDlg : public CDialog
{
// Construction
public:
	void SetSearchUnc (COXIteratorUNC iterUNC, BOOL bFiles, BOOL bDirs, 
		BOOL bRecursive, BOOL bDepthFirst);
	CUNCListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUNCListDlg)
	enum { IDD = IDD_UNC_LIST };
	CButton	m_wndClose;
	CListBox	m_wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUNCListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bRecursive;
	BOOL m_bDirs;
	BOOL m_bFiles;
	BOOL m_bDepthFirst;
	COXIteratorUNC m_iterUNC;

	// Generated message map functions
	//{{AFX_MSG(CUNCListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
