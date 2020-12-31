#if !defined(AFX_CUSTOMIZESTATICDLG_H__804A9323_C115_11D1_B475_3C3908C10000__INCLUDED_)
#define AFX_CUSTOMIZESTATICDLG_H__804A9323_C115_11D1_B475_3C3908C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeStaticDlg.h : header file
//

#include "OXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeStaticDlg dialog

class CCustomizeStaticDlg : public CDialog
{
// Construction
public:
	CCustomizeStaticDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeStaticDlg)
	enum { IDD = IDD_CUSTOMIZESTATIC_DIALOG };
	CEdit	m_ctlEditWindowText;
	CEdit	m_ctlEditToolTipText;
	BOOL	m_bFitToText;
	BOOL	m_bShowToolTip;
	CString	m_sToolTipText;
	DWORD	m_clr;
	CString	m_sFontName;
	CString	m_sWindowText;
	//}}AFX_DATA
	COXStatic* m_pStatic;
	LOGFONT m_lf;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeStaticDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void GetVars();
	void SetVars();
	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CCustomizeStaticDlg)
	afx_msg void OnButtonColor();
	afx_msg void OnButtonFont();
	afx_msg void OnCheckShowTooltip();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZESTATICDLG_H__804A9323_C115_11D1_B475_3C3908C10000__INCLUDED_)
