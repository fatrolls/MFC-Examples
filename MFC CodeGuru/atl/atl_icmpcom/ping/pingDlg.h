// pingDlg.h : header file
//

#if !defined(AFX_PINGDLG_H__170A9479_F824_11D1_841C_00A0244DBC26__INCLUDED_)
#define AFX_PINGDLG_H__170A9479_F824_11D1_841C_00A0244DBC26__INCLUDED_

//#include "icmpcom.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "..\\icmpcom.h"
#include "icmpcomevents.h"
/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog

class CPingDlg : public CDialog
{
// Construction
public:

	DWORD m_dwCookie;
	ICMPCom* m_ICMPCom;
	ICMPComEvents* m_ICMPComEvents;
	CPingDlg(CWnd* pParent = NULL);	// standard constructor
	~CPingDlg();	// standard deconstructor

// Dialog Data
	//{{AFX_DATA(CPingDlg)
	enum { IDD = IDD_PING_DIALOG };
	CListBox	m_pingoutlb;
	CString	m_hostname;
	BOOL	m_interrupt;
	BOOL	m_nofrag;
	INT	m_numpackets;
	INT	m_numstamps;
	INT	m_packetlen;
	BOOL	m_resolve;
	INT	m_rrnum;
	INT	m_timeout;
	INT	m_tos;
	BOOL	m_tracert;
	UINT	m_ttl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStarticmp();
	afx_msg void OnStopicmp();
	afx_msg void OnStopping();
	afx_msg void OnRunping();
	afx_msg void OnSetvars();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// ICMPComEvents
	


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINGDLG_H__170A9479_F824_11D1_841C_00A0244DBC26__INCLUDED_)
