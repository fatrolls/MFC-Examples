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
** $Workfile: CMixerControl.cpp $
** $Revision: 3 $
** $Modtime: 11/17/96 5:51p $
*/

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

   CSimpleSocketFile socket_file( socket_id, host_name, dotted_ip_address_string );

   socket_file.Write( string_to_send );

   socket_file.Close();
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   CMyListeningSocket incoming_connection;

   // Wait for a connection on port number 1111 (23 == telnet)

   while( incoming_connection.WaitForConnection( 1111 ) != FALSE )
   {
      WFCTRACE( TEXT( "Connection was made" ) );
   }

   return( EXIT_SUCCESS );
}
