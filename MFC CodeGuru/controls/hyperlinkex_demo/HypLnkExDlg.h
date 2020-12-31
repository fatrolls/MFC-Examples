// HypLnkExDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHypLnkExDlg dialog

#include "HyperLink.h"

class CHypLnkExDlg : public CDialog
{
// Construction
public:
	CHypLnkExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHypLnkExDlg)
	enum { IDD = IDD_HYPLNKEX_DIALOG };
	CHyperLink m_hyperlink1;
	CHyperLink m_hyperlink2;
	CHyperLink m_hyperlink3;
	CHyperLink m_hyperlink4;
	CHyperLink m_hyperlink5;
	BOOL m_bUseHover;
	BOOL m_bUnderline;
	BOOL m_bShowURL;
	BOOL m_bItalic;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHypLnkExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHypLnkExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CFont m_Font;
	CStatic m_static;
};
