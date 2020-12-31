#if !defined(AFX_TREECTRL_H__EBC846E1_08BC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_TREECTRL_H__EBC846E1_08BC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCTreeCtrl : public CTreeCtrl
{
public:
	MCTreeCtrl();
	virtual ~MCTreeCtrl();
	void CopyItemTo(HTREEITEM, HTREEITEM);
	BOOL IsDescendent(HTREEITEM, HTREEITEM);
	//{{AFX_VIRTUAL(MCTreeCtrl)
	//}}AFX_VIRTUAL

protected:
	BOOL m_bIsDragging;
	CImageList *m_pilDrag;
	HTREEITEM m_hTreeDragSrc;
	HTREEITEM m_hTreeDragTgt;

	//{{AFX_MSG(MCTreeCtrl)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TREECTRL_H__EBC846E1_08BC_11D1_9C9A_444553540000__INCLUDED_)
