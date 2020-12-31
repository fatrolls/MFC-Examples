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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: sl.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:19p $
*/

// To see how this works, start this sample under the debugger and then
// go to a DOS box and type "start telnet ipaddress 1111" where ipaddress
// is the IP address of the machine you are running on. The debug window
// will show the progress of what's happening.

#if defined( _DEBUG )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

class CMyListeningSocket : public CListeningSocket
{
   public:

      virtual void OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address_string );
};

void CMyListeningSocket::OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address_string )
{
   WFCTRACEINIT( TEXT( "CMyListeningSocket::OnNewConnection()" ) );

   CString string_to_send;

   string_to_send.Format( TEXT( "Your name is \"%s\", your IP address is \"%s\"\n" ),
                          host_name,
                          dotted_ip_address_string );

   // You could create a thread here and pass the data along to it so it can handle
   // the session...

   CSimpleSocketFile socket_file( socket_id, host_name, dotted_ip_address_string );

   socket_file.Write( string_to_send );

   socket_file.Close();
}

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CSimpleSocket::StartWindowsSockets();

   CMyListeningSocket incoming_connection;

   // Wait for a connection on port number 1111 (23 == telnet)

   while( incoming_connection.WaitForConnection( 1111 ) != FALSE )
   {
      WFCTRACE( TEXT( "Connection was made" ) );
   }

   DWORD error_code = incoming_connection.GetErrorCode();

   WFCTRACEVAL( TEXT( "Error Code is " ), error_code );

   TCHAR error_string[ 513 ];

   ZeroMemory( error_string, sizeof( error_string ) );

   CSimpleSocket::TranslateErrorCode( error_code, error_string, DIMENSION_OF( error_string ) );

   WFCTRACEVAL( TEXT( "Meaning is " ), CString( error_string ) );

   CSimpleSocket::StopWindowsSockets();

   return( EXIT_SUCCESS );
}
