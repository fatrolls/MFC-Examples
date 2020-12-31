// ExtendedTreeControlDlg.h : header file
//

#if !defined(AFX_EXTENDEDTREECONTROLDLG_H__0B6AD6BE_901E_4D6C_9159_4DEABF9218AA__INCLUDED_)
#define AFX_EXTENDEDTREECONTROLDLG_H__0B6AD6BE_901E_4D6C_9159_4DEABF9218AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXTreeCtrl.h"
#include "OXSeparator.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CExtendedTreeControlDlg dialog

class CExtendedTreeControlDlg : public CDialog
{
// Construction
public:
	CExtendedTreeControlDlg(CWnd* pParent = NULL);	// standard constructor
	virtual	~CExtendedTreeControlDlg();   // destructor

// Dialog Data
	//{{AFX_DATA(CExtendedTreeControlDlg)
	enum { IDD = IDD_EXTENDEDTREECONTROL_DIALOG };
	COXSeparator	m_sepExtendedStyle;
	COXSeparator	m_sepBasicStyles;
	COXTreeCtrl	m_xlc;
	BOOL	m_bMultiSel;
	BOOL	m_bHasButtons;
	BOOL	m_bHasLines;
	BOOL	m_bHasLinesAtRoot;
	BOOL	m_bShowSelAlways;
	BOOL	m_bHasGrid;
	BOOL	m_bRowSel;
	BOOL	m_bItemTips;
	BOOL	m_bNoSortHeader;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedTreeControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXLayoutManager m_LayoutManager;
	HICON m_hIcon;
	HTREEITEM m_hHidenItem;
	CImageList m_il;
	CImageList* m_pDragImage;
	BOOL m_bDragging;
	HTREEITEM m_hDropItem;

	void InsertItems();

	// Generated message map functions
	//{{AFX_MSG(CExtendedTreeControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTvoxsMultisel();
	afx_msg void OnTvsHasbuttons();
	afx_msg void OnTvsHaslines();
	afx_msg void OnTvsHaslinesatroot();
	afx_msg void OnTvsShowselalways();
	afx_msg void OnHide();
	afx_msg void OnUnhideAll();
	afx_msg void OnSetFontToSel();
	afx_msg void OnToggleDisable();
	afx_msg void OnGrid();
	afx_msg void OnRowSel();
	afx_msg void OnBegindragExtendedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTvoxsItemtips();
	afx_msg void OnTvoxsNosortheader();
	afx_msg void OnDestroy();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDTREECONTROLDLG_H__0B6AD6BE_901E_4D6C_9159_4DEABF9218AA__INCLUDED_)
