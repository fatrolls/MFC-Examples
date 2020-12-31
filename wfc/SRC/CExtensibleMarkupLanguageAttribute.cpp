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
** $Workfile: CExtensibleMarkupLanguageAttribute.cpp $
** $Revision: 12 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CExtensibleMarkupLanguageAttribute::CExtensibleMarkupLanguageAttribute()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::CExtensibleMarkupLanguageAttribute()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

CExtensibleMarkupLanguageAttribute::CExtensibleMarkupLanguageAttribute( const CExtensibleMarkupLanguageAttribute& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::CExtensibleMarkupLanguageAttribute( CExtensibleMarkupLanguageAttribute )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CExtensibleMarkupLanguageAttribute::~CExtensibleMarkupLanguageAttribute()
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::~CExtensibleMarkupLanguageAttribute()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

void CExtensibleMarkupLanguageAttribute::Copy( const CExtensibleMarkupLanguageAttribute& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::Copy()" ) );
   Name  = source.Name;
   Value = source.Value;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CExtensibleMarkupLanguageAttribute::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " is a CExtensibleMarkupLanguageAttribute at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Name  is " ) << Name  << TEXT( "\n" );
   dump_context << TEXT( "   Value is " ) << Value << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CExtensibleMarkupLanguageAttribute::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::Empty()" ) );
   Name.Empty();
   Value.Empty();
}

CExtensibleMarkupLanguageAttribute& CExtensibleMarkupLanguageAttribute::operator=( const CExtensibleMarkupLanguageAttribute& source )
{
   WFCLTRACEINIT( TEXT( "CExtensibleMarkupLanguageAttribute::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CExtensibleMarkupLanguageAttribute</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, push technology, source code">
<META name="description" content="The C++ class that handles XML attributes.">
</HEAD>

<BODY>

<H1>CExtensibleMarkupLanguageAttribute</H1>

$Revision: 12 $

<HR>

<H2>Description</H2>

This class holds the name and value of an XML attribute. It is a very
trivial class.

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>CString <B>Name</B></PRE><DD>Contains the attribute name.
<DT><PRE>CString <B>Value</B></PRE><DD>Contains the value of the attribute.

</DL>

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE><B>CExtensibleMarkupLanguageAttribute</B>()
<B>CExtensibleMarkupLanguageAttribute</B>( const CExtensibleMarkupLanguageAttribute&amp; source )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const CExtensibleMarkupLanguageAttribute&amp; source )</PRE><DD>
Copies another <B>CExtensibleMarkupLanguageAttribute</B>.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Clears all data members.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>CExtensibleMarkupLanguageAttribute&amp; operator <B>=</B> ( const CExtensibleMarkupLanguageAttribute&amp; source )</PRE><DD>
Calls <B>Copy</B>().

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CExtensibleMarkupLanguageAttribute.cpp $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
#endif
