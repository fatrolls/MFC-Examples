// RegistryDemoDlg.h : header file
//

#if !defined(AFX_REGISTRYDEMODLG_H__CE454E23_E84D_11D1_8063_0A9C28000000__INCLUDED_)
#define AFX_REGISTRYDEMODLG_H__CE454E23_E84D_11D1_8063_0A9C28000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg dialog

class CRegistryDemoDlg : public CDialog
{
// Construction
public:
	CRegistryDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegistryDemoDlg)
	enum { IDD = IDD_REGISTRYDEMO_DIALOG };
	CEdit	m_EditBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistryDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegistryDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTRYDEMODLG_H__CE454E23_E84D_11D1_8063_0A9C28000000__INCLUDED_)
