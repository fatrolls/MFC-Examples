#if !defined(AFX_STARTSERVICEDLG_H__33EEDDDE_0C35_42F0_A80F_49C376E00CB7__INCLUDED_)
#define AFX_STARTSERVICEDLG_H__33EEDDDE_0C35_42F0_A80F_49C376E00CB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartServiceDlg.h : header file
//

#include "RootDlg.h"
#include <winsvc.h>
#include <process.h>

/////////////////////////////////////////////////////////////////////////////
// CStartServiceDlg dialog

class CStartServiceDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CStartServiceDlg)
// Construction
public:
	CStartServiceDlg(CWnd* pParent = NULL);   // standard constructor
    ~CStartServiceDlg();
// Dialog Data
	//{{AFX_DATA(CStartServiceDlg)
	enum { IDD = IDD_START_SERVICE_DLG };
	CBCGPEdit	m_edtExe;
	CComboBox	m_cmbInterface;
	CListBox	m_ListEXE;
	CBCGPMenuButton	m_btnServiceControl;
	UINT	m_uPauseStart;
	UINT	m_uPauseEnd;
	CString	m_strExe;
	CString	m_strCmdLine;
	UINT	m_uInterGap;
	CString	m_strServiceName;
	int		m_iLast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartServiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStartServiceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListExe();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnCreateSettingFile();
	afx_msg void OnBtnServiceMenu();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

	CMenu menu;
public:
	static bool OnService();
	struct StartExeInfo
	{
		StartExeInfo(CString strExeFile, CString strCmdLine, bool bUserInterface, int nPauseStart, int nPauseEnd)
		{
            this->strExeFile = strExeFile;
			this->strCmdLine = strCmdLine;
			this->bUserInterface = bUserInterface;
			this->nPauseStart = nPauseStart;
			this->nPauseEnd = nPauseEnd;
		}

		CString strExeFile;
		CString strCmdLine;
		bool bUserInterface;
		int nPauseStart;
		int nPauseEnd;

		void OutputToSettingFile(CString Item, CString IniFile);
	};

	BOOL Install(char* pPath, char* pName, BOOL bPrompt = TRUE);
	BOOL UnInstall(char* pName, BOOL bPrompt = TRUE);
	BOOL RunService(char* pName, int nArg, char** pArg, BOOL bPrompt = TRUE) ;
	BOOL KillService(char* pName, BOOL bPrompt = TRUE);
private:
	void ParseSettingFile();
	static BOOL StartProcess(int nIndex);
	static void EndProcess(int nIndex) ;
	static VOID WINAPI XYNTServiceMain( DWORD dwArgc, LPTSTR *lpszArgv );
	static VOID WINAPI XYNTServiceHandler(DWORD fdwControl);
	static UINT WINAPI WorkerProc(void* pParam);

    vector<StartExeInfo> m_StartExeInfo;
	static PROCESS_INFORMATION* m_pProcInfo;
	static int m_nProcCount;
	static SERVICE_STATUS          serviceStatus; 
    static SERVICE_STATUS_HANDLE   hServiceStatusHandle; 
	static char m_pServiceName[500];
	//static SERVICE_TABLE_ENTRY   DispatchTable[2];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTSERVICEDLG_H__33EEDDDE_0C35_42F0_A80F_49C376E00CB7__INCLUDED_)
