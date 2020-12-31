

#include "OXTaskbarIcon.h"

class CDemoTaskbarIcon : public COXTaskbarIcon
{
public:
	CDemoTaskbarIcon() { m_bDownFromDlbClk = FALSE; };
	void DoPopupMenu(LPCTSTR sDemoMenuText);
	CWnd* m_pPopupOwner;
	
	//{{AFX_VIRTUAL(CDemoTaskbarIcon)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDemoTaskbarIcon)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	// to distinguish WM_LBUTTONDBLCLK from WM_LBUTTONDOWN
	BOOL m_bDownFromDlbClk;
};
