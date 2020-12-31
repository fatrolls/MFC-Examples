// MailEngine.cpp : implementation file
//

#include "stdafx.h"
#include "MailEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

short CMailEngine::defError = 0;

CMailEngine theMailEngine;

/////////////////////////////////////////////////////////////////////////////
// CMailEngine

CMailEngine::CMailEngine()
{
}

CMailEngine::~CMailEngine()
{
}

BOOL CMailEngine::LogOn(CString sProfile, CString sPassword)
{
	BOOL bResult;
	
	CMCLogOn* pCmd = new CMCLogOn(sProfile, sPassword);
	PostCommand(pCmd);
	bResult = pCmd->bResult;
	pCmd->Release();
	return bResult;
}

void CMailEngine::LogOff()
{
	CMailCmd* pCmd = new CMCLogOff();
	PostCommand(pCmd);
	pCmd->Release();
}

BOOL CMailEngine::IsLoggedOn()
{
	return m_sendMail.IsInitialized();
}

BOOL CMailEngine::Send(CString sProfile,
					   CString sPassword,
					   CString sRecipient, 
					   CString sSubject, 
					   CString sContent,
					   const CStringArray& sAttachments,
					   short& nError)
{
	CMailCmd*	pCmd;

	pCmd = new CMCLogOn(sProfile, sPassword);
	PostCommand(pCmd);
	pCmd->Release();

	pCmd = new CMCSend(sRecipient,
					 sSubject,
					 sContent,
					 sAttachments);
	PostCommand(pCmd);
	nError = ((CMCSend*)pCmd)->nError;
	pCmd->Release();

	return (nError == 0);
}


// protected:

void CMailEngine::OnExecuteCmd(COXEngineCmd* pCmd)
{
	switch (((CMailCmd*) pCmd)->eCmd)
	{
	case mcLogOn:
		OnLogOn(*((CMCLogOn*) pCmd));
		break;
	case mcLogOff:
		OnLogOff(*((CMCLogOff*) pCmd));
		break;
	case mcSend:
		OnSend(*((CMCSend*) pCmd));
		break;
	default:
		TRACE(_T("'CMailEngine::OnThreadEvent' Unknown command ! \n"));
		ASSERT(FALSE);
		break;
	}
}

void CMailEngine::OnThreadDestruction()
{
	COXThreadEngine::OnThreadDestruction();
	if (m_sendMail.IsInitialized())
		m_sendMail.Uninitialize();
}

void CMailEngine::OnLogOn(CMCLogOn& cmd)
{
	CString	sProfile;
//	HANDLE	hToken;

	sProfile = m_sendMail.GetProfile();
	
	if (sProfile != cmd.sProfile)
	{
		if (m_sendMail.IsInitialized())
			m_sendMail.Uninitialize();
	}
	else if (m_sendMail.IsInitialized())
	{
		cmd.bResult = TRUE;
		return;
	}
	

//LOGON32_LOGON_BATCH
//LOGON32_LOGON_INTERACTIVE
//LOGON32_LOGON_SERVICE

/*	if (!::LogonUser(_T("Kris"), _T("PERIDEV"), _T("poke725"), LOGON32_LOGON_BATCH, LOGON32_PROVIDER_DEFAULT, &hToken))
	{
		DWORD dwResult = GetLastError();
		if (dwResult == ERROR_PRIVILEGE_NOT_HELD)
		{
			cmd.bResult = FALSE;
		}
		cmd.bResult = FALSE;
		return;
	}
	if (!ImpersonateLoggedOnUser(hToken))
	{
		cmd.bResult = FALSE;
		return;
	}
*/
  if (m_sendMail.Initialize(cmd.sProfile, cmd.sPassword)==FALSE)
	{
		cmd.bResult = FALSE;
		return;
	}
	cmd.bResult = TRUE;
}

void CMailEngine::OnLogOff(CMCLogOff& cmd)
{
	UNUSED(cmd);
	if (m_sendMail.IsInitialized())
		m_sendMail.Uninitialize();
}

void CMailEngine::OnSend(CMCSend& cmd)
{
	CString sAttachments;

	if (m_sendMail.IsInitialized() == FALSE)
	{
		cmd.nError = MR_MMERR_LOGON;
		return;
	}

	COXSendMail::CMessage message;

	message.m_sSubject = cmd.sSubject;
	message.m_sContent = cmd.sContent;
	message.AddRecipient(cmd.sRecipient, COXSendMail::rtTO);
	for (int i=0 ; i<cmd.sAttachments.GetSize() ; i++)
		message.AddAttachment(cmd.sAttachments[i], COXSendMail::atFileData);


	if (m_sendMail.SendMessage(message) == FALSE)
	{
		cmd.nError = MR_MMERR_RECIPIENT;
		return;
	}
	cmd.nError = MR_MMERR_SUCCESS;
}
