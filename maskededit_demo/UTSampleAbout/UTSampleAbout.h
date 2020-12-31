#if !defined(_UTSAMPLEABOUTDLG_H_)
#define _UTSAMPLEABOUTDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "../maskededit_src/oxdllext.h"

#include "UTSampleAboutResource.h"

/////////////////////////////////////////////////////////////////////////////
// CUTSampleAboutDlg dialog used for App About

class CUTSampleAboutDlg : public CDialog
{
public:
	CUTSampleAboutDlg();
	CUTSampleAboutDlg(CString sTitle, CString sDescriptionFile);
	CUTSampleAboutDlg(UINT nTitleID, UINT nDescriptionFileID); 

	static DWORD CALLBACK RichEditStreamCallback(DWORD dwCookie, 
		LPBYTE pbBuff, LONG cb, LONG FAR *pcb); 

// Dialog Data
	//{{AFX_DATA(CUTSampleAboutDlg)
	enum { IDD = IDD_UT_SAMPLE_ABOUTBOX };
	CString m_sTitle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTSampleAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CUTSampleAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // _UTSAMPLEABOUTDLG_H_