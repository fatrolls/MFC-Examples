// FileWatcherDlg.h : header file
//

#include "OXFileWatcher.h"

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg dialog

class CFileWatcherDlg : public CDialog
{
	COXFileWatcher	fwWatcher;

// Construction
public:
	~CFileWatcherDlg();
	CFileWatcherDlg(CWnd* pParent = NULL);	// standard constructor

	CString&	GetStringFromFilter( DWORD Filter, CString& str);
	CString&	GetStringFromAction( DWORD Action, CString& str);

// Dialog Data
	//{{AFX_DATA(CFileWatcherDlg)
	enum { IDD = IDD_FILEWATCHER_DIALOG };
	CListCtrl	m_lbWatchedDirs;
	CListCtrl	m_lbNotifications;
	//}}AFX_DATA

	CPtrArray m_arPaths;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileWatcherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileWatcherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddDir();
	afx_msg void OnRemoveDir();
	afx_msg LRESULT OnFileNotify(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
