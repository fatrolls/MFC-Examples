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
** $Workfile: RASCP.CPP $
** $Revision: 12 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CRemoteAccessServiceConnectionProjection, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CRemoteAccessServiceConnectionProjection::CRemoteAccessServiceConnectionProjection()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::CRemoteAccessServiceConnectionProjection()" ) );
   Empty();
}

CRemoteAccessServiceConnectionProjection::CRemoteAccessServiceConnectionProjection( const CRemoteAccessServiceConnectionProjection& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection( const CRemoteAccessServiceConnectionProjection& )" ) );
   Empty();
   Copy( source );
}

CRemoteAccessServiceConnectionProjection::~CRemoteAccessServiceConnectionProjection()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::~CRemoteAccessServiceConnectionProjection()" ) );
   Empty();
}

void CRemoteAccessServiceConnectionProjection::Copy( const CRemoteAccessServiceConnectionProjection& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::Copy( const CRemoteAccessServiceConnectionProjection& )" ) );
   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   ErrorCode = source.ErrorCode;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CRemoteAccessServiceConnectionProjection::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CRemoteAccessServiceConnectionProjection at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   ErrorCode is " ) << ErrorCode << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif

void CRemoteAccessServiceConnectionProjection::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::Empty()" ) );
   ErrorCode = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CRemoteAccessServiceConnectionProjection::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << ErrorCode;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> ErrorCode;
   }
}

#endif // WFC_NO_SERIALIZATION

CRemoteAccessServiceConnectionProjection& CRemoteAccessServiceConnectionProjection::operator = ( const CRemoteAccessServiceConnectionProjection& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceConnectionProjection::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessServiceConnectionProjection</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CRemoteAccessServiceConnectionProjection : CObject</H1>
$Revision: 12 $
<HR>

<H2>Description</H2>
This class is based on the RAS_PORT_STATISTICS structure.

<H2>Data Members</H2>

<B>None.</B>

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Copy</B></DFN><DD>Copies another CRemoteAccessServiceConnectionProjection or a RAS_PORT_STATISTICS structure.
<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.
<DT><DFN><B>Serialize</B></DFN><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: RASCP.CPP $<BR>
$Modtime: 1/05/00 3:37a $
</BODY>

</HTML>
#endif
