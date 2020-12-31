#include "test.h"
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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: TCRAS.CPP $
** $Revision: 4 $
** $Modtime: 2/01/00 8:08p $
*/

VOID PASCAL dial_monitor( HRASCONN     connection_handle, 
                          UINT         message, 
                          RASCONNSTATE connection_state,
                          DWORD        error_code,
                          DWORD        extended_error_code )
{
   switch( connection_state )
   {
      case RASCS_OpenPort:

         OutputDebugString( TEXT( "RASCS_OpenPort : The communication port is about to be opened.\n" ) );
         break;

      case RASCS_PortOpened:

         OutputDebugString( TEXT( "RASCS_PortOpened : The communication port has been opened successfully.\n" ) );
         break;

      case RASCS_ConnectDevice:

         OutputDebugString( TEXT( "RASCS_ConnectDevice : A device is about to be connected. RasGetConnectStatus can be called to determine the name and type of the device being connected.\n" ) );
         break;

      case RASCS_DeviceConnected:

         OutputDebugString( TEXT( "RASCS_DeviceConnected : A device has connected successfully. RasGetConnectStatus can be called to determine the name and type of the device being connected.\n" ) );
         break;

      case RASCS_AllDevicesConnected:

         OutputDebugString( TEXT( "RASCS_AllDevicesConnected : All devices in the device chain have successfully connected. At this point, the physical link is established.\n" ) );
         break;

      case RASCS_Authenticate:

         OutputDebugString( TEXT( "RASCS_Authenticate : 	The authentication process is starting. Remote access does not allow the remote client to generate any traffic on the LAN until authentication has been successfully completed. \n" ) );
         break;

      case RASCS_AuthNotify:

         OutputDebugString( TEXT( "RASCS_AuthNotify : An authentication event has occurred. If dwError is zero, this event will be immediately followed by one of the more specific authentication states following. If dwError is nonzero, authentication has failed, and the error value indicates why.\n" ) );
         break;

      case RASCS_AuthRetry:

         OutputDebugString( TEXT( "RASCS_AuthRetry : The client has requested another validation attempt with a new username/password/domain. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_AuthCallback:

         OutputDebugString( TEXT( "RASCS_AuthCallback : The remote access server has requested a callback number. This occurs only if the user has \"Set By Caller\" callback privilege on the server.\n" ) );
         break;

      case RASCS_AuthChangePassword:

         OutputDebugString( TEXT( "RASCS_AuthChangePassword : The client has requested to change the password on the account. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_AuthProject:

         OutputDebugString( TEXT( "RASCS_AuthProject : The projection phase is starting.\n" ) );
         break;

      case RASCS_AuthLinkSpeed:

         OutputDebugString( TEXT( "RASCS_AuthLinkSpeed : The link-speed calculation phase is starting.\n" ) );
         break;

      case RASCS_AuthAck:

         OutputDebugString( TEXT( "RASCS_AuthAck : An authentication request is being acknowledged.\n" ) );
         break;

      case RASCS_ReAuthenticate:

         OutputDebugString( TEXT( "RASCS_ReAuthenticate : Reauthentication (after callback) is starting.\n" ) );
         break;

      case RASCS_Authenticated:

         OutputDebugString( TEXT( "RASCS_Authenticated : The client has successfully completed authentication.\n" ) );
         break;

      case RASCS_PrepareForCallback:

         OutputDebugString( TEXT( "RASCS_PrepareForCallback : The line is about to disconnect in preparation for callback.\n" ) );
         break;

      case RASCS_WaitForModemReset:

         OutputDebugString( TEXT( "RASCS_WaitForModemReset : The client is delaying in order to give the modem time to reset itself in preparation for callback.\n" ) );
         break;

      case RASCS_WaitForCallback:

         OutputDebugString( TEXT( "RASCS_WaitForCallback : The client is waiting for an incoming call from the remote access server.\n" ) );
         break;

      case RASCS_Projected:

         OutputDebugString( TEXT( "RASCS_Projected : This state occurs after the RASCS_AuthProject state. It indicates that projection result information is available. You can access the projection result information by calling RasGetProjectionInfo.\n" ) );
         break;

#if (WINVER >= 0x400)

      case RASCS_StartAuthentication:    // Windows 95 only 

         OutputDebugString( TEXT( "RASCS_StartAuthentication : Windows 95 only: Indicates that user authentication is being initiated or retried.\n" ) );
         break;

      case RASCS_CallbackComplete:       // Windows 95 only 

         OutputDebugString( TEXT( "RASCS_CallbackComplete : Windows 95 only: Indicates that the client has been called back and is about to resume authentication.\n" ) );
         break;

      case RASCS_LogonNetwork:           // Windows 95 only 

         OutputDebugString( TEXT( "RASCS_LogonNetwork : Windows 95 only: Indicates that the client is logging on to the network.\n" ) );
         break;

#endif 
 
      case RASCS_Interactive:

         OutputDebugString( TEXT( "RASCS_Interactive : This state corresponds to the terminal state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_RetryAuthentication:

         OutputDebugString( TEXT( "RASCS_RetryAuthentication : This state corresponds to the retry authentication state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_CallbackSetByCaller:

         OutputDebugString( TEXT( "RASCS_CallbackSetByCaller : This state corresponds to the Callback state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_PasswordExpired:

         OutputDebugString( TEXT( "RASCS_PasswordExpired : This state corresponds to the change password state supported by RASPHONE.EXE. This state does not occur in Windows NT version 3.1.\n" ) );
         break;

      case RASCS_Connected:

         OutputDebugString( TEXT( "RASCS_Connected : Successful connection.\n" ) );
         break;

      case RASCS_Disconnected:

         OutputDebugString( TEXT( "RASCS_Disconnected : Disconnection or failed connection.\n" ) );
         break;

      default:

         if ( connection_state != 0 )
         {
            TCHAR debug_string[ 99 ];

            _stprintf( debug_string, (LPCTSTR) TEXT( "Unknown connection state %d\n" ), connection_state );
            OutputDebugString( debug_string );
         }

         break;
   }

   switch( extended_error_code )
   {
      case ERROR_SERVER_NOT_RESPONDING:

         OutputDebugString( TEXT( "   Extended Error: Server not responding\n" ) );
         break;

      case ERROR_NETBIOS_ERROR:

         OutputDebugString( TEXT( "   Extended Error: NetBIOS error\n" ) );
         break;

      case ERROR_AUTH_INTERNAL:

         OutputDebugString( TEXT( "   Extended Error: Internal Diagnostics Code\n" ) );
         break;

      case ERROR_CANNOT_GET_LANA:

         OutputDebugString( TEXT( "   Extended Error: Routing error code\n" ) );
         break;

      default:

         if ( extended_error_code != 0 )
         {
            TCHAR debug_string[ 99 ];

            _stprintf( debug_string, (LPCTSTR) TEXT( "Unknown extended error code %lu\n" ), extended_error_code );
            OutputDebugString( debug_string );
         }

         break;
   }
}

void test_CRAS( void )
{
   WFCTRACEINIT( TEXT( "test_CRAS()" ) );

   CRemoteAccessService ras;

   CStringArray strings;

   ras.SetConnectionCallback( dial_monitor );
   ras.SetDialOptions( CRemoteAccessService::dialAcceptPausedStates );

   if ( ras.GetPhoneBookEntries( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      WFCTRACE( TEXT( "Phone Book Entries:" ) );

      while( index < number_of_entries )
      {
         WFCTRACE( strings.GetAt( index ) );
         index++;
      }
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      WFCTRACE( TEXT( "\nCurrent Connections:" ) );

      while( index < number_of_entries )
      {
         WFCTRACE( strings[ index ] );
         index++;
      }
   }

   if ( ras.Open( TEXT( "Erols" ) ) == FALSE )
   {
      CString error_string;
      ras.GetErrorString( error_string );
      WFCTRACEVAL( TEXT( "Ras Open failed with " ), error_string );
   }
   else
   {
      WFCTRACE( TEXT( "RAS Open!\n" ) );
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      WFCTRACE( TEXT( "Current Connections:" ) );

      while( index < number_of_entries )
      {
         WFCTRACE( strings[ index ] );
         index++;
      }
   }

   Sleep( 5000 );

   if ( ras.Close( TEXT( "Erols" ) ) != FALSE )
   {
      WFCTRACE( TEXT( "Close OK\n" ) );
   }
} 
