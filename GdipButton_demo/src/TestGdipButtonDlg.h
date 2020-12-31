// TestGdipButtonDlg.h : header file
//

#if !defined(AFX_TESTGDIPBUTTONDLG_H__B2D9DC86_9992_4E23_9E86_45CD32E6F352__INCLUDED_)
#define AFX_TESTGDIPBUTTONDLG_H__B2D9DC86_9992_4E23_9E86_45CD32E6F352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GdipButton.h"

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonDlg dialog

class CTestGdipButtonDlg : public CDialog
{
// Construction
public:
	void SetButtonBackGrounds(CDC* pDC);
	CTestGdipButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestGdipButtonDlg)
	enum { IDD = IDD_TESTGDIPBUTTON_DIALOG };
	CGdipButton	m_cGear;
	CGdipButton	m_cPlayHi;
	CGdipButton	m_cPlayDis;
	CGdipButton	m_cShutDn;
	CGdipButton	m_cPlay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGdipButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	HBITMAP m_hBitmap;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestGdipButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShutdn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGDIPBUTTONDLG_H__B2D9DC86_9992_4E23_9E86_45CD32E6F352__INCLUDED_)
