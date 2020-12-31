/****************************************************************************
* This Program was developed by Venkata Gopal.T								*
* This file contains definition of CDirPick class						*
*****************************************************************************/


#if !defined(AFX_DIRPICK_H__E4CF2117_DFA5_11D1_AAB6_0080C74D32C6__INCLUDED_)
#define AFX_DIRPICK_H__E4CF2117_DFA5_11D1_AAB6_0080C74D32C6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DirPick.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirPick dialog

class  __declspec(dllexport) CDirPick : public CFileDialog
{
	DECLARE_DYNAMIC(CDirPick)

public:
	CDirPick(BOOL bOpenFileDialog = FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	int SelectDirectory(HWND hWnd,LPTSTR lpTitle,LPTSTR lpDirPath);
protected:
	//{{AFX_MSG(CDirPick)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRPICK_H__E4CF2117_DFA5_11D1_AAB6_0080C74D32C6__INCLUDED_)
