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
** $Workfile: CNetworkSessionInformation.cpp $
** $Revision: 6 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkSessionInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkSessionInformation::CNetworkSessionInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::CNetworkSessionInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkSessionInformation::CNetworkSessionInformation( const SESSION_INFO_502 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::CNetworkSessionInformation( SESSION_INFO_502 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkSessionInformation::CNetworkSessionInformation( const CNetworkSessionInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::CNetworkSessionInformation( CNetworkSessionInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkSessionInformation::~CNetworkSessionInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::~CNetworkSessionInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkSessionInformation::Copy( const SESSION_INFO_502 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->sesi502_cname,       ClientName     );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->sesi502_username,    UserName       );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->sesi502_cltype_name, ClientTypeName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->sesi502_transport,   Transport      );

      NumberOfOpens  = source->sesi502_num_opens;
      Time           = CTimeSpan( source->sesi502_time      );
      IdleTime       = CTimeSpan( source->sesi502_idle_time );
      UserFlags      = source->sesi502_user_flags;
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkSessionInformation::Copy( const CNetworkSessionInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   ClientName     = source.ClientName;
   UserName       = source.UserName;
   ClientTypeName = source.ClientTypeName;
   Transport      = source.Transport;
   NumberOfOpens  = source.NumberOfOpens;
   Time           = source.Time;
   IdleTime       = source.IdleTime;
   UserFlags      = source.UserFlags;
}

void CNetworkSessionInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkSessionInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::m_Initialize()" ) );

   ClientName.Empty();
   UserName.Empty();
   ClientTypeName.Empty();
   Transport.Empty();
   NumberOfOpens = 0;
   Time          = CTimeSpan( 0 );
   IdleTime      = CTimeSpan( 0 );
   UserFlags     = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkSessionInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkSessionInformation::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << ClientName;
      archive << UserName;
      archive << NumberOfOpens;
      archive << Time;
      archive << IdleTime;
      archive << UserFlags;
      archive << ClientTypeName;
      archive << Transport;
   }
   else
   {
      archive >> ClientName;
      archive >> UserName;
      archive >> NumberOfOpens;
      archive >> Time;
      archive >> IdleTime;
      archive >> UserFlags;
      archive >> ClientTypeName;
      archive >> Transport;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source
