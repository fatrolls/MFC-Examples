// DEDemoDlg.h : header file
//

#if !defined(AFX_DEDEMODLG_H__1D8BBDF1_784C_11D1_8159_444553540000__INCLUDED_)
#define AFX_DEDEMODLG_H__1D8BBDF1_784C_11D1_8159_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDEDemoDlg dialog

#include "DropEdit.h"

class CDEDemoDlg : public CDialog
{
// Construction
public:
	CDEDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDEDemoDlg)
	enum { IDD = IDD_DEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDEDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDEDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFiles();
	afx_msg void OnFolders();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CDropEdit m_dropEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEDEMODLG_H__1D8BBDF1_784C_11D1_8159_444553540000__INCLUDED_)
