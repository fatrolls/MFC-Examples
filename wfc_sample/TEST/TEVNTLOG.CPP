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
** $Workfile: TEVNTLOG.CPP $
** $Revision: 6 $
** $Modtime: 4/01/00 1:01p $
*/

void test_CEventLog( void )
{
   WFCTRACEINIT( TEXT( "test_CEventLog()" ) );

#if 0
   CEventLog log( TEXT( "Dodah" ) );

   LPCTSTR string_array[ 1 ];

   string_array[ 0 ] = TEXT( "Hello World" );

   log.Report( CEventLog::eventInformation, 0, 0, 1, string_array );
   log.ReportInformation( TEXT( "ReportInformation" ) );
   log.ReportError( TEXT( "ReportError" ) );
#endif

   CEventLog log;

   DWORD enumerator = 0;

   if ( log.EnumerateLogs( enumerator ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't enumerate logs.\n" ) );
   }

   CString log_name;

   while( log.GetNextLog( enumerator, log_name ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Log: " ), log_name );
   }

   if ( log.CreateCustomLog( TEXT( "WFC" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't create WFC event log because" ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }

   if ( log.Open( TEXT( "WFC" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't Open WFC event log because" ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }

   if ( log.RegisterSource( TEXT( "WFC" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't Open WFC event log because" ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }

   log.ReportInformation( TEXT( "ReportInformation" ) );
   log.ReportError( TEXT( "ReportError" ) );

   CEventLogRecord record;

   DWORD loop_index   = 0;
   DWORD string_index = 0;

   CString event_string;

   while( log.Read( loop_index, record ) != FALSE )
   {
#if defined( _DEBUG ) && ! defined( WFC_STL )
      record.Dump( afxDump );
#endif // _DEBUG

      string_index = 0;

      while( string_index < (DWORD) record.Strings.GetSize() )
      {
         event_string = record.Strings.GetAt( string_index );
         WFCTRACEVAL( TEXT( "String is " ), event_string );
         string_index++;
      }

      loop_index++;
   }

   ASSERT( loop_index != 0 );

#if 1
   if ( log.Delete( TEXT( "WFC" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't delete WFC event log because" ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }
#endif
}
