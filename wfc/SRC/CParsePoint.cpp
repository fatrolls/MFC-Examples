#if 0
<HTML>

<HEAD>
<TITLE>WFC - CParsePoint</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that holds a parsing location.">
</HEAD>

<BODY>

<H1>CParsePoint</H1>
$Revision: 6 $
<HR>

<H2>Description</H2>

This class is built for speed so it breaks all of the OO rules.
It basically is a smart index. It gives you a byte index, 
line number and column number for parsing. It makes it easy
to report errors to the user like &quot;Cannot parse gudfiddlebarb
beginning at line 47 column 3.&quot;

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE>inline <B>CParsePoint</B>()
inline <B>CParsePoint</B>( const CParsePoint&amp; source )</PRE><DD>
Constructs the object. The beginning line number is 1 and
the beginning column is 1.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>inline void <B><A NAME="AutoIncrement">AutoIncrement</A></B>( BYTE character )</PRE><DD>
Automatically increments the byte index. If <CODE>character</CODE>
is a new line, line number is incremented and column number is reset to 1.

<DT><PRE>inline void <B><A NAME="Copy">Copy</A></B>( const CParsePoint&amp; source )</PRE><DD>
Copies <CODE>source</CODE> to this object.

<DT><PRE>inline void <B><A NAME="Empty">Empty</A></B>( void )</PRE><DD>
Re-initializes the object. The byte index will be set to zero,
the line index and column index will be set to one.

<DT><PRE>inline DWORD <B><A NAME="GetIndex">GetIndex</A></B>( void ) const</PRE><DD>
Returns the byte index.

<DT><PRE>inline DWORD <B><A NAME="GetLineIndex">GetLineIndex</A></B>( void ) const</PRE><DD>
Returns the column number (beginning at 1) in the current line.

<DT><PRE>inline DWORD <B>GetLineNumber</B>( void ) const</PRE><DD>
Returns the current line number (beginning at 1).

<DT><PRE>inline void <B><A NAME="SetIndex">SetIndex</A></B>( DWORD index )</PRE><DD>
Sets the byte index.

<DT><PRE>inline void <B><A NAME="SetLineIndex">SetLineIndex</A></B>( DWORD column_number )</PRE><DD>
Sets the column number.

<DT><PRE>inline void <B><A NAME="SetLineNumber">SetLineNumber</A></B>( DWORD line_number )</PRE><DD>
Sets the current line number.

<DT><PRE>inline void <B><A NAME="IncrementIndex">IncrementIndex</A></B>( int steps = 1 )</PRE><DD>
Increments the byte index.

<DT><PRE>inline void <B><A NAME="IncrementLineIndex">IncrementLineIndex</A></B>( int steps = 1 )</PRE><DD>
Increments the line column number.

<DT><PRE>inline void <B><A NAME="IncrementLineNumber">IncrementLineNumber</A></B>( int steps = 1 )</PRE><DD>
Increments the line number.

</DL>

<H2>Operators</H2>

<DT><PRE>inline CParsePoint&amp; operator <B>=</B> ( const CParsePoint&amp; source )</PRE><DD>
Calls <B>Copy</B>().

<H2>Example</H2>

<PRE><CODE>void failed_at_location( const <B>CParsePoint</B>&amp location )
{
   _tprintf( TEXT( &quot;Failed parsing, field began at line number %lu column %lu\n&quot;,
             location.GetLineNumber(),
             location.GetLineIndex() );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CParsePoint.cpp $<BR>
$Modtime: 1/04/00 5:18a $
</BODY>
</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CParsePoint =Byte <m_ByteIndex,lu>, Line <m_LineNumber,lu>, Column <m_LineIndex,lu>
#endif // 0
