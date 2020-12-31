#if !defined(_CUSTOMIZECAPTIONDLG_H_)
#define _CUSTOMIZECAPTIONDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeCaptionDlg.h : header file
//

#include "OXColorPickerButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeCaptionDlg dialog

class CCustomizeCaptionDlg : public CDialog
{
// Construction
public:
	CCustomizeCaptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeCaptionDlg)
	enum { IDD = IDD_CUSTOMIZE_CAPTION_PAINTER };
	CEdit	m_ctlEditNumberShade;
	CComboBox	m_ctlComboCaptionState;
	CComboBox	m_ctlComboGradientAlgorithm;
	CComboBox	m_ctlComboGradientAlignment;
	CButton	m_ctlButtonFont;
	COXColorPickerButton	m_ctlButtonBackground;
	BOOL	m_bGradient;
	int		m_nGradientAlgorithm;
	int		m_nGradientAlignment;
	int		m_nCaptionState;
	int		m_nEllipsis;
	int		m_nHorizontalAlignment;
	int		m_nVerticalAlignment;
	CString	m_sFont;
	int		m_nNumberShade;
//	DWORD	m_clrBackground;
	//}}AFX_DATA
	struct CustomizeCaption arrCustomize[2];
	int m_nOldCaptionState;
	COLORREF m_clrBackground;

protected:
	// caption painter
	COXCaptionPainter m_Caption;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeCaptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void GetVars();
	void SetVars();
	void ShowControls();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeCaptionDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckGradient();
	afx_msg void OnButtonTextFont();
	afx_msg void OnSelchangeComboCaption();
	afx_msg void OnButtonBackgroundColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_CUSTOMIZECAPTIONDLG_H_)
