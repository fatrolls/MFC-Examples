// intsim.h : header file
//

#ifndef INTSIM_H
#define INTSIM_H

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CIntsimApp

class CIntsimApp : public CWinApp
{
public:
	CIntsimApp();
	~CIntsimApp();

	virtual BOOL InitInstance();

	//{{AFX_MSG(CIntsimApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = MAINDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	void (FAR *myvxd)();		// MYVXD api entry point

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnExit();
	afx_msg void OnInterrupt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
