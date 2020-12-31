#include "OXTaskbarIcon.h"

class CCaptureTaskbarIcon : public COXTaskbarIcon
{
public:
	CCaptureTaskbarIcon() { };
	void DoPopupMenu();
	// pointer to window to send messages
	CWnd* m_pPopupOwner;
	
	//{{AFX_VIRTUAL(CCaptureTaskbarIcon)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCaptureTaskbarIcon)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
