#ifndef _SSITASKBARICON_H_
#define _SSITASKBARICON_H_

#include "OXTaskbarIcon.h"

class CSSITaskbarIcon : public COXTaskbarIcon
{
public:
	CSSITaskbarIcon() { };
	void DoPopupMenu();
	// pointer to window to send messages
	CWnd* m_pPopupOwner;
	
	//{{AFX_VIRTUAL(CSSITaskbarIcon)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSSITaskbarIcon)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	//	_SSITASKBARICON_H_
