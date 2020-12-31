// MIMEMessage.h: interface for the CMIMEMessage class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIMEMESSAGE_H__6233D556_EBBF_11D1_870E_444553540001__INCLUDED_)
#define AFX_MIMEMESSAGE_H__6233D556_EBBF_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxmt.h>
#include "MailMessage.h"
#include "MIMEContentAgent.h"

// CMIMEMessage
// Formats a message using the MIME specification.
// 
class CMIMEMessage : public CMailMessage  
{
public:
	CMIMEMessage();
	virtual ~CMIMEMessage();

	// MIME Type Codes
	enum eMIMETypeCode
	{
		TEXT_PLAIN = 0,
		APPLICATION_OCTETSTREAM,
		NEXT_FREE_MIME_CODE
	};
	enum eMIMEEncodingCode
	{
		_7BIT = 0,
		_8BIT,
		BINARY,
		QUOTED_PRINTABLE,
		BASE64,
		NEXT_FREE_ENCODING_CODE
	};
	BOOL AddMIMEPart( LPCTSTR szContent,
					  int nContentType = APPLICATION_OCTETSTREAM,
					  LPCTSTR szParameters = _T( "" ), 
					  int nEncoding = BASE64, 
					  BOOL bPath = TRUE );
protected:
    void insert_message_end( CString& sText );
	void register_mime_type( CMIMEContentAgent* pMIMEType );
	void insert_boundary( CString& sText );

	virtual void append_mime_parts();
	virtual void prepare_header();
	virtual void prepare_body();

	CString m_sNoMIMEText;
	CString m_sPartBoundary;
	CString m_sMIMEContentType;
private:
	class CMIMEPart
	{
	public:
		int m_nEncoding;
		int m_nContentType;
		CString m_sParameters;
		BOOL m_bPath;
		CString m_sContent;
	};
	CList <CMIMEPart, CMIMEPart&> m_MIMEPartList;

	class CMIMETypeManager
	{
	public:
		CMIMEContentAgent* GetHandler( int nContentType );
		void RegisterMIMEType( CMIMEContentAgent* pMIMEType);
		virtual  ~CMIMETypeManager();
		CMIMETypeManager();
	private:
		CCriticalSection m_csAccess;
		CList < CMIMEContentAgent*, CMIMEContentAgent* > m_MIMETypeList;
	};

	static CMIMETypeManager m_MIMETypeManager;
};

#endif // !defined(AFX_MIMEMESSAGE_H__6233D556_EBBF_11D1_870E_444553540001__INCLUDED_)
