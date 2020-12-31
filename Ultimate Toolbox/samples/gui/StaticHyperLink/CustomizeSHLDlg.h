#if !defined(AFX_CUSTOMIZESHLDLG_H__FA57A4C2_ADC7_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_CUSTOMIZESHLDLG_H__FA57A4C2_ADC7_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeSHLDlg.h : header file
//

#include "OXStaticHyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeSHLDlg dialog

class CCustomizeSHLDlg : public CDialog
{
// Construction
public:
	CCustomizeSHLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeSHLDlg)
	enum { IDD = IDD_CUSTOMIZESTATICHYPERLINK_DIALOG };
	CEdit	m_ctlEditWindowText;
	CComboBox	m_ctlComboAction;
	CEdit	m_ctlEditToolTipText;
	CString	m_sDefaultDirectory;
	BOOL	m_bErrorNotify;
	BOOL	m_bFitToText;
	BOOL	m_bShowToolTip;
	BOOL	m_bUseWindowText;
	CString	m_sFile;
	CString	m_sParameters;
	CString	m_sToolTipText;
	DWORD	m_clrUnvisited;
	int		m_nActionID;
	UINT	m_nCallbackMsgID;
	DWORD	m_clrVisited;
	CString	m_sFontName;
	CString	m_sWindowText;
	BOOL	m_bUseSpecialCursor;
	//}}AFX_DATA
	COXStaticHyperLink* m_pStaticHyperLink;
	LOGFONT m_lf;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeSHLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void GetVars();
	void SetVars();
	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CCustomizeSHLDlg)
	afx_msg void OnButtonClrUnvisited();
	afx_msg void OnButtonClrVisited();
	afx_msg void OnButtonFont();
	afx_msg void OnCheckShowTooltip();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZESHLDLG_H__FA57A4C2_ADC7_11D1_A3D5_0080C83F712F__INCLUDED_)
