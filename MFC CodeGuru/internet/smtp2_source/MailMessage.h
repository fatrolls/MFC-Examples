// MailMessage.h: interface for the CMailMessage class.
// Copyright (c) 1998, Wes Clyburn
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_)
#define AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

class CMailMessage  
{
public:
	CMailMessage();
	virtual ~CMailMessage();

	int GetNumRecipients();
	BOOL GetRecipient( CString& sEmailAddress, CString& sFriendlyName, int nIndex = 0 );
	BOOL AddRecipient( LPCTSTR szEmailAddress, LPCTSTR szFriendlyName = "" );
	BOOL AddMultipleRecipients( LPCTSTR szRecipients = NULL );

	CString m_sFrom;
	CString m_sSubject;
	CString m_sHeader;
	CTime m_tDateTime;	
	CString m_sBody;
private:
	class CRecipient
	{
		public:
			CString m_sEmailAddress;
			CString m_sFriendlyName;
	};
	CArray <CRecipient, CRecipient&> m_Recipients;
};

#endif // !defined(AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_)
