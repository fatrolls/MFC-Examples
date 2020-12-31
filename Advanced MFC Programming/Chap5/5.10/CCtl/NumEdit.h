#if !defined(AFX_NUMEDIT_H__59977221_0405_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_NUMEDIT_H__59977221_0405_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCNumEdit : public CEdit
{
public:
	MCNumEdit();

	//{{AFX_VIRTUAL(MCNumEdit)
	//}}AFX_VIRTUAL

public:
	virtual ~MCNumEdit();

protected:
	//{{AFX_MSG(MCNumEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_NUMEDIT_H__59977221_0405_11D1_9C9A_444553540000__INCLUDED_)
