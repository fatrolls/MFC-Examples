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
** $Workfile: IPXCP.cpp $
** $Revision: 12 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CInternetworkPacketExchangeProjectionResult, CRemoteAccessServiceConnectionProjection, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CInternetworkPacketExchangeProjectionResult::CInternetworkPacketExchangeProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::CInternetworkPacketExchangeProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CInternetworkPacketExchangeProjectionResult::CInternetworkPacketExchangeProjectionResult( const CInternetworkPacketExchangeProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult( const CInternetworkPacketExchangeProjectionResult& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CInternetworkPacketExchangeProjectionResult::CInternetworkPacketExchangeProjectionResult( const RAS_PPP_IPXCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult( const RAS_PPP_IPXCP_RESULT * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CInternetworkPacketExchangeProjectionResult::~CInternetworkPacketExchangeProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::~CInternetworkPacketExchangeProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CInternetworkPacketExchangeProjectionResult::Copy( const CInternetworkPacketExchangeProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::Copy( const CInternetworkPacketExchangeProjectionResult& )" ) );
   ErrorCode = source.ErrorCode;
   Address   = source.Address;
}

void CInternetworkPacketExchangeProjectionResult::Copy( const RAS_PPP_IPXCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::Copy( const RAS_PPP_IPXCP_RESULT * )" ) );
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

void CInternetworkPacketExchangeProjectionResult::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CInternetworkPacketExchangeProjectionResult at " ) << (VOID *) this << TEXT( "\n{\n" );
   CRemoteAccessServiceConnectionProjection::Dump( dump_context );
   dump_context << TEXT( "   Address is " ) << Address << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif

void CInternetworkPacketExchangeProjectionResult::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::Empty()" ) );
   CRemoteAccessServiceConnectionProjection::Empty();
   Address.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CInternetworkPacketExchangeProjectionResult::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::Serialize()" ) );

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

CInternetworkPacketExchangeProjectionResult& CInternetworkPacketExchangeProjectionResult::operator = ( const CInternetworkPacketExchangeProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CInternetworkPacketExchangeProjectionResult::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CInternetworkPacketExchangeProjectionResult</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking, source code">
</HEAD>

<BODY>

<H1>CInternetworkPacketExchangeProjectionResult : CRemoteAccessServiceConnectionProjection</H1>
$Revision: 12 $
<HR>

<H2>Description</H2>

This class is based on the RAS_PPP_IPXCP_RESULT structure.

<H2>Data Members</H2>

<B>Address</B> - Contains the address.

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Copy</B></DFN><DD>Copies another CInternetworkPacketExchangeProjectionResult or a RAS_PPP_IPXCP_RESULT structure.

<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.

<DT><DFN><B>Serialize</B></DFN><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: IPXCP.cpp $<BR>
$Modtime: 1/05/00 3:37a $
</BODY>
</HTML>
#endif
