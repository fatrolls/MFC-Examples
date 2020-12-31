// AvidemoDlg.h : header file
//

#if !defined(AFX_AVIDEMODLG_H__0E6D65A6_A650_11D1_ABA0_443100C10000__INCLUDED_)
#define AFX_AVIDEMODLG_H__0E6D65A6_A650_11D1_ABA0_443100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAvidemoDlg dialog

class CAvidemoDlg : public CDialog
{
// Construction
public:
	CAvidemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAvidemoDlg)
	enum { IDD = IDD_AVIDEMO_DIALOG };
	CProgressCtrl	m_progress;
	CAnimateCtrl	m_avi;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAvidemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAvidemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnProgBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDEMODLG_H__0E6D65A6_A650_11D1_ABA0_443100C10000__INCLUDED_)
