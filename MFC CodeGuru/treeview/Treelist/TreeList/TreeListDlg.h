// TreeListDlg.h : header file
//

#if !defined(AFX_TREELISTDLG_H__0ADCB517_5905_11D1_980A_004095E0DEFA__INCLUDED_)
#define AFX_TREELISTDLG_H__0ADCB517_5905_11D1_980A_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTreeListDlg dialog

#include "TLFrame.h"

class CTreeListDlg : public CDialog
{
// Construction
public:
	CTreeListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	CImageList m_cImageList;
	CTLFrame m_wndTreeList;
	//{{AFX_DATA(CTreeListDlg)
	enum { IDD = IDD_TREELIST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTreeListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREELISTDLG_H__0ADCB517_5905_11D1_980A_004095E0DEFA__INCLUDED_)
