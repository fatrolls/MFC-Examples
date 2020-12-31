#include <wfc.h>
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
** $Workfile: CCryptographicAlgorithm.cpp $
** $Revision: 21 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CCryptographicAlgorithm" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CCryptographicAlgorithm, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

// Construction

CCryptographicAlgorithm::CCryptographicAlgorithm()
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::CCryptographicAlgorithm()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CCryptographicAlgorithm::CCryptographicAlgorithm( const CCryptographicAlgorithm& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::CCryptographicAlgorithm( CCryptographicAlgorithm )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CCryptographicAlgorithm::CCryptographicAlgorithm( const PROV_ENUMALGS& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::CCryptographicAlgorithm( PROV_ENUMALGS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CCryptographicAlgorithm::~CCryptographicAlgorithm()
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::CCryptographicAlgorithm()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void CCryptographicAlgorithm::Copy( const CCryptographicAlgorithm& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::Copy( CCryptographicAlgorithm )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Identifier = source.Identifier;
   BitLength  = source.BitLength;
   Name       = source.Name;
}

void CCryptographicAlgorithm::Copy( const PROV_ENUMALGS& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::Copy( PROV_ENUMALGS& )" ) );

   Identifier = source.aiAlgid;
   BitLength  = source.dwBitLen;
   Name       = source.szName;
}

void CCryptographicAlgorithm::Copy( const PROV_ENUMALGS * source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::Copy( PROV_ENUMALGS * )" ) );

   try
   {
      Copy( *source );
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CCryptographicAlgorithm::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CCryptographicAlgorithm at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Identifier is "              ) << Identifier    << TEXT( "\n"    );
   dump_context << TEXT( "   BitLength is  "              ) << BitLength     << TEXT( "\n"    );
   dump_context << TEXT( "   Name is       "              ) << Name          << TEXT( "\n"    );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CCryptographicAlgorithm::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::Empty()" ) );
   Identifier = 0;
   BitLength  = 0;
   Name.Empty();
}

BOOL CCryptographicAlgorithm::IsDataEncrypt( void ) const
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::IsDataEncrypt()" ) );

   if ( GET_ALG_CLASS( Identifier ) == classDataEncrypt )
   {
      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }

   return( FALSE );
}

BOOL CCryptographicAlgorithm::IsHash( void ) const
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::IsHash()" ) );

   if ( GET_ALG_CLASS( Identifier ) == classHash )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CCryptographicAlgorithm::IsKeyExchange( void ) const
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::IsKeyExchange()" ) );

   if ( GET_ALG_CLASS( Identifier ) == classKeyExchange )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CCryptographicAlgorithm::IsMessageEncrypt( void ) const
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::IsMessageEncrypt()" ) );

   if ( GET_ALG_CLASS( Identifier ) == classMessageEncrypt )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CCryptographicAlgorithm::IsSignature( void ) const
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::IsSignature()" ) );

   if ( GET_ALG_CLASS( Identifier ) == classSignature )
   {
      return( TRUE );
   }

   return( FALSE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CCryptographicAlgorithm::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::Serialize()" ) );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Identifier;
      archive << BitLength;
      archive << Name;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Identifier;
      archive >> BitLength;
      archive >> Name;
   }
}

#endif // WFC_NO_SERIALIZATION

// Operators

CCryptographicAlgorithm& CCryptographicAlgorithm::operator=( const CCryptographicAlgorithm& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::operator=( CCryptographicAlgorithm )" ) );
   Copy( source );
   return( *this );
}

CCryptographicAlgorithm& CCryptographicAlgorithm::operator=( const PROV_ENUMALGS& source )
{
   WFCLTRACEINIT( TEXT( "CCryptographicAlgorithm::operator=( PROV_ENUMALGS )" ) );
   Copy( source );
   return( *this );
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CCryptographicAlgorithm</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles CryptoAPI algorithms.">
</HEAD>

<BODY>

<H1>CCryptographicAlgorithm : CObject</H1>
$Revision: 21 $<BR><HR>

<H2>Description</H2>

This is the class handles Cryptographic Algorithms. It
encapsulates the PROV_ENUMALGS data structure and gives you
a few little helpers.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CCryptographicAlgorithm</B>()
<B>CCryptographicAlgorithm</B>( const CCryptographicAlgorithm&amp; source )
<B>CCryptographicAlgorithm</B>( const PROV_ENUMALGS&amp; source )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>DWORD <B>Identifier</B></PRE><DD>
The defined constant for the algorithm.

<DT><PRE>DWORD <B>BitLength</B></PRE><DD>
The number of bits in the key. This will usually be choked by the
United States Commerce Department to 40 bits (which has been proven
to be easily breakable).

<DT><PRE>CString <B>Name</B></PRE><DD>
Hold the name of the algorithm.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const CCryptographicAlgorithm&amp; source )
void <B>Copy</B>( const PROV_ENUMALGS&amp;  source )
void <B>Copy</B>( const PROV_ENUMALGS * source )</PRE><DD>
Copies the data from another object.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Clears the data members.

<DT><PRE>BOOL <B>IsDataEncrypt</B>( void )</PRE><DD>
Returns TRUE if this algorithm can be used to encrypt data.

<DT><PRE>BOOL <B>IsHash</B>( void )</PRE><DD>
Returns TRUE if this algorithm is a secure hash algorithm.

<DT><PRE>BOOL <B>IsKeyExchange</B>( void )</PRE><DD>
Returns TRUE if this algorithm is used to exchange keys with another
person.

<DT><PRE>BOOL <B>IsMessageEncrypt</B>( void )</PRE><DD>
Returns TRUE if this algorithm is used to encrypt messages.

<DT><PRE>BOOL <B>IsSignature</B>( void )</PRE><DD>
Returns TRUE if this algorithm is used to digitally sign messages.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>operator <B>=</B> ( const CCryptographicAlgorithm&amp; source )
operator <B>=</B> ( const PROV_ENUMALGS&amp; source )</PRE><DD>
These call the <B>Copy</B>() methods.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>
<B>CCryptographicAlgorithm</B> uses the following API's:
<UL>
<LI>GET_ALG_CLASS
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CCryptographicAlgorithm.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>

</HTML>
#endif
