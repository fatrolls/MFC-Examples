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
** $Workfile: cnetrsrc.cpp $
** $Revision: 18 $
** $Modtime: 1/04/00 5:16a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_DYNAMIC( CNetworkResources, CNetwork )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

// TO DO: Add "net use" capability, WNetAddConnection

CNetworkResources::CNetworkResources()
{
   WFCLTRACEINIT( TEXT( "CNetworkResources::CNetworkResources()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkResources::~CNetworkResources()
{
   WFCLTRACEINIT( TEXT( "CNetworkResources::~CNetworkResources()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_ResumeHandle != NULL )
   {
      WFCTRACE( TEXT( "Closing Enumeration Handle" ) );
      ::WNetCloseEnum( m_ResumeHandle );
      m_ResumeHandle = NULL;
   }

   m_Initialize();
}

void CNetworkResources::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkResources::m_Initialize()" ) );

   m_ErrorCode    = 0;
   m_ResumeHandle = (HANDLE) NULL;
   ::ZeroMemory( &m_NetResource, sizeof( m_NetResource ) );
}

BOOL CNetworkResources::Enumerate( CNetworkResourceInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkResources::Enumerate()" ) );

   if ( m_ResumeHandle != NULL )
   {
      WFCTRACE( TEXT( "Closing Enumeration Handle" ) );
      ::WNetCloseEnum( m_ResumeHandle );
      m_ResumeHandle = NULL;
   }

   ::ZeroMemory( &m_NetResource, sizeof( m_NetResource ) );
   m_NetResource.dwUsage = usageContainer;

   NETRESOURCE *net_resource_parameter = (NETRESOURCE *) NULL;

   /*
   ** Let's see what we want to enumerate
   */

   switch( information.Scope )
   {
      case scopeConnected: // information.Usage is ignored

         break;
            
      case scopePersistent:  // information.Usage is ignored

         break;

      case scopeAll:

         break;

      default:

         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
   }

   switch( information.Usage )
   {
      case usageAll:

         net_resource_parameter = (NETRESOURCE *) NULL;
         break;

      case usageConnectable:
      case usageContainer:

         net_resource_parameter = &m_NetResource;
         break;

      default:

         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
   }

   m_ErrorCode = ::WNetOpenEnum( information.Scope, 
                                 information.Type, 
                                 information.Usage, 
                                 net_resource_parameter,
                                &m_ResumeHandle );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else if ( m_ErrorCode == ERROR_EXTENDED_ERROR )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }

   return( FALSE );
}

BOOL CNetworkResources::GetNext( CNetworkResourceInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkResources::GetNext()" ) );

   DWORD number_of_entries = 1;
   DWORD size_of_buffer    = sizeof( m_NetResource );

   m_ErrorCode = ::WNetEnumResource( m_ResumeHandle,
                                    &number_of_entries,
                                    &m_NetResource,
                                    &size_of_buffer );

   if ( m_ErrorCode == NO_ERROR )
   {
      information.Copy( &m_NetResource );
      return( TRUE );
   }
   else if ( m_ErrorCode == ERROR_EXTENDED_ERROR )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
                                        
   return( FALSE );
}

// End of source
