// IPAddressCheckDlg.h : header file
//

#if !defined(AFX_IPADDRESSCHECKDLG_H__3C974E26_EB56_11D1_BB83_0040F684401F__INCLUDED_)
#define AFX_IPADDRESSCHECKDLG_H__3C974E26_EB56_11D1_BB83_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCheckDlg dialog
void WINAPI DDX_IPAddress(CDataExchange* pDX, int nIDC, UINT & value);

class CIPAddressCheckDlg : public CDialog
{
// Construction
public:
	CIPAddressCheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPAddressCheckDlg)
	enum { IDD = IDD_IPADDRESSCHECK_DIALOG };
	UINT	m_IPAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddressCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPAddressCheckDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESSCHECKDLG_H__3C974E26_EB56_11D1_BB83_0040F684401F__INCLUDED_)
