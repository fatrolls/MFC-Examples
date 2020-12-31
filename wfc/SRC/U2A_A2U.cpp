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
** $Workfile: u2a_a2u.cpp $
** $Revision: 15 $
** $Modtime: 4/30/00 5:36p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void ASCII_to_UNICODE( LPCSTR ansi_string, LPWSTR unicode_string )
{
   if ( ansi_string == NULL || unicode_string == NULL )
   {
      return;
   }

   if ( ansi_string == (LPCSTR) unicode_string )
   {
      ASSERT( FALSE );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      int loop_index = 0;

      while( ansi_string[ loop_index ] != 0x00 )
      {
         unicode_string[ loop_index ] = ansi_string[ loop_index ];
         loop_index++;
      }

      unicode_string[ loop_index ] = 0;
   }
   catch( ... )
   {
      return;
   }
}

void UNICODE_to_ASCII( LPCWSTR unicode_string, LPSTR ansi_string, long number_of_unicode_characters_to_convert )
{
   WFCLTRACEINIT( TEXT( "UNICODE_to_ASCII()" ) );

   if ( unicode_string == (LPCWSTR) NULL || ansi_string == (LPSTR) NULL )
   {
      return;
   }

   // 2000-04-30
   // Thanks go to Josh Parris (Josh.Parris@auspost.com.au) for finding
   // a bug here. unicode_string cannot equal ansi_string because that will
   // cause WideCharToMultiByte() to fail.

   ASSERT( (void *) unicode_string != (void *) ansi_string );

   // We were passed a pointer, don't trust it

   try
   {
      if ( number_of_unicode_characters_to_convert == (-1) )
      {
         number_of_unicode_characters_to_convert = wcslen( unicode_string ) + 1;
      }

      if ( number_of_unicode_characters_to_convert > (long) ( wcslen( unicode_string ) + 1 ) )
      {
         number_of_unicode_characters_to_convert = wcslen( unicode_string ) + 1;
      }

      if ( WideCharToMultiByte( CP_ACP, 0, unicode_string, number_of_unicode_characters_to_convert, ansi_string, number_of_unicode_characters_to_convert, NULL, NULL ) == 0 )
      {
         ansi_string[ 0 ] = 0x00;
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Conversion from UNICODE to ASCII failed for the above resaon." ) );
      }
   }
   catch( ... )
   {
      return;
   }
}

// End of source
