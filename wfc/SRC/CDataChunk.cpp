#if 0
<HTML>
<HEAD>
<TITLE>WFC - CDataChunk</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="The C++ class that encapsulates data of any size and any format.">
</HEAD>
<BODY>
<H1>CDataChunk</H1>
$Revision: 9 $<BR>
<HR>
<H2>Description</H2>
This class allows you to handle unknown data in an orderly way.
It is patterned after the RIFF idea. RIFF is used in WAV files
and AVI files. It is a very simple way of handling data. You
have a four byte identifier followed by a four byte length 
followed by the length number of bytes. Very simple. Very effective.
<H2>Data Members</H2>
<DL COMPACT>
<DT><PRE>DWORD <B>Identifier</B></PRE><DD>
This contains the four byte identifier.
<DT><PRE>CByteArray <B>Data</B></PRE><DD>
This contains the payload.
</DL>
<H2>Construction</H2>
<DL COMPACT>
<DT><PRE><B>CDataChunk</B>()
<B>CDataChunk</B>( const CDataChunk&amp; source )</PRE><DD>
Constructs the object.
</DL>
<H2>Methods</H2>
<DL COMPACT>
<DT><PRE>inline void <B>Copy</B>( const CDataChunk&amp; source )</PRE><DD>
Copies the contents of another <B>CDataChunk</B> into this one.
<DT><PRE>inline void <B>Copy</B>( DWORD identifier, const CByteArray&amp; payload )</PRE><DD>
Sets the <B>Identifier</B> to <CODE>identifier</CODE> and copies the
<CODE>payload</CODE> into <B>Payload</B>.
<DT><PRE>static void <B>GetIdentifier</B>( DWORD identifier, CString&amp; string )</PRE><DD>
Translates the four byte <CODE>identifier</CODE> into a string. This makes
it easier for humans to decipher the identifier.
</DL>
<H2>Operators</H2>
<DL COMPACT>
<DT><PRE>inline CDataChunk&amp; operator <B>=</B> ( const CDataChunk&amp; source )</PRE><DD>
Calls <B>Copy</B>().
</DL>
<H2>Notes</H2>
This class breaks all of the object oriented rules. No members
are virtual therefore they are useless when it comes to reuse.
The reason I did this was speed. If you're passing data in an
orderly way, I assume you need to do it quickly (at least at this
level of your design).
<H2>Example</H2>
<PRE><CODE>void send_SLVL_chunk( const CByteArray&amp; data, <A HREF="CDataSocket.htm">CDataSocket</A>&amp; socket )
{
   <B>CDataChunk</B> data_chunk;

   data_chunk.Identifier = MAKE_DATA_CHUNK_ID( 'S', 'L', 'V', 'L' );
   data_chunk.Copy( data );

   // Transmit the chunk out of the socket

   socket.AddData( data_chunk );
}</CODE></PRE>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CDataChunk.cpp $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>
</HTML>
#endif
