// XHtmlTreeTestDlg.h : header file
//

#ifndef XHTMLTREETESTDLG_H
#define XHTMLTREETESTDLG_H

#include "XHtmlTree.h"
#include "XListBox.h"
#include "XGlyphButton.h"
#include "CheckedItemsDialog.h"
#include "XBreadCrumbBar.h"
#include "XColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CXHtmlTreeTestDlg dialog

class CXHtmlTreeTestDlg : public CDialog
{
// Construction
public:
	CXHtmlTreeTestDlg(CWnd* pParent = NULL, int nInput = 0);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXHtmlTreeTestDlg)
	enum { IDD = IDD_XHTMLTREETEST_DIALOG };
	CXColorStatic	m_ScrollSpeed1;
	CXColorStatic	m_ScrollSpeed2;
	CXColorStatic	m_ScrollSpeed3;
	CStatic			m_BreadCrumb;
	CButton			m_ItemInfo;
	CXGlyphButton	m_btnCheckAll;
	CXGlyphButton	m_btnCollapseAll;
	CXGlyphButton	m_btnExpandAll;
	CStatic			m_TreeInfo;
	CStatic			m_ItemImage;
	CStatic			m_HtreeItem;
	CStatic			m_NoChildren;
	CStatic			m_NoSeparators;
	CStatic			m_NoChecked;
	CStatic			m_IsChecked;
	CStatic			m_Expanded;
	CEdit			m_Edit;
	CXListBox		m_List;
	CXHtmlTree		m_Tree;
	BOOL			m_bCheckBoxes;
	BOOL			m_bSmartCheckBoxes;
	BOOL			m_bHtml;
	BOOL			m_bStripHtml;
	BOOL			m_bImages;
	BOOL			m_bReadOnly;
	BOOL			m_bCheckAll;
	BOOL			m_bLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXHtmlTreeTestDlg)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;
	HACCEL		m_hAccel;
	CImageList	m_Images;
	CString		m_strResourceName;
	CString		m_strFind;
	int			m_nInput;
	int			m_nLineNo;
	int			m_nFindStart;
	int			m_nFindDir;
	int			m_nCount;
	CRect		m_rectFind;
	BOOL		m_bFindCheck;
	CPoint		m_ptCheckedItems;
	COLORREF	m_rgbText;
	COLORREF	m_rgbBackground;
	CToolTipCtrl m_ToolTips;
	CCheckedItemsDialog * m_pCheckedItemsDlg;
	CXBreadCrumbBar m_BreadCrumbBar;
	HTREEITEM	m_hTrackItem;

	void CreateTooltips();
	void DumpInfo(HTREEITEM hItem);
	void Find();
	void FindNext();
	void FindPrev();
	void LoadTextFileFromResource(LPCTSTR lpszResource, int nRoot = 0);
	void LoadXmlFileFromResource(LPCTSTR lpszResource);
	void LogRightClick(LPCTSTR lpszMsg, CPoint point);
	void SetBreadCrumbBar(HTREEITEM hItem);
	void UpdateTree(BOOL bReInit);

	// Generated message map functions
	//{{AFX_MSG(CXHtmlTreeTestDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdate();
	afx_msg void OnChangeEdit1();
	afx_msg void OnCollapseAll();
	afx_msg void OnExpandAll();
	afx_msg void OnUpdateTree();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowChecked();
	afx_msg void OnFind();
	afx_msg void OnDisable();
	afx_msg void OnEnable();
	afx_msg void OnSeparator();
	afx_msg void OnDelete();
	afx_msg void OnCheckAll();
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColors();
	afx_msg void OnClose();
	afx_msg void OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnAppCommandSel(WPARAM, LPARAM);
	afx_msg LRESULT OnDisplayTreeToolTip(WPARAM, LPARAM);
	afx_msg LRESULT OnInitTreeToolTip(WPARAM, LPARAM);
	afx_msg LRESULT OnCheckedItemsDialogClosing(WPARAM, LPARAM);
	afx_msg LRESULT OnExpanded(WPARAM, LPARAM);
	afx_msg LRESULT OnCheckbox(WPARAM, LPARAM);
	afx_msg LRESULT OnAppCommand1(WPARAM, LPARAM);
	afx_msg LRESULT OnAppCommand2(WPARAM, LPARAM);
#ifdef XHTMLDRAGDROP
	afx_msg LRESULT OnScrollSpeed(WPARAM, LPARAM);
	afx_msg LRESULT OnBeginDrag(WPARAM, LPARAM);
	afx_msg LRESULT OnEndDrag(WPARAM, LPARAM);
	afx_msg LRESULT OnDropHover(WPARAM, LPARAM);
#endif // XHTMLDRAGDROP

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XHTMLTREETESTDLG_H
