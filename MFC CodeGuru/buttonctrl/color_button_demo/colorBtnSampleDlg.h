// colorBtnSampleDlg.h : header file
//

#if !defined(AFX_COLORBTNSAMPLEDLG_H__5163CE19_D92D_11D1_A82F_0060974FADEB__INCLUDED_)
#define AFX_COLORBTNSAMPLEDLG_H__5163CE19_D92D_11D1_A82F_0060974FADEB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "colorbtn.h"

/////////////////////////////////////////////////////////////////////////////
// CColorBtnSampleDlg dialog

class CColorBtnSampleDlg : public CDialog
{
// Construction
public:
	CColorBtnSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorBtnSampleDlg)
	enum { IDD = IDD_COLORBTNSAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtnSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CColorButton m_btnCancel;
	CColorButton m_btnOK;
	CColorButton m_btnUp;
	CColorButton m_btnDown;
	CColorButton m_btnDelete;
	CColorButton m_btnAdd;

	// Generated message map functions
	//{{AFX_MSG(CColorBtnSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBTNSAMPLEDLG_H__5163CE19_D92D_11D1_A82F_0060974FADEB__INCLUDED_)
