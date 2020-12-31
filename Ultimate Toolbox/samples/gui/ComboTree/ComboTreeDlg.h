// ComboTreeDlg.h : header file
//

#if !defined(AFX_COMBOTREEDLG_H__10B74B00_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_)
#define AFX_COMBOTREEDLG_H__10B74B00_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_

#include "..\..\..\INCLUDE\OXComboPickerCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FolderTree.h"
#include "..\..\..\INCLUDE\OXTreeCtrl.h"	// Added by ClassView
#include "ComboOXTree.h"

/////////////////////////////////////////////////////////////////////////////
// CMulticolumnTree
 
class CMulticolumnTree : public COXTreeComboDropDown<COXTreeCtrl>  
{
public:
 virtual CRect GetBestRect()
	{
	 CRect rect=COXTreeComboDropDown<COXTreeCtrl>::GetBestRect();
 
	 int nWidth=0;
	 for(int nIndex=0; nIndex<GetColumnsCount(); nIndex++)
	 {
	  nWidth+=GetColumnWidth(nIndex);
	 }
	 if(rect.Width()<nWidth)
	 {
	  rect.right=rect.left+nWidth;
	 }
 
	 return rect;
	}
};
 
/////////////////////////////////////////////////////////////////////////////
// CComboTreeDlg dialog

class CComboTreeDlg : public CDialog
{
// Construction
public:
	void InitializeControls();
	CComboTreeDlg(CWnd* pParent = NULL);	// standard constructor
	~CComboTreeDlg();
// Dialog Data
	//{{AFX_DATA(CComboTreeDlg)
	enum { IDD = IDD_COMBOTREE_DIALOG };
	CEdit	m_edtmasked;
	UINT	m_nOXTreeHeight;
	UINT	m_nOXTreeWidth;
	UINT	m_nShellHeight;
	UINT	m_nShellWidth;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXComboPickerCtrl m_pckOXTree;
	CMulticolumnTree m_cmbOXTree;
	CImageList m_imgList;
	COXComboPickerCtrl m_pckShell;
	CFolderTree m_cmbShell;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComboTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTREEDLG_H__10B74B00_15F6_11D4_AD12_0050BAAB46B1__INCLUDED_)
