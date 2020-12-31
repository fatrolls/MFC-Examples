#if !defined(AFX_SYSINFODIALOG_H__266F38B4_4D6E_11D2_A730_525400DAF3CE__INCLUDED_)
#define AFX_SYSINFODIALOG_H__266F38B4_4D6E_11D2_A730_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SysInfoDialog.h : header file
//

#include "PageDialog.h"
#include "OXTreeCtrl.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CSysInfoDialog dialog

class CSysInfoDialog : public CPageDialog
{
// Construction
public:
	CSysInfoDialog();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysInfoDialog)
	enum { IDD = IDD_SYSINFO_DIALOG };
	CSpinButtonCtrl	m_spinExpandLevel;
	CEdit	m_editExpandLevel;
	COXTreeCtrl	m_tree;
	UINT	m_nExpandLevel;
	int		m_nExpandType;
	BOOL	m_bShowPrinters;
	//}}AFX_DATA

protected:
	void PopulateTree();
	void ExpandTree(int nExpandLevel=-1, HTREEITEM htiParent=NULL);
	HTREEITEM InsertItem(CString sItem, HTREEITEM htiParent=NULL, int nImage=-1, 
		CFont* pFont=NULL, COLORREF clr=CLR_NONE);

public:
	virtual BOOL IsRefreshAvailable() { return TRUE; }
	virtual void Refresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ilTree;
	COXLayoutManager m_LayoutManager;

protected:
	virtual void OnInitDialog();

	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CSysInfoDialog)
	afx_msg void OnRadioExpandall();
	afx_msg void OnRadioExpandlevel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFODIALOG_H__266F38B4_4D6E_11D2_A730_525400DAF3CE__INCLUDED_)
