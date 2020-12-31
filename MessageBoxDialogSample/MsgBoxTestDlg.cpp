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

CMsgBoxTestDlg::CMsgBoxTestDlg ( CWnd* pParent /*=NULL*/ )
	: CDialog ( CMsgBoxTestDlg::IDD, pParent )
	, m_strTitle(_T("Enter your title here!"))
	, m_strMessage(_T("Enter your message here!"))
	, m_bYesToAll(FALSE)
	, m_bNoToAll(FALSE)
	, m_bRightAlign(FALSE)
	, m_bNoSound(FALSE)
	, m_bDefaultChecked(FALSE)
	, m_bTimeout(FALSE)
	, m_nTimeout(10)
	, m_bDisabledTimeout(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgBoxTestDlg::DoDataExchange ( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_MESSAGE_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_MESSAGE_TEXT, m_strMessage);
	DDX_Control(pDX, IDC_MESSAGE_STYLE, m_cmbMessageStyle);
	DDX_Control(pDX, IDC_MESSAGE_ICON, m_cmbMessageIcon);
	DDX_Control(pDX, IDC_MESSAGE_CHECKBOX, m_cmbMessageCheckbox);
	DDX_Check(pDX, IDC_YES_TO_ALL, m_bYesToAll);
	DDX_Check(pDX, IDC_NO_TO_ALL, m_bNoToAll);
	DDX_Check(pDX, IDC_RIGHT_ALIGN, m_bRightAlign);
	DDX_Check(pDX, IDC_NO_SOUND, m_bNoSound);
	DDX_Control(pDX, IDC_DEFAULT_BUTTON, m_cmbDefaultButton);
	DDX_Check(pDX, IDC_DEFAULT_CHECKED, m_bDefaultChecked);
	DDX_Check(pDX, IDC_CHECK1, m_bTimeout);
	DDX_Text(pDX, IDC_TIMEOUT_SECONDS, m_nTimeout);
	DDV_MinMaxUInt(pDX, m_nTimeout, 1, 60);
	DDX_Check(pDX, IDC_DISABLED_TIMEOUT, m_bDisabledTimeout);
}

BEGIN_MESSAGE_MAP(CMsgBoxTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DISPLAY_MESSAGE_BOX, OnDisplayMessageBox)
	ON_BN_CLICKED(IDC_RESET_MESSAGE_BOXES, OnResetMessageBoxes)
END_MESSAGE_MAP()

BOOL CMsgBoxTestDlg::OnInitDialog ( )
{
	// Call the parent method.
	__super::OnInitDialog();

	// Define the symbol for the dialog.
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Define a list of styles.
	struct tagMSGBOXSTYLES
	{
		UINT	nStyle;
		CString	strStyle;
	} sStyles[] =
	{
		{	MB_OKCANCEL,				_T("MB_OKCANCEL")				},
		{	MB_ABORTRETRYIGNORE,		_T("MB_ABORTRETRYIGNORE")		},
		{	MB_YESNOCANCEL,				_T("MB_YESNOCANCEL")			},
		{	MB_YESNO,					_T("MB_YESNO")					},
		{	MB_RETRYCANCEL,				_T("MB_RETRYCANCEL")			},
		{	MB_CANCELTRYCONTINUE,		_T("MB_CANCELTRYCONTINUE")		},
		{	MB_CONTINUEABORT,			_T("MB_CONTINUEABORT")			},
		{	MB_SKIPSKIPALLCANCEL,		_T("MB_SKIPSKIPALLCANCEL")		},
		{	MB_IGNOREIGNOREALLCANCEL,	_T("MB_IGNOREIGNOREALLCANCEL")	},
		{	MB_OK,						_T("MB_OK")						}
	};

	// Run through all defined styles.
	for ( int i = 0; i < ( sizeof(sStyles) / sizeof(sStyles[0]) ); i++ )
	{
		// Add the style to the combo box.
		m_cmbMessageStyle.InsertString(i, sStyles[i].strStyle);
		m_cmbMessageStyle.SetItemData(i, (DWORD_PTR)sStyles[i].nStyle);
		m_cmbMessageStyle.SetCurSel(i);
	}

	// Define a list of icons.
	struct tagMSGBOXICONS
	{
		UINT	nIcon;
		CString	strIcon;
	} sIcons[] =
	{
		{	MB_ICONEXCLAMATION,			_T("MB_ICONEXCLAMATION")		},
		{	MB_ICONHAND,				_T("MB_ICONHAND")				},
		{	MB_ICONQUESTION,			_T("MB_ICONQUESTION")			},
		{	MB_ICONASTERISK,			_T("MB_ICONASTERISK")			},
		{	0,							_T("None")						}
	};

	// Run through all defined icons.
	for ( int i = 0; i < ( sizeof(sIcons) / sizeof(sIcons[0]) ); i++ )
	{
		// Add the icon to the combo box.
		m_cmbMessageIcon.InsertString(i, sIcons[i].strIcon);
		m_cmbMessageIcon.SetItemData(i, (DWORD_PTR)sIcons[i].nIcon);
		m_cmbMessageIcon.SetCurSel(i);
	}

	// Define a list of checkboxes.
	struct tagMSGBOXCHECKBOXES
	{
		UINT	nCheckbox;
		CString	strCheckbox;
	} sCheckboxes[] =
	{
		{	MB_DONT_DISPLAY_AGAIN,	_T("MB_DONT_DISPLAY_AGAIN")			},
		{	MB_DONT_ASK_AGAIN,		_T("MB_DONT_ASK_AGAIN")				},
		{	0,						_T("None")							}
	};

	// Run through all defined checkboxes.
	for ( int i = 0; i < ( sizeof(sCheckboxes) / sizeof(sCheckboxes[0]) ); i++ )
	{
		// Add the checkbox to the combo box.
		m_cmbMessageCheckbox.InsertString(i, sCheckboxes[i].strCheckbox);
		m_cmbMessageCheckbox.SetItemData(i, (DWORD_PTR)sCheckboxes[i].nCheckbox);
		m_cmbMessageCheckbox.SetCurSel(i);
	}

	// Define a list of defbuttons.
	struct tagMSGBOXDEFBUTTONS
	{
		UINT	nDefButton;
		CString	strDefButton;
	} sDefButtons[] =
	{
		{	MB_DEFBUTTON1,			_T("MB_DEFBUTTON1")					},
		{	MB_DEFBUTTON2,			_T("MB_DEFBUTTON2")					},
		{	MB_DEFBUTTON3,			_T("MB_DEFBUTTON3")					},
		{	MB_DEFBUTTON4,			_T("MB_DEFBUTTON4")					},
		{	MB_DEFBUTTON5,			_T("MB_DEFBUTTON5")					},
		{	MB_DEFBUTTON6,			_T("MB_DEFBUTTON6")					},
		{	0,						_T("Default")						}
	};

	// Run through all defined defbuttons.
	for ( int i = 0; i < ( sizeof(sDefButtons) / sizeof(sDefButtons[0]) ); i++ )
	{
		// Add the defbutton to the combo box.
		m_cmbDefaultButton.InsertString(i, sDefButtons[i].strDefButton);
		m_cmbDefaultButton.SetItemData(i, (DWORD_PTR)sDefButtons[i].nDefButton);
		m_cmbDefaultButton.SetCurSel(i);
	}

	// Return successfully.
	return TRUE;
}

void CMsgBoxTestDlg::OnPaint ( ) 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMsgBoxTestDlg::OnQueryDragIcon ( )
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMsgBoxTestDlg::OnDisplayMessageBox ( )
{
	// Read the information from the dialog.
	UpdateData();

	// Check whether a message was given.
	if ( m_strMessage.IsEmpty() )
	{
		// Display an error message.
		AfxMessageBox(IDS_ERROR_MESSAGE_MISSING, MB_ICONSTOP | MB_OK | 
			MB_RIGHT_ALIGN);

		// Focus the input box.
		GetDlgItem(IDC_MESSAGE_TEXT)->SetFocus();

		// Stop here.
		return;
	}

	// Create a variable containing the style of the message box.
	UINT nStyle = 
		(UINT)m_cmbMessageStyle.GetItemData(m_cmbMessageStyle.GetCurSel()) |
		(UINT)m_cmbMessageIcon.GetItemData(m_cmbMessageIcon.GetCurSel()) |
		(UINT)m_cmbMessageCheckbox.GetItemData(m_cmbMessageCheckbox.GetCurSel()) |
		(UINT)m_cmbDefaultButton.GetItemData(m_cmbDefaultButton.GetCurSel());

	// Check whether to add additional styles.
	if ( m_bYesToAll )
		nStyle |= MB_YES_TO_ALL;
	if ( m_bNoToAll )
		nStyle |= MB_NO_TO_ALL;
	if ( m_bRightAlign )
		nStyle |= MB_RIGHT_ALIGN;
	if ( m_bNoSound )
		nStyle |= MB_NO_SOUND;
	if ( m_bDefaultChecked )
		nStyle |= MB_DEFAULT_CHECKED;

	// Create a variable for storing the result of the message box.
	int nResult = 0;

	// Check whether a title was given or a timeout was choosen.
	if ( m_strTitle.IsEmpty() || !m_bTimeout )
	{
		// NOTE: If not title is given, we can use the standard MFC
		// AfxMessageBox method, because through this method no title can be
		// set and the application name will be used as title. If you want
		// to set a custom title, you have to create a CMessageBoxDialog
		// object and call it directly. Also if you want to use other custom
		// methods like user defined icons or a timeout, you have to create
		// a CMessageBoxDialog object and utilize it directly.

		// Use the standard MFC method.
		nResult = AfxMessageBox(m_strMessage, nStyle);
	}
	else
	{
		// Create a message box dialog.
		CMessageBoxDialog dlgMessageBox(this, m_strMessage, m_strTitle, nStyle);

		// Check whether a timeout was choosen.
		if ( m_bTimeout )
		{
			// Set the timeout for the message box.
			dlgMessageBox.SetTimeout(m_nTimeout, m_bDisabledTimeout);
		}

		// Display the dialog.
		nResult = (int)dlgMessageBox.DoModal();
	}

	// Create a string for storing the result ID.
	CString strResult = _T("");

	// Switch the result.
	switch ( nResult )
	{

		case IDOK:

			// Save the result as a string.
			strResult = _T("IDOK");
			break;

		case IDCANCEL:

			// Save the result as a string.
			strResult = _T("IDCANCEL");
			break;

		case IDABORT:

			// Save the result as a string.
			strResult = _T("IDABORT");
			break;

		case IDRETRY:

			// Save the result as a string.
			strResult = _T("IDRETRY");
			break;

		case IDIGNORE:

			// Save the result as a string.
			strResult = _T("IDIGNORE");
			break;

		case IDYES:

			// Save the result as a string.
			strResult = _T("IDYES");
			break;

		case IDNO:

			// Save the result as a string.
			strResult = _T("IDNO");
			break;

		case IDTRYAGAIN:

			// Save the result as a string.
			strResult = _T("IDTRYAGAIN");
			break;

		case IDCONTINUE:

			// Save the result as a string.
			strResult = _T("IDCONTINUE");
			break;

		case IDYESTOALL:

			// Save the result as a string.
			strResult = _T("IDYESTOALL");
			break;

		case IDNOTOALL:

			// Save the result as a string.
			strResult = _T("IDNOTOALL");
			break;

		case IDSKIP:

			// Save the result as a string.
			strResult = _T("IDSKIP");
			break;

		case IDSKIPALL:

			// Save the result as a string.
			strResult = _T("IDSKIPALL");
			break;

		case IDIGNOREALL:

			// Save the result as a string.
			strResult = _T("IDIGNOREALL");
			break;

	}

	// Create a string for storing the message.
	CString strMessage;

	// Format the message.
	AfxFormatString1(strMessage, IDS_RESULT_MESSAGE, strResult);

	// Display a message box with the result.
	AfxMessageBox(strMessage, MB_OK | MB_ICONINFORMATION | MB_RIGHT_ALIGN);
}

void CMsgBoxTestDlg::OnResetMessageBoxes ( )
{
	// Reset the message boxes.
	CMessageBoxDialog::ResetMessageBoxes();

	// Display a message.
	AfxMessageBox(IDS_RESULT_RESET, MB_OK | MB_ICONINFORMATION | 
		MB_RIGHT_ALIGN);
}
