/****************************************************************************
* This Program was developed by Venkata Gopal.T								*
* This file contains inplementation of CDirPick class						*
*****************************************************************************/

#include "stdafx.h"
#include <commdlg.h>
#include <dlgs.h> 
#include "resource.h"
#include "DirPickf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CDirPick::SelectDirectory(HWND hWnd,LPTSTR lpTitle,LPSTR lpDirPath)
{
	TCHAR         szFile[MAX_PATH + 1]      = "\0";
    strcpy( szFile, "");
	if( ! lpTitle)
	    m_ofn.lpstrTitle        = "Select A Directory";
	else
	    m_ofn.lpstrTitle        = lpTitle;

	// Fill in the OPENFILENAME structure to support a template and hook.
	m_ofn.lStructSize       = sizeof(OPENFILENAME);
    m_ofn.hwndOwner         = hWnd;
    m_ofn.hInstance         = AfxGetResourceHandle();
    m_ofn.lpstrFilter       = NULL;
    m_ofn.lpstrCustomFilter = NULL;
    m_ofn.nMaxCustFilter    = 0;
    m_ofn.nFilterIndex      = 0;
    m_ofn.lpstrFile         = szFile;
    m_ofn.nMaxFile          = sizeof(szFile);
    m_ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_DIRPICK);
    m_ofn.Flags             = OFN_NONETWORKBUTTON | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST  
							  |OFN_NOVALIDATE |OFN_ENABLEHOOK| OFN_ENABLETEMPLATE;
	int nValue =  DoModal();
	GetCurrentDirectory( sizeof(lpDirPath), lpDirPath);

	return nValue;
}

/////////////////////////////////////////////////////////////////////////////
// CDirPick

IMPLEMENT_DYNAMIC(CDirPick, CFileDialog)

CDirPick::CDirPick(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CDirPick, CFileDialog)
	//{{AFX_MSG_MAP(CDirPick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDirPick::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	CWnd *pEditWnd = GetDlgItem(1152);
	pEditWnd->SetWindowText("XXX");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

