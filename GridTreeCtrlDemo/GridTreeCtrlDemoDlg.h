/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GRIDTREECTRLDEMODLG_H__A2C6C2C6_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_)
#define AFX_GRIDTREECTRLDEMODLG_H__A2C6C2C6_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// This macro evaluates to the number of elements in an array -- from Jeff Richter
#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))

#include "GRIDCTRL_SRC\GridCtrl.h"
#include "TreeColumn_src\TreeColumn.h"
#include "GridBtnCell_src\BtnDataBase.h"
#include "DlgOptions.h"

/////////////////////////////////////////////////////////////////////////////
// CGridTreeCtrlDemoDlg dialog

class CGridTreeCtrlDemoDlg : public CDialog
{
// Construction
public:
	CGridTreeCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

    void ChangeImages( TREE_IMAGE aTreeImage); // TREE_IMAGE
    TREE_IMAGE GetCurrentImages() const { return m_TreeImage; };

    void SetTreeLines( BOOL abShowTreeLines);   // T=show tree lines
    BOOL GetTreeLines() const;

// Dialog Data
private:
	//{{AFX_DATA(CGridTreeCtrlDemoDlg)
	enum { IDD = IDD_GRIDTREECTRLDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridTreeCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CImageList m_ImageList;

    CGridCtrl m_Grid;

    CTreeColumn m_TreeColumn;   // grid with tree column
    CBtnDataBase m_BtnDataBase; // grid with some cells with buttons / controls
    TREE_IMAGE m_TreeImage;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGridTreeCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOptions();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnPrint();
	afx_msg void OnButtonBranchDelete();
	afx_msg void OnButtonBranchInsert();
	//}}AFX_MSG
    afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDTREECTRLDEMODLG_H__A2C6C2C6_EBD7_11D3_B75D_00C04F6A7AE6__INCLUDED_)
