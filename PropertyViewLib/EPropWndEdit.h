#if !defined(AFX_ITEMOVERLAYEDIT_H__7F158E1B_9240_4A30_8CA9_3EFBEAC1F116__INCLUDED_)
#define AFX_ITEMOVERLAYEDIT_H__7F158E1B_9240_4A30_8CA9_3EFBEAC1F116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EPropView;

class EPropWndEdit : public CEdit
{

public:
	EPropWndEdit();
	virtual ~EPropWndEdit();

public:

	//{{AFX_VIRTUAL(EPropWndEdit)
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	//}}AFX_VIRTUAL


protected:

	//{{AFX_MSG(EPropWndEdit)
	afx_msg void OnKillFocus( CWnd* );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
