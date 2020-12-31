// RegEventDlg.h : header file
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#if !defined(AFX_REGEVENTDLG_H__8CB72082_D8EC_11D0_A21F_0000929B340A__INCLUDED_)
#define AFX_REGEVENTDLG_H__8CB72082_D8EC_11D0_A21F_0000929B340A__INCLUDED_

#include "OXRegistryWatcher.h"	// Added by ClassView
#include "RemBttn.h"
#include <afxtempl.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRegEventDlg dialog

class CRegEventDlg : public CDialog
{
// Construction
public:
	CMap<DWORD, DWORD&, CString, CString&> m_MesMap;

	// The single COXRegistryWatcher object. It watches for Registry changes.
	COXRegistryWatcher m_RegWatch;

	CRegEventDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegEventDlg)
	enum { IDD = IDD_REGEVENT_DIALOG };
	CButton	m_AddBttn;
	CButton	m_ClrBttn;
	CRemBttn	m_RemBttn;
	CButton	m_RemAllBttn;
	CListCtrl	m_ChangeList;
	CListCtrl	m_KeyList;
	CString	m_HkeyStr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegEventDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegEventDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClickKeylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusKeylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRembttn();
	afx_msg void OnRemallbttn();
	afx_msg void OnClrbttn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEVENTDLG_H__8CB72082_D8EC_11D0_A21F_0000929B340A__INCLUDED_)
