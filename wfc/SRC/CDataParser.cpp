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
** $Workfile: CDataParser.cpp $
** $Revision: 29 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CDataParser::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " is a CDataParser at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_AutomaticallyDelete is " );

   if ( m_AutomaticallyDelete == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_IsASCII is " );

   if ( m_IsASCII == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_IsUCS4 is " );

   if ( m_IsUCS4 == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_IsBigEndian is " );

   if ( m_IsBigEndian == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "   m_Data is " );

   if ( m_Data == NULL )
   {
      dump_context << TEXT( "NULL\n" );
   }
   else
   {
      m_Data->Dump( dump_context );
   }

   dump_context << TEXT( "}\n" );

}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDataParser</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, push technology, source code">
<META name="description" content="The C++ class that parses anything.">
</HEAD>

<BODY>

<H1>CDataParser</H1>

$Revision: 29 $
<HR>

<H2>Description</H2>

This class is a generic class to assist in parsing data.
It provides some basic searching capability as well as
idiot proofed retrieval.

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE><B>CDataParser</B>()</PRE><DD>
Constructs the object.
</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B><A NAME="AdvanceByOneCharacter">AdvanceByOneCharacter</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, DWORD character = 0 ) const</PRE><DD>
Advances the parse point by at least one character. <CODE>parse_point</CODE>
will be incremented (see <A HREF="CParsePoint.htm#AutoIncrement">AutoIncrement()</A>)
by the character it finds. If you want to be incremented based on
a character that you want, put that character's value in <CODE>character</CODE>.

<DT><PRE>void <B><A NAME="Empty">Empty</A></B>( void )</PRE><DD>
Re-initializes the object. If a CByteArray was attached
(and set to automatically delete) it will be deleted.

<DT><PRE>BOOL <B><A NAME="Find">Find</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, BYTE byte_to_find, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; found_at ) const
BOOL <B>Find</B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, const CString&amp; string_to_find, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; found_at ) const
BOOL <B>Find</B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, const CByteArray&amp; bytes_to_find, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; found_at ) const</PRE><DD>
Searches for <CODE>byte_to_find</CODE>, <CODE>string_to_find</CODE> or
<CODE>bytes_to_find</CODE> beginning at <CODE>parse_point</CODE>.
If what you&#39;re looking for is found, the location will be put into
<CODE>found_at</CODE> and the return value will be TRUE. If <B>Find</B>()
cannot find what you're looking for, it will return FALSE.

<DT><PRE>BOOL <B><A NAME="FindNoCase">FindNoCase</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, const CString&amp; string_to_find, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; found_at ) const
BOOL <B>FindNoCase</B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, const CByteArray&amp; bytes_to_find, <A HREF="CParsePoint.htm">CParsePoint</A>&amp; found_at ) const</PRE><DD>
Will search for <CODE>string_to_find</CODE> or <CODE>bytes_to_find</CODE> without
regard to case. It will match 'a' with 'A'.
If what you're looking for is found, the location will be put into
<CODE>found_at</CODE> and the return value will be TRUE. If <B>FindNoCase</B>()
cannot find what you're looking for, it will return FALSE.

<DT><PRE>BOOL <B><A NAME="Get">Get</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, DWORD length, CByteArray&amp; bytes_to_get ) const
BOOL <B>Get</B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, DWORD length, CString&amp; string_to_get ) const</PRE><DD>
Retrieves the <CODE>length</CODE> number of bytes beginning at <CODE>parse_point</CODE>.

<DT><PRE>BYTE <B><A NAME="GetAt">GetAt</A></B>( DWORD index ) const</PRE><DD>
Retrieves the byte at the given <CODE>index</CODE>.

<DT><PRE>DWORD <B><A NAME="GetCharacter">GetCharacter</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; const_parse_point, const DWORD number_of_characters_ahead = 0 ) const</PRE><DD>
Returns a character at the given location. <B>NOTE:<B> Don't assume that characters
are one byte each like in ASCII. Characters can be made up of multiple bytes
each. This will happen when <A HREF="#SetTextToASCII">SetTextToASCII()</A> is set to
FALSE or <A HREF="#SetTextToUCS4">SetTextToUCS4()</A> is set to TRUE.

<DT><PRE>BOOL <B><A NAME="GetNextCharacter">GetNextCharacter</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, DWORD&amp; character ) const</PRE><DD>
Like <A HREF="#GetCharacter">GetCharacter()</A> except the parse point will be advanced
by however many bytes make up one character (1, 2 or 4). It allows you to basically
enumerate through the data stream. It will return TRUE of <CODE>character</CODE> was
filled or FALSE if you have reached the end (or passed the end) of the data.

<DT><PRE>DWORD <B><A NAME="GetUCS4Order">GetUCS4Order</A></B>( void ) const</PRE><DD>
Returns one of the following:

<UL>
<LI>1234
<LI>2143
<LI>3412
<LI>4321
</UL>

<DT><PRE>BYTE <B><A NAME="GetUnicodeToASCIITranslationFailureCharacter">GetUnicodeToASCIITranslationFailureCharacter</A></B>( void ) const</PRE><DD>
Returns the ASCII character that will be substituted when a translation from
UNICODE to ASCII fails.

<DT><PRE>DWORD <B><A NAME="GetSize">GetSize</A></B>( void ) const</PRE><DD>
Returns the number of bytes in the data area.

<DT><PRE>BOOL <B><A NAME="GetUntilAndIncluding">GetUntilAndIncluding</A></B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, BYTE termination_byte, CString&amp; string_to_get ) const
BOOL <B>GetUntilAndIncluding</B>( <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, BYTE termination_byte, CByteArray&amp; bytes_to_get ) const</PRE><DD>
This method retrieves data (filling <CODE>string_to_get</CODE> or <CODE>bytes_to_get</CODE>)
until and including the <CODE>termination_byte</CODE>. The <CODE>parse_point</CODE>
is advanced in the process.

<DT><PRE>BOOL <B><A NAME="Initialize">Initialize</A></B>( CByteArray * data, BOOL automatically_delete = FALSE )
BOOL <B>Initialize</B>( const CStringArray&amp; strings )</PRE><DD>
Tells the parser where to go for data.

<DT><PRE>BOOL <B><A NAME="IsTextASCII">IsTextASCII</A></B>( void ) const</PRE><DD>
Returns TRUE if characters are to be treated as one byte each.

<DT><PRE>BOOL <B><A NAME="IsTextBigEndian">IsTextBigEndian</A></B>( void ) const</PRE><DD>
Returns TRUE if text is big endian (Sun) format. This has meaning when the
underlying characters are treated as UNICODE or ICS-4.

<DT><PRE>BOOL <B><A NAME="IsTextUCS4">IsTextUCS4</A></B>( void ) const</PRE><DD>
Returns TRUE if characters are to be treated as four bytes per character.

<DT><PRE>BOOL <B><A NAME="PeekAtCharacter">PeekAtCharacter</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, DWORD&amp; character, const DWORD number_of_characters_ahead = 1 ) const</PRE><DD>
Allows you to peek ahead at characters. It will return TRUE if
<CODE>character</CODE> was filled with a character from the data stream.
It will return FALSE when you have tried to read passed the end of the stream.

<DT><PRE>DWORD <B><A NAME="PeekCharacter">PeekCharacter</A></B>( const <A HREF="CParsePoint.htm">CParsePoint</A>&amp; parse_point, const LONG number_of_characters_ahead ) const</PRE><DD>
Allows you to peek ahead at characters. It will the character at the current location plus
<CODE>number_of_characters_ahead</CODE>. If you attempt to read a character passed the
end of the data, it will return NULL.

<DT><PRE>BOOL <B><A NAME="SetTextToASCII">SetTextToASCII</A></B>( BOOL text_is_ascii = TRUE )</PRE><DD>
Tells the class to interpret characters as one byte each.

<DT><PRE>BOOL <B><A NAME="SetTextToBigEndian">SetTextToBigEndian</A></B>( BOOL unicode_is_big_endian = TRUE )</PRE><DD>
Tells the class to interpret UNICODE or UCS-4 characters as big endian (Sun) format.
Little endian is Intel format.

<DT><PRE>BOOL <B><A NAME="SetTextToUCS4">SetTextToUCS4</A></B>( BOOL text_is_ucs4 = TRUE )</PRE><DD>
Tells the class to interpret characters as four bytes each.

<DT><PRE>BOOL <B><A NAME="SetUCS4Order">SetUCS4Order</A></B>( DWORD order = 4321 )</PRE><DD>
Tells the parser to interpret UCS-4 characters in 4321 format.

<DT><PRE>void <B><A NAME="SetUnicodeToASCIITranslationFailureCharacter">SetUnicodeToASCIITranslationFailureCharacter</A></B>( BYTE asci_character )</PRE><DD>
This sets the character that will be substituted when a translation must be made
from UNICODE to ASCII. Since ASCII only has 256 possible values and UNICODE has 65536,
some provision must be made for bad translations.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

BOOL parse_document( const CString&amp; filename, <A HREF="CExtensibleMarkupLanguageDocument.htm">CExtensibleMarkupLanguageDocument</A>&amp; document )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;parse_document()&quot; ) );

   CByteArray bytes;

   if ( get_bytes( filename, bytes ) != TRUE )
   {
      return( FALSE );
   }

   <B>CDataParser</B> parser;

   parser.<A HREF="#Initialize">Initialize</A>( &amp;bytes, FALSE );

   if ( document.Parse( parser ) == TRUE )
   {
      WFCTRACE( TEXT( &quot;Parsed OK&quot; ) );
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( &quot;Can't parse document&quot; ) );
      return( FALSE );
   }
}</CODE></PRE>

<HR>
<I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CDataParser.cpp $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CDataParser =size=<m_Data->m_nSize>
#endif // 0