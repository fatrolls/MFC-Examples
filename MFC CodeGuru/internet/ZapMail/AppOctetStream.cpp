// AppOctetStream.cpp: implementation of the CAppOctetStream class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppOctetStream.h"
#include "Base64.h"
#include "MIMEMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// IMPORTANT: The number of bytes we read must be
//  a multiple of 3 because CBase64's Encode()
//  method will append padding characters ('=')
//  to make the output's size a multiple of 4.
//  (Base64 treats 3 8-bit bytes as 4 6-bit 'bytes').
//  MIME decoders are free to treat '=' as a signal
//  that there's no more data, so we don't want to pad
//  until we're supposed to.
// When at the end of the file, the # of bytes read
//  may not be a multiple of 3, but that's okay
//  because we DO want the padding chars then.

#define BYTES_TO_READ 54 // This number guarantess output won't
						 // won't exceed line-length limit

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppOctetStream::CAppOctetStream( int nContentType )
	:CMIMEContentAgent( nContentType )
{
}

CAppOctetStream::~CAppOctetStream()
{
}

BOOL CAppOctetStream::AppendPart(LPCTSTR szContent, 
								 LPCTSTR szParameters, 
								 int nEncoding, 
								 BOOL bPath, 
								 CString & sDestination)
{
	CStdioFile fAttachment;

	ASSERT( szContent != NULL );
	// This class handles only file attachments, so
	// it ignores the bPath parameter.
	if( szContent == NULL )
		return FALSE;
	if( !fAttachment.Open( szContent, (CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary) ) )
		return FALSE;
	sDestination += build_sub_header( szContent,
								      szParameters,
									  nEncoding,
									  TRUE );
	attach_file( &fAttachment, CMIMEMessage::BASE64, sDestination );
	fAttachment.Close();
	return TRUE;
}


CString CAppOctetStream::build_sub_header(LPCTSTR szContent, 
										  LPCTSTR szParameters, 
										  int nEncoding, 
										  BOOL bPath)
{
	CString sSubHeader;
	CString sTemp;
	TCHAR szFName[ _MAX_FNAME ];
	TCHAR szExt[ _MAX_EXT ];

	_tsplitpath( szContent, NULL, NULL, szFName, szExt );

	// This class ignores szParameters and nEncoding.
	// It controls its own parameters and only handles
	// Base64 encoding.
	if( bPath )
		sTemp.Format( "; file=%s%s", szFName, szExt );
	else
		sTemp = _T( "" );
	sSubHeader.Format( _T( "Content-Type: %s%s\r\n" ),
						(LPCTSTR)GetContentTypeString(),
						(LPCTSTR)sTemp );
	sSubHeader += _T( "Content-Transfer-Encoding: base64\r\n" );
	sTemp.Format( _T( "Content-Disposition: attachment; filename=%s%s\r\n" ),
				  szFName, szExt );
	sSubHeader += sTemp;
	// Signal end of sub-header.
	sSubHeader += _T( "\r\n" ); // Warning: numerous concatenations
								// are inefficient.
	return sSubHeader;
}

CString CAppOctetStream::GetContentTypeString()
{
	CString s;
	s = _T( "application/octet-stream" );
	return s;
}

// Caller is responsible for opening and closing the file
void CAppOctetStream::attach_file(CStdioFile* pFileAtt, 
								  int nEncoding, 
								  CString & sDestination)
{
	CMIMECode* pEncoder;
	int nBytesRead;
	TCHAR szBuffer[ BYTES_TO_READ + 1 ];

	ASSERT( pFileAtt != NULL );
	if( pFileAtt == NULL )
		return;
	switch( nEncoding )
	{
		// This class handles only Base64 encoding, but others
		//  may be added here.
		default:
			// Fall through to...
		case CMIMEMessage::BASE64:
			try 
			{
				pEncoder = new CBase64;
			}
			catch( CMemoryException* e )
			{
				delete e;
				return;
			}
	}
	if( pEncoder == NULL )	// Old habits are hard to break
		return;
	do
	{
		try
		{
			nBytesRead = pFileAtt->Read( szBuffer, BYTES_TO_READ );
		}
		catch( CFileException* e )
		{
			delete e;
			break;
		}
		szBuffer[ nBytesRead ] = 0;	// Terminate the string
		sDestination += pEncoder->Encode( szBuffer, nBytesRead );
		sDestination += _T( "\r\n" );
	} while( nBytesRead == BYTES_TO_READ );
	sDestination += _T( "\r\n" );
	delete pEncoder;
}
