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
** $Workfile: IPCP.cpp $
** $Revision: 13 $
** $Modtime: 1/17/00 12:48p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CInternetProtocolProjectionResult, CRemoteAccessServiceConnectionProjection, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CInternetProtocolProjectionResult::CInternetProtocolProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::CInternetProtocolProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CInternetProtocolProjectionResult::CInternetProtocolProjectionResult( const CInternetProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult( const CInternetProtocolProjectionResult& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CInternetProtocolProjectionResult::CInternetProtocolProjectionResult( const RAS_PPP_IPCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult( const RAS_PPP_IPCP_RESULT * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CInternetProtocolProjectionResult::~CInternetProtocolProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::~CInternetProtocolProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CInternetProtocolProjectionResult::Copy( const CInternetProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::Copy( const CInternetProtocolProjectionResult& )" ) );
   ErrorCode = source.ErrorCode;
   Address   = source.Address;
}

void CInternetProtocolProjectionResult::Copy( const RAS_PPP_IPCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::Copy( const RAS_PPP_IPCP_RESULT * )" ) );
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
      ErrorCode = source->dwError;
      ::wfc_convert_lpcwstr_to_cstring( source->wszAddress, Address );
   }
   catch( ... )
   {
      Empty();
      return;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CInternetProtocolProjectionResult::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CInternetProtocolProjectionResult at " ) << (VOID *) this << TEXT( "\n{\n" );
   CRemoteAccessServiceConnectionProjection::Dump( dump_context );
   dump_context << TEXT( "   Address is " ) << Address << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif

void CInternetProtocolProjectionResult::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::Empty()" ) );
   CRemoteAccessServiceConnectionProjection::Empty();
   Address.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CInternetProtocolProjectionResult::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::Serialize()" ) );

   CRemoteAccessServiceConnectionProjection::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Address;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Address;
   }
}

#endif // WFC_NO_SERIALIZATION

CInternetProtocolProjectionResult& CInternetProtocolProjectionResult::operator = ( const CInternetProtocolProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetProtocolProjectionResult::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CInternetProtocolProjectionResult</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking, source code">
</HEAD>

<BODY>
<H1>CInternetProtocolProjectionResult : CRemoteAccessServiceConnectionProjection</H1>
$Revision: 13 $
<HR>

<H2>Description</H2>

This class is based on the RAS_PPP_IPCP_RESULT structure.

<H2>Data Members</H2>

<B>Address</B> - Contains the dotted IP address (&quot;20.2.1.7&quot;).

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Copy</B></DFN><DD>Copies another CInternetProtocolProjectionResult or a RAS_PPP_IPCP_RESULT structure.

<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.

<DT><DFN><B>Serialize</B></DFN><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: IPCP.cpp $<BR>
$Modtime: 1/17/00 12:48p $
</BODY>

</HTML>
#endif
