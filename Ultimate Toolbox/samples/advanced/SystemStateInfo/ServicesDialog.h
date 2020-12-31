#if !defined(AFX_SERVICESDLG_H__FA9CB933_57BC_11D2_A73D_525400DAF3CE__INCLUDED_)
#define AFX_SERVICESDLG_H__FA9CB933_57BC_11D2_A73D_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServicesDialog.h : header file
//

#include "PageDialog.h"
#include "OXTreeCtrl.h"
#include "OXLayoutManager.h"
#include "OXSysInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CServicesDialog dialog

class CServicesDialog : public CPageDialog
{
// Construction
public:
	CServicesDialog();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServicesDialog)
	enum { IDD = IDD_SERVICES_DIALOG };
	CSpinButtonCtrl	m_spinExpandLevel;
	CEdit	m_editExpandLevel;
	COXTreeCtrl	m_tree;
	UINT	m_nExpandLevel;
	int		m_nExpandType;
	//}}AFX_DATA

protected:
	void PopulateTree();
	void ExpandTree(int nExpandLevel=-1, HTREEITEM htiParent=NULL);
	HTREEITEM InsertItem(CString sItem, HTREEITEM htiParent=NULL, int nImage=-1, 
		CFont* pFont=NULL, COLORREF clr=CLR_NONE);
	void InsertServiceInfo(CString sServiceKeyName,	HTREEITEM htiRoot,
		CFont* pFont, BOOL bDevice);

public:
	virtual BOOL IsRefreshAvailable() { return TRUE; }
	virtual void Refresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServicesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ilTree;
	COXLayoutManager m_LayoutManager;
	COXSysInfo m_SysInfo;

protected:
	virtual void OnInitDialog();
	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CServicesDialog)
	afx_msg void OnRadioExpandall();
	afx_msg void OnRadioExpandlevel();
	afx_msg void OnDblclkTreeServices(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICESDLG_H__FA9CB933_57BC_11D2_A73D_525400DAF3CE__INCLUDED_)
