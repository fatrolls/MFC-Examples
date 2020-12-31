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
** $Workfile: cras.cpp $
** $Revision: 37 $
** $Modtime: 1/17/00 9:12a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// Let's define a little function to ease debugging

#if defined( _DEBUG )

static LPCTSTR __convert_RASCONNSTATE_to_string( DWORD ras_state )
{
   switch( ras_state )
   {
      case RASCS_OpenPort:

         return( TEXT( "RASCS_OpenPort - The communication port is about to be opened." ) );

      case RASCS_PortOpened:

         return( TEXT( "RASCS_PortOpened - The communication port has been opened successfully." ) );

      case RASCS_ConnectDevice:

         return( TEXT( "RASCS_ConnectDevice - A device is about to be connected. RasGetConnectStatus can be called to determine the name and type of the device being connected." ) );

      case RASCS_DeviceConnected:

         return( TEXT( "RASCS_DeviceConnected - A device has connected successfully. RasGetConnectStatus can be called to determine the name and type of the device being connected." ) );

      case RASCS_AllDevicesConnected:

         return( TEXT( "RASCS_AllDevicesConnected - All devices in the device chain have successfully connected. At this point, the physical link is established." ) );
  
      case RASCS_Authenticate:

         return( TEXT( "RASCS_Authenticate - The authentication process is starting. Remote access does not allow the remote client to generate any traffic on the LAN until authentication has been successfully completed." ) );
 
      case RASCS_AuthNotify:

         return( TEXT( "RASCS_AuthNotify - An authentication event has occurred. If dwError is zero, this event will be immediately followed by one of the more specific authentication states following. If dwError is nonzero, authentication has failed, and the error value indicates why." ) );

      case RASCS_AuthRetry:

         return( TEXT( "RASCS_AuthRetry - The client has requested another validation attempt with a new user name/password/domain. This state does not occur in Windows NT version 3.1." ) );
 
      case RASCS_AuthCallback:

         return( TEXT( "RASCS_AuthCallback - The remote access server has requested a callback number. This occurs only if the user has “Set By Caller” callback privilege on the server." ) );
 
      case RASCS_AuthChangePassword:

         return( TEXT( "RASCS_AuthChangePassword - The client has requested to change the password on the account. This state does not occur in Windows NT version 3.1." ) );
 
      case RASCS_AuthProject:

         return( TEXT( "RASCS_AuthProject - The projection phase is starting." ) );
 
      case RASCS_AuthLinkSpeed:

         return( TEXT( "RASCS_AuthLinkSpeed - The link-speed calculation phase is starting." ) );
 
      case RASCS_AuthAck:

         return( TEXT( "RASCS_AuthAck - An authentication request is being acknowledged." ) );
 
      case RASCS_ReAuthenticate:

         return( TEXT( "RASCS_ReAuthenticate - Reauthentication (after callback) is starting." ) );
 
      case RASCS_Authenticated:

         return( TEXT( "RASCS_Authenticated - The client has successfully completed authentication." ) );
 
      case RASCS_PrepareForCallback:

         return( TEXT( "RASCS_PrepareForCallback - The line is about to disconnect in preparation for callback." ) );
 
      case RASCS_WaitForModemReset:

         return( TEXT( "RASCS_WaitForModemReset - The client is delaying in order to give the modem time to reset itself in preparation for callback." ) );
 
      case RASCS_WaitForCallback:

         return( TEXT( "RASCS_WaitForCallback - The client is waiting for an incoming call from the remote access server." ) );
 
      case RASCS_Projected:

         return( TEXT( "RASCS_Projected - This state occurs after the RASCS_AuthProject state. It indicates that projection result information is available. You can access the projection result information by calling RasGetProjectionInfo." ) );
 
      case RASCS_StartAuthentication:

         return( TEXT( "RASCS_StartAuthentication - Windows 95 only: Indicates that user authentication is being initiated or retried." ) );
 
      case RASCS_CallbackComplete:

         return( TEXT( "RASCS_CallbackComplete - Windows 95 only: Indicates that the client has been called back and is about to resume authentication." ) );
 
      case RASCS_LogonNetwork:

         return( TEXT( "RASCS_LogonNetwork - Windows 95 only: Indicates that the client is logging on to the network." ) );
 
      case RASCS_SubEntryConnected:

         return( TEXT( "RASCS_SubEntryConnected - When dialing a multilink phone-book entry, this state indicates that a subentry has been connected during the dialing process. The dwSubEntry parameter of a RasDialFunc2 callback function indicates the index of the subentry. When the final state of all subentries in the phone-book entry has been determined, the connection state is RASCS_Connected if one or more subentries have been connected successfully." ) );
 
      case RASCS_SubEntryDisconnected:

         return( TEXT( "RASCS_SubEntryDisconnected - When dialing a multilink phone-book entry, this state indicates that a subentry has been disconnected during the dialing process. The dwSubEntry parameter of a RasDialFunc2 callback function indicates the index of the subentry." ) );
 
      case RASCS_Interactive:

         return( TEXT( "RASCS_Interactive - This state corresponds to the terminal state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1." ) );
 
      case RASCS_RetryAuthentication:

         return( TEXT( "RASCS_RetryAuthentication - This state corresponds to the retry authentication state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1." ) );
 
      case RASCS_CallbackSetByCaller:

         return( TEXT( "RASCS_CallbackSetByCaller - This state corresponds to the callback state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1." ) );
 
      case RASCS_PasswordExpired:

         return( TEXT( "RASCS_PasswordExpired - This state corresponds to the change password state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1." ) );

      case RASCS_Connected:

         return( TEXT( "RASCS_Connected - Successful connection." ) );

      case RASCS_Disconnected:

         return( TEXT( "RASCS_Disconnected - Disconnection or failed connection." ) );

#if ( WINVER >= 0x500 )

      case RASCS_InvokeEapUI:

         return( TEXT( "RASCS_InvokeEapUI - Invoke Authentication User Interface." ) );

#endif // WINVER >= 0x500

      default:

         return( TEXT( "Unknown state." ) );
   }
}

#endif // _DEBUG

/*
** CRASAuthenticationMessageBlock
*/

CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock( const RASAMB *source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock( RASAMB )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock( const CRemoteAccessServiceAuthenticationMessageBlock& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::CRemoteAccessServiceAuthenticationMessageBlock( CRemoteAccessServiceAuthenticationMessageBlock )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceAuthenticationMessageBlock::~CRemoteAccessServiceAuthenticationMessageBlock()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::~CRemoteAccessServiceAuthenticationMessageBlock()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CRemoteAccessServiceAuthenticationMessageBlock::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::m_Initialize()" ) );

   ::ZeroMemory( (RASAMB *) this, sizeof( RASAMB ) );
   dwSize = sizeof( RASAMB );
}

void CRemoteAccessServiceAuthenticationMessageBlock::Copy( const RASAMB *source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::Copy()" ) );

   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwError = source->dwError;
      bLana   = source->bLana;
      _tcscpy( szNetBiosError, source->szNetBiosError );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CRemoteAccessServiceAuthenticationMessageBlock::Copy( const CRemoteAccessServiceAuthenticationMessageBlock& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   dwError = source.dwError;
   bLana   = source.bLana;
   _tcscpy( szNetBiosError, source.szNetBiosError );
}

BYTE CRemoteAccessServiceAuthenticationMessageBlock::GetLana( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::GetLana()" ) );
   return( bLana );
}

DWORD CRemoteAccessServiceAuthenticationMessageBlock::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::GetErrorCode()" ) );
   return( dwError );
}

void CRemoteAccessServiceAuthenticationMessageBlock::GetErrorString( CString &return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::GetErrorString()" ) );
   return_string = szNetBiosError;
}

CRemoteAccessServiceAuthenticationMessageBlock& CRemoteAccessServiceAuthenticationMessageBlock::operator=( const CRemoteAccessServiceAuthenticationMessageBlock& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceAuthenticationMessageBlock::operator=()" ) );
   Copy( source );
   return( *this );
}

/*
** CRemoteAccessServiceNetBEUIFramer
*/

CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer( const RASPPPNBF *source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer( RASPPPNBF )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer( const CRemoteAccessServiceNetBEUIFramer& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::CRemoteAccessServiceNetBEUIFramer( CRemoteAccessServiceNetBEUIFramer )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceNetBEUIFramer::~CRemoteAccessServiceNetBEUIFramer()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::~CRemoteAccessServiceNetBEUIFramer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CRemoteAccessServiceNetBEUIFramer::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::m_Initialize()" ) );

   ::ZeroMemory( (RASPPPNBF *) this, sizeof( RASPPPNBF ) );
   dwSize = sizeof( RASPPPNBF );
}

void CRemoteAccessServiceNetBEUIFramer::Copy( const RASPPPNBF *source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::Copy()" ) );

   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwError        = source->dwError;
      dwNetBiosError = source->dwNetBiosError;
      bLana          = source->bLana;
      _tcscpy( szNetBiosError,    source->szNetBiosError    );
      _tcscpy( szWorkstationName, source->szWorkstationName );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CRemoteAccessServiceNetBEUIFramer::Copy( const CRemoteAccessServiceNetBEUIFramer& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   dwError        = source.dwError;
   dwNetBiosError = source.dwNetBiosError;
   bLana          = source.bLana;                      
   _tcscpy( szNetBiosError,    source.szNetBiosError    );
   _tcscpy( szWorkstationName, source.szWorkstationName );
}

BYTE CRemoteAccessServiceNetBEUIFramer::GetLana( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::GetLana()" ) );
   return( bLana );
}

DWORD CRemoteAccessServiceNetBEUIFramer::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::GetErrorCode()" ) );
   return( dwError );
}

DWORD CRemoteAccessServiceNetBEUIFramer::GetNetBiosErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::GetNetBiosErrorCode()" ) );
   return( dwNetBiosError );
}

void CRemoteAccessServiceNetBEUIFramer::GetErrorString( CString& return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::GetErrorString()" ) );
   return_string = szNetBiosError;
}

void CRemoteAccessServiceNetBEUIFramer::GetWorkstationName( CString& return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::GetWorkstationName()" ) );
   return_string = szWorkstationName;
}

CRemoteAccessServiceNetBEUIFramer& CRemoteAccessServiceNetBEUIFramer::operator=( const CRemoteAccessServiceNetBEUIFramer& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceNetBEUIFramer::operator=()" ) );
   Copy( source );
   return( *this );
}

/*
** CRemoteAccessServiceInternetworkPacketExchange
*/

CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange( const RASPPPIPX * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange( RASPPPIPX )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange( const CRemoteAccessServiceInternetworkPacketExchange& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::CRemoteAccessServiceInternetworkPacketExchange( CRemoteAccessServiceInternetworkPacketExchange )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceInternetworkPacketExchange::~CRemoteAccessServiceInternetworkPacketExchange()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::~CRemoteAccessServiceInternetworkPacketExchange()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CRemoteAccessServiceInternetworkPacketExchange::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::m_Initialize()" ) );
   ::ZeroMemory( (RASPPPIPX *) this, sizeof( RASPPPIPX ) );
   dwSize = sizeof( RASPPPIPX );
}

void CRemoteAccessServiceInternetworkPacketExchange::Copy( const RASPPPIPX * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwError = source->dwError;
      _tcscpy( szIpxAddress, source->szIpxAddress );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CRemoteAccessServiceInternetworkPacketExchange::Copy( const CRemoteAccessServiceInternetworkPacketExchange& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::Copy()" ) );
   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   dwError = source.dwError;
   _tcscpy( szIpxAddress, source.szIpxAddress );
}

DWORD CRemoteAccessServiceInternetworkPacketExchange::GetErrorCode( void ) const
{
   return( dwError );
}

void CRemoteAccessServiceInternetworkPacketExchange::GetIPXAddress( CString& return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::GetIPXAddress()" ) );
   return_string = szIpxAddress;
}

CRemoteAccessServiceInternetworkPacketExchange& CRemoteAccessServiceInternetworkPacketExchange::operator=( const CRemoteAccessServiceInternetworkPacketExchange& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetworkPacketExchange::operator=()" ) );
   Copy( source );
   return( *this );
}

/*
** CRemoteAccessServiceInternetProtocol
*/

CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol( const RASPPPIP * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol( RASPPPIP )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol( const CRemoteAccessServiceInternetProtocol& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::CRemoteAccessServiceInternetProtocol( CRemoteAccessServiceInternetProtocol )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceInternetProtocol::~CRemoteAccessServiceInternetProtocol()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::~CRemoteAccessServiceInternetProtocol()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CRemoteAccessServiceInternetProtocol::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::m_Initialize()" ) );
   ::ZeroMemory( (RASPPPIP *) this, sizeof( RASPPPIP ) );
   dwSize = sizeof( RASPPPIP );
}

void CRemoteAccessServiceInternetProtocol::Copy( const RASPPPIP * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwError = source->dwError;
      _tcscpy( szIpAddress, source->szIpAddress );

#if ! defined( WINNT35COMPATIBLE )

      _tcscpy( szServerIpAddress, source->szServerIpAddress );

#endif // WINNT35COMPATIBLE
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CRemoteAccessServiceInternetProtocol::Copy( const CRemoteAccessServiceInternetProtocol& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   dwError = source.dwError;
   _tcscpy( szIpAddress, source.szIpAddress );

#if ! defined( WINNT35COMPATIBLE )

   _tcscpy( szServerIpAddress, source.szServerIpAddress );

#endif // WINNT35COMPATIBLE
}

DWORD CRemoteAccessServiceInternetProtocol::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::GetErrorCode()" ) );
   return( dwError );
}

void CRemoteAccessServiceInternetProtocol::GetIPAddress( CString& return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::GetIPAddress()" ) );
   return_string = szIpAddress;
}

#if ! defined( WINNT35COMPATIBLE )

void CRemoteAccessServiceInternetProtocol::GetServerIPAddress( CString& return_string ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::GetServerIPAddress()" ) );
   return_string = szServerIpAddress;
}

#endif // WINNT35COMPATIBLE

CRemoteAccessServiceInternetProtocol& CRemoteAccessServiceInternetProtocol::operator=( const CRemoteAccessServiceInternetProtocol& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceInternetProtocol::operator=()" ) );
   Copy( source );
   return( *this );
}

/*
** CRemoteAccessService
*/

CRemoteAccessService::CRemoteAccessService()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::CRemoteAccessService()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Thunk_p = NULL;
   m_Initialize();
   m_InitializeThunk();
   m_AutomaticallyClose = FALSE;
}

CRemoteAccessService::~CRemoteAccessService()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::~CRemoteAccessService()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_Initialize();

   if ( m_Thunk_p != NULL )
   {
      if ( m_Thunk_p->dll_instance_handle != NULL )
      {
         ::FreeLibrary( m_Thunk_p->dll_instance_handle );
      }

      ZeroMemory( m_Thunk_p, sizeof( WFC_RAS_THUNK ) );
      delete m_Thunk_p;
      m_Thunk_p = NULL;
   }
}

BOOL CRemoteAccessService::Close( LPCTSTR name_of_connection )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::Close()" ) );
   //ASSERT_VALID( this );

   CString connection_name;

#if defined( _DEBUG )

   DWORD number_of_tries = 0;

#endif

   // We were passed a pointer, don't trust it

   try
   {
      if ( name_of_connection == NULL )
      {
         connection_name = m_Name;

         m_ErrorCode = m_Thunk_p->RasHangUp( m_ConnectionHandle );

         if ( m_ErrorCode == 0 )
         {
            // Code around the NT bug

            while( m_Thunk_p->RasGetConnectStatus( m_ConnectionHandle, &m_ConnectionStatus ) != ERROR_INVALID_HANDLE )
            {
#if defined( _DEBUG )
               number_of_tries++;
#endif
               // Surrender the rest of our thread's time slice and a little more
               ::Sleep( 250 );
            }

            WFCTRACEVAL( TEXT( "Hung up, it took this number of tries: " ), number_of_tries );

            m_ConnectionHandle = NULL;
         }
      }
      else
      {
         HRASCONN temp_handle = GetConnection( name_of_connection );

         connection_name = name_of_connection;

         m_ErrorCode = m_Thunk_p->RasHangUp( temp_handle );

         if ( m_ErrorCode == 0 )
         {
            WFCTRACEVAL( TEXT( "Waiting until ras really hangs up on " ), CString( name_of_connection ) );

            // Code around he NT bug

            while( m_Thunk_p->RasGetConnectStatus( temp_handle, &m_ConnectionStatus ) != ERROR_INVALID_HANDLE )
            {
#if defined( _DEBUG )
               number_of_tries++;
#endif
               // Surrender the rest of our thread's time slice
               ::Sleep( 250 );
            }

            WFCTRACEVAL( TEXT( "Hung up, it took this number of tries: " ), number_of_tries );
         }
      }

      // By now you're wondering, "Why the heck is he closing the connection again?"
      // Because I have an application that *STILL* doesn't hangup! Gawl dang children...

      HRASCONN temp_handle = NULL;

      do
      {
         temp_handle = GetConnection( connection_name );

         if ( temp_handle != NULL )
         {
            WFCTRACE( TEXT( "Well whaddya know, the connection is still there..." ) );
            m_Thunk_p->RasHangUp( temp_handle );
            ::Sleep( 1000 );
         }
      }
      while( temp_handle != NULL );

      if ( m_ErrorCode == 0 )
      {
         return( TRUE );
      }
      else
      {
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessService::Dial( LPCTSTR who_to_dial )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::Dial()" ) );
   //ASSERT_VALID( this );
   ASSERT( who_to_dial != NULL );

   if ( who_to_dial == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // Disconnect the current connection asynchronously, we don't care when
   // it gets done.

   HangUp();

#if ( WINVER >= 0x401 )

   // Thanks go to Richard Wirth (r.wirth@wirthware.da-net.de) for
   // finding and fixing an endless loop bug here.

   RASCREDENTIALS credentials;

   ::ZeroMemory( &credentials, sizeof( credentials ) );
   credentials.dwSize = sizeof( credentials );
   credentials.dwMask = RASCM_UserName | RASCM_Password | RASCM_Domain;

   // get the default credentials
   m_Thunk_p->RasGetCredentials( NULL, (TCHAR *) who_to_dial, &credentials );

#endif // WINVER >= 0x401

   RASDIALPARAMS dialing_parameters;

   ::ZeroMemory( &dialing_parameters, sizeof( dialing_parameters ) );

   dialing_parameters.dwSize = sizeof( dialing_parameters );

   // We were passed a pointer, don't trust it

   try
   {
      _tcscpy( dialing_parameters.szEntryName, who_to_dial );
#if ( WINVER >= 0x401 )
      // These are thanks to Richard Wirth...
      _tcscpy( dialing_parameters.szUserName, credentials.szUserName );
      _tcscpy( dialing_parameters.szPassword, credentials.szPassword );
      _tcscpy( dialing_parameters.szDomain,   credentials.szDomain   );
#endif // WINVER >= 0x401

      m_ConnectionHandle = NULL;

      m_ErrorCode = m_Thunk_p->RasDial( &m_DialExtensions,
                                NULL,
                               &dialing_parameters,
                                m_NotifierType,
                                m_ConnectionCallbackFunctionPointer,
                               &m_ConnectionHandle );

      if ( m_ErrorCode == 0 )
      {
         m_Name = who_to_dial;
         return( TRUE );
      }
      else
      {
         m_Name.Empty();
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessService::EnableLogging( BOOL enable_logging, LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::EnableLogging()" ) );

   CRegistry registry;

   if ( registry.Connect( HKEY_LOCAL_MACHINE, machine_name ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to HKEY_LOCAL_MACHINE" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Services\\RasMan\\Parameters" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open \"SYSTEM\\CurrentControlSet\\Services\\RasMan\\Parameters\"" ) );
      return( FALSE );
   }

   DWORD value_to_set = 0;

   if ( enable_logging == FALSE )
   {
      value_to_set = 0;
   }
   else
   {
      value_to_set = 1;
   }

   if ( registry.SetValue( TEXT( "Logging" ), value_to_set ) == FALSE )
   {
      WFCTRACE( TEXT( "Logging not set" ) );
      return( FALSE );
   }

   WFCTRACE( TEXT( "Logging was set" ) );

   return( TRUE );
}

HRASCONN CRemoteAccessService::GetConnection( LPCTSTR name_of_connection )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetConnection()" ) );
   //ASSERT_VALID( this );

   if ( name_of_connection == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      LPRASCONN connections       = NULL;
      DWORD     number_of_entries = 0;

      m_GetConnectionsIntoMemory( connections, number_of_entries );

      HRASCONN return_value = NULL;

      if ( m_ErrorCode == 0 )
      {
         DWORD index = 0;

         while( index < number_of_entries )
         {
            if ( _tcsicmp( name_of_connection, connections[ index ].szEntryName ) == 0 )
            {
               return_value = connections[ index ].hrasconn;
               index = number_of_entries;
            }

            index++;
         }
      }

      delete [] connections;

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessService::GetConnections( CStringArray& connection_names )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetConnections()" ) );
   //ASSERT_VALID( this );

   connection_names.RemoveAll();

   LPRASCONN connections       = NULL;
   DWORD     number_of_entries = 0;

   m_GetConnectionsIntoMemory( connections, number_of_entries );

   BOOL return_value = FALSE;

   if ( m_ErrorCode == 0 )
   {
      return_value = TRUE;

      DWORD index = 0;

      while( index < number_of_entries )
      {
         connection_names.Add( connections[ index ].szEntryName );
         index++;
      }
   }

   delete [] connections;

   return( return_value );
}

BOOL CRemoteAccessService::GetConnectionStatus( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetConnectionStatus()" ) );
   //ASSERT_VALID( this );

   m_ErrorCode = m_Thunk_p->RasGetConnectStatus( m_ConnectionHandle, &m_ConnectionStatus );

   if ( m_ErrorCode == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

LONG CRemoteAccessService::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetErrorCode()" ) );
   //ASSERT_VALID( this );

   return( m_ErrorCode );
}

BOOL CRemoteAccessService::GetErrorString( CString& return_string )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetErrorString()" ) );
   //ASSERT_VALID( this );

   TCHAR string[ 4096 ];

   ::ZeroMemory( string, sizeof( string ) );

   if ( m_Thunk_p->RasGetErrorString( m_ErrorCode, string, DIMENSION_OF( string ) ) == 0 )
   {
      return_string = string;
      return( TRUE );
   }
   else
   {
      return_string.Empty();
      return( FALSE );
   }
}

BOOL CRemoteAccessService::GetKeepConnectionsAfterLogoff( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetKeepConnectionsAfterLogoff()" ) );

   // Thanks to Erik Strom (estrom@rcich.com) for getting
   // the information out of Microsoft

   CRegistry registry;

   if ( registry.Connect( HKEY_LOCAL_MACHINE, machine_name ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to HKEY_LOCAL_MACHINE" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open \"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\"" ) );
      return( FALSE );
   }

   CString keep_connections( TEXT( "" ) );

   if ( registry.GetValue( TEXT( "KeepRasConnections" ), keep_connections ) == FALSE )
   {
      // The value doesn't exist, this means the RAS connections will be dropped at logoff
      return( FALSE );
   }

   int keep_connections_value = 0;

   keep_connections_value = _ttoi( keep_connections );

   if ( keep_connections_value == 0 )
   {
      return( FALSE );
   }

   return( TRUE );
}

void CRemoteAccessService::GetName( CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetName()" ) );
   name = m_Name;
}

BOOL CRemoteAccessService::GetPhoneBookEntries( CStringArray& phone_book_entries )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetPhoneBookEntries()" ) );
   //ASSERT_VALID( this );

   phone_book_entries.RemoveAll();

   DWORD size_of_buffer         = 64 * sizeof( RASENTRYNAME );
   DWORD number_of_bytes_needed = size_of_buffer;
   DWORD number_of_entries      = 0;

   LPRASENTRYNAME memory_buffer = (LPRASENTRYNAME) new BYTE[ size_of_buffer ]; // Get room for 64 entries (to begin with)

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
      return( FALSE );
   }

   ::ZeroMemory( memory_buffer, size_of_buffer );

   memory_buffer->dwSize = sizeof( RASENTRYNAME );

   m_ErrorCode = m_Thunk_p->RasEnumEntries( NULL, NULL, memory_buffer, &number_of_bytes_needed, &number_of_entries );

   if ( m_ErrorCode != 0 )
   {
      if ( m_ErrorCode == ERROR_BUFFER_TOO_SMALL || m_ErrorCode == ERROR_NOT_ENOUGH_MEMORY )
      {
         delete [] memory_buffer;

         memory_buffer = (LPRASENTRYNAME) new BYTE[ number_of_bytes_needed ];

         if ( memory_buffer == NULL )
         {
            m_ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            return( FALSE );
         }

         ::ZeroMemory( memory_buffer, number_of_bytes_needed );

         memory_buffer->dwSize = sizeof( RASENTRYNAME );
         m_ErrorCode = m_Thunk_p->RasEnumEntries( NULL, NULL, memory_buffer, &number_of_bytes_needed, &number_of_entries );
      }
   }

   BOOL return_value = FALSE;

   if ( m_ErrorCode == 0 )
   {
      return_value = TRUE;

      DWORD index = 0;

      while( index < number_of_entries )
      {
         phone_book_entries.Add( memory_buffer[ index ].szEntryName );
         index++;
      }
   }

   delete [] memory_buffer;

   return( return_value );
}

BOOL CRemoteAccessService::GetProtocolInformation( CRemoteAccessServiceAuthenticationMessageBlock& data_to_get )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetProtocolInformation()" ) );
   //ASSERT_VALID( this );

   CRemoteAccessServiceAuthenticationMessageBlock return_data;

   // Thanks to Chad Stevens (c-stephens1@ti.com) for finding a Symantec 7.5 casting problem here

   if ( m_Thunk_p->RasGetProjectionInfo( m_ConnectionHandle, static_cast< enum tagRASPROJECTION >( RASP_Amb ), (LPVOID) (RASAMB *) &return_data, &return_data.dwSize ) == 0 )
   {
      data_to_get.Copy( return_data );

      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CRemoteAccessService::GetProtocolInformation( CRemoteAccessServiceNetBEUIFramer& data_to_get )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetProtocolInformation()" ) );
   //ASSERT_VALID( this );

   CRemoteAccessServiceNetBEUIFramer return_data;

   // Thanks to Chad Stevens (c-stephens1@ti.com) for finding a Symantec 7.5 casting problem here

   if ( m_Thunk_p->RasGetProjectionInfo( m_ConnectionHandle, static_cast< enum tagRASPROJECTION >( RASP_PppNbf ), (LPVOID) (RASPPPNBF *) &return_data, &return_data.dwSize ) == 0 )
   {
      data_to_get.Copy( return_data );

      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CRemoteAccessService::GetProtocolInformation( CRemoteAccessServiceInternetworkPacketExchange& data_to_get )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetProtocolInformation()" ) );
   //ASSERT_VALID( this );

   CRemoteAccessServiceInternetworkPacketExchange return_data;

   // Thanks to Chad Stevens (c-stephens1@ti.com) for finding a Symantec 7.5 casting problem here

   if ( m_Thunk_p->RasGetProjectionInfo( m_ConnectionHandle, static_cast< enum tagRASPROJECTION >( RASP_PppIpx ), (LPVOID) (RASPPPIPX *) &return_data, &return_data.dwSize ) == 0 )
   {
      data_to_get.Copy( return_data );

      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CRemoteAccessService::GetProtocolInformation( CRemoteAccessServiceInternetProtocol& data_to_get )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::GetProtocolInformation()" ) );
   //ASSERT_VALID( this );

   CRemoteAccessServiceInternetProtocol return_data;

   // Thanks to Chad Stevens (c-stephens1@ti.com) for finding a Symantec 7.5 casting problem here

   if ( m_Thunk_p->RasGetProjectionInfo( m_ConnectionHandle, static_cast< enum tagRASPROJECTION >( RASP_PppIp ), (LPVOID) (RASPPPIP *) &return_data, &return_data.dwSize ) == 0 )
   {
      data_to_get.Copy( return_data );

      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CRemoteAccessService::HangUp( LPCTSTR name_of_connection )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::HangUp()" ) );
   //ASSERT_VALID( this );

   /*
   ** RasHangUp is mis-documented. It is an asynchronous call (although they don't bother
   ** to tell you that). Don't assume that when RasHangUp returns, the connection is
   ** terminates. THAT AIN'T THE CASE!
   **
   ** RasHangUp should be documented as follows:
   **
   ** DWORD RasPostHangUpRequest( HRASCONN ras_connection_handle );
   **
   ** Return Values
   ** If the function succeeds, zero if a hangup message was put in the RAS command queue, 
   ** If the function fails, the return value is a nonzero error value listed in the RAS header file, or ERROR_INVALID_HANDLE.
   **
   ** Remarks
   ** RasPostHangUpRequest (formerly named RasHangUp) issues a request to RAS to terminate
   ** the session. If you exit your process or thread before the request is processed, the
   ** RAS port will remain open. You must put code in your application to work around
   ** this little gem.
   */

   // We were passed a pointer, don't trust it

   try
   {
      if ( name_of_connection == NULL )
      {
         m_ErrorCode = m_Thunk_p->RasHangUp( m_ConnectionHandle );

         // m_ConnectionHandle is left intact because RAS doesn't really hangup.
      }
      else
      {
         HRASCONN temp_handle = GetConnection( name_of_connection );

         m_ErrorCode = m_Thunk_p->RasHangUp( temp_handle );
      }

      if ( m_ErrorCode == 0 )
      {
         return( TRUE );
      }
      else
      {
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessService::IsConnected( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::IsConnected()" ) );
   //ASSERT_VALID( this );

   GetConnectionStatus();

   if ( m_ConnectionStatus.rasconnstate == RASCS_Connected )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACEVAL( TEXT( "state is " ), CString( __convert_RASCONNSTATE_to_string( m_ConnectionStatus.rasconnstate ) ) );
      return( FALSE );
   }
}
                                                              
void CRemoteAccessService::m_GetConnectionsIntoMemory( LPRASCONN& connections, DWORD& number_of_connections )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::m_GetConnectionsIntoMemory()" ) );
   //ASSERT_VALID( this );

   DWORD size_of_buffer         = 64 * sizeof( RASCONN );
   DWORD number_of_bytes_needed = size_of_buffer;
   DWORD number_of_entries      = 0;

   LPRASCONN memory_buffer = (LPRASCONN) new BYTE[ size_of_buffer ]; // Get room for 64 entries (to begin with)

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
      return;
   }

   ::ZeroMemory( memory_buffer, size_of_buffer );

   memory_buffer->dwSize = sizeof( RASCONN );

   m_ErrorCode = m_Thunk_p->RasEnumConnections( memory_buffer, &number_of_bytes_needed, &number_of_entries );

   if ( m_ErrorCode != 0 )
   {
      if ( m_ErrorCode == ERROR_BUFFER_TOO_SMALL || m_ErrorCode == ERROR_NOT_ENOUGH_MEMORY )
      {
         delete [] memory_buffer;

         memory_buffer = (LPRASCONN) new BYTE[ number_of_bytes_needed ];

         if ( memory_buffer == NULL )
         {
            m_ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            return;
         }

         ::ZeroMemory( memory_buffer, number_of_bytes_needed );

         memory_buffer->dwSize = sizeof( RASCONN );
         m_ErrorCode = m_Thunk_p->RasEnumConnections( memory_buffer, &number_of_bytes_needed, &number_of_entries );
      }
   }

   connections           = memory_buffer;
   number_of_connections = number_of_entries;
}

void CRemoteAccessService::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::m_Initialize()" ) );
   //ASSERT_VALID( this );

   m_ErrorCode                         = 0;
   m_ConnectionHandle                  = NULL;
   m_ConnectionCallbackFunctionPointer = NULL;
   m_NotifierType                      = 0;
   m_Name.Empty();

   // Always play with member structures last, Microsoft likes to 
   // change the size of them so when you ZeroMemory() them, things
   // break.

   // Here's a stack corruptor if WINVER is less than 0x401
   ::ZeroMemory( &m_ConnectionStatus, sizeof( m_ConnectionStatus ) );
   m_ConnectionStatus.dwSize = sizeof( m_ConnectionStatus );

   ::ZeroMemory( &m_DialExtensions, sizeof( m_DialExtensions ) );
   m_DialExtensions.dwSize = sizeof( m_DialExtensions );
}

static DWORD APIENTRY _wfc_ras_thunk_not_implemented( void )
{
   return( ERROR_CALL_NOT_IMPLEMENTED );
}

#define WFC_LOAD_RAS_THUNK( dll_instance_handle, structure_pointer, function_name ) \
{\
   *( (FARPROC *) &structure_pointer->function_name ) = GetProcAddress( dll_instance_handle, #function_name );\
   if ( structure_pointer->function_name == NULL ) \
{\
   WFCTRACEVAL( TEXT( "Loading not-implemented thunk for " ), CString( #function_name ) ); \
   *( (FARPROC *) &structure_pointer->function_name ) = (FARPROC) _wfc_ras_thunk_not_implemented;\
}\
}

void CRemoteAccessService::m_InitializeThunk( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::m_InitializeThunk()" ) );

   if ( m_Thunk_p != NULL )
   {
      WFCTRACE( TEXT( "Thunk already in place" ) );
      return;
   }

   try
   {
      m_Thunk_p = new WFC_RAS_THUNK;
   }
   catch( ... )
   {
      m_Thunk_p = NULL;
   }

   if ( m_Thunk_p == NULL )
   {
      WFCTRACE( TEXT( "Out of memory" ) );
      return;
   }

   ZeroMemory( m_Thunk_p, sizeof( WFC_RAS_THUNK ) );

   // Now is the time for all good programmers to detect the operating system

   _tcsncpy( m_Thunk_p->dll_name, TEXT( "RASAPI32.DLL" ), DIMENSION_OF( m_Thunk_p->dll_name ) );

   m_Thunk_p->dll_instance_handle = ::LoadLibrary( m_Thunk_p->dll_name );

   if ( m_Thunk_p->dll_instance_handle == NULL )
   {
      WFCTRACEVAL( TEXT( "Can't load " ), CString( m_Thunk_p->dll_name ) );
   }

   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasDialA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasDialW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumConnectionsA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumConnectionsW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumEntriesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumEntriesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetConnectStatusA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetConnectStatusW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetErrorStringA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetErrorStringW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasHangUpA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasHangUpW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetProjectionInfoA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetProjectionInfoW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasCreatePhonebookEntryA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasCreatePhonebookEntryW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEditPhonebookEntryA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEditPhonebookEntryW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetEntryDialParamsA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetEntryDialParamsW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetEntryDialParamsA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetEntryDialParamsW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumDevicesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumDevicesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetCountryInfoA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetCountryInfoW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetEntryPropertiesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetEntryPropertiesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetEntryPropertiesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetEntryPropertiesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasRenameEntryA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasRenameEntryW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasDeleteEntryA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasDeleteEntryW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasValidateEntryNameA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasValidateEntryNameW );

#if ( WINVER >= 0x401 )

   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetSubEntryHandleA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetSubEntryHandleW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetCredentialsA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetCredentialsW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetCredentialsA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetCredentialsW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasConnectionNotificationA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasConnectionNotificationW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetSubEntryPropertiesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetSubEntryPropertiesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetSubEntryPropertiesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetSubEntryPropertiesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialAddressA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialAddressW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialAddressA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialAddressW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumAutodialAddressesA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasEnumAutodialAddressesW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialEnableA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialEnableW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialEnableA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialEnableW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialParamA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasGetAutodialParamW );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialParamA );
   WFC_LOAD_RAS_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, RasSetAutodialParamW );

#endif
}

BOOL CRemoteAccessService::Open( LPCTSTR who_to_dial )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::Open()" ) );
   //ASSERT_VALID( this );
   ASSERT( who_to_dial != NULL );

   if ( who_to_dial == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // Sometimes Open() would go into an endless loop.
      // Luckily, Richard Wirth (r.wirth@wirthware.da-net.de)
      // was smart enough to catch it.

#if ( WINVER >= 0x401 )
      RASCREDENTIALS credentials;

      ::ZeroMemory( &credentials, sizeof( credentials ) );
      credentials.dwSize = sizeof( credentials );
      credentials.dwMask = RASCM_UserName | RASCM_Password | RASCM_Domain;

      // get the default credentials
      m_Thunk_p->RasGetCredentials( NULL, (TCHAR *) who_to_dial, &credentials );

#endif // WINVER >= 0x401

      RASDIALPARAMS dialing_parameters;

      ::ZeroMemory( &dialing_parameters, sizeof( dialing_parameters ) );

      dialing_parameters.dwSize = sizeof( dialing_parameters );
      _tcscpy( dialing_parameters.szEntryName, who_to_dial );

#if ( WINVER >= 0x401 )
      // These are thanks to Richard Wirth...
      _tcscpy( dialing_parameters.szUserName, credentials.szUserName );
      _tcscpy( dialing_parameters.szPassword, credentials.szPassword );
      _tcscpy( dialing_parameters.szDomain,   credentials.szDomain   );
#endif // WINVER >= 0x401

      m_ConnectionHandle = NULL;
      m_Name.Empty();

      m_ErrorCode = m_Thunk_p->RasDial( &m_DialExtensions,
                                NULL,
                               &dialing_parameters,
                                m_NotifierType,
                                m_ConnectionCallbackFunctionPointer,
                               &m_ConnectionHandle );

      if ( m_ErrorCode == 0 )
      {
         m_Name = who_to_dial;

         // Now we've got a connection handle, with it, we can wait until we're connected

         // First, let's sleep for a while. This let's RAS dial the phone instead of
         // respond to all of our GetConnectionStatus() calls. We are hammering RAS
         // when we call that function.

         ::Sleep( 6000 ); // six seconds

         // Now start hammering RAS for the status

         while( 1 )
         {
            if ( GetConnectionStatus() != FALSE )
            {
               if ( m_ConnectionStatus.rasconnstate == RASCS_Connected )
               {
                  WFCTRACE( TEXT( "Connected!" ) );
                  return( TRUE );
               }

               if ( m_ConnectionStatus.rasconnstate == RASCS_Disconnected )
               {
                  WFCTRACE( TEXT( "Disconnected" ) );
                  return( FALSE );
               }

               // only ask RAS about 4 times per second... (i.e. be nice)

               ::Sleep( 250 );
            }
            else
            {
               WFCTRACEVAL( TEXT( "Not Connected Error: " ), m_ErrorCode );
               WFCTRACEERROR( m_ErrorCode );

               WFCTRACEVAL( TEXT( "Connection Status Error: " ), m_ConnectionStatus.dwError );
               WFCTRACEERROR( m_ConnectionStatus.dwError );

               WFCTRACEVAL( TEXT( "rasconnstate " ), CString( __convert_RASCONNSTATE_to_string( m_ConnectionStatus.rasconnstate ) ) );

               return( FALSE );
            }
         }
      }
      else
      {
        return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRemoteAccessService::SetAutomaticallyClose( BOOL auto_close )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::SetAutomaticallyClose()" ) );
   BOOL return_value = m_AutomaticallyClose;

   m_AutomaticallyClose = auto_close;

   return( return_value );
}

LPVOID CRemoteAccessService::SetConnectionCallback( LPVOID function_pointer )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::SetConnectionCallback()" ) );

   LPVOID return_value = NULL;

   if ( m_NotifierType == 1 )
   {
      WFCTRACE( TEXT( "Returning old function pointer" ) );
      return_value = m_ConnectionCallbackFunctionPointer;
   }

   m_ConnectionCallbackFunctionPointer = function_pointer;
   m_NotifierType                      = 1;

   return( return_value );
}

HWND CRemoteAccessService::SetConnectionCallbackWindow( HWND window_handle )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::SetConnectionCallbackWindow()" ) );

   HWND return_value = NULL;

   if ( m_NotifierType == 0xFFFFFFFF )
   {
      WFCTRACE( TEXT( "Returning old window handle" ) );
      return_value = (HWND) m_ConnectionCallbackFunctionPointer;
   }

   m_ConnectionCallbackFunctionPointer = (LPVOID) window_handle;
   m_NotifierType = 0xFFFFFFFF;

   return( return_value );
}

DWORD CRemoteAccessService::SetDialOptions( DWORD dial_options )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::SetDialOptions()" ) );

   DWORD return_value = m_DialExtensions.dwfOptions;

   m_DialExtensions.dwfOptions = dial_options;

   return( return_value );
}

BOOL CRemoteAccessService::SetKeepConnectionsAfterLogoff( BOOL keep_connections, LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessService::SetKeepConnectionsAfterLogoff()" ) );

   // Thanks to Erik Strom (estrom@rcich.com) for getting
   // the information out of Microsoft

   CRegistry registry;

   if ( registry.Connect( HKEY_LOCAL_MACHINE, machine_name ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to HKEY_LOCAL_MACHINE" ) );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open \"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\"" ) );
      return( FALSE );
   }

   CString keep_connections_string( TEXT( "" ) );

   if ( keep_connections == FALSE )
   {
      keep_connections_string = TEXT( "0" );
   }
   else
   {
      keep_connections_string = TEXT( "1" );
   }

   if ( registry.SetValue( TEXT( "KeepRasConnections" ), keep_connections_string ) == FALSE )
   {
      // The value doesn't exist, this means the RAS connections will be dropped at logoff
      return( FALSE );
   }

   return( TRUE );
}

/*
** How to get rid of the "Done" button on the terminal screen
**
** 1. Get your macro in SWITCH.INF working so the only thing left to do
**    is click on the Done button in the terminal window
**
** 2. Set "Authenticate using current username and password" ON.
**
** 3. Choose "Authenticate using any method including clear text" under
**    the "Security" button.
**
** 4. ENJOY!
*/

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessService</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking, source code">
<META name="description" content="The C++ class that encapsulates Remote Access Service (Dialup networking).">
</HEAD>

<BODY>

<H1>CRemoteAccessService : CObject</H1>
$Revision: 37 $
<HR>

<H2>Description</H2>

This class makes RAS a little easier. From a programming perspective, RAS is like most Microsoft API's: almost useful.
What's lacking from RAS is the ability to play with ports. I had to write software for a fault-tolerant mail postoffice
and wrote a little program to page a system administrator when something went wrong. I had to dedicate one modem to
this task because there's no way to tell RAS to release a port for other use. There's a RasPortxxx API that is not
exposed so we lowly developer's can't use it. In short, it is impossible to write the RASPHONE application using
the documented RAS API.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CRemoteAccessService</B>()
<B>CRemoteAccessService</B>( DWORD input_buffer_size )
<B>CRemoteAccessService</B>( DWORD input_buffer_size, output_buffer_size )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="Close">Close</A></B>( LPCTSTR name_of_connection = NULL )</PRE><DD>
Same as <B><A HREF="#HangUp">HangUp()</A></B>
except it will not return until RAS really hangs up.

<DT><PRE>BOOL <B><A NAME="Dial">Dial</A></B>( LPCTSTR who_to_call )</PRE><DD>
Dials a phone book entry. Makes a connection.

<DT><PRE>static BOOL <B><A NAME="EnableLogging">EnableLogging</A></B>( BOOL enable_logging, LPCTSTR machine_name = NULL )</PRE><DD>
This method allows you to enable logging of the connection. If set to
TRUE, it will create a DEVICE.LOG file that holds the commands and
responses during a RAS connection (when you dial).

<DT><PRE>HRASCONN <B><A NAME="GetConnection">GetConnection</A></B>( LPCTSTR name_of_connection )</PRE><DD>
Gives you the HRASONN for the named connection.

<DT><PRE>BOOL <B><A NAME="GetConnections">GetConnections</A></B>( CStringArray&amp; connection_names )</PRE><DD>
Gives you a list of connection names. These are the names of the
phone book entries that are currently connected. It is a list
of the active RAS connections.

<DT><PRE>BOOL <B><A NAME="GetConnectionStatus">GetConnectionStatus</A></B>( void )</PRE><DD>
Returns TRUE is you're connected.

<DT><PRE>LONG <B><A NAME="GetErrorCode">GetErrorCode</A></B>( void ) const</PRE><DD>
Returns the error code should any function return FALSE.

<DT><PRE>BOOL <B><A NAME="GetErrorString">GetErrorString</A></B>( CString&amp; error_string )</PRE><DD>
Same as <B>GetErrorCode</B>() but it gives you a human
readable string instead of a number.

<DT><PRE>BOOL <B><A NAME="GetKeepConnectionsAfterLogoff">GetKeepConnectionsAfterLogoff</A></B>( LPCTSTR machine_name = NULL )</PRE><DD>
Tells you if your RAS connections
will be dropped (disconnected) when the user logs off.
If <CODE></CODE> is not NULL,

<DT><PRE>void <B><A NAME="GetName">GetName</A></B>( CString&amp; name )</PRE><DD>
Gives you the name of the connection that was successfully
<B><A HREF="#Open">Open()</A></B>'d or
<B><A HREF="#Dial">Dial()</A></B>'d.

<DT><PRE>BOOL <B><A NAME="GetPhoneBookEntries">GetPhoneBookEntries</A></B>( CStringArray&amp; phone_book_entries )</PRE><DD>
Gives you back a list of phone book entry
names. You can use these names to pass to <B><A HREF="#Dial">Dial()</A></B>.

<DT><PRE>BOOL <B><A NAME="GetProtocolInformation">GetProtocolInformation</A></B>( CRemoteAccessServiceAuthenticationMessageBlock&amp; data_to_get )
BOOL <B>GetProtocolInformation</B>( CRemoteAccessServiceNetBEUIFramer&amp; data_to_get )
BOOL <B>GetProtocolInformation</B>( CRemoteAccessServiceInternetworkPacketExchange&amp; data_to_get )
BOOL <B>GetProtocolInformation</B>( CRemoteAccessServiceInternetProtocol&amp; data_to_get )</PRE><DD>
Gives you back information about the networking protocol used on the active connection.

<DT><PRE>BOOL <B><A NAME="HangUp">HangUp</A></B>( LPCTSTR name_of_connection = NULL )</PRE><DD>
Tells RAS to terminate the connection. <B>NOTE!</B>
When this function returns, <B><I>THE CONNECTION HAS NOT BEEN TERMINATED!!</I></B>
If you immediately exit from your thread/process after calling <B>HangUp()</B>, the connection
will be left in a random state. It is much safer to use
<B><A HREF="#Close">Close()</A></B> instead.

<DT><PRE>BOOL <B><A NAME="IsConnected">IsConnected</A></B>( void )</PRE><DD>
Returns TRUE if you're connected.

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( LPCTSTR who_to_call )</PRE><DD>
Same as Dial but lets you treat RAS like most other object in WFC.

<DT><PRE>BOOL <B><A NAME="SetAutomaticallyClose">SetAutomaticallyClose</A></B>( BOOL automatically_close )</PRE><DD>
When this property is TRUE, the destructor will terminate the connection if there is one. 

<DT><PRE>LPVOID <B><A NAME="SetConnectionCallback">SetConnectionCallback</A></B>( LPVOID RasDialFunc1_function_pointer )</PRE><DD>
Lets you pass a pointer to a function so you can monitor the progress of RAS.

<DT><PRE>HWND <B><A NAME="SetConnectionCallbackWindow">SetConnectionCallbackWindow</A></B>( HWND window_handle )</PRE><DD>
Lets you pass a window handle that will
receive <CODE>WM_RASDIALEVENT</CODE> messages so you can monitor the progress of RAS.

<DT><PRE>DWORD <B><A NAME="SetDialOptions">SetDialOptions</A></B>( DWORD dial_options )</PRE><DD>
Let's you set the dialing options.

<DT><PRE>BOOL <B><A NAME="SetKeepConnectionsAfterLogoff">SetKeepConnectionsAfterLogoff</A></B>( BOOL keep_connections = TRUE, LPCTSTR machine_name )</PRE><DD>
Lets you tell NT whether or not it
should drop all RAS connections when the current user logs off.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CRAS( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CRAS()&quot; ) );

   <B>CRemoteAccessService</B> ras;

   CStringArray strings;

   ras.<A HREF="#SetDialOptions">SetDialOptions</A>( CRemoteAccessService::dialAcceptPausedStates );

   if ( ras.<A HREF="#GetPhoneBookEntries">GetPhoneBookEntries</A>( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;Phone Book Entries:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   strings.RemoveAll();

   if ( ras.<A HREF="#GetConnections">GetConnections</A>( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;\nCurrent Connections:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   if ( ras.<A HREF="#Open">Open</A>( TEXT( &quot;EROLS&quot; ) ) == FALSE )
   {
      CString error_string;
      ras.<A HREF="#GetErrorString">GetErrorString</A>( error_string );
      TRACE1( TEXT( &quot;Ras Open failed with \&quot;%s\&quot;!\n&quot; ), (LPCTSTR) error_string );
   }
   else
   {
      TRACE( TEXT( &quot;RAS Open!\n&quot; ) );
   }

   strings.RemoveAll();

   if ( ras.<A HREF="#GetConnections">GetConnections</A>( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;\nCurrent Connections:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   if ( ras.<A HREF="#HangUp">HangUp</A>( TEXT( &quot;EROLS&quot; ) ) != FALSE )
   {
      TRACE( TEXT( &quot;Hangup OK\n&quot; ) );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>RasDial
<LI>RasEnumConnections
<LI>RasEnumEntries
<LI>RasGetConnectStatus
<LI>RasGetErrorString
<LI>RasGetProjectionInfo
<LI>RasHangUp
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cras.cpp $<BR>
$Modtime: 1/17/00 9:12a $
</BODY>

</HTML>
#endif
