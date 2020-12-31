// MyTreeListCtrl.h: interface for the CMyTreeListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTREELISTCTRL_H__97C33F84_2D59_4692_B330_7C24A3014F1E__INCLUDED_)
#define AFX_MYTREELISTCTRL_H__97C33F84_2D59_4692_B330_7C24A3014F1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTreeListCtrl : public CTreeListCtrl  
{
public:
	CMyTreeListCtrl();
	virtual ~CMyTreeListCtrl();

protected:
	//{{AFX_MSG(CMyTreeListCtrl)
	afx_msg void OnExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdating(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdated(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDragEnter(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDragLeave(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDragOver(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrop(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_MYTREELISTCTRL_H__97C33F84_2D59_4692_B330_7C24A3014F1E__INCLUDED_)
