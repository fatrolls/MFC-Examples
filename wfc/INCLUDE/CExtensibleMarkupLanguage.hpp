#if ! defined( XML_CLASSES_HEADER )

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
** $Workfile: CExtensibleMarkupLanguage.hpp $
** $Revision: 32 $
** $Modtime: 3/12/00 3:31p $
*/

#define XML_CLASSES_HEADER

// Helper functions

BOOL is_xml_BaseChar( DWORD character_to_test );
BOOL is_xml_Char( DWORD character_to_test );
BOOL is_xml_CombiningChar( DWORD character_to_test );
BOOL is_xml_Digit( DWORD character_to_test );
BOOL is_xml_Extender( DWORD character_to_test );
BOOL is_xml_Ideographic( DWORD character_to_test );
BOOL is_xml_Letter( DWORD character_to_test );
BOOL is_xml_NameChar( DWORD character_to_test );
BOOL is_xml_PubidChar( DWORD character_to_test );
BOOL is_xml_white_space( DWORD character_to_test );

// An Entity (as described in the XML specification section 4.2) is "An
// entity reference refers to the content of a named entity." Doesn't that
// make sense?? OK, if you're a layman (like me) it means "that which lies
// between & and ;". What it does is allow you to define your own
// search-and-replace strings. If you know HTML, then you know what an
// "entity" is. Here's some examples from HTML:
// &gt; &lt; &quot;
// XML let's you roll your own:
// &myentity; &yourentity;
// In the DTD document (which I'll get around to parsing later) contains
// a list of these entities in <!ENTITY lines for example:
// <!ENTITY myentity "I hate entities." >

class CExtensibleMarkupLanguageEntities
{
   protected:

      CStringArray m_Entities;
      CStringArray m_Values;

   public:

      // Construction

      CExtensibleMarkupLanguageEntities();
      CExtensibleMarkupLanguageEntities( const CExtensibleMarkupLanguageEntities& source );
      virtual ~CExtensibleMarkupLanguageEntities();

      // Methods

      virtual BOOL Add( const CString& tag, const CString& text );
      virtual void Copy( const CExtensibleMarkupLanguageEntities& source );
      virtual void Empty( void );
      virtual BOOL Enumerate( DWORD& enumerator ) const;
      virtual BOOL GetNext( DWORD& enumerator, CString& entity, CString& value ) const;
      virtual long GetSize( void ) const;
      virtual BOOL IsEntity( const CString& tag, DWORD& rule_that_was_broken ) const;
      virtual BOOL Resolve( const CString& tag, CString& text ) const;

      // Operators

      virtual CExtensibleMarkupLanguageEntities& operator=( const CExtensibleMarkupLanguageEntities& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CExtensibleMarkupLanguageAttribute
{
   public:

      // Construction

      CExtensibleMarkupLanguageAttribute();
      CExtensibleMarkupLanguageAttribute( const CExtensibleMarkupLanguageAttribute& source );
      virtual ~CExtensibleMarkupLanguageAttribute();

      // Properties

      CString Name;
      CString Value;

      // Methods

      virtual void Copy( const CExtensibleMarkupLanguageAttribute& source );
      virtual void Empty( void );

      virtual CExtensibleMarkupLanguageAttribute& operator = ( const CExtensibleMarkupLanguageAttribute& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CExtensibleMarkupLanguageDocument; // Avoid chicken-or-the-egg problem

class CExtensibleMarkupLanguageElement
{
   private:

      // Don't allow stack objects...

      CExtensibleMarkupLanguageElement();
      CExtensibleMarkupLanguageElement( const CExtensibleMarkupLanguageElement& source );

   protected:

      CExtensibleMarkupLanguageDocument * m_Document;

      CExtensibleMarkupLanguageElement * m_Parent;

      CPtrArray m_Children;   // Array of CExtensibleMarkupLanguageElement pointers
      CPtrArray m_Attributes; // Array of CExtensibleMarkupLanguageAttribute pointers

      CString m_Contents;
      CString m_Tag;

      DWORD m_Type;

      CParsePoint m_Beginning;
      CParsePoint m_Ending;

      BOOL m_AbortParsing; // Used only while parsing a document
      BOOL m_IsTagTerminated;
      BOOL m_IsAllWhiteSpace; // TRUE if we are a typeTextSegment and m_Text contains nothing but space-like characters
      BOOL m_ShorthandTerminatorDetected;

      virtual void m_AddCharacterToOutput( DWORD character, DWORD write_options, CByteArray& output ) const;
      virtual void m_AddIndentation( CByteArray& bytes ) const;
      virtual void m_AppendAttributes( CByteArray& data ) const;
      virtual void m_AppendChildren( CByteArray& data ) const;
      virtual void m_DecrementIndentation( void ) const;
      virtual void m_GetTag( const CString& xml_data, CString& tag );
      virtual void m_IncrementIndentation( void ) const;
      virtual void m_Initialize( void );
      virtual BOOL m_ParseCDATASection( const CString& tag, const CDataParser& parser );
      virtual BOOL m_ParseDOCTYPESection( const CString& tag, const CDataParser& parser );
      virtual BOOL m_ParseElementName( const CString& name, CString& parent_name, DWORD& desired_instance_number, CString& child_name ) const;
      virtual BOOL m_ParseProcessingInstruction( void );
      virtual BOOL m_ParseTag( const CString& tag, BOOL& did_tag_contain_terminator, const CDataParser& parser );
      virtual BOOL m_ParseXMLDeclaration( const CString& tag );
      virtual void m_ReportParsingError( LPCTSTR error_message = reinterpret_cast< LPCTSTR >( NULL ) );
      virtual void m_ResolveEntities( CString& encoded_entity_string ) const;
      virtual BOOL m_TrimQuotesAndSpaces( CString& value, TCHAR quote_to_trim = TEXT( '\"' ) ) const;

   public:

      enum ElementTypes
      {
         typeUnknown = 0,
         typeProcessingInstruction, // Start Tag is "<?" End Tag is "?>
         typeComment, // Start Tag is "<!--" End Tag is "-->"
         typeCharacterData, // Start Tag is "<![CDATA[" End Tag is "]]>"
         typeElement, // A user's element
         typeTextSegment, // that which lies between sub-elements
         typeMetaData // Anything in a "<!" field that ain't typeComment or typeCharacterData
      };

      static CExtensibleMarkupLanguageElement * NewElement( CExtensibleMarkupLanguageElement * parent_element = NULL, DWORD type = typeElement, CExtensibleMarkupLanguageDocument * document = NULL );
      static void DeleteElement( CExtensibleMarkupLanguageElement * element_p );

      virtual ~CExtensibleMarkupLanguageElement();

      /*
      ** <ITEM HREF=" http://www.samplecdf.com/page1.htm">
      **    <LOGO HREF=" http://www.samplecdf.com/red.ico" STYLE="ICON"/>
      **    <Log VALUE="document:view"/>
      **    <TITLE>The Red Page</TITLE>
      **    <ABSTRACT>This is the abstract description for the red page.</ABSTRACT>
      **    These are the times that try mens souls.
      ** </ITEM>
      */

      /*
      ** Element Start Tag     Attribute Name
      **  |                    |
      **  |    +---------------+
      **  v    v
      ** <ITEM HREF="http://www.samplecdf.com/page1.htm">
      ** These are the times that try mens souls.</ITEM>
      ** ^                                       ^
      ** |                                       |
      ** |                                       Element End Tag
      ** Content
      */

      // Element manipulation
      virtual void  AddChild( CExtensibleMarkupLanguageElement * element_p, DWORD insert_at = (0xFFFFFFFF) );
      virtual void  DestroyChildren( void );
      virtual BOOL  EnumerateChildren( DWORD& enumerator ) const;
      virtual BOOL  GetNextChild( DWORD& enumerator, CExtensibleMarkupLanguageElement *& element_p ) const;
      virtual DWORD GetNumberOfChildren( void ) const;
      virtual void  RemoveChild( CExtensibleMarkupLanguageElement * element_p );

      // Attributes
      virtual BOOL  AddAttribute( const CString& name, const CString& value );
      virtual void  DestroyAttributeByName( const CString& name );
      virtual void  DestroyAttributeByValue( const CString& value );
      virtual void  DestroyAttributes( void );
      virtual BOOL  EnumerateAttributes( DWORD& enumerator ) const;
      virtual BOOL  GetAttributeByName( CExtensibleMarkupLanguageAttribute& attribute ) const;
      virtual BOOL  GetAttributeByName( const CString& name, CString& value ) const;
      virtual CExtensibleMarkupLanguageAttribute * GetAttributeByName( const CString& name ) const; // Added by Mats Johnsson 1998-09-02
      virtual BOOL  GetAttributeByValue( CExtensibleMarkupLanguageAttribute& attribute ) const;
      virtual BOOL  GetNextAttribute( DWORD& enumerator, CExtensibleMarkupLanguageAttribute*& attribute ) const;
      virtual DWORD GetNumberOfAttributes( void ) const;

      // General being a good C++ citizen kind of things go here

      virtual BOOL  AddText( const CString& text_segment );
      virtual void  Copy( const CExtensibleMarkupLanguageElement& source );
      virtual DWORD CountChildren( const CString& name ) const;
      virtual void  Empty( void );
      virtual BOOL  GetAbortParsing( void ) const;
      virtual void  GetBeginning( CParsePoint& parse_point ) const;
      virtual CExtensibleMarkupLanguageElement * GetChild( const CString& tag_name ) const;
      virtual CExtensibleMarkupLanguageDocument * GetDocument( void ) const;
      virtual void  GetEnding( CParsePoint& parse_point ) const;
      virtual void  GetCompleteName( CString& name ) const;
      virtual void  GetContents( CString& contents ) const;
      virtual void  GetName( CString& name ) const;
      virtual CExtensibleMarkupLanguageElement * GetParent( void ) const;
      virtual CExtensibleMarkupLanguageElement * GetParent( const CString& name ) const;
      virtual void  GetTag(  CString& tag  ) const;
      virtual void  GetText( CString& text ) const;
      virtual DWORD GetTotalNumberOfChildren( void ) const;
      virtual DWORD GetType( void ) const;
      virtual BOOL  IsAllWhiteSpace( void ) const;
      virtual BOOL  IsRoot( void ) const;
      virtual BOOL  Parse( const CParsePoint& beginning, const CDataParser& parser );
      virtual void  SetAbortParsing( BOOL abort_parsing = TRUE );
      virtual void  SetContents( const CString& contents );
      virtual void  SetDocument( CExtensibleMarkupLanguageDocument * document_p );
      virtual void  SetTag( const CString& tag_name );
      virtual void  SetType( DWORD element_type );
      virtual void  WriteTo( CByteArray& destination ) const;

      virtual CExtensibleMarkupLanguageElement& operator=( const CExtensibleMarkupLanguageElement& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

typedef void (*XML_ELEMENT_CALLBACK)( void * parameter, CExtensibleMarkupLanguageElement * element_p );

// Parsing options

#define WFC_XML_IGNORE_CASE_IN_XML_DECLARATION        (0x1)
#define WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES (0x2)
#define WFC_XML_FAIL_ON_ILL_FORMED_ENTITIES           (0x4)
#define WFC_XML_IGNORE_ALL_WHITE_SPACE_ELEMENTS       (0x8)
#define WFC_XML_IGNORE_MISSING_XML_DECLARATION        (0x10)
#define WFC_XML_DISALLOW_MULTIPLE_ELEMENTS            (0x20)
#define WFC_XML_LOOSE_COMMENT_PARSING                 (0x40)
#define WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS          (0x80)

// Writing Options
#define WFC_XML_INCLUDE_TYPE_INFORMATION              (0x1)
#define WFC_XML_DONT_OUTPUT_XML_DECLARATION           (0x2)
#define WFC_XML_WRITE_AS_UNICODE                      (0x4)
#define WFC_XML_WRITE_AS_BIG_ENDIAN                   (0x8)
#define WFC_XML_WRITE_AS_UCS4                         (0x10)
#define WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143            (0x20)
#define WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412            (0x40)
#define WFC_XML_WRITE_AS_ASCII                        (0x80)
#define WFC_XML_WRITE_AS_UTF8                         (0x100)

class CExtensibleMarkupLanguageDocument
{
   protected:

      CExtensibleMarkupLanguageElement * m_XML; // The <?xml ... ?> tag

      CPtrArray m_Callbacks;

      CExtensibleMarkupLanguageEntities m_Entities;

      BOOL m_IgnoreWhiteSpace;
      BOOL m_AutomaticIndentation;

      DWORD m_IndentationLevel;
      DWORD m_IndentBy;
      DWORD m_ParseOptions;
      DWORD m_WriteOptions;

      // Parsing Error Information

      BOOL        m_ParseErrorEncountered;
      CParsePoint m_ErrorElementBeganAt;
      CParsePoint m_ErrorOccuredAt;
      CString     m_ErrorTagName;
      CString     m_ErrorMessage;

      // Data from XMLDecl
      CString     m_Encoding;
      BOOL        m_IsStandalone;
      CString     m_Version;

      TCHAR m_ParentChildSeparatorCharacter;

      DWORD m_ConversionCodePage;

      virtual void m_InitializeRootElement( void );
      virtual void m_InitializeEntities( void );
      virtual void m_RemoveAllCallbacks( void );

   public:

      CExtensibleMarkupLanguageDocument();
      CExtensibleMarkupLanguageDocument( const CExtensibleMarkupLanguageDocument& source );
      virtual ~CExtensibleMarkupLanguageDocument();

      virtual BOOL  AddEntity( const CString& entity, const CString& value );
      virtual void  Append( const CExtensibleMarkupLanguageDocument& source );
      virtual void  Copy( const CExtensibleMarkupLanguageDocument& source );
      virtual void  CopyCallbacks( const CExtensibleMarkupLanguageDocument& source );
      virtual DWORD CountElements( const CString& name ) const;
      virtual void  Empty( void );
      virtual CExtensibleMarkupLanguageElement * GetElement( const CString& name ) const;
      virtual void  GetAutomaticIndentation( BOOL& automatically_indent, DWORD& level, DWORD& indent_by );
      inline  DWORD GetConversionCodePage( void ) const { return( m_ConversionCodePage ); }
      virtual void  GetEncoding( CString& encoding ) const;
      virtual const CExtensibleMarkupLanguageEntities& GetEntities( void ) const;
      virtual BOOL  GetIgnoreWhiteSpace( void ) const;
      virtual DWORD GetNumberOfElements( void ) const;
      virtual TCHAR GetParentChildSeparatorCharacter( void ) const;
      virtual DWORD GetParseOptions( void ) const;
      virtual void  GetParsingErrorInformation( CString& tag_name, CParsePoint& beginning, CParsePoint& error_location, CString * error_message = reinterpret_cast< CString * >( NULL ) ) const;
      virtual CExtensibleMarkupLanguageElement * GetRootElement( void ) const;
      virtual void  GetVersion( CString& version ) const;
      virtual DWORD GetWriteOptions( void ) const;
      virtual BOOL  IsStandalone( void ) const;
      virtual BOOL  Parse( CDataParser& source );
      virtual BOOL  ResolveEntity( const CString& entity, CString& resolved_to ) const;
      virtual void  SetAutomaticIndentation( BOOL automatically_indent = TRUE, DWORD level = 0, DWORD indent_by = 2 );
      virtual void  SetConversionCodePage( DWORD new_page );
      virtual void  SetEncoding( LPCTSTR encoding );
      virtual BOOL  SetIgnoreWhiteSpace( BOOL ignore_whitespace );
      virtual BOOL  SetParentChildSeparatorCharacter( TCHAR separator );
      virtual DWORD SetParseOptions( DWORD new_options );
      virtual void  SetParsingErrorInformation( const CString& tag_name, const CParsePoint& beginning, const CParsePoint& error_location, LPCTSTR error_message = reinterpret_cast< LPCTSTR >( NULL ) );
      virtual void  SetStandalone( BOOL standalone );
      virtual void  SetVersion( LPCTSTR version_string );
      virtual DWORD SetWriteOptions( DWORD new_options );
      virtual void  WriteTo( CByteArray& destination ) const;

      // Add callback methods here...

      virtual BOOL AddCallback( LPCTSTR element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter );
      virtual BOOL EnumerateCallbacks( DWORD& enumerator ) const;
      virtual void ExecuteCallbacks( CExtensibleMarkupLanguageElement * element_p ) const;
      virtual BOOL GetNextCallback( DWORD& enumerator, CString& element_name, XML_ELEMENT_CALLBACK& callback, void * & parameter ) const;
      virtual BOOL RemoveCallback( const char * element_name, XML_ELEMENT_CALLBACK callback, void * callback_parameter );

      virtual CExtensibleMarkupLanguageDocument& operator=( const CExtensibleMarkupLanguageDocument& source );
      virtual CExtensibleMarkupLanguageDocument& operator+=( const CExtensibleMarkupLanguageDocument& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // XML_CLASSES_HEADER
