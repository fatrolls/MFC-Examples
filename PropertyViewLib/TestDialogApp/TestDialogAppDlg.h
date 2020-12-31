// TestDialogAppDlg.h : header file
//

#if !defined(AFX_TESTDIALOGAPPDLG_H__7087D79D_F2A1_4C74_93AD_B9B0C7D299B4__INCLUDED_)
#define AFX_TESTDIALOGAPPDLG_H__7087D79D_F2A1_4C74_93AD_B9B0C7D299B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EPropCtrl.h"
//#include "PropertyViewLib/ETreeCtrl.h"
#include "SomeObject.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDialogAppDlg dialog

class CTestDialogAppDlg : public CDialog , public IPropertyHost
{

//	ETreeCtrl m_TreeCtrl;
	EPropCtrl m_PropCtrl;

	SomeObject0 m_SomeObject0;
	SomeObject1 m_SomeObject1;

// Construction
public:
	CTestDialogAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDialogAppDlg)
	enum { IDD = IDD_TESTDIALOGAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialogAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDialogAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//
	// ITreeListener
	//
//	virtual void TreeNodeSelected( ITreeHost* pHost );

	//
	// ITreeHost
	//
//	virtual void GetTreeChildren( IHostList* pList );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOGAPPDLG_H__7087D79D_F2A1_4C74_93AD_B9B0C7D299B4__INCLUDED_)
