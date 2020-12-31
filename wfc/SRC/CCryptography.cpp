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
** $Workfile: CCryptography.cpp $
** $Revision: 15 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CCryptography" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CCryptography::CCryptography()
{
   WFCLTRACEINIT( TEXT( "CCryptography::CCryptography()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_ErrorCode = 0;
}

CCryptography::~CCryptography()
{
   WFCLTRACEINIT( TEXT( "CCryptography::CCryptography()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_ErrorCode = 0;
}

// Methods

DWORD CCryptography::GetErrorCode( void ) const
{
   return( m_ErrorCode );
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CCryptography</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ base class for all CryptoAPI related classes.">
</HEAD>

<BODY>

<H1>CCryptography</H1>
$Revision: 15 $<BR><HR>

<H2>Description</H2>
This is the base class for all cryptographic classes that provide functionality.

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>DWORD <B>GetErrorCode</B>( void ) const</PRE><DD>
Returns the error code of the last error.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CCryptography.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>

</HTML>
#endif
