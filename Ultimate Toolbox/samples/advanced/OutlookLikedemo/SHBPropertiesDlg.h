#if !defined(AFX_SHBPROPERTIESDLG_H__BAAEE534_09DB_11D2_887D_0080C83F712F__INCLUDED_)
#define AFX_SHBPROPERTIESDLG_H__BAAEE534_09DB_11D2_887D_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SHBPropertiesDlg.h : header file
//

#include "OXColorPickerButton.h"
#include "OXStatic.h"
#include "OXShortcutBar.h"

/////////////////////////////////////////////////////////////////////////////
// CSHBPropertiesDlg dialog

class CSHBPropertiesDlg : public CDialog
{
// Construction
public:
	CSHBPropertiesDlg(COXShortcutBar* pShortcutBar, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CSHBPropertiesDlg)
	enum { IDD = IDD_SHBPROPERTIES_DIALOG };
	COXStatic	m_ctlNameTextFont;
	COXStatic	m_ctlNameHeaderFont;
	COXColorPickerButton	m_btnHeaderClrBack;
	COXColorPickerButton	m_btnClrBack;
	BOOL	m_bApplyOnlyToExpanded;
	int		m_nBottomMargin;
	int		m_nGroupMargin;
	int		m_nRightMargin;
	int		m_nLeftMargin;
	UINT	m_nScrollBtnHeight;
	UINT	m_nScrollBtnWidth;
	int		m_nTopMargin;
	CString	m_sNameTextFont;
	CString	m_sNameHeaderFont;
	int		m_nHeaderHeight;
	//}}AFX_DATA
	COLORREF m_clrBackground;
	COLORREF m_clrHeaderBackground;
	COLORREF m_clrText;
	COLORREF m_clrHeaderText;
	LOGFONT m_lfText;
	LOGFONT m_lfHeader;

protected:
	COXShortcutBar* m_pShortcutBar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHBPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void GetVars();
	void SetVars();
	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CSHBPropertiesDlg)
	afx_msg void OnHdrfont();
	afx_msg void OnTextfont();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHBPROPERTIESDLG_H__BAAEE534_09DB_11D2_887D_0080C83F712F__INCLUDED_)
