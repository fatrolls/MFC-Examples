#if !defined(AFX_MDLGBAR_H__E097B221_EEDF_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MDLGBAR_H__E097B221_EEDF_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class MCDialogBar : public CDialogBar  
{
public:
	MCDialogBar();
	virtual ~MCDialogBar();
//	BOOL OnToolTipNotify(UINT, NMHDR *, LRESULT *);

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(MCDialogBar)
};

#endif // !defined(AFX_MDLGBAR_H__E097B221_EEDF_11D0_9C9A_444553540000__INCLUDED_)
