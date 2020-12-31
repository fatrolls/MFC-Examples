#if !defined(AFX_APPLICATIONSDIALOG_H__0786AFA1_58C3_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_APPLICATIONSDIALOG_H__0786AFA1_58C3_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ApplicationsDialog.h : header file
//

#include "afxtempl.h"

#include "PageDialog.h"
#include "OXTreeCtrl.h"
#include "OXLayoutManager.h"
#include "OXSysInfo.h"
#include "OXProcess.h"

/////////////////////////////////////////////////////////////////////////////
// CApplicationsDialog dialog

typedef struct _tagAPPLICATIONINFO
{
	DWORD dwProcessID;
	HWND hMainWnd;
	BOOL bGotRespond;

	// constructor
	_tagAPPLICATIONINFO()
	{
		dwProcessID=0xffffffff;
		hMainWnd=NULL;
		bGotRespond=TRUE;
	}

	// copy constructor
	_tagAPPLICATIONINFO& operator=(const _tagAPPLICATIONINFO& appInfo)
	{
		dwProcessID=appInfo.dwProcessID;
		hMainWnd=appInfo.hMainWnd;
		bGotRespond=appInfo.bGotRespond;
		return *this;
	}

} APPLICATIONINFO;

typedef CArray<APPLICATIONINFO,APPLICATIONINFO&> CAppInfoArray;


class CApplicationsDialog : public CPageDialog
{
// Construction
public:
	CApplicationsDialog();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CApplicationsDialog)
	enum { IDD = IDD_APPLICATIONS_DIALOG };
	CSpinButtonCtrl	m_spinExpandLevel;
	CEdit	m_editExpandLevel;
	COXTreeCtrl	m_tree;
	UINT	m_nExpandLevel;
	int		m_nExpandType;
	//}}AFX_DATA

protected:
	void PopulateTree();
	void ExpandTree(int nExpandLevel=-1, HTREEITEM htiParent=NULL);
	HTREEITEM InsertItem(CString sItem, HTREEITEM htiParent=NULL, int nImage=-1, 
		CFont* pFont=NULL, COLORREF clr=CLR_NONE);

public:
	virtual ~CApplicationsDialog() {
		CleanThreads();
	}
	virtual BOOL IsRefreshAvailable() { return TRUE; }
	virtual void Refresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ilTree;
	COXLayoutManager m_LayoutManager;
	COXSysInfo m_SysInfo;
	CAppInfoArray m_arrAppInfo;
	CArray<HANDLE,HANDLE> m_arrThreads;
	int m_nCurrentIndex;
	COXProcess m_process;

protected:
	virtual void OnInitDialog();
	void ShowControls();
	void CleanThreads();

	static BOOL CALLBACK EnumMainWindows(HWND hWnd, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CApplicationsDialog)
	afx_msg void OnRadioExpandall();
	afx_msg void OnRadioExpandlevel();
	afx_msg void OnDblclkTreeServices(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTreeApplications(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnAppWndSwitchTo();
	afx_msg void OnAppWndBringToFront();
	afx_msg void OnAppWndMinimize();
	afx_msg void OnAppWndMaximize();
	afx_msg void OnAppWndRestore();
	afx_msg void OnAppWndClose();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATIONSDIALOG_H__0786AFA1_58C3_11D2_B475_00E0291A4FD3__INCLUDED_)
