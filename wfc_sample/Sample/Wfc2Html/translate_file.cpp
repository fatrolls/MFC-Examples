#include "wfc2html.h"
#pragma hdrstop

void translate_file( const CString& filename, CCPPToHTMLTranslator& translator )
{
   WFCTRACEINIT( TEXT( "translate_file()" ) );

   CStdioFile file;

   if ( file.Open( filename, CFile::modeRead ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filename );
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) filename );
      return;
   }

   CString line;
   CStringArray source_code;

   while( file.ReadString( line ) != FALSE )
   {
      source_code.Add( line );
   }

   file.Close();

   CStringArray html;

   translator.Translate( source_code, html );

   int index           = 0;
   int number_of_lines = html.GetSize();

   while( index < number_of_lines )
   {
      OutputDebugString( html.GetAt( index ) );
      OutputDebugString( TEXT( "\n" ) );
      index++;
   }
}
