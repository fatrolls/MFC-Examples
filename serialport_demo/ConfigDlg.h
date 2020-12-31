/*
**	FILENAME			ConfigDlg.cpp
**
**	PURPOSE				Here the ports can be configured
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
*/


#if !defined(AFX_CONFIGDLG_H__E8DCAF4F_5B32_11D1_94BA_00805A147202__INCLUDED_)
#define AFX_CONFIGDLG_H__E8DCAF4F_5B32_11D1_94BA_00805A147202__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CConfigDlg : public CDialog
{
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	CConfigDlg(CWnd* pParent, DCB dcb);

	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIGDIALOG };
	CString	m_strBaudRate;
	CString	m_strDataBits;
	CString	m_strParity;
	CString	m_strStopBits;
	BOOL	m_CommBreakDetected;
	BOOL	m_CommCTSDetected;
	BOOL	m_CommDSRDetected;
	BOOL	m_CommERRDetected;
	BOOL	m_CommRingDetected;
	BOOL	m_CommRLSDDetected;
	BOOL	m_CommRxchar;
	BOOL	m_CommRxcharFlag;
	BOOL	m_CommTXEmpty;
	CString	m_strSendBuffer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	DCB		m_dcb;

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__E8DCAF4F_5B32_11D1_94BA_00805A147202__INCLUDED_)
