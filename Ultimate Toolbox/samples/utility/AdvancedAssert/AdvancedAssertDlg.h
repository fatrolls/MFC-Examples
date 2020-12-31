// AdvancedAssertDlg.h : header file
//

#include "OXStaticHyperLink.h"

#if !defined(AFX_ADVANCEDASSERTDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_ADVANCEDASSERTDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAdvancedAssertDlg dialog

class CAdvancedAssertDlg : public CDialog
{
// Construction
public:
	CAdvancedAssertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdvancedAssertDlg)
	enum { IDD = IDD_ADVANCEDASSERT_DIALOG };
	COXStaticHyperLink	m_ctlAssertion;
	COXStaticHyperLink	m_ctlCustomize;
	COXStatic m_ctlStaticSampleCaption;
	COXStaticHyperLink m_ctlStaticAbout;
	COXStaticHyperLink m_ctlStaticClose;
	//}}AFX_DATA
	CString m_sNote1;
	CString m_sNote2;
	CString m_sEmailAddress;
	BOOL m_bSendMail;


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedAssertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAdvancedAssertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg LONG OnAboutActivated(UINT wParam, LONG lParam);
	afx_msg LONG OnCloseActivated(UINT wParam, LONG lParam);
	afx_msg LONG OnCustomizeActivated(UINT wParam, LONG lParam);
	afx_msg LONG OnAssertionActivated(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDASSERTDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
