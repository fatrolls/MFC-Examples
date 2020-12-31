// FontPickersDlg.h : header file
//

#if !defined(AFX_FONTPICKERSDLG_H__74F10E77_563A_11D3_8B11_0080C8F8F09F__INCLUDED_)
#define AFX_FONTPICKERSDLG_H__74F10E77_563A_11D3_8B11_0080C8F8F09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXFontPickerButton.h"
#include "OXSeparator.h"
#include "OXFontComboBox.h"


/////////////////////////////////////////////////////////////////////////////
// CFontPickersDlg dialog

class CFontPickersDlg : public CDialog
{
// Construction
public:
	CFontPickersDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFontPickersDlg)
	enum { IDD = IDD_FONTPICKERS_DIALOG };
	COXSeparator	m_sepCombo;
	COXSeparator	m_sepButton;
	COXFontComboBox	m_cmbFontPicker;
	COXFontPickerButton	m_btnFontPicker;
	//}}AFX_DATA
	CFont m_font;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontPickersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFontPickersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFontPicker();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTPICKERSDLG_H__74F10E77_563A_11D3_8B11_0080C8F8F09F__INCLUDED_)
