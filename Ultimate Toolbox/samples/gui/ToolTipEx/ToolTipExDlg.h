// ToolTipExDlg.h : header file
//

#if !defined(AFX_TOOLTIPEXDLG_H__7FF81957_1C44_11D2_965C_00A0C9668BF9__INCLUDED_)
#define AFX_TOOLTIPEXDLG_H__7FF81957_1C44_11D2_965C_00A0C9668BF9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CToolTipExDlg dialog
#include "Resource.h"
#include "OXToolTipCtrl.h"
#include "OXSeparator.h"
#include "OXColorPickerButton.h"
#include "OXFontPickerButton.h"

class CToolTipExDlg : public CDialog
{
// Construction
public:
	CToolTipExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolTipExDlg)
	enum { IDD = IDD_TOOLTIPEX_DIALOG };
	CTreeCtrl	m_tree;
	COXSeparator	m_sepSamples;
	COXSeparator	m_sepCustomize;
	COXColorPickerButton	m_btnBkColor;
	COXFontPickerButton	m_btnTextFontColor;
	CListBox	m_ListBox;
	BOOL	m_bBoldTips;
	BOOL	m_bSetMaxWidth;
	UINT	m_nMaxWidth;
	//}}AFX_DATA
	COLORREF m_clrBackground;
	COLORREF m_clrText;
	CFont m_font;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CToolTipExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonColorBackground();
	afx_msg void OnButtonTextFontColor();
	afx_msg void OnCheckSetMaxWidth();
	afx_msg void OnChangeEditMaxWidth();
	//}}AFX_MSG
    BOOL OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	DECLARE_MESSAGE_MAP()

protected:
	COXToolTipCtrl m_toolTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPEXDLG_H__7FF81957_1C44_11D2_965C_00A0C9668BF9__INCLUDED_)
