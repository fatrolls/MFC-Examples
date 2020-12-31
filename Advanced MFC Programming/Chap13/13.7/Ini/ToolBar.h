#if !defined(AFX_TOOLBAR_H__D1C586B7_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_TOOLBAR_H__D1C586B7_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CToolBarEx : public CToolBar
{
public:
	CToolBarEx();
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL
	virtual ~CToolBarEx();

protected:
	//{{AFX_MSG(CToolBarEx)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TOOLBAR_H__D1C586B7_3E3F_11D1_9C9A_444553540000__INCLUDED_)
