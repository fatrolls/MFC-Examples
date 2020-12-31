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
** $Workfile: CMixerControl.cpp $
** $Revision: 18 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CMixerControl, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

CMixerControl::CMixerControl()
{
   WFCLTRACEINIT( TEXT( "CMixerControl::CMixerControl()" ) );
   Empty();
}

CMixerControl::CMixerControl( const CMixerControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::CMixerControl( CMixerControl )" ) );
   Copy( source );
}

CMixerControl::CMixerControl( const MIXERCONTROL& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::CMixerControl()" ) );
   Copy( source );
}

CMixerControl::~CMixerControl()
{
   WFCLTRACEINIT( TEXT( "CMixerControl::~CMixerControl()" ) );
   Empty();
}

void CMixerControl::Copy( const CMixerControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::Copy( CMixerControl )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Empty();
   ID                      = source.ID;
   Type                    = source.Type;
   StatusFlags             = source.StatusFlags;
   NumberOfItemsPerChannel = source.NumberOfItemsPerChannel;
   ShortName               = source.ShortName;
   Name                    = source.Name;
   Minimum                 = source.Minimum;
   Maximum                 = source.Maximum;
   NumberOfSteps           = source.NumberOfSteps;
   NumberOfCustomDataBytes = source.NumberOfCustomDataBytes;
   Data.Copy( source.Data );
}

void CMixerControl::Copy( const MIXERCONTROL& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::Copy( MIXERCONTROL )" ) );
   Empty();
   ID                      = source.dwControlID;
   Type                    = source.dwControlType;
   StatusFlags             = source.fdwControl;
   NumberOfItemsPerChannel = source.cMultipleItems;
   ShortName               = source.szShortName;
   Name                    = source.szName;
   Minimum                 = source.Bounds.dwMinimum;
   Maximum                 = source.Bounds.dwMaximum;
   NumberOfSteps           = source.Metrics.cSteps;
   NumberOfCustomDataBytes = source.Metrics.cbCustomData;
   Data.Add( source.Metrics.dwReserved[ 0 ] );
   Data.Add( source.Metrics.dwReserved[ 1 ] );
   Data.Add( source.Metrics.dwReserved[ 2 ] );
   Data.Add( source.Metrics.dwReserved[ 3 ] );
   Data.Add( source.Metrics.dwReserved[ 4 ] );
   Data.Add( source.Metrics.dwReserved[ 5 ] );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerControl::Dump( CDumpContext& dump_context ) const
{
   CString temp_string;

   dump_context << TEXT( "a CMixerControl at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   ID is " ) << ID << TEXT( "\n" );

   DWORD thing = Type & MIXERCONTROL_CT_CLASS_MASK;

   switch( thing )
   {
      case typeFader:

         temp_string = TEXT( "typeFader |" );
         break;

      case typeList:

         temp_string = TEXT( "typeList |" );
         break;

      case typeMeter:

         temp_string = TEXT( "typeMeter |" );
         break;

      case typeNumber:

         temp_string = TEXT( "typeNumber |" );
         break;

      case typeSlider:

         temp_string = TEXT( "typeSlider |" );
         break;

      case typeSwitch:

         temp_string = TEXT( "typeSwitch |" );
         break;

      case typeTime:

         temp_string = TEXT( "typeTime |" );
         break;

      default:

         temp_string = TEXT( "unknown |" );
         break;
   }

   thing = Type & MIXERCONTROL_CT_UNITS_MASK;

   switch( thing )
   {
      case unitsBoolean:

         temp_string += TEXT( "unitsBoolean" );
         break;

      case unitsSigned:

         temp_string += TEXT( "unitsSigned" );
         break;

      case unitsUnsigned:

         temp_string += TEXT( "unitsUnsigned" );
         break;

      case unitsDecibels:

         temp_string += TEXT( "unitsDecibels" );
         break;

      case unitsPercent:

         temp_string += TEXT( "unitsPercent" );
         break;

      default:

         temp_string += TEXT( "unitsCustom" );
         break;
   }

   switch( Type )
   {
      case Custom:

         temp_string += TEXT( " [Custom]" );
         break;

      case Bass:

         temp_string += TEXT( " [Bass]" );
         break;

      case Equalizer:

         temp_string += TEXT( " [Equalizer]" );
         break;

      case Fader:

         temp_string += TEXT( " [Fader]" );
         break;

      case Treble:

         temp_string += TEXT( " [Treble]" );
         break;

      case Volume:

         temp_string += TEXT( " [Volume]" );
         break;

      case Mixer:

         temp_string += TEXT( " [Mixer]" );
         break;

      case MultipleSelect:

         temp_string += TEXT( " [MultipleSelect]" );
         break;

      case Mux:

         temp_string += TEXT( " [Mux]" );
         break;

      case SingleSelect:

         temp_string += TEXT( " [SingleSelect]" );
         break;

      case BooleanMeter:

         temp_string += TEXT( " [BooleanMeter]" );
         break;

      case PeakMeter:

         temp_string += TEXT( " [PeakMeter]" );
         break;

      case SignedMeter:

         temp_string += TEXT( " [SignedMeter]" );
         break;

      case UnsignedMeter:

         temp_string += TEXT( " [UnsignedMeter]" );
         break;

      case Decibels:

         temp_string += TEXT( " [Decibels]" );
         break;

      case Percent:

         temp_string += TEXT( " [Percent]" );
         break;

      case Signed:

         temp_string += TEXT( " [Signed]" );
         break;

      case Unsigned:

         temp_string += TEXT( " [Unsigned]" );
         break;

      case Pan:

         temp_string += TEXT( " [Pan]" );
         break;

      case QSoundPan:

         temp_string += TEXT( " [QSoundPan]" );
         break;

      case Slider:

         temp_string += TEXT( " [Slider]" );
         break;

      case Boolean:

         temp_string += TEXT( " [Boolean]" );
         break;

      case Button:

         temp_string += TEXT( " [Button]" );
         break;

      case Loudness:

         temp_string += TEXT( " [Loudness]" );
         break;

      case Mono:

         temp_string += TEXT( " [Mono]" );
         break;

      case Mute:

         temp_string += TEXT( " [Mute]" );
         break;

      case OnOff:

         temp_string += TEXT( " [OnOff]" );
         break;

      case StereoEnhance:

         temp_string += TEXT( " [StereoEnhance]" );
         break;

      case MicroTime:

         temp_string += TEXT( " [MicroTime]" );
         break;

      case MilliTime:

         temp_string += TEXT( " [MilliTime]" );
         break;

      default:

         temp_string += TEXT( " [Unknown]" );
         break;
   }

   dump_context << TEXT( "   Type is                    " ) << Type                    << TEXT( " ( " ) << temp_string << TEXT( " )\n" );
   dump_context << TEXT( "   StatusFlags is             " ) << StatusFlags             << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfItemsPerChannel is " ) << NumberOfItemsPerChannel << TEXT( "\n" );
   dump_context << TEXT( "   Minimum is                 " ) << Minimum                 << TEXT( "\n" );
   dump_context << TEXT( "   Maximum is                 " ) << Maximum                 << TEXT( "\n" );
   dump_context << TEXT( "   ShortName is               " ) << ShortName               << TEXT( "\n" );
   dump_context << TEXT( "   Name is                    " ) << Name                    << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfSteps is           " ) << NumberOfSteps           << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfCustomDataBytes is " ) << NumberOfCustomDataBytes << TEXT( "\n" );
   
   if ( Data.GetSize() > 5 )
   {
      dump_context << TEXT( "   Data[ 0 ] is               " ) << Data.GetAt( 0 ) << TEXT( "\n" );
      dump_context << TEXT( "   Data[ 1 ] is               " ) << Data.GetAt( 1 ) << TEXT( "\n" );
      dump_context << TEXT( "   Data[ 2 ] is               " ) << Data.GetAt( 2 ) << TEXT( "\n" );
      dump_context << TEXT( "   Data[ 3 ] is               " ) << Data.GetAt( 3 ) << TEXT( "\n" );
      dump_context << TEXT( "   Data[ 4 ] is               " ) << Data.GetAt( 4 ) << TEXT( "\n" );
      dump_context << TEXT( "   Data[ 5 ] is               " ) << Data.GetAt( 5 ) << TEXT( "\n" );
   }
   else
   {
      dump_context << TEXT( "   Data is corrupted.\n" );
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMixerControl::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::Empty()" ) );

   ID                      = 0;
   NumberOfCustomDataBytes = 0;
   NumberOfItemsPerChannel = 0;
   NumberOfSteps           = 0;
   Maximum                 = 0;
   Minimum                 = 0;
   StatusFlags             = 0;
   Type                    = 0;
   ShortName.Empty();
   Name.Empty();
   Data.RemoveAll();
}

DWORD CMixerControl::GetType( void ) const
{
   WFCLTRACEINIT( TEXT( "CMixerControl::GetType()" ) );

   DWORD type = Type & MIXERCONTROL_CT_CLASS_MASK;

   switch( type )
   {
      case typeFader:
      case typeList:
      case typeMeter:
      case typeNumber:
      case typeSlider:
      case typeSwitch:
      case typeTime:

         return( type );

      default:

         return( typeCustom );
   }
}

void CMixerControl::GetTypeName( CString& name ) const
{
   WFCLTRACEINIT( TEXT( "CMixerControl::GetTypeName()" ) );

   switch( Type )
   {
      case Custom:

         name = TEXT( "Custom" );
         break;

      case Bass:

         name = TEXT( "Bass Fader" );
         break;

      case Equalizer:

         name = TEXT( "Equalizer Fader" );
         break;

      case Fader:

         name = TEXT( "Fader" );
         break;

      case Treble:

         name = TEXT( "Treble Fader" );
         break;

      case Volume:

         name = TEXT( "Volume Fader" );
         break;

      case Mixer:

         name = TEXT( "Mixer List" );
         break;

      case MultipleSelect:

         name = TEXT( "Multiple-Select List" );
         break;

      case Mux:

         name = TEXT( "Mux List" );
         break;

      case SingleSelect:

         name = TEXT( "Single-Select List" );
         break;

      case BooleanMeter:

         name = TEXT( "Boolean Meter" );
         break;

      case PeakMeter:

         name = TEXT( "Peak Meter" );
         break;

      case SignedMeter:

         name = TEXT( "Signed Meter" );
         break;

      case UnsignedMeter:

         name = TEXT( "Unsigned Meter" );
         break;

      case Decibels:

         name = TEXT( "Decibels Number" );
         break;

      case Percent:

         name = TEXT( "Percent Number" );
         break;

      case Signed:

         name = TEXT( "Signed Number" );
         break;

      case Unsigned:

         name = TEXT( "Unsigned Number" );
         break;

      case Pan:

         name = TEXT( "Pan Slider" );
         break;

      case QSoundPan:

         name = TEXT( "Q-Sound Pan Slider" );
         break;

      case Slider:

         name = TEXT( "Slider" );
         break;

      case Boolean:

         name = TEXT( "Boolean" );
         break;

      case Button:

         name = TEXT( "Button" );
         break;

      case Loudness:

         name = TEXT( "Loudness Switch" );
         break;

      case Mono:

         name = TEXT( "Mono Switch" );
         break;

      case Mute:

         name = TEXT( "Mute Switch" );
         break;

      case OnOff:

         name = TEXT( "On/Off Switch" );
         break;

      case StereoEnhance:

         name = TEXT( "Stereo Enhance Switch" );
         break;

      case MicroTime:

         name = TEXT( "Microsecond Time" );
         break;

      case MilliTime:

         name = TEXT( "Millisecond Time" );
         break;
   }
}

DWORD CMixerControl::GetUnits( void ) const
{
   WFCLTRACEINIT( TEXT( "CMixerControl::GetUnits()" ) );

   DWORD units = Type & MIXERCONTROL_CT_UNITS_MASK;

   switch( units )
   {
      case unitsBoolean:
      case unitsSigned:
      case unitsUnsigned:
      case unitsDecibels:
      case unitsPercent:

         return( units );

      default:

         return( unitsCustom );
   }
}

BOOL CMixerControl::IsBooleanUnits( void ) const
{
   if ( GetUnits() == unitsBoolean )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsCustom( void ) const
{
   if ( GetType() == typeCustom )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsCustomUnits( void ) const
{
   if ( GetUnits() == unitsCustom )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsDecibelsUnits( void ) const
{
   if ( GetUnits() == unitsDecibels )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsDisabled( void ) const
{
   DWORD status = 0;

   status = StatusFlags & statusDisabled;

   if ( status != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsFader( void ) const
{
   if ( GetType() == typeFader )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsList( void ) const
{
   if ( GetType() == typeList )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsMeter( void ) const
{
   if ( GetType() == typeMeter )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsMultiple( void ) const
{
   DWORD multiple = 0;

   multiple = StatusFlags & statusMultiple;

   if ( multiple != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsNumber( void ) const
{
   if ( GetType() == typeNumber )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsPercentUnits( void ) const
{
   if ( GetUnits() == unitsPercent )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsSignedUnits( void ) const
{
   if ( GetUnits() == unitsSigned )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsSlider( void ) const
{
   if ( GetType() == typeSlider )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsSwitch( void ) const
{
   if ( GetType() == typeSwitch )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsTime( void ) const
{
   if ( GetType() == typeTime )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsUniform( void ) const
{
   DWORD uniform = 0;

   uniform = StatusFlags & statusUniform;

   if ( uniform != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerControl::IsUnsignedUnits( void ) const
{
   if ( GetUnits() == unitsUnsigned )
   {
      return( TRUE );
   }

   return( FALSE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixerControl::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << ID;
      archive << Type;
      archive << StatusFlags;
      archive << NumberOfItemsPerChannel;
      archive << ShortName;
      archive << Name;
      archive << Minimum;
      archive << Maximum;
      archive << NumberOfSteps;
      archive << NumberOfCustomDataBytes;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> ID;
      archive >> Type;
      archive >> StatusFlags;
      archive >> NumberOfItemsPerChannel;
      archive >> ShortName;
      archive >> Name;
      archive >> Minimum;
      archive >> Maximum;
      archive >> NumberOfSteps;
      archive >> NumberOfCustomDataBytes;
   }

   Data.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

// Operators

CMixerControl& CMixerControl::operator=( const CMixerControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::operator=( CMixerControl )" ) );
   Copy( source );
   return( *this );
}

CMixerControl& CMixerControl::operator=( const MIXERCONTROL& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControl::operator=( MIXERCONTROL )" ) );
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CMixerControl</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles Mixer controls.">
</HEAD>

<BODY>

<H1>CMixerControl : CObject</H1>
$Revision: 18 $<BR><HR>

<H2>Description</H2>

This class encapsulates the MIXERCONTROL data structure. What is a MIXERCONTROL?
The way the Mixer API works is the idea of sources and controls. A control is
something you can set or read.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CMixerControl</B>()
<B>CMixerControl</B>( const CMixerControl&amp; source )
<B>CMixerControl</B>( const MIXERCONTROL&amp; source )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE><B>ID</B></PRE><DD>A unique control ID.

<DT><PRE><B>Type</B></PRE><DD>Holds the type of control. It will be one of the following:

<UL>
<LI>Custom<LI>Bass<LI>Equalizer<LI>Fader<LI>Treble<LI>Volume<LI>Mixer<LI>MultipleSelect
<LI>Mux<LI>SingleSelect<LI>BooleanMeter<LI>PeakMeter<LI>SignedMeter<LI>UnsignedMeter
<LI>Decibels<LI>Percent<LI>Signed<LI>Unsigned<LI>Pan<LI>QSoundPan<LI>Slider<LI>Boolean
<LI>Button<LI>Loudness<LI>Mono<LI>Mute<LI>OnOff<LI>StereoEnhance<LI>MicroTime<LI>MilliTime
</UL>

<DT><PRE><B>StatusFlags</B></PRE><DD>Holds several flags. Here they are:

<UL>
<LI><CODE>statusDisabled</CODE>
<LI><CODE>statusMultiple</CODE>
<LI><CODE>statusUniform</CODE>
</UL>

<DT><B>NumberOfItemsPerChannel</B><DD>Holds the number of items per channel.

<DT><PRE><B>ShortName</B></PRE><DD>Contains the short name of the control.
Example: &quot;Vol&quot;

<DT><PRE><B>Name</B></PRE><DD>Contains the long name of the control.
Example: &quot;Volume&quot;

<DT><PRE><B>Minimum</B></PRE><DD>Holds the minimum possible value.

<DT><PRE><B>Maximum</B></PRE><DD>Holds the maximum possible value.

<DT><PRE><B>NumberOfSteps</B></PRE><DD>Holds the number of steps between <B>Minimum</B>
and <B>Maximum</B>.

<DT><PRE><B>NumberOfCustomDataBytes</B></PRE><DD>Holds the number of custom data bytes.

<DT><PRE><B>Data</B></PRE><DD>Holds the custom data bytes.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const CMixerControl&amp; source )
void <B>Copy</B>( const MIXERCONTROL&amp; source )</PRE><DD>
Copies the contents of another CMixerControl or a
MIXERCONTROL data structure.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>Zeroizes the data members.

<DT><PRE>DWORD <B>GetType</B>( void ) const</PRE><DD>
Returns the type (or class) of the control. It
will be one of the following:

<UL>
<LI><CODE>typeCustom</CODE>
<LI><CODE>typeFader</CODE>
<LI><CODE>typeList</CODE>
<LI><CODE>typeMeter</CODE>
<LI><CODE>typeNumber</CODE>
<LI><CODE>typeSlider</CODE>
<LI><CODE>typeSwitch</CODE>
<LI><CODE>typeTime</CODE>
</UL>

<DT><PRE>void <B>GetTypeName</B>( CString&amp; name ) const</PRE><DD>
Returns a string containing a human readable
form for the <B>Type</B>.

<DT><PRE>DWORD <B>GetUnits</B>( void ) const</PRE><DD>
Returns the units the control is measured in. It
will return one of the following:

<UL>
<LI><CODE>unitsCustom</CODE>
<LI><CODE>unitsBoolean</CODE>
<LI><CODE>unitsSigned</CODE>
<LI><CODE>unitsUnsigned</CODE>
<LI><CODE>unitsDecibels</CODE>
<LI><CODE>unitsPercent</CODE>
</UL>

<DT><PRE>BOOL <B>IsBooleanUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses Boolean Units.
False if it doesn't.

<DT><PRE>BOOL <B>IsCustom</B>( void ) const</PRE><DD>
Returns TRUE if the control is a Custom.
False if it isn't.

<DT><PRE>BOOL <B>IsCustomUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses Custom Units.
False if it doesn't.

<DT><PRE>BOOL <B>IsDecibelsUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses Decibel Units.
False if it doesn't.

<DT><PRE>BOOL <B>IsDisabled</B>( void ) const</PRE><DD>
Returns TRUE if the control is Disabled.
False if it isn't.

<DT><PRE>BOOL <B>IsFader</B>( void ) const</PRE><DD>
Returns TRUE if the control is a Fader.
False if it isn't.

<DT><PRE>BOOL <B>IsList</B>( void ) const</PRE><DD>
Returns TRUE if the control is a list of controls.
False if it isn't.

<DT><PRE>BOOL <B>IsMeter</B>( void ) const</PRE><DD>
Returns TRUE if the control is a Meter.
False if it isn't.

<DT><PRE>BOOL <B>IsMultiple</B>( void ) const</PRE><DD>
Returns TRUE if the control is multiple.
False if it isn't.

<DT><PRE>BOOL <B>IsNumber</B>( void ) const</PRE><DD>
Returns TRUE if the control is a number.
False if it isn't.

<DT><PRE>BOOL <B>IsPercentUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses percent units.
False if it doesn't.

<DT><PRE>BOOL <B>IsSignedUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses signed number units.
False if it doesn't.

<DT><PRE>BOOL <B>IsSlider</B>( void ) const</PRE><DD>
Returns TRUE if the control is a slider.
False if it isn't.

<DT><PRE>BOOL <B>IsSwitch</B>( void ) const</PRE><DD>
Returns TRUE if the control is a switch.
False if it isn't.

<DT><PRE>BOOL <B>IsTime</B>( void ) const</PRE><DD>
Returns TRUE if the control is a time.
False if it isn't.

<DT><PRE>BOOL <B>IsUniform</B>( void ) const</PRE><DD>
Returns TRUE if the control is uniform.
False if it isn't.

<DT><PRE>BOOL <B>IsUnsignedUnits</B>( void ) const</PRE><DD>
Returns TRUE if the control uses unsigned number units.
False if it doesn't.

<DT><PRE>void <B>Serialize</B>( CArchive&amp; archive )</PRE><DD>
After all, we are a CObject...

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CMixerControl.cpp $<BR>
$Modtime: 1/04/00 5:15a $
</BODY>

</HTML>
#endif
