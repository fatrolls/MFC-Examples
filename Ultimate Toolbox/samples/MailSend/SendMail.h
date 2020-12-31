// ==========================================================================
// 					Class Specification : CSendMail
// ==========================================================================

// Header file : SendMail.h

//----------------- Dundas Software ----------------------------------------                          
//========================================================================
                          
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
//	
//   

// Remark:
//		***
// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __SENDMAIL_H__
#define __SENDMAIL_H__

#include <mapix.h>

class CSendMail : public CObject
{
protected:

	LPMAPISESSION       m_pMAPISession;       
	LPADRBOOK           m_pAddressBook; 
	LPENTRYID 			m_peidDefaultMDB;
	ULONG     			m_cbeidDefaultMDB;
	LPMDB     			m_pDefaultMDB;
	LPMAPIFOLDER  		m_pRootFolder;
	LPSTR     			m_szRecipient;
	ULONG     			m_uLogoffFlags;
	LPSTR     			m_szAttachData;
	CString				m_sMAPIProfile;

public:
	CSendMail();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
 
	~CSendMail();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object


	BOOL Initialize(CString sProfileName, CString sPassword = NULL);
	BOOL IsInitialized() const;
	void Uninitialize();
	CString GetProfile() const;
	BOOL SendMapiMail(CString sTo, CString sSubject, CString sDescription, CString sAtt);

protected:
	CString GetReturnMsg(int nErr);
	BOOL InitializeMessageStore();


	LPMESSAGE ComposeMessage(LPCTSTR szRecipient, LPCTSTR szSubject, LPCTSTR szDescription, LPCTSTR szAtt);
	LPADRLIST GetRecipient(LPCTSTR szRecipient);
	HRESULT AddAttachments(LPMESSAGE pMessage, LPCTSTR szAttachData);
};

#endif	// __MAILTO_H__
// ==========================================================================

