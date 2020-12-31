#include "TortureXML.h"
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   CRandomNumberGenerator2 random;

   DWORD number_of_characters = 100;

   if ( number_of_command_line_arguments > 1 )
   {
      number_of_characters = _ttoi( command_line_arguments[ 1 ] );
   }

   if ( number_of_characters < 1 )
   {
      number_of_characters = 10;
   }

   create_huge_element(                TEXT( "torture001.xml" ), number_of_characters, random );
   create_huge_encoding(               TEXT( "torture002.xml" ), number_of_characters, random );
   create_huge_version(                TEXT( "torture003.xml" ), number_of_characters, random );
   create_huge_element_and_attribute(  TEXT( "torture004.xml" ), number_of_characters, random );
   create_huge_element_name(           TEXT( "torture005.xml" ), number_of_characters, random );
   create_huge_character_reference(    TEXT( "torture006.xml" ), number_of_characters, random );

   return( EXIT_SUCCESS );
}
