// FormatRTFDlg.h : header file
//

#if !defined(AFX_FORMATRTFDLG_H__96742796_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
#define AFX_FORMATRTFDLG_H__96742796_94A4_11D1_B661_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFDlg dialog

class CFormatRTFDlg : public CDialog
{
// Construction
public:
	CFormatRTFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFormatRTFDlg)
	enum { IDD = IDD_FORMATRTF_DIALOG };
	LRichEditCtrl	m_edRTF;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatRTFDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFormatRTFDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPbToggle();
	afx_msg void OnPbHide();
	afx_msg void OnPbShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATRTFDLG_H__96742796_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
