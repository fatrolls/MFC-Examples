// HLSampleDlg.h : header file
//

#if !defined(AFX_HLSAMPLEDLG_H__D1625067_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HLSAMPLEDLG_H__D1625067_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHLSampleDlg dialog

#include "HyperLink.h"

class CHLSampleDlg : public CDialog
{
// Construction
public:
	CHLSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHLSampleDlg)
	enum { IDD = IDD_HLSAMPLE_DIALOG };
	CHyperLink	m_HyperLink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHLSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHLSampleDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLSAMPLEDLG_H__D1625067_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
