#if !defined(AFX_TOOLBAR_H__636ED3A1_158B_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_TOOLBAR_H__636ED3A1_158B_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDlgToolBar : public CToolBar
{
public:
	CDlgToolBar();
	//{{AFX_VIRTUAL(CDlgToolBar)
	//}}AFX_VIRTUAL

public:
	virtual ~CDlgToolBar();

protected:
	//{{AFX_MSG(CDlgToolBar)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TOOLBAR_H__636ED3A1_158B_11D1_9C9A_444553540000__INCLUDED_)
