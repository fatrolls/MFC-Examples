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
** $Workfile: RASPPPCR.cpp $
** $Revision: 12 $
** $Modtime: 1/05/00 3:40a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CPointToPointProtocolProjectionResult, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CPointToPointProtocolProjectionResult::CPointToPointProtocolProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::CPointToPointProtocolProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CPointToPointProtocolProjectionResult::CPointToPointProtocolProjectionResult( const CPointToPointProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult( const CPointToPointProtocolProjectionResult& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CPointToPointProtocolProjectionResult::CPointToPointProtocolProjectionResult( const RAS_PPP_PROJECTION_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult( const RAS_PPP_PROJECTION_RESULT * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CPointToPointProtocolProjectionResult::~CPointToPointProtocolProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::~CPointToPointProtocolProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CPointToPointProtocolProjectionResult::Copy( const CPointToPointProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::Copy( CPointToPointProtocolProjectionResult& )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   AppleTalk.Copy( source.AppleTalk );
   IP.Copy( source.IP );
   IPX.Copy( source.IPX );
   NetBEUI.Copy( source.NetBEUI );
}

void CPointToPointProtocolProjectionResult::Copy( const RAS_PPP_PROJECTION_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::Copy( RAS_PPP_PROJECTION_RESULT * )" ) );

   // Choose to live

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      AppleTalk.Copy( &source->at );
      IP.Copy( &source->ip );
      IPX.Copy( &source->ipx );
      NetBEUI.Copy( &source->nbf );
   }
   catch( ... )
   {
      Empty();
      return;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CPointToPointProtocolProjectionResult::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CPointToPointProtocolProjectionResult at " ) << (VOID *) this << TEXT( "\n{\n" );

   dump_context << TEXT( "   AppleTalk is " );
   AppleTalk.Dump( dump_context );

   dump_context << TEXT( "   IP is " );
   IP.Dump( dump_context );

   dump_context << TEXT( "   IPX is " );
   IPX.Dump( dump_context );

   dump_context << TEXT( "   NetBEUI is " );
   NetBEUI.Dump( dump_context );

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CPointToPointProtocolProjectionResult::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::Empty()" ) );
   AppleTalk.Empty();
   IP.Empty();
   IPX.Empty();
   NetBEUI.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CPointToPointProtocolProjectionResult::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::Serialize()" ) );

   CObject::Serialize( archive );
   AppleTalk.Serialize( archive );
   IP.Serialize( archive );
   IPX.Serialize( archive );
   NetBEUI.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

CPointToPointProtocolProjectionResult& CPointToPointProtocolProjectionResult::operator = ( const CPointToPointProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CPointToPointProtocolProjectionResult::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPointToPointProtocolProjectionResult</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CPointToPointProtocolProjectionResult : CObject</H1>
$Revision: 12 $
<HR>

<H2>Description</H2>
This class is based on the RAS_PPP_PROJECTION_RESULT structure.

<H2>Data Members</H2>

<B>None.</B>

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Copy</B><DD>Copies another CPointToPointProtocolProjectionResult or a RAS_PPP_PROJECTION_RESULT structure.
<DT><B>Empty</B><DD>Clears all data members.
<DT><B>Serialize</B><DD>After all, we are a CObject...

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: RASPPPCR.cpp $<BR>
$Modtime: 1/05/00 3:40a $
</BODY>

</HTML>
#endif
