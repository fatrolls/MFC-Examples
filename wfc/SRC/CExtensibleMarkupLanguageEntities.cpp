#if ! defined( SUBSET_STLXML )
#include <wfc.h>
#else
#include <stlxml.h>
#endif
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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CExtensibleMarkupLanguageEntities.cpp $
** $Revision: 21 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CExtensibleMarkupLanguageEntities::CExtensibleMarkupLanguageEntities()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::CExtensibleMarkupLanguageEntities()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

CExtensibleMarkupLanguageEntities::CExtensibleMarkupLanguageEntities( const CExtensibleMarkupLanguageEntities& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::CExtensibleMarkupLanguageEntities( CExtensibleMarkupLanguageEntities )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CExtensibleMarkupLanguageEntities::~CExtensibleMarkupLanguageEntities()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::~CExtensibleMarkupLanguageEntities()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

BOOL CExtensibleMarkupLanguageEntities::Add( const CString& entity, const CString& text )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::Add()" ) );

   // entity is in &xxx; form

   // Validate the entity

   if ( entity.GetLength() < 3 )
   {
      WFCTRACE( TEXT( "Entity too short." ) );
      return( FALSE );
   }

   if ( entity.GetAt( 0 ) != TEXT( '&' ) )
   {
      return( FALSE );
   }

   if ( entity.GetAt( entity.GetLength() - 1 ) != TEXT( ';' ) )
   {
      return( FALSE );
   }

   // Now validate the name characters according to Rule 68->5

   if ( ::is_xml_Letter( entity.GetAt( 1 ) ) != TRUE &&
        entity.GetAt( 1 ) != TEXT( '_' ) &&
        entity.GetAt( 1 ) != TEXT( ':' ) )
   {
      WFCTRACE( TEXT( "Bad first character of entity name." ) );
      return( FALSE );
   }

   int loop_index = 2;

   while( loop_index < entity.GetLength() - 1 )
   {
      if ( ::is_xml_NameChar( entity.GetAt( loop_index ) ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "This entity is bad " ), entity );
         WFCTRACEVAL( TEXT( "This character index " ), loop_index );
         return( FALSE );
      }

      loop_index++;
   }

   // First, normalize the text as described in Appendix D

   CString resolved_string;

   if ( text.Find( TEXT( "&#" ) ) == (-1) )
   {
      // Well, that was easy
      resolved_string = text;
   }
   else
   {
      CString temp_string( text );
      CString number_string;

      int location_of_character_reference = temp_string.Find( TEXT( "&#" ) );

      while( location_of_character_reference != (-1) )
      {
         resolved_string += temp_string.Left( location_of_character_reference );
         temp_string = temp_string.Right( temp_string.GetLength() - ( location_of_character_reference + 2 ) );
         number_string.Empty();

         // See if we are decimal or hexadecimal . . .

         BOOL is_hexadecimal_character_reference = FALSE;

         if ( temp_string.GetLength() > 0 && temp_string.GetAt( 0 ) == TEXT( 'x' ) )
         {
            // We are hexadecimal
            is_hexadecimal_character_reference = TRUE;

            // Skip the x (yes, it must be lower case)

            temp_string = temp_string.Right( temp_string.GetLength() - 1 );

            while( temp_string.GetLength() > 0 &&
                   ( ( temp_string.GetAt( 0 ) >= '0' && temp_string.GetAt( 0 ) <= '9' ) ||
                     ( temp_string.GetAt( 0 ) >= 'A' && temp_string.GetAt( 0 ) <= 'Z' ) ||
                     ( temp_string.GetAt( 0 ) >= 'a' && temp_string.GetAt( 0 ) <= 'z' ) ) )
            {
               number_string += temp_string.GetAt( 0 );
               temp_string = temp_string.Right( temp_string.GetLength() - 1 );
            }
         }
         else
         {
            // We are decimal

            while( temp_string.GetLength() > 0 &&
                   temp_string.GetAt( 0 ) >= '0' && temp_string.GetAt( 0 ) <= '9' )
            {
               number_string += temp_string.GetAt( 0 );
               temp_string = temp_string.Right( temp_string.GetLength() - 1 );
            }
         }

         if ( temp_string.GetLength() == 0 || temp_string.GetAt( 0 ) != ';' )
         {
            WFCTRACE( TEXT( "Ill-formed character reference" ) );
            return( FALSE );
         }

         temp_string = temp_string.Right( temp_string.GetLength() - 1 );

         DWORD character_to_add_to_string = 0;

         TCHAR * end_pointer = NULL;

         if ( is_hexadecimal_character_reference == TRUE )
         {
            character_to_add_to_string = ::_tcstoul( number_string, &end_pointer, 16 );
         }
         else
         {
            character_to_add_to_string = ::_tcstoul( number_string, &end_pointer, 10 );
         }

         if ( ::is_xml_Char( character_to_add_to_string ) == FALSE )
         {
            WFCTRACE( TEXT( "Illegal XML character resolved" ) );
            return( FALSE );
         }

         resolved_string += static_cast< TCHAR >( ::_ttoi( number_string ) );
         location_of_character_reference = temp_string.Find( TEXT( "&#" ) );
      }

      resolved_string += temp_string;
   }

   WFCTRACEVAL( TEXT( "resolved_string is " ), resolved_string );

   // The list is sorted for quick searching using a binary search

   long lower_limit = 0;
   long upper_limit = m_Entities.GetUpperBound();

   if ( upper_limit == (-1) )
   {
      m_Entities.Add( entity );
      m_Values.Add( resolved_string );
      return( TRUE );
   }

   long here = upper_limit / 2;

   CString entity_in_list;

   int comparison_result = 0;

   do
   {
      entity_in_list = m_Entities.GetAt( here );

      comparison_result = entity.Compare( entity_in_list );

      if ( comparison_result < 0 )
      {
         upper_limit = here - 1;
      }
      else if ( comparison_result > 0 )
      {
         lower_limit = here + 1;
      }
      else
      {
         // WE FOUND IT!
         // This means we must be reading an existing entity

         CString text_already_defined;

         text_already_defined = m_Values.GetAt( here );

         if ( text.Compare( text_already_defined ) != 0 )
         {
            WFCTRACE( TEXT( "WARNING! Redefining an existing entity!" ) );

            m_Values.SetAt( here, resolved_string );
         }

         return( TRUE );
      }

      here = ( lower_limit + upper_limit ) / 2;
   }
   while( lower_limit <= upper_limit );

   // If we get here, the entity wasn't in the list, we need to add it

   if ( here > 0 )
   {
      here--;
   }

   upper_limit = m_Entities.GetUpperBound();

   comparison_result = entity.Compare( m_Entities.GetAt( here ) );

   while( here < upper_limit && comparison_result > 0 )
   {
      here++;
      comparison_result = entity.Compare( m_Entities.GetAt( here ) );
   }

   if ( here >= upper_limit && comparison_result > 0 )
   {
      m_Entities.Add( entity );
      m_Values.Add( resolved_string );
   }
   else
   {
      m_Entities.InsertAt( here, entity );
      m_Values.InsertAt( here, resolved_string );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageEntities::Copy( const CExtensibleMarkupLanguageEntities& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::Copy()" ) );
   m_Entities.Copy( source.m_Entities );
   m_Values.Copy( source.m_Values );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CExtensibleMarkupLanguageEntities::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CExtensibleMarkupLanguageEntities at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_Entities has " ) << m_Entities.GetSize() << TEXT( " elements.\n   {\n" );

   long loop_index         = 0;
   long number_of_elements = m_Entities.GetSize();

   while( loop_index < number_of_elements )
   {
      dump_context << TEXT( "      " ) << loop_index << TEXT( " - \"" ) << m_Entities.GetAt( loop_index ) << TEXT( "\"\n" );
      loop_index++;
   }

   dump_context << TEXT( "   }\n" );

   dump_context << TEXT( "   m_Values has " ) << m_Values.GetSize() << TEXT( " elements.\n   {\n" );

   loop_index         = 0;
   number_of_elements = m_Values.GetSize();

   while( loop_index < number_of_elements )
   {
      dump_context << TEXT( "      " ) << loop_index << TEXT( " - \"" ) << m_Values.GetAt( loop_index ) << TEXT( "\"\n" );
      loop_index++;
   }

   dump_context << TEXT( "   }\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUGDump

void CExtensibleMarkupLanguageEntities::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::Empty()" ) );
   m_Entities.RemoveAll();
   m_Values.RemoveAll();
}

BOOL CExtensibleMarkupLanguageEntities::Enumerate( DWORD& enumerator ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::Enumerate()" ) );

   ASSERT( m_Entities.GetSize() == m_Values.GetSize() );

   enumerator = 0;

   if ( m_Entities.GetSize() > 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CExtensibleMarkupLanguageEntities::GetNext( DWORD& enumerator, CString& entity, CString& value ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::GetNext()" ) );

   ASSERT( m_Entities.GetSize() == m_Values.GetSize() );

   if ( enumerator < (DWORD) m_Entities.GetSize() )
   {
      entity = m_Entities.GetAt( enumerator );
      value  = m_Values.GetAt( enumerator );

      enumerator++;

      return( TRUE );
   }

   return( FALSE );
}

long CExtensibleMarkupLanguageEntities::GetSize( void ) const
{
   ASSERT( m_Entities.GetSize() == m_Values.GetSize() );
   return( m_Entities.GetSize() );
}

BOOL CExtensibleMarkupLanguageEntities::IsEntity( const CString& entity, DWORD& rule_that_was_broken ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::IsEntity()" ) );

   // First, check to see if this is a mathematical entity.

   rule_that_was_broken = 0;

   int entity_length = entity.GetLength();

   if ( entity_length < 3 )
   {
      // We must have a leading & and trailing ; and at least one character in the middle

      rule_that_was_broken = 68;
      return( FALSE );
   }

   if ( entity.GetAt( 0 ) != TEXT( '&' ) )
   {
      rule_that_was_broken = 68;
      return( FALSE );
   }

   if ( entity.GetAt( entity.GetLength() - 1 ) != TEXT( ';' ) )
   {
      rule_that_was_broken = 68;
      return( FALSE );
   }

   int loop_index = 0;

   if ( entity.GetAt( 1 ) == TEXT( '#' ) )
   {
      // Check to see if mathematical entity is possible

      if ( entity_length == 3 )
      {
         rule_that_was_broken = 66;
         return( FALSE );
      }

      // Let's see if it is hexadecimal or decimal

      if ( entity.GetAt( 2 ) == TEXT( 'X' ) )
      {
         rule_that_was_broken = 66;
         return( FALSE );
      }

      if ( entity.GetAt( 2 ) == TEXT( 'x' ) )
      {
         // Yup, we be hexadecimal

         loop_index = 0;

         // loop through the digits but skip the trailing ;

         // We use entity_length - 4 because we need to skip the &#x at the beginning and ; at the end

         while( loop_index < ( entity_length - 4 ) )
         {
            if ( _istxdigit( entity.GetAt( loop_index + 3 ) ) == 0 ) // + 3 skips &#x
            {
               rule_that_was_broken = 66;
               return( FALSE );
            }

            loop_index++;
         }

         return( TRUE );
      }
      else
      {
         // Nope, we must be decimal

         loop_index = 0;

         // We use entity_length - 3 because we need to skip the &# at the beginning and ; at the end
         while( loop_index < ( entity_length - 3 ) )
         {
            if ( _istdigit( entity.GetAt( loop_index + 2 ) ) == 0 ) // + 2 skips &#
            {
               rule_that_was_broken = 66;
               return( FALSE );
            }

            loop_index++;
         }

         return( TRUE );
      }
   }

   // Welp, it weren't no mathematical entity

   // Now validate the name characters according to Rule 68->5

   if ( ::is_xml_Letter( entity.GetAt( 1 ) ) != TRUE &&
        entity.GetAt( 1 ) != TEXT( '_' ) &&
        entity.GetAt( 1 ) != TEXT( ':' ) )
   {
      WFCTRACE( TEXT( "Bad first character of entity name." ) );
      rule_that_was_broken = 5;
      return( FALSE );
   }

   loop_index = 2;

   while( loop_index < entity.GetLength() - 1 )
   {
      if ( ::is_xml_NameChar( entity.GetAt( loop_index ) ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "This entity is bad " ), entity );
         WFCTRACEVAL( TEXT( "This character index " ), loop_index );
         rule_that_was_broken = 5;
         return( FALSE );
      }

      loop_index++;
   }

   // The entity list is sorted so we can use a binary search

   long lower_limit = 0;
   long upper_limit = m_Entities.GetUpperBound();

   if ( upper_limit == (-1) )
   {
      rule_that_was_broken = 0;
      return( FALSE );
   }

   long here = upper_limit / 2;

   CString entity_in_list;

   int comparison_result = 0;

   do
   {
      entity_in_list = m_Entities.GetAt( here );

      comparison_result = entity.Compare( entity_in_list );

      if ( comparison_result < 0 )
      {
         upper_limit = here - 1;
      }
      else if ( comparison_result > 0 )
      {
         lower_limit = here + 1;
      }
      else
      {
         return( TRUE );
      }

      // Thanks go to Darin Greaham (greaham@cyberramp.net) for finding
      // where I wasn't calculating a new value for "here". That meant
      // I went into an endless loop.
      // 1998-08-10

      here = ( lower_limit + upper_limit ) / 2;
   }
   while( lower_limit <= upper_limit );

   // Returning FALSE with rule set to zero means it is well-formed
   // but it is not in our database.

   return( FALSE );
}

BOOL CExtensibleMarkupLanguageEntities::Resolve( const CString& entity, CString& text ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::Resolve()" ) );

   ASSERT( m_Entities.GetSize() == m_Values.GetSize() );

   // First, check to see if this is a mathematical entity.

   int entity_length = entity.GetLength();

   if ( entity_length < 3 )
   {
      // We must have a leading & and trailing ; and at least one character in the middle

      WFCTRACE( TEXT( "Entity too short (less than three characters)" ) );
      text.Empty();
      return( FALSE );
   }

   if ( entity.GetAt( 0 ) != TEXT( '&' ) )
   {
      WFCTRACE( TEXT( "First character isn't &" ) );
      return( FALSE );
   }

   if ( entity.GetAt( entity.GetLength() - 1 ) != TEXT( ';' ) )
   {
      WFCTRACE( TEXT( "Last character isn't ;" ) );
      return( FALSE );
   }

   int loop_index = 0;

   if ( entity.GetAt( 1 ) == TEXT( '#' ) )
   {
      // Check to see if mathematical entity is possible

      if ( entity_length == 3 )
      {
         WFCTRACE( TEXT( "No body for the mathematical entity." ) );
         text.Empty();
         return( FALSE );
      }

      // Let's see if it is hexadecimal or decimal

      if ( entity.GetAt( 2 ) == TEXT( 'X' ) )
      {
         WFCTRACE( TEXT( "Ill-formed entity, it uses a capital X instead of x." ) );
         text.Empty();
         return( FALSE );
      }

      TCHAR number_string[ 12 ]; // insanely large buffer

      int number_index = 0;

      long translated_character = 0;

      if ( entity.GetAt( 2 ) == TEXT( 'x' ) )
      {
         // Yup, we be hexadecimal

         loop_index = 0;

         // loop through the digits but skip the trailing ;

         // We use entity_length - 4 because we need to skip the &#x at the beginning and ; at the end

         while( loop_index < ( entity_length - 4 ) )
         {
            if ( _istxdigit( entity.GetAt( loop_index + 3 ) ) == 0 ) // + 3 skips &#x
            {
               WFCTRACEVAL( TEXT( "Ill-formed hexadecimal entity. Character is not a hexadecimal digit at index " ), loop_index + 3 );
               text.Empty();
               return( FALSE );
            }

            if ( number_index > 0 )
            {
               if ( number_index < 11 )
               {
                  number_string[ number_index ] = entity.GetAt( loop_index + 3 );
                  number_index++;
                  number_string[ number_index ] = 0; // NULL terminate the string
               }
            }
            else
            {
               // Skip any leading zeroes
               if ( entity.GetAt( loop_index + 3 ) != TEXT( '0' ) )
               {
                  number_string[ number_index ] = entity.GetAt( loop_index + 3 );
                  number_index++;
                  number_string[ number_index ] = 0; // NULL terminate the string
               }
            }

            loop_index++;
         }

         // number_string now contains the hex number of the character

         TCHAR * stopped_at_address = NULL;

         translated_character = _tcstol( number_string, &stopped_at_address, 16 );

         text = CString( (TCHAR) translated_character );

         return( TRUE );
      }
      else
      {
         // Nope, we must be decimal

         loop_index = 0;

         // We use entity_length - 3 because we need to skip the &# at the beginning and ; at the end
         while( loop_index < ( entity_length - 3 ) )
         {
            if ( _istdigit( entity.GetAt( loop_index + 2 ) ) == 0 ) // + 2 skips &#
            {
               WFCTRACEVAL( TEXT( "Ill-formed decimal entity. Character is not a digit at index " ), loop_index + 2 );
               text.Empty();
               return( FALSE );
            }

            if ( number_index > 0 )
            {
               if ( number_index < 11 )
               {
                  number_string[ number_index ] = entity.GetAt( loop_index + 2 );
                  number_index++;
                  number_string[ number_index ] = 0; // NULL terminate the string
               }
            }
            else
            {
               // Skip any leading zeroes
               if ( entity.GetAt( loop_index + 2 ) != TEXT( '0' ) )
               {
                  number_string[ number_index ] = entity.GetAt( loop_index + 2 );
                  number_index++;
                  number_string[ number_index ] = 0; // NULL terminate the string
               }
            }

            loop_index++;
         }

         // number_string now contains the decimal number of the character

         translated_character = _ttol( number_string );

         text = CString( (TCHAR) translated_character );

         return( TRUE );
      }
   }

   // Welp, it weren't no mathematical entity

   // The entity list is sorted so we can use a binary search

   long lower_limit = 0;
   long upper_limit = m_Entities.GetUpperBound();

   if ( upper_limit == (-1) )
   {
      text.Empty();
      return( FALSE );
   }

   long here = upper_limit / 2;

   CString entity_in_list;

   int comparison_result = 0;

   do
   {
      entity_in_list = m_Entities.GetAt( here );

      comparison_result = entity.Compare( entity_in_list );

      if ( comparison_result < 0 )
      {
         upper_limit = here - 1;
      }
      else if ( comparison_result > 0 )
      {
         lower_limit = here + 1;
      }
      else
      {
         // YIPPEE!! We found that sucker!

         text = m_Values.GetAt( here );

         return( TRUE );
      }

      // Thanks go to Darin Greaham (greaham@cyberramp.net) for finding
      // where I wasn't calculating a new value for "here". That meant
      // I went into an endless loop.
      // 1998-08-10

      here = ( lower_limit + upper_limit ) / 2;
   }
   while( lower_limit <= upper_limit );

   // Entity was not found

   WFCTRACEVAL( TEXT( "Cannot resolve " ), entity );

   text.Empty();

   return( FALSE );
}

CExtensibleMarkupLanguageEntities& CExtensibleMarkupLanguageEntities::operator=( const CExtensibleMarkupLanguageEntities& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageEntities::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CExtensibleMarkupLanguageEntities</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, push technology, source code">
<META name="description" content="The C++ class that handles XML entities.">
</HEAD>

<BODY>

<H1>CExtensibleMarkupLanguageEntities</H1>

$Revision: 21 $

<HR>

<H2>Description</H2>

This class holds the name and value of an XML entity. It is a very
trivial class.

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Copy</B><DD>Copies another <B>CExtensibleMarkupLanguageEntities</B>.

<DT><B>Empty</B><DD>Clears all data members.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CExtensibleMarkupLanguageEntities.cpp $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
#endif
