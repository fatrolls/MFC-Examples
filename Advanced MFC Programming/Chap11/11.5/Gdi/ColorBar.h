#if !defined(AFX_COLORBAR_H__C2EEA5C2_29BE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_COLORBAR_H__C2EEA5C2_29BE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GDIDoc.h"
#include "Button.h"

class CColorBar : public CDialogBar
{
public:
	CColorBar();
	BOOL Create(CWnd *, LPCTSTR, UINT, UINT);
	BOOL Create(CWnd *, UINT, UINT, UINT);
	void UpdateAllButtons();
	//{{AFX_DATA(CColorBar)
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CColorBar)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	CColorButton m_btnColor[COLOR_BUTTON_NUM];
	CFBButton m_btnFB;

	BOOL InitButtons();
	//{{AFX_MSG(CColorBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLORBAR_H__C2EEA5C2_29BE_11D1_9C9A_444553540000__INCLUDED_)
