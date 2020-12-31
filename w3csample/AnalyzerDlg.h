#if !defined(AFX_ANALYZERDLG_H__C16EA7F9_8E0B_4FB0_94BB_A205B4A2B68F__INCLUDED_)
#define AFX_ANALYZERDLG_H__C16EA7F9_8E0B_4FB0_94BB_A205B4A2B68F__INCLUDED_

#include "HttpAnalyzerView.h"
#include "w3c.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalyzerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalyzerDlg dialog

class CAnalyzerDlg : public CDialog
{
public:
	CHttpAnalyzerView *_pview;
	W3Client *_pclient;	
// Construction
public:
	CAnalyzerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnalyzerDlg)
	enum { IDD = IDD_ANALYZER };
	CString	_szheader;
	CString	_szsource;
	CString	_szurl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalyzerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalyzerDlg)
	afx_msg void OnGo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYZERDLG_H__C16EA7F9_8E0B_4FB0_94BB_A205B4A2B68F__INCLUDED_)
