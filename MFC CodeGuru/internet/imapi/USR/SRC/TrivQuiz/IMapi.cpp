/*
 *	$Header:$
 *
 *	$Log:$
 */
#include "stdafx.h"
#include <mapi.h>
#include "imapi.h"

HINSTANCE CIMapi::m_hInstMail = (HINSTANCE) NULL;
BOOL	  CIMapi::m_isMailAvail = (BOOL) -1;

CIMapi::CIMapi()
{
	m_error = 0;										//	Initially error free

	memset(&m_message, 0, sizeof(MapiMessage));
	memset(&m_from, 0, sizeof(MapiRecipDesc));
	m_message.lpOriginator = &m_from;
	m_from.ulRecipClass = MAPI_ORIG;

	if (m_hInstMail == (HINSTANCE) NULL)				//	Load the MAPI dll
		m_hInstMail = ::LoadLibraryA("MAPI32.DLL");

	if (m_hInstMail == (HINSTANCE) NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
		m_error = IMAPI_LOADFAILED;
		return;
	}

	ASSERT(m_hInstMail != (HINSTANCE) NULL);			//	Now get the pointer to the send function
	(FARPROC&) m_lpfnSendMail = GetProcAddress(m_hInstMail, "MAPISendMail");

	if (m_lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
		m_error = IMAPI_INVALIDDLL;
		return;
	}

	ASSERT(m_lpfnSendMail != NULL);
}

CIMapi::~CIMapi()
{
	if (m_hInstMail != (HINSTANCE) NULL)
		::FreeLibrary(m_hInstMail);

	m_hInstMail = (HINSTANCE) NULL;
	
	free(m_message.lpFiles);
	free(m_message.lpRecips);
}

BOOL CIMapi::HasEmail()
{
	if (m_isMailAvail == (BOOL) -1)
		m_isMailAvail = ::GetProfileInt(_T("MAIL"), _T("MAPI"), 0) != 0 && SearchPath(NULL, _T("MAPI32.DLL"), NULL, 0, NULL, NULL) != 0;

	return m_isMailAvail;
}

UINT CIMapi::Error()
{
	UINT temp = m_error;

	m_error = IMAPI_SUCCESS;
	return temp;
}

BOOL CIMapi::AllocNewTo()
{
	//	Allocate a new MapiRecipDesc structure and initialise it to all zeros
	m_message.lpRecips = (MapiRecipDesc *) realloc(m_message.lpRecips, (m_message.nRecipCount + 1) * sizeof(MapiRecipDesc));
	memset(&m_message.lpRecips[m_message.nRecipCount], 0, sizeof(MapiRecipDesc));

	ASSERT(m_message.lpRecips);
	return m_message.lpRecips != (MapiRecipDesc *) NULL;
}

BOOL CIMapi::To(LPCTSTR recip)
{
	if (AllocNewTo())
	{
		//	We succeeded in allocating a new recipient record
		m_message.lpRecips[m_message.nRecipCount].lpszName = (LPTSTR) recip;
		m_message.lpRecips[m_message.nRecipCount].ulRecipClass = MAPI_TO;
		m_message.nRecipCount++;
		return TRUE;
	}

	m_error = IMAPI_FAILTO;
	return FALSE;
}

BOOL CIMapi::Cc(LPCTSTR recip)
{
	if (AllocNewTo())
	{
		//	We succeeded in allocating a new recipient record
		m_message.lpRecips[m_message.nRecipCount].lpszName = (LPTSTR) recip;
		m_message.lpRecips[m_message.nRecipCount].ulRecipClass = MAPI_CC;
		m_message.nRecipCount++;
		return TRUE;
	}

	m_error = IMAPI_FAILCC;
	return FALSE;
}

BOOL CIMapi::Attach(LPCTSTR path, LPCTSTR name)
{
	//	Add a new attachment record
	m_message.lpFiles = (MapiFileDesc *) realloc(m_message.lpFiles, (m_message.nFileCount + 1) * sizeof(MapiFileDesc));
	memset(&m_message.lpFiles[m_message.nFileCount], 0, sizeof(MapiFileDesc));

	ASSERT(m_message.lpFiles);
	
	if (m_message.lpFiles == (MapiFileDesc *) NULL)
	{
		m_error = IMAPI_FAILATTACH;
		return FALSE;
	}

	m_message.lpFiles[m_message.nFileCount].lpszPathName = (LPTSTR) path;
	m_message.lpFiles[m_message.nFileCount].lpszFileName = (LPTSTR) name;
	m_message.nFileCount++;
	return TRUE;
}

BOOL CIMapi::Send(ULONG flags)
{
	CWaitCursor wait;
	int			offset = m_text.GetLength();

	//	Add 1 space per attachment at the end of the body text.
	m_text += CString(' ', m_message.nFileCount);

	//	Set each attachment to replace one of the added spaces at the end of the body text.
	for (UINT i = 0; i < m_message.nFileCount; i++)
		m_message.lpFiles[i].nPosition = offset++;

	m_message.lpszNoteText = (LPTSTR) (LPCTSTR) m_text;	//  Set the body text

	// prepare for modal dialog box
	AfxGetApp()->EnableModeless(FALSE);
	HWND hWndTop;
	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

	// some extra precautions are required to use MAPISendMail as it
	// tends to enable the parent window in between dialogs (after
	// the login dialog, but before the send note dialog).
	pParentWnd->SetCapture();
	::SetFocus(NULL);
	pParentWnd->m_nFlags |= WF_STAYDISABLED;

	int nError = m_lpfnSendMail(0, (ULONG) pParentWnd->GetSafeHwnd(), &m_message, MAPI_LOGON_UI | flags, 0);

	// after returning from the MAPISendMail call, the window must
	// be re-enabled and focus returned to the frame to undo the workaround
	// done before the MAPI call.
	::ReleaseCapture();
	pParentWnd->m_nFlags &= ~WF_STAYDISABLED;

	pParentWnd->EnableWindow(TRUE);
	::SetActiveWindow(NULL);
	pParentWnd->SetActiveWindow();
	pParentWnd->SetFocus();
	
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	
	AfxGetApp()->EnableModeless(TRUE);

	if (nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
		return FALSE;
	}

	return TRUE;
}
