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

#pragma once

#include "afxwin.h"

class CMsgBoxTestDlg : public CDialog
{

public:

	CMsgBoxTestDlg ( CWnd* pParent = NULL );

	enum { IDD = IDD_MSGBOXTEST_DIALOG };

protected:

	virtual void DoDataExchange ( CDataExchange* pDX );

protected:

	HICON m_hIcon;

	virtual BOOL OnInitDialog ( );
	afx_msg void OnPaint ( );
	afx_msg HCURSOR OnQueryDragIcon ( );
	DECLARE_MESSAGE_MAP()

private:

	afx_msg void OnDisplayMessageBox ( );
	afx_msg void OnResetMessageBoxes ( );

	CString m_strTitle;
	CString m_strMessage;
	CComboBox m_cmbMessageStyle;
	CComboBox m_cmbMessageIcon;
	CComboBox m_cmbMessageCheckbox;
	CComboBox m_cmbDefaultButton;
	BOOL m_bYesToAll;
	BOOL m_bNoToAll;
	BOOL m_bRightAlign;
	BOOL m_bNoSound;
	BOOL m_bDefaultChecked;
	BOOL m_bTimeout;
	UINT m_nTimeout;
	BOOL m_bDisabledTimeout;

};
