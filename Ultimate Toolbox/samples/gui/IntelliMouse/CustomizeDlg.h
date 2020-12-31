#if !defined(AFX_CUSTOMIZEDLG_H__166392C2_9CF5_11D1_B475_444553540000__INCLUDED_)
#define AFX_CUSTOMIZEDLG_H__166392C2_9CF5_11D1_B475_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog

class CCustomizeDlg : public CDialog
{
// Construction
public:
	CCustomizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeDlg)
	enum { IDD = IDD_CUSTOMIZE };
	CButton	m_ctlRadioTextType;
	CEdit	m_ctlEditWidth;
	CEdit	m_ctlEditRows;
	CComboBox	m_ctlComboToolbar;
	BOOL	m_bCustomizable;
	BOOL	m_bFlat;
	BOOL	m_bGripper;
	BOOL	m_bList;
	BOOL	m_bSeparator;
	BOOL	m_bText;
	UINT	m_nRows;
	UINT	m_nWidth;
	int		m_nToolbar;
	int		m_nTextType;
	UINT	m_nIndent;
	//}}AFX_DATA
	struct CustomizeToolbar arrCustomize[3];
	int m_nOldToolbar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void GetVars();
	void SetVars();
	void ShowControls();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboToolbar();
	afx_msg void OnCheckText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEDLG_H__166392C2_9CF5_11D1_B475_444553540000__INCLUDED_)
