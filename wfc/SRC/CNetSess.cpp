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
** $Workfile: cnetsess.cpp $
** $Revision: 22 $
** $Modtime: 4/30/00 6:13p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkSessions, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkSessions::CNetworkSessions()
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::CNetworkSessions()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkSessions::CNetworkSessions( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::CNetworkSessions( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Open( machine_name );
}

CNetworkSessions::~CNetworkSessions()
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::~CNetworkSessions()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

void CNetworkSessions::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::Close()" ) );
   CNetwork::Close();
   m_Initialize();
}

BOOL CNetworkSessions::Delete( CNetworkSessionInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::Delete()" ) );

   WCHAR wide_user_name[ 256 ];
   WCHAR wide_client_name[ 256 ];

   ::ZeroMemory( wide_user_name,   sizeof( wide_user_name   ) );
   ::ZeroMemory( wide_client_name, sizeof( wide_client_name ) );

   LPWSTR user   = (LPWSTR) NULL;
   LPWSTR client = (LPWSTR) NULL;

   if ( information.UserName.GetLength() > 0 )
   {
#if ! defined( UNICODE )
      ::ASCII_to_UNICODE( information.UserName, wide_user_name );
#else
      _tcscpy( wide_user_name, information.UserName );
#endif // UNICODE

      user = wide_user_name;
   }

   if ( information.ClientName.GetLength() > 0 )
   {
#if ! defined( UNICODE )
      ::ASCII_to_UNICODE( information.ClientName, wide_client_name );
#else
      _tcscpy( wide_client_name, information.ClientName );
#endif // UNICODE

      client = wide_client_name;
   }

   m_ErrorCode = ::NetSessionDel( (LMSTR) m_WideMachineName,
                                  (LMSTR) client,
                                  (LMSTR) user );
   
   if ( m_ErrorCode == NERR_Success )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CNetworkSessions::Enumerate( CNetworkSessionInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::Enumerate()" ) );

   SESSION_INFO_502 *information_p = (SESSION_INFO_502 *) NULL;

   SESSION_INFO_502 s;

   ::ZeroMemory( &s, sizeof( s ) );

   information_p = &s;

   DWORD prefered_maximum_length = sizeof( SESSION_INFO_502 ) * 128;
   DWORD number_of_entries_read  = 0;
   DWORD total_number_of_entries = 0;

   m_ErrorCode = ::NetSessionEnum( (LMSTR) m_WideMachineName, 
                                   (LMSTR) NULL, 
                                   (LMSTR) NULL, 
                                           502,
                               (LPBYTE *) &information_p,
                                           prefered_maximum_length,
                                          &number_of_entries_read,
                                          &total_number_of_entries,
                                          &m_ResumeHandle );

   if ( information_p != (SESSION_INFO_502 *) NULL )
   {
      information.Copy( information_p );
      return( TRUE );
   }

   return( FALSE );
}

BOOL CNetworkSessions::GetNext( CNetworkSessionInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::GetNext()" ) );
   return( Enumerate( information ) );
}

void CNetworkSessions::m_Get_0_Data( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Get_0_Data()" ) );

   LPBYTE buffer = (LPBYTE) NULL;

   /*
   ** One of the children got loose in the header files again...
   **
   ** Also, we can't get 101 information because it doesn't work if you supply
   ** a machine name... Go Figure...
   */

   ::NetSessionGetInfo( (LMSTR) m_WideMachineName, NULL, NULL, 0, &buffer );

   if ( buffer != NULL )
   {
      SESSION_INFO_0 * information_p = (SESSION_INFO_0 *) buffer;

      /*
      ** Now store the info we want...
      */

      m_ServerName = CString( (LPCWSTR) information_p->sesi0_cname );
      m_Retrieved0 = TRUE;
   }
}

void CNetworkSessions::m_Get_1_Data( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Get_1_Data()" ) );
}

void CNetworkSessions::m_Get_2_Data( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Get_2_Data()" ) );
}

void CNetworkSessions::m_Get_10_Data( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Get_10_Data()" ) );
}

void CNetworkSessions::m_Get_502_Data( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Get_502_Data()" ) );
}

void CNetworkSessions::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessions::m_Initialize()" ) );

   m_ServerName.Empty();
   m_ClientName.Empty();

   m_Retrieved0   = FALSE;
   m_Retrieved1   = FALSE;
   m_Retrieved2   = FALSE;
   m_Retrieved10  = FALSE;
   m_Retrieved502 = FALSE;

   m_ErrorCode    = 0;
   m_ResumeHandle = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkSessions::Serialize( CArchive& archive )
{
   CNetwork::Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

// End of source
