// ==========================================================================
// 					Class Specification : COXSendMail
// ==========================================================================

// Header file : OXSendMail.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	The COXSendMail class is designed to send Mail from Windows NT service applications
//	like the Microsoft IIS server. The class has an extremely simple interface which
//	enables you to send mail with only 3 function calls.
//	The COXSendMail class is based on our MFC framework for extended MAPI (through
//	OLE Messaging). This framework provides 14 powerful classes which allow you to add
//	quickly and easily the ability to send and receive mail messages to your MFC application.
//	It also enables easy interaction with folders and address books. You can create
//	programmable messaging objects. The functionality of these objects can be used to build
//	workflow automation solutions.
//	You can add different kind of recipients (CC, BCC, distribution lists) and attachments
//	(binary, ole-objects) and send it to a MAPI compatible mail system (Exchange, Microsoft
//	Mail, Internet Mail, ...).
//   

// Remark:
//	If your NT service application logs on with a specific user account you must provide an
//	additional privilege for this account: the user-right "Restore Files and Directories" must
//	be granted. If the service uses the system account you have to impersonate a specific
//	user account if you send a message. For example, if you use the Microsoft IIS to call
//	your ISAPI extensions, the IIS will impersonate the anonymous WWW-account ‘USR_COMPUTER_NAME’
//	before calling your extension DLL. 
//	You have to provide a suitable Profile for that user account. If MAPI logs on to a store or
//	transport provider it uses a MAPI profile which defines the providers to use.
//	Instantiate a COXSendMail object and call the Logon() function with the profile name and
//	password as parameters. Call the CreateMessage() function and add your recipients and attachments
//	with the AddRecipient() and AddAttachment() functions. Finally call the SendMessage() function
//	and you are done.
//
//	*** There are two compile version of this class. One that uses our OXMapi framework (don't define 
//		the OX_MAPI_DIRECT switch. And one that uses extended MAPI direct (use the #define OX_MAPI_DIRECT 
//		switch.


// Prerequisites (necessary conditions):
//	

/////////////////////////////////////////////////////////////////////////////

#ifndef __SENDMAIL_H__
#define __SENDMAIL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


// See the *** remark section for the following switch
//#define OX_MAPI_DIRECT

#ifndef OX_MAPI_DIRECT
#include "oxmdisp.h"
#else
#include <mapix.h>
#endif


#define CRecipientArray CArray<CMessage::SRecipient*, CMessage::SRecipient*>
#define CAttachmentArray CArray<CMessage::SAttachment*, CMessage::SAttachment*>
#define CInternRecipientArray CArray<SRecipient*, SRecipient*>
#define CInternAttachmentArray CArray<SAttachment*, SAttachment*>

class OX_CLASS_DECL COXSendMail : public CObject
{
// Data Members
public:
	enum ERecipientType
	{
		rtTO = 1,
		rtCC = 2,
		rtBCC = 3
	};
	enum EAttachmentType
	{
		atFileData = 1,
		atFileLink = 2,
		atOleObject = 3
	};
	class OX_CLASS_DECL CMessage
	{
	friend COXSendMail;
	// Data Members
	public:
		CString m_sSubject;
		CString	m_sContent;

	protected:
		struct SRecipient
		{
			CString			sName;
			ERecipientType	eType;
		};
		struct SAttachment
		{
			CString			sPath;
			EAttachmentType	eType;
			CString			sOleDocument;
		};
		CInternRecipientArray	m_recipients;
		CInternAttachmentArray	m_attachments;

	// Member Functions
	public:
		CMessage();
		virtual ~CMessage();
		void AddRecipient(CString sRecipient, ERecipientType eType);
		void AddAttachment(CString sAttachment, EAttachmentType eType, CString sOleDocument = _T(""));
	};

protected:

	CString				m_sMAPIProfile;

#ifndef OX_MAPI_DIRECT
	COXMSession			m_objSession;
#endif

public:
	COXSendMail();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
 
	virtual ~COXSendMail();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

	BOOL Initialize(CString sProfileName, CString sPassword = _T(""));
	// --- In: sProfileName: name of the profile you want to log on with
	//		   sPassword: optional password to log on
	// --- Out: none
	// --- Returns: if successful or not
	// --- Effect: Logs on to the mail services defined in the given profile

	BOOL IsInitialized();
	// --- In: none
	// --- Out: none
	// --- Returns: if initialized or not
	// --- Effect: none

	void Uninitialize();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: logs off from the mail system and does some cleaning

	CString GetProfile();
	// --- In: none
	// --- Out: none
	// --- Returns: if initialized the name of the profile
	// --- Effect: none

	BOOL SendMessage(CMessage& message);
	// --- In: message: the message to send
	// --- Out: none
	// --- Returns: if message was send successful or not
	// --- Effect: sends the message

	static CString GetReturnMsg(int nErr);
	// --- In: nErr: the error code returned by MAPI
	// --- Out: none
	// --- Returns: a description of the error message
	// --- Effect: none

protected:


// ******************************************************************
// this is needed for the Extended MAPI alternative; see the *** remark section
// ******************************************************************
#ifdef OX_MAPI_DIRECT
	BOOL InitializeMessageStore();
	LPMESSAGE ComposeMessage(CMessage& message);
	HRESULT AddRecipients(LPMESSAGE pMessage, CRecipientArray& recipients);
	HRESULT AddAttachments(LPMESSAGE pMessage, CAttachmentArray& attachments);
	LPMAPISESSION       m_pMAPISession;       
	LPADRBOOK           m_pAddressBook; 
	LPENTRYID 			m_peidDefaultMDB;
	ULONG     			m_cbeidDefaultMDB;
	LPMDB     			m_pDefaultMDB;
	LPMAPIFOLDER  		m_pRootFolder;
	LPSTR     			m_szRecipient;
	ULONG     			m_uLogoffFlags;
	LPSTR     			m_szAttachData;
#endif
// ******************************************************************

};

#endif	// __MAILTO_H__
// ==========================================================================

