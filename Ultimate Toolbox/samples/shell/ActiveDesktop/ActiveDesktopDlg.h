// ActiveDesktopDlg.h : header file
//

#if !defined(AFX_ACTIVEDESKTOPDLG_H__CD16C205_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_)
#define AFX_ACTIVEDESKTOPDLG_H__CD16C205_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_

#include "OXActiveDesktop.h"	// Added by ClassView
#include "CompDialog.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopDlg dialog

class CActiveDesktopDlg : public CDialog
{
// Construction
public:
	BOOL m_bRemoveEnabled;
	BOOL m_bEditEnabled;
	void ApplyChanges();
	CCompDialog m_dlgComp;
	void UpdatePattern();
	BOOL Init();
	COXActiveDesktop m_desktop;
	CActiveDesktopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveDesktopDlg)
	enum { IDD = IDD_ACTIVEDESKTOP_DIALOG };
	CButton	m_btnOK;
	CStatic	m_stcPattern;
	CListCtrl	m_lstMain;
	CEdit	m_edtWallpaper;
	CButton	m_btnRemove;
	CButton	m_btnEdit;
	CButton	m_btnApply;
	BOOL	m_bComps;
	BOOL	m_bDesktop;
	CBitmap m_bitmap;
	int		m_nWOpt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveDesktopDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BYTE	m_bmp[512];
	BYTE m_pattern[8];

	// Generated message map functions
	//{{AFX_MSG(CActiveDesktopDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckDesktop();
	afx_msg void OnCheckComps();
	afx_msg void OnApply();
	afx_msg void OnEdit();
	afx_msg void OnNew();
	afx_msg void OnRemove();
	afx_msg void OnItemchangedListMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStaticPattern();
	virtual void OnOK();
	afx_msg void OnRefresh();
	afx_msg void OnChangeEditWallpaper();
	afx_msg void OnSelchangeComboWopt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEDESKTOPDLG_H__CD16C205_EDE3_11D3_ACB6_0050BAAB46B1__INCLUDED_)
