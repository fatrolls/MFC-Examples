#if !defined(AFX_MDLGBAR_H__BCBCDFED_F3B1_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MDLGBAR_H__BCBCDFED_F3B1_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif
class MCDialogBar : public CDialogBar
{
public:
	MCDialogBar();
	//{{AFX_DATA(MCDialogBar)
	//}}AFX_DATA
	virtual CSize CalcDynamicLayout(int, DWORD);
	//{{AFX_VIRTUAL(MCDialogBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(MCDialogBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MDLGBAR_H__BCBCDFED_F3B1_11D0_9C9A_444553540000__INCLUDED_)
