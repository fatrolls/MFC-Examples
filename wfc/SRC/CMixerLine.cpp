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
** $Workfile: CMixerLine.cpp $
** $Revision: 14 $
** $Modtime: 2/03/00 6:57p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CMixerLine, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

// Construction

CMixerLine::CMixerLine()
{
   WFCLTRACEINIT( TEXT( "CMixerLine::CMixerLine()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMixerLine::CMixerLine( const CMixerLine& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::CMixerLine()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerLine::CMixerLine( const MIXERLINE& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::CMixerLine()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerLine::~CMixerLine()
{
   WFCLTRACEINIT( TEXT( "CMixerLine::~CMixerLine()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void CMixerLine::Copy( const CMixerLine& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::Copy( CMixerLine )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   DestinationNumber   = source.DestinationNumber;
   Source              = source.Source;
   ID                  = source.ID;
   Status              = source.Status;
   Reserved            = source.Reserved;
   Component           = source.Component;
   NumberOfChannels    = source.NumberOfChannels;
   NumberOfConnections = source.NumberOfConnections;
   NumberOfControls    = source.NumberOfControls;
   Target              = source.Target;
   TargetDeviceID      = source.TargetDeviceID;
   TargetManufacturer  = source.TargetManufacturer;
   TargetProduct       = source.TargetProduct;
   TargetDriverVersion = source.TargetDriverVersion;
   ShortName           = source.ShortName;
   Name                = source.Name;
   TargetName          = source.TargetName;
}

void CMixerLine::Copy( const MIXERLINE& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::Copy( MIXERLINE )" ) );

   DestinationNumber   = source.dwDestination;
   Source              = source.dwSource;
   ID                  = source.dwLineID;
   Status              = source.fdwLine;
   Reserved            = source.dwUser;
   Component           = source.dwComponentType;
   NumberOfChannels    = source.cChannels;
   NumberOfConnections = source.cConnections;
   NumberOfControls    = source.cControls;
   Target              = source.Target.dwType;
   TargetDeviceID      = source.Target.dwDeviceID;
   TargetManufacturer  = source.Target.wMid;
   TargetProduct       = source.Target.wPid;
   TargetDriverVersion = source.Target.vDriverVersion;
   ShortName           = source.szShortName;
   Name                = source.szName;
   TargetName          = source.Target.szPname;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerLine::Dump( CDumpContext& dump_context ) const
{
   CString temp_string;

   dump_context << TEXT( "a CMixerLine at "           ) << (VOID *) this     << TEXT( "\n{\n" );
   dump_context << TEXT( "   ShortName is           " ) << ShortName         << TEXT( "\n" );
   dump_context << TEXT( "   Name is                " ) << Name              << TEXT( "\n" );
   dump_context << TEXT( "   DestinationNumber is   " ) << DestinationNumber << TEXT( "\n" );
   dump_context << TEXT( "   Source is              " ) << Source            << TEXT( "\n" );
   dump_context << TEXT( "   ID is                  " ) << ID                << TEXT( "\n" );

   GetStatus( temp_string );
   dump_context << TEXT( "   Status is              " ) << temp_string       << TEXT( "\n" );
   dump_context << TEXT( "   Reserved is            " ) << Reserved          << TEXT( "\n" );
   
   GetComponent( temp_string );
   dump_context << TEXT( "   Component is           " ) << temp_string         << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfChannels is    " ) << NumberOfChannels    << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfConnections is " ) << NumberOfConnections << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfControls is    " ) << NumberOfControls    << TEXT( "\n" );

   GetTarget( temp_string );
   dump_context << TEXT( "   Target is              " ) << temp_string         << TEXT( "\n" );
   dump_context << TEXT( "   TargetName is          " ) << TargetName          << TEXT( "\n" );
   dump_context << TEXT( "   TargetDeviceID is      " ) << TargetDeviceID      << TEXT( "\n" );
   dump_context << TEXT( "   TargetManufacturer is  " ) << TargetManufacturer  << TEXT( "\n" );
   dump_context << TEXT( "   TargetProduct is       " ) << TargetProduct       << TEXT( "\n" );
   dump_context << TEXT( "   TargetDriverVersion is " ) << TargetDriverVersion << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMixerLine::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::Empty()" ) );

   DestinationNumber   = 0;
   Source              = 0;
   ID                  = 0;
   Status              = 0;
   Reserved            = 0;
   Component           = 0;
   NumberOfChannels    = 0;
   NumberOfConnections = 0;
   NumberOfControls    = 0;
   Target              = 0;
   TargetDeviceID      = 0;
   TargetManufacturer  = 0;
   TargetProduct       = 0;
   TargetDriverVersion = 0;
   ShortName.Empty();
   Name.Empty();
   TargetName.Empty();
}

void CMixerLine::GetComponent( CString& component_string ) const
{
   switch( Component )
   {
      case destinationUndefined:

         component_string = TEXT( "Undefined Destination" );
         break;

      case destinationDigital:

         component_string = TEXT( "Digital Destination" );
         break;

      case destinationLine:

         component_string = TEXT( "Line Destination" );
         break;

      case destinationMonitor:

         component_string = TEXT( "Monitor Destination" );
         break;

      case destinationSpeakers:

         component_string = TEXT( "Speakers Destination" );
         break;

      case destinationHeadphones:

         component_string = TEXT( "Headphones Destination" );
         break;

      case destinationTelephone:

         component_string = TEXT( "Telephone Destination" );
         break;

      case destinationWaveIn:

         component_string = TEXT( "Wave In Destination" );
         break;

      case destinationVoiceIn:

         component_string = TEXT( "Voice In Destination" );
         break;

      case sourceUndefined:

         component_string = TEXT( "Undefined Source" );
         break;

      case sourceDigital:

         component_string = TEXT( "Digital Source" );
         break;

      case sourceLine:

         component_string = TEXT( "Line Source" );
         break;

      case sourceMicrophone:

         component_string = TEXT( "Microphone Source" );
         break;

      case sourceSynthesizer:

         component_string = TEXT( "Synthesizer Source" );
         break;

      case sourceCompactDisc:

         component_string = TEXT( "Compact Disc Source" );
         break;

      case sourceTelephone:

         component_string = TEXT( "Telephone Source" );
         break;

      case sourcePCSpeaker:

         component_string = TEXT( "PC Speaker Source" );
         break;

      case sourceWaveOut:

         component_string = TEXT( "Wave Out Source" );
         break;

      case sourceAuxillary:

         component_string = TEXT( "Auxillary Source" );
         break;

      case sourceAnalog:

         component_string = TEXT( "Analog Source" );
         break;

      default:

         component_string.Format( TEXT( "Unknown (%lu)" ), Component );
         break;
   }
}

void CMixerLine::GetStatus( CString& status_string ) const
{
   status_string.Empty();

   if ( Status & statusActive )
   {
      status_string = TEXT( "Active" );
   }

   if ( Status & statusDisconnected )
   {
      if ( status_string.GetLength() > 0 )
      {
         status_string += TEXT( ", " );
      }

      status_string += TEXT( "Disconnected" );
   }

   if ( Status & statusSource )
   {
      if ( status_string.GetLength() > 0 )
      {
         status_string += TEXT( ", " );
      }

      status_string += TEXT( "Source" );
   }
}

void CMixerLine::GetTarget( CString& target_string ) const
{
   switch( Target )
   {
      case targetUndefined:

         target_string = TEXT( "Undefined" );
         break;

      case targetWaveOut:

         target_string = TEXT( "Wave Out" );
         break;

      case targetWaveIn:

         target_string = TEXT( "Wave In" );
         break;

      case targetMidiOut:

         target_string = TEXT( "MIDI Out" );
         break;

      case targetMidiIn:

         target_string = TEXT( "MIDI In" );
         break;

      case targetAuxillary:

         target_string = TEXT( "Aux" );
         break;

      default:

         target_string.Format( TEXT( "Unknown (%lu)" ), Target );
         break;
   }
}

BOOL CMixerLine::IsActive( void ) const
{
   DWORD active = 0;

   active = Status & statusActive;

   if ( active != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerLine::IsDisconnected( void ) const
{
   DWORD disconnected = 0;

   disconnected = Status & statusDisconnected;

   if ( disconnected != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerLine::IsSource( void ) const
{
   DWORD source = 0;

   source = Status & statusSource;

   if ( source != 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixerLine::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive >> DestinationNumber;
      archive >> Source;
      archive >> ID;
      archive >> Status;
      archive >> Reserved;
      archive >> Component;
      archive >> NumberOfChannels;
      archive >> NumberOfConnections;
      archive >> NumberOfControls;
      archive >> ShortName;
      archive >> Name;
      archive >> Target;
      archive >> TargetDeviceID;
      archive >> TargetManufacturer;
      archive >> TargetProduct;
      archive >> TargetDriverVersion;
      archive >> TargetName;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive << DestinationNumber;
      archive << Source;
      archive << ID;
      archive << Status;
      archive << Reserved;
      archive << Component;
      archive << NumberOfChannels;
      archive << NumberOfConnections;
      archive << NumberOfControls;
      archive << ShortName;
      archive << Name;
      archive << Target;
      archive << TargetDeviceID;
      archive << TargetManufacturer;
      archive << TargetProduct;
      archive << TargetDriverVersion;
      archive << TargetName;
   }
}

#endif // WFC_NO_SERIALIZATION

CMixerLine& CMixerLine::operator=( const CMixerLine& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::operator=( CMixerLine )" ) );
   Copy( source );
   return( *this );
}

CMixerLine& CMixerLine::operator=( const MIXERLINE& source )
{
   WFCLTRACEINIT( TEXT( "CMixerLine::operator=( MIXERLINE )" ) );
   Copy( source );
   return( *this );
}

// End of source
