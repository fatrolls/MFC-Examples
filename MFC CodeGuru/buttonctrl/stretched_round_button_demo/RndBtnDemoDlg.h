// RndBtnDemoDlg.h : header file
//

#if !defined(AFX_RNDBTNDEMODLG_H__52541706_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_RNDBTNDEMODLG_H__52541706_59CF_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "RoundButton.h"


/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoDlg dialog

class CRndBtnDemoDlg : public CDialog
{
// Construction
public:
	CRndBtnDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRndBtnDemoDlg)
	enum { IDD = IDD_RNDBTNDEMO_DIALOG };
	//}}AFX_DATA
	CRoundButton m_Button1, m_Button2, m_Button3, m_Button4, m_Button5, m_Button6, m_Button7;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRndBtnDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRndBtnDemoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RNDBTNDEMODLG_H__52541706_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
