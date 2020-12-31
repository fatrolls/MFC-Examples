// DemoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__CC1A7709_0681_11D2_B105_00805F6D79ED__INCLUDED_)
#define AFX_DEMODLG_H__CC1A7709_0681_11D2_B105_00805F6D79ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
	CVtxButton	m_cButton12;
	CVtxButton	m_cButton11;
	CVtxButton	m_cButton10;
	CVtxButton	m_cButton9;
	CVtxButton	m_cButton8;
	CVtxButton	m_cButton7;
	CVtxButton	m_cButton6;
	CVtxButton	m_cButton5;
	CVtxButton	m_cButton4;
	CVtxButton	m_cButton3;
	CVtxButton	m_cButton2;
	CVtxButton	m_cButton1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__CC1A7709_0681_11D2_B105_00805F6D79ED__INCLUDED_)
