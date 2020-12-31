// TextPlain.cpp: implementation of the CTextPlain class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextPlain.h"
#include "MIMEMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextPlain::CTextPlain( int nContentType, UINT nWrapPos )
	:CMIMEContentAgent( nContentType )
{
	m_nWrapPos = nWrapPos;	
}

CTextPlain::~CTextPlain()
{

}

CString CTextPlain::GetContentTypeString()
{
	CString s;
	s = _T( "text/plain" );
	return s;
}

BOOL CTextPlain::AppendPart(LPCTSTR szContent, 
							LPCTSTR szParameters, 
							int nEncoding, 
							BOOL bPath, 
							CString & sDestination)
{
	CString sSubHeader;
	CString sWrapped;
	sSubHeader = build_sub_header( szContent,
								   szParameters,
								   nEncoding,
								   bPath );
	sWrapped = wrap_text( szContent );
	sDestination += (sSubHeader + sWrapped);
	return TRUE;
}

CString CTextPlain::build_sub_header(LPCTSTR szContent, 
									 LPCTSTR szParameters, 
									 int nEncoding, 
									 BOOL bPath)
{
	CString sSubHeader;
	sSubHeader.Format( _T( "Content-Type: %s%s\r\n" ),
					   (LPCTSTR)GetContentTypeString(),
					   szParameters );
	sSubHeader += _T( "Content-Transfer-Encoding: " );
	switch( nEncoding )
	{
		// This class handles only 7bit encoding, but others
		//  may be added here.
		default:
			//Fall through to...
		case CMIMEMessage::_7BIT:
			sSubHeader += _T( "7Bit" );
	}
	sSubHeader += _T( "\r\n\r\n" );
	return sSubHeader;
}

CString CTextPlain::wrap_text(LPCTSTR szText)
{
	CString sTemp;
	CString sLeft;
	CString sRight;
	int lp = 0;
	UINT nCount = 0;
	int nSpacePos = 0;

	ASSERT( szText != NULL );
	if( szText == NULL )
		return sTemp;
	sTemp = szText;
	while( lp < sTemp.GetLength() )
	{
		if( sTemp[ lp ] == ' ' )
			nSpacePos = lp;
		// Reset counter on newline
		if( sTemp.Mid( lp, 2 ) == _T( "\r\n" ) )
			nCount = 0;
		// Wrap text at last found space
		if( nCount > m_nWrapPos )
		{
			sLeft = sTemp.Left( nSpacePos );
			sRight = sTemp.Right( sTemp.GetLength() - nSpacePos );
			sLeft.TrimRight();
			sRight.TrimLeft();
			sLeft += _T( "\r\n" );
			sTemp = sLeft + sRight;
			nCount = 0;
		}
		else
			nCount++;
		lp++;
	}
	return sTemp;
}
