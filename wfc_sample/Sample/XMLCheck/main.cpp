#include "XMLCheck.h"
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
** Copyright, 1999, Samuel R. Blackburn
**
** $Workfile: save_document.cpp $
** $Revision: 1 $
** $Modtime: 3/23/98 7:09p $
*/

#if defined( _DEBUG )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

BOOL directory_read_callback_function( void * , const CString& filename )
{
   check_xml_file( filename );
   return( TRUE );
}

void test_CDataParser( void )
{
   WFCTRACEINIT( TEXT( "test_CDataParser()" ) );

   CByteArray bytes;

   bytes.Add( '1' );
   bytes.Add( '5' );
   bytes.Add( '7' );
   bytes.Add( '.' );
   bytes.Add( '1' );
   bytes.Add( '9' );
   bytes.Add( '8' );
   bytes.Add( '.' );
   bytes.Add( '1' );
   bytes.Add( '7' );
   bytes.Add( '.' );
   bytes.Add( '1' );
   bytes.Add( '9' );

   CDataParser parser;

   parser.Initialize( &bytes );

   CParsePoint here;

   CString string_to_get;

   if ( parser.Get( here, 13, string_to_get ) == FALSE )
   {
      WFCTRACE( TEXT( "Failed string." ) );
      return;
   }

   WFCTRACEVAL( TEXT( "Passed with " ), string_to_get );

   here.Empty();

   CByteArray bytes_to_get;

   if ( parser.Get( here, 13, bytes_to_get ) == FALSE )
   {
      WFCTRACE( TEXT( "Failed bytes." ) );
      return;
   }

   WFCTRACE( TEXT( "Passed bytes." ) );
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   // WFCTRACELEVELON( 31 );
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   //check_xml_file( "d:\\test3.xml" );

   //return( EXIT_SUCCESS );

   //test_CDataParser();

   //return( EXIT_SUCCESS );

   if ( number_of_command_line_arguments < 2 )
   {
      _tprintf( TEXT( "Usage: xml_file [xml_file [xml_file [...]]]\n" ) );
      return( EXIT_SUCCESS );
   }

#if 0

   CFileDirectory directory;

   int index = 1;

   while( index < number_of_command_line_arguments )
   {
      if ( directory.Open( command_line_arguments[ index ] ) != FALSE )
      {
         directory.ReadRecursively( directory_read_callback_function, NULL );
      }
      else
      {
         _tprintf( TEXT( "Can't open directory \"%s\"\n" ), command_line_arguments[ index ] );
      }

      index++;
   }

#else

   HANDLE find_file_handle = (HANDLE) NULL;

   WIN32_FIND_DATA find_data;

   int index = 1;

   while( index < number_of_command_line_arguments )
   {
      ZeroMemory( &find_data, sizeof( find_data ) );

      WFCTRACEVAL( TEXT( "Finding " ), CString( command_line_arguments[ index ] ) );

      find_file_handle = FindFirstFile( command_line_arguments[ index ], &find_data );

      if ( find_file_handle != INVALID_HANDLE_VALUE )
      {
         check_xml_file( find_data.cFileName );

         while( FindNextFile( find_file_handle, &find_data ) != FALSE )
         {
            check_xml_file( find_data.cFileName );
         }

         FindClose( find_file_handle );
      }

      index++;
   }

#endif

   return( EXIT_SUCCESS );
}
