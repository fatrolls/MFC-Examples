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
** $Workfile: CExtensibleMarkupLanguageDocument.cpp $
** $Revision: 44 $
** $Modtime: 1/17/00 9:01a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

typedef struct _xml_element_callback_entry
{
   CString              name;
   XML_ELEMENT_CALLBACK callback;
   void *               parameter;
}
XML_ELEMENT_CALLBACK_ENTRY, *XML_ELEMENT_CALLBACK_ENTRY_P;

CExtensibleMarkupLanguageDocument::CExtensibleMarkupLanguageDocument()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::CExtensibleMarkupLanguageDocument()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   // Initialize in the same order as in the header file. This makes it
   // easier to debug.

   m_XML = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

   // m_Callbacks is an object and doesn't need initializing
   // m_Entities is an object and doesn't need initializing
   m_IgnoreWhiteSpace     = FALSE;
   m_AutomaticIndentation = FALSE;
   m_IndentationLevel     = 0;
   m_IndentBy             = 0;
   m_ParseOptions         = WFC_XML_IGNORE_MISSING_XML_DECLARATION;
   m_WriteOptions         = WFC_XML_WRITE_AS_ASCII;
   m_IsStandalone         = TRUE;
   m_ParentChildSeparatorCharacter = TEXT( '.' );

   // 1998-08-27 Thanks go to Christopher Remington (chrisr@silversoft.net)
   // for finding where I wasn't intializing m_ParseErrorEncountered.

   m_ParseErrorEncountered = FALSE;

   // m_ErrorElementBeganAt is an object and doesn't need initializing
   // m_ErrorOccuredAt is an object and doesn't need initializing
   // m_ErrorTagName is an object and doesn't need initializing
   // m_ErrorMessage is an object and doesn't need initializing

   m_ConversionCodePage = CP_UTF8;

   OSVERSIONINFO operating_system_version_information;

   ZeroMemory( &operating_system_version_information, sizeof( operating_system_version_information ) );
   operating_system_version_information.dwOSVersionInfoSize = sizeof( operating_system_version_information );

   if ( ::GetVersionEx( &operating_system_version_information ) != FALSE )
   {
      if ( operating_system_version_information.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
      {
         // Piece of crap Windows95 garbage
         m_ConversionCodePage = CP_ACP;
      }
   }

   m_InitializeEntities();
   m_InitializeRootElement();
}

CExtensibleMarkupLanguageDocument::CExtensibleMarkupLanguageDocument( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::CExtensibleMarkupLanguageDocument( CExtensibleMarkupLanguageDocument )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   // Initialize in the same order as in the header file. This makes it
   // easier to debug.

   m_XML = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

   // m_Callbacks is an object and doesn't need initializing
   // m_Entities is an object and doesn't need initializing
   m_IgnoreWhiteSpace     = FALSE;
   m_AutomaticIndentation = FALSE;
   m_IndentationLevel     = 0;
   m_IndentBy             = 0;
   m_ParseOptions         = WFC_XML_IGNORE_MISSING_XML_DECLARATION;
   m_WriteOptions         = WFC_XML_WRITE_AS_ASCII;
   m_IsStandalone         = TRUE;
   m_ParentChildSeparatorCharacter = TEXT( '.' );

   // 1998-08-27 Thanks go to Christopher Remington (chrisr@silversoft.net)
   // for finding where I wasn't intializing m_ParseErrorEncountered.

   m_ParseErrorEncountered = FALSE;

   // m_ErrorElementBeganAt is an object and doesn't need initializing
   // m_ErrorOccuredAt is an object and doesn't need initializing
   // m_ErrorTagName is an object and doesn't need initializing
   // m_ErrorMessage is an object and doesn't need initializing

   m_ConversionCodePage = CP_UTF8;

   OSVERSIONINFO operating_system_version_information;

   ZeroMemory( &operating_system_version_information, sizeof( operating_system_version_information ) );
   operating_system_version_information.dwOSVersionInfoSize = sizeof( operating_system_version_information );

   if ( ::GetVersionEx( &operating_system_version_information ) != FALSE )
   {
      if ( operating_system_version_information.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
      {
         // Piece of crap Windows95 garbage
         m_ConversionCodePage = CP_ACP;
      }
   }

   m_InitializeEntities();
   m_InitializeRootElement();

   // Now that we have a valid object, let's copy someone.

   Copy( source );
}

CExtensibleMarkupLanguageDocument::~CExtensibleMarkupLanguageDocument()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::~CExtensibleMarkupLanguageDocument()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Empty();

   m_IgnoreWhiteSpace      = FALSE;
   m_AutomaticIndentation  = FALSE;
   m_IndentationLevel      = 0;
   m_IndentBy              = 0;
   m_ParseErrorEncountered = FALSE;
   m_ParseOptions          = 0;
   m_WriteOptions          = WFC_XML_WRITE_AS_ASCII;
   m_IsStandalone          = FALSE;
   m_ConversionCodePage    = 0;

   if ( m_XML != NULL )
   {
      CExtensibleMarkupLanguageElement::DeleteElement( m_XML );
      m_XML = NULL;
   }
}

BOOL CExtensibleMarkupLanguageDocument::AddCallback( LPCTSTR element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::AddCallback()" ) );

   if ( element_name == NULL )
   {
      WFCTRACE( TEXT( "Nameless element callbacks not supported" ) );
      return( FALSE );
   }

   if ( element_name[ 0 ] == 0x00 )
   {
      WFCTRACE( TEXT( "Empty element name not supported" ) );
      return( FALSE );
   }

   if ( callback == NULL )
   {
      WFCTRACE( TEXT( "NULL Callback not added" ) );
      return( FALSE );
   }

   // Now go find this entry (to make sure we don't call it twice)

   int loop_index        = 0;
   int number_of_entries = m_Callbacks.GetSize();

   CString name( element_name );

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );

   while( loop_index < number_of_entries )
   {
      entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( loop_index ) );

      if ( entry_p != NULL )
      {
         if ( entry_p->callback  == callback &&
              entry_p->parameter == callback_parameter &&
              name.Compare( entry_p->name ) == 0 )
         {
            return( FALSE );
         }
      }

      loop_index++;
   }

   // If we get here, it means we have a new entry for the list

   try
   {
      entry_p = new XML_ELEMENT_CALLBACK_ENTRY;
   }
   catch( ... )
   {
      entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );
   }

   if ( entry_p == NULL )
   {
      return( FALSE );
   }

   entry_p->callback  = callback;
   entry_p->parameter = callback_parameter;
   entry_p->name      = name;

   m_Callbacks.Add( entry_p );

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageDocument::AddEntity( const CString& entity, const CString& value )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::AddEntity()" ) );

   // First, we must check to see if we allow default entities to be replaced...
   // The default entities are:
   // &amp;
   // &apos;
   // &gt;
   // &lt;
   // &quot;

   if ( m_ParseOptions & WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES )
   {
      // We don't care if default entities are replaced 
      if ( m_Entities.Add( entity, value ) == FALSE )
      {
         return( FALSE );
      }

      return( TRUE );
   }
   else
   {
      // We must check to make sure the default entities aren't replaced

      if ( entity.Compare( TEXT( "&amp;"  ) ) == 0 ||
           entity.Compare( TEXT( "&apos;" ) ) == 0 ||
           entity.Compare( TEXT( "&gt;"   ) ) == 0 ||
           entity.Compare( TEXT( "&lt;"   ) ) == 0 ||
           entity.Compare( TEXT( "&quot;" ) ) == 0 )
      {
         // The user tried to replace a default entity
         return( FALSE );
      }
      else
      {
         if ( m_Entities.Add( entity, value ) == FALSE )
         {
            return( FALSE );
         }

         return( TRUE );
      }
   }
}

void CExtensibleMarkupLanguageDocument::Append( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::Append()" ) );

   if ( m_XML == NULL || source.m_XML == NULL )
   {
      WFCTRACE( TEXT( "an m_XML is NULL!" ) );
      return;
   }

   CExtensibleMarkupLanguageElement * element_to_copy_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
   CExtensibleMarkupLanguageElement * element_to_add_p  = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );

   DWORD enumerator = 0;

   if ( source.m_XML->EnumerateChildren( enumerator ) != FALSE )
   {
      while( source.m_XML->GetNextChild( enumerator, element_to_copy_p ) != FALSE )
      {
         if ( element_to_copy_p != NULL )
         {
            element_to_add_p = CExtensibleMarkupLanguageElement::NewElement( m_XML );

            if ( element_to_add_p == NULL )
            {
               WFCTRACE( TEXT( "Can't create element!" ) );
               return;
            }

            element_to_add_p->Copy( *element_to_copy_p );

            m_XML->AddChild( element_to_add_p );
            element_to_add_p = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
         }
      }
   }
}

void CExtensibleMarkupLanguageDocument::Copy( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::Copy()" ) );

   Empty();

   if ( m_XML == NULL )
   {
      m_XML = CExtensibleMarkupLanguageElement::NewElement( NULL, CExtensibleMarkupLanguageElement::typeProcessingInstruction, this );

      if ( m_XML == NULL )
      {
         WFCTRACE( TEXT( "Can't allocate memory for the document node" ) );
         return;
      }
   }

   if ( source.m_XML != NULL )
   {
      m_XML->Copy( *source.m_XML );
   }
}

void CExtensibleMarkupLanguageDocument::CopyCallbacks( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::CopyCallbacks()" ) );

   m_RemoveAllCallbacks();

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );

   int loop_index        = 0;
   int number_of_entries = source.m_Callbacks.GetSize();

   while( loop_index < number_of_entries )
   {
      entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( loop_index ) );

      if ( entry_p != NULL )
      {
         AddCallback( entry_p->name, entry_p->callback, entry_p->parameter );
      }

      loop_index++;
   }
}

DWORD CExtensibleMarkupLanguageDocument::CountElements( const CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::CopyCallbacks()" ) );

   if ( m_XML != NULL )
   {
      return( m_XML->CountChildren( name ) );
   }

   return( 0 );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CExtensibleMarkupLanguageDocument::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CExtensibleMarkupLanguageDocument at " ) << (VOID *) this << TEXT( "\n{\n" );

   dump_context << TEXT( "      m_IgnoreWhiteSpace is " );

   if ( m_IgnoreWhiteSpace == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "      m_AutomaticIndentation is " );

   if ( m_AutomaticIndentation == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_IndentationLevel is " ) << m_IndentationLevel << TEXT( "\n" );
   dump_context << TEXT( "   m_IndentBy         is " ) << m_IndentBy         << TEXT( "\n" );

   dump_context << TEXT( "   m_XML" );

   if ( m_XML == NULL )
   {
      dump_context << TEXT( " is NULL\n" );
   }
   else
   {
      m_XML->Dump( dump_context );
   }

   dump_context << TEXT( "   m_ParseErrorEncountered is " );

   if ( m_ParseErrorEncountered == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_ParseOptions is " ) << m_ParseOptions << TEXT( "\n" );

   if ( m_ParseOptions > 0 )
   {
      // Some parsing options have been set. Let's break out the bit fields

      dump_context << TEXT( "   {\n" );

      if ( m_ParseOptions & WFC_XML_IGNORE_CASE_IN_XML_DECLARATION )
      {
         dump_context << TEXT( "      WFC_XML_IGNORE_CASE_IN_XML_DECLARATION\n" );
      }

      if ( m_ParseOptions & WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES )
      {
         dump_context << TEXT( "      WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES\n" );
      }

      if ( m_ParseOptions & WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES )
      {
         dump_context << TEXT( "      WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES\n" );
      }

      if ( m_ParseOptions & WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS )
      {
         dump_context << TEXT( "      WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS\n" );
      }

      if ( m_ParseOptions & WFC_XML_IGNORE_MISSING_XML_DECLARATION )
      {
         dump_context << TEXT( "      WFC_XML_IGNORE_MISSING_XML_DECLARATION\n" );
      }

      if ( m_ParseOptions & WFC_XML_DISALLOW_MULTIPLE_ELEMENTS )
      {
         dump_context << TEXT( "      WFC_XML_DISALLOW_MULTIPLE_ELEMENTS\n" );
      }

      if ( m_ParseOptions & WFC_XML_LOOSE_COMMENT_PARSING )
      {
         dump_context << TEXT( "      WFC_XML_LOOSE_COMMENT_PARSING\n" );
      }

      if ( m_ParseOptions & WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS )
      {
         dump_context << TEXT( "      WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS\n" );
      }

      dump_context << TEXT( "   }\n" );
   }

   dump_context << TEXT( "   m_WriteOptions is " ) << m_WriteOptions << TEXT( "\n" );

   if ( m_WriteOptions > 0 )
   {
      // Some parsing options have been set. Let's break out the bit fields

      dump_context << TEXT( "   {\n" );

      if ( m_ParseOptions & WFC_XML_INCLUDE_TYPE_INFORMATION )
      {
         dump_context << TEXT( "      WFC_XML_INCLUDE_TYPE_INFORMATION\n" );
      }

      if ( m_ParseOptions & WFC_XML_DONT_OUTPUT_XML_DECLARATION )
      {
         dump_context << TEXT( "      WFC_XML_DONT_OUTPUT_XML_DECLARATION\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_UNICODE )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_UNICODE\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_ASCII )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_ASCII\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_UCS4 )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_UCS4\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143 )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412 )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412\n" );
      }

      if ( m_ParseOptions & WFC_XML_WRITE_AS_UTF8 )
      {
         dump_context << TEXT( "      WFC_XML_WRITE_AS_UTF8\n" );
      }

      dump_context << TEXT( "   }\n" );
   }

   dump_context << TEXT( "   m_Version      is " ) << m_Version  << TEXT( "\n" );
   dump_context << TEXT( "   m_Encoding     is " ) << m_Encoding << TEXT( "\n" );
   dump_context << TEXT( "   m_IsStandalone is " );

   if ( m_IsStandalone == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_ParentChildSeparatorCharacter is " ) << m_ParentChildSeparatorCharacter << TEXT( "\n" );
   dump_context << TEXT( "   m_ErrorTagName is " ) << m_ErrorTagName << TEXT( "\n" );

   dump_context << TEXT( "   m_ErrorElementBeganAt is " );
   //m_ErrorElementBeganAt.Dump( dump_context );

   dump_context << TEXT( "   m_ErrorOccuredAt is " );
   //m_ErrorOccuredAt.Dump( dump_context );

   dump_context << TEXT( "   m_ErrorMessage is " ) << m_ErrorMessage << TEXT( "\n" );

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CExtensibleMarkupLanguageDocument::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::Empty()" ) );

   m_RemoveAllCallbacks();
   m_Entities.Empty();

   m_ParseErrorEncountered = FALSE;
   m_ErrorElementBeganAt.Empty();
   m_ErrorOccuredAt.Empty();
   m_ErrorTagName.Empty();
   m_ErrorMessage.Empty();

   if ( m_XML != NULL )
   {
      CExtensibleMarkupLanguageElement::DeleteElement( m_XML );
      m_XML = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
   }

   m_IgnoreWhiteSpace = FALSE;
   m_ParseOptions     = WFC_XML_IGNORE_MISSING_XML_DECLARATION;
   m_WriteOptions     = 0;

   // Things from XMLDecl
   m_Encoding.Empty();
   m_IsStandalone = TRUE;
   m_Version.Empty();

   m_InitializeEntities();
   m_InitializeRootElement();
}

BOOL CExtensibleMarkupLanguageDocument::EnumerateCallbacks( DWORD& enumerator ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::EnumerateCallbacks()" ) );

   enumerator = 0;

   if ( m_Callbacks.GetSize() == 0 )
   {
      // There aren't any callbacks to enumerate
      return( FALSE );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageDocument::ExecuteCallbacks( CExtensibleMarkupLanguageElement * element_p ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::ExecuteCallbacks()" ) );

   if ( element_p == NULL )
   {
      WFCTRACE( TEXT( "Can't pass NULL!" ) );
      return;
   }

   int loop_index          = 0;
   int number_of_callbacks = m_Callbacks.GetSize();

   CString tag;

   try
   {
      element_p->GetTag( tag );
   }
   catch( ... )
   {
      return;
   }

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = NULL;

   while( loop_index < number_of_callbacks )
   {
      try
      {
         entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( loop_index ) );

         if ( entry_p != NULL )
         {
            if ( tag.Compare( entry_p->name ) == 0 )
            {
               // We found a callback

               entry_p->callback( entry_p->parameter, element_p );
            }
         }
      }
      catch( ... )
      {
         // Do Nothing
      }

      loop_index++;
   }
}

void CExtensibleMarkupLanguageDocument::GetAutomaticIndentation( BOOL& automatically_indent, DWORD& indentation_level, DWORD& indent_by )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::GetAutomaticIndentation()" ) );

   automatically_indent = m_AutomaticIndentation;
   indentation_level    = m_IndentationLevel;
   indent_by            = m_IndentBy;
}

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageDocument::GetElement( const CString& element_name ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::GetElement()" ) );

   if ( m_XML == NULL )
   {
      return( NULL );
   }

   // The element_name is in the form of "Parent(0).Child(1)"

   return( m_XML->GetChild( element_name ) );
}

void CExtensibleMarkupLanguageDocument::GetEncoding( CString& encoding ) const
{
   if ( m_WriteOptions & WFC_XML_WRITE_AS_UNICODE )
   {
      encoding = TEXT( "UTF-16" );
   }
   else
   {
      encoding = m_Encoding;
   }
}

const CExtensibleMarkupLanguageEntities& CExtensibleMarkupLanguageDocument::GetEntities( void ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::GetEntities()" ) );
   return( m_Entities );
}

BOOL CExtensibleMarkupLanguageDocument::GetIgnoreWhiteSpace( void ) const
{
   return( ( m_IgnoreWhiteSpace == FALSE ) ? FALSE : TRUE );
}

BOOL CExtensibleMarkupLanguageDocument::GetNextCallback( DWORD& enumerator, CString& element_name, XML_ELEMENT_CALLBACK& callback, void *& parameter ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::GetNextCallback()" ) );

   if ( enumerator >= static_cast< DWORD >( m_Callbacks.GetSize() ) )
   {
      element_name.Empty();
      callback = reinterpret_cast< XML_ELEMENT_CALLBACK >( NULL );
      parameter = NULL;

      return( FALSE );
   }

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = NULL;

   entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( enumerator ) );

   enumerator++;

   if ( entry_p == NULL )
   {
      return( FALSE );
   }

   element_name = entry_p->name;
   callback     = entry_p->callback;
   parameter    = entry_p->parameter;

   return( TRUE );
}

DWORD CExtensibleMarkupLanguageDocument::GetNumberOfElements( void ) const
{
   if ( m_XML == NULL )
   {
      return( 0 );
   }

   return( m_XML->GetTotalNumberOfChildren() );
}

TCHAR CExtensibleMarkupLanguageDocument::GetParentChildSeparatorCharacter( void ) const
{
   return( m_ParentChildSeparatorCharacter );
}

DWORD CExtensibleMarkupLanguageDocument::GetParseOptions( void ) const
{
   return( m_ParseOptions );
}

void CExtensibleMarkupLanguageDocument::GetParsingErrorInformation( CString& tag_name, CParsePoint& beginning, CParsePoint& error_location, CString * error_message_p ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::GetParsingErrorInformation()" ) );

   tag_name = m_ErrorTagName;
   beginning.Copy( m_ErrorElementBeganAt );
   error_location.Copy( m_ErrorOccuredAt );

   if ( error_message_p != NULL )
   {
      // We were passed a pointer by the user, don't trust it

      try
      {
         *error_message_p = m_ErrorMessage;
      }
      catch( ... )
      {
         // Do Nothing
      }
   }
}

CExtensibleMarkupLanguageElement * CExtensibleMarkupLanguageDocument::GetRootElement( void ) const
{
   return( m_XML );
}

void CExtensibleMarkupLanguageDocument::GetVersion( CString& version ) const
{
   version = m_Version;
}

DWORD CExtensibleMarkupLanguageDocument::GetWriteOptions( void ) const
{
   return( m_WriteOptions );
}

BOOL CExtensibleMarkupLanguageDocument::IsStandalone( void ) const
{
   return( m_IsStandalone );
}

void CExtensibleMarkupLanguageDocument::m_InitializeEntities( void )
{
   if ( m_Entities.GetSize() > 0 )
   {
      m_Entities.Empty();
   }

   // Add the internal entities listed in section 4.6 of REC-xml-19980210
   m_Entities.Add( TEXT( "&amp;"  ), TEXT( "&"  ) );
   m_Entities.Add( TEXT( "&apos;" ), TEXT( "'"  ) );
   m_Entities.Add( TEXT( "&gt;"   ), TEXT( ">"  ) );
   m_Entities.Add( TEXT( "&lt;"   ), TEXT( "<"  ) );
   m_Entities.Add( TEXT( "&quot;" ), TEXT( "\"" ) );
}

void CExtensibleMarkupLanguageDocument::m_InitializeRootElement( void )
{
   if ( m_XML != reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL ) )
   {
      CExtensibleMarkupLanguageElement::DeleteElement( m_XML );
      m_XML = reinterpret_cast< CExtensibleMarkupLanguageElement * >( NULL );
   }

   m_XML = CExtensibleMarkupLanguageElement::NewElement( NULL, CExtensibleMarkupLanguageElement::typeProcessingInstruction, this );
}

void CExtensibleMarkupLanguageDocument::m_RemoveAllCallbacks( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::m_RemoveAllCallbacks()" ) );

   int loop_index        = 0;
   int number_of_entries = m_Callbacks.GetSize();

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );

   while( loop_index < number_of_entries )
   {
      entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( loop_index ) );
      m_Callbacks.SetAt( loop_index, NULL );

      if ( entry_p != NULL )
      {
         WFCTRACEVAL( TEXT( "Removing callback for " ), entry_p->name );
         delete entry_p;
         entry_p = NULL;
      }

      loop_index++;
   }

   m_Callbacks.RemoveAll();
}

BOOL CExtensibleMarkupLanguageDocument::Parse( CDataParser& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::Parse( CDataParser )" ) );

   m_ParseErrorEncountered = FALSE;
   m_ErrorElementBeganAt.Empty();
   m_ErrorOccuredAt.Empty();
   m_ErrorTagName.Empty();
   m_ErrorMessage.Empty();

   if ( m_XML == NULL )
   {
      m_XML = CExtensibleMarkupLanguageElement::NewElement( NULL, CExtensibleMarkupLanguageElement::typeProcessingInstruction, this );

      if ( m_XML == NULL )
      {
         WFCTRACE( TEXT( "Can't allocate memory for the document node" ) );
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Can't allocate memory." );
         return( FALSE );
      }
   }

   if ( source.GetSize() < 4 )
   {
      // The minimum size of an XML document is 4 bytes (<a/>)
      m_ParseErrorEncountered = TRUE;
      m_ErrorMessage = TEXT( "Too few bytes to parse." );
      return( FALSE );
   }

   // Here's where we look for the <?xml tag

   CParsePoint parse_point;

   // See if the FEFF or FFFE tags are present

   if ( source.GetAt( 0 ) == 0xFE )
   {
      if ( source.GetAt( 1 ) == 0xFF )
      {
         // We found the 0xFEFF tag.
         // That means it is UTF-16 Big Endian

         source.SetTextToASCII( FALSE );
         source.SetTextToBigEndian( TRUE );
      }
      else
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Second character of Byte Order Mark is invalid for UTF-16 Big Endian (Appendix F)." );
         return( FALSE );
      }

      // Skip the first two characters
      parse_point.SetIndex( 2 );
   }
   else if ( source.GetAt( 0 ) == 0xFF )
   {
      if ( source.GetAt( 1 ) == 0xFE )
      {
         // We found the 0xFFFE tag.
         // That means it is UTF-16 Little Endian

         source.SetTextToASCII( FALSE );
         source.SetTextToBigEndian( FALSE );
      }
      else
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Second character of Byte Order Mark is invalid for UTF-16 Little Endian (Appendix F)." );
         return( FALSE );
      }

      // Skip the first two characters
      parse_point.SetIndex( 2 );
   }
   else
   {
      // Now it gets a little more interesting

      BYTE byte_1 = source.GetAt( 0 );
      BYTE byte_2 = source.GetAt( 1 );
      BYTE byte_3 = source.GetAt( 2 );
      BYTE byte_4 = source.GetAt( 3 );

      if ( byte_1 == 0x3C && byte_2 == 0x3F )
      {
         // Plain old ASCII
         source.SetTextToASCII( TRUE );
      }
      else if ( byte_1 == 0x00 && byte_2 == 0x3C &&
                byte_3 == 0x00 && byte_4 == 0x3F )
      {
         // UTF-16, Big Endian
         source.SetTextToASCII( FALSE );
         source.SetTextToBigEndian( TRUE );

         // Don't autoincrement parse_point
      }
      else if ( byte_1 == 0x3C && byte_2 == 0x00 &&
                byte_3 == 0x3F && byte_4 == 0x00 )
      {
         // UTF-16, Little Endian
         source.SetTextToASCII( FALSE );
         source.SetTextToBigEndian( FALSE );

         // Don't autoincrement parse_point
      }
      else if ( byte_1 == 0x00 &&
                byte_2 == 0x00 &&
                byte_3 == 0x00 &&
                byte_4 == 0x3C )
      {
         // UCS-4 Big Endian
         source.SetTextToUCS4( TRUE );
         source.SetUCS4Order( 1234 );
      }
      else if ( byte_1 == 0x3C &&
                byte_2 == 0x00 &&
                byte_3 == 0x00 &&
                byte_4 == 0x00 )
      {
         // UCS-4 Little Endian
         source.SetTextToUCS4( TRUE );
         source.SetUCS4Order( 4321 );
      }
      else if ( byte_1 == 0x00 &&
                byte_2 == 0x00 &&
                byte_3 == 0x3C &&
                byte_4 == 0x00 )
      {
         // UCS-4 Unusual
         source.SetTextToUCS4( TRUE );
         source.SetUCS4Order( 2143 );
      }
      else if ( byte_1 == 0x00 &&
                byte_2 == 0x3C &&
                byte_3 == 0x00 &&
                byte_4 == 0x00 )
      {
         // UCS-4 Unusual
         source.SetTextToUCS4( TRUE );
         source.SetUCS4Order( 3412 );
      }
      else if ( byte_1 == 0x3C )
      {
         // We'll just default to ASCII
         source.SetTextToASCII( TRUE );
      }
      else
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Can't determine Character Encoding (Appendix F)." );
         return( FALSE );
      }
   }

   CParsePoint beginning_of_tag;
   CParsePoint end_of_tag;

   // Now skip leading spaces until we get to a less-than sign.
   // This according to Rule 1->27->3

   DWORD character_to_test = source.PeekCharacter( parse_point, 0 );

   while( ::is_xml_white_space( character_to_test ) != FALSE )
   {
      parse_point.AutoIncrement( (BYTE)( character_to_test ) );

      if ( source.PeekAtCharacter( parse_point, character_to_test, 0 ) == FALSE )
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Document is all white space (Rule 1)." );
         return( FALSE );
      }
   }

   // See if the first 5 chracters are <?xml

   BOOL xml_declaration_found         = FALSE;
   BOOL xml_declaration_is_mixed_case = FALSE;

   if (   source.PeekCharacter( parse_point, 0 ) == TEXT( '<' )   &&
          source.PeekCharacter( parse_point, 1 ) == TEXT( '?' )   &&
        ( source.PeekCharacter( parse_point, 2 ) == TEXT( 'x' )   ||
          source.PeekCharacter( parse_point, 2 ) == TEXT( 'X' ) ) &&
        ( source.PeekCharacter( parse_point, 3 ) == TEXT( 'm' )   ||
          source.PeekCharacter( parse_point, 3 ) == TEXT( 'M' ) ) &&
        ( source.PeekCharacter( parse_point, 4 ) == TEXT( 'l' )   ||
          source.PeekCharacter( parse_point, 4 ) == TEXT( 'L' ) ) )
   {
      beginning_of_tag.Copy( parse_point );
      xml_declaration_found = TRUE;

      if ( source.PeekCharacter( parse_point, 2 ) != TEXT( 'x' ) ||
           source.PeekCharacter( parse_point, 3 ) != TEXT( 'm' ) ||
           source.PeekCharacter( parse_point, 4 ) != TEXT( 'l' ) )
      {
         xml_declaration_is_mixed_case = TRUE;
      }
   }
   else
   {
      if ( source.PeekCharacter( parse_point, 0 ) != TEXT( '<' ) )
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "First non-space character is not '<' (Rule 1)." );
         return( FALSE );
      }
   }

   // According to REC-xml-19980210 Rule 23, the beginning of an XML document
   // is at the "<?xml" tag. Notice this is lower case!

   if ( xml_declaration_found == TRUE )
   {
      // See if it is lower case

      if ( xml_declaration_is_mixed_case != FALSE &&
         ! ( m_ParseOptions & WFC_XML_IGNORE_CASE_IN_XML_DECLARATION ) )
      {
         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "XML Declaration is not lower case (Rule 23)." );
         return( FALSE );
      }

      // If we get here, it means we've got an XML declaration
      // Just break out of the if...
   }
   else
   {
      // If we get here, it means we don't have an XML declaration but we
      // do have something that starts with '<'

      if ( m_ParseOptions & WFC_XML_IGNORE_MISSING_XML_DECLARATION )
      {
         WFCTRACE( TEXT( "Skipping the missing XML declaration" ) );

         if ( m_XML == NULL )
         {
            m_InitializeRootElement();
         }

         if ( m_XML != NULL )
         {
            m_XML->SetContents( TEXT( "xml version=\"1.0\" standalone=\"yes\"" ) );
            m_XML->AddAttribute( TEXT( "version"    ), TEXT( "1.0" ) );
            m_XML->AddAttribute( TEXT( "standalone" ), TEXT( "yes" ) );
            SetVersion( TEXT( "1.0" ) );
            SetStandalone( TRUE );
         }

         // OK, the XML declaration is missing, this is bad but allowable under
         // the specification. Let's just use the default set in the constructors.

         CExtensibleMarkupLanguageElement * child_element_p = (CExtensibleMarkupLanguageElement *) NULL;

         beginning_of_tag.Copy( parse_point );

         DWORD character = 0;

         while( beginning_of_tag.GetIndex() < source.GetSize() )
         {
            character = source.PeekCharacter( beginning_of_tag, 0 );

            if ( character != TEXT( '<' ) )
            {
               child_element_p = CExtensibleMarkupLanguageElement::NewElement( m_XML, CExtensibleMarkupLanguageElement::typeTextSegment, this );
            }
            else
            {
               child_element_p = CExtensibleMarkupLanguageElement::NewElement( m_XML, CExtensibleMarkupLanguageElement::typeElement, this );
            }

            if ( child_element_p == NULL )
            {
               WFCTRACE( TEXT( "Can't allocate memory for another element" ) );
               m_XML->DestroyChildren();
               return( FALSE );
            }

            if ( child_element_p->Parse( beginning_of_tag, source ) == FALSE )
            {
               WFCTRACE( TEXT( "Parse failed." ) );
               m_XML->DestroyChildren();
               return( FALSE );
            }

            child_element_p->GetEnding( beginning_of_tag );
         }

         return( TRUE );
      }
      else
      {
         // We still failed

         m_ParseErrorEncountered = TRUE;
         m_ErrorMessage = TEXT( "Can't find beginning-of-XML tag (<?xml) regardless of case." );
         return( FALSE );
      }
   }

   // If we get here, it means we are parsing starting at an XML declaration

   WFCTRACEVAL( TEXT( "Found beginning at byte " ), beginning_of_tag.GetIndex() );
   WFCTRACEVAL( TEXT( "Line " ), beginning_of_tag.GetLineNumber() );
   WFCTRACEVAL( TEXT( "Column " ), beginning_of_tag.GetLineIndex() );

   if ( source.Find( beginning_of_tag, TEXT( "?>" ), end_of_tag ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find ?>" ) );
      m_ParseErrorEncountered = TRUE;
      m_ErrorMessage = TEXT( "Can't find the end of the end of the beginning-of-XML tag (?>)." );
      return( FALSE );
   }

   if ( m_XML == NULL )
   {
      WFCTRACE( TEXT( "m_XML is NULL!" ) );
      m_ParseErrorEncountered = TRUE;
      m_ErrorMessage = TEXT( "Internal error : m_XML is NULL." );
      return( FALSE );
   }

   if ( m_XML->Parse( beginning_of_tag, source ) == FALSE )
   {
      WFCTRACE( TEXT( "m_XML - Can't parse" ) );

      // m_ParseErrorEncountered and m_ErrorMessag are set by the m_XML->Parse() call
      // so we don't need to fill them in here.

      m_XML->DestroyAttributes();
      m_XML->SetContents( TEXT( "xml version=\"1.0\" standalone=\"yes\"" ) );
      m_XML->AddAttribute( TEXT( "version"    ), TEXT( "1.0" ) );
      m_XML->AddAttribute( TEXT( "standalone" ), TEXT( "yes" ) );

      return( FALSE );
   }

   // Now let's see if the user wants to make the parser more useless

   if ( m_ParseOptions & WFC_XML_DISALLOW_MULTIPLE_ELEMENTS )
   {
      DWORD element_enumerator = 0;

      if ( m_XML->EnumerateChildren( element_enumerator ) == TRUE )
      {
         CExtensibleMarkupLanguageElement * child_p = (CExtensibleMarkupLanguageElement *) NULL;

         DWORD element_count = 0;

         while( m_XML->GetNextChild( element_enumerator, child_p ) == TRUE )
         {
            if ( child_p->GetType() == CExtensibleMarkupLanguageElement::typeElement )
            {
               // We have more than one element, that is. strictly speaking, a bad thing
               // but having more than one element is so much more useful. Never mind that.
               // The spec says to error out. So we will...

               element_count++;

               if ( element_count > 1 )
               {
                  m_ParseErrorEncountered = TRUE;
                  m_ErrorMessage          = TEXT( "There can be only one element (Rule 1)." );
                  child_p->GetBeginning( m_ErrorElementBeganAt );
                  m_ErrorOccuredAt.Copy( m_ErrorElementBeganAt );
                  child_p->GetTag( m_ErrorTagName );

                  return( FALSE );
               }
            }
         }

      }
   }

   WFCTRACEVAL( TEXT( "?xml began at line " ), beginning_of_tag.GetLineNumber() );
   WFCTRACEVAL( TEXT( "Column " ), beginning_of_tag.GetLineIndex() );
   WFCTRACEVAL( TEXT( "And ended at line " ), end_of_tag.GetLineNumber() );
   WFCTRACEVAL( TEXT( "Column " ), end_of_tag.GetLineIndex() );

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageDocument::RemoveCallback( const char * element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::RemoveCallback()" ) );
   // Now go find this entry (to make sure we don't call it twice)

   int loop_index        = 0;
   int number_of_entries = m_Callbacks.GetSize();

   CString name( element_name );

   XML_ELEMENT_CALLBACK_ENTRY_P entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );

   while( loop_index < number_of_entries )
   {
      entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( m_Callbacks.GetAt( loop_index ) );

      if ( entry_p != NULL )
      {
         if ( entry_p->callback  == callback &&
              entry_p->parameter == callback_parameter &&
              name.Compare( entry_p->name ) == 0 )
         {
            m_Callbacks.SetAt( loop_index, NULL );
            delete entry_p;
            entry_p = reinterpret_cast< XML_ELEMENT_CALLBACK_ENTRY_P >( NULL );
            number_of_entries--;
            loop_index--;
         }
      }

      loop_index++;
   }

   return( TRUE );
}

BOOL CExtensibleMarkupLanguageDocument::ResolveEntity( const CString& entity, CString& resolved_to ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::ResolveEntity()" ) );

   if ( m_Entities.Resolve( entity, resolved_to ) == FALSE )
   {
      return( FALSE );
   }

   return( TRUE );
}

void CExtensibleMarkupLanguageDocument::SetAutomaticIndentation( BOOL automatically_indent, DWORD indentation_level, DWORD indent_by )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::SetAutomaticIndentation()" ) );

   m_AutomaticIndentation = automatically_indent;
   m_IndentationLevel     = indentation_level;
   m_IndentBy             = indent_by;
}

void CExtensibleMarkupLanguageDocument::SetConversionCodePage( DWORD new_page )
{
   m_ConversionCodePage = new_page;
}

void CExtensibleMarkupLanguageDocument::SetEncoding( LPCTSTR encoding )
{
   m_Encoding = encoding;
}

BOOL CExtensibleMarkupLanguageDocument::SetIgnoreWhiteSpace( BOOL new_setting )
{
   BOOL return_value = ( m_IgnoreWhiteSpace == FALSE ) ? FALSE : TRUE;

   if ( new_setting == FALSE )
   {
      m_IgnoreWhiteSpace = FALSE;
   }
   else
   {
      m_IgnoreWhiteSpace = TRUE;
   }

   return( return_value );
}

BOOL CExtensibleMarkupLanguageDocument::SetParentChildSeparatorCharacter( TCHAR separator )
{
   if ( separator == NULL )
   {
      return( FALSE );
   }

   m_ParentChildSeparatorCharacter = separator;

   return( TRUE );
}

DWORD CExtensibleMarkupLanguageDocument::SetParseOptions( DWORD new_options )
{
   DWORD return_value = m_ParseOptions;

   m_ParseOptions = new_options;

   return( return_value );
}

void CExtensibleMarkupLanguageDocument::SetParsingErrorInformation( const CString& tag_name, const CParsePoint& beginning, const CParsePoint& error_location, LPCTSTR error_message )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::SetParsingErrorInformation()" ) );

   if ( m_ParseErrorEncountered == FALSE )
   {
      m_ParseErrorEncountered = TRUE;
      m_ErrorTagName          = tag_name;
      m_ErrorElementBeganAt.Copy( beginning );
      m_ErrorOccuredAt.Copy( error_location );

      if ( error_message == NULL )
      {
         m_ErrorMessage.Empty();
      }
      else
      {
         m_ErrorMessage = error_message;
      }
   }
}

void CExtensibleMarkupLanguageDocument::SetStandalone( BOOL standalone )
{
   m_IsStandalone = ( standalone == FALSE ) ? FALSE : TRUE;
}

void CExtensibleMarkupLanguageDocument::SetVersion( LPCTSTR version )
{
   m_Version = version;
}

DWORD CExtensibleMarkupLanguageDocument::SetWriteOptions( DWORD new_options )
{
   DWORD return_value = m_WriteOptions;

   m_WriteOptions = new_options;

   return( return_value );
}

void CExtensibleMarkupLanguageDocument::WriteTo( CByteArray& destination ) const
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::WriteTo( CByteArray )" ) );

   if ( m_XML == NULL )
   {
      WFCTRACE( TEXT( "Root element is NULL." ) );
      return;
   }

   if ( m_WriteOptions & WFC_XML_DONT_OUTPUT_XML_DECLARATION )
   {
      // The user doesn't want to write the XML declaration. Just write
      // the children.

      DWORD enumerator = 0;

      if ( m_XML->EnumerateChildren( enumerator ) != FALSE )
      {
         CExtensibleMarkupLanguageElement * child_p = (CExtensibleMarkupLanguageElement *) NULL;

         while( m_XML->GetNextChild( enumerator, child_p ) != FALSE )
         {
            if ( child_p != NULL )
            {
               child_p->WriteTo( destination );
            }
         }
      }
      else
      {
         WFCTRACE( TEXT( "No children to enumerate and thusly write." ) );
      }
   }
   else
   {
      // See if the user wants to write as UNICODE or not

      if ( m_WriteOptions & WFC_XML_WRITE_AS_UNICODE )
      {
         if ( m_WriteOptions & WFC_XML_WRITE_AS_BIG_ENDIAN )
         {
            // Write UTF-16 Big Endian as specified in Appendix F
            destination.Add( 0xFE );
            destination.Add( 0xFF );
         }
         else
         {
            destination.Add( 0xFF );
            destination.Add( 0xFE );
         }
      }

      m_XML->WriteTo( destination );
   }

#if defined( _UNICODE )

   if ( ! ( m_WriteOptions & WFC_XML_WRITE_AS_UNICODE ) )
   {
      // We need to convert Unicode to ASCII

      int size_of_buffer = 0;

      UINT code_page = CP_UTF8;

      OSVERSIONINFO operating_system_version_information;

      ZeroMemory( &operating_system_version_information, sizeof( operating_system_version_information ) );
      operating_system_version_information.dwOSVersionInfoSize = sizeof( operating_system_version_information );

      if ( ::GetVersionEx( &operating_system_version_information ) != FALSE )
      {
         if ( operating_system_version_information.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
         {
            // Piece of crap Windows95 garbage
            code_page = CP_ACP;
         }
      }

      size_of_buffer = ::WideCharToMultiByte( m_ConversionCodePage,
                                              0,
                                              (const WCHAR *) destination.GetData(),
                                              destination.GetSize(),
                                              NULL,
                                              0,
                                              NULL,
                                              NULL );

      if ( size_of_buffer == 0 )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Failed to determine size of conversion buffer." ) );
         destination.RemoveAll();
         return;
      }

      CByteArray conversion_buffer;

      conversion_buffer.SetSize( size_of_buffer );

      if ( ::WideCharToMultiByte ( CP_UTF8,
                                   0,
                                   (const WCHAR *)  destination.GetData(),
                                   destination.GetSize() / 2,
                                   (char *) conversion_buffer.GetData(),
                                   conversion_buffer.GetSize(),
                                   NULL,
                                   NULL ) == 0 )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "Failed to convert." ) );
         destination.RemoveAll();
         return;
      }

      destination.Copy( conversion_buffer );
   }

#endif // _UNICODE
}

CExtensibleMarkupLanguageDocument& CExtensibleMarkupLanguageDocument::operator=( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::operator=()" ) );
   Copy( source );
   return( *this );
}

CExtensibleMarkupLanguageDocument& CExtensibleMarkupLanguageDocument::operator+=( const CExtensibleMarkupLanguageDocument& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageDocument::operator+=()" ) );
   Append( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CExtensibleMarkupLanguageDocument</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, push technology, source code">
<META name="description" content="The C++ class that parses and constructs XML documents.">
</HEAD>

<BODY>

<H1>CExtensibleMarkupLanguageDocument</H1>
$Revision: 44 $
<HR>

<H2>Description</H2>

This class is the mother of all
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
classes. It holds the
things like the element tree and settings that apply to
the entire document. It is designed to help application developers
handle XML-like data. It will parse (and construct) well formed,
standalone XML documents. It will also allow you to loosen the 
parsing rules when dealing with XML from sources you can't control.

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE><B>CExtensibleMarkupLanguageDocument</B>()
<B>CExtensibleMarkupLanguageDocument</B>( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Creates another <B>CExtensibleMarkupLanguageDocument</B>.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="AddCallback">AddCallback</A></B>( const char * element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter )</PRE><DD>
Allows you to specify a function (and a parameter for that function) that
will be called when an element with a tag matching <CODE>element_name</CODE>
has been successfully parsed. The <CODE>element_name</CODE> comparison
is not case sensitive.

<DT><PRE>void <B><A NAME="Append">Append</A></B>( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Appends the elements of <CODE>source</CODE> to this document.

<DT><PRE>void <B><A NAME="Copy">Copy</A></B>( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Copies the contents of <CODE>source</CODE> to this object. It will not
copy the callback functions as this may cause unintentional results.

<DT><PRE>void <B><A NAME="CopyCallbacks">CopyCallbacks</A></B>( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Copies the callback functions from <CODE>source</CODE> to this object.
If you are a careful programmer, this is perfectly safe to do. Generally
speaking, you shouldn&#39;t have to copy the callbacks of <CODE>source</CODE>
because parsing should have already taken place.

<DT><PRE>DWORD <B><A NAME="CountElements">CountElements</A></B>( const CString&amp; element_name ) const</PRE><DD>
Counts the number of elements. <CODE>element_name</CODE> takes much the
same form as used in the <B><A HREF="#GetElement">GetElement()</A></B> method.
Consider the following
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
If you wanted to know how many &quot;Boy&quot; elements there
are in the first set of characters, you would use an element name
of <CODE>&quot;SouthPark.Characters&quot;</CODE> If you wanted to
know how many &quot;Girl&quot; elements there are in the second
set of characters, you would use this for <CODE>element_name</CODE>:
&quot;Southpark.Characters(1).Girl&quot;

<DT><PRE>void <B><A NAME="Empty">Empty</A></B>( void )</PRE><DD>
Empties the contents of the document. The object is reset to an
intial state. All elements are deleted. All callbacks are deleted.

<DT><PRE>BOOL <B><A NAME="EnumerateCallbacks">EnumerateCallbacks</A></B>( DWORD&amp; enumerator ) const</PRE><DD>
Initializes the <CODE>enumerator</CODE> in preparation for calling
<B><A HREF="#GetNextCallback">GetNextCallback()</A></B>. If there are
no callbacks (i.e. <B><A HREF="#AddCallback">AddCallback()</A></B> has
not been called), FALSE will be returned. If there are callbacks, TRUE
will be returned.

<DT><PRE>void <B><A NAME="ExecuteCallbacks">ExecuteCallbacks</A></B>( <A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * element_p )</PRE><DD>
This is generally called during the parsing of a document by the
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A>
that just parsed itself. However, you can pull an element out of the
document and call <B>ExecuteCallbacks</B>() yourself.

<DT><PRE>void <B><A NAME="GetAutomaticIndentation">GetAutomaticIndentation</A></B>( BOOL&amp; automatically_indent, DWORD&amp; indentation_level, DWORD&amp; indent_by ) const</PRE><DD>
Retrieves the automatic indentation parameters. Automatic indentation does
nothing but make the XML output look pretty. It makes it easier for humans
to read. If your application is sensitive to white space, don't use automatic
indentation.

<DT><PRE>DWORD <B><A NAME="GetConversionCodePage">GetConversionCodePage</A></B>( void ) const</PRE><DD>
Returns the code page that will be used for conversion from UNICODE.

<DT><PRE><A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B><A NAME="GetElement">GetElement</A></B>( const CString&amp; element_name ) const</PRE><DD>
Searches and finds the specified element in the document. The
<CODE>element_name</CODE> is in the form of &quot;Parent(0).Child(0)&quot;
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
To retrieve the element for Cartman, <CODE>element_name</CODE> should
be &quot;Southpark.Characters.Boy&quot; If you want Ms. Ellen (even
though she doesn't play for the home team) you would use
&quot;Southpark.Characters(1).Girl(1)&quot;

<DT><PRE>void <B><A NAME="GetEncoding">GetEncoding</A></B>( CString&amp; encoding ) const</PRE><DD>
Returns the encoding of the document.

<DT><PRE>const <A HREF="CExtensibleMarkupLanguageEntities.htm">CExtensibleMarkupLanguageEntities</A>&amp; <B><A NAME="GetEntities">GetEntities</A></B>( void ) const</PRE><DD>
Returns a const reference to the entities for this document.
Basically all you can do with it is enumerate the entries.

<DT><PRE>BOOL <B><A NAME="GetIgnoreWhiteSpace">GetIgnoreWhiteSpace</A></B>( void ) const</PRE><DD>
Returns whether or not the document will suppress the output
of elements that contain only space characters. This output
occurs when you call <B><A HREF="#WriteTo">WriteTo()</A></B>.

<DT><PRE>BOOL <B><A NAME="GetNextCallback">GetNextCallback</A></B>( DWORD&amp; enumerator, CString&amp; element_name, XML_ELEMENT_CALLBACK&amp; callback, void *&amp; callback_parameter )</PRE><DD>
Retrieves the next callback. It will return TRUE if the callback has been
retrieved or FALSE if you are at the end of the list. If FALSE is returned,
all parameters are set to NULL. Callbacks are added via the
<B><A HREF="#AddCallback">AddCallback()</A></B> method.

<DT><PRE>DWORD <B><A NAME="GetNumberOfElements">GetNumberOfElements</A></B>( void ) const</PRE><DD>
Returns the number of elements in this document.

<DT><PRE>TCHAR <B><A NAME="GetParentChildSeparatorCharacter">GetParentChildSeparatorCharacter</A></B>( void ) const</PRE><DD>
Returns the character that will be used to separate parent element names
from child element names in the <B>GetElement</B>() method.

<DT><PRE>DWORD <B><A NAME="GetParseOptions">GetParseOptions</A></B>( void ) const</PRE><DD>
Returns the parse options. This is a bit field (32 wide) that
controls the sloppiness of the parser.

<DT><PRE>void <B><A NAME="GetParsingErrorInformation">GetParsingErrorInformation</A></B>( CString&amp; tag_name, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; beginning, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; error_location, CString * error_message = NULL ) const</PRE><DD>
If
<B><A HREF="#Parse">Parse()</A></B>
returns FALSE, you can call this method to find out
interesting information as to where the parse failed. This will help you
correct the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>.
If <CODE>error_message</CODE> is not NULL, it will be filled
with a human readable error message.
The <CODE>beginning</CODE> parameter is filled with the location in
the document where the element began.
The <CODE>error_location</CODE> parameter is filled with the location
where the parser encountered the fatal problem.

<DT><PRE><A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>GetRootElement</B>( void ) const</PRE><DD>
Returns the pointer to the ultimate parent element. This will be the element
that contains the data from the <CODE>&lt;?xml ... ?&gt;</CODE> line.

<DT><PRE>void <B><A NAME="GetVersion">GetVersion</A></B>( CString&amp; version ) const</PRE><DD>
Returns the version of the document.

<DT><PRE>DWORD <B><A NAME="GetWriteOptions">GetWriteOptions</A></B>( void ) const</PRE><DD>
Returns the writing options. This is a bit field (32 wide) that
controls how the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
documents are written.

<DT><PRE>BOOL <B><A NAME="IsStandalone">IsStandalone</A></B>( void ) const</PRE><DD>
Returns TRUE if this is a standalone document.

<DT><PRE>BOOL <B><A NAME="Parse">Parse</A></B>( const <A HREF="CDataParser.htm">CDataParser</A>&amp; source )</PRE><DD>
Parses the data from <CODE>source</CODE>. This will construct
the document tree.

<DT><PRE>BOOL <B><A NAME="RemoveCallback">RemoveCallback</A></B>( const char * element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter )</PRE><DD>
This will remove the specified callback from the list. All parameters
must match for the callback to be removed.

<DT><PRE>BOOL <B><A NAME="ResolveEntity">ResolveEntity</A></B>( const CString&amp; entity, CString&amp; resolved_to ) const</PRE><DD>
This method will resolve the <CODE>entity</CODE> and put the result into <CODE>resolved_to</CODE>.
If the entity cannot be resolved, it will return FALSE.

<DT><PRE>void <B><A NAME="SetAutomaticIndentation">SetAutomaticIndentation</A></B>( BOOL automatically_indent = TRUE, DWORD starting_column = 0, DWORD indent_by = 2 )</PRE><DD>
This will turn automatic indentation on or off.

<DT><PRE>BOOL <B><A NAME="SetConversionCodePage">SetConversionCodePage</A></B>( DWORD new_page )</PRE><DD>
When you must convert from UNICODE to something else, this is the
code page that will be used. See the <CODE><B>WideCharToMultiByte()</B></CODE> Win32 API
for more information. If the code is run on a real operating system (NT), the
default code page is <CODE>CP_UTF8</CODE>. If you are running on a piece of crap
(Windows 95) the default code page is <CODE>CP_ACP</CODE>.

<DT><PRE>void <B><A NAME="SetEncoding">SetEncoding</A></B>( LPCTSTR encoding )</PRE><DD>
Sets the encoding of the document. You will usuall do this when you are about
to write the document.

<DT><PRE>BOOL <B><A NAME="SetIgnoreWhiteSpace">SetIgnoreWhiteSpace</A></B>( BOOL ignore_whitespace )</PRE><DD>
Tells the document whether or not to ignore text segments that contain
only space characters. It returns what the previous setting was.

<DT><PRE>BOOL <B><A NAME="SetParentChildSeparatorCharacter">SetParentChildSeparatorCharacter</A></B>( TCHAR separator )</PRE><DD>
Allows you to specify the character that will separate parent and child
names in the <B>GetElement()</B> call.

<DT><PRE>DWORD <B><A NAME="SetParseOptions">SetParseOptions</A></B>( DWORD new_options )</PRE><DD>
Sets the parsing options. This allows you to customize the parser to
be as loose or as strict as you want. The default is to be as strict
as possible when parsing. <B>SetParseOptions</B>() returns the previous
options. Here are the current parse options that can be set:

<UL>

<LI><B><CODE>WFC_XML_IGNORE_CASE_IN_XML_DECLARATION</CODE></B> - When set, this option
will allow uppercase letters in the XML declaration. For example:
<CODE>&lt;?XmL ?&gt;</CODE> will be allowed even though it does not
conform to the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">specification</A>.

<LI><B><CODE>WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES</CODE></B> - Though the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML specification</A>
doesn&#39;t talk about it, what should a parser do if default entities
are replaced? If you set this option, the parser will allow replacement
of the default entities. Here is a list of the default entities:

<UL>
<LI><B><CODE>&#38;amp;</CODE></B>
<LI><B><CODE>&#38;apos;</CODE></B>
<LI><B><CODE>&#38;gt;</CODE></B>
<LI><B><CODE>&#38;lt;</CODE></B>
<LI><B><CODE>&#38;quot;</CODE></B>
</UL>

<LI><B><CODE>WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES</CODE></B> - <I><B>Not yet implemented.</B></I>
It will allow the parser to ignore ill formed entities such as <BR>
<CODE>&lt;!ENTITY amp &quot;&#38;#38;&quot;&gt;</CODE>

<LI><B><CODE>WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS</CODE></B> - Tells the parser
to ignore elements (of type <B><CODE>typeTextSegment</CODE></B>) that contain
nothing but white space characters. <B>WARNING!</B> If you use this option, it will
not be possible to reproduce that input file exactly. Elements that contain
nothing but white spaces will be deleted from the document.

<LI><B><CODE>WFC_XML_IGNORE_MISSING_XML_DECLARATION</CODE></B> - Tells the parser
to ignore the fact that the <CODE>&lt;?xml ?&gt;</CODE> element is missing.
If it was not specified in the data stream, one will be automatically
added to the document. This is the default behavior.

<LI><B><CODE>WFC_XML_DISALLOW_MULTIPLE_ELEMENTS</CODE></B> - Tells the parser
to allow multiple elements to be present in the document. The first rule (Rule 1)
of the 
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML specification</A>
says (like Connor MacLeod of the clan MacLeod) <I>There can be only one</I>
element in an XML document. That element can have a billion child elements
but there can be only one root element. If this option is set
(it is not set by default), the parser will strictly enforce this rule. This rule
really gets in the way of using XML for things like log files (where you
want to open the file, append a record to it and close the file).

<LI><B><CODE>WFC_XML_LOOSE_COMMENT_PARSING</CODE></B> - Tells the parser
to allow double dashes (--) to appear in comment tags.

<LI><B><CODE>WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS</CODE></B> - Tells the parser
to allow &amp;'s to appear in the contents of an element without being
a reference of some kind..

</UL>

<DT><PRE>void <B><A NAME="SetParsingErrorInformation">SetParsingErrorInformation</A></B>( const CString&amp; tag_name, const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; beginning, const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; error_location, LPCTSTR error_message = NULL )</PRE><DD>
This method is usually called by the element that cannot parse
itself. There is logic that prevents the information from being
overwritten by subsequent calls to <B>SetParsingErrorInformation</B>().
This means you can call <B>SetParsingErrorInformation</B>() as
many times as you want but only information from the first call
will be recorded (and reported via
<B><A HREF="#GetParsingErrorInformation">GetParsingErrorInformation()</A></B>)
for each call to
<B><A HREF="#Parse">Parse()</A></B>.

<DT><PRE>void <B><A NAME="SetStandalone">SetStandalone</A></B>( BOOL standalone )</PRE><DD>
Sets the standalone attribute of the document.
This is usually done just before you start writing the document.

<DT><PRE>void <B><A NAME="SetVersion">SetVersion</A></B>( LPCTSTR version )</PRE><DD>
Sets the version of the document.
This is usually done just before you start writing the document.

<DT><PRE>DWORD <B><A NAME="SetWriteOptions">SetWriteOptions</A></B>( DWORD new_options )</PRE><DD>
Sets the writing options. This allows you to customize how the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> is written.
The default is to be as strict as possible when writing.
<B>SetWriteOptions</B>() returns the previous
options. Here are the current options that can be set:

<UL>

<LI><B><CODE>WFC_XML_INCLUDE_TYPE_INFORMATION</CODE></B> - <I><B>Not Yet Implemented.</B></I>
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
is woefully inept at handling data. They use things called DTD&#39;s but
they have a &quot;the world is flat&quot; outlook on life.
DTD&#39;s lack the ability to scope.
It would be like programming where all variables have to have unique names
no matter what function they exist in.
DTD&#39;s are used to give HTML browsers the ability to correctly
display
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>.
They also give you the ability to do some lame data validation.
In the future, I will include the
ability to write type information in a programmer friendly fashion.
This type information is intended to be a programmer-to-programmer
communication medium.

<LI><B><CODE>WFC_XML_DONT_OUTPUT_XML_DECLARATION</CODE></B> - This allows
you to skip writing the
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A>
declaration when you output. For example, this
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> document:
<PRE><CODE>&lt;?xml version=&quot;1.0&quot; ?&gt;
&lt;TRUTH&gt;Sam loves Laura.&lt;/TRUTH&gt;</CODE></PRE>
Would look like this when <CODE>WFC_XML_DONT_OUTPUT_XML_DECLARATION</CODE>
is set:
<PRE><CODE>&lt;TRUTH&gt;Sam loves Laura.&lt;/TRUTH&gt;</CODE></PRE>

<LI><B><CODE>WFC_XML_WRITE_AS_UNICODE</CODE></B> - This
tells the document to write output as UNICODE (two bytes per
character). It will default to writing in little endian format.

<LI><B><CODE>WFC_XML_WRITE_AS_BIG_ENDIAN</CODE></B> - This
tells the document to write UNICODE or UCS4 characters in
big endian format.

<LI><B><CODE>WFC_XML_WRITE_AS_UCS4</CODE></B> - This will write
the data in UCS4 (four bytes per character). The default is to
write in little endian format. For example, the &lt; character
would come out as these bytes <CODE>3C 00 00 00</CODE>

<LI><B><CODE>WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143</CODE></B> - This
will format the output in an unusual 4 bytes per character format.
For example, the &lt; character
would come out as these bytes <CODE>00 00 3C 00</CODE>

<LI><B><CODE>WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412</CODE></B> - This
will format the output in another unusual 4 bytes per character
format.
For example, the &lt; character
would come out as these bytes <CODE>00 3C 00 00</CODE>

<LI><B><CODE>WFC_XML_WRITE_AS_ASCII</CODE></B> - This 
will format the output in ASCII format. This is the default.

<LI><B><CODE>WFC_XML_WRITE_AS_UTF8</CODE></B> - Ths will
write the data out in UTF-8 format.

</UL>

<DT><PRE>void <B><A NAME="WriteTo">WriteTo</A></B>( CByteArray&amp; destination )</PRE><DD>
Write the data to <CODE>destination</CODE> in
<A HREF="http://www.w3.org/TR/" TARGET="_parent">XML</A> form.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>CExtensibleMarkupLanguageDocument&amp; operator <B>=</B> ( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Calls <B><A HREF="#Copy">Copy()</A></B>.

<DT><PRE>CExtensibleMarkupLanguageDocument&amp; operator <B>+=</B> ( const CExtensibleMarkupLanguageDocument&amp; source )</PRE><DD>
Calls <B><A HREF="#Append">Append()</A></B>.

</DL>

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

BOOL get_bytes( const CString&amp; filename, CByteArray&amp; bytes )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;get_bytes()&quot; ) );

   bytes.RemoveAll();

   CFile file;

   if ( file.Open( filename, CFile::modeRead ) == FALSE )
   {
      return( FALSE );
   }

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );

   file.Close();

   return( TRUE );
}

BOOL parse_document( const CString&amp; filename, CExtensibleMarkupLanguageDocument&amp; document )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;parse_document()&quot; ) );

   CByteArray bytes;

   if ( get_bytes( filename, bytes ) != TRUE )
   {
      return( FALSE );
   }

   <A HREF="CDataParser.htm">CDataParser</A> parser;

   parser.<A HREF="CDataParser.htm#Initialize">Initialize</A>( &amp;bytes, FALSE );

   if ( document.<A HREF="#Parse">Parse</A>( parser ) == TRUE )
   {
      _tprintf( TEXT( &quot;Parsed OK\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;Can't parse document\n&quot; ) );
   }

   return( TRUE );
}

void stanza_callback( void * parameter, <A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * element_p )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;stanza_callback()&quot; ) );

   _tprintf( TEXT( &quot;Got a stanza with %lu children\n&quot; ), (DWORD) element_p->GetNumberOfChildren() );
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>CExtensibleMarkupLanguageDocument</B> document;

   document.<A HREF="#AddCallback">AddCallback</A>( TEXT( &quot;stanza&quot; ), stanza_callback, NULL );

   if ( parse_document( TEXT( &quot;poem.xml&quot; ), document ) == TRUE )
   {
      CByteArray bytes;

      document.<A HREF="#SetWriteOptions">SetWriteOptions</A>( WFC_XML_DONT_OUTPUT_XML_DECLARATION );

      document.<A HREF="#WriteTo">WriteTo</A>( bytes );

      _tprintf( TEXT( &quot;Wrote %d bytes\n&quot; ), bytes.GetSize() );

      CFile file;

      if ( file.Open( TEXT( &quot;xml.out&quot; ), CFile::modeCreate | CFile::modeWrite ) != FALSE )
      {
         file.Write( bytes.GetData(), bytes.GetSize() );
         file.Close();
      }
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CExtensibleMarkupLanguageDocument.cpp $<BR>
$Modtime: 1/17/00 9:01a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=
#endif
