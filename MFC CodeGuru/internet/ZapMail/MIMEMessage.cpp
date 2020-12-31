// MIMEMessage.cpp: implementation of the CMIMEMessage class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MIMEMessage.h"
#include "TextPlain.h"
#include "AppOctetStream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Static Member Initializers
CMIMEMessage::CMIMETypeManager CMIMEMessage::m_MIMETypeManager;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMIMEMessage::CMIMEMessage()
{
	m_sMIMEContentType = _T( "multipart/mixed" );
	m_sPartBoundary = _T( "WC_MAIL_PaRt_BoUnDaRy_05151998" );
	m_sNoMIMEText = _T( "This is a multi-part message in MIME format." );

	// Register the MIME types handled by this class
	//
	CMIMEContentAgent* pType;
	// These objects are deleted by CMIMTypeManager's destructor
	pType = new CTextPlain( TEXT_PLAIN, GetCharsPerLine() );
	register_mime_type( pType );
	pType = new CAppOctetStream( APPLICATION_OCTETSTREAM );
	register_mime_type( pType );
}

CMIMEMessage::~CMIMEMessage()
{
}

// This implementation adds the part to the part-list used
//  to build the body.
BOOL CMIMEMessage::AddMIMEPart(LPCTSTR szContent,
							   int nContentType, 
							   LPCTSTR szParameters, 
							   int nEncoding, 
							   BOOL bPath )
{
	CMIMEPart part;
	part.m_nContentType = nContentType;
	part.m_sParameters = szParameters;
	part.m_nEncoding = nEncoding;
	part.m_bPath = bPath;
	part.m_sContent = szContent;
	part.m_sContent.TrimLeft();
	part.m_sContent.TrimRight();
	if( nContentType == TEXT_PLAIN )
		m_MIMEPartList.AddHead( part );
	else
		m_MIMEPartList.AddTail( part );
	return TRUE;
}

void CMIMEMessage::prepare_header()
{
	CString sTemp;

	// Let the base class add its headers
	CMailMessage::prepare_header();
	
	add_header_line( _T( "MIME-Version: 1.0" ) );
	sTemp.Format( _T( "Content-Type: %s; boundary=%s" ),
				  (LPCTSTR)m_sMIMEContentType,
				  (LPCTSTR)m_sPartBoundary );
	add_header_line( (LPCTSTR)sTemp );
}

void CMIMEMessage::prepare_body()
{
	// Class user may have assigned body text directly.
	// Convert it to just another MIME part to be processed.
	// If this default Content-Type isn't good enough for the
	// class user, he or she should have used AddMIMEPart() instead.
	if( m_sBody != _T( "" ) )
		AddMIMEPart( (LPCTSTR)m_sBody, TEXT_PLAIN, "", _7BIT, FALSE );

	// Initialize the body (replace current contents).
	m_sBody = m_sNoMIMEText;
	m_sBody += _T( "\r\n\r\n" );
	append_mime_parts();
	insert_message_end( m_sBody );

	// Let the base class take me to Funky Town
	CMailMessage::prepare_body();
}

void CMIMEMessage::insert_boundary( CString& sText )
{
	CString sTemp;
	if( sText.Right( 2 ) != _T( "\r\n" ) )
		sText += _T( "\r\n" );
	sTemp.Format( _T( "--%s\r\n" ), (LPCTSTR)m_sPartBoundary );
	sText += sTemp;
}

void CMIMEMessage::insert_message_end( CString& sText )
{
	CString sTemp;
	if( sText.Right( 2 ) != _T( "\r\n" ) )
		sText += _T( "\r\n" );
	sTemp.Format( _T( "--%s--\r\n" ), (LPCTSTR)m_sPartBoundary );
	sText += sTemp;
}

void CMIMEMessage::register_mime_type(CMIMEContentAgent* pMIMEType)
{
	ASSERT( pMIMEType != NULL );
	if( pMIMEType == NULL )
		return;
	m_MIMETypeManager.RegisterMIMEType( pMIMEType );
}


void CMIMEMessage::append_mime_parts()
{
	POSITION part_position;
	CMIMEPart* pMIMEPart = NULL;
	CMIMEContentAgent* pMIMEType = NULL;

	part_position = m_MIMEPartList.GetHeadPosition();
	// Get each part from the list, retrieve a handler for it,
	//  and let the handler do its thing.
	while( part_position != NULL )
	{
		pMIMEPart = & m_MIMEPartList.GetNext( part_position );
		pMIMEType = m_MIMETypeManager.GetHandler( pMIMEPart->m_nContentType );
		if( pMIMEType != NULL )
		{
			insert_boundary( m_sBody );
			pMIMEType->AppendPart( pMIMEPart->m_sContent,
								   pMIMEPart->m_sParameters,
								   pMIMEPart->m_nEncoding,
								   pMIMEPart->m_bPath,
								   m_sBody );
		}
	}

}

//////////////////////////////////////////////////////////////////////
// CMIMETypeManager Implementation
//////////////////////////////////////////////////////////////////////

CMIMEMessage::CMIMETypeManager::CMIMETypeManager()
{
}

CMIMEMessage::CMIMETypeManager::~CMIMETypeManager()
{
	POSITION pos;
	CMIMEContentAgent* p;
	m_csAccess.Lock();
	pos = m_MIMETypeList.GetHeadPosition();
	while( pos != NULL )
	{
		p = m_MIMETypeList.GetNext( pos );
		delete p;
	}
}

void CMIMEMessage::CMIMETypeManager::RegisterMIMEType(CMIMEContentAgent *pMIMEType)
{
	ASSERT( pMIMEType != NULL );
	if( pMIMEType == NULL )
		return;
	m_csAccess.Lock();
	m_MIMETypeList.AddTail( pMIMEType );
}



CMIMEContentAgent* CMIMEMessage::CMIMETypeManager::GetHandler(int nContentType)
{
	POSITION pos;
	CMIMEContentAgent* pType = NULL;

	m_csAccess.Lock();
	pos = m_MIMETypeList.GetHeadPosition();
	while( pos != NULL )
	{
		pType = m_MIMETypeList.GetNext( pos );
		if( pType->QueryType( nContentType ) == TRUE )
			break;
	}
	return pType;
}

