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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: LastEvent.cpp $
** $Revision: 2 $
** $Modtime: 4/02/98 6:24a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if defined( UNICODE )
extern "C"
#endif // UNICODE

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   DWORD number_of_events = 10;

   CEventLog event_log;

   if ( event_log.Open( TEXT( "System" ) ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "event_log.Open() failed with error code " ), event_log.GetErrorCode() );
      _tprintf( TEXT( "Can't open event log because %lu\n" ), event_log.GetErrorCode() );
      return( EXIT_SUCCESS );
   }

   if ( number_of_command_line_arguments > 2 )
   {
      number_of_events = _ttoi( command_line_arguments[ 1 ] );

      if ( number_of_events == 0 )
      {
         number_of_events = 1;
      }
   }

   DWORD number_of_records = 0;

   if ( event_log.GetNumberOfRecords( number_of_records ) == FALSE )
   {
      _tprintf( TEXT( "Can't get number of records because %lu\n" ), event_log.GetErrorCode() );
      return( EXIT_SUCCESS );
   }

   WFCTRACEVAL( TEXT( "Number of records is " ), number_of_records );
   _tprintf( TEXT( "There are %lu number of records.\n" ), number_of_records );

   DWORD last_record_number = 0;

   last_record_number = event_log.GetOldestRecordNumber();

   WFCTRACEVAL( TEXT( "Oldest record number is " ), last_record_number );
   _tprintf( TEXT( "Oldest record number is %lu\n" ), last_record_number );

   CEventLogRecord record;

   DWORD index                 = 0;
   DWORD record_number_to_read = 0;

   while( index < number_of_events )
   {
      if ( event_log.Read( index + 1, record, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "Cant read because " ), event_log.GetErrorCode() );
         _tprintf( TEXT( "Can't read record #%lu because %lu\n" ), index, event_log.GetErrorCode() );
      }
      else
      {
         if ( record.Strings.GetSize() > 0 )
         {
            _tprintf( TEXT( "%s, %lu %s\n" ),
                      (LPCTSTR) record.Source,
                      (DWORD) LOWORD( record.EventID ),
                      (LPCTSTR) record.Strings.GetAt( 0 ) );
         }
         else
         {
            _tprintf( TEXT( "%s, %lu\n" ),
                      (LPCTSTR) record.Source,
                      (DWORD) LOWORD( record.EventID ) );
         }
      }

      index++;
   }

   return( EXIT_SUCCESS );
}
