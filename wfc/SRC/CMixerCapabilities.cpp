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
** $Workfile: CMixerCapabilities.cpp $
** $Revision: 17 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CMixerCapabilities, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

CMixerCapabilities::CMixerCapabilities()
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::CMixerCapabilities()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMixerCapabilities::CMixerCapabilities( const CMixerCapabilities& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::CMixerCapabilities( CMixerCapabilities )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerCapabilities::CMixerCapabilities( const MIXERCAPS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::CMixerCapabilities( MIXERCAPS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerCapabilities::~CMixerCapabilities()
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::~CMixerCapabilities()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CMixerCapabilities::Copy( const CMixerCapabilities& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::Copy( CMixerCapabilities )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Manufacturer         = source.Manufacturer;
   Product              = source.Product;
   Version              = source.Version;
   ProductName          = source.ProductName;
   Support              = source.Support;
   NumberOfDestinations = source.NumberOfDestinations;
}

void CMixerCapabilities::Copy( const MIXERCAPS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::Copy( CMixerCapabilities )" ) );
   Manufacturer         = source.wMid;
   Product              = source.wPid;
   Version              = source.vDriverVersion;
   ProductName          = source.szPname;
   Support              = source.fdwSupport;
   NumberOfDestinations = source.cDestinations;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerCapabilities::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerCapabilities at "    ) << (VOID *) this        << TEXT( "\n{\n" );
   dump_context << TEXT( "   Manufacturer is         " ) << Manufacturer         << TEXT( "\n" );
   dump_context << TEXT( "   Product is              " ) << Product              << TEXT( "\n" );
   dump_context << TEXT( "   Version is              " ) << Version              << TEXT( "\n" );
   dump_context << TEXT( "   ProductName is          " ) << ProductName          << TEXT( "\n" );
   dump_context << TEXT( "   Support is              " ) << Support              << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfDestinations is " ) << NumberOfDestinations << TEXT( "\n}\n" );
}

#endif // _DEBUG

void CMixerCapabilities::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::Empty()" ) );
   Manufacturer         = 0;
   Product              = 0;
   Version              = 0;
   ProductName.Empty();
   Support              = 0;
   NumberOfDestinations = 0;
}

BOOL CMixerCapabilities::Get( const UINT device_number )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::Get()" ) );

   MMRESULT result = 0;

   MIXERCAPS mixer_capabilities;

   ::ZeroMemory( &mixer_capabilities, sizeof( mixer_capabilities ) );

   result = ::mixerGetDevCaps( device_number, &mixer_capabilities, sizeof( mixer_capabilities ) );

   if ( result != MMSYSERR_NOERROR )
   {
      // Leave us with that empty feeling
      Empty();
      return( FALSE );
   }

   Copy( mixer_capabilities );

   return( TRUE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixerCapabilities::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::Serialize()" ) );
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Manufacturer;
      archive << Product;
      archive << Version;
      archive << ProductName;
      archive << Support;
      archive << NumberOfDestinations;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Manufacturer;
      archive >> Product;
      archive >> Version;
      archive >> ProductName;
      archive >> Support;
      archive >> NumberOfDestinations;
   }
}

#endif // WFC_NO_SERIALIZATION

CMixerCapabilities& CMixerCapabilities::operator = ( const CMixerCapabilities& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::operator = ( CMixerCapabilities )" ) );
   Copy( source );
   return( *this );
}

CMixerCapabilities& CMixerCapabilities::operator = ( const MIXERCAPS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerCapabilities::operator = ( MIXERCAPS )" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CMixerCapabilities</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles Mixer capabilities.">
</HEAD>

<BODY>

<H1>CMixerCapabilities : CObject</H1>
$Revision: 17 $<BR><HR>

<H2>Description</H2>
This class encapsulates the MIXERCAPS data structure.

<H2>Data Members</H2>

<DL>

<DT><B>Manufacturer</B><DD>Holds the manufacturer's identifier.
<DT><B>Product</B><DD>Holds the product identifier.
<DT><B>Version</B><DD>Holds the version of the driver.
<DT><B>ProductName</B><DD>Holds the name of the mixer device.
<DT><B>Support</B><DD>A 32-bit bitmap mask of supported functions. The only
problem is there are no definitions for the bits so this member is basically
worthless.
<DT><B>NumberOfDestinations</B><DD>Holds the number of places you can
route audio output to. There will always be at least one destination (i.e. speakers).

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Copy</B><DD>Copies the contents of another CMixerCapabilities or a
MIXERCAPS data structure.

<DT><B>Empty</B><DD>Zeroizes the data members.

<DT><B>Get</B><DD>Retrieves the mixer's capabilities via CMixerCapabilities.

<DT><B>Serialize</B><DD>After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CMixerCapabilities.cpp $<BR>
$Modtime: 1/04/00 5:15a $
</BODY>

</HTML>
#endif
