// ColorPickerButtonDlg.h : header file
//

#if !defined(AFX_COLORPICKERBUTTONDLG_H__875CC119_F4B4_11D1_8862_0080C83F712F__INCLUDED_)
#define AFX_COLORPICKERBUTTONDLG_H__875CC119_F4B4_11D1_8862_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButtonDlg dialog

#include "OXColorPickerButton.h"

class CColorPickerButtonDlg : public CDialog
{
// Construction
public:
	CColorPickerButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorPickerButtonDlg)
	enum { IDD = IDD_COLORPICKERBUTTON_DIALOG };
	CComboBox	m_comboNumColors;
	COXColorPickerButton	m_btnColorPicker;
	CEdit	m_ctlTooltip;
	CButton	m_btnSetTooltip;
	CString	m_sTooltip;
	CString	m_sText;
	int		m_nArrowStyle;
	int		m_nButtonAlignment;
	BOOL	m_bAutoResize;
	BOOL	m_bDisable;
	BOOL	m_bHyperlook;
	BOOL	m_bImage;
	BOOL	m_bMultiline;
	BOOL	m_bTooltip;
	BOOL	m_bTracklook;
	int		m_nNumColors;
	//}}AFX_DATA
	COLORREF m_clr;
	CSize m_originalSize;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPickerButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// array of tooltip - color pairs for 20 standard colors
	static ButtonToolTipIDTable m_arrStandardColorsTooltips[];

	CRect m_rectTop;
	CRect m_rectBottom;

	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CColorPickerButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFontcolor();
	afx_msg void OnButtonSettext();
	afx_msg void OnButtonSettooltip();
	afx_msg void OnCheckAutoresize();
	afx_msg void OnCheckDisabled();
	afx_msg void OnCheckHyperlook();
	afx_msg void OnCheckImage();
	afx_msg void OnCheckMultiline();
	afx_msg void OnCheckTooltip();
	afx_msg void OnCheckTracklook();
	afx_msg void OnRadioArrow();
	afx_msg void OnRadioButtonAlignment();
	afx_msg void OnSelchangeComboNumcolors();
	afx_msg void OnButtonColorPicker();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKERBUTTONDLG_H__875CC119_F4B4_11D1_8862_0080C83F712F__INCLUDED_)
