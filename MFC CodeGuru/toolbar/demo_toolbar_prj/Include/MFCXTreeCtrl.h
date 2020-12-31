// MFCXTreeCtrl.h : header file
// 
// 1998 Zafir Anjum ( zafir@home.com )
// www.codeguru.com
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author(s) blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#ifndef MFCXTREECTRL__H
#define MFCXTREECTRL__H

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCXTreeCtrl window

class CLASS_EXPORT CMFCXTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMFCXTreeCtrl)

protected:
	const int DRAG_DELAY;

	CImageList  m_image;
	CImageList*	m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM	m_hitemDrag;
	HTREEITEM   m_hitemDrop;
	HTREEITEM   m_pSelected;
	DWORD       m_dwDragStart;
	UINT		m_nTimerID;
	UINT		m_timerticks;
	UINT		m_nMenuID;
	BOOL		m_bParentDrag;

// Construction
public:
	CMFCXTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCXTreeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DisableParentDragging( BOOL bEnable );
	HTREEITEM GetPrevItem( HTREEITEM hItem );
	HTREEITEM GetNextItem( HTREEITEM hItem );
	HTREEITEM GetLastItem( HTREEITEM hItem );
	HTREEITEM CopyBranch( HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST );
	HTREEITEM CopyItem( HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST );
	HTREEITEM AddTreeItem(HTREEITEM hParent, CString strText, HTREEITEM hInsAfter = TVI_LAST, int iImage = 0, BOOL bChildren = TRUE);
	void SetPopupMenuID( UINT uID );
	void EnableDragOperations( BOOL bDrag );
	UINT GetSelectedIcon();
	void SetSelectedIcon( int nIcon );
	void CollapseAll();
	void CollapseBranch( HTREEITEM hTreeItem);
	void ExpandBranch( HTREEITEM hTreeItem );
	void SetTreeStyle( DWORD dwStyle = TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT );
	void CreateImageList( int nID, int nSize, COLORREF crMask );
	virtual BOOL IsFindValid( HTREEITEM );
	virtual HTREEITEM FindItem( CString &str, BOOL bCaseSensitive /*= FALSE */, BOOL bDownDir /*= TRUE */, BOOL bWholeWord /*= FALSE */, HTREEITEM hItem /*= NULL */ );
	virtual void OnItemCopied(HTREEITEM hItem, HTREEITEM hNewItem );
	virtual ~CMFCXTreeCtrl();

	// Generated message map functions
protected:
	BOOL m_bDragEnabled;
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CMFCXTreeCtrl)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
