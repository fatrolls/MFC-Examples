#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CSecureChannel.cpp $
** $Revision: 7 $
** $Modtime: 1/04/00 5:24a $
*/

#if defined( _DEBUG )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if 0 // Not yet supported

// Construction

CSecureChannel::CSecureChannel()
{
   WFCLTRACEINIT( "CSecureChannel::CSecureChannel()" );
   m_ErrorCode = 0;
}

CSecureChannel::~CSecureChannel()
{
   WFCLTRACEINIT( "CSecureChannel::~CSecureChannel()" );
   Close();
   m_ErrorCode = 0;
}

BOOL CSecureChannel::Authenticate( void )
{
   WFCLTRACEINIT( "CSecureChannel::Authenticate()" );

   if ( m_Provider.CreateKey( m_Algorithm, m_SendingKey ) != TRUE )
   {
      WFCTRACE( "Can't create a key" );
      m_ErrorCode = m_Provider.GetErrorCode();
      return( FALSE );
   }


}

void CSecureChannel::Close( void )
{
   WFCLTRACEINIT( "CSecureChannel::Close()" );
   return;
}

BOOL CSecureChannel::Open( const CUniformResourceLocator& url )
{
   WFCLTRACEINIT( "CSecureChannel::Open()" );

   BOOL return_value = FALSE;

   m_Algorithm.Identifier = CALG_RC2;

   return_value = m_Provider.Open();

   if ( return_value != TRUE )
   {
      m_ErrorCode = m_Provider.GetErrorCode();
   }

   return( return_value );
}

#endif // Not yet supported
