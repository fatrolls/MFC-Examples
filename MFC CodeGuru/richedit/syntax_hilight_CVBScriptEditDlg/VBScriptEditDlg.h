// VBScriptEditDlg.h : header file
//

#if !defined(AFX_VBSCRIPTEDITDLG_H__62D8DFD9_C490_11D1_8635_00403395B157__INCLUDED_)
#define AFX_VBSCRIPTEDITDLG_H__62D8DFD9_C490_11D1_8635_00403395B157__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCVBScriptEditDlg dialog

#include "TWScriptEdit.h"

class CCVBScriptEditDlg : public CDialog
{
// Construction
public:
	CCVBScriptEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCVBScriptEditDlg)
	enum { IDD = IDD_CVBSCRIPTEDITDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCVBScriptEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

// TWSCRIPTEDIT	->
	CTWScriptEdit m_wndScriptEdit;
// <- TWSCRIPTEDIT

	// Generated message map functions
	//{{AFX_MSG(CCVBScriptEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VBSCRIPTEDITDLG_H__62D8DFD9_C490_11D1_8635_00403395B157__INCLUDED_)
