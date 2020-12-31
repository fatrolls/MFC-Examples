// ==========================================================================
//      Class Implementation : COXSendMail
// ==========================================================================

// Source file : SendMail.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"  // standard MFC include
#include "OXSendMail.h"

#pragma warning(disable: 4228)
#include <mapi.h>
#include <mapix.h>
#include <mapiwin.h>
#include <mapiutil.h>

#define USES_IID_IMAPIFolder
#define INITGUID
#include <initguid.h>
#include <mapiguid.h>
#pragma warning(default: 4228)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COXSendMail::CMessage::CMessage()
{
}

COXSendMail::CMessage::~CMessage()
{
	int i;
	
	for (i=0 ; i<m_recipients.GetSize() ; i++)
		delete m_recipients[i];
	for (i=0 ; i<m_attachments.GetSize() ; i++)
		delete m_attachments[i];
}

void COXSendMail::CMessage::AddRecipient(CString sRecipient, ERecipientType eType)
{
	SRecipient* pRecipient = new SRecipient;
	
	pRecipient->sName = sRecipient;
	pRecipient->eType = eType;
	m_recipients.Add(pRecipient);
}

void COXSendMail::CMessage::AddAttachment(CString sAttachment, EAttachmentType eType, CString sOleDocument /*= _T("")*/)
{
	SAttachment* pAttachment = new SAttachment;
	
	pAttachment->sPath = sAttachment;
	pAttachment->eType = eType;
	pAttachment->sOleDocument = sOleDocument;
	m_attachments.Add(pAttachment);
}


#ifndef OX_MAPI_DIRECT

COXSendMail::COXSendMail()
{
}

COXSendMail::~COXSendMail()
{
	if (IsInitialized())
	Uninitialize();
}


BOOL COXSendMail::Initialize(CString sProfileName, CString sPassword)
{
	ASSERT_VALID(this);

	LPMAPISESSION	pMAPISession;       
	HRESULT			hResult;
	BOOL			bMAPIInitialized = FALSE;
	BOOL			bResult = TRUE;

	TRY
	{
		MAPIINIT_0 MAPIINIT = { 0, MAPI_NT_SERVICE | MAPI_MULTITHREAD_NOTIFICATIONS }; 
		hResult = MAPIInitialize(&MAPIINIT);
		if (FAILED (hResult))
			return FALSE;

		bMAPIInitialized = TRUE;

		hResult = MAPILogonEx(
						(ULONG)NULL,
						sProfileName.GetBuffer(256),
						sPassword.GetBuffer(256),
						MAPI_LOGON_UI | MAPI_NO_MAIL | MAPI_EXTENDED | MAPI_EXPLICIT_PROFILE | MAPI_NEW_SESSION,
						&pMAPISession);

		sProfileName.ReleaseBuffer();
		sPassword.ReleaseBuffer();

		if (FAILED (hResult))
		{
			MAPIUninitialize();
			return FALSE;
		}
		
		if (m_objSession.m_lpDispatch == NULL)
		{
			if (m_objSession.CreateDispatch(_T("MAPI.Session")) == FALSE)
			{
				MAPIUninitialize();
				bResult = FALSE;
			}
		}
		if (bResult)
			m_objSession.SetMapiobject(pMAPISession);
	}
	CATCH_ALL(e)
	{
		if (bMAPIInitialized)
			MAPIUninitialize();
		bResult = FALSE;
	}
	END_CATCH_ALL

	if (bResult)
		m_sMAPIProfile = sProfileName;
	return bResult;
}

BOOL COXSendMail::IsInitialized()
{
	if (m_objSession.m_lpDispatch)
		if (m_objSession.GetMapiobject() != NULL)
			return TRUE;
	return FALSE;
}

void COXSendMail::Uninitialize()
{
	TRY
	{
		ASSERT(m_objSession.m_lpDispatch);
		if (m_objSession.m_lpDispatch)
			m_objSession.Logoff();
	}
	CATCH_ALL(e)
	{
	}
	END_CATCH_ALL
	m_objSession.ReleaseDispatch();
	MAPIUninitialize();
}

CString COXSendMail::GetProfile()
{
	CString sProfile;

	if (IsInitialized())
		sProfile = m_sMAPIProfile;
	return sProfile;
}

BOOL COXSendMail::SendMessage(CMessage& message)
{
    COXMMessage objMessage;
    COXMRecipient objOneRecip;
	COXMAttachment objAttachment;
	ASSERT(m_objSession.m_lpDispatch);

	if (m_objSession.m_lpDispatch == NULL)
		return FALSE;

	TRY
	{
		// create new message and set subject and content
		objMessage = m_objSession.GetOutbox().GetMessages().Add();
		objMessage.SetSubject(message.m_sSubject);
		objMessage.SetText(message.m_sContent);

		// set the recipients
		for (int i=0 ; i<message.m_recipients.GetSize() ; i++)
		{
			objOneRecip = objMessage.GetRecipients().Add();
			objOneRecip.SetName(message.m_recipients[i]->sName);
			switch (message.m_recipients[i]->eType)
			{
			case rtCC:
				objOneRecip.SetType(oxmrtCc);
				break;
			case rtBCC:
				objOneRecip.SetType(oxmrtBcc);
				break;
			default:
				objOneRecip.SetType(oxmrtTo);
			}
		    objOneRecip.Resolve(FALSE);
		}

		// add the attachments
		for (i=0 ; i<message.m_attachments.GetSize() ; i++)
		{
			CString sAttachment;
			TCHAR pszDrive[_MAX_DRIVE];
			TCHAR pszSubdir[_MAX_DIR];
			TCHAR pszBaseName[_MAX_FNAME];
			TCHAR pszExtender[_MAX_EXT];

			sAttachment = message.m_attachments[i]->sPath;
			_tsplitpath(sAttachment, pszDrive, pszSubdir, pszBaseName, pszExtender);
			_tmakepath(sAttachment.GetBuffer(_MAX_PATH), NULL, NULL, pszBaseName, pszExtender);
			sAttachment.ReleaseBuffer();

			objAttachment = objMessage.GetAttachments().Add(sAttachment);
			objAttachment.SetName(sAttachment);
			objAttachment.SetType((EOXMAttachmentType) message.m_attachments[i]->eType);
			objAttachment.ReadFromFile(message.m_attachments[i]->sPath);
		}

		// send the message
		objMessage.Send();
	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;

}

#endif



CString COXSendMail::GetReturnMsg(int nErr)
{
	CString sErrorMsg;
	switch(nErr)
	{
		case SUCCESS_SUCCESS:
			sErrorMsg = _T("Sending of Mail was succesful");
			break;
		case MAPI_E_USER_ABORT:
			sErrorMsg = _T("Sending of Mail has been aborted by user");
			break;
		case MAPI_E_FAILURE:
			sErrorMsg = _T("Sending of Mail was not succesful");
			break;
		case MAPI_E_LOGIN_FAILURE:
			sErrorMsg = _T("login failure");
			break;
		case MAPI_E_DISK_FULL:
			sErrorMsg = _T("Disk full");
			break;
		case MAPI_E_INSUFFICIENT_MEMORY:
			sErrorMsg = _T("not enough memory");
			break;
		case MAPI_E_ACCESS_DENIED:
			sErrorMsg = _T("access denied");
			break;
		case MAPI_E_TOO_MANY_SESSIONS:
			sErrorMsg = _T("too many sessions open");
			break;
		case MAPI_E_TOO_MANY_FILES:
			sErrorMsg = _T("too many open files");
			break;
		case MAPI_E_TOO_MANY_RECIPIENTS:
			sErrorMsg = _T("too many recipients specified");
			break;
		case MAPI_E_ATTACHMENT_NOT_FOUND:
			sErrorMsg = _T("attachment not found");
			break;
		case MAPI_E_ATTACHMENT_OPEN_FAILURE:
			sErrorMsg = _T("could not open attachment");
			break;
		case MAPI_E_ATTACHMENT_WRITE_FAILURE:
			sErrorMsg = _T("could not write attachment");
			break;
		case MAPI_E_UNKNOWN_RECIPIENT:
			sErrorMsg = _T("unknown recipient");
			break;
		case MAPI_E_BAD_RECIPTYPE:
			sErrorMsg = _T("unknown reciptype");
			break;
		case MAPI_E_NO_MESSAGES:
			sErrorMsg = _T("no messages");
			break;
		case MAPI_E_INVALID_MESSAGE:
			sErrorMsg = _T("invalid message");
			break;
		case MAPI_E_TEXT_TOO_LARGE:
			sErrorMsg = _T("text too large");
			break;
		case MAPI_E_INVALID_SESSION:
			sErrorMsg = _T("invalid session");
			break;
		case MAPI_E_TYPE_NOT_SUPPORTED:
			sErrorMsg = _T("type not supported");
			break;
		case MAPI_E_AMBIG_RECIP:
			sErrorMsg = _T("ambiguous recipiebt");
			break;
		case MAPI_E_MESSAGE_IN_USE:
			sErrorMsg = _T("message in use");
			break;
		case MAPI_E_NETWORK_FAILURE:
			sErrorMsg = _T("network failure");
			break;
		case MAPI_E_INVALID_EDITFIELDS:
			sErrorMsg = _T("invalid editfields");
			break;
		case MAPI_E_INVALID_RECIPS:
			sErrorMsg = _T("invalid recipients");
			break;
		case MAPI_E_NOT_SUPPORTED:
			sErrorMsg = _T("not supported request");
			break;
		default:
			sErrorMsg = _T("unknown error");
			break;
	}
	
	return sErrorMsg;
}






/////////////////////////////////////////////////////////////////////////////
// The Extended MAPI alternative



#ifdef OX_MAPI_DIRECT
/////////////////////////////////////////////////////////////////////////////
// MAPI implementation helpers and globals

#define _countof(array)  (sizeof(array)/sizeof(array[0]))

static BOOL IsMailAvail = (BOOL)-1;    // start out not determined

// _AFX_MAIL_STATE

class OX_CLASS_DECL _AFX_MAIL_STATE : public CNoTrackObject
{
public:
	HINSTANCE m_hInstMail;      // handle to MAPI32.DLL
	virtual ~_AFX_MAIL_STATE();
};

_AFX_MAIL_STATE::~_AFX_MAIL_STATE()
{
	if (m_hInstMail != NULL)
		::FreeLibrary(m_hInstMail);
}

_AFX_MAIL_STATE* _afxMailState;
int nCount = 0;



COXSendMail::COXSendMail() :
	m_pMAPISession(NULL),
	m_pAddressBook(NULL),
	m_peidDefaultMDB(NULL),
	m_cbeidDefaultMDB(0),
	m_pDefaultMDB(NULL),
	m_pRootFolder(NULL),
	m_szRecipient(NULL),
	m_uLogoffFlags(LOGOFF_ORDERLY),
	m_szAttachData(NULL)
{
	if (nCount==0)
		_afxMailState = new _AFX_MAIL_STATE;
	nCount++;
}


COXSendMail::~COXSendMail()
{
	if (IsInitialized())
		Uninitialize();

	nCount--;
	if (nCount==0)
		delete _afxMailState;
}

BOOL COXSendMail::Initialize(CString sProfileName, CString sPassword)
{
	ASSERT_VALID(this);

	HRESULT hResult;

	if (IsInitialized())
		Uninitialize();
	
	// Initialize the MAPI libraries before calling ANY MAPI function
	MAPIINIT_0 MAPIINIT = { 0, MAPI_NT_SERVICE | MAPI_MULTITHREAD_NOTIFICATIONS }; 
	hResult = MAPIInitialize(&MAPIINIT);
	if (!FAILED (hResult))
	{
		// Logon onto the message subsystem. We are going to ask the user to
		// select a profile to log into. The UI for this will be provided by MAPI.
		hResult = MAPILogonEx((ULONG)NULL,
			sProfileName.GetBuffer(256),
			sPassword.GetBuffer(256),
			MAPI_NO_MAIL | MAPI_EXTENDED | MAPI_EXPLICIT_PROFILE /*| MAPI_USE_DEFAULT */| MAPI_NEW_SESSION,
			&m_pMAPISession);
		
		sProfileName.ReleaseBuffer();
		sPassword.ReleaseBuffer();

		if (!FAILED (hResult))
		{
			// get the address book
			// be sure to have the correct address book set as the default
			// see the Addressing tab in the profile config control panel applet
			hResult = m_pMAPISession->OpenAddressBook(NULL, NULL, 0, &m_pAddressBook);
			if (!FAILED(hResult))
			{
				if (InitializeMessageStore())
				{
					// get the root folder
					ULONG uObjType;
					hResult = m_pDefaultMDB->OpenEntry(0, 
													 NULL, 
													 (LPIID)&IID_IMAPIFolder, 
													 MAPI_MODIFY, 
													 &uObjType, 
													 (LPUNKNOWN *)&m_pRootFolder);
	
					if (!FAILED(hResult))
					{
						m_sMAPIProfile = sProfileName;
						return TRUE;
					}
				}
			}
		}
		Uninitialize();
	}
	else
		MAPIUninitialize();
	return FALSE;
}

BOOL COXSendMail::IsInitialized()
{
	return (m_pMAPISession!=NULL);
}

void COXSendMail::Uninitialize()
{
	if (m_pRootFolder != NULL)
	{
		m_pRootFolder->Release();
		m_pRootFolder = NULL;
	}
	
	if (m_pDefaultMDB != NULL)
	{
		m_pDefaultMDB->StoreLogoff(&m_uLogoffFlags);
		m_pDefaultMDB->Release();
		m_pDefaultMDB = NULL;
	}
	
	if (m_peidDefaultMDB != NULL)
	{
		MAPIFreeBuffer(m_peidDefaultMDB);
		m_peidDefaultMDB = NULL;
	}
	
	if (m_pAddressBook != NULL)
	{
		m_pAddressBook->Release();
		m_pAddressBook = NULL;
	}
	
	if (m_pMAPISession!=NULL)
	{
		ULONG ulUIParam = (ULONG)NULL;   // null window handle
		ULONG ulFlags =    0;
		ULONG ulReserved = 0;

		m_pMAPISession->Logoff(ulUIParam, ulFlags, ulReserved);
		m_pMAPISession->Release();
		m_pMAPISession = NULL;
		MAPIUninitialize();
	}
}

CString COXSendMail::GetProfile()
{
	CString sProfile;

	if (IsInitialized())
		sProfile = m_sMAPIProfile;
	return sProfile;
}

BOOL COXSendMail::SendMessage(CMessage& message)
{
	LPMESSAGE	pMessage;
	HRESULT		hResult;
	
	pMessage = ComposeMessage(message);
	if (pMessage == NULL)
		return FALSE;	
	
	hResult = pMessage->SubmitMessage(FORCE_SUBMIT);
		
	if (pMessage != NULL)
		pMessage->Release();

	if (FAILED(hResult))
		return FALSE;
	return TRUE;
}


// protected functions


BOOL COXSendMail::InitializeMessageStore()
{
	LPSRowSet		pRow = NULL;
	ULONG			ulRow;
	ULONG			uRowCount;
	HRESULT			hResult;
	LPMAPITABLE		pStoresTable;
	LPSPropValue	pProps;
	BOOL			bFound;
	

// The order for this enumaration must match the order of the properties
// in the tag array below
	enum
	{
		DEFAULT_STORE,    
		STORE_EID,
		MSG_STORES_TABLE_PROPS        // number columns in the proptagarray
	};
	
	SizedSPropTagArray (MSG_STORES_TABLE_PROPS, sptMsgStores) =
	{
		MSG_STORES_TABLE_PROPS,
		{
			PR_DEFAULT_STORE,
			PR_ENTRYID,
		}
	};
	
///// end of local declarations
	
	m_cbeidDefaultMDB = 0;
	m_peidDefaultMDB = NULL;
	
	
// first get a table of the message stores available
	hResult = m_pMAPISession->GetMsgStoresTable (0, &pStoresTable);
	if (FAILED(hResult))
		return FALSE;	
	
	
// we only want the default store flag and the entry id
	hResult = pStoresTable->SetColumns((LPSPropTagArray)&sptMsgStores, 0);
	if (FAILED(hResult))
		return FALSE;
	
	pStoresTable->GetRowCount(0, &uRowCount);   // one row corresponds to one MDB provider
// typically no one should have more than
// 6 or 7 MDB providers.
	
// Get row(s) from the message stores table
	hResult = pStoresTable->QueryRows(uRowCount, 0, &pRow);
	if (FAILED(hResult))
		return FALSE;
	
	bFound = FALSE;
// loop through each row -- each row represents the properties of a message store
	for (ulRow=0; ulRow<pRow->cRows; ulRow++)
	{
		pProps = pRow->aRow[ulRow].lpProps;
		
		if (pProps[DEFAULT_STORE].Value.b == 1)    // we found it!
		{
			
			m_cbeidDefaultMDB = pProps[STORE_EID].Value.bin.cb;
			hResult = MAPIAllocateBuffer(m_cbeidDefaultMDB, (LPVOID *)&m_peidDefaultMDB);
			if (FAILED(hResult))
				return FALSE;
			
			memcpy(m_peidDefaultMDB, pProps[STORE_EID].Value.bin.lpb, m_cbeidDefaultMDB);
			
			bFound = TRUE;
		}
/// else ignore the non-defaults    
	}
	
	if (bFound)
		hResult = S_OK;
	else
		hResult = MAPI_E_NOT_FOUND;
	
	
	
// clean up if neccessary
	if (pRow != NULL)
		FreeProws(pRow);
	
	if (pStoresTable != NULL)
		pStoresTable->Release();


	if (FAILED(hResult))   // there was an error
		return FALSE;	
	
// open the default message store
	m_pDefaultMDB = NULL;
	hResult = m_pMAPISession->OpenMsgStore ((ULONG)NULL,
		m_cbeidDefaultMDB,
		m_peidDefaultMDB,
		NULL,
		MDB_WRITE,
		&m_pDefaultMDB);
	if (FAILED(hResult))
		return FALSE;	
	
	return TRUE;
}

LPMESSAGE COXSendMail::ComposeMessage(CMessage& message)
{
	HRESULT		hrRet = 0;
	LPMESSAGE	pMessage = NULL;
	SPropValue	pMessageProps[5];
	LPSPropProblemArray pPropProblems;
	
	// create the message
	hrRet = m_pRootFolder->CreateMessage(NULL, 0, &pMessage);
	if (FAILED(hrRet))
		return NULL;	
	
	// setup the properties
	pMessageProps[0].ulPropTag = PR_MESSAGE_CLASS;
	pMessageProps[1].ulPropTag = PR_PRIORITY;
	pMessageProps[2].ulPropTag = PR_SUBJECT;
	pMessageProps[3].ulPropTag = PR_BODY;
	pMessageProps[4].ulPropTag = PR_CLIENT_SUBMIT_TIME;

	pMessageProps[0].Value.lpszA = "IPM.NOTE";
	pMessageProps[1].Value.l = PRIO_NORMAL;
#ifdef _UNICODE
	pMessageProps[2].Value.lpszW = message.m_sSubject.GetBuffer(message.m_sSubject.GetLength());
	pMessageProps[3].Value.lpszW = message.m_sContent.GetBuffer(message.m_sContent.GetLength());
#else
	pMessageProps[2].Value.lpszA = message.m_sSubject.GetBuffer(message.m_sSubject.GetLength());
	pMessageProps[3].Value.lpszA = message.m_sContent.GetBuffer(message.m_sContent.GetLength());
#endif
	message.m_sSubject.ReleaseBuffer();
	message.m_sContent.ReleaseBuffer();
	
	// set the message submission time
	SYSTEMTIME	tSysTime;
	FILETIME	tSubmitTime;
	GetSystemTime(&tSysTime);
	SystemTimeToFileTime(&tSysTime, &tSubmitTime);  // convert to file time
	pMessageProps[4].Value.ft = tSubmitTime;
	
	
	// set the properties
	hrRet = pMessage->SetProps(5, pMessageProps, &pPropProblems);
	if (!FAILED(hrRet))
	{
		hrRet = AddRecipients(pMessage, message.m_recipients);
		if (!FAILED(hrRet))
		{
			// Create the attachment
			AddAttachments(pMessage, message.m_attachments);
			hrRet = pMessage->SaveChanges(KEEP_OPEN_READWRITE);
		}

		if (!FAILED(hrRet))
			return pMessage;	
	}

	if (pMessage != NULL)
		pMessage->Release();

	return NULL;
}


HRESULT COXSendMail::AddRecipients(LPMESSAGE pMessage, CRecipientArray& recipients)
{
	HRESULT		hrRet;
	LPADRLIST	pAddressList;
	
// allocate address list for one recipient
	MAPIAllocateBuffer(sizeof(ADRLIST) + sizeof(ADRENTRY) * recipients.GetSize(),
		(LPVOID *) &pAddressList);
	
// set properties for address list  
	pAddressList->cEntries = recipients.GetSize();
	for (int i=0 ; i<recipients.GetSize() ; i++)
	{
		// allocate space for properties
		MAPIAllocateBuffer(sizeof(SPropValue) * 2, 
		(LPVOID *) &(pAddressList->aEntries[i].rgPropVals) );

		pAddressList->aEntries[i].cValues = 2;
		pAddressList->aEntries[i].rgPropVals[0].ulPropTag = PR_DISPLAY_NAME;
		pAddressList->aEntries[i].rgPropVals[0].Value.lpszA = recipients[i]->sName.GetBuffer(recipients[i]->sName.GetLength());
		pAddressList->aEntries[i].rgPropVals[1].ulPropTag = PR_RECIPIENT_TYPE;
		recipients[i]->sName.ReleaseBuffer();
		switch (recipients[i]->eType)
		{
		case rtTO:
			pAddressList->aEntries[i].rgPropVals[1].Value.l = MAPI_TO;
			break;
		case rtCC:
			pAddressList->aEntries[i].rgPropVals[1].Value.l = MAPI_CC;
			break;
		case rtBCC:
			pAddressList->aEntries[i].rgPropVals[1].Value.l = MAPI_BCC;
			break;
		}
	}
	
// resolve the address
	hrRet = m_pAddressBook->ResolveName(0, 0, NULL, pAddressList);
	if (!FAILED(hrRet))
	{
		// set the recipients to the message
		hrRet = pMessage->ModifyRecipients(MODRECIP_ADD, pAddressList);
	}

	for (i=0 ; i<recipients.GetSize() ; i++)
		MAPIFreeBuffer(pAddressList->aEntries[i].rgPropVals);

	MAPIFreeBuffer(pAddressList);

	return hrRet;	
}

HRESULT COXSendMail::AddAttachments(LPMESSAGE pMessage, CAttachmentArray& attachments)
{
	HRESULT hrRet;
	UINT idx;
	LPTSTR szAttachment;
	
// if there are no attachments, just return
	if (attachments.GetSize() == 0)
		return 0;
	
	enum
	{ 
		REND_POS,
		PATH_NAME,
		ATT_METHOD,
		DISP_NAME,
		ATT_FILENAME,
		ATT_DIM
	};
	
	SizedSPropTagArray(ATT_DIM , sptAttachTags) =
	{ 
		ATT_DIM,
		{ 
			PR_RENDERING_POSITION, 
			PR_ATTACH_PATHNAME,
			PR_ATTACH_METHOD, 
			PR_DISPLAY_NAME, 
			PR_ATTACH_FILENAME 
		}
	};
	SPropValue spvAttachProps[ATT_DIM];
	
	
	CString sAttachment;

	for (int i=0 ; i<attachments.GetSize() ; i++)
	{
		sAttachment = attachments[i]->sPath;
		
		LPATTACH lpAttach = NULL;
		ULONG ulAttachNum = 0;
		
		hrRet = pMessage->CreateAttach(NULL, 0, &ulAttachNum, &lpAttach);
		if (FAILED(hrRet))
			return hrRet;
		
		for(idx = 0; idx < ATT_DIM; ++idx)
		{
			spvAttachProps[idx].ulPropTag = sptAttachTags.aulPropTag[idx];
			spvAttachProps[idx].dwAlignPad = 0;
		}
		
		
// Split the path of the attachment, so we can extract the filename
// to display under the attachment
		TCHAR pszDrive[_MAX_DRIVE];
		TCHAR pszSubdir[_MAX_DIR];
		TCHAR pszBaseName[_MAX_FNAME];
		TCHAR pszExtender[_MAX_EXT];
		TCHAR pszFileName[_MAX_FNAME + _MAX_EXT];
		
		szAttachment = sAttachment.GetBuffer(_MAX_PATH);

		_tsplitpath(szAttachment, pszDrive, pszSubdir, pszBaseName, pszExtender);
		_tmakepath(pszFileName, NULL, NULL, pszBaseName, pszExtender);
		
		spvAttachProps[REND_POS].Value.l = -1;
		spvAttachProps[PATH_NAME].Value.LPSZ = szAttachment;
		spvAttachProps[ATT_METHOD].Value.l = ATTACH_BY_REF_RESOLVE;
//		spvAttachProps[ATT_METHOD].Value.l = ATTACH_BY_VALUE;
		spvAttachProps[DISP_NAME].Value.LPSZ = pszFileName;
		spvAttachProps[ATT_FILENAME].Value.LPSZ = pszFileName;
		
		hrRet = lpAttach->SetProps(ATT_DIM, spvAttachProps, NULL);
		if (FAILED(hrRet))
		{
			sAttachment.ReleaseBuffer();
			return hrRet;
		}
		
		hrRet = lpAttach->SaveChanges(KEEP_OPEN_READWRITE);

		sAttachment.ReleaseBuffer();
		if (FAILED(hrRet))
			return hrRet;
		
		szAttachment = NULL;
		UlRelease(lpAttach);
	}
	
	return hrRet;
}

#endif

