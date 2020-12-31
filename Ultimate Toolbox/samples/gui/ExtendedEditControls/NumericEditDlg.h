// NumericEditDlg.h : header file
//

#if !defined(AFX_NUMERICEDITDLG_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_)
#define AFX_NUMERICEDITDLG_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXEdit.h"
#include "OXColorPickerButton.h"
#include "OXFontPickerButton.h"
#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CNumericEditDlg dialog

class CNumericEditDlg : public CPropertyPage
{
// Construction
public:
	CNumericEditDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNumericEditDlg)
	enum { IDD = IDD_NUMERICEDIT_DIALOG };
	COXSeparator	m_sepBottom;
	CComboBox	m_comboNegativeFormat;
	CComboBox	m_comboGroupSeparator;
	CComboBox	m_comboDecimalSeparator;
	CComboBox	m_comboMask;
	CComboBox	m_comboGroupLength;
	CComboBox	m_comboDecimalCount;
	COXSeparator	m_sepNumericEdit;
	COXSeparator	m_sepNumericEditSettings;
	COXSeparator	m_sepControlAppearance;
	COXColorPickerButton	m_btnTextColorNegative;
	COXFontPickerButton	m_btnFont;
	COXNumericEdit	m_edit;
	COXColorPickerButton	m_btnTextColor;
	COXColorPickerButton	m_btnBackColor;
	BOOL	m_bLeadingZero;
	BOOL	m_bIndefiniteDecimalDigitCount;
	BOOL	m_bNoDiditInGroup;
	CString	m_sDecimalSeparator;
	CString	m_sGroupSeparator;
	CString	m_sNegativeValueFormat;
	int		m_nDecimalDigitCount;
	int		m_nFractionalDigitCount;
	int		m_nGroupLength;
	CString	m_sMask;
	//}}AFX_DATA
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrTextNegative;
	CFont m_font;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumericEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNumericEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBackcolor();
	afx_msg void OnButtonTextcolor();
	afx_msg void OnButtonFont();
	afx_msg void OnButtonTextcolorNegative();
	afx_msg void OnCheckDecimalDigitCountIndefinite();
	afx_msg void OnCheckNoGroup();
	afx_msg void OnEditchangeComboMask();
	afx_msg void OnSelchangeComboMask();
	afx_msg void OnCheckLeadingZero();
	afx_msg void OnSelchangeComboDecimalDigitCount();
	afx_msg void OnEditchangeComboDecimalSeparator();
	afx_msg void OnSelchangeComboDecimalSeparator();
	afx_msg void OnSelchangeComboFractionalDigitCount();
	afx_msg void OnSelchangeComboGroupLength();
	afx_msg void OnEditchangeComboGroupSeparator();
	afx_msg void OnSelchangeComboGroupSeparator();
	afx_msg void OnEditchangeComboNegativeValueFormat();
	afx_msg void OnSelchangeComboNegativeValueFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMERICEDITDLG_H__368B4776_AA35_11D2_A7AA_525400DAF3CE__INCLUDED_)
