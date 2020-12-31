// ComboExDemoDlg.h : header file
//

#if !defined(AFX_COMBOEXDEMODLG_H__115F4226_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_COMBOEXDEMODLG_H__115F4226_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ComboBoxEx.h"

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoDlg dialog

class CComboExDemoDlg : public CDialog
{
// Construction
public:
	CComboExDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CComboExDemoDlg)
	enum { IDD = IDD_COMBOEXDEMO_DIALOG };
	CComboBoxEx	m_ComboBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboExDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CComboExDemoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOEXDEMODLG_H__115F4226_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
