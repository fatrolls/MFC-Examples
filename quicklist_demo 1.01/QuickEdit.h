#if !defined(AFX_QUICKEDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_QUICKEDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditCell.h : header file
//

#include "quicklist.h"
class CQuickList;

/*
	The code in this class is very much based on Lee Nowotny's article 
	"Easy Navigation Through an Editable List View",
	http://www.codeproject.com/listctrl/listeditor.asp

	And that article is based on another article by Zafir Anjum, "Editable Subitems":
	http://www.codeguru.com/listview/edit_subitems.shtml

    However, currently most of it is now rewritten. But I thought it 
	would be unfair to not mention it.
*/

/////////////////////////////////////////////////////////////////////////////
// CQuickEdit window
class CQuickEdit : public CEdit
{
public:
	CQuickEdit (CQuickList* pCtrl, int iItem, int iSubItem, CString sInitText, bool endonlostfocus);
    virtual ~CQuickEdit();

	void SetEndOnLostFocus(bool autoend);
	void StopEdit(bool cancel, UINT endkey=0);

    //{{AFX_VIRTUAL(CQuickEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
    CQuickList* pListCtrl;
    int			Item;
    int			SubItem;
    CString		InitText;
	
	bool		m_endOnLostFocus;
	bool		m_isClosing;
    
    //{{AFX_MSG(CQuickEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKEDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_)
