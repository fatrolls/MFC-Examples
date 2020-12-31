// SoundTestDlg.h : header file
//

#ifndef _SOUNDTESTDLG_H_
#define _SOUNDTESTDLG_H_

#include "OXSound.h"

/////////////////////////////////////////////////////////////////////////////
// CSoundTestDlg dialog

class CSoundTestDlg : public CDialog
{
// Construction
public:
	CSoundTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSoundTestDlg)
	enum { IDD = IDD_SOUNDTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;

	COXSound	m_oxSound ;

	void		ShowStatus(LPCTSTR pStatus) ;

	// Generated message map functions
	//{{AFX_MSG(CSoundTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnAsync();
	afx_msg LRESULT OnPlayComplete(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnPlayLoop(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
