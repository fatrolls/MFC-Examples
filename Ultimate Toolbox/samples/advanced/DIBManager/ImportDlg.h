#if !defined(AFX_IMPORTDLG_H__97965B42_754D_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_IMPORTDLG_H__97965B42_754D_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImportDlg.h : header file
//

#include "OXHistoryCombo.h"
#include "OXSpinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog

class CImportDlg : public CDialog
{
protected:
	CButton& ctlOnePass() { 
		return *(CButton*)GetDlgItem(IDC_CHECK_ONE_PASS); }
	CButton& ctlDitherMethodFS() { 
		return *(CButton*)GetDlgItem(IDC_RADIO_DM_FLOYD_STEIN); }
	CButton& ctlDitherMethodOrdered() { 
		return *(CButton*)GetDlgItem(IDC_RADIO_DM_ORDERED); }
	CButton& ctlDitherMethodNone() { 
		return *(CButton*)GetDlgItem(IDC_RADIO_DM_NONE); }
	void ShowButtons();
	BOOL CheckFileName();

// Construction
public:
	CImportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportDlg)
	enum { IDD = IDD_DIALOG_IMPORT };
	CEdit	m_ctlEditColors;
	COXSpinCtrl	m_ctlSpinColors;
	COXHistoryCombo	m_cbFileName;
	BOOL	m_bColors;
	BOOL	m_bGrayscale;
	BOOL	m_bNoSmooth;
	BOOL	m_bOnePass;
	CString	m_sFileName;
	int		m_nColors;
	//}}AFX_DATA
	// we use mem file as temporarily one in which we import info from JPEG
	CMemFile m_tmpBMPFile;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportDlg)
	virtual void OnOK();
	afx_msg void OnCheckOnePass();
	afx_msg void OnCheckColors();
	afx_msg void OnCheckGrayscale();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDLG_H__97965B42_754D_11D1_A3D5_0080C83F712F__INCLUDED_)
