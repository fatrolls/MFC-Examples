#include "TortureXML.h"
#pragma hdrstop

void create_huge_character_reference( LPCTSTR filename, DWORD size, CRandomNumberGenerator2& random )
{
   WFCTRACEINIT( TEXT( "create_huge_character_reference()" ) );

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

   DWORD loop_index = 0;

   CByteArray element_text;

   element_text.SetSize( 0, 8192 );

   DWORD end_tick_count = 0;
   DWORD start_tick_count = GetTickCount();
   element_text.Add( '&' );
   element_text.Add( '#' );
   
   while( loop_index < size )
   {
      element_text.Add( '0' );
      loop_index++;
   }

   element_text.Add( '6' );
   element_text.Add( '5' );
   element_text.Add( ';' );

   end_tick_count = GetTickCount();

   WFCTRACEVAL( TEXT( "Milliseconds is " ), (DWORD)( end_tick_count - start_tick_count ) );

   file.Write( element_text.GetData(), element_text.GetSize() );

   loop_index = 0;

   element_text.SetSize( 0, 8192 );

   element_text.Add( '&' );
   element_text.Add( '#' );
   element_text.Add( 'x' );
   
   while( loop_index < size )
   {
      element_text.Add( '0' );
      loop_index++;
   }

   element_text.Add( '4' );
   element_text.Add( '1' );
   element_text.Add( ';' );

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
