// ExtTreeDemoDlg.h : header file
//

#if !defined(AFX_EXTTREEDEMODLG_H__3049C3C8_BCB8_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_EXTTREEDEMODLG_H__3049C3C8_BCB8_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CExtTreeDemoDlg dialog

class CExtTreeDemoDlg : public CDialog
{
// Construction
public:
	CExtTreeDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CExtTreeDemoDlg();	

// Dialog Data
	//{{AFX_DATA(CExtTreeDemoDlg)
	enum { IDD = IDD_EXTTREEDEMO_DIALOG };
	COXTreeCtrl	m_xlc;
	BOOL	m_bShowColumnHdr;
	BOOL	m_bMultiSel;
	BOOL	m_bEditLabels;
	BOOL	m_bHasButtons;
	BOOL	m_bHasLines;
	BOOL	m_bHasLinesAtRoot;
	BOOL	m_bShowSelAlways;
	BOOL	m_bHasHGrid;
	BOOL	m_bHasVGrid;
	BOOL	m_bRowSel;
	BOOL	m_bFullLength;
	BOOL	m_bPickAnywhere;
	BOOL	m_bItemTips;
	BOOL	m_bNoSortHeader;
	BOOL	m_bNoScroll;
	//}}AFX_DATA
	CImageList m_il1;
	CImageList m_il;
	CImageList m_ils;
	CImageList* m_pDragImage;
	BOOL m_bDragging;
	HTREEITEM m_hDropItem;

protected:
	HTREEITEM m_hHidenItem;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtTreeDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExtTreeDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetdispinfoTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvoxsColumnhdr();
	afx_msg void OnTvoxsMultisel();
	afx_msg void OnTvsEditlabels();
	afx_msg void OnTvsHasbuttons();
	afx_msg void OnTvsHaslines();
	afx_msg void OnTvsHaslinesatroot();
	afx_msg void OnTvsShowselalways();
	afx_msg void OnHide();
	afx_msg void OnUnhideAll();
	afx_msg void OnAddToFocus();
	afx_msg void OnSetFontToSel();
	afx_msg void OnToggleDisable();
	afx_msg void OnVgrid();
	afx_msg void OnHgrid();
	afx_msg void OnRowSel();
	afx_msg void OnFullLength();
	afx_msg void OnPickAnywhere();
	afx_msg void OnBegindragList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvoxsItemtips();
	afx_msg void OnTvoxsNoscroll();
	afx_msg void OnTvoxsNosortheader();
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemExpandingTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteSelected();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTTREEDEMODLG_H__3049C3C8_BCB8_11D1_A3D5_0080C83F712F__INCLUDED_)
