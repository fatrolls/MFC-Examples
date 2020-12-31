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
** $Workfile: NBFCP.cpp $
** $Revision: 12 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetBEUIFramerProjectionResult, CRemoteAccessServiceConnectionProjection, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetBEUIFramerProjectionResult::CNetBEUIFramerProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::CNetBEUIFramerProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CNetBEUIFramerProjectionResult::CNetBEUIFramerProjectionResult( const CNetBEUIFramerProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult( const CNetBEUIFramerProjectionResult& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CNetBEUIFramerProjectionResult::CNetBEUIFramerProjectionResult( const RAS_PPP_NBFCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult( const RAS_PPP_NBFCP_RESULT * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CNetBEUIFramerProjectionResult::~CNetBEUIFramerProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::~CNetBEUIFramerProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CNetBEUIFramerProjectionResult::Copy( const CNetBEUIFramerProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::Copy( const CNetBEUIFramerProjectionResult& )" ) );
   ErrorCode       = source.ErrorCode;
   NetBiosError    = source.NetBiosError;
   Name            = source.Name;
   WorkstationName = source.WorkstationName;
}

void CNetBEUIFramerProjectionResult::Copy( const RAS_PPP_NBFCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::Copy( const RAS_PPP_NBFCP_RESULT * )" ) );
   ASSERT( source != NULL );

   // Choose to live

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      ErrorCode    = source->dwError;
      NetBiosError = source->dwNetBiosError;
      Name         = source->szName;
      ::wfc_convert_lpcwstr_to_cstring( source->wszWksta, WorkstationName );
   }
   catch( ... )
   {
      Empty();
      return;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetBEUIFramerProjectionResult::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CNetBEUIFramerProjectionResult at " ) << (VOID *) this << TEXT( "\n{\n" );
   CRemoteAccessServiceConnectionProjection::Dump( dump_context );
   dump_context << TEXT( "   NetBiosError is    " ) << NetBiosError    << TEXT( "\n" );
   dump_context << TEXT( "   Name is            " ) << Name            << TEXT( "\n" );
   dump_context << TEXT( "   WorkstationName is " ) << WorkstationName << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CNetBEUIFramerProjectionResult::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::Empty()" ) );
   CRemoteAccessServiceConnectionProjection::Empty();
   NetBiosError = 0;
   Name.Empty();
   WorkstationName.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetBEUIFramerProjectionResult::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::Serialize()" ) );

   CRemoteAccessServiceConnectionProjection::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << NetBiosError;
      archive << Name;
      archive << WorkstationName;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> NetBiosError;
      archive >> Name;
      archive >> WorkstationName;
   }
}

#endif // WFC_NO_SERIALIZATION

CNetBEUIFramerProjectionResult& CNetBEUIFramerProjectionResult::operator = ( const CNetBEUIFramerProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CNetBEUIFramerProjectionResult::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetBEUIFramerProjectionResult</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking, source code">
</HEAD>

<BODY>

<H1>CNetBEUIFramerProjectionResult : CRemoteAccessServiceConnectionProjection</H1>
$Revision: 12 $
<HR>

<H2>Description</H2>

This class is based on the RAS_PPP_NBFCP_RESULT structure.

<H2>Data Members</H2>

<B>None.</B>

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Copy</B></DFN><DD>Copies another CNetBEUIFramerProjectionResult or a RAS_PPP_NBFCP_RESULT structure.

<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.

<DT><DFN><B>Serialize</B></DFN><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: NBFCP.cpp $<BR>
$Modtime: 1/05/00 3:37a $
</BODY>
</HTML>
#endif
