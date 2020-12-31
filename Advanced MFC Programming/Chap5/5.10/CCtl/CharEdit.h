#if !defined(AFX_CHAREDIT_H__59977222_0405_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CHAREDIT_H__59977222_0405_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCCharEdit : public CEdit
{
public:
	MCCharEdit();
	//{{AFX_VIRTUAL(MCCharEdit)
	//}}AFX_VIRTUAL

public:
	virtual ~MCCharEdit();

protected:
	//{{AFX_MSG(MCCharEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CHAREDIT_H__59977222_0405_11D1_9C9A_444553540000__INCLUDED_)
