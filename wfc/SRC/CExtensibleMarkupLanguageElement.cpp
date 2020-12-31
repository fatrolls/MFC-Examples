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
** $Workfile: CExtensibleMarkupLanguageElement.cpp $
** $Revision: 74 $
** $Modtime: 3/12/00 3:49p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

/*
** Thanks go to Mats Johnsson (mats.johnsson@comfact.com) for adding
** humanly readable error messages to the works.
** 1998-08-17
*/

static inline void __replace( CString& string, const CString& what_to_replace, const CString& what_to_replace_it_with )
{
   CString translated_string;

   int string_length = what_to_replace.GetLength();
   int location      = string.Find( what_to_replace );

   while( location >= 0 )
   {
      // Append the data up to the what_to_replace to our translated string

      translated_string += string.Left( location );
      translated_string += what_to_replace_it_with;

      string = string.Right( string.GetLength() - ( location + string_length ) );

      location = string.Find( what_to_replace );
   }

   translated_string += string;
   string = translated_string;
}

// All comparison must be case-sensitive. This is in accordance
// with the term "match" in section 1.2 (Terminology) in the spec.
// Yes, this is vague.

CExtensibleMarkupLanguageElement::CExtensibleMarkupLanguageElement()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::CExtensibleMarkupLanguageElement()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_AbortParsing                = FALSE;
   m_Document                    = reinterpret_cast< CExtensibleMarkupLanguageDocument * >( NULL );
   m_Parent                      = reinterpret_cast< CExtensibleMarkupLanguageElement *  >( NULL );
   m_Type                        = typeUnknown;
   m_IsTagTerminated             = FALSE;
   m_IsAllWhiteSpace             = FALSE;
   m_ShorthandTerminatorDetected = FALSE;
   m_Beginning.Empty();
   m_Ending.Empty();
}

CExtensibleMarkupLanguageElement::CExtensibleMarkupLanguageElement( const CExtensibleMarkupLanguageElement& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::CExtensibleMarkupLanguageElement()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_AbortParsing                = FALSE;
   m_Document                    = reinterpret_cast< CExtensibleMarkupLanguageDocument * >( NULL );
   m_Parent                      = reinterpret_cast< CExtensibleMarkupLanguageElement *  >( NULL );
   m_Type                        = typeUnknown;
   m_IsTagTerminated             = FALSE;
   m_IsAllWhiteSpace             = FALSE;
   m_ShorthandTerminatorDetected = FALSE;
   m_Beginning.Empty();
   m_Ending.Empty();
   Copy( source );
}

CExtensibleMarkupLanguageElement::~CExtensibleMarkupLanguageElement()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::~CExtensibleMarkupLanguageElement()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   m_Document                    = reinterpret_cast< CExtensibleMarkupLanguageDocument * >( NULL );
   m_Parent                      = reinterpret_cast< CExtensibleMarkupLanguageElement *  >( NULL );
   m_Type                        = typeUnknown;
   m_IsTagTerminated             = FALSE;
   m_IsAllWhiteSpace             = FALSE;
   m_ShorthandTerminatorDetected = FALSE;
   m_Beginning.Empty();
   m_Ending.Empty();
}

BOOL CExtensibleMarkupLanguageElement::AddAttribute( const CString& name, const CString& value )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::AddAttribute()" ) );

   CExtensibleMarkupLanguageAttribute * attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( NULL );

   try
   {
      attribute_p = new CExtensibleMarkupLanguageAttribute;
   }
   catch( ... )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( NULL );
   }

   if ( attribute_p == NULL )
   {
      WFCTRACE( TEXT( "Can't allocate memory for a new attribute" ) );
      return( FALSE );
   }

   WFCTRACEVAL( TEXT( "Adding attribute named " ), name );
   WFCTRACEVAL( TEXT( "Value is " ), value );

   attribute_p->Name  = name;
   attribute_p->Value = value;

   // 1998-09-04
   // Thanks go to Mats Johnsson (mats.johnsson@comfact.com)
   // for pointing out that I wasn't normalizing the attribute
   // values according to section 3.3.3 of XML 1.0 Recommendatation
   // dated 1998-02-10

   // First, we need replace and CARRIAGE_RETURN/LINE_FEED pairs
   // with a single space

   CString temporary_string;

   int location_of_character = attribute_p->Value.Find( CARRIAGE_RETURN );

   while( location_of_character != (-1) )
   {
      // We found a carriage return, let's normalize it.

      attribute_p->Value.SetAt( location_of_character, TEXT( ' ' ) );

      if ( location_of_character < ( attribute_p->Value.GetLength() - 1 ) )
      {
         // There's at least one more character after the carriage return

         if ( attribute_p->Value.GetAt( location_of_character + 1 ) == LINE_FEED )
         {
            // Yup. It was one of those danged line feeds. Let's delete it

            temporary_string  = attribute_p->Value.Left( location_of_character );
            temporary_string += attribute_p->Value.Right( attribute_p->Value.GetLength() - ( location_of_character + 1 ) );

            attribute_p->Value = temporary_string;
         }
      }

      location_of_character = attribute_p->Value.Find( CARRIAGE_RETURN );
   }

   // Now that we've gotten rid of all carriage returns (and carriage
   // return/line feed pairs), we need to get rid of all line feeds.

   location_of_character = attribute_p->Value.Find( LINE_FEED );

   while( location_of_character != (-1) )
   {
      // We found a carriage return, let's normalize it.

      attribute_p->Value.SetAt( location_of_character, TEXT( ' ' ) );
      location_of_character = attribute_p->Value.Find( LINE_FEED );
   }

   // And last but not least, we need to get rid of all TAB characters

   location_of_character = attribute_p->Value.Find( 0x09 );

   while( location_of_character != (-1) )
   {
      // We found a carriage return, let's normalize it.

      attribute_p->Value.SetAt( location_of_character, TEXT( ' ' ) );
      location_of_character = attribute_p->Value.Find( 0x09 );
   }

   // 1999-06-21
   // Fixed a couple of (unreported, I found them myself) bugs dealing with
   // well formedness constraints in regards to attributes

   if ( GetAttributeByName( attribute_p->Name ) != NULL )
   {
      CString parsing_error_message;

      parsing_error_message.Format( TEXT( "Attributes must be unique (Rule 40). An attribute named \"%s\" was repeated." ),
                                    (LPCTSTR) attribute_p->Name );

      m_ReportParsingError( parsing_error_message );

      delete attribute_p;
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( NULL );

      return( FALSE );
   }

   if ( attribute_p->Value.Find( TEXT( '<' ) ) != (-1) )
   {
      CString parsing_error_message;

      parsing_error_message.Format( TEXT( "Attribute values cannot contain a '<' (Rule 41). Offending attribute is named named \"%s\"" ),
                                    (LPCTSTR) attribute_p->Name );
      m_ReportParsingError( parsing_error_message );

      delete attribute_p;
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( NULL );

      return( FALSE );
   }

   m_Attributes.Add( attribute_p );

   return( TRUE );
}

void CExtensibleMarkupLanguageElement::AddChild( CExtensibleMarkupLanguageElement * item_p, DWORD insert_at )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::AddChild()" ) );
   ASSERT( item_p != NULL );
   ASSERT( item_p != this );

   if ( item_p == this )
   {
      // We can't be our own child
      return;
   }

   if ( item_p != NULL )
   {
      try
      {
         // First, let's make sure we aren't already in there

         DWORD loop_index        = 0;
         DWORD number_of_entries = m_Children.GetSize();

         while( loop_index < number_of_entries )
         {
            if ( m_Children.GetAt( loop_index ) == item_p )
            {
               WFCTRACE( TEXT( "Element is already a child." ) );
               // the item is already in the list
               return;
            }

            loop_index++;
         }

         // If we get here, it means the item_p ain't already in the list

         item_p->SetDocument( m_Document );
         item_p->m_Parent = this;

         // 2000-03-12
         // New functionality as suggested by Perry Rapp, we now have
         // the ability to add a child at a specific index.

         if ( insert_at >= number_of_entries )
         {
            m_Children.Add( item_p );
         }
         else
         {
            m_Children.InsertAt( insert_at, item_p );
         }
      }
      catch( ... )
      {
      }
   }
}

BOOL CExtensibleMarkupLanguageElement::AddText( const CString& text_segment )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::AddText()" ) );

   // Create a child text segment thingy

   CExtensibleMarkupLanguageElement * child_element_p = NULL;
   child_element_p = NewElement( this, typeTextSegment, m_Document );

   if ( child_element_p == NULL )
   {
      return( FALSE );
   }

   // Here's where we encode the default entities

   if ( text_segment.FindOneOf( TEXT( "&\"<>'" ) ) == (-1) )
   {
      // Nothing to translate
      child_element_p->SetContents( text_segment );
   }
   else
   {
      CString encoded_entity_string( text_segment );

      __replace( encoded_entity_string, TEXT( "&"  ), TEXT( "&amp;"  ) );
      __replace( encoded_entity_string, TEXT( ">"  ), TEXT( "&gt;"   ) );
      __replace( encoded_entity_string, TEXT( "<"  ), TEXT( "&lt;"   ) );
      __replace( encoded_entity_string, TEXT( "\"" ), TEXT( "&quot;" ) );
      __replace( encoded_entity_string, TEXT( "'"  ), TEXT( "&apos;" ) );

      child_element_p->SetContents( encoded_entity_string );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageElement::Copy( const CExtensibleMarkupLanguageElement& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::Copy()" ) );

   Empty();

   m_Tag                         = source.m_Tag;
   m_Contents                    = source.m_Contents;
   m_ShorthandTerminatorDetected = source.m_ShorthandTerminatorDetected;
   m_IsAllWhiteSpace             = source.m_IsAllWhiteSpace;
   m_IsTagTerminated             = source.m_IsTagTerminated;
   m_Type                        = source.m_Type;

   int loop_index         = 0;
   int number_of_elements = source.m_Attributes.GetSize();

   // Let's copy the attributes

   CExtensibleMarkupLanguageAttribute * this_attribute_p = NULL;
   CExtensibleMarkupLanguageAttribute * that_attribute_p = NULL;

   while( loop_index < number_of_elements )
   {
      that_attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( source.m_Attributes.GetAt( loop_index ) );

      if ( that_attribute_p != NULL )
      {
         try
         {
            this_attribute_p = new CExtensibleMarkupLanguageAttribute;
         }
         catch( ... )
         {
            this_attribute_p = NULL;
         }

         if ( this_attribute_p == NULL )
         {
            WFCTRACE( TEXT( "Can't allocate memory for a new attribute" ) );
            Empty();
            return;
         }

         this_attribute_p->Copy( *that_attribute_p );

         m_Attributes.Add( this_attribute_p );
         this_attribute_p = NULL;
      }

      loop_index++;
   }

   // Now let's copy the children

   loop_index         = 0;
   number_of_elements = source.m_Children.GetSize();

   CExtensibleMarkupLanguageElement * this_item_p = NULL;
   CExtensibleMarkupLanguageElement * that_item_p = NULL;

   while( loop_index < number_of_elements )
   {
      that_item_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( source.m_Children.GetAt( loop_index ) );

      if ( that_item_p != NULL )
      {
         try
         {
            this_item_p = NewElement( this );
         }
         catch( ... )
         {
            this_item_p = NULL;
         }

         if ( this_item_p == NULL )
         {
            WFCTRACE( TEXT( "Can't allocate memory for a new child item" ) );
            Empty();
            return;
         }

         this_item_p->Copy( *that_item_p );

         AddChild( this_item_p );
         this_item_p = NULL;
      }

      loop_index++;
   }
}

DWORD CExtensibleMarkupLanguageElement::CountChildren( const CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::CountChildren()" ) );

   if ( name.GetLength() == 0 )
   {
      return( 0 );
   }

   TCHAR parent_child_separator_character = TEXT( '.' );

   if ( m_Document != NULL )
   {
      parent_child_separator_character = m_Document->GetParentChildSeparatorCharacter();
   }

   int loop_index = 0;

   if ( name.Find( parent_child_separator_character ) == (-1) )
   {
      // Count the elements at this level

      // Many thanks go to Johann Plank (johann.plank@atabb.mail.abb.com)
      // for finding a hole in my code. I forgot to write this section!!!

      DWORD enumerator = 0;

      CExtensibleMarkupLanguageElement * child_p = NULL;

      if ( EnumerateChildren( enumerator ) != FALSE )
      {
         DWORD number_of_children = 0;

         while( GetNextChild( enumerator, child_p ) != FALSE )
         {
            if ( name.Compare( child_p->m_Tag ) == 0 )
            {
               number_of_children++;
            }
         }

         return( number_of_children );
      }

      return( 0 );
   }
   else
   {
      // Find the last . in the name, we know there's one in there somewhere

      int index_of_character = 0;

      loop_index = name.GetLength() - 1;

      while( loop_index >= 0 )
      {
         if ( name.GetAt( loop_index ) == parent_child_separator_character )
         {
            index_of_character = loop_index;
            loop_index = 0; // exit_loop
         }

         loop_index--;
      }

      CString parent_name;
      CString child_name;

      parent_name = name.Left( index_of_character );
      child_name  = name.Right( name.GetLength() - ( index_of_character + 1 ) );

      WFCTRACEVAL( TEXT( "parent_name is " ), parent_name );
      WFCTRACEVAL( TEXT( "child_name is " ), child_name );

      // Now that we have the parent and child names, we need
      // to massage the child_name so it doesn't have any [ or ] in it

      index_of_character = child_name.Find( TEXT( '(' ) );

      if ( index_of_character != (-1) )
      {
         // Yup, we've got us a [

         child_name = child_name.Left( index_of_character );
      }

      // Now let's find any )'s (which may have preceeded (

      index_of_character = child_name.Find( TEXT( ')' ) );

      if ( index_of_character != (-1) )
      {
         // Yup, we've got us a (

         child_name = child_name.Left( index_of_character );
      }

      // We may have chopped off the entire string

      if ( child_name.GetLength() == 0 )
      {
         WFCTRACE( TEXT( "Trimmed everything off" ) );
         return( 0 );
      }

      // Whew! OK, now we need to get that parent

      CExtensibleMarkupLanguageElement * element_p = NULL;

      element_p = GetChild( parent_name );

      if ( element_p == NULL )
      {
         WFCTRACE( TEXT( "Can't find parent" ) );
         return( 0 );
      }

      DWORD enumerator = 0;

      CExtensibleMarkupLanguageElement * child_p = NULL;

      if ( element_p->EnumerateChildren( enumerator ) != FALSE )
      {
         DWORD number_of_children = 0;

         while( element_p->GetNextChild( enumerator, child_p ) != FALSE )
         {
            if ( child_name.Compare( child_p->m_Tag ) == 0 )
            {
               number_of_children++;
            }
         }

         return( number_of_children );
      }
      else
      {
         WFCTRACE( TEXT( "No children to enumerate" ) );
         return( 0 );
      }
   }

   return( 0 );
}

void CExtensibleMarkupLanguageElement::DeleteElement( CExtensibleMarkupLanguageElement * element_p )
{
   // This destroys the element in whatever manor is appropriate for how NewElement()
   // created it.

   delete element_p;
}

void CExtensibleMarkupLanguageElement::DestroyAttributeByName( const CString& name )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::DestroyAttributeByName()" ) );

   CExtensibleMarkupLanguageAttribute * attribute_p = (CExtensibleMarkupLanguageAttribute *) NULL;

   int loop_index           = 0;
   int number_of_attributes = m_Attributes.GetSize();

   while( loop_index < number_of_attributes )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( loop_index ) );

      if ( attribute_p != NULL )
      {
         if ( attribute_p->Name.Compare( name ) == 0 )
         {
            // We found one
            m_Attributes.RemoveAt( loop_index );

            delete attribute_p;
            loop_index--;
            number_of_attributes--;
         }
      }

      loop_index++;
   }
}

void CExtensibleMarkupLanguageElement::DestroyAttributeByValue( const CString& value )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::DestroyAttributeByValue()" ) );

   CExtensibleMarkupLanguageAttribute * attribute_p = NULL;

   int loop_index           = 0;
   int number_of_attributes = m_Attributes.GetSize();

   while( loop_index < number_of_attributes )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( loop_index ) );

      if ( attribute_p != NULL )
      {
         if ( attribute_p->Value.Compare( value ) == 0 )
         {
            // We found one
            m_Attributes.RemoveAt( loop_index );

            delete attribute_p;
            loop_index--;
            number_of_attributes--;
         }
      }

      loop_index++;
   }
}

void CExtensibleMarkupLanguageElement::DestroyAttributes( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::DestroyAttributes()" ) );

   CExtensibleMarkupLanguageAttribute * attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( NULL );

   int loop_index           = 0;
   int number_of_attributes = m_Attributes.GetSize();

   while( loop_index < number_of_attributes )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( loop_index ) );

      m_Attributes.SetAt( loop_index, NULL );
      delete attribute_p;

      loop_index++;
   }

   m_Attributes.RemoveAll();
}

void CExtensibleMarkupLanguageElement::DestroyChildren( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::DestroyChildren()" ) );

   CExtensibleMarkupLanguageElement * item_p = NULL;

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   while( loop_index < number_of_children )
   {
      item_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( loop_index ) );
      m_Children.SetAt( loop_index, NULL );

      DeleteElement( item_p );

      loop_index++;
   }

   m_Children.RemoveAll();
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CExtensibleMarkupLanguageElement::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CExtensibleMarkupLanguageElement at " ) << reinterpret_cast< const void * >( this ) << TEXT( "\n{\n" );

   dump_context << TEXT( "   m_Beginning is\n" );
   dump_context << TEXT( "   {\n" );
   dump_context << TEXT( "      Byte Index  " ) << m_Beginning.GetIndex()      << TEXT( "\n" );
   dump_context << TEXT( "      Line Number " ) << m_Beginning.GetLineNumber() << TEXT( "\n" );
   dump_context << TEXT( "      Column      " ) << m_Beginning.GetLineIndex()  << TEXT( "\n" );
   dump_context << TEXT( "   }\n" );

   dump_context << TEXT( "   m_Ending is\n" );
   dump_context << TEXT( "   {\n" );
   dump_context << TEXT( "      Byte Index  " ) << m_Ending.GetIndex()      << TEXT( "\n" );
   dump_context << TEXT( "      Line Number " ) << m_Ending.GetLineNumber() << TEXT( "\n" );
   dump_context << TEXT( "      Column      " ) << m_Ending.GetLineIndex()  << TEXT( "\n" );
   dump_context << TEXT( "   }\n" );

   dump_context << TEXT( "   m_IsTagTerminated is " );

   if ( m_IsTagTerminated == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_IsAllWhiteSpace is " );

   if ( m_IsAllWhiteSpace == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_ShorthandTerminatorDetected is " );

   if ( m_ShorthandTerminatorDetected == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_Tag is      \"" ) << m_Tag      << TEXT( "\"\n" );
   dump_context << TEXT( "   m_Contents is \"" ) << m_Contents << TEXT( "\"\n" );

   dump_context << TEXT( "   m_Type is " );

   switch( m_Type )
   {
      case typeUnknown:

         dump_context << TEXT( "typeUnknown\n" );
         break;

      case typeProcessingInstruction:

         dump_context << TEXT( "typeProcessingInstruction\n" );
         break;

      case typeComment:

         dump_context << TEXT( "typeComment\n" );
         break;

      case typeCharacterData:

         dump_context << TEXT( "typeCharacterData\n" );
         break;

      case typeElement:

         dump_context << TEXT( "typeElement\n" );
         break;

      case typeTextSegment:

         dump_context << TEXT( "typeTextSegment\n" );
         break;

      case typeMetaData:

         dump_context << TEXT( "typeMetaData\n" );
         break;

      default:

         dump_context << TEXT( "an invalid value of " ) << m_Type << TEXT( "\n" );
         break;
   }

   dump_context << TEXT( "   m_Parent is " ) << reinterpret_cast< VOID * >( m_Parent ) << TEXT( "\n" );
   dump_context << TEXT( "   m_Children is " );
   m_Children.Dump( dump_context );
   dump_context << TEXT( "   m_Attributes is " );
   m_Attributes.Dump( dump_context );

   int loop_index         = 0;
   int number_of_elements = m_Attributes.GetSize();

   CExtensibleMarkupLanguageAttribute * attribute_p = NULL;

   while( loop_index < number_of_elements )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( loop_index ) );

      if ( attribute_p != NULL )
      {
         attribute_p->Dump( dump_context );
      }

      loop_index++;
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CExtensibleMarkupLanguageElement::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::Empty()" ) );

   m_IsTagTerminated = FALSE;
   DestroyChildren();
   DestroyAttributes();
   m_Tag.Empty();
   m_Contents.Empty();
}

BOOL CExtensibleMarkupLanguageElement::EnumerateAttributes( DWORD& enumerator ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::EnumerateAttributes()" ) );

   enumerator = 0;

   if ( m_Attributes.GetSize() == 0 )
   {
      // There ain't no attributes to enumerate

      return( FALSE );
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::EnumerateChildren( DWORD& enumerator ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::EnumerateChildren()" ) );

   enumerator = 0;

   if ( m_Children.GetSize() == 0 )
   {
      // There ain't no children to enumerate

      return( FALSE );
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::GetAbortParsing( void ) const
{
   return( ( m_AbortParsing == FALSE ) ? FALSE : TRUE );
}

BOOL CExtensibleMarkupLanguageElement::GetAttributeByName( CExtensibleMarkupLanguageAttribute& attribute ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetAttributeByName()" ) );

   DWORD enumerator = 0;

   if ( EnumerateAttributes( enumerator ) != FALSE )
   {
      CExtensibleMarkupLanguageAttribute * this_attribute_p = NULL;

      while( GetNextAttribute( enumerator, this_attribute_p ) != FALSE )
      {
         if ( this_attribute_p != NULL )
         {
            if ( attribute.Name.Compare( this_attribute_p->Name ) == 0 )
            {
               attribute.Copy( *this_attribute_p );
               return( TRUE );
            }
         }
      }
   }

   return( FALSE );
}

// Suggested by Mats Johnsson (mats.johnsson@comfact.com)

CExtensibleMarkupLanguageAttribute * CExtensibleMarkupLanguageElement::GetAttributeByName( const CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetAttributeByName( name )" ) );

   DWORD enumerator = 0;

   if ( EnumerateAttributes( enumerator ) != FALSE )
   {
      CExtensibleMarkupLanguageAttribute * this_attribute_p = NULL;

      while( GetNextAttribute( enumerator, this_attribute_p ) != FALSE )
      {
         if ( this_attribute_p != NULL )
         {
            if ( name.Compare( this_attribute_p->Name ) == 0 )
            {
               return( this_attribute_p );
            }
         }
      }
   }

   return( NULL );
}

BOOL CExtensibleMarkupLanguageElement::GetAttributeByName( const CString& name, CString& value ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetAttributeByName( CString )" ) );

   // Always start from a known state
   value.Empty();

   DWORD enumerator = 0;

   if ( EnumerateAttributes( enumerator ) != FALSE )
   {
      CExtensibleMarkupLanguageAttribute * this_attribute_p = NULL;

      while( GetNextAttribute( enumerator, this_attribute_p ) != FALSE )
      {
         if ( this_attribute_p != NULL )
         {
            if ( name.Compare( this_attribute_p->Name ) == 0 )
            {
               value = this_attribute_p->Value;

               // Now that we have the attribute value, we need to resolve any
               // entities in it. This according to section 3.3.3 of
               // the XML 1.0 recommendation (REC-xml-19980210)

               m_ResolveEntities( value );

               return( TRUE );
            }
         }
      }
   }

   return( FALSE );
}

BOOL CExtensibleMarkupLanguageElement::GetAttributeByValue( CExtensibleMarkupLanguageAttribute& attribute ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetAttributeByValue()" ) );

   DWORD enumerator = 0;

   if ( EnumerateAttributes( enumerator ) != FALSE )
   {
      CExtensibleMarkupLanguageAttribute * this_attribute_p = NULL;

      while( GetNextAttribute( enumerator, this_attribute_p ) != FALSE )
      {
         if ( this_attribute_p != NULL )
         {
            if ( attribute.Value.Compare( this_attribute_p->Value ) == 0 )
            {
               attribute.Copy( *this_attribute_p );
               return( TRUE );
            }
         }
      }
   }

   return( FALSE );
}

void CExtensibleMarkupLanguageElement::GetBeginning( CParsePoint& parse_point ) const
{
   parse_point.Copy( m_Beginning );
}

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageElement::GetChild( const CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetChild()" ) );
   WFCTRACEVAL( TEXT( "Searching for " ), name );

   CString parent_name;
   CString child_name;

   DWORD desired_instance_number = 0;

   if ( m_ParseElementName( name, parent_name, desired_instance_number, child_name ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't parse element name " ), name );
      return( 0 );
   }

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   WFCTRACEVAL( TEXT( "desired parent_name is " ), parent_name );
   WFCTRACEVAL( TEXT( "desired_instance_number is " ), desired_instance_number );

   DWORD this_instance_number = 0;

   CExtensibleMarkupLanguageElement * element_p = NULL;

   while( loop_index < number_of_children )
   {
      element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( loop_index ) );

      if ( element_p != NULL )
      {
         if ( parent_name.Compare( element_p->m_Tag ) == 0 )
         {
            if ( this_instance_number == desired_instance_number )
            {
               // YIPPEE!! We found our instance! Let's see if this is the
               // ultimate element we're searching for or if we are a parent
               // searching for a child

               if ( child_name.GetLength() == 0 )
               {
                  WFCTRACEVAL( TEXT( "We are the one! " ), parent_name );
                  // We are the one!
                  return( element_p );
               }
               else
               {
                  WFCTRACEVAL( TEXT( "Contiuing the search " ), parent_name );
                  // Nope, we are not the Key Master, continue the search
                  // further down the tree

                  return( element_p->GetChild( child_name ) );
               }
            }
            else
            {
               WFCTRACE( TEXT( "Wrong instance" ) );
            }

            this_instance_number++;
         }
      }
      else
      {
         WFCTRACE( TEXT( "Element is NULL!" ) );
      }

      loop_index++;
   }
   
   return( NULL );
}

void CExtensibleMarkupLanguageElement::GetCompleteName( CString& name ) const
{
   name.Empty();

   if ( IsRoot() == TRUE || m_Tag.GetLength() == 0 )
   {
      // The root is nameless
      return;
   }

   GetName( name );

   CString parent_name;

   TCHAR parent_child_separator_character = TEXT( '.' );

   if ( m_Document != NULL )
   {
      parent_child_separator_character = m_Document->GetParentChildSeparatorCharacter();
   }

   CExtensibleMarkupLanguageElement * parent_element_p = GetParent();

   while( parent_element_p != NULL )
   {
      parent_element_p->GetName( parent_name );

      if ( parent_element_p->IsRoot() == TRUE || parent_name.GetLength() == 0 )
      {
         return;
      }

      parent_name += parent_child_separator_character;
      parent_name += name;
      name = parent_name;

      parent_element_p = parent_element_p->GetParent();
   }
}

void CExtensibleMarkupLanguageElement::GetContents( CString& contents ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetContents()" ) );
   contents = m_Contents;
}

CExtensibleMarkupLanguageDocument * CExtensibleMarkupLanguageElement::GetDocument( void ) const
{
   return( m_Document );
}

void CExtensibleMarkupLanguageElement::GetEnding( CParsePoint& parse_point ) const
{
   parse_point.Copy( m_Ending );
}

void CExtensibleMarkupLanguageElement::GetName( CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetName()" ) );

   name.Empty();

   if ( IsRoot() == TRUE || m_Tag.GetLength() == 0 )
   {
      // The root is nameless
      return;
   }

   GetTag( name );

   // Now let's find which instance we are

   CExtensibleMarkupLanguageElement * parent_element_p = GetParent();

   DWORD enumerator      = 0;
   DWORD instance_number = 0;

   if ( parent_element_p->EnumerateChildren( enumerator ) == TRUE )
   {
      CString child_tag_name;

      CExtensibleMarkupLanguageElement * child_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

      while( parent_element_p->GetNextChild( enumerator, child_element_p ) != FALSE )
      {
         if ( child_element_p == this )
         {
            // We've found ourselves

            if ( instance_number > 0 )
            {
               child_tag_name.Format( TEXT( "(%lu)" ), (unsigned long) instance_number );
               name += child_tag_name;
               return;
            }
         }

         // Let's see if this is an instance of us

         child_element_p->GetTag( child_tag_name );

         if ( name.Compare( child_tag_name ) == 0 )
         {
            // We have the same name, let's increment out count
            instance_number++;
         }
      }
   }
}

BOOL CExtensibleMarkupLanguageElement::GetNextAttribute( DWORD& enumerator, CExtensibleMarkupLanguageAttribute*& attribute_p ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetNextAttribute()" ) );

   if ( m_Attributes.GetSize() < 1 )
   {
      attribute_p = NULL;
      return( FALSE );
   }

   if ( enumerator > static_cast< DWORD >( m_Attributes.GetUpperBound() ) )
   {
      attribute_p = NULL;
      return( FALSE );
   }

   attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( enumerator ) );

   enumerator++;

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::GetNextChild( DWORD& enumerator, CExtensibleMarkupLanguageElement*& item_p ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetNextChild()" ) );

   // 1999-06-07
   // Thanks go to Ryan Swan (rswan@nj.navisys.com) for finding a bug here.
   // If m_Children is empty, I thought there was 4 billion children. DOH!

   if ( m_Children.GetSize() < 1 )
   {
      item_p = NULL;
      return( FALSE );
   }

   if ( enumerator > static_cast< DWORD >( m_Children.GetUpperBound() ) )
   {
      item_p = NULL;
      return( FALSE );
   }

   item_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( enumerator ) );

   enumerator++;

   return( TRUE );
}

DWORD CExtensibleMarkupLanguageElement::GetNumberOfAttributes( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetNumberOfAttributes()" ) );
   return( m_Attributes.GetSize() );
}

DWORD CExtensibleMarkupLanguageElement::GetNumberOfChildren( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetNumberOfChildren()" ) );
   return( m_Children.GetSize() );
}

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageElement::GetParent( void ) const
{
   return( m_Parent );
}

// Suggested by Mats Johnsson (mats.johnsson@comfact.com)

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageElement::GetParent( const CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetParent( name )" ) );
   WFCTRACEVAL( TEXT( "Searching for " ), name );

   if ( m_Parent != NULL )
   {
      if ( name.Compare( m_Parent->m_Tag ) == 0 )
      {
         return( m_Parent );
      }
      else
      {
         WFCTRACEVAL( TEXT( "Continuing the search " ), name );
         return( m_Parent->GetParent( name ) );
      }
   }

   return( NULL );
}

void CExtensibleMarkupLanguageElement::GetTag( CString& tag ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetTag()" ) );
   tag = m_Tag;
}

void CExtensibleMarkupLanguageElement::GetText( CString& text ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetText()" ) );
   WFCTRACEVAL( TEXT( "Tag is " ), m_Tag );

   // Always start with an empty string

   text.Empty();

   // Retrieves the contents and text segments

   if ( m_Document->GetIgnoreWhiteSpace() != FALSE )
   {
      // We should ignore white space

      if ( m_IsAllWhiteSpace == FALSE )
      {
         text = m_Contents;
      }
   }
   else
   {
      // We shouldn't ignore white space
      text = m_Contents;
   }

   WFCTRACEVAL( TEXT( "text is now " ), text );

   // Here's where it begins to get fun. If we are
   // a textSegment, then we need to translate the entities.

   if ( m_Type == typeTextSegment )
   {
      m_ResolveEntities( text );
   }

   // Now get all of the text of our children

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   CExtensibleMarkupLanguageElement * element_p = NULL;

   CString text_segment;

   while( loop_index < number_of_children )
   {
      element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( loop_index ) );

      if ( element_p != NULL )
      {
         element_p->GetText( text_segment );
         text += text_segment;
      }

      loop_index++;
   }
}

DWORD CExtensibleMarkupLanguageElement::GetTotalNumberOfChildren( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::GetTotalNumberOfChildren()" ) );

   DWORD return_value = 0;

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   CExtensibleMarkupLanguageElement * element_p = NULL;

   while( loop_index < number_of_children )
   {
      element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( loop_index ) );

      if ( element_p != NULL )
      {
         return_value += element_p->GetTotalNumberOfChildren();
      }

      return_value++; // Don't forget to count this child

      loop_index++;
   }

   return( return_value );
}

DWORD CExtensibleMarkupLanguageElement::GetType( void ) const
{
   return( m_Type );
}

BOOL CExtensibleMarkupLanguageElement::IsAllWhiteSpace( void ) const
{
   return( ( m_IsAllWhiteSpace == FALSE ) ? FALSE : TRUE );
}

BOOL CExtensibleMarkupLanguageElement::IsRoot( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::IsRoot()" ) );

   // If we have no parent, we must be the root

   if ( m_Parent == NULL )
   {
      return( TRUE );
   }

   return( FALSE );
}

void CExtensibleMarkupLanguageElement::m_AddCharacterToOutput( DWORD character, DWORD options, CByteArray& output ) const
{
   if ( options & WFC_XML_WRITE_AS_ASCII )
   {
#if defined( _DEBUG )
      if ( character > 255 )
      {
         ASSERT( FALSE );
      }
#endif // _DEBUG
      output.Add( LOBYTE( LOWORD( character ) ) );
   }
   else if ( options & WFC_XML_WRITE_AS_UNICODE )
   {
      if ( options & WFC_XML_WRITE_AS_BIG_ENDIAN )
      {
         output.Add( HIBYTE( LOWORD( character ) ) );
         output.Add( LOBYTE( LOWORD( character ) ) );
      }
      else
      {
         output.Add( LOBYTE( LOWORD( character ) ) );
         output.Add( HIBYTE( LOWORD( character ) ) );
      }
   }
   else if ( options & WFC_XML_WRITE_AS_UCS4 )
   {
      if ( options & WFC_XML_WRITE_AS_BIG_ENDIAN )
      {
         // 1234
         output.Add( HIBYTE( HIWORD( character ) ) );
         output.Add( LOBYTE( HIWORD( character ) ) );
         output.Add( HIBYTE( LOWORD( character ) ) );
         output.Add( LOBYTE( LOWORD( character ) ) );
      }
      else
      {
         // 4321
         output.Add( LOBYTE( LOWORD( character ) ) );
         output.Add( HIBYTE( LOWORD( character ) ) );
         output.Add( LOBYTE( HIWORD( character ) ) );
         output.Add( HIBYTE( HIWORD( character ) ) );
      }
   }
   else if ( options & WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143 )
   {
      output.Add( LOBYTE( HIWORD( character ) ) );
      output.Add( HIBYTE( HIWORD( character ) ) );
      output.Add( LOBYTE( LOWORD( character ) ) );
      output.Add( HIBYTE( LOWORD( character ) ) );
   }
   else if ( options & WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412 )
   {
      output.Add( HIBYTE( LOWORD( character ) ) );
      output.Add( LOBYTE( LOWORD( character ) ) );
      output.Add( HIBYTE( HIWORD( character ) ) );
      output.Add( LOBYTE( HIWORD( character ) ) );
   }
   else if ( options & WFC_XML_WRITE_AS_UTF8 )
   {
      // This is by far the slowest method

      ASSERT( character <= 0xFFFF ); // Make sure it will fit

      WCHAR string[ 2 ];

      string[ 0 ] = (WCHAR) character;
      string[ 1 ] = 0x00;

      BYTE output_buffer[ 32 ];

      int number_of_bytes_written = 0;
      
      if ( m_Document != NULL )
      {
         WideCharToMultiByte( m_Document->GetConversionCodePage(), 0, string, 1, (char *) output_buffer, 31, NULL, NULL );
      }
      else
      {
         // Hack for WIndows 95 which doesn't support CP_UTF8
         WideCharToMultiByte( CP_ACP, 0, string, 1, (char *) output_buffer, 31, NULL, NULL );
      }

      if ( number_of_bytes_written > 0 )
      {
         int loop_index = 0;

         while( loop_index < number_of_bytes_written )
         {
            output.Add( output_buffer[ loop_index ] );
            loop_index++;
         }
      }
      else
      {
         ASSERT( FALSE );
      }
   }
}

void CExtensibleMarkupLanguageElement::m_AddIndentation( CByteArray& bytes ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_AddIndentation()" ) );

   DWORD write_options = WFC_XML_WRITE_AS_ASCII;

   if ( m_Document != NULL )
   {
      write_options = m_Document->GetWriteOptions();
   }

   BOOL automatically_indent = FALSE;

   DWORD indentation_level = 0;
   DWORD indent_by         = 0;

   try
   {
      m_Document->GetAutomaticIndentation( automatically_indent, indentation_level, indent_by );

      if ( automatically_indent != FALSE )
      {
         m_AddCharacterToOutput( CARRIAGE_RETURN, write_options,  bytes );
         m_AddCharacterToOutput( LINE_FEED,       write_options, bytes );

         indent_by = 0;

         CByteArray indentation;

         while( indent_by < indentation_level )
         {
            m_AddCharacterToOutput( TEXT( ' ' ), write_options, bytes );
            indent_by++;
         }
      }
   }
   catch( ... )
   {
   }
}

void CExtensibleMarkupLanguageElement::m_AppendAttributes( CByteArray& data ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_AppendAttributes()" ) );

   int attribute_index      = 0;
   int number_of_attributes = 0;
   int string_index         = 0;
   int string_length        = 0;

   DWORD write_options = WFC_XML_WRITE_AS_ASCII;

   if ( m_Document != NULL )
   {
      write_options = m_Document->GetWriteOptions();
   }

   number_of_attributes = m_Attributes.GetSize();

   CExtensibleMarkupLanguageAttribute * attribute_p = NULL;

   while( attribute_index < number_of_attributes )
   {
      attribute_p = reinterpret_cast< CExtensibleMarkupLanguageAttribute * >( m_Attributes.GetAt( attribute_index ) );

      if ( attribute_p != NULL )
      {
         string_length = attribute_p->Name.GetLength();

         string_index = 0;

         if ( string_length > 0 )
         {
            m_AddCharacterToOutput( TEXT( ' ' ), write_options, data );
         }

         while( string_index < string_length )
         {
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( attribute_p->Name.GetAt( string_index ) ) ), write_options, data );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( attribute_p->Name.GetAt( string_index ) ), write_options, data );
#endif
            string_index++;
         }

         m_AddCharacterToOutput( TEXT( '=' ), write_options, data );

         BOOL we_need_single_quotes = FALSE;

         if ( attribute_p->Value.Find( TEXT( "\"" ) ) == (-1) )
         {
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, data );
         }
         else
         {
            we_need_single_quotes = TRUE;
            m_AddCharacterToOutput( TEXT( '\'' ), write_options, data );
         }

         string_length = attribute_p->Value.GetLength();

         string_index = 0;

         while( string_index < string_length )
         {
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( attribute_p->Value.GetAt( string_index ) ) ), write_options, data );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( attribute_p->Value.GetAt( string_index ) ), write_options, data );
#endif
            string_index++;
         }

         if ( we_need_single_quotes == FALSE )
         {
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, data );
         }
         else
         {
            m_AddCharacterToOutput( TEXT( '\'' ), write_options, data );
         }
      }

      attribute_index++;
   }
}

void CExtensibleMarkupLanguageElement::m_AppendChildren( CByteArray& data ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_AppendChildren()" ) );

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   CExtensibleMarkupLanguageElement * element_p = NULL;

   while( loop_index < number_of_children )
   {
      element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( loop_index ) );

      if ( element_p != NULL )
      {
         element_p->WriteTo( data );
      }

      loop_index++;
   }
}

void CExtensibleMarkupLanguageElement::m_DecrementIndentation( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_DecrementIndentation()" ) );

   BOOL automatically_indent = FALSE;

   DWORD indentation_level = 0;
   DWORD indent_by         = 0;

   try
   {
      m_Document->GetAutomaticIndentation( automatically_indent, indentation_level, indent_by );

      if ( automatically_indent != FALSE )
      {
         indentation_level -= indent_by;

         m_Document->SetAutomaticIndentation( automatically_indent, indentation_level, indent_by );
      }
   }
   catch( ... )
   {
      return;
   }
}

void CExtensibleMarkupLanguageElement::m_GetTag( const CString& xml_data, CString& tag )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_GetTag()" ) );

   tag.Empty();

   int loop_index      = 0;
   int xml_data_length = xml_data.GetLength();

   while( loop_index < xml_data_length )
   {
      if ( xml_data.GetAt( loop_index ) == TEXT( '<' ) )
      {
         loop_index++;

         while( loop_index < xml_data_length )
         {
            if ( xml_data.GetAt( loop_index ) == TEXT( '>' ) )
            {
               return;
            }

            tag += xml_data.GetAt( loop_index );

            loop_index++;
         }
      }

      loop_index++;
   }

   // if we get here, it means something is wrong (i.e. no closing > character )

   tag.Empty();
}

void CExtensibleMarkupLanguageElement::m_IncrementIndentation( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_IncrementIndentation()" ) );

   BOOL automatically_indent = FALSE;

   DWORD indentation_level = 0;
   DWORD indent_by         = 0;

   try
   {
      m_Document->GetAutomaticIndentation( automatically_indent, indentation_level, indent_by );

      if ( automatically_indent != FALSE )
      {
         indentation_level += indent_by;

         m_Document->SetAutomaticIndentation( automatically_indent, indentation_level, indent_by );
      }
   }
   catch( ... )
   {
      return;
   }
}

void CExtensibleMarkupLanguageElement::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_Initialize()" ) );
   m_Parent = NULL;
}

BOOL CExtensibleMarkupLanguageElement::m_ParseCDATASection( const CString& tag, const CDataParser& parser )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseCDATASection()" ) );

   // When we get here, we should have "<![CDATA[" some characters and a ">" in the tag parameter.
   // the trailing ">" may or may not be part of the terminator for "<![CDATA["

   // CDATA sections are a hack. What rookie garbage. They are delimited by ]]>
   // we must assume that ]]> will escape ]]> occuring in the data (although
   // the XML specification doesn't clearly state this if it states it all).

   // We need the CDataParser because triggering on > (which caused m_ParseTag to
   // be called) may have been seen in the CDATA section

   // We should be sitting on a CDATA section now.

   if ( tag.GetLength() < 10 )
   {
      WFCTRACEVAL( TEXT( "Length of tag is too short, length is " ), tag.GetLength() );
      return( FALSE );
   }

   // We have to do this checking all over again because we are a virtual function.
   // We cannot trust that someone who inherited from CExtensibleMarkupLanguageElement
   // knows what they are doing.

   DWORD character = 0x00;

   CString temp_string;

   temp_string = tag.Left( 9 );

   if ( temp_string.Compare( TEXT( "<![CDATA[" ) ) != 0 )
   {
      WFCTRACEVAL( TEXT( "tag does not begin with \"<![CDATA[\" it begins with " ), temp_string );
      return( FALSE );
   }

   m_Type = typeCharacterData;
   m_Tag  = temp_string.Right( 7 ); // Record the tag
   m_Contents.Empty();

   // Now we need to see if the end of this string contains the ]]> tag
   // which may or may not signify the end of the cdata section

   temp_string = tag.Right( 3 );

   if ( temp_string.Compare( TEXT( "]]>" ) ) == 0 )
   {
      // This may be the end...

      if ( parser.PeekCharacter( m_Ending, 0 ) == ']' &&
           parser.PeekCharacter( m_Ending, 1 ) == ']' &&
           parser.PeekCharacter( m_Ending, 2 ) == '>' )
      {
         WFCTRACE( TEXT( "Escape sequence detected!" ) );

         m_Contents += TEXT( "]]>" ); // Add the escaped characters

         BOOL exit_loop = FALSE;

         while( exit_loop == FALSE )
         {
            if ( m_Ending.GetIndex() >= parser.GetSize() )
            {
               WFCTRACE( TEXT( "We ran out of room!" ) );
               return( FALSE );
            }

            character = parser.PeekCharacter( m_Ending, 0 );

            if ( character == ']' )
            {
               // DANG! It might be the terminator

               if ( parser.PeekCharacter( m_Ending, 1 ) == ']' &&
                    parser.PeekCharacter( m_Ending, 2 ) == '>' )
               {
                  // OK, we've got a terminator, let's see if it is an escape sequence

                  if ( parser.PeekCharacter( m_Ending, 3 ) == ']' &&
                       parser.PeekCharacter( m_Ending, 4 ) == ']' &&
                       parser.PeekCharacter( m_Ending, 5 ) == '>' )
                  {
                     // Yup, it is another escape sequence
                     // Let's skip the next 5 characters

                     m_Contents += TEXT( "]]" );

                     parser.AdvanceByOneCharacter( m_Ending, character );
                     parser.AdvanceByOneCharacter( m_Ending, ']' );
                     parser.AdvanceByOneCharacter( m_Ending, '>' );
                     parser.AdvanceByOneCharacter( m_Ending, ']' );
                     parser.AdvanceByOneCharacter( m_Ending, ']' );
                     character = '>';
                  }
                  else
                  {
                     // Well whaddya know, we found The Terminitor!
                     parser.AdvanceByOneCharacter( m_Ending, ']' );
                     parser.AdvanceByOneCharacter( m_Ending, '>' );
                     return( TRUE );
                  }

                  m_Contents += static_cast< TCHAR >( character );
                  parser.AdvanceByOneCharacter( m_Ending, character );
               }
            }
            else
            {
               // This is a safe character to add
               m_Contents += static_cast< TCHAR >( character );
            }
         }
      }
      else
      {
         // Normally terminated

         // Thanks to Stephane Drouin (stephane.drouin@inference.com)
         // for finding an off-by-one error here. I was subtracting
         // 11 when it should have been 12.
         // 1998-07-15

         m_Contents = tag.Mid( 9, tag.GetLength() - 12 );
         return( TRUE );
      }
   }
   else
   {
      // Nope, no such luck, add this text to the m_Contents and search for the true ending
      m_Contents = tag.Right( tag.GetLength() - 9 ); // Everything except <![CDATA
      BOOL exit_loop = FALSE;

      while( exit_loop == FALSE )
      {
         if ( m_Ending.GetIndex() >= parser.GetSize() )
         {
            WFCTRACE( TEXT( "We ran out of room!" ) );
            return( FALSE );
         }

         character = parser.PeekCharacter( m_Ending, 0 );

         if ( character == ']' )
         {
            // DANG! It might be the terminator

            if ( parser.PeekCharacter( m_Ending, 1 ) == ']' &&
                 parser.PeekCharacter( m_Ending, 2 ) == '>' )
            {
               // OK, we've got a terminator, let's see if it is an escape sequence

               if ( parser.PeekCharacter( m_Ending, 3 ) == ']' &&
                    parser.PeekCharacter( m_Ending, 4 ) == ']' &&
                    parser.PeekCharacter( m_Ending, 5 ) == '>' )
               {
                  // Yup, it is another escape sequence
                  // Let's skip the next 5 characters

                  m_Contents += TEXT( "]]" );

                  parser.AdvanceByOneCharacter( m_Ending, character );
                  parser.AdvanceByOneCharacter( m_Ending, ']' );
                  parser.AdvanceByOneCharacter( m_Ending, '>' );
                  parser.AdvanceByOneCharacter( m_Ending, ']' );
                  character = '>';
               }
               else
               {
                  // Well whaddya know, we found The Terminitor!
                  parser.AdvanceByOneCharacter( m_Ending, ']' );
                  parser.AdvanceByOneCharacter( m_Ending, '>' );
                  return( TRUE );
               }

               m_Contents += static_cast< TCHAR >( character );

               parser.AdvanceByOneCharacter( m_Ending, character );
            }
            else
            {
               // 1998-12-02, bug fix for release 38
               // I found that trailing ]]]]'s weren't properly added, DOH!
               // At least, for once, I found a bug in WFC before it being
               // reported to me.

               m_Contents += static_cast< TCHAR >( character );
            }
         }
         else
         {
            // This is a safe character to add
            m_Contents += static_cast< TCHAR >( character );
         }

         parser.AdvanceByOneCharacter( m_Ending, character );
      }
   }

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( '<' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( '!' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( '[' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( 'C' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( 'D' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( 'A' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( 'T' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( 'A' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   character = parser.PeekCharacter( m_Ending, 0 );

   if ( character != TEXT( '[' ) )
   {
      return( FALSE );
   }

   parser.AdvanceByOneCharacter( m_Ending, character );

   return( FALSE );
}

BOOL CExtensibleMarkupLanguageElement::m_ParseDOCTYPESection( const CString& tag, const CDataParser& parser )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseDOCTYPESection()" ) );

   // IDEA: Convert all parsing to CParsePoint's!!!!

   // The crappy thing about DOCTYPE sections is they don't follow XML syntax.
   // They are leftovers from SGML (i.e. the obfuscation layer of XML) days.

   // The tag parameter contains a terminating > character, however, we don't
   // know if there are any child elements yet.

   ASSERT( IsRoot() == FALSE );

   // First, strip off the DOCTYPE characters

   CString string_to_parse = tag.Right( tag.GetLength() - 9 );

   string_to_parse.TrimLeft();

   WFCTRACEVAL( TEXT( "Now parsing " ), string_to_parse );

   // We should now be sitting at the Name part of the doctypedecl

   if ( string_to_parse.GetLength() < 1 )
   {
      ASSERT( FALSE );
      m_ReportParsingError( TEXT( "DOCTYPE Section, not enough room to parse Name (Rule 28)." ) );
      return( FALSE );
   }

   DWORD character = 0;
   
#if ! defined( UNICODE )
   // ASCII Build
   
   character = static_cast< DWORD >( static_cast< BYTE >( string_to_parse.GetAt( 0 ) ) );

#else

   // UNICODE build

   character = string_to_parse.GetAt( 0 );

#endif // UNICODE

   // Test the first character of the name for legality (according to Rule 5)

   if ( ::is_xml_Letter( character ) == FALSE )
   {
      // the first character can also be a _ or a :

      if ( character != '_' && character != ':' )
      {
          m_ReportParsingError( TEXT( "DOCTYPE Section, illegal first character of Name (Rule 5)." ) );
         return( FALSE );
      }
   }

   // Name sections can be terminated by a space or a [

   int location_of_character = string_to_parse.FindOneOf( TEXT( " \t\r\n[" ) );

   if ( location_of_character == (-1) )
   {
      // 1999-09-01
      // Thanks go to Kim Winther Jorgensen <kwj@dia.dk> for finding
      // a bug here. I was not properly parsing simple DOCTYPE declarations

      // Let's see if we have a simplistic DOCTYPE

      location_of_character = string_to_parse.Find( TEXT( '>' ) );

      if ( location_of_character == (-1) )
      {
         m_ReportParsingError( TEXT( "Illegal DOCTYPE name terminator (Rule 28)." ) );
         return( FALSE );
      }
   }

   CString name = string_to_parse.Left( location_of_character );

   name.TrimRight();
   WFCTRACEVAL( TEXT( "Name is " ), name );

   // Now let's validate name as being valid characters

   int loop_index           = 1;
   int number_of_characters = name.GetLength();

   while( loop_index < number_of_characters )
   {
#if ! defined( UNICODE )
   // ASCII Build
   
   character = static_cast< DWORD >( static_cast< BYTE >( name.GetAt( loop_index ) ) );

#else

   // UNICODE build

   character = name.GetAt( loop_index );

#endif // UNICODE

      if ( ::is_xml_NameChar( character ) == FALSE )
      {
         m_ReportParsingError( TEXT( "Illegal DOCTYPE name character (Rule 28)." ) );
         return( FALSE );
      }

      loop_index++;
   }

   // Is the last character of the name a '['

   // Keep contents for later writing

   m_Contents = TEXT( "DOCTYPE " );
   m_Contents += name;

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - name.GetLength() );
   string_to_parse.TrimLeft();

   WFCTRACEVAL( TEXT( "Now parsing " ), string_to_parse );

   if ( string_to_parse.Compare( TEXT( ">" ) ) == 0 )
   {
      // We're done
      return( TRUE );
   }

   // The next character can be one of three possibilites, [, S or P

   if ( string_to_parse.GetAt( 0 ) != TEXT( '[' ) &&
        string_to_parse.GetAt( 0 ) != TEXT( 'S' ) &&
        string_to_parse.GetAt( 0 ) != TEXT( 'P' ) )
   {
      m_ReportParsingError( TEXT( "Impossible character in DOCTYPE declaration (Rule 28)." ) );
      return( FALSE );
   }

   // If we get here, we know the next thing is either SYSTEM, PUBLIC or [

   if ( string_to_parse.GetAt( 0 ) != TEXT( '[' ) )
   {
      if ( string_to_parse.GetLength() < 6 )
      {
         m_ReportParsingError( TEXT( "No more room to parse SYSTEM or PUBLIC (Rule 75)." ) );
         return( FALSE );
      }

      if ( string_to_parse.Left( 6 ).Compare( TEXT( "PUBLIC" ) ) != 0 &&
           string_to_parse.Left( 6 ).Compare( TEXT( "SYSTEM" ) ) != 0 )
      {
         m_ReportParsingError( TEXT( "DOCTYPE ExternalID is not SYSTEM or PUBLIC (Rule 75)." ) );
         return( FALSE );
      }

      BOOL is_public = FALSE;

      if ( string_to_parse.GetAt( 0 ) == TEXT( 'P' ) )
      {
         is_public = TRUE;
      }

      if ( is_public == TRUE )
      {
         // If it is PUBLIC, there should be two quoted strings following it (Rule 75)

         WFCTRACE( TEXT( "Parsing PUBLIC" ) );

         m_Contents += TEXT( " PUBLIC " );

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 6 );
         string_to_parse.TrimLeft();

         WFCTRACEVAL( TEXT( "Would now parse " ), string_to_parse );

         // We should now be sitting on a quoted string

         if ( string_to_parse.GetLength() < 2 )
         {
            m_ReportParsingError( TEXT( "Not enough room to quote a string (Rule 11)." ) );
            return( FALSE );
         }

         if ( string_to_parse.GetAt( 0 ) != TEXT( '\'' ) &&
              string_to_parse.GetAt( 0 ) != TEXT( '\"' ) )
         {
            m_ReportParsingError( TEXT( "String not properly quoted (Rule 11)." ) );
            return( FALSE );
         }

         BOOL we_started_with_a_double_quote = FALSE;

         if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
         {
            we_started_with_a_double_quote = TRUE;
         }

         // If we get here, it means we need to strip off the leading quote

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

         if ( we_started_with_a_double_quote != FALSE )
         {
            location_of_character = string_to_parse.Find( TEXT( '\"' ) );
         }
         else
         {
            location_of_character = string_to_parse.Find( TEXT( '\'' ) );
         }

         if ( location_of_character == (-1) )
         {
            m_ReportParsingError( TEXT( "Mismatched quotes (Rule 11)." ) );
            return( FALSE );
         }

         name = string_to_parse.Left( location_of_character );

         WFCTRACEVAL( TEXT( "Name is " ), name );

         // Now check to make sure the characters in name are legal Pubidchar's

         int loop_index = 0;

         while( loop_index < name.GetLength() )
         {
            if ( ::is_xml_PubidChar( name.GetAt( loop_index ) ) == FALSE )
            {
               m_ReportParsingError( TEXT( "Illegal PubidChar (Rule 13)." ) );
               return( FALSE );
            }

            loop_index++;
         }

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_character + 1 ) );
         string_to_parse.TrimLeft();

         WFCTRACEVAL( TEXT( "Would now parse " ), string_to_parse );

         if ( we_started_with_a_double_quote == TRUE )
         {
            m_Contents += TEXT( "\"" );
            m_Contents += name;
            m_Contents += TEXT( "\"" );
         }
         else
         {
            m_Contents += TEXT( "\'" );
            m_Contents += name;
            m_Contents += TEXT( "\'" );
         }

         WFCTRACEVAL( TEXT( "m_Contents iss now " ), m_Contents );

         // We should now be sitting on another quote character (SystemLiteral)

         if ( string_to_parse.GetLength() < 2 )
         {
            // There's not enough room for an opening and closing quote
            m_ReportParsingError( TEXT( "No more room to quote a string (Rule 11)." ) );
            return( FALSE );
         }

         if ( string_to_parse.GetAt( 0 ) != TEXT( '\'' ) &&
              string_to_parse.GetAt( 0 ) != TEXT( '\"' ) )
         {
            m_ReportParsingError( TEXT( "PUBLIC SystemLiteral not properly quoted (Rule 11)." ) );
            return( FALSE );
         }

         we_started_with_a_double_quote = FALSE;

         if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
         {
            we_started_with_a_double_quote = TRUE;
         }

         // If we get here, it means we need to strip off the leading quote

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

         if ( we_started_with_a_double_quote != FALSE )
         {
            location_of_character = string_to_parse.Find( TEXT( '\"' ) );
         }
         else
         {
            location_of_character = string_to_parse.Find( TEXT( '\'' ) );
         }

         if ( location_of_character == (-1) )
         {
            m_ReportParsingError( TEXT( "Mismatched quotes (Rule 11)." ) );
            return( FALSE );
         }

         name = string_to_parse.Left( location_of_character );
         WFCTRACEVAL( TEXT( "Name is " ), name );

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_character + 1 ) );
         string_to_parse.TrimLeft();
         
         WFCTRACEVAL( TEXT( "Would  now parse " ), string_to_parse );

         if ( we_started_with_a_double_quote == TRUE )
         {
            m_Contents += TEXT( "\"" );
            m_Contents += name;
            m_Contents += TEXT( "\"" );
         }
         else
         {
            m_Contents += TEXT( "\'" );
            m_Contents += name;
            m_Contents += TEXT( "\'" );
         }

         WFCTRACEVAL( TEXT( "m_Contents isss now " ), m_Contents );

         if ( string_to_parse.GetLength() == 0 )
         {
            m_ReportParsingError( TEXT( "No more room (Rule 28)." ) );
            return( FALSE );
         }
      }
      else
      {
         // If it is SYSTEM, there should be one quoted string following it (Rule 75)

         WFCTRACE( TEXT( "Parsing SYSTEM" ) );

         m_Contents += TEXT( " SYSTEM " );

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 6 );
         string_to_parse.TrimLeft();

         WFCTRACEVAL( TEXT( "Would now parse " ), string_to_parse );

         // We should now be sitting on a quote character (SystemLiteral)

         if ( string_to_parse.GetLength() < 2 )
         {
            // There's not enough room for an opening an and closing quotes
            m_ReportParsingError( TEXT( "No more room to parse a quoted string (Rule 11)." ) );
            return( FALSE );
         }

         if ( string_to_parse.GetAt( 0 ) != TEXT( '\'' ) &&
              string_to_parse.GetAt( 0 ) != TEXT( '\"' ) )
         {
            m_ReportParsingError( TEXT( "PUBLIS SystemLiteral not properly quoted (Rule 11)." ) );
            return( FALSE );
         }

         BOOL we_started_with_a_double_quote = FALSE;

         if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
         {
            we_started_with_a_double_quote = TRUE;
         }

         // If we get here, it means we need to strip off the leading quote

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

         if ( we_started_with_a_double_quote != FALSE )
         {
            location_of_character = string_to_parse.Find( TEXT( '\"' ) );
         }
         else
         {
            location_of_character = string_to_parse.Find( TEXT( '\'' ) );
         }

         if ( location_of_character == (-1) )
         {
            m_ReportParsingError( TEXT( "Mismatched quotes (Rule 11)." ) );
            return( FALSE );
         }

         name = string_to_parse.Left( location_of_character );

         WFCTRACEVAL( TEXT( "Name is " ), name );

         string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_character + 1 ) );
         string_to_parse.TrimLeft();

         WFCTRACEVAL( TEXT( "Would now parse " ), string_to_parse );

         if ( we_started_with_a_double_quote == TRUE )
         {
            m_Contents += TEXT( "\"" );
            m_Contents += name;
            m_Contents += TEXT( "\"" );
         }
         else
         {
            m_Contents += TEXT( "\'" );
            m_Contents += name;
            m_Contents += TEXT( "\'" );
         }

         WFCTRACEVAL( TEXT( "m_Contents iss now " ), m_Contents );

         if ( string_to_parse.GetLength() == 0 )
         {
            m_ReportParsingError( TEXT( "No more room (Rule 28)." ) );
            return( FALSE );
         }
      }
   }

   // Yet another inconsistency in XML, child elements of DOCTYPE are delimited
   // by square brackets. No, it doesn't make any sense. It is one of the problems
   // of maintaining backward compatibility with SGML.

   if ( string_to_parse.GetAt( 0 ) == TEXT( '>' ) )
   {
      WFCTRACE( TEXT( "Finished parsing." ) );
      return( TRUE );
   }

   if ( string_to_parse.GetAt( 0 ) != TEXT( '[' ) )
   {
      m_ReportParsingError( TEXT( "Illegal character at contiuation point (Rule 28)." ) );
      return( FALSE );
   }

   m_Contents += TEXT( " [" );
   WFCTRACEVAL( TEXT( "m_Contents is now " ), m_Contents );

   // If it is [, then we have a whole lot of SGML pain to go through

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
   WFCTRACEVAL( TEXT( "string_to_parse is now " ), string_to_parse );

   // The next valid characters are spaces (Rule 28), a closing bracket (Rule 28) or an opening < (Rule 29)
   // Let's go for the easy stuff first

   while( string_to_parse.GetLength() > 0 && ::is_xml_white_space( string_to_parse.GetAt( 0 ) ) )
   {
      m_Contents += string_to_parse.GetAt( 0 );
      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
   }

   WFCTRACEVAL( TEXT( "Now would parse " ), string_to_parse );

   // We have now narrowed things down to a ] or a <

   if ( string_to_parse.GetLength() == 0 )
   {
      m_ReportParsingError( TEXT( "No room after continuation point (Rule 28)." ) );
      return( FALSE );
   }

   if ( string_to_parse.GetAt( 0 ) == TEXT( ']' ) )
   {
      m_Contents += TEXT( "]" );

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
      string_to_parse.TrimLeft();
      WFCTRACEVAL( TEXT( "Now would parse " ), string_to_parse );

      if ( string_to_parse.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "No room after closing ] (Rule 28)." ) );
         return( FALSE );
      }

      // This character must be the closing >

      if ( string_to_parse.GetAt( 0 ) != TEXT( '>' ) )
      {
         m_ReportParsingError( TEXT( "Missing closing > (Rule 28)." ) );
         return( FALSE );
      }

      return( TRUE );
   }

   // It wasn't a ']' so it must be a <

   if ( string_to_parse.GetAt( 0 ) != TEXT( '<' ) )
   {
      m_ReportParsingError( TEXT( "Ill-formed DOCTYPE child, missing < (Rule 29)." ) );
      return( FALSE );
   }

   // We must recurse

   CParsePoint beginning_of_child( m_Beginning );

   // The following while loop is to preserve the line and column counts

   int number_of_bytes_per_character = 1;

   if ( parser.IsTextASCII() == FALSE )
   {
      if ( parser.IsTextUCS4() != FALSE )
      {
         number_of_bytes_per_character = 4;
      }
      else
      {
         number_of_bytes_per_character = 2;
      }
   }

   while( beginning_of_child.GetIndex() < ( m_Ending.GetIndex() - ( string_to_parse.GetLength() * number_of_bytes_per_character ) ) )
   {
      parser.AdvanceByOneCharacter( beginning_of_child );
   }

   CExtensibleMarkupLanguageElement * sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

   // Now parse until we find the end of DOCTYPE

   BOOL exit_loop = FALSE;

   DWORD character_to_test = 0;

   while( exit_loop != TRUE )
   {
      if ( parser.PeekCharacter( beginning_of_child, 0 ) == '<' )
      {
         sub_element_p = NewElement( this, typeElement, m_Document );

         if ( sub_element_p->Parse( beginning_of_child, parser ) == FALSE )
         {
            WFCTRACE( TEXT( "Failed to parse sub element" ) );
            return( FALSE );
         }
      }
      else if ( parser.PeekCharacter( beginning_of_child, 0 ) == '%' )
      {
         // We've got a reference to an entity

         CString entity_string;

         if ( parser.GetUntilAndIncluding( beginning_of_child, TEXT( ";" ), entity_string ) == FALSE )
         {
            m_ReportParsingError( TEXT( "DOCTYPE PEReference is missing terminating semi-colon (Rule 69)." ) );
            return( FALSE );
         }

         WFCTRACEVAL( TEXT( "Would now parse " ), entity_string );

         CString entity_to_resolve( entity_string );

         if ( entity_to_resolve.GetAt( 0 ) == TEXT( '%' ) )
         {
            entity_to_resolve.SetAt( 0, TEXT( '&' ) );
         }

         CString entity_resolved_to;

         if ( m_Document == NULL )
         {
            m_ReportParsingError( TEXT( "No entity database." ) );
            return( FALSE );
         }

         if ( m_Document->ResolveEntity( entity_to_resolve, entity_resolved_to ) == FALSE )
         {
            m_ReportParsingError( TEXT( "Can't resolve DOCTYPE PEReference (Rule 69)." ) );
            return( FALSE );
         }

         // OK, now that we have resolved the entity, we need to parse it (it is kind of recursive)

         BOOL exit_parse_loop = FALSE;

         while( exit_parse_loop == FALSE )
         {
            if ( entity_resolved_to.GetAt( 0 ) == TEXT( '%' ) )
            {
               // I hates dragon rabbits. We have another entity to resolve.

               entity_to_resolve = entity_resolved_to;
               entity_to_resolve.SetAt( 0, TEXT( '&' ) );

               if ( m_Document->ResolveEntity( entity_to_resolve, entity_resolved_to ) == FALSE )
               {
                  m_ReportParsingError( TEXT( "Can't resolve embedded DOCTYPE PEReference (Rule 69)." ) );
                  return( FALSE );
               }
            }
            else if ( entity_resolved_to.GetAt( 0 ) == TEXT( '<' ) )
            {
               // This code implements an insert type function. We need
               // to parse bytes that aren't present in the data stream
               // (wrapped by CDataParser). We need to insert those bytes
               // at this time and parse them. We create a new CDataParser
               // to solve this problem.

               CByteArray new_bytes;

               wfc_append_string_to_CByteArray( entity_resolved_to, new_bytes );

               CDataParser entity_parser;

               entity_parser.Initialize( &new_bytes, FALSE );

               CParsePoint entity_beginning;

               sub_element_p = NewElement( this, typeElement, m_Document );

               if ( sub_element_p == NULL )
               {
                  m_ReportParsingError( TEXT( "Ran out of memory allocating for a tricky element." ) );
                  return( FALSE );
               }

               if ( sub_element_p->Parse( entity_beginning, entity_parser ) == FALSE )
               {
                  m_ReportParsingError( TEXT( "Can't parse tricky element (Rule 69)." ) );
                  return( FALSE );
               }
               else
               {
                  exit_parse_loop = TRUE;
                  sub_element_p->m_Ending.Copy( beginning_of_child );
               }
            }
            else
            {
               // If we get here, it means there's most likely been an external
               // reference. Since we are a standalone only parser, we must
               // error out.

               CString error_message;

               error_message  = TEXT( "Unsupported (non-standalone) External Reference to \"" );
               error_message += entity_resolved_to;
               error_message += TEXT( "\"" );

               m_ReportParsingError( error_message );

               return( FALSE );
            }
         }
      }
      else
      {
         sub_element_p = NewElement( this, typeTextSegment, m_Document );

         // The only thing we cal allow in a text segment that is a child of DOCTYPE is
         // on that contains all white spaces, Rule 28

         sub_element_p->m_Beginning.Copy( beginning_of_child );

         while( ::is_xml_white_space( parser.PeekCharacter( beginning_of_child, 0 ) ) == TRUE )
         {
            sub_element_p->m_Contents += static_cast< TCHAR >( parser.PeekCharacter( beginning_of_child, 0 ) );
            parser.AdvanceByOneCharacter( beginning_of_child );
         }

         sub_element_p->m_Ending.Copy( beginning_of_child );
      }

      // Now skip characters until we get to ] or <

      sub_element_p->GetEnding( beginning_of_child );

      if ( beginning_of_child.GetIndex() >= parser.GetSize() )
      {
         // We're done
         return( TRUE ); // this should probably be FALSE
      }

      character_to_test = parser.PeekCharacter( beginning_of_child, 0 );

      if ( character_to_test == TEXT( ']' ) )
      {
         // Hey! we're at the end, now skip spaces

         parser.AdvanceByOneCharacter( beginning_of_child, ']' );

         while( ::is_xml_white_space( parser.PeekCharacter( beginning_of_child, 0 ) ) == TRUE )
         {
            parser.AdvanceByOneCharacter( beginning_of_child );

            if ( beginning_of_child.GetIndex() >= parser.GetSize() )
            {
               m_ReportParsingError( TEXT( "Error 2490 (Rule 28)." ) );     
               return( FALSE ); // this should probably be FALSE
            }
         }

         // We had better be on a closing >

         if ( parser.PeekCharacter( beginning_of_child, 0 ) != TEXT( '>' ) )
         {
            m_ReportParsingError( TEXT( "Ill-formed DOCTYPE child, missing terminating > (Rule 28)." ) );     
            return( FALSE ); // this should probably be FALSE
         }

         parser.AdvanceByOneCharacter( beginning_of_child );
         m_Ending.Copy( beginning_of_child );

         WFCTRACE( TEXT( "Successful parse!" ) );
         return( TRUE );
      }

      sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
   }

   // Need to validate the sub-elements to make sure they ain't XML (i.e. regular elements)
   // They must all be processing instructions

   m_ReportParsingError( TEXT( "DOCTYPE Section did not parse." ) );
   return( FALSE );
}

BOOL CExtensibleMarkupLanguageElement::m_ParseElementName( const CString& name, CString& parent_name, DWORD& desired_instance_number, CString& child_name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseElementName()" ) );

   if ( name.GetLength() == 0 )
   {
      return( FALSE );
   }

   TCHAR parent_child_separator_character = TEXT( '.' );

   if ( m_Document != NULL )
   {
      parent_child_separator_character = m_Document->GetParentChildSeparatorCharacter();
   }

   parent_name = name;

   // Let's pull off the first field

   int location_of_separator = 0;

   location_of_separator = parent_name.Find( parent_child_separator_character );

   if ( location_of_separator != (-1) )
   {
      child_name  = parent_name.Right( parent_name.GetLength() - ( location_of_separator + 1 ) );
      parent_name = parent_name.Left( location_of_separator );
   }

   //WFCTRACEVAL( TEXT( "Parent name is " ), parent_name );
   //WFCTRACEVAL( TEXT( "Child name is  " ), child_name );

   // What we're looking for is the parent_name portion of what was passed to us.
   // We know it's name but we need to know which instance of that named object we want.

   desired_instance_number = 0;

   desired_instance_number = parent_name.Find( TEXT( '(' ) );

   if ( desired_instance_number != (-1) )
   {
      // Looks like we've got an instance number in here

      int location_of_beginning = desired_instance_number;
      int location_of_ending    = parent_name.Find( TEXT( ')' ) );

      // Check to make sure they didn't pass us something like "Southpark)0("
      
      if ( location_of_ending < location_of_beginning )
      {
         WFCTRACE( TEXT( "[] is ][ (they're backwards)" ) );
         return( FALSE );
      }

      location_of_beginning++; // skip the (

      if ( location_of_beginning >= location_of_ending )
      {
         WFCTRACE( TEXT( "location_of_beginning >= location_of_ending" ) );
         // we saw "()" so we default to an instance number of zero
         desired_instance_number = 0;
      }
      else
      {
         // There something between ( and )

         CString instance_number_string;

         instance_number_string = parent_name.Mid( location_of_beginning, (location_of_ending - location_of_beginning ) );

         instance_number_string.TrimLeft();
         instance_number_string.TrimRight();

         // WFCTRACEVAL( TEXT( "instance_number_string is " ), instance_number_string );

         desired_instance_number = ::_ttol( instance_number_string );

         // Now trim off the ( xxx )

         parent_name = parent_name.Left( location_of_beginning - 1 );
      }
   }
   else
   {
      WFCTRACE( TEXT( "There ain't no ()" ) );
      desired_instance_number = 0;
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::m_ParseProcessingInstruction( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseProcessingInstruction()" ) );

   if ( m_Contents.GetLength() == 0 )
   {
      m_ReportParsingError( TEXT( "The processing instruction cannot be empty (Rule 16)." ) );
      return( FALSE );
   }

   // m_Contents has been filled with the data between the <? and the ?>

   if ( m_Contents.GetLength() > 2 )
   {
      if ( m_Contents.Left( 3 ).CompareNoCase( TEXT( "xml" ) ) == 0 )
      {
         return( m_ParseXMLDeclaration( m_Contents ) );
      }
   }

   // Check to see if the first character of the name is legal

   CString legal_characters( TEXT( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_:" ) );

   int value_index = 0;

   value_index = legal_characters.Find( m_Contents.Left( 1 ) );

   if ( value_index == (-1) )
   {
      m_ReportParsingError( TEXT( "Illegal first character in processing instruction (Rule 16->5)." ) );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::m_ParseTag( const CString& tag, BOOL& did_tag_contain_terminator, const CDataParser& parser )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseTag()" ) );

   // At this point, tag should contain both a '<' and a '>'

   did_tag_contain_terminator = FALSE;

   CString tag_data( tag );
   CString tag_name;
   CString attribute_name;
   CString attribute_value;

   BOOL we_started_with_a_double_quote = FALSE;

   // The first thing we must do is check for a <![CDATA[ section.

   if ( tag.GetLength() > 9 )
   {
      tag_name = tag.Left( 9 );

      if ( tag_name.Compare( TEXT( "<![CDATA[" ) ) == 0 )
      {
         // Yup, this here is a CDATA section

         if ( m_ParseCDATASection( tag, parser ) != FALSE )
         {
            did_tag_contain_terminator = TRUE; // CDATA sections are self-terminating
            return( TRUE );
         }
         else
         {
            m_ReportParsingError( TEXT( "Ill formed CDATA section." ) );
            return( FALSE );
         }
      }

      tag_name.Empty();
   }

   int location_of_character = 0;

   location_of_character = tag_data.FindOneOf( TEXT( " \t\r\n" ) ); // This list of space characters is taken from section 2.3 of the XML 1.0 recommendation (REC-xml-19980210)

   if ( location_of_character == (-1) )
   {
      WFCTRACE( TEXT( "There ain't no attributes" ) );

      // There ain't no attributes (and no spaces)

      tag_name = tag;
      tag_data.Empty();

      if ( tag_name.GetLength() > 0 )
      {
         if ( tag_name.GetAt( 0 ) == TEXT( '<' ) )
         {
            tag_name = tag_name.Right( tag_name.GetLength() - 1 );
         }
      }

      if ( tag_name.GetLength() > 0 )
      {
         if ( tag_name.GetAt( tag_name.GetLength() - 1 ) == TEXT( '>' ) )
         {
            tag_name = tag_name.Left( tag_name.GetLength() - 1 );
         }
      }

      tag_name.TrimRight();
      tag_name.TrimLeft();

      // Let's see if we are a terminator

      if ( tag_name.GetLength() > 0 )
      {
         if ( tag_name.GetAt( 0 ) == TEXT( '/' ) )
         {
            did_tag_contain_terminator = TRUE;
         }
         else
         {
            // Thanks go to Jeff Winkler (winkler1@sprynet.com)
            // For adding this section. I was not properly
            // handling self terminating tags (like <job/>)

            if ( tag_name.GetAt( tag_name.GetLength() - 1 ) == TEXT( '/' ) )
            {
               did_tag_contain_terminator = TRUE;

               // Now trim off that terminator

               tag_name = tag_name.Left( tag_name.GetLength() - 1 );
            }
         }
      }

      m_Tag = tag_name;
   }
   else
   {
      // There are some attributes

      tag_name = tag_data.Left( location_of_character );

      if ( tag_name.GetLength() > 0 )
      {
         if ( tag_name.GetAt( 0 ) == TEXT( '<' ) )
         {
            // OOPS! We need to trim off the beginning
            tag_name = tag_name.Right( tag_name.GetLength() - 1 );
            tag_name.TrimRight();
            tag_name.TrimLeft();
         }
      }
   }

   WFCTRACEVAL( TEXT( "Setting m_Tag to " ), tag_name );

   // Checkout the first character of the tag name, it may be
   // a special one

   if ( tag_name.GetLength() < 1 )
   {
      WFCTRACE( TEXT( "Tag is empty." ) );
      m_ReportParsingError( TEXT( "Tag is empty." ) );
      return( FALSE );
   }

   switch( tag_name.GetAt( 0 ) )
   {
      case TEXT( '?' ):

         // We got us one of them there processing instructions

         WFCTRACEVAL( TEXT( "It is a processing instruction " ), this );
         m_Type = typeProcessingInstruction;

         m_Tag.Empty();

         if ( tag.Find( TEXT( "?>" ) ) == (-1) )
         {
            // If we get here, it means we hit something tricky like "<?pi some data ? > <??>"
            WFCTRACE( TEXT( "Can't find processing instruction terminator \"?>\"" ) );

            m_Contents = tag.Right( tag.GetLength() - 2 );
            WFCTRACEVAL( TEXT( "Contents is now " ), m_Contents );

            CString tricky_end;

            if ( parser.GetUntilAndIncluding( m_Ending, TEXT( "?>" ), tricky_end ) == FALSE )
            {
               m_ReportParsingError( TEXT( "Processing instruction is not terminated with ?> (Rule 16)" ) );
               return( FALSE );
            }

            m_Contents += tricky_end.Left( tricky_end.GetLength() - 2 );

            if ( IsRoot() == FALSE )
            {
               did_tag_contain_terminator = TRUE;
            }

            return( m_ParseProcessingInstruction() );
         }

         m_Contents = tag.Mid( 2, tag.GetLength() - 4 );

         if ( IsRoot() == FALSE )
         {
            did_tag_contain_terminator = TRUE;
         }

         WFCTRACEVAL( "Contents is ", m_Contents );

         return( m_ParseProcessingInstruction() );

         break;

      case TEXT( '!' ):

         // We got us one of them there META tags, but hold on! It could
         // be any one of a number of things (I thought this was designed
         // to be easily parsed).

         WFCTRACE( TEXT( "It is a META tag thingy" ) );

         if ( tag_name.GetLength() < 3 )
         {
            WFCTRACE( TEXT( "Giving up" ) );
            m_ReportParsingError( TEXT( "META tag is too short." ) );
            return( FALSE );
         }

         // See if it is a comment <!--
         if ( tag_name.GetAt( 1 ) == TEXT( '-' ) &&
              tag_name.GetAt( 2 ) == TEXT( '-' ) )
         {
            // Yup, it is a comment

            WFCTRACE( TEXT( "It is a comment" ) );

            m_Type = typeComment;

            m_Contents = tag_data.Right( tag_data.GetLength() - 4 );

            if ( m_Document != NULL && ( m_Document->GetParseOptions() & WFC_XML_LOOSE_COMMENT_PARSING ) )
            {
               location_of_character = m_Contents.Find( TEXT( "-->" ) );

               if ( location_of_character == (-1) )
               {
                  // If we get here, it means the comment text contains a >

                  CString temp_string;

                  if ( parser.GetUntilAndIncluding( m_Ending, TEXT( "-->" ), temp_string ) == FALSE )
                  {
                     WFCTRACE( TEXT( "Can't find comment terminator \"-->\"" ) );
                     m_ReportParsingError( TEXT( "Comment is missing the --> terminator (Rule 15)." ) );
                     return( FALSE );
                  }

                  m_Contents += temp_string;
                  location_of_character = m_Contents.Find( TEXT( "-->" ) );
               }
            }
            else
            {
               // Strict comment parsing

               location_of_character = m_Contents.Find( TEXT( "--" ) );

               if ( location_of_character == (-1) )
               {
                  WFCTRACE( TEXT( "Can't find comment terminator \"--\"" ) );
                  m_ReportParsingError( TEXT( "Comment is missing the -- terminator (Rule 15)." ) );
                  return( FALSE );
               }

               if ( m_Contents.GetAt( location_of_character + 2 ) != TEXT( '>' ) )
               {
                  WFCTRACE( TEXT( "Comment contains illegal double dashes (Rule 15)." ) );
                  m_ReportParsingError( TEXT( "Comment contains illegal double dashes (Rule 15)." ) );
                  return( FALSE );
               }
            }

            m_Contents = m_Contents.Left( location_of_character );
            did_tag_contain_terminator = TRUE;

            return( TRUE );
         }
         else if ( tag_name.GetAt( 1 ) == TEXT( '[' ) &&
                 ( tag_name.GetAt( 2 ) == TEXT( 'C' ) || tag_name.GetAt( 2 ) == TEXT( 'c' ) ) )
         {
            // We may have a CDATA section here

            if ( tag_name.GetLength() < 9 )
            {
               WFCTRACE( TEXT( "Giving up on funky CData section" ) );
               m_ReportParsingError( TEXT( "Ill formed CDATA section (Rule 19)." ) );
               return( FALSE );
            }

            CString cdata;

            cdata = tag_name.Mid( 1, 8 );

            if ( cdata.Compare( TEXT( "![CDATA[" ) ) == 0 )
            {
               WFCTRACE( TEXT( "It is a CDATA section" ) );

               // Well, whaddya know... It is a CDATA section
               m_Type = typeCharacterData;
               tag_name = TEXT( "[CDATA[" );

               if ( m_ParseCDATASection( tag, parser ) == FALSE )
               {
                  WFCTRACE( TEXT( "Can't parse CDATA section" ) );
                  m_ReportParsingError( TEXT( "Bad CDATA section (Rule 20)." ) );
                  return( FALSE );
               }
            }
            else
            {
               m_Type                     = typeMetaData;
               did_tag_contain_terminator = TRUE;
            }
         }
         else if ( tag_name.GetLength() > 6   &&
                   tag_name.GetAt( 1 ) == TEXT( 'E' ) &&
                   tag_name.GetAt( 2 ) == TEXT( 'N' ) &&
                   tag_name.GetAt( 3 ) == TEXT( 'T' ) &&
                   tag_name.GetAt( 4 ) == TEXT( 'I' ) &&
                   tag_name.GetAt( 5 ) == TEXT( 'T' ) &&
                   tag_name.GetAt( 6 ) == TEXT( 'Y' ) )
         {
            WFCTRACE( TEXT( "ENTITY tag found" ) );

            // First, parse it like a generic processing instruction. This
            // allows us to output it just like we input it.

            m_Tag = tag_name.Right( tag_name.GetLength() - 1 );

            // The rest of the line goes into m_Contents

            m_Contents = tag_data.Right( tag_data.GetLength() - ( location_of_character + 1 ) );

            // Strip off the trailing '>'

            if ( m_Contents.GetLength() > 0 )
            {
               if ( m_Contents.GetAt( m_Contents.GetLength() - 1 ) == TEXT( '>' ) )
               {
                  m_Contents = m_Contents.Left( m_Contents.GetLength() - 1 );
               }
            }

            // Now add the entity to the document

            int location_of_entity = tag_data.Find( TEXT( "ENTITY" ) );

            if ( location_of_entity == (-1) )
            {
               WFCTRACE( TEXT( "Something bad wrong in ENTITY processing." ) );
               m_ReportParsingError( TEXT( "Ill formed ENTITY section (Rule 71)." ) );
               return( FALSE );
            }

            tag_data = tag_data.Right( tag_data.GetLength() - (location_of_entity + 6) );

            tag_data.TrimLeft();
            tag_data.TrimRight();

            if ( tag_data.GetLength() > 0 )
            {
               // There's something in there, Rule 72 says there can be a
               // percent sign as the first character

               if ( tag_data.GetAt( 0 ) == TEXT( '%' ) )
               {
                  tag_data = tag_data.Right( tag_data.GetLength() - 1 );

                  // Trim leading spaces

                  tag_data.TrimLeft();
               }

               // Hopefully we are now left with a string like this:
               // WFC_HOME "c:\wfc"

               if ( tag_data.GetLength() > 1 )
               {
                  // We should now be on the entity name

                  int location_of_space = tag_data.FindOneOf( TEXT( " \t\r\n" ) );

                  if ( location_of_space == (-1) )
                  {
                     WFCTRACE( TEXT( "Ill-formed ENTITY" ) );
                     m_ReportParsingError( TEXT( "Ill formed ENTITY section[2] (Rule 71)." ) );
                     return( FALSE );
                  }

                  CString entity_name;

                  entity_name = tag_data.Left( location_of_space );

                  WFCTRACEVAL( TEXT( "Entity name is " ), entity_name );

                  tag_data = tag_data.Right( tag_data.GetLength() - location_of_space );

                  tag_data.TrimLeft();

                  // We should now be on a quote (single or double)

                  if ( tag_data.GetAt( 0 ) != TEXT( '"' ) && tag_data.GetAt( 0 ) != '\'' )
                  {
                     // 1999-03-26
                     // Thanks go to Jurgen Lumera (jlumera@vftis.com) for finding
                     // a bug where I wasn't correctly parsing ENTITY lines. DOH DOH DOH!
                     // We must be an external entity

                     WFCTRACE( TEXT( "First character of entity value is not a quote or single quote (see Rule 9). Let's see if it is an external reference." ) );

                     // We must attempt to parse according to rules 75 and 76

                     if ( tag_data.GetAt( 0 ) != TEXT( 'S' ) && tag_data.GetAt( 0 ) != TEXT( 'P' ) )
                     {
                        WFCTRACE( TEXT( "Ill-formed external entity value. Character is not S or P. Refer to rule 75." ) );
                        m_ReportParsingError( TEXT( "Ill formed ENTITY section[4] (Rule 71)." ) );
                        return( FALSE );
                     }

                     if ( tag_data.GetAt( 0 ) == TEXT( 'S' ) )
                     {
                        // Entity must be SYSTEM

                        if ( tag_data.GetLength() < 6 )
                        {
                           // Not enough room to succeede
                           WFCTRACE( TEXT( "Ran out of room parsing SYSTEM. Refer to rule 75." ) );
                           m_ReportParsingError( TEXT( "Ill formed ENTITY section (Rule 75)." ) );
                           return( FALSE );
                        }

                        // See if the next few characters make up YSTEM

                        if ( tag_data.GetAt( 1 ) != TEXT( 'Y' ) ||
                             tag_data.GetAt( 2 ) != TEXT( 'S' ) ||
                             tag_data.GetAt( 3 ) != TEXT( 'T' ) ||
                             tag_data.GetAt( 4 ) != TEXT( 'E' ) ||
                             tag_data.GetAt( 5 ) != TEXT( 'M' ) )
                        {
                           WFCTRACE( TEXT( "External entity is not SYSTEM. Refer to rule 75." ) );
                           m_ReportParsingError( TEXT( "Ill formed ENTITY section[2] (Rule 75)." ) );
                           return( FALSE );
                        }

                        // <!ENTITY smelc80562AA1 SYSTEM "smelc80562AA1.tif" NDATA saetiff>

                        tag_data = tag_data.Right( tag_data.GetLength() - 6 );
                        tag_data.TrimLeft();
                     }
                     else
                     {
                        // Entity must be PUBLIC
                        if ( tag_data.GetLength() < 6 )
                        {
                           // Not enough room to succeede
                           WFCTRACE( TEXT( "Ran out of room parsing PUBLIC. Refer to rule 75." ) );
                           m_ReportParsingError( TEXT( "Ill formed ENTITY (PUBLIC) section (Rule 75)." ) );
                           return( FALSE );
                        }

                        // See if the next few characters make up UBLIC

                        if ( tag_data.GetAt( 1 ) != TEXT( 'U' ) ||
                             tag_data.GetAt( 2 ) != TEXT( 'B' ) ||
                             tag_data.GetAt( 3 ) != TEXT( 'L' ) ||
                             tag_data.GetAt( 4 ) != TEXT( 'I' ) ||
                             tag_data.GetAt( 5 ) != TEXT( 'C' ) )
                        {
                           WFCTRACE( TEXT( "External entity is not PUBLIC. Refer to rule 75." ) );
                           m_ReportParsingError( TEXT( "Ill formed ENTITY (PUBLIC) section[2] (Rule 75)." ) );
                           return( FALSE );
                        }

                        m_Contents                 = tag_data;
                        did_tag_contain_terminator = TRUE;

                        return( TRUE );
                     }
                  }

                  if ( tag_data.GetAt( 0 ) == TEXT( '"' ) )
                  {
                     // Double quote terminated

                     tag_data = tag_data.Right( tag_data.GetLength() - 1 );

                     location_of_entity = tag_data.Find( TEXT( '"' ) );

                     while( location_of_entity == (-1) )
                     {
                        // This could be the result of a > existing in the entity value

                        WFCTRACE( TEXT( "Can't find closing double quote." ) );

                        CString temp_string;

                        if ( parser.GetUntilAndIncluding( m_Ending, TEXT( ">" ), temp_string ) == FALSE )
                        {
                           m_ReportParsingError( TEXT( "ENTITY value missing closing double quote (Rule 9)." ) );
                           return( FALSE );
                        }

                        tag_data += temp_string;

                        location_of_entity = tag_data.Find( TEXT( '"' ) );
                     }

                     tag_data = tag_data.Left( location_of_entity );
                  }
                  else
                  {
                     // Single quote terminated

                     tag_data = tag_data.Right( tag_data.GetLength() - 1 );

                     location_of_entity = tag_data.Find( TEXT( '\'' ) );

                     while( location_of_entity == (-1) )
                     {
                        WFCTRACE( TEXT( "Can't find closing single quote." ) );

                        CString temp_string;

                        if ( parser.GetUntilAndIncluding( m_Ending, TEXT( ">" ), temp_string ) == FALSE )
                        {
                           m_ReportParsingError( TEXT( "ENTITY value missing closing single quote (Rule 9)." ) );
                           return( FALSE );
                        }

                        tag_data += temp_string;

                        location_of_entity = tag_data.Find( TEXT( '\'' ) );
                     }

                     tag_data = tag_data.Left( location_of_entity );
                  }

                  WFCTRACEVAL( TEXT( "Entity value is " ), tag_data );

                  if ( m_Document != NULL )
                  {
                     CString entity_to_add( TEXT( "&" ) );

                     entity_to_add += entity_name;
                     entity_to_add += TEXT( ";" );

                     if ( m_Document->AddEntity( entity_to_add, tag_data ) == FALSE )
                     {
                        WFCTRACE( TEXT( "Can't add entity to document." ) );
                        m_ReportParsingError( TEXT( "Internal error adding ENTITY" ) );
                        return( FALSE );
                     }
                  }
                  else
                  {
                     WFCTRACE( TEXT( "Not adding entity because we are an orphaned element." ) );
                  }

                  m_Type                     = typeMetaData;
                  did_tag_contain_terminator = TRUE;

                  return( TRUE );
               }
            }
         }
         else if ( tag_name.GetLength() > 7   &&
                   tag_name.GetAt( 1 ) == TEXT( 'D' ) &&
                   tag_name.GetAt( 2 ) == TEXT( 'O' ) &&
                   tag_name.GetAt( 3 ) == TEXT( 'C' ) &&
                   tag_name.GetAt( 4 ) == TEXT( 'T' ) &&
                   tag_name.GetAt( 5 ) == TEXT( 'Y' ) &&
                   tag_name.GetAt( 6 ) == TEXT( 'P' ) &&
                   tag_name.GetAt( 7 ) == TEXT( 'E' ) )
         {
            WFCTRACE( TEXT( "DOCTYPE tag found" ) );

            m_Type = typeMetaData;
            did_tag_contain_terminator = TRUE;

            if ( m_ParseDOCTYPESection( tag, parser ) == FALSE )
            {
               // m_ParseDOCTYPESection() calls m_ReportParsingError()
               return( FALSE );
            }
            else
            {
               return( TRUE );
            }
         }
         else
         {
            // This is some generic processing instruction

            WFCTRACE( TEXT( "Generic processing instruction" ) );

            // Strip off the leading !
            tag_name = tag_name.Right( tag_name.GetLength() - 1 );
            m_Type                     = typeMetaData;
            did_tag_contain_terminator = TRUE;

            m_Tag = tag_name;

            // The rest of the line goes into m_Contents

            m_Contents = tag_data.Right( tag_data.GetLength() - ( location_of_character + 1 ) );

            // Strip off the trailing '>'

            if ( m_Contents.GetLength() > 0 )
            {
               if ( m_Contents.GetAt( m_Contents.GetLength() - 1 ) == TEXT( '>' ) )
               {
                  m_Contents = m_Contents.Left( m_Contents.GetLength() - 1 );
               }
            }

            return( TRUE );
         }

         break;

      default:

         m_Type = typeElement;
         break;
   }

   m_Tag = tag_name;

   if ( m_Type == typeProcessingInstruction )
   {
      return( TRUE );
   }
   else if ( m_Type == typeElement )
   {
      // We must now validate the element name as being legal

      if ( m_Tag.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "EmptyTag." ) );
         return( FALSE );
      }

      if ( ::is_xml_Letter( m_Tag.GetAt( 0 ) ) == FALSE &&
           m_Tag.GetAt( 0 ) != TEXT( '/' )              &&
           m_Tag.GetAt( 0 ) != TEXT( '_' )              &&
           m_Tag.GetAt( 0 ) != TEXT( ':' ) )
      {
         m_ReportParsingError( TEXT( "First character of element name is not legal (Rule 5)." ) );
         return( FALSE );
      }

      // 1999-09-10
      // Thanks go to Jean-Loup Clement (Jean-Loup.Clement@bull.net)
      // for finding out that VC5 doesn't support UINT32.

      DWORD name_loop_index = 1;

      while( name_loop_index < (DWORD) m_Tag.GetLength() )
      {
         if ( ::is_xml_NameChar( m_Tag.GetAt( name_loop_index ) ) == FALSE )
         {
            CString error_message;

            error_message.Format( TEXT( "Character %lu of element named \"%s\" is invalid (Rule 999192)." ),
               (unsigned long) name_loop_index,
               (LPCTSTR) m_Tag );
            m_ReportParsingError( error_message );
            return( FALSE );
         }

         name_loop_index++;
      }
   }

   tag_data = tag_data.Right( tag_data.GetLength() - ( location_of_character + 1 ) );
   tag_data.TrimLeft();

   // Let's see if we are terminated via shorthand

   if ( tag_data.GetLength() > 1 )
   {
      // The next-to-last character should be a /
      if ( tag_data.GetAt( tag_data.GetLength() - 2 ) == TEXT( '/' ) )
      {
         did_tag_contain_terminator = TRUE;
      }

      if ( tag_data.GetAt( 0 ) == TEXT( '/' ) )
      {
         return( TRUE );
      }
   }

   BOOL we_parsed_at_least_one_attribute = FALSE;

   while( tag_data.GetLength() > 1 )
   {
      location_of_character = tag_data.Find( TEXT( '=' ) );

      if ( location_of_character == (-1) )
      {
         if ( we_parsed_at_least_one_attribute == FALSE )
         {
            m_ReportParsingError( TEXT( "Attribute must have '=' between the name and the value (Rule 41)." ) );
            return( FALSE );
         }

         WFCTRACE( TEXT( "No More attributes" ) );
         return( TRUE );
      }

      we_parsed_at_least_one_attribute = TRUE;

      attribute_name = tag_data.Left( location_of_character );
      attribute_name.TrimRight();
      attribute_name.TrimLeft();

      tag_data = tag_data.Right( tag_data.GetLength() - ( location_of_character + 1 ) );
      tag_data.TrimLeft();

      // Here's where Jeff Winkler found another bug. I was not
      // correctly parsing attributes with spaces in them. DOH!

      if ( tag_data.GetLength() == 0 )
      {
         WFCTRACE( TEXT( "Ran out of room looking for attribute value" ) );
         m_ReportParsingError( TEXT( "Not yet documented error 2726." ) );
         return( FALSE );
      }

      // When we get here tag_data contains "Two Words">

      // Search for the beginning quote (single or double)
      // The XML specification (Rule [10]) says attribute
      // values can be deliminated by single or double quotes

      we_started_with_a_double_quote = FALSE;

      if ( tag_data.GetAt( 0 ) != TEXT( '\"' ) )
      {
         WFCTRACE( TEXT( "First character of an attribute value was not a quote!" ) );

         if ( tag_data.GetAt( 0 ) != TEXT( '\'' ) )
         {
            WFCTRACE( TEXT( "And it ain't a single quote either!" ) );
            m_ReportParsingError( TEXT( "Attribute values must begin with a \" or a ' (Rule 10)." ) );
            return( FALSE );
         }
         else
         {
            we_started_with_a_double_quote = FALSE;
         }
      }
      else
      {
         we_started_with_a_double_quote = TRUE;
      }

      // If we get here, we need to strip off the leading quote

      tag_data = tag_data.Right( tag_data.GetLength() - 1 );

      if ( we_started_with_a_double_quote != FALSE )
      {
         location_of_character = tag_data.Find( TEXT( '\"' ) );
      }
      else
      {
         location_of_character = tag_data.Find( TEXT( '\'' ) );
      }

      if ( location_of_character == (-1) )
      {
         WFCTRACEVAL( TEXT( "Couldn't find anything at line " ), __LINE__ );

         // At the end of the line?

         attribute_value = tag_data;

         if ( attribute_value.GetLength() == 0 )
         {
            ASSERT( FALSE );
            return( FALSE );
         }

         // Since we are the last, we need to check the terminating characters
         // The last character should always be a '>'

         if ( attribute_value.GetAt( attribute_value.GetLength() - 1 ) != TEXT( '>' ) )
         {
            WFCTRACE( TEXT( "missing terminating >" ) );
            m_ReportParsingError( TEXT( "Not yet documented error 2785." ) );
            return( FALSE );
         }

         // Trim off that character

         attribute_value = attribute_value.Left( attribute_value.GetLength() - 1 );

         // Now, here comes the fun part. The next-to-last
         // character will be different depending on the type
         // of element this fella is.

         if ( m_Type == typeProcessingInstruction )
         {
            // The next-to-last character should be a ?

            if ( attribute_value.GetAt( attribute_value.GetLength() - 1 ) != TEXT( '?' ) )
            {
               WFCTRACE( TEXT( "Missing trailing ? from Processing Instruction field" ) );
               m_ReportParsingError( TEXT( "Not yet documented error 2804." ) );
               return( FALSE );
            }

            attribute_value = attribute_value.Left( attribute_value.GetLength() - 1 );
         }
         else if ( m_Type == typeMetaData || m_Type == typeElement )
         {
            if ( attribute_value.GetLength() > 0 )
            {
               if ( attribute_value.GetAt( attribute_value.GetLength() - 1 ) == TEXT( '/' ) )
               {
                  // Shorthand terminator
                  did_tag_contain_terminator = TRUE;

                  attribute_value = attribute_value.Left( attribute_value.GetLength() - 1 );
               }
            }
         }

         // Add this attribute...

         if ( attribute_value.GetLength() > 0 )
         {
            if ( we_started_with_a_double_quote != FALSE )
            {
               if ( m_TrimQuotesAndSpaces( attribute_value, TEXT( '\"' ) ) == FALSE )
               {
                  m_ReportParsingError( TEXT( "Attribute missing matching \" (Rule 10)." ) );
                  return( FALSE );
               }
            }
            else
            {
               if ( m_TrimQuotesAndSpaces( attribute_value, TEXT( '\'' ) ) == FALSE )
               {
                  m_ReportParsingError( TEXT( "Attribute missing matching \' (Rule 10)." ) );
                  return( FALSE );
               }
            }

            if ( AddAttribute( attribute_name, attribute_value ) == FALSE )
            {
               // Adding attribute failed. It called m_ReportParsingError() for us.
               return( FALSE );
            }

            return( TRUE );
         }
         else
         {
            // Rule 10
            m_ReportParsingError( TEXT( "Empty attribute not allowed (Rule 10)." ) );
            return( FALSE );
         }
      }
      else
      {
         attribute_value = tag_data.Left( location_of_character );

         if ( we_started_with_a_double_quote != FALSE )
         {
            m_TrimQuotesAndSpaces( attribute_value, TEXT( '\"' ) );
         }
         else
         {
            m_TrimQuotesAndSpaces( attribute_value, TEXT( '\'' ) );
         }

         tag_data = tag_data.Right( tag_data.GetLength() - ( location_of_character + 1 ) );

         tag_data.TrimLeft();

         if ( AddAttribute( attribute_name, attribute_value ) == FALSE )
         {
            // Adding attribute failed. It called m_ReportParsingError() for us.
            return( FALSE );
         }
      }

      attribute_name.Empty();
      attribute_value.Empty();
   }

   WFCTRACEVAL( TEXT( "Successfully parsed tag " ), m_Tag );

   if ( m_Tag.GetLength() > 1 )
   {
      if ( m_Tag.GetAt( 0 ) == TEXT( '/' ) )
      {
         // If we get here, it means that our end tag had trailing spaces.
         // Or, it could have had attributes which is a no no.

         if ( m_Attributes.GetSize() > 0 )
         {
            m_ReportParsingError( TEXT( "Attributes not allowed in end tag (Rule 42)." ) );
            return( FALSE );
         }

         did_tag_contain_terminator = TRUE;
      }
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageElement::m_ParseXMLDeclaration( const CString& tag )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ParseXMLDeclaration()" ) );
   WFCTRACEVAL( TEXT( "Would parse " ), tag );

   CString temp_string = tag.Left( 3 );

   DWORD parsing_options = 0;

   if ( m_Document != NULL )
   {
      parsing_options = m_Document->GetParseOptions();
   }

   if ( ! ( parsing_options & WFC_XML_IGNORE_CASE_IN_XML_DECLARATION ) )
   {
      // We must begin with lower case xml

      if ( temp_string.Compare( TEXT( "xml" ) ) != 0 )
      {
         m_ReportParsingError( TEXT( "The xml declaration must be lower case (Rule 23)." ) );
         return( FALSE );
      }
   }

   // We've found the XML declaration, let's see if we are the root element

   if ( IsRoot() == FALSE )
   {
      // We ain't root. That means we've come across another XML declaration in the data.
      // That ain't legal.

      m_ReportParsingError( TEXT( "There can be only one prolog (Rule 1)." ) );
      return( FALSE );
   }

   CString string_to_parse;

   string_to_parse = tag.Right( tag.GetLength() - 3 );
   string_to_parse.TrimLeft();

   if ( string_to_parse.GetLength() < 7 )
   {
      m_ReportParsingError( TEXT( "Missing VersionInfo data (Rule 23)." ) );
      return( FALSE );
   }

   CString attribute_name = string_to_parse.Left( 7 );

   if ( attribute_name.Compare( TEXT( "version" ) ) != 0 )
   {
      m_ReportParsingError( TEXT( "The VersionInfo must be lower case (Rule 23)." ) );
      return( FALSE );
   }

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 7 );
   string_to_parse.TrimLeft();

   // We should be at the = character

   if ( string_to_parse.GetLength() == 0 )
   {
      m_ReportParsingError( TEXT( "Truncated VersionInfo (Rule 24)." ) );
      return( FALSE );
   }

   if ( string_to_parse.GetAt( 0 ) != TEXT( '=' ) )
   {
      m_ReportParsingError( TEXT( "Ill-formed VersionInfo missing = character (Rule 24)." ) );
      return( FALSE );
   }

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
   string_to_parse.TrimLeft();

   if ( string_to_parse.GetLength() == 0 )
   {
      m_ReportParsingError( TEXT( "Ill-formed VersionInfo, missing VersionNum (Rule 24)." ) );
      return( FALSE );
   }

   BOOL we_started_with_a_double_quote = FALSE;

   if ( string_to_parse.GetAt( 0 ) != TEXT( '\"' ) &&
        string_to_parse.GetAt( 0 ) != TEXT( '\'' ) )
   {
      m_ReportParsingError( TEXT( "Illegal VersionNum delimiter, must be a single or double quote (Rule 24)." ) );
      return( FALSE );
   }

   if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
   {
      we_started_with_a_double_quote = TRUE;
   }

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

   int location_of_delimiter = 0;

   if ( we_started_with_a_double_quote == TRUE )
   {
      location_of_delimiter = string_to_parse.Find( TEXT( '\"' ) );
   }
   else
   {
      location_of_delimiter = string_to_parse.Find( TEXT( '\'' ) );
   }

   if ( location_of_delimiter == (-1) )
   {
      m_ReportParsingError( TEXT( "VersionNum missing matching delimiter (Rule 24)." ) );
      return( FALSE );
   }

   CString value;

   value = string_to_parse.Left( location_of_delimiter );

   if ( value.GetLength() == 0 )
   {
      m_ReportParsingError( TEXT( "Empty VersionNum not allowed (Rule 26)." ) );
      return( FALSE );
   }

   string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_delimiter + 1 ) );
   string_to_parse.TrimLeft();

   CString legal_characters( TEXT( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.:" ) );

   int value_index = 0;

   while( value_index < value.GetLength() )
   {
      if ( legal_characters.Find( value.GetAt( value_index ) ) == (-1) )
      {
         CString error_message;

         error_message.Format( TEXT( "Character %d (decimal %d) of the \"version\" attribute is illegal (Rule 26)." ), value_index, (int) value.GetAt( value_index ) );

         WFCTRACE( error_message );

         m_ReportParsingError( error_message );

         return( FALSE );
      }

      value_index++;
   }

   if ( m_Document != NULL )
   {
      m_Document->SetVersion( value );
   }

   if ( string_to_parse.GetLength() == 0 )
   {
      // EncodingDecl and SDDecl are missing but that's OK
      return( TRUE );
   }

   // If we get here, we can expect to see EncodingDecl or SDDecl

   WFCTRACEVAL( TEXT( "Now parsing" ), string_to_parse );

   // Let's see if we are sitting on "encoding"

   if ( string_to_parse.GetLength() < 8 )
   {
      // There's not enough room for either "encoding" or "standalone"
      m_ReportParsingError( TEXT( "Not enough room left to parse (Rule 23)." ) );
      return( FALSE );
   }

   int loop_index = 0;

   value = string_to_parse.Left( 8 );

   if ( value.Compare( TEXT( "encoding" ) ) == 0 )
   {
      // We are encoding, let's parse it

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 8 );
      string_to_parse.TrimLeft();

      // We should be at the = character

      if ( string_to_parse.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Truncated EncodingDecl (Rule 80)." ) );
         return( FALSE );
      }

      if ( string_to_parse.GetAt( 0 ) != TEXT( '=' ) )
      {
         m_ReportParsingError( TEXT( "Ill-formed EncodingDecl missing = character (Rule 80)." ) );
         return( FALSE );
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
      string_to_parse.TrimLeft();

      if ( string_to_parse.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Ill-formed EncodingDecl, missing EncName (Rule 80)." ) );
         return( FALSE );
      }

      we_started_with_a_double_quote = FALSE;

      if ( string_to_parse.GetAt( 0 ) != TEXT( '\"' ) &&
           string_to_parse.GetAt( 0 ) != TEXT( '\'' ) )
      {
         m_ReportParsingError( TEXT( "Illegal EncName delimiter, must be a single or double quote (Rule 80)." ) );
         return( FALSE );
      }

      if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
      {
         we_started_with_a_double_quote = TRUE;
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

      location_of_delimiter = 0;

      if ( we_started_with_a_double_quote == TRUE )
      {
         location_of_delimiter = string_to_parse.Find( TEXT( '\"' ) );
      }
      else
      {
         location_of_delimiter = string_to_parse.Find( TEXT( '\'' ) );
      }

      if ( location_of_delimiter == (-1) )
      {
         m_ReportParsingError( TEXT( "EncName missing matching delimiter (Rule 80)." ) );
         return( FALSE );
      }

      value = string_to_parse.Left( location_of_delimiter );

      if ( value.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Empty EncName not allowed (Rule 81)." ) );
         return( FALSE );
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_delimiter + 1 ) );
      string_to_parse.TrimLeft();

      // Now validate the contents of EncName

      TCHAR character = value.GetAt( 0 );

      if (  ( character >= 'a' && character <= 'z' ) ||
            ( character >= 'A' && character <= 'Z' ) )
      {
         // Do Nothing
      }
      else
      {
         m_ReportParsingError( TEXT( "Illegal first character in EncName (Rule 81)." ) );
         return( FALSE );
      }

      if ( value.GetLength() > 1 )
      {
         legal_characters = TEXT( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-" );

         loop_index = 1;

         while( loop_index < value.GetLength() )
         {
            if ( legal_characters.Find( value.GetAt( loop_index ) ) == (-1) )
            {
               CString error_message;

               error_message.Format( TEXT( "Character %d is illegal in EncName of \"%s\" (Rule 81)." ), loop_index + 1, (LPCTSTR) value );

               m_ReportParsingError( TEXT( "Illegal first character in EncName (Rule 81)." ) );
               return( FALSE );
            }

            loop_index++;
         }

         if ( m_Document != NULL )
         {
            m_Document->SetEncoding( value );
         }
      }
   }

   if ( string_to_parse.GetLength() == 0 )
   {
      // Missing SDDecl but that's OK
      return( TRUE );
   }

   // If we get here, we can expect to see SDDecl

   if ( string_to_parse.GetLength() < 10 )
   {
      // There's not enough room for either "encoding" or "standalone"
      m_ReportParsingError( TEXT( "Not enough room left to parse SDDecl (Rule 32)." ) );
      return( FALSE );
   }

   value = string_to_parse.Left( 10 );

   if ( value.Compare( TEXT( "standalone" ) ) == 0 )
   {
      // We are standalone, let's parse it
      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 10 );
      string_to_parse.TrimLeft();

      // We should be at the = character

      if ( string_to_parse.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Truncated SDDecl (Rule 32)." ) );
         return( FALSE );
      }

      if ( string_to_parse.GetAt( 0 ) != TEXT( '=' ) )
      {
         m_ReportParsingError( TEXT( "Ill-formed SDDecl missing = character (Rule 32)." ) );
         return( FALSE );
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );
      string_to_parse.TrimLeft();

      if ( string_to_parse.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Ill-formed SDDecl, missing data (Rule 32)." ) );
         return( FALSE );
      }

      we_started_with_a_double_quote = FALSE;

      if ( string_to_parse.GetAt( 0 ) != TEXT( '\"' ) &&
           string_to_parse.GetAt( 0 ) != TEXT( '\'' ) )
      {
         m_ReportParsingError( TEXT( "Illegal SDDecl delimiter, must be a single or double quote (Rule 32)." ) );
         return( FALSE );
      }

      if ( string_to_parse.GetAt( 0 ) == TEXT( '\"' ) )
      {
         we_started_with_a_double_quote = TRUE;
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - 1 );

      location_of_delimiter = 0;

      if ( we_started_with_a_double_quote == TRUE )
      {
         location_of_delimiter = string_to_parse.Find( TEXT( '\"' ) );
      }
      else
      {
         location_of_delimiter = string_to_parse.Find( TEXT( '\'' ) );
      }

      if ( location_of_delimiter == (-1) )
      {
         m_ReportParsingError( TEXT( "SDDecl missing matching delimiter (Rule 32)." ) );
         return( FALSE );
      }

      value = string_to_parse.Left( location_of_delimiter );

      if ( value.GetLength() == 0 )
      {
         m_ReportParsingError( TEXT( "Empty SDDecl not allowed (Rule 32)." ) );
         return( FALSE );
      }

      string_to_parse = string_to_parse.Right( string_to_parse.GetLength() - ( location_of_delimiter + 1 ) );
      string_to_parse.TrimLeft();

      // Now validate the contents of SDDecl

      if ( value.Compare( TEXT( "yes" ) ) != 0 && value.Compare( TEXT( "no" ) ) != 0 )
      {
         m_ReportParsingError( TEXT( "Illegal value for SDDecl, it must me lower case \"yes\" or \"no\" (Rule 32)." ) );
         return( FALSE );
      }

      if ( m_Document != NULL )
      {
         if ( value.Compare( TEXT( "yes" ) ) == 0 )
         {
            m_Document->SetStandalone( TRUE );
         }
         else
         {
            m_Document->SetStandalone( FALSE );
         }
      }
   }

   if ( string_to_parse.GetLength() != 0 )
   {
      m_ReportParsingError( TEXT( "Extra characters after SDDecl (Rule 23)." ) );
      return( FALSE );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageElement::m_ReportParsingError( LPCTSTR error_message )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ReportParsingError()" ) );

   if ( m_Document != NULL )
   {
      try
      {
         m_Document->SetParsingErrorInformation( m_Tag, m_Beginning, m_Ending, error_message );
      }
      catch( ... )
      {
         // Do Nothing
      }
   }
}

void CExtensibleMarkupLanguageElement::m_ResolveEntities( CString& encoded_entity_string ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_ResolveEntities()" ) );

   if ( m_Document == NULL )
   {
      // There ain't no stinking document! Only the document knows what the entities are
      return;
   }

   if ( encoded_entity_string.Find( TEXT( '&' ) ) == (-1) )
   {
      // YIPPEE!! There aren't any entities to decode
      return;
   }

   // Yup, there be entities in that there string

   int location = 0;

   CString translated_string;
   CString temp_string( encoded_entity_string );
   CString entity;
   CString text;

   location = temp_string.Find( TEXT( '&' ) );

   while( location >= 0 )
   {
      // We found the beginning of an entity (hopefully)
      translated_string += temp_string.Left( location );

      temp_string = temp_string.Right( temp_string.GetLength() - location );

      location = temp_string.Find( TEXT( ';' ) );

      if ( location == (-1) )
      {
         WFCTRACEVAL( TEXT( "Found the beginning of an entity but not the end in: " ), encoded_entity_string );
         return;
      }

      entity = temp_string.Left( location + 1 );

      if ( m_Document->ResolveEntity( entity, text ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "Unresloved entity " ), entity );
         return;
      }

      translated_string += text;

      temp_string = temp_string.Right( temp_string.GetLength() - ( location + 1 ) );

      // Let's try to find another entity...
      location = temp_string.Find( TEXT( '&' ) );
   }

   translated_string += temp_string;

   encoded_entity_string = translated_string;
}

BOOL CExtensibleMarkupLanguageElement::m_TrimQuotesAndSpaces( CString& value, TCHAR quote_to_trim ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::m_TrimQuotesAndSpaces()" ) );

   value.TrimRight();
   value.TrimLeft();

   BOOL return_value = FALSE;

   if ( value.GetLength() > 0 )
   {
      if ( value.GetAt( 0 ) == quote_to_trim )
      {
         value = value.Right( value.GetLength() - 1 );
      }

      if ( value.GetLength() > 0 )
      {
         if ( value.GetAt( value.GetLength() - 1 ) == quote_to_trim )
         {
            return_value = TRUE;
            value = value.Left( value.GetLength() - 1 );
         }
      }

      value.TrimRight();
      value.TrimLeft();
   }

   return( return_value );
}

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageElement::NewElement( CExtensibleMarkupLanguageElement * parent_item, DWORD type, CExtensibleMarkupLanguageDocument * document )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::NewElement()" ) );

   CExtensibleMarkupLanguageElement * element_p = (CExtensibleMarkupLanguageElement *) NULL;

   try
   {
      element_p = new CExtensibleMarkupLanguageElement;

      if ( element_p != NULL )
      {
         element_p->SetType( type );
         element_p->m_Parent   = parent_item;
         element_p->m_Document = document;

         // Let's see if we should inherit the document

         if ( element_p->m_Parent != NULL )
         {
            if ( element_p->m_Document == NULL )
            {
               element_p->m_Document = element_p->m_Parent->m_Document;
            }

            // Since we have a parent, that parent must have a child

            element_p->m_Parent->AddChild( element_p );
         }
      }
   }
   catch( ... )
   {
      element_p = NULL;
   }

   return( element_p );
}

BOOL CExtensibleMarkupLanguageElement::Parse( const CParsePoint& beginning, const CDataParser& parser )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::Parse()" ) );
   WFCTRACEVAL( TEXT( "Parsing at line " ), beginning.GetLineNumber() );
   WFCTRACEVAL( TEXT( "Column          " ), beginning.GetLineIndex()  );
   WFCTRACEVAL( TEXT( "Byte Index      " ), beginning.GetIndex()      );

   m_AbortParsing = FALSE;

   // Start out with an empty object

   Empty();

   DWORD parsing_options = 0;

   if ( m_Document != NULL )
   {
      parsing_options = m_Document->GetParseOptions();
   }

   if ( m_Ending.GetIndex() >= parser.GetSize() )
   {
      WFCTRACE( TEXT( "Ran out of room before we started" ) );
      m_ReportParsingError( TEXT( "There are no more bytes to parse. We ran out of bytes before we rand out of XML." ) );
      return( FALSE );
   }

   if ( m_Type == typeUnknown )
   {
      WFCTRACE( TEXT( "We don't know what type of element we are therefore we don't know how to parse the data" ) );
      m_ReportParsingError( TEXT( "Type of element is unknown. Could not parse element data." ) );
      return( FALSE );
   }

   m_Beginning.Copy( beginning );
   m_Ending.Copy( beginning );

   DWORD end_of_data = parser.GetSize();

   DWORD character = 0x00;

   // OK we are at a location that must contain something interesting
   // to parse. How we parse depends on what type of element we are.

   if ( m_Type == typeTextSegment )
   {
      WFCTRACE( TEXT( "We are a text segment" ) );

      m_IsAllWhiteSpace = TRUE;

      // 1999-08-20
      // Thanks go to Scott Dowson (scott.dowson@pnl.gov) for the tremendous
      // speed improvement

      CByteArray text_segment_array;

      // Now tell the array to grow by big chunks (16KB in this instance)
      // We want to keep the allocations in a page size (4KB) for effeciency

      text_segment_array.SetSize( 0, 16 * 1024 );

      // We are a text segment, we start copying until we reach
      // a < or until we run out of room.

      while( m_Ending.GetIndex() < end_of_data )
      {
         character = parser.PeekCharacter( m_Ending, 0 );

         if ( character == TCHAR( '<' ) )
         {
            // We've reached the end of our segment

            text_segment_array.Add( 0 );

#if defined( UNICODE )
            text_segment_array.Add( 0 );
#endif // UNICODE

            m_Contents = (LPCTSTR) text_segment_array.GetData();

            return( TRUE );
         }

         // Now let's see if we are still in the running to be all white space

         if ( m_IsAllWhiteSpace != FALSE )
         {
            if ( character != 0x20 &&
                 character != 0x09 &&
                 character != CARRIAGE_RETURN &&
                 character != LINE_FEED )
            {
               // We didn't find this character in the space string so it must not be a space-like character

               m_IsAllWhiteSpace = FALSE;
            }
         }

         parser.AdvanceByOneCharacter( m_Ending, character );

#if defined( UNICODE )

         text_segment_array.Add( LOBYTE( character ) );
         text_segment_array.Add( HIBYTE( character ) );

#else // UNICODE

         text_segment_array.Add( static_cast< BYTE >( character ) );

#endif // UNICODE
      }
   }
   else
   {
      WFCTRACE( TEXT( "We are an element" ) );

      // We are some type of element, we should therefore be sitting on
      // a '<' (to start the tag).

      character = parser.PeekCharacter( m_Ending, 0 );

      if ( character != '<' )
      {
         WFCTRACE( TEXT( "Can't parse element without '<' being the first character" ) );
         WFCTRACEVAL( TEXT( "Failed at input line number " ), m_Ending.GetLineNumber() );
         WFCTRACEVAL( TEXT( "Character into line " ), m_Ending.GetLineIndex() );
         WFCTRACEVAL( TEXT( "Byte index " ), m_Ending.GetIndex() );
         ASSERT( FALSE );
         return( FALSE );
      }

      // OK, we are sitting on a '<', let's parse the tag
      // We need to put the data into a CString so m_ParseTag can deal with it

      CString tag_string;

      // 1998-11-22, new for Release 38
      // Thanks go to Jeff Barczewski (jb@snowflight.com) for finding a bug where
      // comments weren't begin parsed correctly.

      // There's a special case we must consider here. If what we're parsing
      // is a comment (i.e. it begins with "<!--"), we must ignore all special
      // characters until we reach "-->".

      BOOL terminator_found = FALSE;

      if ( parser.PeekCharacter( m_Ending, 1 ) == '!' &&
           parser.PeekCharacter( m_Ending, 2 ) == '-' &&
           parser.PeekCharacter( m_Ending, 3 ) == '-' )
      {
         // Yup, we are in the special case here. We are parsing a comment tag
         terminator_found = parser.GetUntilAndIncluding( m_Ending, TEXT( "-->" ), tag_string );
      }
      else if ( parser.PeekCharacter( m_Ending, 1 ) == '!' &&
                parser.PeekCharacter( m_Ending, 2 ) == '[' &&
                parser.PeekCharacter( m_Ending, 3 ) == 'C' &&
                parser.PeekCharacter( m_Ending, 4 ) == 'D' &&
                parser.PeekCharacter( m_Ending, 5 ) == 'A' &&
                parser.PeekCharacter( m_Ending, 6 ) == 'T' &&
                parser.PeekCharacter( m_Ending, 7 ) == 'A' &&
                parser.PeekCharacter( m_Ending, 8 ) == '[' )
      {
         // Gawl dang CDATA sections
         terminator_found = parser.GetUntilAndIncluding( m_Ending, TEXT( "]]>" ), tag_string );
      }
      else
      {
         terminator_found = parser.GetUntilAndIncluding( m_Ending, TEXT( ">" ), tag_string );
      }

      if ( terminator_found != FALSE )
      {
         WFCTRACEVAL( TEXT( "tag_string is " ), tag_string );

         if ( m_ParseTag( tag_string, m_ShorthandTerminatorDetected, parser ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't m_ParseTag()" ) );
            // m_ParseTag calls m_ReportParsingError
            //m_ReportParsingError( TEXT( "Internal error: Could not parse tag." ) );
            Empty();
            return( FALSE );
         }

         if ( m_ShorthandTerminatorDetected == TRUE )
         {
            WFCTRACE( TEXT( "m_ShorthandTerminatorDetected is TRUE" ) );
            m_IsTagTerminated = TRUE;
         }

         // We've parsed our opening tag, let's see what the future holds

         CExtensibleMarkupLanguageElement * sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

         // while ( m_IsTagTerminated == FALSE || m_Type == typeProcessingInstruction )
         while ( m_IsTagTerminated == FALSE )
         {
            // We've got sub_elements!
            WFCTRACE( TEXT( "We've got sub-elements!" ) );

            // Let's see if the sub-element is a text segment or not

            if ( m_Ending.GetIndex() < end_of_data )
            {
               character = parser.PeekCharacter( m_Ending, 0 );

               if ( character != '<' )
               {
#if 0
                  if ( m_Type == typeProcessingInstruction && m_Parent != NULL )
                  {
                     // If we are a processing instruction then the child will be the
                     // child of our parent and not us. The child will be a sibling

                     WFCTRACEVAL( TEXT( "New sub element will be SIBLING a text segment, character was " ), character );
                     WFCTRACEVAL( TEXT( "It will be a child of " ), m_Parent->m_Tag );
                     sub_element_p = NewElement( m_Parent, typeTextSegment, m_Document ); // Makes the new element a child of this element
                  }
                  else
                  {
                     WFCTRACEVAL( TEXT( "New sub element will be a text segment, character was " ), character );
                     sub_element_p = NewElement( this, typeTextSegment, m_Document ); // Makes the new element a child of this element
                  }
#endif
                  WFCTRACEVAL( TEXT( "New sub element will be a text segment, character was " ), character );
                  sub_element_p = NewElement( this, typeTextSegment, m_Document ); // Makes the new element a child of this element
               }
               else
               {
                  WFCTRACE( TEXT( "New sub element will be some sort of element" ) );
                  sub_element_p = NewElement( this, typeElement, m_Document ); // Makes the new element a child of this element
               }

               if ( sub_element_p == NULL )
               {
                  WFCTRACE( TEXT( "Can't create a NewElement()" ) );
                  m_ReportParsingError( TEXT( "Internal error: Could not create new element." ) );
                  Empty();
                  return( FALSE );
               }
            }
            else
            {
               WFCTRACE( TEXT( "We are at the end of the document" ) );

               // We are at the end of the document

               if ( IsRoot() == FALSE )
               {
                  m_ReportParsingError( TEXT( "Premature end of data." ) );
                  Empty();

                  return( FALSE );
               }

               if ( m_Document != NULL )
               {
                  m_Document->ExecuteCallbacks( this );
               }

               return( TRUE );
            }

            if ( sub_element_p != NULL )
            {
               WFCTRACE( TEXT( "Sub element was created" ) );

               if ( sub_element_p->Parse( m_Ending, parser ) != FALSE )
               {
                  WFCTRACE( TEXT( "Adding sub element as child" ) );
                  sub_element_p->GetEnding( m_Ending ); // Here's where we check to see if the sub-element just added is our terminator

                  sub_element_p->GetTag( tag_string );

                  if ( tag_string.GetLength() > 0 )
                  {
                     if ( tag_string.GetAt( 0 ) == TEXT( '/' ) )
                     {
                        // We've got a terminator, let's make sure it is ours!

                        tag_string = tag_string.Right( tag_string.GetLength() - 1 );

                        tag_string.TrimRight();
                        tag_string.TrimLeft();

                        if ( tag_string.Compare( m_Tag ) != 0 )
                        {
                           WFCTRACEVAL( TEXT( "received a terminator for " ), tag_string );
                           WFCTRACEVAL( TEXT( "Unfortunately we are a " ), m_Tag );
                           WFCTRACE( TEXT( "That means we have overlapping tags!" ) );

                           // Error message added by Mats, 1998-08-17
                           CString error_text;

                           error_text.Format( TEXT( "Overlapping tags detected. Found \"%s\" but needed to find \"%s\"." ),
                                              (LPCTSTR) tag_string,
                                              (LPCTSTR) m_Tag );

                           m_ReportParsingError( error_text );

                           RemoveChild( sub_element_p ); // Because NewElement made it our child
                           DeleteElement( sub_element_p );
                           sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
                           Empty();

                           return( FALSE );
                        }
                        else
                        {
                           WFCTRACE( TEXT( "We found our terminator!" ) );

                           // Yup, we are the correct terminator
                           m_IsTagTerminated = TRUE;

                           RemoveChild( sub_element_p ); // Because NewElement made it our child
                           DeleteElement( sub_element_p );
                           sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

                           if ( m_Document != NULL )
                           {
                              m_Document->ExecuteCallbacks( this );
                           }

                           // Now that the callbacks have had their shot, let's
                           // see if we should abort parsing

                           if ( m_AbortParsing != FALSE )
                           {
                              m_ReportParsingError( TEXT( "Parsing was aborted by Callback function." ) );
                              return( FALSE );
                           }

                           return( TRUE );
                        }
                     }
                  }
                  else
                  {
                     // 1998-12-02
                     // Larry Brendehoeft (Larry.Bredehoeft@sierra.com) suggested this feature be added

                     // 1999-08-19
                     // Added & checking

                     if (     parsing_options & WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS ||
                          ! ( parsing_options & WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS ) )
                     {
                        if ( sub_element_p->GetType() == typeTextSegment )
                        {
                           if ( sub_element_p->m_IsAllWhiteSpace )
                           {
                              RemoveChild( sub_element_p );
                              DeleteElement( sub_element_p );
                              sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
                           }
                           else
                           {
                              WFCTRACE( TEXT( "Checking for ampersands..." ) );

                              // If we get here, it means we need to check the text segment for ampersands

                              int location_of_ampersand = sub_element_p->m_Contents.Find( TEXT( '&' ) );

                              while( location_of_ampersand != (-1) )
                              {
                                 // There's an ampersand in there, now let's validate it

                                 int location_of_semicolon = sub_element_p->m_Contents.Find( TEXT( ';' ), location_of_ampersand + 1 );

                                 if ( location_of_semicolon == (-1) )
                                 {
                                    m_ReportParsingError( TEXT( "Ill-formed entity reference in text section (Rule 68)." ) );
                                    return( FALSE );
                                 }

                                 DWORD rule_that_was_broken = 0;

                                 if ( m_Document->GetEntities().IsEntity( sub_element_p->m_Contents.Mid( location_of_ampersand, ( location_of_semicolon + 1 ) - location_of_ampersand ), rule_that_was_broken ) == FALSE )
                                 {
                                    CString error_message;

                                    error_message.Format( TEXT( "Bad entity reference in text section (Rule %lu)." ), (unsigned long) rule_that_was_broken );
                                    m_ReportParsingError( error_message );
                                    return( FALSE );
                                 }

                                 location_of_ampersand = sub_element_p->m_Contents.Find( TEXT( '&' ), location_of_ampersand + 1 );
                              }
                           }
                        }
                     }
                  }
               }
               else
               {
                  WFCTRACE( TEXT( "Sub-Element parse failed" ) );
                  WFCTRACEVAL( TEXT( "We began parsing at index " ), sub_element_p->m_Beginning.GetIndex() );
                  WFCTRACEVAL( TEXT( "Line " ), sub_element_p->m_Beginning.GetLineNumber() );
                  WFCTRACEVAL( TEXT( "Column " ), sub_element_p->m_Beginning.GetLineIndex() );

#if 0
                  // This error reporting is unnecessary because sub_element_p will have
                  // reported the information. We would only be overwriting what it reported.

                  // Error message added by Mats, 1998-08-17
                  CString error_text;

                  error_text.Format( TEXT( "Internal error: Parsing of sub-element failed. Current element is \"%s\". ),
                                     (LPCTSTR) m_Tag );

                  m_ReportParsingError( error_text );
#endif // 0

                  RemoveChild( sub_element_p );
                  DeleteElement( sub_element_p );
                  sub_element_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

                  return( FALSE );
               }
            }
         }
      }
      else
      {
         // Terminator could not be found
         // 1998-12-08 what happens when the terminator ain't found
         m_ReportParsingError( TEXT( "Could not find terminator. Premature end of data encountered." ) );
         return( FALSE );
      }
   }

   if ( m_Document != NULL )
   {
      m_Document->ExecuteCallbacks( this );
   }

   // Now that the callbacks have had their shot, let's
   // see if we should abort parsing

   if ( m_AbortParsing != FALSE )
   {
      m_ReportParsingError( TEXT( "Parsing aborted by Callback function." ) );
      return( FALSE );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageElement::RemoveChild( CExtensibleMarkupLanguageElement * element_p )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::RemoveChild()" ) );
   ASSERT( element_p != NULL );

   int loop_index         = 0;
   int number_of_children = m_Children.GetSize();

   while( loop_index < number_of_children )
   {
      if ( m_Children.GetAt( loop_index ) == element_p )
      {
         m_Children.RemoveAt( loop_index );
         return;
      }

      loop_index++;
   }
}

void CExtensibleMarkupLanguageElement::SetAbortParsing( BOOL abort_parsing )
{
   m_AbortParsing = ( abort_parsing == FALSE ) ? FALSE : TRUE;
}

void CExtensibleMarkupLanguageElement::SetContents( const CString& contents )
{
   m_Contents = contents;
}

void CExtensibleMarkupLanguageElement::SetDocument( CExtensibleMarkupLanguageDocument * document_p )
{
   m_Document = document_p;
}

void CExtensibleMarkupLanguageElement::SetTag( const CString& tag_name )
{
   m_Tag = tag_name;
}

void CExtensibleMarkupLanguageElement::SetType( DWORD type )
{
   // Make sure type is a valid type

   switch( type )
   {
      case typeUnknown:
      case typeProcessingInstruction:
      case typeComment:
      case typeCharacterData:
      case typeElement:
      case typeTextSegment:
      case typeMetaData:

         m_Type = type;
         break;

      default:

         m_Type = typeUnknown;
   }
}

void CExtensibleMarkupLanguageElement::WriteTo( CByteArray& xml ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::WriteTo()" ) );

   if ( m_Type == typeUnknown )
   {
      WFCTRACE( TEXT( "Don't know how to write a typeUnknown element" ) );
      return;
   }

   DWORD write_options = WFC_XML_WRITE_AS_ASCII;

   if ( m_Document != NULL )
   {
      write_options = m_Document->GetWriteOptions();
   }

   int loop_index = 0;
   int length     = 0;

   if ( m_Type == typeTextSegment )
   {
      length = m_Contents.GetLength();

      while( loop_index < length )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Contents.GetAt( loop_index ) ) ), write_options,  xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( m_Contents.GetAt( loop_index ) ), write_options,  xml );
#endif
         loop_index++;
      }
   }
   else if ( m_Type == typeMetaData )
   {
      m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '!' ), write_options, xml );

      loop_index = 0;
      length     = m_Tag.GetLength();

      while( loop_index < length )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Tag.GetAt( loop_index ) ) ), write_options, xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( m_Tag.GetAt( loop_index ) ), write_options, xml );
#endif
         loop_index++;
      }

      // Even though we started with a !, we don't end with one

      // MetaData has no attributes

      m_AddCharacterToOutput( TEXT( ' ' ), write_options, xml );

      loop_index = 0;
      length     = m_Contents.GetLength();

      while( loop_index < length )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Contents.GetAt( loop_index ) ) ), write_options,  xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( m_Contents.GetAt( loop_index ) ), write_options,  xml );
#endif

         loop_index++;
      }

      // Now we have to see if we are a DOCTYPE element. If so, we need to
      // reverse the order in which children are added as well as how we are
      // terminated. Yes, this is stupid. Yes, it doesn't fit with the rest
      // of XML syntax. Yes, we have SGML to thank for this.

      if ( m_Contents.GetLength() > 6 && m_Contents.Left( 7 ).Compare( TEXT( "DOCTYPE" ) ) == 0 )
      {
         // Yup, we are a DOCTYPE element

         m_AppendChildren( xml );

         if ( m_Children.GetSize() > 0 )
         {
            m_AddCharacterToOutput( TEXT( ']' ), write_options, xml );
         }

         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );
      }
      else
      {
         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );
         m_AppendChildren( xml );
      }
   }
   else if ( m_Type == typeComment )
   {
      m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '!' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '-' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '-' ), write_options, xml );

      loop_index = 0;
      length     = m_Contents.GetLength();

      while( loop_index < length )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Contents.GetAt( loop_index ) ) ), write_options, xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( m_Contents.GetAt( loop_index ) ), write_options, xml );
#endif
         loop_index++;
      }

      m_AddCharacterToOutput( TEXT( '-' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '-' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );
   }
   else if ( m_Type == typeCharacterData )
   {
      m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '!' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '[' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( 'C' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( 'D' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( 'A' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( 'T' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( 'A' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '[' ), write_options, xml );

      CString temp_string = m_Contents;

      int location_of_string = temp_string.Find( TEXT( "]]>" ) );

      int cdata_index = 0;

      while( location_of_string != (-1) )
      {
         // There's sections that need escaping

         cdata_index = 0;

         while( cdata_index < ( location_of_string + 3 ) )
         {
            // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( temp_string.GetAt( cdata_index ) ) ), write_options, xml );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( temp_string.GetAt( cdata_index ) ), write_options, xml );
#endif
            
            // 1998-09-30 Thanks go to Pei-Chiang Ma (north@uni-scape.com) for
            // finding a bug here. I was incrementing index instead of cdata_index.

            cdata_index++;
         }

         // Now add the escape sequence

         m_AddCharacterToOutput( TEXT( ']' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( ']' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );

         temp_string = temp_string.Right( temp_string.GetLength() - ( location_of_string + 3 ) );

         location_of_string = temp_string.Find( TEXT( "]]>" ) );
      }

      cdata_index = 0;

      while( cdata_index < temp_string.GetLength() )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( temp_string.GetAt( cdata_index ) ) ), write_options, xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( temp_string.GetAt( cdata_index ) ), write_options, xml );
#endif
         cdata_index++;
      }

      m_AddCharacterToOutput( TEXT( ']' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( ']' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '>' ), write_options, xml ); // 1998-12-02 bug fixed by Larry Brendehoeft (Larry.Bredehoeft@sierra.com)
   }
   else if ( m_Type == typeProcessingInstruction )
   {
      // We may be the root of the problem...

      m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '?' ), write_options, xml );

      if ( IsRoot() == TRUE )
      {
         m_AddCharacterToOutput( TEXT( 'x' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'm' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'l' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( ' ' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'v' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'e' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'r' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 's' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'i' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'o' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'n' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '=' ), write_options, xml );

         if ( m_Document == NULL )
         {
            WFCTRACE( TEXT( "m_Document is NULL!" ) );
            xml.RemoveAll();
            return;
         }

         CString temp_string;
         
         m_Document->GetVersion( temp_string );

         if ( temp_string.GetLength() == 0 )
         {
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '1'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '.'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '0'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );
         }
         else
         {
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );

            // We will trust the document to have been set correctly

            loop_index = 0;
            length     = temp_string.GetLength();

            while( loop_index < length )
            {
               // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
               m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( temp_string.GetAt( loop_index ) ) ), write_options, xml );
#else
               m_AddCharacterToOutput( static_cast< DWORD >( temp_string.GetAt( loop_index ) ), write_options, xml );
#endif
               loop_index++;
            }

            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );
         }

         // Now let's see if it has encoding

         m_Document->GetEncoding( temp_string );

         if ( temp_string.GetLength() > 0 )
         {
            m_AddCharacterToOutput( TEXT( ' '  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'e'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'n'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'c'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'o'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'd'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'i'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'n'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'g'  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '='  ), write_options, xml );
            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );

            // We will trust the document to have been set correctly

            loop_index = 0;
            length     = temp_string.GetLength();

            while( loop_index < length )
            {
               // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
               m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( temp_string.GetAt( loop_index ) ) ), write_options, xml );
#else
               m_AddCharacterToOutput( static_cast< DWORD >( temp_string.GetAt( loop_index ) ), write_options, xml );
#endif
               loop_index++;
            }

            m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );
         }

         // Now add the standalone declaration

         m_AddCharacterToOutput( TEXT( ' '  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 's'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 't'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'a'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'n'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'd'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'a'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'l'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'o'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'n'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( 'e'  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '='  ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );

         if ( m_Document->IsStandalone() == TRUE )
         {
            m_AddCharacterToOutput( TEXT( 'y' ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'e' ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 's' ), write_options, xml );
         }
         else
         {
            m_AddCharacterToOutput( TEXT( 'n' ), write_options, xml );
            m_AddCharacterToOutput( TEXT( 'o' ), write_options, xml );
         }

         m_AddCharacterToOutput( TEXT( '\"' ), write_options, xml );
      }
      else
      {
         loop_index = 0;
         length     = m_Contents.GetLength();

         while( loop_index < length )
         {
            // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Contents.GetAt( loop_index ) ) ), write_options, xml );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( m_Contents.GetAt( loop_index ) ), write_options, xml );
#endif
            loop_index++;
         }
      }

      m_AddCharacterToOutput( TEXT( '?' ), write_options, xml );
      m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );

      m_AppendChildren( xml );
   }
   else if ( m_Type == typeElement )
   {
      m_IncrementIndentation();
      m_AddIndentation( xml );

      m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );

      // Add Tag

      loop_index = 0;
      length     = m_Tag.GetLength();

      while( loop_index < length )
      {
         // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
         m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Tag.GetAt( loop_index ) ) ), write_options, xml );
#else
         m_AddCharacterToOutput( static_cast< DWORD >( m_Tag.GetAt( loop_index ) ), write_options, xml );
#endif
         loop_index++;
      }

      m_AppendAttributes( xml );

      if ( m_ShorthandTerminatorDetected != FALSE )
      {
         // Terminated elements have no text fields
         m_AddCharacterToOutput( TEXT( '/' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );
      }
      else
      {
         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );

         loop_index = 0;
         length     = m_Contents.GetLength();

         while( loop_index < length )
         {
            // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Contents.GetAt( loop_index ) ) ), write_options, xml );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( m_Contents.GetAt( loop_index ) ), write_options, xml );
#endif
            loop_index++;
         }

         m_AppendChildren( xml );

         if ( m_Children.GetSize() > 0 )
         {
            CExtensibleMarkupLanguageElement * first_child_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( m_Children.GetAt( 0 ) );

            if ( first_child_p->m_Type != typeTextSegment || m_Children.GetSize() > 1 )
            {
               m_AddIndentation( xml );
            }
         }

         // Now add our closing tag

         m_AddCharacterToOutput( TEXT( '<' ), write_options, xml );
         m_AddCharacterToOutput( TEXT( '/' ), write_options, xml );

         loop_index = 0;
         length     = m_Tag.GetLength();

         while( loop_index < length )
         {
            // CByteArray doesn't have a method to append a lot of bytes all at once
#if ! defined( UNICODE )
            m_AddCharacterToOutput( static_cast< DWORD >( static_cast< BYTE >( m_Tag.GetAt( loop_index ) ) ), write_options, xml );
#else
            m_AddCharacterToOutput( static_cast< DWORD >( m_Tag.GetAt( loop_index ) ), write_options, xml );
#endif
            loop_index++;
         }

         m_AddCharacterToOutput( TEXT( '>' ), write_options, xml );
      }

      m_DecrementIndentation();
   }
}

CExtensibleMarkupLanguageElement& CExtensibleMarkupLanguageElement::operator=( const CExtensibleMarkupLanguageElement& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageElement::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CExtensibleMarkupLanguageElement</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, push technology, Extensible Markup Language, source code">
<META name="description" content="The C++ class that parses and constructs XML elements.">
</HEAD>

<BODY>

<H1>CExtensibleMarkupLanguageElement</H1>
$Revision: 74 $
<HR>

<H2>Description</H2>

This class is the work horse of the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
classes. It does all of the parsing
and outputting the elements that make up an
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
document in a very 
simplistic manner. It does not assume that you are connected to Internet
or that networking even exists (or files for that matter). To parse an
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
document, you must retrieve the document. How this document is retrieved
is left to the caller of this class. This class only parses
what it is given. It will not make any attempts to retrieve data
on its own.

<H2>Construction</H2>

<DL COMPACT>
<DT><PRE>static CExtensibleMarkupLanguageElement *<B><A NAME="NewElement">NewElement</A></B>( CExtensibleMarkupLanguageElement * parent_element = NULL, DWORD type = typeElement, <A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A> * document = NULL )</PRE><DD>
Creates another <B>CExtensibleMarkupLanguageElement</B>.
There is no constructor for this class. If you want
to create a <B>CExtensibleMarkupLanguageElement</B> object you must use <B>NewElement</B>().
The <CODE>type</CODE> parameter
can be one of the following values:<P>
<UL>
<LI><CODE><B>typeUnknown</B></CODE> - We don't know what it is.
<LI><CODE><B>typeProcessingInstruction</B></CODE> - Start Tag is &quot;&lt;?&quot; End Tag is &quot;?&gt;&quot;
<LI><CODE><B>typeComment</B></CODE> - Start Tag is &quot;&lt;!--&quot; End Tag is &quot;--&gt;&quot;
<LI><CODE><B>typeCharacterData</B></CODE> - Start Tag is &quot;&lt;![CDATA[&quot; End Tag is &quot;]]&gt;&quot;
<LI><CODE><B>typeElement</B></CODE> - A user's element
<LI><CODE><B>typeTextSegment</B></CODE> - That which lies between sub-elements
<LI><CODE><B>typeMetaData</B></CODE> -  Anything in a &quot;&lt;!&quot; field that ain't <CODE><B>typeComment</B></CODE> or <CODE><B>typeCharacterData</B></CODE>
</UL>
If the <CODE>document</CODE> parameter is NULL, the newly created
element will inherit the document of the <CODE>parent_element</CODE>.
The newly created element will also have been made a child
of <CODE>parent_element</CODE>.
</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="AddAttribute">AddAttribute</A></B>( const CString&amp; name, const CString&amp; value )</PRE><DD>
Attributes are those parts of an element that ain&#39;t supposed to be data. It
contains meta data (data about data). Sometimes though, people put data into
the attributes. Consider the following sample:
<PRE>&lt;DATE data=&quot;19630502&quot;/&gt;</PRE>
The part <CODE>data=&quot;19630502&quot;</CODE> is considered to be the attribute.
The attribute name is &quot;data&quot; and its value is &quot;19630502&quot;.
It returns TRUE if the attribute was successfully added.

<DT><PRE>void <B><A NAME="AddChild">AddChild</A></B>( CExtensibleMarkupLanguageElement * element_p, DWORD insert_at = (0xFFFFFFFF) )</PRE><DD>
Makes <CODE>element_p</CODE> a child of this element. A copy of
<CODE>element_p</CODE> is <STRONG>not</STRONG> made so don&#39;t send
<B>AddChild</B>() the address of a local variable. Also, the <CODE>element_p</CODE>
will have it&#39;s document member set to the document of this element.
If you set <CODE>insert_at</CODE> to be less than the number of children,
the new child will be added at that location. This allows you to insert
children at a specific location in the list (useful for pretty-text documents
but frivolous for data-centric tasks.)

<DT><PRE>BOOL <B><A NAME="AddText">AddText</A></B>( const CString&amp; text_segment )</PRE><DD>
This method will create a child element of type <CODE><B>typeTextSegment</B></CODE>
and set its contents to <CODE>text_segment</CODE>.

<DT><PRE>void <B><A NAME="Copy">Copy</A></B>( const CExtensibleMarkupLanguageElement&amp; source )</PRE><DD>
Copies the contents of <CODE>source</CODE>. It will copy
all attributes and children of <CODE>source</CODE>.

<DT><PRE>DWORD <B><A NAME="CountChildren">CountChildren</A></B>( const CString&amp; name ) const</PRE><DD>
Returns the number of children by that name.
Consider the following
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> snippet:
<PRE><CODE>&lt;Southpark&gt;
   &lt;Characters&gt;
      &lt;Boy&gt;Cartman&lt;/Boy&gt;
      &lt;Boy&gt;Kenny&lt;/Boy&gt;
      &lt;Boy&gt;Kyle&lt;/Boy&gt;
      &lt;Boy&gt;Stan&lt;/Boy&gt;
   &lt;/Characters&gt;
   &lt;Characters&gt;
      &lt;Girl&gt;Wendy&lt;/Girl&gt;
      &lt;Boy&gt;Chef&lt;/Boy&gt;
      &lt;Girl&gt;Ms. Ellen&lt;/Girl&gt;
   &lt;/Characters&gt;
&lt;/Southpark&gt;</CODE></PRE>
If you wanted to know how many &quot;Girl&quot; children there
are in the second set of characters, you would use a <CODE>name</CODE>
of <CODE>&quot;SouthPark.Characters(1).Girl&quot;</CODE>
If you set the parent/child separator character (via the
<A HREF="CExtensibleMarkupLanguageDocument.htm#SetParentChildSeparatorCharacter">SetParentChildSeparatorCharacter()</A>
method) to a forward slash, you could us a <CODE>name</CODE> of
of <CODE>&quot;SouthPark/Characters(1)/Girl&quot;</CODE>

<DT><PRE>void <B><A NAME="DestroyAttributeByName">DestroyAttributeByName</A></B>( const CString&amp; name )</PRE><DD>
Let's you get rid of a particular attribute.

<DT><PRE>void <B><A NAME="DestroyAttributeByValue">DestroyAttributeByValue</A></B>( const CString&amp; value )</PRE><DD>
Let's you get rid of all attributes with a particular value.

<DT><PRE>void <B><A NAME="DestroyAttributes">DestroyAttributes</A></B>( void )</PRE><DD>
Removes all of the attributes associated with this element.

<DT><PRE>void <B><A NAME="DestroyChildren">DestroyChildren</A></B>( void )</PRE><DD>
Removes all children (this will destroy all grand children too).

<DT><PRE>void <B><A NAME="Dump">Dump</A></B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in debug builds of WFC. It helps in debugging. It will
print the contents of this object in human readable form to <CODE>dump_context</CODE>.

<DT><PRE>void <B><A NAME="Empty">Empty</A></B>( void )</PRE><DD>
Destroys all children and attributes. Empties the tag name and text fields.
It does <STRONG>not</STRONG> reset the parent document
(<B><A HREF="#SetDocument">SetDocument</A></B>())
pointer nor the parent element pointer.

<DT><PRE>BOOL <B><A NAME="EnumerateAttributes">EnumerateAttributes</A></B>( DWORD&amp; enumerator ) const</PRE><DD>
Allows you to enumerate through the attributes. It will initialize
<CODE>enumerator</CODE> and return TRUE if there are any attributes
to enumerate through. It will return FALSE when the number of attributes
is zero (i.e. there ain't no attributes to enumerate).

<DT><PRE>BOOL <B><A NAME="EnumerateChildren">EnumerateChildren</A></B>( DWORD&amp; enumerator ) const</PRE><DD>
Allows you to enumerate through the children. It will initialize
<CODE>enumerator</CODE> and return TRUE if there are any children
to enumerate through. It will return FALSE when the number of children
is zero (i.e. there ain't no children to enumerate).

<DT><PRE>BOOL <B><A NAME="GetAbortParsing">GetAbortParsing</A></B>( void ) const</PRE><DD>
Returns whether you should abort parsing or not. This method is here
so you can abort the parsing of an
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
stream whenever a callback function deems it necessary.

<DT><PRE>BOOL <B><A NAME="GetAttributeByName">GetAttributeByName</A></B>( <A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A>&amp; attribute ) const
BOOL <B>GetAttributeByName</B>( const CString&amp; name, CString&amp; value ) const
<A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A> * <B>GetAttributeByName</B>( const CString&amp; name ) const</PRE><DD>
Retrieves the value of an attribute based on its name. If you retrieve the
<CODE>value</CODE>, you will get the attribute value after all entities
in the string have been resolved. If you retrieve the entire attribute
(in a CExtensibleMarkupLanguageAttribute), the value will not pass through
the entity resolution filter. The reason for this is there is no link between a
<A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A> and a
<A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A>.
Only the <A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A>
knows about entities.

<DT><PRE>BOOL <B><A NAME="GetAttributeByValue">GetAttributeByValue</A></B>( <A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A>&amp; attribute ) const</PRE><DD>
Retrieves a copy of an attribute by its value.

<DT><PRE>void <B><A NAME="GetBeginning">GetBeginning</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point ) const</PRE><DD>
Fills <CODE>parse_point</CODE> with the point at which this element
began in the data stream.

<DT><PRE>CExtensibleMarkupLanguageElement * <B><A NAME="GetChild">GetChild</A></B>( const CString&amp; child_name ) const</PRE><DD>
Returns the child of the given <CODE>child_name</CODE>.
Consider the following
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> snippet:
<PRE><CODE>&lt;Southpark&gt;
   &lt;Characters&gt;
      &lt;Boy&gt;Cartman&lt;/Boy&gt;
      &lt;Boy&gt;Kenny&lt;/Boy&gt;
      &lt;Boy&gt;Kyle&lt;/Boy&gt;
      &lt;Boy&gt;Stan&lt;/Boy&gt;
   &lt;/Characters&gt;
   &lt;Characters&gt;
      &lt;Girl&gt;Wendy&lt;/Girl&gt;
      &lt;Boy&gt;Chef&lt;/Boy&gt;
      &lt;Girl&gt;Ms. Ellen&lt;/Girl&gt;
   &lt;/Characters&gt;
&lt;/Southpark&gt;</CODE></PRE>
To retrieve the element for Cartman, <CODE>child_name</CODE> should
be &quot;Southpark.Characters.Boy&quot; If you want Ms. Ellen (even
though she doesn&#39;s play for the home team) you would use
&quot;Southpark.Characters(1).Girl(1)&quot;
If you set the parent/child separator character (via the
<A HREF="CExtensibleMarkupLanguageDocument.htm#SetParentChildSeparatorCharacter">SetParentChildSeparatorCharacter()</A>
method) to a forward slash, you could us a <CODE>child_name</CODE> of
of &quot;Southpark/Characters(1)/Girl(1)&quot;

<DT><PRE>void <B><A NAME="GetCompleteName">GetCompleteName</A></B>( CString&amp; name ) const</PRE><DD>
This is the inverse to <B><A HREF="#GetChild">GetChild</A></B>().
It will give you the complete path name for this element.

<DT><PRE>void <B><A NAME="GetContents">GetContents</A></B>( CString&amp; contents ) const</PRE><DD>
Retrieves the contents of this element only. It will not resolve
any entities nor will it retrieve the contents of any children elements.
Returns the data (or contents) portion of the element. For example, if the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> element was:
<PRE>&lt;LINE n=&quot;1&quot;&gt;Darmok and Jilad at Tenagara!&lt;/LINE&gt;</PRE>
<B>GetContents</B>() would fill <CODE>contents</CODE> with 
<STRONG>NOTHING!</STRONG> If you want to retrieve 
&quot;Darmok and Jilad at Tenagara!&quot; you will have to call
<B><A HREF="#GetText">GetText</A></B>(). The reason for this is the parser has to support
embedded elements in the text portion of this element. Consider the following:
<PRE>&lt;LINE n=&quot;1&quot;&gt;Darmok and &lt;ITALICS&gt;Jilad&lt;/ITALICS&gt; at Tenagara!&lt;/LINE&gt;</PRE>
Notice there is an embedded element named <CODE>ITALICS</CODE> right in
the middle of a perfectly good text.

<DT><PRE><A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A> * <B><A NAME="GetDocument">GetDocument</A></B>( void ) const</PRE><DD>
Returns the pointer to the parent document.

<DT><PRE>void <B><A NAME="GetEnding">GetEnding</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point ) const</PRE><DD>
Fills <CODE>parse_point</CODE> with the point at which this element
ended in the data stream.

<DT><PRE>void <B><A NAME="GetName">GetName</A></B>( CString&amp; name ) const</PRE><DD>
Gives you the name (and possibly instance number) of this element.

<DT><PRE>BOOL <B><A NAME="GetNextAttribute">GetNextAttribute</A></B>( DWORD&amp; enumerator, <A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A>*&amp; attribute_p ) const</PRE><DD>
Returns TRUE if <CODE>attribute_p</CODE> was filled with an attribute&#39;s pointer.
Returns FALSE (and sets <CODE>attribute_p</CODE> to NULL) when no
attribute has been retrieved.

<DT><PRE>BOOL <B><A NAME="GetNextChild">GetNextChild</A></B>( DWORD&amp; enumerator, CExtensibleMarkupLanguageElement *&amp; element_p ) const</PRE><DD>
Returns TRUE if <CODE>element_p</CODE> was filled with a child's pointer.
Returns FALSE (and sets <CODE>element_p</CODE> to NULL) when no
child has been retrieved.

<DT><PRE>DWORD <B><A NAME="GetNumberOfChildren">GetNumberOfChildren</A></B>( void ) const</PRE><DD>
Returns the number of children this element has. Consider the following
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
snippet:
<PRE><CODE>&lt;Southpark&gt;
   &lt;Characters&gt;
      &lt;Boy&gt;Cartman&lt;/Boy&gt;
      &lt;Boy&gt;Kenny&lt;/Boy&gt;
      &lt;Boy&gt;Kyle&lt;/Boy&gt;
      &lt;Boy&gt;Stan&lt;/Boy&gt;
   &lt;/Characters&gt;
   &lt;Characters&gt;
      &lt;Girl&gt;Wendy&lt;/Girl&gt;
      &lt;Boy&gt;Chef&lt;/Boy&gt;
      &lt;Girl&gt;Ms. Ellen&lt;/Girl&gt;
   &lt;/Characters&gt;
&lt;/Southpark&gt;</CODE></PRE>
If you have the element for Southpark and call <B>GetNumberOfChildren</B>(), it
will return 

<DT><PRE>DWORD <B><A NAME="GetNumberOfAttributes">GetNumberOfAttributes</A></B>( void ) const</PRE><DD>
Returns the number of attributes this element has.

<DT><PRE>CExtensibleMarkupLanguageElement * <B><A NAME="GetParent">GetParent</A></B>( void ) const</PRE><DD>
Returns the pointer to the immediate parent of this element.

<DT><PRE>CExtensibleMarkupLanguageElement * <B>GetParent</B>( const CString&amp; name ) const</PRE><DD>
Returns the parent element that matches <CODE>name</CODE>. The element
returned my be the parent, grand parent or great grand parent.

<DT><PRE>void <B><A NAME="GetTag">GetTag</A></B>( CString&amp; tag ) const</PRE><DD>
Returns the tag value. For example, if the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> element was:
<PRE>&lt;DATE data=&quot;1963-05-02&quot;/&gt;</PRE>
<B>GetTag</B>() will return &quot;DATE&quot;

<DT><PRE>void <B><A NAME="GetText">GetText</A></B>( CString&amp; text_string ) const</PRE><DD>
Retrieves all text segments and resolves all entities in the text.
This parser is very very particular about
whether white-space is holy or not.
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
is for data so we will treat every character in the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
document as though it is data. Consider the following:
<PRE>&lt;WFC&gt;
&lt;AUTHOR&gt;Samuel R. Blackburn
wfc@pobox.com&lt;/AUTHOR&gt;
&lt;/WFC&gt;</PRE>
The WFC element has <I>three</I> children. The first child
is of type <CODE><B>typeTextSegment</B></CODE>
and contains the data between the end of the <CODE>&lt;WFC&gt;</CODE>
tag and the beginning of the <CODE>&lt;AUTHOR&gt;</CODE> tag (i.e.
a new-line character).
The next child is of type <CODE><B>typeElement</B></CODE>
which contains the AUTHOR element. This last child
is of type <CODE><B>typeTextSegment</B></CODE>
which contains the data between the end of the
<CODE>&lt;/AUTHOR&gt;</CODE> tag and the beginning of the
<CODE>&lt;/WFC&gt;</CODE> tag (another new-line character).

<BR>

<STRONG>NOTE:</STRONG> There is one thing you must keep in mind
when calling <B>GetText</B>(). Remember that we have a pointer to our parent
<A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A>.
That parent has a property called <B>IgnoreWhiteSpace</B> and is boolean.
If the user sets that property to TRUE, <B>GetText</B>() will ignore
text segments (<CODE><B>typeTextSegment</B></CODE> child elements) that
contain nothing but space characters.

<DT><PRE>DWORD <B><A NAME="GetTotalNumberOfChildren">GetTotalNumberOfChildren</A></B>( void ) const</PRE><DD>
This tells you how many children this element has plus the number
of children they have and so on and so forth.

<DT><PRE>DWORD <B><A NAME="GetType">GetType</A></B>( void ) const</PRE><DD>
Tells you what type of element this object is. It will return
one of the following values:
<UL>
<LI><CODE><B>typeUnknown</B></CODE> - We don't know what it is.
<LI><CODE><B>typeProcessingInstruction</B></CODE> - Start Tag is &quot;&lt;?&quot; End Tag is &quot;?&gt;&quot;
<LI><CODE><B>typeComment</B></CODE> - Start Tag is &quot;&lt;!--&quot; End Tag is &quot;--&gt;&quot;
<LI><CODE><B>typeCharacterData</B></CODE> - Start Tag is &quot;&lt;![CDATA[&quot; End Tag is &quot;]]&gt;&quot;
<LI><CODE><B>typeElement</B></CODE> - A user's element
<LI><CODE><B>typeTextSegment</B></CODE> - That which lies between sub-elements
<LI><CODE><B>typeMetaData</B></CODE> -  Anything in a &quot;&lt;!&quot; field that ain't <CODE><B>typeComment</B></CODE> or <CODE><B>typeCharacterData</B></CODE>
</UL>

<DT><PRE>BOOL <B><A NAME="IsAllWhiteSpace">IsAllWhiteSpace</A></B>( void ) const</PRE><DD>
Returns TRUE if this is a <CODE><B>typeTextSegment</B></CODE> and
it contains nothing but space-like characters.

<DT><PRE>BOOL <B><A NAME="IsRoot">IsRoot</A></B>( void ) const</PRE><DD>
Returns TRUE if this element is the root element. The root element
holds the data from the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> identifier.
The <A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> identifier line
looks something like this:
<PRE>&lt;?xml version=&quot;1.0&quot;?&gt;</PRE>

<DT><PRE>static CExtensibleMarkupLanguageElement *<B>NewElement</B>( CExtensibleMarkupLanguageElement * parent_element = NULL, DWORD type = typeElement, <A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A> * document = NULL )</PRE><DD>
Creates another <B>CExtensibleMarkupLanguageElement</B>.
There is no constructor for CExtensibleMarkupLanguageElement. If you want
to create a CExtensibleMarkupLanguageElement you must use <B>NewElement</B>().
The <CODE>type</CODE> parameter can be one of the following values:

<P>

<UL>
<LI><CODE><B>typeUnknown</B></CODE> - We don't know what it is.
<LI><CODE><B>typeProcessingInstruction</B></CODE> - Start Tag is &quot;&lt;?&quot; End Tag is &quot;?&gt;&quot;
<LI><CODE><B>typeComment</B></CODE> - Start Tag is &quot;&lt;!--&quot; End Tag is &quot;--&gt;&quot;
<LI><CODE><B>typeCharacterData</B></CODE> - Start Tag is &quot;&lt;![CDATA[&quot; End Tag is &quot;]]&gt;&quot;
<LI><CODE><B>typeElement</B></CODE> - A user's element
<LI><CODE><B>typeTextSegment</B></CODE> - That which lies between sub-elements
<LI><CODE><B>typeMetaData</B></CODE> -  Anything in a &quot;&lt;!&quot; field that ain't <CODE><B>typeComment</B></CODE> or <CODE><B>typeCharacterData</B></CODE>
</UL>
If the <CODE>document</CODE> parameter is NULL, the newly created element
will inherit the document from the <CODE>parent_element</CODE>.

<DT><PRE>BOOL <B><A NAME="Parse">Parse</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; beginning, const <A HREF="CDataParser.htm">CDataParser</A>&amp; parser )</PRE><DD>
Tells the element to start read itself from <CODE>parser</CODE>
starting at the location in <CODE>beginning</CODE>. It returns TRUE if it successfully
parsed (and all of its children successfully parsed).

<DT><PRE>void <B><A NAME="RemoveChild">RemoveChild</A></B>( CExtensibleMarkupLanguageElement * element_p )</PRE><DD>
Removes <CODE>element_p</CODE> from the list of children. It will not
destroy the child. This is the method you would use to steal a child
from one element and give it to another.

<DT><PRE>void <B><A NAME="SetAbortParsing">SetAbortParsing</A></B>( BOOL abort_parsing = TRUE )</PRE><DD>
This sets a flag in the class to abort parsing. This is usually
called from callback functions. When an element is finished parsing,
it is sent to the document's list of callback functions. One of those
callbacks may choose to abort parsing of the document. One example of
why you would want to do this is searching. You would parse the document
until you found what you're looking for then stop parsing the document
(because the document may be very large).

<DT><PRE>void <B><A NAME="SetDocument">SetDocument</A></B>( <A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A> * document_p )</PRE><DD>
Tells the element which
<A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A>
this element belongs to.

<DT><PRE>void <B><A NAME="SetTag">SetTag</A></B>( const CString&amp; tag_name )</PRE><DD>
Sets the tag name.

<DT><PRE>void <B><A NAME="SetType">SetType</A></B>( DWORD element_type )</PRE><DD>
<CODE>element_type</CODE> can be one of the following values:

<P>

<UL>
<LI><CODE><B>typeUnknown</B></CODE> - We don't know what it is.
<LI><CODE><B>typeProcessingInstruction</B></CODE> - Start Tag is &quot;&lt;?&quot; End Tag is &quot;?&gt;&quot;
<LI><CODE><B>typeComment</B></CODE> - Start Tag is &quot;&lt;!--&quot; End Tag is &quot;--&gt;&quot;
<LI><CODE><B>typeCharacterData</B></CODE> - Start Tag is &quot;&lt;![CDATA[&quot; End Tag is &quot;]]&gt;&quot;
<LI><CODE><B>typeElement</B></CODE> - A user's element
<LI><CODE><B>typeTextSegment</B></CODE> - That which lies between sub-elements
<LI><CODE><B>typeMetaData</B></CODE> -  Anything in a &quot;&lt;!&quot; field that ain't <CODE><B>typeComment</B></CODE> or <CODE><B>typeCharacterData</B></CODE>
</UL>

<P>

If <CODE>element_type</CODE> is not one of the above values, the type
will be set to <CODE><B>typeUnknown</B></CODE>.

<DT><PRE>void <B><A NAME="WriteTo">WriteTo</A></B>( CByteArray&amp; destination )</PRE><DD>
Writes the element (and sub-elements) to the byte array in
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> form.

</DL>

<H2>Operators</H2>

<DT><PRE>CExtensibleMarkupLanguageElement&amp; operator <B>=</B> ( const CExtensibleMarkupLanguageElement&amp; source )</PRE><DD>
Basically calls <B><A HREF="#Copy">Copy</A></B>().

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

BOOL contains_id_attribute( <B>CExtensibleMarkupLanguageElement</B> * element_p )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;contains_id_attribute()&quot; ) );

   <A HREF="CExtensibleMarkupLanguageAttribute.htm">CExtensibleMarkupLanguageAttribute</A> * attribute_p = NULL;

   attribute_p = element_p-&gt;<A HREF="#GetAttributeByName">GetAttributeByName</A>( &quot;ID&quot; );

   if ( attribute_p == NULL )
   {
      return( FALSE );
   }

   return( TRUE );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CExtensibleMarkupLanguageElement.cpp $<BR>
$Modtime: 3/12/00 3:49p $

</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CExtensibleMarkupLanguageElement =<m_Tag,s>
#endif
