// MultiComboDlg.h : header file
//

#if !defined(AFX_MULTICOMBODLG_H__9FAE7789_723F_11D1_AEBB_00A0240D05AF__INCLUDED_)
#define AFX_MULTICOMBODLG_H__9FAE7789_723F_11D1_AEBB_00A0240D05AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "jcombo.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiComboDlg dialog

class CMultiComboDlg : public CDialog
{
// Construction
public:
	void InitJCombo();
	CMultiComboDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiComboDlg)
	enum { IDD = IDD_MULTICOMBO_DIALOG };
	CJCombo	m_combo3;
	CJCombo	m_combo2;
	CJCombo	m_combo1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMultiComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelendokCombo3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTICOMBODLG_H__9FAE7789_723F_11D1_AEBB_00A0240D05AF__INCLUDED_)
