// GridCtrlDemoDlg.h : header file
//

#if !defined(AFX_GRIDCTRLDEMODLG_H__7E2ABF76_017B_11D2_AB4A_5C7377000000__INCLUDED_)
#define AFX_GRIDCTRLDEMODLG_H__7E2ABF76_017B_11D2_AB4A_5C7377000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ComboGridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

class CGridCtrlDemoDlg : public CDialog
{
// Construction
public:
	CGridCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGridCtrlDemoDlg)
	enum { IDD = IDD_GRIDCTRLDEMO_DIALOG };
	//}}AFX_DATA
    CComboGridCtrl m_GridCtrl;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLDEMODLG_H__7E2ABF76_017B_11D2_AB4A_5C7377000000__INCLUDED_)
