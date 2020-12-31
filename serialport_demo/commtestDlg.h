/*
**	FILENAME			CommTestDlg.h
**
**	PURPOSE				This is the dialog that shows the comm activity.
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
*/

#if !defined(AFX_COMMTESTDLG_H__4FDAC186_34B5_11D1_9481_00805A147202__INCLUDED_)
#define AFX_COMMTESTDLG_H__4FDAC186_34B5_11D1_9481_00805A147202__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ColorStatic.h"
#include "SerialPort.h"

class CCommtestDlg : public CDialog
{

public:
	CCommtestDlg(CWnd* pParent = NULL);	// standard constructor

	//{{AFX_DATA(CCommtestDlg)
	enum { IDD = IDD_COMMTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommtestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON			m_hIcon;
	CListBox		m_ListBox[4];
	CEdit			m_Edit[4];
	CSerialPort		m_Ports[4];
	CString			m_strReceived[4];

	// Generated message map functions
	//{{AFX_MSG(CCommtestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendButton1();
	afx_msg void OnSendButton2();
	afx_msg void OnSendButton3();
	afx_msg void OnSendButton4();
	afx_msg LONG OnCommunication(UINT, LONG);
	afx_msg LONG OnCTSDetected(UINT, LONG);
	afx_msg void OnClearButton1();
	afx_msg void OnClearButton2();
	afx_msg void OnClearButton3();
	afx_msg void OnClearButton4();
	afx_msg void OnConfigbutton1();
	afx_msg void OnConfigbutton2();
	afx_msg void OnConfigbutton3();
	afx_msg void OnConfigbutton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMTESTDLG_H__4FDAC186_34B5_11D1_9481_00805A147202__INCLUDED_)
