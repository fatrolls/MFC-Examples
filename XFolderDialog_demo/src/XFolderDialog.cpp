// XFolderDialog.cpp  Version 1.4
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// Description:
//     XFolderDialog implements CXFolderDialog, a folder browsing dialog that
//     uses the new Windows 2000-style dialog.  Please see article at
//     www.codeproject.com.
//
// History
//     Version 1.4 - 2010 June 2
//     - Fixed problem with Win7
//
//     Version 1.3 - 2008 February 22
//     - Fixed problems related to compiling under recent versions of VS.
//     - Fixed bug when new folder is created and OK pressed, reported 
//       by McLyndon and Super Garrison.
//     - Fixed bug when new path entered in mru combo, reported by Brad Bruce, 
//       with fix suggested by Manfred Drasch.
//     - Fixed bug when used in dll, reported by k-mommos.
//     - Fixed bug where you click My Computer then select folder, with fix 
//       suggested by Wade Ledbetter.
//     - Added ability to set/save list view mode, requested by Aetschmaen.
//
//     Version 1.2 - 2005 March 22
//     - Fixed initial sizing problem with placebar
//
//     Version 1.1 - 2005 March 17
//     - Improved performance by using file filter
//
//     Version 1.0 - 2005 March 15
//     - Initial public release;  based on Version 1.2 of XFileDialog,
//       with fixes provided by Ned Harding and Rail Jon Rogut.
//
// Public APIs:
//          NAME                           DESCRIPTION
//     ----------------  -----------------------------------------------------
//     EnableRegistry()  Enables/disables use of registry to store view mode
//     GetPath()         Returns folder path
//     GetOsVersion()    Returns OS version used to control dialog appearance
//     GetViewMode()     Gets last-used view mode from folder select dialog
//     SetOsVersion()    Set OS version used to control dialog appearance
//     SetTitle()        Set title of dialog ("Select Folder" is default)
//     SetViewMode()     Sets view mode for folder select dialog list control
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxpriv.h>
#include "XFolderDialog.h"
#include "XFolderDialogRes.h"
#include <io.h>
#include "dlgs.h"
#include "xWinVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#pragma warning(disable : 4996)	// disable bogus deprecation warning

//=============================================================================
// display _WIN32_WINNT in output window - this determines OPENFILENAME size
//=============================================================================
#define makestring2(x) #x
#define makestring(x) makestring2(x)
#ifdef _WIN32_WINNT
	#pragma message(__FILE__ "(" makestring(__LINE__) ") : _WIN32_WINNT = " makestring(_WIN32_WINNT) "\n")
#else
	#pragma message(__FILE__ "(" makestring(__LINE__) ") : _WIN32_WINNT is not defined\n")
#endif


//=============================================================================
// set resource handle (in case used in DLL)
//=============================================================================
#ifdef _USRDLL
#define AFXMANAGESTATE AfxGetStaticModuleState
#else
#define AFXMANAGESTATE AfxGetAppModuleState
#endif

#ifndef OPENFILENAME_SIZE_VERSION_400A
	#define OPENFILENAME_SIZE_VERSION_400A  CDSIZEOF_STRUCT(OPENFILENAMEA,lpTemplateName)
	#define OPENFILENAME_SIZE_VERSION_400W  CDSIZEOF_STRUCT(OPENFILENAMEW,lpTemplateName)
	#ifdef UNICODE
		#define OPENFILENAME_SIZE_VERSION_400  OPENFILENAME_SIZE_VERSION_400W
	#else
		#define OPENFILENAME_SIZE_VERSION_400  OPENFILENAME_SIZE_VERSION_400A
	#endif // !UNICODE
#endif //


#ifndef __noop
#if _MSC_VER < 1300
#define __noop ((void)0)
#endif
#endif

#undef TRACE
#define TRACE __noop

//=============================================================================
// if you want to see the TRACE output, uncomment this line:
//#include "XTrace.h"
//=============================================================================


//=============================================================================
// CXFolderDialog
//=============================================================================

IMPLEMENT_DYNAMIC(CXFolderDialog, CFileDialog)


//=============================================================================
// registry key
//=============================================================================
static LPCTSTR PROFILE_SETTINGS = _T("XFolderDialog");
static LPCTSTR PROFILE_VIEWMODE = _T("ViewMode");


//=============================================================================
// static string for file filter
//=============================================================================
static LPCTSTR szFilter = _T("Files (*.XFolderDialog-8C0C924B-7A86-4e8d-8D6E-A1C50D74E8DF)|")
								 _T("*.XFolderDialog-8C0C924B-7A86-4e8d-8D6E-A1C50D74E8DF||");

//=============================================================================
BEGIN_MESSAGE_MAP(CXFolderDialog, CFileDialog)
//=============================================================================
	//{{AFX_MSG_MAP(CXFolderDialog)
	ON_WM_SIZE()
	ON_CBN_SELENDOK(IDC_MRU_COMBO, OnSelendokMruCombo)
	ON_CBN_KILLFOCUS(IDC_MRU_COMBO, OnCbnKillfocusMruCombo)	
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

//=============================================================================
CXFolderDialog::CXFolderDialog(LPCTSTR lpszInitialFolder /*= NULL*/,
							   DWORD dwFlags /*= 0*/,
							   CWnd* pParentWnd /*= NULL*/)
	: CFileDialog(TRUE, NULL, NULL, dwFlags | OFN_HIDEREADONLY, szFilter, pParentWnd)
//=============================================================================
{
	m_strInitialFolder     = lpszInitialFolder;
	m_strPath              = _T("");
	m_dwFlags              = dwFlags;
	m_eOsVersion           = XFILEDIALOG_AUTO_DETECT_OS_VERSION;
	m_strTitle             = _T("");
	m_nIdFileNameStatic    = 1090;
	m_nIdFileNameCombo     = 1148;	// or 1152
	m_nIdFilesOfTypeStatic = 1089;
	m_nIdFilesOfTypeCombo  = 1136;
	m_nIdPlaceBar          = 1184;
	m_nViewMode            = XLVM_XP_UNDEFINED;
	m_bUseRegistry         = FALSE;
	m_bPersist             = FALSE;
	m_bVistaFlag           = FALSE;
#if _MFC_VER > 0x700
	m_bVistaFlag = m_bVistaStyle;
	m_bVistaStyle = FALSE;
#endif
	// we use string version of SetTemplate(), to avoid resource id collisions
	SetTemplate(0, _T("IDD_XFOLDERDIALOG"));
}

//=============================================================================
CXFolderDialog::~CXFolderDialog()
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::~CXFolderDialog\n"));
	if (m_bUseRegistry && m_bPersist)
	{
		TRACE(_T("writing view mode to registry:  0x%X\n"), 
			m_wndListView.m_lastViewMode);

		AfxGetApp()->WriteProfileInt(PROFILE_SETTINGS, PROFILE_VIEWMODE,
			m_wndListView.m_lastViewMode);
	}

	if (m_bVistaFlag)
		m_dwRef--;
}

//=============================================================================
void CXFolderDialog::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXFolderDialog)
	DDX_Control(pDX, IDC_MRU_COMBO, m_cmbRecentFolders);
	//}}AFX_DATA_MAP
}

//=============================================================================
// DoModal override copied mostly from MFC, with modification to use
// m_ofnEx instead of m_ofn.
int CXFolderDialog::DoModal()
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::DoModal\n"));

	ASSERT_VALID(this);
	ASSERT(m_ofn.Flags & OFN_ENABLEHOOK);
	ASSERT(m_ofn.lpfnHook != NULL); // can still be a user hook

	AFX_MANAGE_STATE(AFXMANAGESTATE())

	m_bFirstTime = TRUE;

	m_wndListView.Init(this);

	// zero out the file buffer for consistent parsing later
	TCHAR * pBuf = new TCHAR [m_ofn.nMaxFile + 100];
	memset(pBuf, 0, (m_ofn.nMaxFile + 100) * sizeof(TCHAR));
	if (m_ofn.lpstrFile)
	{
		// copy file buffer
		_tcsncpy(pBuf, m_ofn.lpstrFile, m_ofn.nMaxFile);
		// zero out file buffer in OPENFILENAME struct
		memset(m_ofn.lpstrFile, 0, m_ofn.nMaxFile*sizeof(TCHAR));
		// restore copied file buffer
		_tcsncpy(m_ofn.lpstrFile, pBuf, m_ofn.nMaxFile);
	}
	if (pBuf)
		delete [] pBuf;
	pBuf = NULL;

	// WINBUG: This is a special case for the file open/save dialog,
	// which sometimes pumps while it is coming up but before it has
	// disabled the main window.
	HWND hWndFocus = ::GetFocus();
	BOOL bEnableParent = FALSE;
	m_ofn.hwndOwner = PreModal();
	AfxUnhookWindowCreate();
	if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
	{
		bEnableParent = TRUE;
		::EnableWindow(m_ofn.hwndOwner, FALSE);
	}

	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	ASSERT(pThreadState->m_pAlternateWndInit == NULL);

	if (m_ofn.Flags & OFN_EXPLORER)
		pThreadState->m_pAlternateWndInit = this;
	else
		AfxHookWindowCreate(this);

	memset(&m_ofnEx, 0, sizeof(m_ofnEx));
	memcpy(&m_ofnEx, &m_ofn, sizeof(m_ofn));
	if (m_ofnEx.hInstance == 0)
		m_ofnEx.hInstance = AfxGetInstanceHandle();

	m_ofnEx.Flags |= OFN_ENABLESIZING;

#if (_WIN32_WINNT >= 0x0500)

	TRACE(_T("_WIN32_WINNT=0x%X\n"), _WIN32_WINNT);

	#pragma message(__FILE__ "(" makestring(__LINE__) \
		") : OPENFILENAME is large size (3 extra items are included)")

	if (IsWin2000())
		m_ofnEx.lStructSize = sizeof(OPENFILENAME);				// OS >= 2000, force to large size
	else
		m_ofnEx.lStructSize = OPENFILENAME_SIZE_VERSION_400;	// use small size

#else	// _WIN32_WINNT < 0x0500, or isn't defined

	#pragma message(__FILE__ "(" makestring(__LINE__) \
		") : OPENFILENAME is small size (3 extra items are NOT included)")

	if (IsWin2000())
		m_ofnEx.lStructSize = sizeof(OPENFILENAMEEX_FOLDER);			// OS >= 2000, force to large size
	else
		m_ofnEx.lStructSize = OPENFILENAME_SIZE_VERSION_400;	// use small size

#endif

	m_ofnEx.lpstrInitialDir = m_strInitialFolder;

	int nResult = 0;
	if (m_bOpenFileDialog)
		nResult = ::GetOpenFileName((OPENFILENAME*)&m_ofnEx);
	else
		nResult = ::GetSaveFileName((OPENFILENAME*)&m_ofnEx);

	memcpy(&m_ofn, &m_ofnEx, sizeof(m_ofn));
	m_ofn.lStructSize = sizeof(m_ofn);

	if (nResult)
	{
		ASSERT(pThreadState->m_pAlternateWndInit == NULL);
	}
	pThreadState->m_pAlternateWndInit = NULL;

	// WINBUG: Second part of special case for file open/save dialog.
	if (bEnableParent)
		::EnableWindow(m_ofnEx.hwndOwner, TRUE);
	if (::IsWindow(hWndFocus))
		::SetFocus(hWndFocus);

	PostModal();

	return nResult ? nResult : IDCANCEL;
}

//=============================================================================
BOOL CXFolderDialog::OnInitDialog()
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::OnInitDialog\n"));

	CFileDialog::OnInitDialog();

	// load folder history - check if valid folder
	m_cmbRecentFolders.SetMaxHistoryItems(50);
	m_cmbRecentFolders.SetDropSize(20);
	m_cmbRecentFolders.SetCheckAccess(TRUE);
	m_cmbRecentFolders.LoadHistory(_T("FolderHistory"), _T("Folder"));

	CString str;
	if (m_cmbRecentFolders.GetCount() > 0)
	{
		m_cmbRecentFolders.GetLBText(0, str);
		m_cmbRecentFolders.SetWindowText(str);
	}

	CWnd *pWndParent = GetParent();
	ASSERT(pWndParent && IsWindow(pWndParent->m_hWnd));

	// save left margin for combo boxes
	CWnd *pWndFileNameCombo = pWndParent->GetDlgItem(m_nIdFileNameCombo);
	if (!pWndFileNameCombo)
	{
		// the File Name control ID is either 1148 or 1152, depending on whether
		// it is used as an edit box (1152) or a combo box (1148).  If the OS
		// version is < 5, it is 1152; if >= 5, it is 1148.  It will also be
		// 1152 if the registry key
		//    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\comdlg32\NoFileMru
		// is set to 1.  For convenience, we will always refer to this control
		// as a combobox.
		m_nIdFileNameCombo = 1152;
		pWndFileNameCombo = pWndParent->GetDlgItem(m_nIdFileNameCombo);
	}

	CRect rect;

	CWnd *pWndFileNameStatic = pWndParent->GetDlgItem(m_nIdFileNameStatic);
	ASSERT(pWndFileNameStatic);
	if (pWndFileNameStatic)
	{
		pWndFileNameStatic->GetWindowRect(&rect);
		pWndParent->ScreenToClient(&rect);
		m_nStaticLeftMargin = rect.left;
	}
	else
	{
		m_nStaticLeftMargin = 60;
	}

	// set title if specified
	if (m_strTitle.IsEmpty())
		pWndParent->SetWindowText(_T("Select Folder"));
	else
		pWndParent->SetWindowText(m_strTitle);

	static BOOL bFirstTime = TRUE;
	if (bFirstTime)
	{
		bFirstTime = FALSE;
		CToolBarCtrl *ptb = (CToolBarCtrl *) pWndParent->GetDlgItem(m_nIdPlaceBar);
		if (ptb && IsWindow(ptb->m_hWnd))
			ptb->ShowWindow(SW_HIDE);
	}

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

//=============================================================================
void CXFolderDialog::SetViewMode(int cmd)
//=============================================================================
{ 
	TRACE(_T("in CXFolderDialog::SetViewMode:  0x%X\n"), cmd);

	m_nViewMode = cmd;

	if (m_nViewMode == -1)
	{
		m_bUseRegistry = FALSE;
		m_bPersist     = FALSE;
	}
	else //if (m_nViewMode == 0)
	{
		m_bUseRegistry = TRUE;
		m_bPersist     = TRUE;
	}
}

//=============================================================================
// OnSize - position and size controls on default and new dialogs
void CXFolderDialog::OnSize(UINT nType, int cx, int cy)
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::OnSize:  cx=%d  cy=%d\n"), cx, cy);

	CFileDialog::OnSize(nType, cx, cy);

	// original dialog box
	CWnd *pWndParent = GetParent();
	if ((pWndParent == NULL) || (!::IsWindow(pWndParent->m_hWnd)))
		return;

	CRect rectNoWhere(10000, 10000, 10001, 10001);

	// File name combobox
	CWnd *pWndFileNameCombo = pWndParent->GetDlgItem(m_nIdFileNameCombo);
	if (pWndFileNameCombo && ::IsWindow(pWndFileNameCombo->m_hWnd))
	{
		pWndFileNameCombo->MoveWindow(&rectNoWhere);
		pWndFileNameCombo->EnableWindow(FALSE);
	}

	// File name static
	CWnd *pWnd = pWndParent->GetDlgItem(m_nIdFileNameStatic);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->MoveWindow(&rectNoWhere);
		pWnd->EnableWindow(FALSE);
	}

	// Files of type combobox
	pWnd = pWndParent->GetDlgItem(m_nIdFilesOfTypeCombo);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->MoveWindow(&rectNoWhere);
		pWnd->EnableWindow(FALSE);
	}

	// Files of type static
	pWnd = pWndParent->GetDlgItem(m_nIdFilesOfTypeStatic);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->MoveWindow(&rectNoWhere);
		pWnd->EnableWindow(FALSE);
	}

	CRect rectOK;
	CWnd *pWndOK = pWndParent->GetDlgItem(1);
	if (pWndOK && ::IsWindow(pWndOK->m_hWnd))
	{
		pWndOK->GetWindowRect(&rectOK);
		pWndParent->ScreenToClient(&rectOK);
		pWndOK->ShowWindow(SW_HIDE);
	}

	CWnd *pWndOkButton = GetDlgItem(IDOK);
	if (pWndOkButton && ::IsWindow(pWndOkButton->m_hWnd))
	{
		pWndOkButton->MoveWindow(&rectOK);
	}

	// Folder name static
	CRect rectRecentFoldersStatic;
	int h = 0;
	int w = 0;
	pWnd = GetDlgItem(IDC_MRU_CAPTION);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->GetWindowRect(&rectRecentFoldersStatic);
		pWndParent->ScreenToClient(&rectRecentFoldersStatic);
		h = rectRecentFoldersStatic.Height();
		w = rectRecentFoldersStatic.Width();
		rectRecentFoldersStatic.left   = m_nStaticLeftMargin;
		rectRecentFoldersStatic.right  = rectRecentFoldersStatic.left + w;
		rectRecentFoldersStatic.top    = rectOK.top + 2;
		rectRecentFoldersStatic.bottom = rectRecentFoldersStatic.top + h;
		pWnd->MoveWindow(&rectRecentFoldersStatic);
	}

	// Folder name combobox
	CRect rectRecentFoldersCombo;
	pWnd = GetDlgItem(IDC_MRU_COMBO);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->GetWindowRect(&rectRecentFoldersCombo);
		pWndParent->ScreenToClient(&rectRecentFoldersCombo);
		w = rectRecentFoldersCombo.Width();
		h = rectRecentFoldersCombo.Height();
		rectRecentFoldersCombo.left   = rectRecentFoldersStatic.right + 2;
		rectRecentFoldersCombo.right  = rectOK.left - 6;
		rectRecentFoldersCombo.top    = rectOK.top;
		rectRecentFoldersCombo.bottom = rectRecentFoldersCombo.top + h;
		pWnd->MoveWindow(&rectRecentFoldersCombo);
	}

	CRect rectCancelWindow, rectCancelClient;
	pWnd = pWndParent->GetDlgItem(2);
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->GetWindowRect(&rectCancelClient);
		rectCancelWindow = rectCancelClient;
		pWndParent->ScreenToClient(&rectCancelClient);
	}

	// Place bar
	pWnd = pWndParent->GetDlgItem(m_nIdPlaceBar);

	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		CRect rectPlaceBar;
		pWnd->GetWindowRect(&rectPlaceBar);
		pWndParent->ScreenToClient(&rectPlaceBar);
		rectPlaceBar.bottom = rectCancelClient.bottom;
		pWnd->MoveWindow(&rectPlaceBar);
	}

	// Dialog
	CRect rectDialog;
	pWndParent->GetWindowRect(&rectDialog);
	rectDialog.bottom = rectCancelWindow.bottom + rectCancelWindow.Height()/2 + 3;
	rectDialog.right  = rectCancelWindow.right + 10;
	pWndParent->MoveWindow(&rectDialog);

	///////////////////////////////////////////////////////////////////////////
	// following code is necessary to prevent having the
	// recent folders combobox highlighted
	static BOOL bFirstTime = TRUE;
	if (bFirstTime)
	{
		bFirstTime = FALSE;
		m_cmbRecentFolders.SetFocus();
		SetTimer(1, 20, NULL);		// ensure all placebar buttons are visible
	}
	else
	{
		m_cmbRecentFolders.SetEditSel(-1, 0);
		pWndFileNameCombo->SetFocus();
	}
}

//=============================================================================
CString CXFolderDialog::GetPath(UINT nMessage)
//=============================================================================
{
	CString strPath = _T("");

	CWnd *pWnd = GetParent();

	if (pWnd && IsWindow(pWnd->m_hWnd))
	{
		TCHAR szDir[MAX_PATH*3];
		szDir[0] = _T('\0');
		pWnd->SendMessage(nMessage, sizeof(szDir)/sizeof(TCHAR)-2,
			(LPARAM)(LPCTSTR)szDir);
		szDir[sizeof(szDir)/sizeof(TCHAR)-1] = _T('\0');
		strPath = szDir;
	}

	return strPath;
}

//=============================================================================
// OnNotify - when the open dialog sends a notification, copy m_ofnEx to m_ofn
// in case handler function is expecting updated information in the
// OPENFILENAME struct.
//
BOOL CXFolderDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::OnNotify\n"));

	memcpy(&m_ofn, &m_ofnEx, sizeof(m_ofn));
	m_ofn.lStructSize = sizeof(m_ofn);

	NMHDR * pNmhdr = (NMHDR *) lParam;

	if (pNmhdr->code == CDN_SELCHANGE)
	{
		TRACE(_T("XFolderDialog::OnNotify() CDN_SELCHANGE ===============\n"));
		
		m_strPath = GetPath(CDM_GETFILEPATH);
		if (!m_strPath.IsEmpty())
			m_cmbRecentFolders.SetWindowText(m_strPath);
		TRACE(_T("m_strPath=%s\n"), m_strPath);
	}
	else if (pNmhdr->code == CDN_FOLDERCHANGE)
	{
		TRACE(_T("XFolderDialog::OnNotify() CDN_FOLDERCHANGE ===============\n"));

		m_strPath = GetPath(CDM_GETFOLDERPATH);
		if (!m_strPath.IsEmpty())
			m_cmbRecentFolders.SetWindowText(m_strPath);
		TRACE(_T("m_strPath=%s\n"), m_strPath);

		TRACE(_T("m_bPersist=%d -----\n"), m_bPersist);

		if (m_bPersist)
		{
			if (m_wndListView.m_hWnd && IsWindow(m_wndListView.m_hWnd))
				m_wndListView.UnsubclassWindow();							// unsubclass myself

			m_wndListView.m_hWnd = 0;

			VERIFY(m_wndListView.SubclassDlgItem(lst2, GetParent()));

			if (m_bFirstTime) 
			{ 
				TRACE(_T("first-time init: %d\n"), m_bUseRegistry);
				// if first-time init:
				// Set view mode based on value saved in profile settings.
				if (m_bUseRegistry && (m_nViewMode == 0))
				{
					m_nViewMode = AfxGetApp()->GetProfileInt(PROFILE_SETTINGS, PROFILE_VIEWMODE, 0);
					TRACE(_T("reading view mode from registry:  0x%X\n"), m_nViewMode);
				}
				m_bFirstTime = FALSE;
			}
			TRACE(_T("setting view mode to 0x%X\n"), m_nViewMode);
			m_wndListView.SetViewMode(m_nViewMode);
		}
	}

	return CFileDialog::OnNotify(wParam, lParam, pResult);
}

//=============================================================================
void CXFolderDialog::OnOK()
//=============================================================================
{
	TRACE(_T("CXFolderDialog::OnOK: m_strPath=%s\n"), m_strPath);

	m_strPath = GetPath(CDM_GETFILEPATH);
	if (!m_strPath.IsEmpty())
		m_cmbRecentFolders.SetWindowText(m_strPath);
	else
		m_cmbRecentFolders.GetWindowText(m_strPath);
	TRACE(_T("m_strPath=%s\n"), m_strPath);

	if (m_strPath.IsEmpty())
	{
		AfxMessageBox(_T("Please select a folder."));
		return;
	}
	else if (_taccess(m_strPath, 00) == -1)
	{
		CString strMessage = _T("");
		strMessage.Format(_T("The folder '%s' isn't accessible."), m_strPath);
		AfxMessageBox(strMessage);
		return;
	}

	m_cmbRecentFolders.SaveHistory(TRUE);

	((CDialog*)GetParent())->EndDialog(IDOK);
}

//=============================================================================
void CXFolderDialog::OnSelendokMruCombo()
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::OnSelendokMruCombo\n"));

	if (!::IsWindow(m_cmbRecentFolders.m_hWnd))
		return;

	CString strFolder = _T("");

	int index = m_cmbRecentFolders.GetCurSel();

	if (index >= 0)
	{
		m_cmbRecentFolders.GetLBText(index, strFolder);

		if (!strFolder.IsEmpty() && (_taccess(strFolder, 00) == 0))
		{
			CWnd *pWnd = GetParent();
			if ((pWnd != NULL) && ::IsWindow(pWnd->m_hWnd))
			{
				// change to new folder, leave file name control unchanged
				TCHAR szText[_MAX_PATH*2];
				szText[0] = _T('\0');
				pWnd->GetDlgItem(m_nIdFileNameCombo)->SendMessage(WM_GETTEXT,
								sizeof(szText)/sizeof(TCHAR)-2, (LPARAM)szText);
				pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
								(LPARAM)(LPCTSTR)strFolder);
				pWnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED),
								(LPARAM)GetDlgItem(IDOK)->GetSafeHwnd());
				pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
								(LPARAM)szText);
			}
		}
	}
}

//=============================================================================
void CXFolderDialog::OnCbnKillfocusMruCombo()
//=============================================================================
{
	CString strFolder = _T("");
	m_cmbRecentFolders.GetWindowText(strFolder);
	
	if (!strFolder.IsEmpty() && (_taccess(strFolder, 00) == 0))
	{
		CWnd *pWnd = GetParent();
		if (pWnd && ::IsWindow(pWnd->m_hWnd))
		{
			// change to new folder, leave file name control unchanged
			TCHAR szText[MAX_PATH*2];
			szText[0] = _T('\0');
			pWnd->GetDlgItem(m_nIdFileNameCombo)->SendMessage(WM_GETTEXT,
				sizeof(szText)/sizeof(TCHAR)-2, (LPARAM)szText);
			pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
				(LPARAM)(LPCTSTR)strFolder);
			pWnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED),
				(LPARAM)GetDlgItem(IDOK)->GetSafeHwnd());
			pWnd->SendMessage(CDM_SETCONTROLTEXT, m_nIdFileNameCombo,
				(LPARAM)szText);
			
			m_strPath = strFolder;
		}
	}
}

//=============================================================================
BOOL CXFolderDialog::IsWin2000()
//=============================================================================
{
	if (GetOsVersion() == XFILEDIALOG_OS_VERSION_4)
		return FALSE;
	else if (GetOsVersion() == XFILEDIALOG_OS_VERSION_5)
		return TRUE;

	// auto detect
	if (Is2000OrGreater())
		return TRUE;

	return FALSE;
}

//=============================================================================
// OnTimer - adjust dialog size so placebar fits
void CXFolderDialog::OnTimer(UINT nIDEvent)
//=============================================================================
{
	KillTimer(nIDEvent);

	if (nIDEvent == 1)
	{
		CWnd *pWndParent = GetParent();
		if (pWndParent && IsWindow(pWndParent->m_hWnd))
		{
			CRect rectPlaceBar;
			CWnd *pWnd = pWndParent->GetDlgItem(m_nIdPlaceBar);

			if (pWnd && IsWindow(pWnd->m_hWnd))
			{
				pWnd->GetWindowRect(&rectPlaceBar);

				CToolBarCtrl *ptb = (CToolBarCtrl *) pWndParent->GetDlgItem(m_nIdPlaceBar);

				if (ptb && IsWindow(ptb->m_hWnd))
				{
					int nCount = ptb->GetButtonCount();

					DWORD dwSize = ptb->GetButtonSize();
					UINT nButtonHeight = HIWORD(dwSize);

					int nMinHeight = nCount * nButtonHeight + 2;

					CRect rectDialog;
					pWndParent->GetWindowRect(&rectDialog);

					if ((rectPlaceBar.Height() < nMinHeight) &&
						(nMinHeight < GetSystemMetrics(SM_CYSCREEN)))	// might not work on multiple monitors
					{
						// adjust dialog so all buttons are visible
						rectDialog.bottom += nMinHeight - rectPlaceBar.Height();
						pWndParent->MoveWindow(&rectDialog);
					}

					ptb->ShowWindow(SW_SHOW);
				}
			}
		}
		SetFocus();		// set focus back to dialog
	}

	CFileDialog::OnTimer(nIDEvent);
}

//=============================================================================
void CXFolderDialog::OnDestroy() 
//=============================================================================
{
	TRACE(_T("in CXFolderDialog::OnDestroy\n"));
	m_nViewMode = m_wndListView.m_lastViewMode;
	CFileDialog::OnDestroy();
}
