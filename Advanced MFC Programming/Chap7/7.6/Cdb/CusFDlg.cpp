#include "stdafx.h"
#include "CDB.h"
#include "CusFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(MCCusFileDialog, CFileDialog)

MCCusFileDialog::MCCusFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(MCCusFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(MCCusFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL MCCusFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	LPOFNOTIFY pofn;
	CString szStr;
	CFile file;
	char szBuf[256];

	pofn=(LPOFNOTIFY)lParam;
	if(pofn->hdr.code == CDN_SELCHANGE)
	{
		szStr=GetPathName();
		if(GetFileExt().CompareNoCase("CPP") == 0)
		{
			if(file.Open(szStr, CFile::modeRead) == FALSE)
			{
				file.Abort();
				return TRUE;
			}
			file.Read(szBuf, 255);
			file.Close();
			((CEdit *)GetDlgItem(IDC_EDIT))->SetWindowText(szBuf);
		}
		else ((CEdit *)GetDlgItem(IDC_EDIT))->SetWindowText(NULL);
	}

	return TRUE;
}
