#if !defined(AFX_PSHT_H__6F1FA2EA_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_PSHT_H__6F1FA2EA_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "Page.h"

class CMLPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMLPropertySheet)
public:
	CMLPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMLPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	//{{AFX_VIRTUAL(CMLPropertySheet)
	//}}AFX_VIRTUAL

public:
	virtual ~CMLPropertySheet();
	void DoModeless();

protected:
	CWnd *m_pParentWnd;
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	//{{AFX_MSG(CMLPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PSHT_H__6F1FA2EA_130A_11D1_9C9A_444553540000__INCLUDED_)
