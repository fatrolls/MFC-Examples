#if !defined(AFX_NETWORKRESOURCESDIALOG_H__33FD9B83_533B_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_NETWORKRESOURCESDIALOG_H__33FD9B83_533B_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NetworkResourcesDialog.h : header file
//

#include "PageDialog.h"
#include "OXNetBrowseTree.h"
#include "OXLayoutManager.h"
#include "OXItemTip.h"
#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CNetworkResourcesDialog dialog

class CNetworkResourcesDialog : public CPageDialog
{
// Construction
public:
	CNetworkResourcesDialog();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetworkResourcesDialog)
	enum { IDD = IDD_NETWORKRESOURCES_DIALOG };
	CSpinButtonCtrl	m_spinMaxLevel;
	CSpinButtonCtrl	m_spinInitialLevel;
	COXSeparator	m_ctlSeparator2;
	COXSeparator	m_ctlSeparator1;
	COXNetBrowseTree	m_treeNetBrowse;
	CListCtrl	m_listDetails;
	CEdit	m_editMaxLevel;
	CEdit	m_editInitialLevel;
	CComboBox	m_cmbResourceScope;
	BOOL	m_bShowComment;
	BOOL	m_bShowDisks;
	BOOL	m_bShowPrinters;
	BOOL	m_bReportErrors;
	int		m_nResourceScope;
	UINT	m_nInitialLevel;
	UINT	m_nMaxLevel;
	//}}AFX_DATA

public:
	virtual BOOL IsRefreshAvailable() { return TRUE; }
	virtual void Refresh();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkResourcesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXLayoutManager m_LayoutManager;
	COXItemTip m_ItemTip;

	virtual void OnInitDialog();

	void SetTreeInitSettings();
	void PopulateDetailsList(const NETRESOURCE* pNetResource);
	void InsertDetailsListItem(int& nIndex, const CString& sName,
		const CString& sValue, const CString& sDescription);
	CString GetScopeName(const NETRESOURCE* pNetResource) const;
	CString GetTypeName(const NETRESOURCE* pNetResource) const;
	CString GetDisplayTypeName(const NETRESOURCE* pNetResource) const;
	CString GetUsageName(const NETRESOURCE* pNetResource) const;


	// Generated message map functions
	//{{AFX_MSG(CNetworkResourcesDialog)
	afx_msg void OnSelchangedResourcesTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKRESOURCESDIALOG_H__33FD9B83_533B_11D2_B475_00E0291A4FD3__INCLUDED_)
