#include "my_xml.h"
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
** $Workfile: main.cpp $
** $Revision: 3 $
** $Modtime: 4/18/98 9:24a $
*/

void stanza_callback( void *, CExtensibleMarkupLanguageElement * element_p )
{
   WFCTRACEINIT( TEXT( "stanza_callback()" ) );
   WFCTRACEVAL( TEXT( "Got a stanza, number of children is " ), element_p->GetNumberOfChildren() );

   _tprintf( TEXT( "Got a stanza with %lu children\n" ), (DWORD) element_p->GetNumberOfChildren() );
}

#if defined( UNICODE )
extern "C"
#endif

int _tmain( int /* number_of_command_line_arguments */, LPCTSTR /* command_line_arguments */ [] )
{
   WFCTRACELEVELOFF( 31 ); // Turn WFC debugging statements off
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CExtensibleMarkupLanguageDocument document;

   CExtensibleMarkupLanguageElement * element_p = NULL;

   WFCTRACELEVELON( 31 ); // Turn WFC debugging statements on

   if ( parse_document( TEXT( "/wfc/sample/xml/hell.xml" ), document ) == TRUE )
   {
      WFCTRACELEVELOFF( 31 ); // Turn WFC debugging statements off
      // OK, we parsed the document, let's get the offending element

      element_p = document.GetElement( TEXT( "PERSON" ) );

      if ( element_p != NULL )
      {
         CString attribute_value;

         if ( element_p->GetAttributeByName( TEXT( "Attribute" ), attribute_value ) != FALSE )
         {
            attribute_value += TEXT( "<--" );
            WFCTRACEVAL( TEXT( "Attribute value is " ), attribute_value );
         }
      }
      else
      {
         WFCTRACE( TEXT( "Can't find element PERSON" ) );
      }

      element_p = document.GetElement( TEXT( "PERSON(1)" ) );

      if ( element_p != NULL )
      {
         CString attribute_value;

         if ( element_p->GetAttributeByName( TEXT( "A1" ), attribute_value ) != FALSE )
         {
            attribute_value += TEXT( "<--" );
            WFCTRACEVAL( TEXT( "Attribute value is " ), attribute_value );
         }
         else
         {
            WFCTRACE( TEXT( "Can't get attribute A1" ) );
         }

         if ( element_p->GetAttributeByName( TEXT( "A2" ), attribute_value ) != FALSE )
         {
            attribute_value += TEXT( "<--" );
            WFCTRACEVAL( TEXT( "Attribute value is " ), attribute_value );
         }
         else
         {
            WFCTRACE( TEXT( "Can't get attribute A2" ) );
         }
      }
      else
      {
         WFCTRACE( TEXT( "Can't find element PERSON" ) );
      }
   }

   WFCTRACELEVELOFF( 31 ); // Turn WFC debugging statements off

   return( EXIT_SUCCESS );

   document.AddCallback( TEXT( "stanza" ), stanza_callback, NULL );

   //CString element_name( TEXT( "poem.body.stanza(1).line(1)" ) );
   CString element_name( TEXT( "poem.front.[cdata[" ) );

   DWORD number_of_elements = 0;

   // if ( parse_document( TEXT( "/wfc/sample/xml/poem.original" ), document ) == TRUE )
   if ( parse_document( TEXT( "/wfc/sample/xml/test.xml" ), document ) == TRUE )
   {
   WFCTRACELEVELON( 31 );
      number_of_elements = document.CountElements( TEXT( "poem.body.stanza(  1  ).line" ) );
   WFCTRACELEVELOFF( 31 );

      WFCTRACEVAL( TEXT( "Number of elements is " ), number_of_elements );

      element_p = document.GetElement( element_name );

      if ( element_p != NULL )
      {
         WFCTRACE( TEXT( "Element FOUND!" ) );

         CString element_text;

         element_p->GetText( element_text );

         WFCTRACEVAL( TEXT( "Text is " ), element_text );
         _tprintf( TEXT( "%s" ), (LPCTSTR) element_text );

         if ( element_text.Compare( TEXT( "Behind, before, above, between, below." ) ) == 0 )
         {
            WFCTRACE( TEXT( "YES! IT WORKS!!!!" ) );
         }
         else
         {
            WFCTRACE( TEXT( "You screwed up again." ) );
         }
      }
      else
      {
         WFCTRACEVAL( TEXT( "Can't find that there element " ), element_name );
      }

      CByteArray xml;

      document.WriteTo( xml );

      WFCTRACEVAL( TEXT( "Number of bytes written is " ), xml.GetSize() );
      _tprintf( TEXT( "Wrote %d bytes\n" ), xml.GetSize() );

      CFile file;

      if ( file.Open( TEXT( "xml.out" ), CFile::modeCreate | CFile::modeWrite ) != FALSE )
      {
         file.Write( xml.GetData(), xml.GetSize() );
         file.Close();
      }
   }

   return( EXIT_SUCCESS );
}