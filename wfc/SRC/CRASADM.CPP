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
** $Workfile: CRASADM.CPP $
** $Revision: 19 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CRemoteAccessServiceAdministration" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CRemoteAccessServiceAdministration
*/

CRemoteAccessServiceAdministration::CRemoteAccessServiceAdministration()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::CRemoteAccessServiceAdministration()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_PortArray = NULL;
   m_Initialize();
}

CRemoteAccessServiceAdministration::~CRemoteAccessServiceAdministration()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::~CRemoteAccessServiceAdministration()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

BOOL CRemoteAccessServiceAdministration::ClearPortStatistics( const CString& port_name, LPCTSTR server_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::ClearPortStatistics()" ) );

   // We were passed a pointer, don't trust it

   try
   {
      CNetwork network_server_name( server_name );

      if ( server_name == NULL )
      {
         // OOPS! We need to use the name of this machine...

         TCHAR this_machine_name[ MAX_COMPUTERNAME_LENGTH + 1 ];

         DWORD machine_name_length = MAX_COMPUTERNAME_LENGTH + 1;
   
         ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

         if ( ::GetComputerName( this_machine_name, &machine_name_length ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't get computer name\n" ) );
            return( FALSE );
         }

         network_server_name.Open( this_machine_name );
      }

      WCHAR unicode_port_name[ UNCLEN + 1 ];
      ::ZeroMemory( unicode_port_name, sizeof( unicode_port_name ) );

#if ! defined( UNICODE )

      ::ASCII_to_UNICODE( port_name, unicode_port_name );

#else

      ::wcscpy( unicode_port_name, port_name );

#endif // UNICODE

      m_ErrorCode = ::RasAdminPortClearStatistics( (LPCWSTR) network_server_name, unicode_port_name );

      if ( m_ErrorCode != ERROR_SUCCESS )
      {
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessServiceAdministration::DisconnectPort( const CString& port_name, LPCTSTR server_name  )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::DisconnectPort()" ) );

   // We were passed a pointer, don't trust it

   try
   {
      CNetwork network_server_name( server_name );

      if ( server_name == NULL )
      {
         // OOPS! We need to use the name of this machine...

         TCHAR this_machine_name[ MAX_COMPUTERNAME_LENGTH + 1 ];

         DWORD machine_name_length = MAX_COMPUTERNAME_LENGTH + 1;

         ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

         if ( ::GetComputerName( this_machine_name, &machine_name_length ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't get computer name\n" ) );
            return( FALSE );
         }

         network_server_name.Open( this_machine_name );
      }

      WCHAR unicode_port_name[ UNCLEN + 1 ];
      ::ZeroMemory( unicode_port_name, sizeof( unicode_port_name ) );

#if ! defined( UNICODE )

      ::ASCII_to_UNICODE( port_name, unicode_port_name );

#else

      ::wcscpy( unicode_port_name, port_name );

#endif // UNICODE

      m_ErrorCode = ::RasAdminPortDisconnect( (LPCWSTR) network_server_name, unicode_port_name );

      if ( m_ErrorCode != ERROR_SUCCESS )
      {
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CRemoteAccessServiceAdministration::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );
}

#endif // _DEBUG

BOOL CRemoteAccessServiceAdministration::EnumeratePorts( LPCTSTR server_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::EnumeratePorts()" ) );

   m_Initialize();

   // We were passed a pointer, don't trust it

   try
   {
      CNetwork network_server_name( server_name );

      if ( server_name == NULL )
      {
         // OOPS! We need to use the name of this machine...

         TCHAR this_machine_name[ MAX_COMPUTERNAME_LENGTH + 1 ];

         DWORD machine_name_length = MAX_COMPUTERNAME_LENGTH + 1;

         ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

         if ( ::GetComputerName( this_machine_name, &machine_name_length ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't get computer name\n" ) );
            return( FALSE );
         }

         network_server_name.Open( this_machine_name );
      }

      WCHAR wide_machine_name[ MAX_COMPUTERNAME_LENGTH + 3 ];

      ZeroMemory( wide_machine_name, sizeof( wide_machine_name ) );

      ::wcscpy( wide_machine_name, L"\\\\" );
      ::wcscat( wide_machine_name, (LPCWSTR) network_server_name );

      DWORD return_value = 0;

#if defined( _DEBUG )      
      CString debug_string;
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) wide_machine_name, debug_string );
      WFCTRACEVAL( TEXT( "Network server name is " ), debug_string );
#endif // _DEBUG

      return_value = ::RasAdminPortEnum( (LPCWSTR) wide_machine_name, &m_PortArray, &m_TotalNumberOfEntries );

      if ( return_value != ERROR_SUCCESS )
      {
         WFCTRACEVAL( TEXT( "RasAdminPortEnum failed with " ), return_value );
         m_Initialize();
         m_ErrorCode = return_value;
         return( FALSE );
      }

      WFCTRACEVAL( TEXT( "Number of entries retrieved " ), m_TotalNumberOfEntries );

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

DWORD CRemoteAccessServiceAdministration::GetErrorCode( void ) const
{
   return( m_ErrorCode );
}

void CRemoteAccessServiceAdministration::GetErrorString( const UINT error_code, CString& error_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::GetErrorString()" ) );

   WCHAR temp_string[ 512 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );

   DWORD return_value = 0;

   return_value = ::RasAdminGetErrorString( error_code, temp_string, 511 );

   if ( return_value == ERROR_SUCCESS )
   {
      ::wfc_convert_lpcwstr_to_cstring( temp_string, error_string );
   }
   else
   {
      error_string.Empty();
   }
}

BOOL CRemoteAccessServiceAdministration::GetNext( CRemoteAccessServicePort& port )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::GetNext()" ) );
   ASSERT( m_PortArray != NULL );

   port.Empty();

   if ( m_PortArray == NULL )
   {
      return( FALSE );
   }

   if ( m_CurrentEntryNumber < m_TotalNumberOfEntries )
   {
      WFCTRACEVAL( TEXT( "Getting entry number " ), m_CurrentEntryNumber );
      port.Copy( &m_PortArray[ m_CurrentEntryNumber ] );
      m_CurrentEntryNumber++;
   }
   else
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CRemoteAccessServiceAdministration::GetUserAccountServer( CString& user_account_server_name, LPCTSTR ras_server_name, LPCTSTR ras_server_domain_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::GetUserAccountServer()" ) );

   // Idiot proof the parameters

   if ( ras_server_domain_name == NULL && ras_server_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // OK, at least one of the parameters is not null. This is a good thing.

      // Get ready to receive PDC name

      WCHAR primary_domain_controller_name[ UNCLEN + 1 ];

      ::ZeroMemory( primary_domain_controller_name, sizeof( primary_domain_controller_name ) );

      DWORD return_value = 0;

      if ( ras_server_domain_name != NULL && ras_server_name != NULL )
      {
         // CNetwork is cool because it will convert the name to a real server name
         // taking into account UNICODE and prepending

         CNetwork network_server_name( ras_server_name );
         CNetwork network_domain_name( ras_server_domain_name );

         return_value = ::RasAdminGetUserAccountServer( (LPCWSTR) network_domain_name, (LPCWSTR) network_server_name, primary_domain_controller_name );
      }
      else if ( ras_server_domain_name == NULL )
      {
         CNetwork network_server_name( ras_server_name );

         return_value = ::RasAdminGetUserAccountServer( NULL, (LPCWSTR) network_server_name, primary_domain_controller_name );
      }
      else
      {
         CNetwork network_domain_name( ras_server_domain_name );

         return_value = ::RasAdminGetUserAccountServer( (LPCWSTR) network_domain_name, NULL, primary_domain_controller_name );
      }

      if ( return_value == ERROR_SUCCESS )
      {
         ::wfc_convert_lpcwstr_to_cstring( primary_domain_controller_name, user_account_server_name );
         return( TRUE );
      }
 
      user_account_server_name.Empty();
      return( FALSE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

void CRemoteAccessServiceAdministration::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAdministration::m_Initialize()" ) );
   m_ErrorCode            = 0;
   m_TotalNumberOfEntries = 0;
   m_CurrentEntryNumber   = 0;

   if ( m_PortArray != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer" ) );
      ::RasAdminFreeBuffer( m_PortArray );
   }

   m_PortArray = NULL;
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessServiceAdministration</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking, source code">
<META name="description" content="The C++ class that encapsulates Remote Access Service (Dialup networking) administration.">
</HEAD>

<BODY>

<H1>CRemoteAccessServiceAdministration : CObject</H1>
$Revision: 19 $
<HR>

<H2>Description</H2>

This class handles Remote Access Service Administration. It is
still under development.

<H2>Data Members</H2><B>None.</B>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B><A NAME="GetErrorString">GetErrorString</A></B>( const UINT error_code, CString&amp; error_string ) const</PRE><DD>

<DT><PRE>DWORD <B><A NAME="GetErrorCode">GetErrorCode</A></B>( void ) const</PRE><DD>
Returns the error code should any method return FALSE.

<DT><PRE>BOOL <B><A NAME="GetUserAccountServer">GetUserAccountServer</A></B>( CString&amp; user_account_server_name, LPCTSTR ras_server_name, LPCTSTR ras_server_domain_name = NULL )</PRE><DD>

<DT><PRE>BOOL <B><A NAME="ClearPortStatistics">ClearPortStatistics</A></B>( const CString&amp; port_name, LPCTSTR server_name = NULL )</PRE><DD>

<DT><PRE>BOOL <B><A NAME="DisconnectPort">DisconnectPort</A></B>( const CString&amp; port_name, LPCTSTR server_name = NULL )</PRE><DD>

<DT><PRE>BOOL <B><A NAME="EnumeratePorts">EnumeratePorts</A></B>( LPCTSTR server_name = NULL )</PRE><DD>
Let's you enumerator the RAS ports on the local machine or on
a machine on the network.

<DT><PRE>BOOL <B><A NAME="GetNext">GetNext</A></B>( CRemoteAccessServicePort&amp; port )</PRE><DD>

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<B>CRemoteAccessServiceAdministration</B> uses the following API's:

<UL>
<LI>GetComputerName
<LI>RasAdminFreeBuffer
<LI>RasAdminGetErrorString
<LI>RasAdminGetUserAccountServer
<LI>RasAdminPortClearStatistics
<LI>RasAdminPortDisconnect
<LI>RasAdminPortEnum
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CRASADM.CPP $<BR>
$Modtime: 1/04/00 5:18a $
</BODY>

</HTML>
#endif
