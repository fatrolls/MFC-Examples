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
** $Workfile: SprintSpectrum.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:20p $
*/

void wait_for_ring( void )
{
   WFCTRACEINIT( TEXT( "wait_for_ring()" ) );
   CSerialFile serial;

   while( 1 )
   {
      _tprintf( TEXT( "Opening serial port\n" ) );
      WFCTRACE( TEXT( "Opening serial port" ) );

      if ( serial.Open( TEXT( "COM1:57600,n,8,1" ) ) != FALSE )
      {
         CString response;

         response = TEXT( "ATM0\r\n" );

         serial.Write( response );

         // See if the phone rang

         while ( serial.WaitForString( TEXT( "RING" ), 2, &response ) == FALSE )
         {
            if ( response.GetLength() > 0 )
            {
               _tprintf( TEXT( "Didn't get RING, going to sleep \"%s\"\n" ), (LPCTSTR) response );
               WFCTRACEVAL( TEXT( "Didn't get RING, got " ), response );
            }

            ::Sleep( 10000 );
         }

         _tprintf( TEXT( "Received a RING, waiting for them to end\n" ) );
         WFCTRACE( TEXT( "Waiting for RINGs to stop" ) );

         while( serial.WaitForString( TEXT( "RING" ), 7 ) != FALSE )
         {
            // Do Nothing
         }

         _tprintf( TEXT( "Closing serial port\n" ) );

         serial.Close();

         CTime time_now( CTime::GetCurrentTime() );

         ::Sleep( 1000 );

         CString message;
         
         message.Format( TEXT( "The phone rang at %s" ), (LPCTSTR) time_now.Format( "%H:%M:%S %d %b %y" ) );

         CSprintSpectrum pager;

         pager.SetAccount( TEXT( "4109057269" ) );
         pager.SetMessage( message );

         _tprintf( TEXT( "Calling pager.Send()\n" ) );

         pager.Send();
      }
      else
      {
         _tprintf( TEXT( "Can't open serial port\n" ) );
      }

      ::Sleep( 1000 );
   }
}

int _tmain( int argc, LPCTSTR argv[] )
{
   // wait_for_ring();

   if ( argc < 3 )
   {
      _tprintf( TEXT( "Usage: SprintSpectrum Account \"Message\" [com_port][phone_number]\n" ) );
      _tprintf( TEXT( "Example: SprintSpectrum 4101234567 \"Hello World\" COM1:9600,e,7,1 1-800-272-6505\n" ) );
      return( EXIT_SUCCESS );
   }

   CSprintSpectrum pager;

   pager.SetAccount( argv[ 1 ] );
   pager.SetMessage( argv[ 2 ] );

   if ( argc > 3 )
   {
      pager.SetSerialPort( argv[ 3 ] );
   }

   if ( argc > 4 )
   {
      pager.SetPhoneNumber( argv[ 4 ] );
   }

   if ( pager.Send() == FALSE )
   {
      _tprintf( TEXT( "Page not sent.\n" ) );
   }
   else
   {
      _tprintf( TEXT( "Page sent.\n" ) );
   }

   return( EXIT_SUCCESS );
}
