// TcxMsgBoxDemoDlg.h : header file
//

#if !defined(AFX_TCXMSGBOXDEMODLG_H__5887525B_90FF_11D3_A393_00104B4DFB35__INCLUDED_)
#define AFX_TCXMSGBOXDEMODLG_H__5887525B_90FF_11D3_A393_00104B4DFB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBoxDemoDlg dialog

class CTcxMsgBoxDemoDlg : public CDialog
{
// Construction
public:
	CTcxMsgBoxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTcxMsgBoxDemoDlg)
	enum { IDD = IDD_TCXMSGBOXDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcxMsgBoxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTcxMsgBoxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSample1();
	afx_msg void OnSample2();
	afx_msg void OnSample3();
	afx_msg void OnSample4();
	afx_msg void OnSample5();
	afx_msg void OnSample6();
	afx_msg void OnSample7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCXMSGBOXDEMODLG_H__5887525B_90FF_11D3_A393_00104B4DFB35__INCLUDED_)
