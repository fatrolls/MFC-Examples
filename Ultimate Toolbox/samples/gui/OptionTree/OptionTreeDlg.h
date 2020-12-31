// OptionTreeDlg.h : header file
//

#if !defined(AFX_OPTIONTREEDLG_H__1D5197E7_DB32_11D2_B476_00E0291A4FD3__INCLUDED_)
#define AFX_OPTIONTREEDLG_H__1D5197E7_DB32_11D2_B476_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXOptionTreeCtrl.h"
#include "OXSeparator.h"
#include "OXStaticText.h"

/////////////////////////////////////////////////////////////////////////////
// COptionTreeDlg dialog

class COptionTreeDlg : public CDialog
{
// Construction
public:
	COptionTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COptionTreeDlg)
	enum { IDD = IDD_OPTIONTREE_DIALOG };
	COXStaticText	m_staticUpdateInfo;
	COXSeparator	m_separator2;
	COXSeparator	m_separator1;
	COXOptionTreeCtrl	m_treeOption;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COptionTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnOptionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONTREEDLG_H__1D5197E7_DB32_11D2_B476_00E0291A4FD3__INCLUDED_)
