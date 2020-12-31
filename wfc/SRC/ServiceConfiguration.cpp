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
** $Workfile: ServiceConfiguration.cpp $
** $Revision: 17 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if ! defined( WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CServiceConfigurationA, CObject, 1 );
IMPLEMENT_SERIAL( CServiceConfigurationW, CObject, 1 );
#endif // WFC_NO_SERIALIZATION

// Here's the ASCII Version

CServiceConfigurationA::CServiceConfigurationA()
{
   Empty();
}

CServiceConfigurationA::CServiceConfigurationA( const CServiceConfigurationA& source )
{
   Copy( source );
}

CServiceConfigurationA::CServiceConfigurationA( const CServiceConfigurationA * source )
{
   Copy( source );
}

CServiceConfigurationA::CServiceConfigurationA( const _QUERY_SERVICE_CONFIGA& source )
{
   Copy( source );
}

CServiceConfigurationA::CServiceConfigurationA( const _QUERY_SERVICE_CONFIGA * source )
{
   Copy( source );
}

CServiceConfigurationA::~CServiceConfigurationA()
{
   Empty();
}

void CServiceConfigurationA::Copy( const CServiceConfigurationA& source )
{
   Empty();

   m_TypeOfService        = source.m_TypeOfService;
   m_WhenToStart          = source.m_WhenToStart;
   m_ErrorControl         = source.m_ErrorControl;
   m_Tag                  = source.m_Tag;
   m_NameOfExecutableFile = source.m_NameOfExecutableFile;
   m_LoadOrderGroup       = source.m_LoadOrderGroup;
   m_StartName            = source.m_StartName;
   m_DisplayName          = source.m_DisplayName;

   int index             = 0;
   int number_of_strings = source.m_Dependencies.GetSize();

   while( index < number_of_strings )
   {
      m_Dependencies.Add( source.m_Dependencies.GetAt( index ) );
      index++;
   }
}

void CServiceConfigurationA::Copy( const CServiceConfigurationA * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == this )
   {
      return;
   }

   // The user passed us a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationA::Copy( const _QUERY_SERVICE_CONFIGA& source )
{
   // The user didn't pass us a pointer but they did pass us
   // something that contains pointers so we cannot trust it

   try
   {
      Empty();

      // Copy the data structure stuff first...

      m_TypeOfService      = source.dwServiceType;
      m_WhenToStart        = source.dwStartType;
      m_ErrorControl       = source.dwErrorControl;
      m_Tag                = source.dwTagId;

      if ( source.lpBinaryPathName != NULL )
      {
         m_NameOfExecutableFile = source.lpBinaryPathName;
      }
      else
      {
         m_NameOfExecutableFile.Empty();
      }

      if ( source.lpLoadOrderGroup != NULL )
      {
         m_LoadOrderGroup = source.lpLoadOrderGroup;
      }
      else
      {
         m_LoadOrderGroup.Empty();
      }

      if ( source.lpServiceStartName != NULL )
      {
         m_StartName = source.lpServiceStartName;
      }
      else
      {
         m_StartName.Empty();
      }

      if ( source.lpDisplayName != NULL )
      {
         m_DisplayName = source.lpDisplayName;
      }
      else
      {
         m_DisplayName.Empty();
      }

      // Now for the fun part, double-NULL terminated string....

      CString string_to_add;

      if ( source.lpDependencies != NULL )
      {
         BYTE *temp_pointer = (BYTE *) source.lpDependencies;

         while ( temp_pointer[ 0 ] != 0x00 )
         {
            wfc_convert_lpcstr_to_cstring( reinterpret_cast< const char * >( temp_pointer ), string_to_add );

            m_Dependencies.Add( string_to_add );

            // Thanks go to Ullrich Pollaehne [Ullrich_Pollaehne@ka2.maus.de]
            // for noticing my stupidity here (i.e. finding a bug);
            temp_pointer += ::strlen( (LPCSTR) temp_pointer ) + 1; // YES, this should be strlen() and not _tcslen()
         }
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationA::Copy( const _QUERY_SERVICE_CONFIGA * source )
{
   ASSERT( source != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationA::Empty( void )
{
   // We put a try block here because it is called from
   // catch blocks. In other words, we absolutely cannot
   // fail.

   try
   {
      m_TypeOfService = 0;
      m_WhenToStart   = 0;
      m_ErrorControl  = 0;
      m_Tag           = 0;
      m_NameOfExecutableFile.Empty();
      m_LoadOrderGroup.Empty();
      m_StartName.Empty();
      m_DisplayName.Empty();
      m_Dependencies.RemoveAll();
   }
   catch( ... )
   {
      return;
   }
}

void CServiceConfigurationA::GetDependencies( CStringArray& dependencies ) const
{
   int index = 0;
   int number_of_dependencies = m_Dependencies.GetSize();

   dependencies.RemoveAll();

   while( index < number_of_dependencies )
   {
      dependencies.Add( m_Dependencies.GetAt( index ) );
      index++;
   }
}

void CServiceConfigurationA::GetDisplayName( CString& display_name ) const
{
   display_name = m_DisplayName;
}

DWORD CServiceConfigurationA::GetErrorControl( void ) const
{
   return( m_ErrorControl );
}

void CServiceConfigurationA::GetLoadOrderGroup( CString& load_order_group ) const
{
   load_order_group = m_LoadOrderGroup;
}

void CServiceConfigurationA::GetNameOfExecutableFile( CString& name_of_executable ) const
{
   name_of_executable = m_NameOfExecutableFile;
}

void CServiceConfigurationA::GetStartName( CString& start_name ) const
{
   start_name = m_StartName;
}

DWORD CServiceConfigurationA::GetTag( void ) const
{
   return( m_Tag );
}

DWORD CServiceConfigurationA::GetTypeOfService( void ) const
{
   return( m_TypeOfService );
}

DWORD CServiceConfigurationA::GetWhenToStart( void ) const
{
   return( m_WhenToStart );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CServiceConfigurationA::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_TypeOfService;
      archive << m_WhenToStart;
      archive << m_ErrorControl;
      archive << m_Tag;
      archive << m_NameOfExecutableFile;
      archive << m_LoadOrderGroup;
      archive << m_StartName;
      archive << m_DisplayName;
   }
   else
   {
      archive >> m_TypeOfService;
      archive >> m_WhenToStart;
      archive >> m_ErrorControl;
      archive >> m_Tag;
      archive >> m_NameOfExecutableFile;
      archive >> m_LoadOrderGroup;
      archive >> m_StartName;
      archive >> m_DisplayName;
   }

   m_Dependencies.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

// Thanks go to Ullrich Pollaehne [Ullrich_Pollaehne@ka2.maus.de] for
// pointing out I had no implementation for these guys.

CServiceConfigurationA& CServiceConfigurationA::operator=( const CServiceConfigurationA& source )
{
   Copy( source );
   return( *this );
}

CServiceConfigurationA& CServiceConfigurationA::operator=( const _QUERY_SERVICE_CONFIGA& source )
{
   Copy( source );
   return( *this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CServiceConfigurationA::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_TypeOfService is        "   ) << m_TypeOfService        << TEXT( "\n" );
   dump_context << TEXT( "   m_WhenToStart is          "   ) << m_WhenToStart          << TEXT( "\n" );
   dump_context << TEXT( "   m_ErrorControl is         "   ) << m_ErrorControl         << TEXT( "\n" );
   dump_context << TEXT( "   m_Tag is                  "   ) << m_Tag                  << TEXT( "\n" );
   dump_context << TEXT( "   m_NameOfExecutableFile is \"" ) << m_NameOfExecutableFile << TEXT( "\"\n" );
   dump_context << TEXT( "   m_LoadOrderGroup is       \"" ) << m_LoadOrderGroup       << TEXT( "\"\n" );
   dump_context << TEXT( "   m_StartName is            \"" ) << m_StartName            << TEXT( "\"\n" );
   dump_context << TEXT( "   m_DisplayName is          \"" ) << m_DisplayName          << TEXT( "\"\n" );

   int index = 0;

   while( index < m_Dependencies.GetSize() )
   {
      dump_context << TEXT( "   m_Dependencies[ " ) << index << TEXT( " ] is \"" ) << m_Dependencies.GetAt( index ) << TEXT( "\"\n" );
      index++;
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// Here's the UNICODE version

CServiceConfigurationW::CServiceConfigurationW()
{
   Empty();
}

CServiceConfigurationW::CServiceConfigurationW( const CServiceConfigurationW& source )
{
   Copy( source );
}

CServiceConfigurationW::CServiceConfigurationW( const CServiceConfigurationW * source )
{
   Copy( source );
}

CServiceConfigurationW::CServiceConfigurationW( const QUERY_SERVICE_CONFIGW& source )
{
   Copy( source );
}

CServiceConfigurationW::CServiceConfigurationW( const QUERY_SERVICE_CONFIGW * source )
{
   Copy( source );
}

CServiceConfigurationW::~CServiceConfigurationW()
{
   Empty();
}

void CServiceConfigurationW::Copy( const CServiceConfigurationW& source )
{
   Empty();

   m_TypeOfService        = source.m_TypeOfService;
   m_WhenToStart          = source.m_WhenToStart;
   m_ErrorControl         = source.m_ErrorControl;
   m_Tag                  = source.m_Tag;
   m_NameOfExecutableFile = source.m_NameOfExecutableFile;
   m_LoadOrderGroup       = source.m_LoadOrderGroup;
   m_StartName            = source.m_StartName;
   m_DisplayName          = source.m_DisplayName;

   int index             = 0;
   int number_of_strings = source.m_Dependencies.GetSize();

   while( index < number_of_strings )
   {
      m_Dependencies.Add( source.m_Dependencies.GetAt( index ) );
      index++;
   }
}

void CServiceConfigurationW::Copy( const CServiceConfigurationW * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationW::Copy( const QUERY_SERVICE_CONFIGW& source )
{
   // The user didn't pass us a pointer but they did pass us
   // something that contains pointers so we cannot trust it

   try
   {
      Empty();

      // Copy the data structure stuff first...

      m_TypeOfService      = source.dwServiceType;
      m_WhenToStart        = source.dwStartType;
      m_ErrorControl       = source.dwErrorControl;
      m_Tag                = source.dwTagId;

      if ( source.lpBinaryPathName != NULL )
      {
#if defined( UNICODE )
         m_NameOfExecutableFile = source.lpBinaryPathName;
#else // UNICODE
         wfc_convert_lpcwstr_to_cstring( source.lpBinaryPathName, m_NameOfExecutableFile );
#endif // UNICODE
      }
      else
      {
         m_NameOfExecutableFile.Empty();
      }

      if ( source.lpLoadOrderGroup != NULL )
      {
#if defined( UNICODE )
         m_LoadOrderGroup = source.lpLoadOrderGroup;
#else // UNICODE
         wfc_convert_lpcwstr_to_cstring( source.lpLoadOrderGroup, m_LoadOrderGroup );
#endif // UNICODE
      }
      else
      {
         m_LoadOrderGroup.Empty();
      }

      if ( source.lpServiceStartName != NULL )
      {
#if defined( UNICODE )
         m_StartName = source.lpServiceStartName;
#else // UNICODE
         wfc_convert_lpcwstr_to_cstring( source.lpServiceStartName, m_StartName );
#endif // UNICODE
      }
      else
      {
         m_StartName.Empty();
      }

      if ( source.lpDisplayName != NULL )
      {
#if defined( UNICODE )
         m_DisplayName = source.lpDisplayName;
#else // UNICODE
         wfc_convert_lpcwstr_to_cstring( source.lpDisplayName, m_DisplayName );
#endif // UNICODE
      }
      else
      {
         m_DisplayName.Empty();
      }

      // Now for the fun part, double-NULL terminated string....

      if ( source.lpDependencies != NULL )
      {
         TCHAR *temp_pointer = (TCHAR *) source.lpDependencies;

         while ( temp_pointer[ 0 ] != 0x00 )
         {
            m_Dependencies.Add( temp_pointer );
            temp_pointer += wcslen( (LPCWSTR) temp_pointer ) + 1;
         }
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationW::Copy( const QUERY_SERVICE_CONFIGW * source )
{
   ASSERT( source != NULL );

   // The user passed us a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CServiceConfigurationW::Empty( void )
{
   // We put a try block here because it is called from
   // catch blocks. In other words, we absolutely cannot
   // fail.

   try
   {
      m_TypeOfService = 0;
      m_WhenToStart   = 0;
      m_ErrorControl  = 0;
      m_Tag           = 0;
      m_NameOfExecutableFile.Empty();
      m_LoadOrderGroup.Empty();
      m_StartName.Empty();
      m_DisplayName.Empty();
      m_Dependencies.RemoveAll();
   }
   catch( ... )
   {
      return;
   }
}

void CServiceConfigurationW::GetDependencies( CStringArray& dependencies ) const
{
   int index                  = 0;
   int number_of_dependencies = m_Dependencies.GetSize();

   dependencies.RemoveAll();

   while( index < number_of_dependencies )
   {
      dependencies.Add( m_Dependencies.GetAt( index ) );
      index++;
   }
}

void CServiceConfigurationW::GetDisplayName( CString& display_name ) const
{
   display_name = m_DisplayName;
}

DWORD CServiceConfigurationW::GetErrorControl( void ) const
{
   return( m_ErrorControl );
}

void CServiceConfigurationW::GetLoadOrderGroup( CString& load_order_group ) const
{
   load_order_group = m_LoadOrderGroup;
}

void CServiceConfigurationW::GetNameOfExecutableFile( CString& name_of_executable ) const
{
   name_of_executable = m_NameOfExecutableFile;
}

void CServiceConfigurationW::GetStartName( CString& start_name ) const
{
   start_name = m_StartName;
}

DWORD CServiceConfigurationW::GetTag( void ) const
{
   return( m_Tag );
}

DWORD CServiceConfigurationW::GetTypeOfService( void ) const
{
   return( m_TypeOfService );
}

DWORD CServiceConfigurationW::GetWhenToStart( void ) const
{
   return( m_WhenToStart );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CServiceConfigurationW::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_TypeOfService;
      archive << m_WhenToStart;
      archive << m_ErrorControl;
      archive << m_Tag;
      archive << m_NameOfExecutableFile;
      archive << m_LoadOrderGroup;
      archive << m_StartName;
      archive << m_DisplayName;
   }
   else
   {
      archive >> m_TypeOfService;
      archive >> m_WhenToStart;
      archive >> m_ErrorControl;
      archive >> m_Tag;
      archive >> m_NameOfExecutableFile;
      archive >> m_LoadOrderGroup;
      archive >> m_StartName;
      archive >> m_DisplayName;
   }

   m_Dependencies.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

// Thanks go to Ullrich Pollaehne [Ullrich_Pollaehne@ka2.maus.de] for
// pointing out I had no implementation for these guys.

CServiceConfigurationW& CServiceConfigurationW::operator=( const CServiceConfigurationW& source )
{
   Copy( source );
   return( *this );
}

CServiceConfigurationW& CServiceConfigurationW::operator=( const _QUERY_SERVICE_CONFIGW& source )
{
   Copy( source );
   return( *this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CServiceConfigurationW::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_TypeOfService is        "   ) << m_TypeOfService        << TEXT( "\n" );
   dump_context << TEXT( "   m_WhenToStart is          "   ) << m_WhenToStart          << TEXT( "\n" );
   dump_context << TEXT( "   m_ErrorControl is         "   ) << m_ErrorControl         << TEXT( "\n" );
   dump_context << TEXT( "   m_Tag is                  "   ) << m_Tag                  << TEXT( "\n" );
   dump_context << TEXT( "   m_NameOfExecutableFile is \"" ) << m_NameOfExecutableFile << TEXT( "\"\n" );
   dump_context << TEXT( "   m_LoadOrderGroup is       \"" ) << m_LoadOrderGroup       << TEXT( "\"\n" );
   dump_context << TEXT( "   m_StartName is            \"" ) << m_StartName            << TEXT( "\"\n" );
   dump_context << TEXT( "   m_DisplayName is          \"" ) << m_DisplayName          << TEXT( "\"\n" );

   int index = 0;

   while( index < m_Dependencies.GetSize() )
   {
      dump_context << TEXT( "   m_Dependencies[ " ) << index << TEXT( " ] is \"" ) << m_Dependencies.GetAt( index ) << TEXT( "\"\n" );
      index++;
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source
