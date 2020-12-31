#if !defined(AFX_WORDPAD_H__D065BD7A_43C2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_WORDPAD_H__D065BD7A_43C2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

#define STRING_FILTER	"Rich Text Format (*.rtf)\0*.RTF\0Plain Text Format (*.txt)\0*.TXT\0All Files (*.*)\0*.*\0"

class CWordPadApp : public CWinApp
{
public:
	CWordPadApp();
	//{{AFX_VIRTUAL(CWordPadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CWordPadApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_WORDPAD_H__D065BD7A_43C2_11D1_9C9A_444553540000__INCLUDED_)
