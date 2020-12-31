// CTestProgressBarDlg.h : header file
//

#if !defined(AFX_CTESTPROGRESSBARDLG_H__35E926A6_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_)
#define AFX_CTESTPROGRESSBARDLG_H__35E926A6_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// The custom progress control
#include "GradientProgressCtrl.h"

// The color picker
#include "ColourPicker.h"

/////////////////////////////////////////////////////////////////////////////
// CCTestProgressBarDlg dialog

class CCTestProgressBarDlg : public CDialog
{
// Construction
public:
	CCTestProgressBarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCTestProgressBarDlg)
	enum { IDD = IDD_CTESTPROGRESSBAR_DIALOG };
	CColourPicker	m_cClrText;
	CColourPicker	m_cClrStart;
	CColourPicker	m_cClrEnd;
	CColourPicker	m_cClrBkGnd;
	CGradientProgressCtrl	m_cProgress;
	UINT	m_nRange;
	BOOL	m_bShowPercent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTestProgressBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COLORREF m_clrText, m_clrBk, m_clrStart, m_clrEnd;

	// Generated message map functions
	//{{AFX_MSG(CCTestProgressBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTESTPROGRESSBARDLG_H__35E926A6_EBE7_11D1_9871_C5E6F2F2B45F__INCLUDED_)
