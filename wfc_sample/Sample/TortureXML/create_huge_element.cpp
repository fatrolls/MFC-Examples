#include "TortureXML.h"
#pragma hdrstop

void create_huge_element( LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random )
{
   WFCTRACEINIT( TEXT( "create_huge_element()" ) );

   CFile file;

   if ( file.Open( filename, CFile::modeCreate | CFile::modeWrite ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't create file." ) );
      return;
   }

   BYTE buffer[ 100 ];

   ZeroMemory( buffer, sizeof( buffer ) );

   strcpy( (char *) buffer, "<?xml version=\"1.0\" ?>" );

   file.Write( (const char *) buffer, strlen( (const char *) buffer ) );

   buffer[ 0 ] = CARRIAGE_RETURN;
   buffer[ 1 ] = LINE_FEED;
   buffer[ 2 ] = '<';
   buffer[ 3 ] = 'S';
   buffer[ 4 ] = '>';

   file.Write( buffer, 5 );

   CString legal_characters( TEXT( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_:.-" ) );

   DWORD number_of_legal_characters = legal_characters.GetLength();
   DWORD loop_index                 = 0;

   CByteArray element_text;

   element_text.SetSize( 0, 8192 );
   
   while( loop_index < size )
   {
      element_text.Add( legal_characters.GetAt( random.GetInteger() % number_of_legal_characters ) );

      if ( ( loop_index % 72 ) == 0 )
      {
         element_text.Add( CARRIAGE_RETURN );
         element_text.Add( LINE_FEED );
      }

      loop_index++;
   }

   file.Write( element_text.GetData(), element_text.GetSize() );

   buffer[ 0 ] = '<';
   buffer[ 1 ] = '/';
   buffer[ 2 ] = 'S';
   buffer[ 3 ] = '>';
   buffer[ 4 ] = CARRIAGE_RETURN;
   buffer[ 5 ] = LINE_FEED;

   file.Write( buffer, 6 );
   file.Close();
}

