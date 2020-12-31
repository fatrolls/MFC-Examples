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
** $Workfile: cnetwkst.cpp $
** $Revision: 19 $
** $Modtime: 3/12/00 8:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CWorkstationUser, CObject, 1 )
IMPLEMENT_SERIAL( CWorkstationInformation, CObject, 1 )
IMPLEMENT_SERIAL( CWorkstationTransport, CObject, 1 )
IMPLEMENT_SERIAL( CNetWorkstation, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CWorkstationUser stuff
*/

CWorkstationUser::CWorkstationUser()
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::CWorkstationUser()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CWorkstationUser::CWorkstationUser( const WKSTA_USER_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::CWorkstationUser( WKSTA_USER_INFO_1 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationUser::CWorkstationUser( const CWorkstationUser& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::CWorkstationUser( CWorkstationUser& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationUser::~CWorkstationUser()
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::~CWorkstationUser()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

/*
** Can't make Copy take a const pointer because Microsoft screwed up the 
** net API header files...
*/

void CWorkstationUser::Copy( const WKSTA_USER_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkui1_username,     UserName     );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkui1_logon_domain, LogonDomain  );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkui1_oth_domains,  OtherDomains );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkui1_logon_server, LogonServer  );
   }
   catch( ... )
   {
      Empty();
   }
}

void CWorkstationUser::Copy( const CWorkstationUser& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   UserName     = source.UserName;
   LogonDomain  = source.LogonDomain;
   OtherDomains = source.OtherDomains;
   LogonServer  = source.LogonServer;
}

void CWorkstationUser::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::Empty()" ) );
   m_Initialize();
}

void CWorkstationUser::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::m_Initialize()" ) );
   UserName.Empty();
   LogonDomain.Empty();
   OtherDomains.Empty();
   LogonServer.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CWorkstationUser::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CWorkstationUser::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << UserName;
      archive << LogonDomain;
      archive << OtherDomains;
      archive << LogonServer;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> UserName;
      archive >> LogonDomain;
      archive >> OtherDomains;
      archive >> LogonServer;
   }
}

#endif // WFC_NO_SERIALIZATION

const CWorkstationUser& CWorkstationUser::operator = ( const CWorkstationUser& source )
{
   Copy( source );
   return( *this );
}

/*
** CWorkstationInformation stuff
*/

CWorkstationInformation::CWorkstationInformation()
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::CWorkstationInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CWorkstationInformation::CWorkstationInformation( const WKSTA_INFO_100 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::CWorkstationInformation( WKSTA_INFO_100 * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationInformation::CWorkstationInformation( const WKSTA_INFO_101 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::CWorkstationInformation( WKSTA_INFO_101 * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationInformation::CWorkstationInformation( const CWorkstationInformation& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::CWorkstationInformation( CWorkstationInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationInformation::~CWorkstationInformation()
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::~CWorkstationInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CWorkstationInformation::Copy( const WKSTA_INFO_100 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Copy( WKSTA_INFO_100 *source )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki100_computername, ComputerName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki100_langroup,     LANGroup     );

      PlatformID            = source->wki100_platform_id;
      MajorVersion          = source->wki100_ver_major;
      MinorVersion          = source->wki100_ver_minor;
      LANRoot.Empty();
      NumberOfLoggedOnUsers = 0;
   }
   catch( ... )
   {
      Empty();
   }
}

void CWorkstationInformation::Copy( const WKSTA_INFO_101 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Copy( WKSTA_INFO_101 *source )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki101_computername, ComputerName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki101_langroup,     LANGroup     );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki101_lanroot,      LANRoot      );

      PlatformID            = source->wki101_platform_id;
      MajorVersion          = source->wki101_ver_major;
      MinorVersion          = source->wki101_ver_minor;
      NumberOfLoggedOnUsers = 0;
   }
   catch( ... )
   {
      Empty();
   }
}

void CWorkstationInformation::Copy( const WKSTA_INFO_102 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Copy( WKSTA_INFO_102 *source )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki102_computername, ComputerName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki102_langroup,     LANGroup     );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wki102_lanroot,      LANRoot      );

      PlatformID            = source->wki102_platform_id;
      MajorVersion          = source->wki102_ver_major;
      MinorVersion          = source->wki102_ver_minor;
      NumberOfLoggedOnUsers = source->wki102_logged_on_users;
   }
   catch( ... )
   {
      Empty();
   }
}

void CWorkstationInformation::Copy( const CWorkstationInformation& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Copy( const CWorkstationInformation& source )" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   PlatformID            = source.PlatformID;
   ComputerName          = source.ComputerName;
   LANGroup              = source.LANGroup;
   MajorVersion          = source.MajorVersion;
   MinorVersion          = source.MinorVersion;
   LANRoot               = source.LANRoot;
   NumberOfLoggedOnUsers = source.NumberOfLoggedOnUsers;
}

void CWorkstationInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Empty()" ) );
   m_Initialize();
}

void CWorkstationInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::m_Initialize()" ) );
   PlatformID            = 0;
   ComputerName.Empty();
   LANGroup.Empty();
   MajorVersion          = 0;
   MinorVersion          = 0;
   LANRoot.Empty();
   NumberOfLoggedOnUsers = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CWorkstationInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CWorkstationInformation::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << PlatformID;
      archive << ComputerName;
      archive << LANGroup;
      archive << MajorVersion;
      archive << MinorVersion;
      archive << LANRoot;
      archive << NumberOfLoggedOnUsers;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> PlatformID;
      archive >> ComputerName;
      archive >> LANGroup;
      archive >> MajorVersion;
      archive >> MinorVersion;
      archive >> LANRoot;
      archive >> NumberOfLoggedOnUsers;
   }
}

#endif // WFC_NO_SERIALIZATION

const CWorkstationInformation& CWorkstationInformation::operator = ( const CWorkstationInformation& source )
{
   Copy( source );
   return( *this );
}

/*
** CWorkstationTransport stuff
*/

CWorkstationTransport::CWorkstationTransport()
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::CWorkstationTransport()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CWorkstationTransport::CWorkstationTransport( const WKSTA_TRANSPORT_INFO_0 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::CWorkstationTransport( WKSTA_TRANSPORT_INFO_0 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationTransport::CWorkstationTransport( const CWorkstationTransport& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::CWorkstationTransport( CWorkstationTransport )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CWorkstationTransport::~CWorkstationTransport()
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::~CWorkstationTransport()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CWorkstationTransport::Copy( const WKSTA_TRANSPORT_INFO_0 *source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::Copy( WKSTA_TRANSPORT_INFO_0 *source )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkti0_transport_name,    Name    );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->wkti0_transport_address, Address );

      QualityOfService        = source->wkti0_quality_of_service;
      NumberOfVirtualCircuits = source->wkti0_number_of_vcs;
      WANish                  = source->wkti0_wan_ish;
   }
   catch( ... )
   {
      Empty();
   }
}

void CWorkstationTransport::Copy( const CWorkstationTransport& source )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::Copy( const CWorkstationTransport& source )" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   QualityOfService        = source.QualityOfService;
   NumberOfVirtualCircuits = source.NumberOfVirtualCircuits;
   Name                    = source.Name;
   Address                 = source.Address;
   WANish                  = source.WANish;
}

void CWorkstationTransport::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::Empty()" ) );
   m_Initialize();
}

void CWorkstationTransport::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::m_Initialize()" ) );
   QualityOfService        = 0;
   NumberOfVirtualCircuits = 0;
   Name.Empty();
   Address.Empty();
   WANish = FALSE;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CWorkstationTransport::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CWorkstationTransport::Serialize()" ) );

   CObject::Serialize( archive );

   DWORD temp_value = 0;

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << QualityOfService;
      archive << NumberOfVirtualCircuits;
      archive << Name;
      archive << Address;

      temp_value = WANish;
      archive << temp_value;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> QualityOfService;
      archive >> NumberOfVirtualCircuits;
      archive >> Name;
      archive >> Address;
      archive >> temp_value;
      WANish = (BOOL) temp_value;
   }
}

#endif // WFC_NO_SERIALIZATION

const CWorkstationTransport& CWorkstationTransport::operator = ( const CWorkstationTransport& source )
{
   Copy( source );
   return( *this );
}

/*
** CNetWorkstation Stuff
*/

CNetWorkstation::CNetWorkstation()
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::CNetWorkstation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetWorkstation::CNetWorkstation( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::CNetWorkstation( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetWorkstation::~CNetWorkstation()
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::~CNetWorkstation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

void CNetWorkstation::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::Close()" ) );

   CNetwork::Close();

   if ( m_InformationBuffer100 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 100" ) );
      ::NetApiBufferFree( m_InformationBuffer100 );
      m_InformationBuffer100 = NULL;
   }

   if ( m_InformationBuffer101 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 101" ) );
      ::NetApiBufferFree( m_InformationBuffer101 );
      m_InformationBuffer101 = NULL;
   }

   if ( m_InformationBuffer102 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 102" ) );
      ::NetApiBufferFree( m_InformationBuffer102 );
      m_InformationBuffer102 = NULL;
   }

   if ( m_TransportBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Transport Buffer" ) );
      ::NetApiBufferFree( m_TransportBuffer );
      m_TransportBuffer = NULL;
   }

   if ( m_UserBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing User Buffer" ) );
      ::NetApiBufferFree( m_UserBuffer );
      m_UserBuffer = NULL;
   }

   m_TransportBuffer = NULL;
   m_UserBuffer      = NULL;
}

void CNetWorkstation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::m_Initialize()" ) );

   m_ErrorCode                     = 0;
   m_InformationBuffer100          = NULL;
   m_InformationBuffer101          = NULL;
   m_InformationBuffer102          = NULL;
   m_TransportBuffer               = NULL;
   m_TransportResumeHandle         = 0;
   m_TransportCurrentEntryNumber   = 0;
   m_TransportNumberOfEntriesRead  = 0;
   m_TransportTotalNumberOfEntries = 0;
   m_UserBuffer                    = NULL;
   m_UserResumeHandle              = NULL;
   m_UserCurrentEntryNumber        = NULL;
   m_UserNumberOfEntriesRead       = NULL;
   m_UserTotalNumberOfEntries      = NULL;
}

BOOL CNetWorkstation::EnumerateInformation( void )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::EnumerateInformation()" ) );

   if ( m_InformationBuffer100 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 100" ) );
      ::NetApiBufferFree( m_InformationBuffer100 );
      m_InformationBuffer100 = NULL;
   }

   if ( m_InformationBuffer101 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 101" ) );
      ::NetApiBufferFree( m_InformationBuffer101 );
      m_InformationBuffer101 = NULL;
   }

   if ( m_InformationBuffer102 != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 102" ) );
      ::NetApiBufferFree( m_InformationBuffer102 );
      m_InformationBuffer102 = NULL;
   }

   m_ErrorCode = ::NetWkstaGetInfo( (LMSTR) m_WideMachineName, 102, (LPBYTE *) &m_InformationBuffer102 );

   if ( m_ErrorCode == ERROR_ACCESS_DENIED )
   {
      WFCTRACE( TEXT( "Can't Get 102 level data, falling back to 101" ) );
      m_ErrorCode = ::NetWkstaGetInfo( (LMSTR) m_WideMachineName, 101, (LPBYTE *) &m_InformationBuffer101 );

      if ( m_ErrorCode == ERROR_ACCESS_DENIED )
      {
         WFCTRACE( TEXT( "Can't Get 101 level data, falling back to 100" ) );
         m_ErrorCode = ::NetWkstaGetInfo( (LMSTR) m_WideMachineName, 100, (LPBYTE *) &m_InformationBuffer100 );

         if ( m_ErrorCode != NERR_Success || m_InformationBuffer100 == NULL )
         {
            WFCTRACE( TEXT( "Can't get 100 level data, giving up" ) );
            return( FALSE );
         }
      }
      else if ( m_ErrorCode != NERR_Success || m_InformationBuffer101 == NULL )
      {
         return( FALSE );
      }
   }
   else if ( m_ErrorCode != NERR_Success || m_InformationBuffer102 == NULL )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CNetWorkstation::EnumerateTransports( void )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::EnumerateTransports()" ) );

   if ( m_TransportBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Transport Buffer" ) );
      ::NetApiBufferFree( m_TransportBuffer );
      m_TransportBuffer = NULL;
   }

   m_TransportCurrentEntryNumber   = 0;
   m_TransportNumberOfEntriesRead  = 0;
   m_TransportResumeHandle         = 0;
   m_TransportTotalNumberOfEntries = 0;

   m_ErrorCode = ::NetWkstaTransportEnum( (LMSTR) m_WideMachineName, 
                                                  0, 
                                      (LPBYTE *) &m_TransportBuffer,
                                                  65536,
                                                 &m_TransportNumberOfEntriesRead,
                                                 &m_TransportTotalNumberOfEntries,
                                                 &m_TransportResumeHandle );

   if ( m_ErrorCode != NERR_Success || m_TransportBuffer == NULL || m_TransportNumberOfEntriesRead == 0 )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CNetWorkstation::EnumerateUsers( void )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::EnumerateUsers()" ) );

   if ( m_UserBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing User Buffer" ) );
      ::NetApiBufferFree( m_UserBuffer );
      m_UserBuffer = NULL;
   }

   m_UserCurrentEntryNumber   = 0;
   m_UserNumberOfEntriesRead  = 0;
   m_UserTotalNumberOfEntries = 0;
   m_UserResumeHandle         = 0;

   m_ErrorCode = ::NetWkstaUserEnum( (LMSTR) m_WideMachineName, 
                                     1, 
                         (LPBYTE *) &m_UserBuffer,
                                     65536,
                                    &m_UserNumberOfEntriesRead,
                                    &m_UserTotalNumberOfEntries,
                                    &m_UserResumeHandle );

   if ( m_ErrorCode != NERR_Success || m_UserBuffer == NULL || m_UserNumberOfEntriesRead == 0 )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CNetWorkstation::GetCurrentUser( CWorkstationUser& information )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::GetCurrentUser()" ) );

   WKSTA_USER_INFO_1 *buffer = NULL;

   m_ErrorCode = ::NetWkstaUserGetInfo( NULL, 1, (LPBYTE *) &buffer );

   if ( m_ErrorCode != NERR_Success || buffer == NULL )
   {
      information.Empty();
      return( FALSE );
   }

   information.Copy( buffer );

   ::NetApiBufferFree( buffer );

   return( TRUE );
}

BOOL CNetWorkstation::GetNext( CWorkstationInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::GetNext( CWorkstationInformation& information )" ) );

   if ( m_InformationBuffer102 != NULL )
   {
      information.Copy( m_InformationBuffer102 );
      ::NetApiBufferFree( m_InformationBuffer102 );
      m_InformationBuffer102 = NULL;
      return( TRUE );
   }

   if ( m_InformationBuffer101 != NULL )
   {
      information.Copy( m_InformationBuffer101 );
      ::NetApiBufferFree( m_InformationBuffer101 );
      m_InformationBuffer101 = NULL;
      return( TRUE );
   }

   if ( m_InformationBuffer100 != NULL )
   {
      information.Copy( m_InformationBuffer100 );
      ::NetApiBufferFree( m_InformationBuffer100 );
      m_InformationBuffer100 = NULL;
      return( TRUE );
   }

   information.Empty();

   return( FALSE );
}

BOOL CNetWorkstation::GetNext( CWorkstationTransport& information )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::GetNext( CWorkstationTransport& information )" ) );

   if ( m_TransportCurrentEntryNumber < m_TransportTotalNumberOfEntries )
   {
      information.Copy( &m_TransportBuffer[ m_TransportCurrentEntryNumber ] );
      m_TransportCurrentEntryNumber++;
      return( TRUE );
   }

   information.Empty();
   return( FALSE );
}

BOOL CNetWorkstation::GetNext( CWorkstationUser& information )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::GetNext( CWorkstationUser& information )" ) );

   if ( m_UserCurrentEntryNumber < m_UserTotalNumberOfEntries )
   {
      information.Copy( &m_UserBuffer[ m_UserCurrentEntryNumber ] );
      m_UserCurrentEntryNumber++;
      return( TRUE );
   }

   information.Empty();
   return( FALSE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetWorkstation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetWorkstation::Serialize()" ) );

   CNetwork::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << m_ErrorCode;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> m_ErrorCode;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source
