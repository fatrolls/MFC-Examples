#include <wfc.h>
#include "../CSimpleClass.hpp"
#pragma hdrstop

class CChunkReceivingSocket : public CListeningSocket
{
   public:

      virtual void OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address_string ); // Called by WaitForConnection
};

void CChunkReceivingSocket::OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address_string )
{
   CSimpleSocketFile socket( socket_id, host_name, dotted_ip_address_string );

   CDataChunk chunk;

   CDataSocket data_socket( &socket );

   // Read a chunk

   data_socket.GetData( chunk );

   // Now find out what to do with it

   switch( chunk.Identifier )
   {
      case MAKE_DATA_ID( 'S', 'I', 'M', 'P' ):
      {
         // We've got a CSimpleClass chunk

         CSimpleClass simple_class;

         CDataArchive archive;

         archive.ReadFrom( &chunk );

         simple_class.Serialize( archive );

         _tprintf( TEXT( "Received " ) );

         simple_class.Dump();
      }

      break;
   }

   socket.Close();
}

void _tmain( void )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CChunkReceivingSocket socket;

   if ( socket.WaitForConnection( 6060 ) != FALSE )
   {
      _tprintf( TEXT( "Got a connection\n" ) );
   }
   else
   {
      TCHAR error_message[ 513 ];

      ZeroMemory( error_message, sizeof( error_message ) );

      CSimpleSocket::TranslateErrorCode( socket.GetErrorCode(), error_message, DIMENSION_OF( error_message ) );

      _tprintf( TEXT( "Couldn't open because %s\n" ), error_message );
   }
}
