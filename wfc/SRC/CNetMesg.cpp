#if 0
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
** $Workfile: CNetMesg.cpp $
** $Revision: 9 $
** $Modtime: 3/12/00 8:15a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( CMessageInformation, CObject, 1 )
IMPLEMENT_SERIAL( CNetMessage, CNetwork, 1 )

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif

/*
** CMessageInformation stuff
*/

CMessageInformation::CMessageInformation()
{
   m_Initialize();
}

/*
** Can't make Copy take a const pointer because Microsoft screwed up the 
** net API header files...
*/

CMessageInformation::CMessageInformation( const WKSTA_USER_INFO_1 *source )
{
   Copy( source );
}

CMessageInformation::CMessageInformation( const CMessageInformation& source )
{
   Copy( source );
}

CMessageInformation::~CMessageInformation()
{
   m_Initialize();
}

void CMessageInformation::Copy( const MSG_INFO_0 *source )
{
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   ::wfc_convert_lpcwstr_to_cstring( source->msgi0_name, Name );

   ForwardFlag = 0;
   ForwardName.Empty();
}

void CMessageInformation::Copy( const MSG_INFO_1 *source )
{
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->msgi1_name,    Name        );
   ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->msgi1_forward, ForwardName );

   Name        = source->msgi1_name;
   ForwardFlag = source->msgi1_forward_flag;
   ForwardName = source->msgi1_forward;
}

void CMessageInformation::Copy( const CMessageInformation& source )
{
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   Name        = source.Name;
   ForwardFlag = source.ForwardFlag;
   ForwardName = source.ForwardName;
}

void CMessageInformation::Empty( void )
{
   m_Initialize();
}

void CMessageInformation::m_Initialize( void )
{
   Name.Empty();
   ForwardName.Empty();
   ForwardFlag = 0;
}

void CMessageInformation::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << Name;
      archive << ForwardFlag;
      archive << ForwardName;
   }
   else
   {
      archive >> Name;
      archive >> ForwardFlag;
      archive >> ForwardName;
   }
}

/*
** CNetMessage Stuff
*/

CNetMessage::CNetMessage()
{
   m_Initialize();
}

CNetMessage::CNetMessage( LPCTSTR machine_name )
{
   m_Initialize();
   Open( machine_name );
}

CNetMessage::~CNetMessage()
{
   Close();
}

void CNetMessage::Close( void )
{
   CNetwork::Close();

   if ( m_InformationBuffer0 != NULL )
   {
      ::NetApiBufferFree( m_InformationBuffer0 );
      m_InformationBuffer0 = NULL;
   }

   if ( m_InformationBuffer1 != NULL )
   {
      ::NetApiBufferFree( m_InformationBuffer1 );
      m_InformationBuffer1 = NULL;
   }
}

void CNetMessage::m_Initialize( void )
{
   m_ErrorCode            = 0;
   m_InformationBuffer0   = NULL;
   m_InformationBuffer1   = NULL;
   m_ResumeHandle         = NULL;
   m_CurrentEntryNumber   = NULL;
   m_NumberOfEntriesRead  = NULL;
   m_TotalNumberOfEntries = NULL;
}

BOOL CNetMessage::GetInformation( const CString& name, CMessageInformation& information )
{
   if ( m_InformationBuffer0 != NULL )
   {
      ::NetApiBufferFree( m_InformationBuffer0 );
      m_InformationBuffer0 = NULL;
   }

   if ( m_InformationBuffer1 != NULL )
   {
      ::NetApiBufferFree( m_InformationBuffer1 );
      m_InformationBuffer1 = NULL;
   }

   m_ErrorCode = ::NetMessageNameGetInfo( (LMSTR) m_WideMachineName, 1, (LPBYTE *) &m_InformationBuffer1 );

   if ( m_ErrorCode == ERROR_ACCESS_DENIED )
   {
      m_ErrorCode = ::NetMessageNameGetInfo( (LMSTR) m_WideMachineName, 0, (LPBYTE *) &m_InformationBuffer0 );

      if ( m_ErrorCode != NERR_Success || m_InformationBuffer0 == NULL )
      {
         return( FALSE );
      }
      else
      {
         information.Copy( m_InformationBuffer0 ); 
      }
   }
   else if ( m_ErrorCode != NERR_Success || m_InformationBuffer1 == NULL )
   {
      return( FALSE );
   }
   else
   {
      information.Copy( m_Information1 );
   }

   return( TRUE );
}

BOOL CNetMessage::Enumerate( void )
{
   ::NetApiBufferFree( m_InformationBuffer0 );
   m_InformationBuffer0 = NULL;

   m_CurrentEntryNumber   = 0;
   m_NumberOfEntriesRead  = 0;
   m_ResumeHandle         = 0;
   m_TotalNumberOfEntries = 0;

   m_ErrorCode = ::NetMessageNameEnum( (LMSTR) m_WideMachineName, 
                                               0, 
                                   (LPBYTE *) &m_InformationBuffer0,
                                               65536,
                                              &m_NumberOfEntriesRead,
                                              &m_TotalNumberOfEntries,
                                              &m_ResumeHandle );

   if ( m_ErrorCode != NERR_Success || m_TransportBuffer == NULL || m_TransportNumberOfEntriesRead == 0 )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CNetMessage::GetNext( CNetMessage& information )
{
   if ( m_InformationBuffer100 != NULL )
   {
      information.Copy( m_InformationBuffer100 );
      ::NetApiBufferFree( m_InformationBuffer100 );
      m_InformationBuffer100 = NULL;
      return( TRUE );
   }

   if ( m_InformationBuffer101 != NULL )
   {
      information.Copy( m_InformationBuffer101 );
      ::NetApiBufferFree( m_InformationBuffer101 );
      m_InformationBuffer101 = NULL;
      return( TRUE );
   }

   if ( m_InformationBuffer102 != NULL )
   {
      information.Copy( m_InformationBuffer102 );
      ::NetApiBufferFree( m_InformationBuffer102 );
      m_InformationBuffer102 = NULL;
      return( TRUE );
   }

   information.Empty();
   return( FALSE );
}

BOOL CNetMessage::GetNext( CWorkstationTransport& information )
{
   if ( m_TransportCurrentEntryNumber < m_TransportTotalNumberOfEntries )
   {
      information.Copy( &m_TransportBuffer[ m_TransportCurrentEntryNumber ] );
      m_TransportCurrentEntryNumber++;
      return( TRUE );
   }

   information.Empty();
   return( FALSE );
}

void CNetMessage::Serialize( CArchive& archive )
{
   CNetwork::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_ErrorCode;
   }
   else
   {
      archive >> m_ErrorCode;
   }
}

#endif // 0
