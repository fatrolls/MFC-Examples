#include "XMLConformanceTest.h"
#pragma hdrstop

bool should_parse_have_failed( const CString& filename )
{
   CString test_string( filename );

   test_string.MakeLower();

   if ( test_string.Find( TEXT( "knowngood" ) ) != (-1) )
   {
      return( false );
   }

   if ( test_string.Find( TEXT( "good" ) ) != (-1) )
   {
      return( false );
   }

   if ( test_string.Find( TEXT( "ambiguous" ) ) != (-1) )
   {
      return( false );
   }

   if ( test_string.Find( TEXT( "pass" ) ) != (-1) )
   {
      return( false );
   }

   if ( test_string.Find( TEXT( "\\valid\\" ) ) != (-1) )
   {
      return( false );
   }

   return( true );
}

void check_xml_file( DWORD file_index, const CStringArray& filenames, CDWordArray& results )
{
   WFCTRACEINIT( TEXT( "check_xml_file()" ) );
   //WFCTRACEVAL( TEXT( "Checking " ), filename );
   // d:\WFC\test\xml\xmltest\not-wf\sa

   CExtensibleMarkupLanguageDocument document;

#if 0
   DWORD parsing_options = document.GetParseOptions();

   parsing_options |= WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES;

   document.SetParseOptions( parsing_options );
#endif

   CFile file;

   if ( file.Open( filenames.GetAt( file_index ), CFile::modeRead ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filenames.GetAt( file_index ) );
      WFCTRACEERROR( GetLastError() );
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) filenames.GetAt( file_index ) );
      return;
   }

   CByteArray bytes;

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );

   file.Close();

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   if ( document.Parse( parser ) == FALSE )
   {
      // The parse failed. Let's see if it *should* have failed

      if ( should_parse_have_failed( filenames.GetAt( file_index ) ) == false )
      {
         // The parse should not have failed. That means we flunk the test :-(
         results.SetAt( file_index, 1 );
      }
   }
}

BOOL directory_read_callback_function( void * parameter, const CString& filename )
{
   CStringArray * filenames = (CStringArray *) parameter;

   if ( filenames != NULL )
   {
      if ( filename.Right( 4 ).CompareNoCase( ".XML" ) == 0 )
      {
         // This is an XML file...

         filenames->Add( filename );
      }
   }

   return( TRUE );
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   if ( number_of_command_line_arguments < 2 )
   {
      _tprintf( TEXT( "WFC XML Conformance Tester 1.0\nUsage: %s directory_name [directory_name [...]]\n" ), command_line_arguments[ 0 ] );
      return( EXIT_SUCCESS );
   }

   CFileDirectory directory;

   CStringArray filenames;

   DWORD loop_index = 1;

   while( loop_index < number_of_command_line_arguments )
   {
      if ( directory.Open( command_line_arguments[ loop_index ] ) != FALSE )
      {
         directory.ReadRecursively( directory_read_callback_function, &filenames );
         directory.Close();
      }
      else
      {
         _tprintf( TEXT( "Can't open directory \"%s\"\n" ), command_line_arguments[ loop_index ] );
      }

      loop_index++;
   }

   WFCTRACEVAL( TEXT( "Number of files to test is " ), filenames.GetSize() );
   _tprintf( TEXT( "%lu files to test.\n" ), filenames.GetSize() );

   CDWordArray results;

   DWORD number_of_files_to_test = (DWORD) filenames.GetSize();

   results.SetSize( number_of_files_to_test );

   loop_index = 0;

   // Make sure the results are empty

   while( loop_index < number_of_files_to_test )
   {
      results.SetAt( loop_index, 0 );
      loop_index++;
   }

   // Now go test the files

   loop_index = 0;

   while( loop_index < number_of_files_to_test )
   {
      _tprintf( TEXT( "%lu - \"%s\" - " ),
                (unsigned long) loop_index,
                (LPCTSTR) filenames.GetAt( loop_index ) );
      check_xml_file( loop_index, filenames, results );
      _tprintf( TEXT( "%lu\n" ), (unsigned long) results.GetAt( loop_index ) );

      loop_index++;
   }

   return( EXIT_SUCCESS );
}
