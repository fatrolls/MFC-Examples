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
** $Workfile: ATCP.cpp $
** $Revision: 17 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CAppleTalkProjectionResult, CRemoteAccessServiceConnectionProjection, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif // _DEBUG

CAppleTalkProjectionResult::CAppleTalkProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::CAppleTalkProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CAppleTalkProjectionResult::CAppleTalkProjectionResult( const CAppleTalkProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult( const CAppleTalkProjectionResult& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CAppleTalkProjectionResult::CAppleTalkProjectionResult( const RAS_PPP_ATCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult( const RAS_PPP_ATCP_RESULT * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CAppleTalkProjectionResult::~CAppleTalkProjectionResult()
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::~CAppleTalkProjectionResult()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CAppleTalkProjectionResult::Copy( const CAppleTalkProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::Copy( const CAppleTalkProjectionResult& )" ) );
   ErrorCode = source.ErrorCode;
   Address   = source.Address;
}

void CAppleTalkProjectionResult::Copy( const RAS_PPP_ATCP_RESULT * source )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::Copy( const RAS_PPP_ATCP_RESULT * )" ) );
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

void CAppleTalkProjectionResult::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CAppleTalkProjectionResult at " ) << (VOID *) this << TEXT( "\n{\n" );
   CRemoteAccessServiceConnectionProjection::Dump( dump_context );
   dump_context << TEXT( "   Address is " ) << Address << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif

void CAppleTalkProjectionResult::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::Empty()" ) );
   CRemoteAccessServiceConnectionProjection::Empty();
   Address.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CAppleTalkProjectionResult::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::Serialize()" ) );

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

CAppleTalkProjectionResult& CAppleTalkProjectionResult::operator = ( const CAppleTalkProjectionResult& source )
{
   WFCLTRACEINIT( TEXT( "CAppleTalkProjectionResult::operator =()" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CAppleTalkProjectionResult</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles Appletalk RAS projection results.">
</HEAD>

<BODY>

<H1>CAppleTalkProjectionResult : CRemoteAccessServiceConnectionProjection</H1>
$Revision: 17 $
<HR>

<H2>Description</H2>

This class is based on the RAS_PPP_ATCP_RESULT structure.

<H2>Data Members</H2>

<B>Address</B> - Contains the address.

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Copy</B><DD>Copies another CAppleTalkProjectionResult or a RAS_PPP_ATCP_RESULT structure.
<DT><B>Empty</B><DD>Clears all data members.
<DT><B>Serialize</B><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: ATCP.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>

</HTML>
#endif
