// ShortcutBarDlg.h : header file
//

#if !defined(AFX_SHORTCUTBARDLG_H__427CC91A_FEDC_11D1_8872_0080C83F712F__INCLUDED_)
#define AFX_SHORTCUTBARDLG_H__427CC91A_FEDC_11D1_8872_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXShortcutBar.h"
#include "OXLayoutManager.h"
#include "UTB64Bit.h"

#define IDC_TREE					1000
#define	SHB_IDMPROPERTIES			SHB_IDMUSER+1

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarDlg dialog

class CShortcutBarDlg : public CDialog
{
// Construction
public:
	CShortcutBarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShortcutBarDlg)
	enum { IDD = IDD_SHORTCUTBAR_DIALOG };
	COXShortcutBar	m_ctlShortcutBar;
	BOOL	m_bAutoScroll;
	BOOL	m_bBoldExpandedGroup;
	CString	m_sDescription;
	BOOL	m_bDisableDragDropHeader;
	BOOL	m_bEditHeaders;
	BOOL	m_bEditItems;
	BOOL	m_bHandleNotifications;
	BOOL	m_bInfoTip;
	int		m_nSorting;
	BOOL	m_bNoScroll;
	BOOL	m_bShowActiveAlways;
	BOOL	m_bUnderlineHotItem;
	BOOL	m_bAnimateExpand;
	BOOL	m_bAutoExpand;
	BOOL	m_bDrawHeaderDragImage;
	BOOL	m_bDrawItemDragImage;
	BOOL	m_bDisableDragItem;
	BOOL	m_bDisableDropItem;
	//}}AFX_DATA
	CImageList m_ilLarge;
	CImageList m_ilSmall;

	CTreeCtrl m_tree;
	CImageList m_ilTree;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COXLayoutManager m_LayoutManager;

	BOOL m_bItemDroped;
	DWORD_PTR m_dwDropedItemData;

	void InitShortcutBar();
	void GetVars();
	void ShowControls();

	// Generated message map functions
	//{{AFX_MSG(CShortcutBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAscending();
	afx_msg void OnAutoscroll();
	afx_msg void OnBoldexpandedgroup();
	afx_msg void OnDescending();
	afx_msg void OnDisableddragdropheader();
	afx_msg void OnEditheaders();
	afx_msg void OnEdititems();
	afx_msg void OnHandlenotifications();
	afx_msg void OnInfotip();
	afx_msg void OnNoSort();
	afx_msg void OnNoscroll();
	afx_msg void OnShowactivealways();
	afx_msg void OnUnderlinehotitem();
	afx_msg void OnAutoexpand();
	afx_msg void OnAnimateexpand();
	afx_msg void OnDrawitemdragimage();
	afx_msg void OnDrawheaderdragimage();
	afx_msg void OnDisabledragitem();
	afx_msg void OnDisabledropitem();
	//}}AFX_MSG

	afx_msg void OnBeginDragHeader(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnBeginHeaderEdit(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDeleteGroup(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnEndHeaderEdit(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnGetHeaderInfoTip(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnGroupExpanded(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnGroupExpanding(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDrawHeader(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDropGroup(NMHDR* pNotifyStruct, LRESULT* result);

	afx_msg void OnBeginDragItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnBeginItemEdit(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDeleteItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDeleteAllItems(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnEndItemEdit(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnGetItemInfoTip(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnInsertItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnSelectItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnActivateItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnHotItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDrawItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDropItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnEndDragDropItem(NMHDR* pNotifyStruct, LRESULT* result);

	afx_msg void OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* result);

	afx_msg void OnSHBProperties();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTBARDLG_H__427CC91A_FEDC_11D1_8872_0080C83F712F__INCLUDED_)
