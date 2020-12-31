#include "TortureXML.h"
#pragma hdrstop

void create_huge_encoding( LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random )
{
   WFCTRACEINIT( TEXT( "create_huge_encoding()" ) );

   CFile file;

   if ( file.Open( filename, CFile::modeCreate | CFile::modeWrite ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't create file." ) );
      return;
   }

   BYTE buffer[ 100 ];

   ZeroMemory( buffer, sizeof( buffer ) );

   strcpy( (char *) buffer, "<?xml version=\"1.0\" encoding=\"" );

   file.Write( (const char *) buffer, strlen( (const char *) buffer ) );

   CString legal_characters( TEXT( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-" ) );

   DWORD number_of_legal_characters = legal_characters.GetLength();
   DWORD loop_index                 = 0;

   while( loop_index < size )
   {
      buffer[ 0 ] = legal_characters.GetAt( random.GetInteger() % number_of_legal_characters );
      file.Write( buffer, 1 );
      loop_index++;
   }

   buffer[ 0 ] = '\"';
   buffer[ 1 ] = ' ';
   buffer[ 2 ] = '?';
   buffer[ 3 ] = '>';
   buffer[ 4 ] = CARRIAGE_RETURN;
   buffer[ 5 ] = LINE_FEED;

   file.Write( buffer, 6 );
   file.Close();
}

