#include <afx.h>
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
** $Workfile: html.cpp $
** $Revision: 7 $
** $Modtime: 9/09/98 6:46a $
*/

#if defined( _DEBUG )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

void set_directory_name( const CString& input, CString& output )
{
   output = input.Right( input.GetLength() - 1 );

   if ( output.GetLength() > 0 )
   {
      if ( output.GetAt( output.GetLength() - 1 ) != TEXT( '\\' ) )
      {
         output += TEXT( "\\" );
      }
   }
}

void pull_html_from_file( const CString& file_name, const CString& output_directory_name )
{
   CStdioFile input_file;

   if ( input_file.Open( file_name, CFile::modeRead ) == FALSE )
   {
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) file_name );
      return;
   }

   CString string_from_file;
   CString start_tag( TEXT( "<HTML>" ) );
   CString stop_tag( TEXT( "</HTML>" ) );
   CString output_filename;

   int start_tag_length = start_tag.GetLength();
   int stop_tag_length  = stop_tag.GetLength();

   while( input_file.ReadString( string_from_file ) != FALSE )
   {
      // Look for that start tag

      if ( string_from_file.GetLength() >= start_tag_length )
      {
         if ( start_tag.CompareNoCase( string_from_file.Left( start_tag_length ) ) == 0 )
         {
            // We've found the beginning of the documentation

            CString html_file_name = file_name;

            int period_location = file_name.Find( TEXT( '.' ) );

            if ( period_location != (-1) )
            {
               html_file_name = file_name.Left( period_location );
            }
            else
            {
               html_file_name = file_name;
            }

            html_file_name += TEXT( ".htm" );

            if ( output_directory_name.GetLength() > 0 )
            {
               output_filename  = output_directory_name;
               output_filename += html_file_name;
            }
            else
            {
               output_filename = html_file_name;
            }

            CStdioFile html_file;

            if ( html_file.Open( output_filename, CFile::modeCreate | CFile::modeWrite ) == FALSE )
            {
               _tprintf( TEXT( "Can't open output file %s\n" ), (LPCTSTR) html_file_name );
               input_file.Close();
               return;
            }
            else
            {
               _tprintf( TEXT( "Creating %s\n" ), (LPCTSTR) html_file_name );
            }

            while( input_file.ReadString( string_from_file ) != FALSE )
            {
               if ( string_from_file.GetLength() >= stop_tag_length )
               {
                  if ( stop_tag.CompareNoCase( string_from_file.Left( stop_tag_length ) ) == 0 )
                  {
                     // Stop tag reached

                     html_file.Close();
                     input_file.Close();
                     return;
                  }
               }

               string_from_file += TEXT( "\n" );

               html_file.WriteString( string_from_file );
            }

            // If we get here it means there wasn't a stop tag!

            _tprintf( TEXT( "WARNING! %s has no stop tag (%s)\n" ), (LPCTSTR) file_name, (LPCTSTR) stop_tag );

            html_file.Close();
         }
      }
   }

   input_file.Close();
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   // When I renamed argv and argc, I forgot to change the following
   // statement. Thanks go to Robin Abecasis (robina@pacific.net.sg)
   // for pointing this out...

   if ( number_of_command_line_arguments < 2 )
   {
      _tprintf( TEXT( "HTML Extractor, Samuel R. Blackburn, %s\n" ), TEXT( "$Revision: 7 $" ) );
      _tprintf( TEXT( "Usage: html [-output_directory] html_file [html_file|-output_directory [...]]\n" ) );
      _tprintf( TEXT( "HTML pulls all lines between (and including) start of HTML\n" ) );
      _tprintf( TEXT( "and end of HTML tags and puts them into a file with an .htm extension.\n" ) );
      _tprintf( TEXT( "<HTML> and </HTML> tags must exist on lines all by themselves.\n" ) );
      _tprintf( TEXT( "For example:\n<HTML>\n<H1>My Page</H1>\n</HTML>\n" ) );
      _tprintf( TEXT( "You can use the -output_directory option to have the resulting .htm\n" ) );
      _tprintf( TEXT( "written there. Example:\n" ) );
      _tprintf( TEXT( "html -c:\\wfc\\classes *.cpp -c:\\documents *.prg\n" ) );
      _tprintf( TEXT( "This will pull the HTML from all .cpp files and put the .htm files\n" ) );
      _tprintf( TEXT( "into the c:\\wfc\\classes directory. All of the HTML pulled from .prg\n" ) );
      _tprintf( TEXT( "files will be put into the c:\\documents directory.\n" ) );

      return( EXIT_SUCCESS );
   }

   CString output_directory_name;

   HANDLE find_file_handle = (HANDLE) NULL;

   WIN32_FIND_DATA find_data;

   int index = 1;

   while( index < number_of_command_line_arguments )
   {
      if ( command_line_arguments[ index ][ 0 ] == TEXT( '-' ) )
      {
         set_directory_name( command_line_arguments[ index ], output_directory_name );
         _tprintf( TEXT( "Output Directory now %s\n" ), (LPCTSTR) output_directory_name );
      }
      else
      {
         ZeroMemory( &find_data, sizeof( find_data ) );

         find_file_handle = FindFirstFile( command_line_arguments[ index ], &find_data );

         if ( find_file_handle != INVALID_HANDLE_VALUE )
         {
            pull_html_from_file( find_data.cFileName, output_directory_name );

            while( FindNextFile( find_file_handle, &find_data ) != FALSE )
            {
               pull_html_from_file( find_data.cFileName, output_directory_name );
            }

            FindClose( find_file_handle );
         }
      }

      index++;
   }

   return( EXIT_SUCCESS );
}
