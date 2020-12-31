// ExtendedEditDlg.h : header file
//

#if !defined(AFX_ExtendedEditDlg_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_)
#define AFX_ExtendedEditDlg_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXEdit.h"
#include "OXColorPickerButton.h"
#include "OXFontPickerButton.h"
#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CExtendedEditDlg dialog

class CExtendedEditDlg : public CPropertyPage
{
// Construction
public:
	CExtendedEditDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExtendedEditDlg)
	enum { IDD = IDD_EXTENDEDEDIT_DIALOG };
	COXSeparator	m_sepBottom;
	CComboBox	m_comboMask;
	COXSeparator	m_sepNumericEdit;
	COXSeparator	m_sepControlAppearance;
	COXFontPickerButton	m_btnFont;
	COXEdit	m_edit;
	COXColorPickerButton	m_btnTextColor;
	COXColorPickerButton	m_btnBackColor;
	CString	m_sMask;
	CString	m_sTooltipText;
	//}}AFX_DATA
	COLORREF m_clrBack;
	COLORREF m_clrText;
	CFont m_font;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExtendedEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBackcolor();
	afx_msg void OnButtonTextcolor();
	afx_msg void OnButtonFont();
	afx_msg void OnSelchangeComboMask();
	afx_msg void OnEditchangeComboMask();
	afx_msg void OnChangeEditTooltip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ExtendedEditDlg_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_)
