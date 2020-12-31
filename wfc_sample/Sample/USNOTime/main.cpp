#include <wfc.h>
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CTalkingSocket socket;

   CString line;
   CString temp_string;

   CSystemTime system_time;

   CTime the_time = CTime::GetCurrentTime();

   int year = the_time.GetYear();

   CTimeSpan time_span;

   socket.SetStringReadTerminatorCharacter( LINE_FEED );

   if ( socket.Open( TEXT( "192.5.41.41" ), 13 ) == FALSE )
   {
      _tprintf( TEXT( "Can't connect to tock.usno.navy.mil trying tick.usno.navy.mil\n" ) );

      if ( socket.Open( TEXT( "192.5.41.40" ), 13 ) == FALSE )
      {
         _tprintf( TEXT( "Can't connect to tick or tock at usno.navy.mil\n" ) );
         return( EXIT_FAILURE );
      }
   }

   int number_of_lines = 0;
   int network_delay   = 0;
   int days            = 0;
   int hours           = 0;
   int minutes         = 0;
   int seconds         = 0;

   socket.Read( line );
   socket.Read( line );

   socket.Read( line );

   int location = line.Find( TEXT( "= " ) );

   if ( location == (-1) )
   {
      _tprintf( TEXT( "Can't find network delay\n" ) );
      socket.Close();
      return( EXIT_SUCCESS );
   }

   temp_string = line.Right( line.GetLength() - ( location + 2 ) );

   network_delay = _ttoi( temp_string );

   socket.Read( line );
   WFCTRACE( line );

   socket.Read( line ); // ERROR RETURNED ON IOCTL CALL (169)!

   // 00000000001111111111
   // 01234567890123456789
   // 50652 204 102729 UTC

   if ( line.GetLength() > 22 )
   {
      _tprintf( TEXT( "Unexpected line %s" ), (LPCTSTR) line );
      WFCTRACEVAL( TEXT( "Unexpected line " ), line );
      WFCTRACEVAL( TEXT( "length " ), line.GetLength() );
      socket.Close();
      return( EXIT_SUCCESS );
   }

   days    = _ttoi( line.Mid(  6, 3 ) );
   hours   = _ttoi( line.Mid( 10, 2 ) );
   minutes = _ttoi( line.Mid( 12, 2 ) );
   seconds = _ttoi( line.Mid( 14, 2 ) );

   // Let's adjust the seconds for the delay

   if ( network_delay >= 1000 )
   {
      seconds += (network_delay / 1000);
      network_delay %= 1000;
   }

   time_span = CTimeSpan( days - 1, hours, minutes, seconds );

   the_time = CTime( year, 1, 1, 0, 0, 0 ); // The beginning of this year

   the_time += time_span;

#if defined( _DEBUG )

   afxDump << TEXT( "Setting time to " ) << the_time << TEXT( "\n" );

#endif // _DEBUG

   system_time.wYear         = (short) the_time.GetYear();
   system_time.wMonth        = (short) the_time.GetMonth();
   system_time.wDay          = (short) the_time.GetDay();
   system_time.wHour         = (short) the_time.GetHour();
   system_time.wMinute       = (short) the_time.GetMinute();
   system_time.wSecond       = (short) the_time.GetSecond();
   system_time.wMilliseconds = (short) network_delay;

   socket.Read( line );

   if ( system_time.Set() != FALSE )
   {
      _tprintf( TEXT( "Time synchronized\n" ) );
      WFCTRACE( TEXT( "Time was set" ) );
   }
   else
   {
      _tprintf( TEXT( "Time not synchronized\n" ) );
      WFCTRACE( TEXT( "Time was not set" ) );
   }

   socket.Close();

   return( EXIT_SUCCESS );
}