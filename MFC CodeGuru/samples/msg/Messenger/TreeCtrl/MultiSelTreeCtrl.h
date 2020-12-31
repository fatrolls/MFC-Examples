///////////////////////////////////////////////////////////////////////////////
// 
// CMultiSelTreeCtrl - Multiple selection tree control (MFC 4.2)
// 
// Bendik Engebretsen (c) 1997 
// bendik@techsoft.no
// http://www.techsoft.no/bendik/
//
//

#ifndef __MULTISELTREECTRL_H
#define __MULTISELTREECTRL_H

#ifndef __TREECTLX_H__
	#include "TreeCtrlEx.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiSelTreeCtrl window

class CMultiSelTreeCtrl : public CTreeCtrlEx
{
	DECLARE_DYNAMIC(CMultiSelTreeCtrl)

// Construction
public:
	CMultiSelTreeCtrl() : m_bSelectPending(FALSE) {}

// Attributes
public:
	UINT GetSelectedCount();
	CTreeCursor GetFirstSelectedItem();
	CTreeCursor GetNextSelectedItem(CTreeCursor &hItem);
	CTreeCursor GetPrevSelectedItem(CTreeCursor &hItem);

	BOOL SelectItemEx(CTreeCursor &hItem, BOOL bSelect = TRUE);

	BOOL SelectItems(CTreeCursor &hFromItem, CTreeCursor &hToItem);
	void ClearSelection(BOOL bMultiOnly = FALSE);

protected:
	void SelectMultiple( CTreeCursor &hClickedItem, UINT nFlags );

private:
	BOOL		m_bSelectPending;
	CPoint		m_ptClick;
	CTreeCursor	m_hClickedItem;
	CTreeCursor	m_hFirstSelectedItem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiSelTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiSelTreeCtrl() {}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiSelTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif
