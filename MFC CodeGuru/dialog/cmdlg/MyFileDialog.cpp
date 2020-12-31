// MyFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CmDgTest.h"
#include "MyFileDialog.h"
#include <dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////
// This is where the real action is going on
// Remember #include <dlgs.h>
BOOL CMyFileDialog::OnInitDialog() // Override
{
	// This variable should be changed acording to your wishes
	// about the size of the finished dialog
	const UINT iExtraSize = 150;
	// Number of controls in the File Dialog
	const UINT nControls = 7;	

	// Get a pointer to the original dialog box.
	CWnd *wndDlg = GetParent();

	RECT Rect;
	wndDlg->GetWindowRect(&Rect);
	// Change the size
	wndDlg->SetWindowPos(NULL, 0, 0, 
						 Rect.right - Rect.left, 
						 Rect.bottom - Rect.top + iExtraSize, 
						 SWP_NOMOVE);

	// Control ID's - defined in <dlgs.h>
	UINT Controls[nControls] = {stc3, stc2,  // The two label controls
								edt1, cmb1,  // The eidt control and the drop-down box
								IDOK, IDCANCEL, 
								lst1};       // Explorer vinduet

	// Go through each of the controls in the dialog box, and move them to a new position
	for (int i=0 ; i<nControls ; i++)
	{
		CWnd *wndCtrl = wndDlg->GetDlgItem(Controls[i]);
		wndCtrl->GetWindowRect(&Rect);
		wndDlg->ScreenToClient(&Rect); // Remember it is child controls

		// Move all the controls according to the new size of the dialog.
		if (Controls[i] != lst1)
			wndCtrl->SetWindowPos(NULL, 
							  Rect.left, Rect.top + iExtraSize,
							  0, 0, SWP_NOSIZE);
		else // This is the explorer like window. It should be sized - not moved.
			wndCtrl->SetWindowPos(NULL, 0, 0,
								 Rect.right - Rect.left, 
								 Rect.bottom - Rect.top + iExtraSize, 
								 SWP_NOMOVE);
	}

	// Remember to call the baseclass.
	return CFileDialog::OnInitDialog();
}
