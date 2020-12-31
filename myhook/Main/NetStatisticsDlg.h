#if !defined(AFX_NETSTATISTICSDLG_H__E7B05AF9_B028_4A03_BFC5_962B13B9534B__INCLUDED_)
#define AFX_NETSTATISTICSDLG_H__E7B05AF9_B028_4A03_BFC5_962B13B9534B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetStatisticsDlg.h : header file
//

#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CNetStatisticsDlg dialog


class CNetStatisticsDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CNetStatisticsDlg)
// Construction
public:
	CNetStatisticsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetStatisticsDlg)
	enum { IDD = IDD_NET_STATISTICS_DLG };
	CBCGPMenuButton	m_btnFunction;
	CStatic	m_wndType;
	CStatic	m_wndPlace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetStatisticsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetStatisticsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFunction();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBCGPProp* AddGroupProp(CString strName, CBCGPProp* pParent = NULL);
	void AddChildProp(CString strName, CString strValue, CBCGPProp* pParent = NULL);
	void GetUdpStatistics();
	void GetTcpStatistics();
	void GetIcmpStatistics();
	void GetIpStatistics();

	CBCGPPropList m_wndPropList;
	CMenu menu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSTATISTICSDLG_H__E7B05AF9_B028_4A03_BFC5_962B13B9534B__INCLUDED_)
