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
	//{{AFX_VIRTUAL(MCTreeCtrl)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(MCTreeCtrl)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TREECTRL_H__EBC846E1_08BC_11D1_9C9A_444553540000__INCLUDED_)
