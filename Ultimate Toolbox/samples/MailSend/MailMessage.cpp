// MailMessage.cpp : implementation file
//

#include "stdafx.h"
#include "MailEngine.h"
#include "MailMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailMessage

IMPLEMENT_DYNCREATE(CMailMessage, COXOwnThreadCmdTarget)

CMailMessage::CMailMessage() :
	m_nLastError(MR_MMERR_SUCCESS)
{
	EnableAutomation();
	EnableOwnThread();	
	
	AfxOleLockApp();
}

CMailMessage::~CMailMessage()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CMailMessage::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	COXOwnThreadCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMailMessage, COXOwnThreadCmdTarget)
	//{{AFX_MSG_MAP(CMailMessage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMailMessage, COXOwnThreadCmdTarget)
	//{{AFX_DISPATCH_MAP(CMailMessage)
	DISP_PROPERTY_NOTIFY(CMailMessage, "Subject", m_sSubject, OnSubjectChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CMailMessage, "Content", m_sContent, OnContentChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CMailMessage, "AttachmentCount", m_nAttachmentCount, OnAttachmentCountChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CMailMessage, "LastError", m_nLastError, OnLastErrorChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CMailMessage, "To", m_sTo, OnToChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CMailMessage, "Profile", m_sProfile, OnProfileChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CMailMessage, "Password", m_sPassword, OnPasswordChanged, VT_BSTR)
	DISP_FUNCTION(CMailMessage, "AddAttachment", AddAttachment, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CMailMessage, "GetAttachment", GetAttachment, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CMailMessage, "RemoveAttachment", RemoveAttachment, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CMailMessage, "Send", Send, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMailMessage to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {48452B86-D40F-11CF-AA2E-00AA00489A36}
static const IID IID_IMailMessage =
{ 0x48452b86, 0xd40f, 0x11cf, { 0xaa, 0x2e, 0x0, 0xaa, 0x0, 0x48, 0x9a, 0x36 } };

BEGIN_INTERFACE_MAP(CMailMessage, CCmdTarget)
	INTERFACE_PART(CMailMessage, IID_IMailMessage, Dispatch)
END_INTERFACE_MAP()

// {48452B86-D40F-11CF-AA2E-00AA00489A36}
IMPLEMENT_OLECREATE(CMailMessage, "OXSENDMAIL.MESSAGE", 0x48452b87, 0xd40f, 0x11cf, 0xaa, 0x2e, 0x0, 0xaa, 0x0, 0x48, 0x9a, 0x36)

/////////////////////////////////////////////////////////////////////////////
// CMailMessage message handlers

BOOL CMailMessage::Send() 
{
	BOOL	bResult = FALSE;
	CString	sProfile;
	CString	sPassword;

	bResult = theMailEngine.Send(
						m_sProfile,
						m_sPassword,
						m_sTo,
						m_sSubject,
						m_sContent,
						m_sAttachments,
						m_nLastError);
	if (!bResult)
		m_nLastError = MR_MMERR_HOMEID;
	return bResult;
}

BOOL CMailMessage::AddAttachment(LPCTSTR sFilePath) 
{
	CFileStatus status;
	
	if (!CFile::GetStatus(sFilePath, status))
		return FALSE;
	m_sAttachments.Add(sFilePath);
	m_nAttachmentCount = (short)m_sAttachments.GetSize();
	return TRUE;
}

BSTR CMailMessage::GetAttachment(short nIndex) 
{
	CString strResult;

	if (nIndex >= m_sAttachments.GetSize())
		return FALSE;
	strResult = m_sAttachments[nIndex];
	return strResult.AllocSysString();
}

BOOL CMailMessage::RemoveAttachment(short nIndex) 
{
	if (nIndex >= m_sAttachments.GetSize())
		return FALSE;
	m_sAttachments.RemoveAt(nIndex);
	m_nAttachmentCount = (short)m_sAttachments.GetSize();
	return TRUE;
}


void CMailMessage::OnSubjectChanged() {}
void CMailMessage::OnContentChanged() {}
void CMailMessage::OnAttachmentCountChanged() {GetNotSupported();}
void CMailMessage::OnLastErrorChanged() {GetNotSupported();}
void CMailMessage::OnToChanged() {}
void CMailMessage::OnProfileChanged() {}
void CMailMessage::OnPasswordChanged() {}
