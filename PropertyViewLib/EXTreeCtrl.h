#ifndef EXTREECTRL_H
#define EXTREECTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EXMenu.h"
#include "EXWaitingTreeCtrl.h"
#include <list>

class IXTreeItem;

class EXTreeCtrl : public EXWaitingTreeCtrl
{

protected:

	bool BuildTreePath( IXTreeItem* pNode , std::list<IXTreeItem*>& List , IXTreeItem* pParent );

	DECLARE_DYNAMIC(EXTreeCtrl)

public:



	class ITreeListener
	{
	public:	
		virtual void	TreeNodeSelected(IXTreeItem *pTreeItem)						{}
	};

public:

	EXTreeCtrl();

	void InitTree( IXTreeItem* pRoot , int nIconsBitmap );

protected:

	CImageList *m_pIconImageList;

	// Drag'n'drop
	CImageList*	m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM	m_hitemDrag,m_hitemDrop;
	
	// 
	IXTreeItem*	m_pRootMember;
	HTREEITEM m_hActiveItem;
	bool m_bContextMenuActivated;
	ITreeListener* m_pTreeListener;

// Operations
public:
	bool m_bDontSend;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EXTreeCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	IXTreeItem* GetSelectedTreeItem(void);

	void RefreshDataItem(IXTreeItem *pITreeMember);
	void SelectDataItem(IXTreeItem *pITreeMember);
	void Moveup();
	void Movedown();
	void ExpandTree(HTREEITEM hItem = NULL,bool bIncludeSub=false);
	void OnViewRefresh();
	void SetRootMember(IXTreeItem *pRootMember);
	virtual BOOL PopulateItem(HTREEITEM hParent);
	virtual ~EXTreeCtrl();

	void SetTreeListener(ITreeListener *pTreeListener)
	{
		m_pTreeListener = pTreeListener;
	}

	HTREEITEM FindItemInSubTree(HTREEITEM hti, IXTreeItem *pITreeItem);

protected:

//	bool m_bSelectionWasInitializedByMyself;

	IXTreeItem* h2p(HTREEITEM h);
	LRESULT CopyTreeNodes( HTREEITEM srcitem, HTREEITEM destparent );

	HTREEITEM CopyBranch( HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST );
	HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter);
	
//	EBaseItem* GetBaseItem(HTREEITEM hTi = 0);
//	LRESULT SendUpdate(UINT nMessage, LPARAM nID);
	HTREEITEM FindItem(HTREEITEM hti, HTREEITEM hItem);
	void AddItem(HTREEITEM hParent, IXTreeItem *pITreeItem);
	bool InsertItems(HTREEITEM hParent, IXTreeItem *pParentTreeItem);

	//{{AFX_MSG(EXTreeCtrl)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTREECTRL_H__5742B942_083A_4243_962D_28C2E98A145B__INCLUDED_)
