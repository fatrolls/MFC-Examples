/*
 *	Extended MFC message boxes -- Version 1.1a
 *	Copyright (c) 2004 Michael P. Mehl. All rights reserved.
 *
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1a (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at 
 *	http://www.mozilla.org/MPL/.
 *
 *	Software distributed under the License is distributed on an "AS IS" basis,
 *	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 *	for the specific language governing rights and limitations under the
 *	License. 
 *
 *	The Original Code is Copyright (c) 2004 Michael P. Mehl. All rights
 *	reserved. The Initial Developer of the Original Code is Michael P. Mehl
 *	<michael.mehl@web.de>.
 *
 *	Alternatively, the contents of this file may be used under the terms of
 *	the GNU Lesser General Public License Version 2.1 (the "LGPL License"),
 *	in which case the provisions of LGPL License are applicable instead of
 *	those above. If you wish to allow use of your version of this file only
 *	under the terms of the LGPL License and not to allow others to use your
 *	version of this file under the MPL, indicate your decision by deleting
 *	the provisions above and replace them with the notice and other provisions
 *	required by the LGPL License. If you do not delete the provisions above,
 *	a recipient may use your version of this file under either the MPL or
 *	the LGPL License.
 */

#include "stdafx.h"
#include "MsgBoxTest.h"
#include "MsgBoxTestDlg.h"

#include "MessageBoxDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMsgBoxTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMsgBoxTestApp::CMsgBoxTestApp ( )
{
}

CMsgBoxTestApp theApp;

BOOL CMsgBoxTestApp::InitInstance ( )
{
	AfxOleInit();
	InitCommonControls();

	__super::InitInstance();

	SetRegistryKey(_T("Michael P. Mehl"));

	CMsgBoxTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

/*
 *	Method for changing the application-wide behavior of AfxMessageBox().
 *
 *	If you want, that every call of AfxMessageBox() in your application is
 *	replaced by the new message box dialog, simply use the following code.
 *	All codes of AfxMessageBox will call this method and use the new message
 *	boxes.
 */
int CMsgBoxTestApp::DoMessageBox ( LPCTSTR lpszPrompt, UINT nType, 
	UINT nIDPrompt )
{
	// Create a handle to store the parent window of the message box.
	CWnd* pParentWnd = CWnd::GetActiveWindow();

	// Check whether an active window was retrieved successfully.
	if ( pParentWnd == NULL )
	{
		// Try to retrieve a handle to the last active popup.
		pParentWnd = GetMainWnd()->GetLastActivePopup();
	}
	
	// Create the message box dialog.
	CMessageBoxDialog dlgMessage(pParentWnd, lpszPrompt, _T(""), nType,
		nIDPrompt);

	// Display the message box dialog an return the result.
	return (int)dlgMessage.DoModal();
}
