// StatTextDlg.h : header file
//

#if !defined(AFX_STATTEXTDLG_H__A9D60061_542B_11D1_A98F_0000929B340A__INCLUDED_)
#define AFX_STATTEXTDLG_H__A9D60061_542B_11D1_A98F_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXSpinCtrl.h"
#include "OXStaticText.h"

#define IDC_STATICTEXT	WM_USER + 100

/////////////////////////////////////////////////////////////////////////////
// CStatTextDlg dialog

class CStatTextDlg : public CDialog
{
// Construction
public:
	CStatTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStatTextDlg)
	enum { IDD = IDD_STATTEXT_DIALOG };
	COXStaticText m_StaticText;
	CEdit	m_ctlEditGapWidth;
	CEdit	m_ctlEditGapHeight;
	COXSpinCtrl	m_ctlSpinGapWidth;
	COXSpinCtrl	m_ctlSpinGapHeight;
	COXSpinCtrl	m_DirSpin;
	CEdit	m_DirEdit;
	COXSpinCtrl	m_SpeedSpin;
	CEdit	m_SpeedEdit;
	COXSpinCtrl	m_OrientSpin;
	CEdit	m_OrientEdit;
	COXSpinCtrl	m_AngleSpin;
	CEdit	m_AngleEdit;
	int		m_nAngleValue;
	int		m_nOrientValue;
	int		m_nSpeedValue;
	BOOL	m_bScroll;
	int		m_nDirValue;
	int		m_nHorzAlignment;
	int		m_nVertAlignment;
	int		m_nBorderStyle;
	int		m_nGraphicalMode;
	int		m_nGapHeight;
	int		m_nGapWidth;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStatTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeAngleEdit();
	afx_msg void OnChangeOrientEdit();
	afx_msg void OnAdvanRadio();
	afx_msg void OnCompatRadio();
	afx_msg void OnChangeSpeedEdit();
	afx_msg void OnScrollCheck();
	afx_msg void OnChangeDirEdit();
	afx_msg void OnAttrButton();
	afx_msg void OnRestoreButton();
	afx_msg void OnBRaisedRadio();
	afx_msg void OnBStaticRadio();
	afx_msg void OnBDottedRadio();
	afx_msg void OnBNormalRadio();
	afx_msg void OnBClientRadio();
	afx_msg void OnRadioHorzCenter();
	afx_msg void OnRadioHorzLeft();
	afx_msg void OnRadioHorzRight();
	afx_msg void OnRadioVertBottom();
	afx_msg void OnRadioVertCenter();
	afx_msg void OnRadioVertTop();
	afx_msg void OnChangeEditGapHeight();
	afx_msg void OnChangeEditGapWidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATTEXTDLG_H__A9D60061_542B_11D1_A98F_0000929B340A__INCLUDED_)
