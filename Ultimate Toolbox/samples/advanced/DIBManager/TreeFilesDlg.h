#if !defined(AFX_TREEFILESDLG_H__D2552D20_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_TREEFILESDLG_H__D2552D20_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeFilesDlg.h : header file
//

#include "OXSizeDlgBar.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTreeFilesDlg dialog

class CTreeFilesDlg : public COXSizeDialogBar
{
// Construction
public:
	CTreeFilesDlg(CWnd* pParent = NULL);   // standard constructor

	void AddNewWindowToTree(CWnd* pWnd);
	void RemoveWindowFromTree(CWnd* pWnd);
	void SetTextForWindowInTree(CWnd* pWnd, const CString& string);
	void SetActiveWindowInTree(CWnd* pWnd);

// Dialog Data
	//{{AFX_DATA(CTreeFilesDlg)
	enum { IDD = IDD_DIALOG_TREE_FILES };
	CTreeCtrl	m_TreeFiles;
	//}}AFX_DATA
	// list of images to use in tree control
	CImageList m_ilTypeFile;

	BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeFilesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL IniTreeFiles();
	HTREEITEM FindWindowInTree(CWnd* pWnd);
	void ActivateWindowInTree(DWORD itemData);

	// Generated message map functions
	//{{AFX_MSG(CTreeFilesDlg)
	afx_msg void OnSelchangedTreeFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEFILESDLG_H__D2552D20_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
