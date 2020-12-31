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
** $Workfile: TCLZFile.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:31p $
*/

void test_CLZFile( LPTSTR lz_file_name )
{
   WFCTRACEINIT( TEXT( "test_CLZFile()" ) );

   CLZFile lz_file;

   if ( lz_file_name == (LPTSTR) NULL )
   {
      return;
   }

   CString expanded_name;

   lz_file.GetExpandedName( lz_file_name, expanded_name );

   _tprintf( TEXT( "LZ File \"%s\" expanded name is \"%s\"\n" ), lz_file_name, (LPCTSTR) expanded_name );

   if ( lz_file.Open( lz_file_name ) != FALSE )
   {
      CLZFile output_file;

      if ( output_file.Open( TEXT( "d:\\temp\\winhlp32.exe" ), OF_CREATE ) != FALSE )
      {
         if ( output_file.Copy( lz_file ) != FALSE )
         {
            _tprintf( TEXT( "Successfully copied\n" ) );
         }
         else
         {
            CString error_message_string;
            CLZFile::TranslateErrorCode( (int) lz_file.GetErrorCode(), error_message_string );
            _tprintf( TEXT( "Can't Copy because %s\n" ), (LPCTSTR) error_message_string );
         }
      }
      else
      {
         CString error_message_string;
         CLZFile::TranslateErrorCode( (int) output_file.GetErrorCode(), error_message_string );
         _tprintf( TEXT( "Can't open LZ output file because %s\n" ), (LPCTSTR) error_message_string );
      }
   }
   else
   {
      CString error_message_string;
      CLZFile::TranslateErrorCode( (int) lz_file.GetErrorCode(), error_message_string );
      _tprintf( TEXT( "Can't open LZ file \"%s\" because \n" ), lz_file_name, (LPCTSTR) error_message_string );
   }
}
