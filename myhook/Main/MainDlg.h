// MainDlg.h : header file
//

#if !defined(AFX_MAINDLG_H__CB8C7E17_3483_420C_94FC_04C8045DB745__INCLUDED_)
#define AFX_MAINDLG_H__CB8C7E17_3483_420C_94FC_04C8045DB745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction 
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor
    ~CMainDlg();
// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAIN_DIALOG };
	CButton	m_wndPlace;
	CListBox	m_FuncList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeListFunction();
	afx_msg void OnFileAddMachine();
	afx_msg void OnFileDeleteMachine();
	afx_msg void OnFileExecuteProcess();
	afx_msg void OnFileKillProcess();
	afx_msg void OnFileOpen();
	afx_msg void OnFileRefreshprocess();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileShutdownHalt();
	afx_msg void OnFileShutdownReboot();
	afx_msg void OnFileshutdownAbortshutdown();
	afx_msg void OnSettingsTimers();
	afx_msg void OnSettingsWindowAlwaysontop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddDlg(CRuntimeClass* pDlgClass, CString strCaption);
	void InitialFunctionList();
	static LRESULT CALLBACK DialogBoxCallbackProc(int code, WPARAM wParam, LPARAM lparam);
	static HHOOK m_hHook;
	static CBCGPDialog m_MessageBox;
	static CBCGPDialog* m_pCurDlg;
public:
	map<CRuntimeClass*, pair<CDialog*, CRect> > m_aChild;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__CB8C7E17_3483_420C_94FC_04C8045DB745__INCLUDED_)
