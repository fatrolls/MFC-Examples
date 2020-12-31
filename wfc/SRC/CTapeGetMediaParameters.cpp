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
** $Workfile: CTapeGetMediaParameters.cpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CTapeGetMediaParameters::CTapeGetMediaParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::CTapeGetMediaParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CTapeGetMediaParameters::CTapeGetMediaParameters( const CTapeGetMediaParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::CTapeGetMediaParameters( CTapeGetMediaParameters )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeGetMediaParameters::CTapeGetMediaParameters( const TAPE_GET_MEDIA_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::CTapeGetMediaParameters( TAPE_GET_MEDIA_PARAMETERS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeGetMediaParameters::~CTapeGetMediaParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::~CTapeGetMediaParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CTapeGetMediaParameters::Copy( const CTapeGetMediaParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::Copy( const CTapeGetMediaParameters& )" ) );
   Copy( (const TAPE_GET_MEDIA_PARAMETERS *) &source );
}

void CTapeGetMediaParameters::Copy( const TAPE_GET_MEDIA_PARAMETERS *source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::Copy( const TAPE_GET_MEDIA_PARAMETERS * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      Capacity.LowPart   = source->Capacity.LowPart;
      Capacity.HighPart  = source->Capacity.HighPart;
      Remaining.LowPart  = source->Remaining.LowPart;
      Remaining.HighPart = source->Remaining.HighPart;
      BlockSize          = source->BlockSize;
      PartitionCount     = source->PartitionCount;
      WriteProtected     = source->WriteProtected;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTapeGetMediaParameters::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTapeGetMediaParameters at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Capacity.LowPart = "   ) << Capacity.LowPart   << TEXT( "\n" );
   dump_context << TEXT( "   Capacity.HighPart = "  ) << Capacity.HighPart  << TEXT( "\n" );
   dump_context << TEXT( "   Remaining.LowPart = "  ) << Remaining.LowPart  << TEXT( "\n" );
   dump_context << TEXT( "   Remaining.HighPart = " ) << Remaining.HighPart << TEXT( "\n" );
   dump_context << TEXT( "   BlockSize = "          ) << BlockSize          << TEXT( "\n" );
   dump_context << TEXT( "   PartitionCount = "     ) << PartitionCount     << TEXT( "\n" );
   dump_context << TEXT( "   WriteProtected = "     ) << WriteProtected     << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTapeGetMediaParameters::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CTapeGetMediaParameters::Empty()" ) );

   Capacity.LowPart   = 0;
   Capacity.HighPart  = 0;
   Remaining.LowPart  = 0;
   Remaining.HighPart = 0;
   BlockSize          = 0;
   PartitionCount     = 0;
   WriteProtected     = 0;
}

CTapeGetMediaParameters& CTapeGetMediaParameters::operator=( const CTapeGetMediaParameters& source )
{
   Copy( source );
   return( *this );
}

CTapeGetMediaParameters& CTapeGetMediaParameters::operator=( const TAPE_GET_MEDIA_PARAMETERS& source )
{
   Copy( &source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CTapeGetMediaParameters</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that encapsulates TAPE_GET_MEDIA_PARAMETERS.">
</HEAD>

<BODY>

<H1>CTapeGetMediaParameters : _TAPE_GET_MEDIA_PARAMETERS</H1>
$Revision: 11 $<BR>
<HR>

<H2>Description</H2>

This class wraps the TAPE_GET_MEDIA_PARAMETERS data structure.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CTapeGetMediaParameters</B>()
<B>CTapeGetMediaParameters</B>( const CTapeGetMediaParameters&amp; source )
<B>CTapeGetMediaParameters</B>( const TAPE_GET_MEDIA_PARAMETERS * source )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const CTapeGetMediaParameters&amp; source )
void <B>Copy</B>( const TAPE_GET_MEDIA_PARAMETERS * source )</PRE><DD>
Copies the contents of <CODE>source</CODE> to this object.

<DT><PRE>void <B>Dump</B>( CDumpContext&amp; dump_context )</PRE><DD>
Present in debug builds only. Dumps the contents of the object
to the <CODE>dump_context</CODE>.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Zeroizes the member variables.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CTapeGetMediaParameters.cpp $<BR>
$Modtime: 1/04/00 5:24a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CTape=hFile=<m_hFile> name=<m_strFileName.m_pchData,s>
#endif
