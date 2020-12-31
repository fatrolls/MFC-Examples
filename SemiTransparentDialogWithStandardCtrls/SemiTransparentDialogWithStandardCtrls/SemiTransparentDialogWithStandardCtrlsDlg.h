
// SemiTransparentDialogWithStandardCtrlsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

#include "./Src/ImgDialogBase.h"

// CSemiTransparentDialogWithStandardCtrlsDlg dialog
class CSemiTransparentDialogWithStandardCtrlsDlg : public CImgDialogBase
{
// Construction
public:
	CSemiTransparentDialogWithStandardCtrlsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SEMITRANSPARENTDIALOGWITHSTANDARDCTRLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonDemo2();
	DECLARE_MESSAGE_MAP()
	CListBox m_ctlListbox;
public:
	afx_msg void OnBnClickedButton2();
};
