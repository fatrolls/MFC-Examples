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
** $Workfile: CMixerControlDetailsData.cpp $
** $Revision: 16 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CMixerControlDetailsData, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

// Construction

CMixerControlDetailsData::CMixerControlDetailsData()
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData()" ) );
   Empty();
}

CMixerControlDetailsData::CMixerControlDetailsData( const CMixerControlDetailsData& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData( CMixerControlDetailsData )" ) );
   Copy( source );
}

CMixerControlDetailsData::CMixerControlDetailsData( const MIXERCONTROLDETAILS_LISTTEXT& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData( MIXERCONTROLDETAILS_LISTTEXT )" ) );
   Copy( source );
}

CMixerControlDetailsData::CMixerControlDetailsData( const MIXERCONTROLDETAILS_BOOLEAN& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData( MIXERCONTROLDETAILS_BOOLEAN )" ) );
   Copy( source );
}

CMixerControlDetailsData::CMixerControlDetailsData( const MIXERCONTROLDETAILS_SIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData( MIXERCONTROLDETAILS_SIGNED )" ) );
   Copy( source );
}

CMixerControlDetailsData::CMixerControlDetailsData( const MIXERCONTROLDETAILS_UNSIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::CMixerControlDetailsData( MIXERCONTROLDETAILS_UNSIGNED )" ) );
   Copy( source );
}

CMixerControlDetailsData::~CMixerControlDetailsData()
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::~CMixerControlDetailsData()" ) );
   Empty();
}

void CMixerControlDetailsData::Copy( const CMixerControlDetailsData& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Copy( CMixerControlDetailsData )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Parameter1 = source.Parameter1;
   Parameter2 = source.Parameter2;
   Name       = source.Name;
}

void CMixerControlDetailsData::Copy( const MIXERCONTROLDETAILS_LISTTEXT& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Copy( MIXERCONTROLDETAILS_LISTTEXT )" ) );
   Parameter1 = source.dwParam1;
   Parameter2 = source.dwParam2;
   Name       = source.szName;
   WFCTRACEVAL( TEXT( "Name is       " ), Name       );
   WFCTRACEVAL( TEXT( "Source is     " ), Parameter1 );
   WFCTRACEVAL( TEXT( "Parameter2 is " ), Parameter2 );
}

void CMixerControlDetailsData::Copy( const MIXERCONTROLDETAILS_BOOLEAN& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Copy( MIXERCONTROLDETAILS_BOOLEAN )" ) );
   Parameter1 = source.fValue;
   Parameter2 = 0;
   Name.Empty();
}

void CMixerControlDetailsData::Copy( const MIXERCONTROLDETAILS_SIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Copy( MIXERCONTROLDETAILS_SIGNED )" ) );
   Parameter1 = source.lValue;
   Parameter2 = 0;
   Name.Empty();
}

void CMixerControlDetailsData::Copy( const MIXERCONTROLDETAILS_UNSIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Copy( MIXERCONTROLDETAILS_UNSIGNED )" ) );
   Parameter1 = source.dwValue;
   Parameter2 = 0;
   Name.Empty();
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerControlDetailsData::Dump( CDumpContext& dump_context ) const
{
   CString temp_string;

   dump_context << TEXT( "a CMixerControlDetailsData at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Parameter1 is " ) << Parameter1 << TEXT( "\n" );
   dump_context << TEXT( "   Parameter2 is " ) << Parameter2;

   if ( Name.IsEmpty() == FALSE )
   {
      if ( Parameter2 == CMixerLine::sourceUndefined )
      {
         temp_string = TEXT( "sourceUndefined" );
      }
      else if ( Parameter2 == CMixerLine::sourceDigital )
      {
         temp_string = TEXT( "sourceDigital" );
      }
      else if ( Parameter2 == CMixerLine::sourceLine )
      {
         temp_string = TEXT( "sourceLine" );
      }
      else if ( Parameter2 == CMixerLine::sourceMicrophone )
      {
         temp_string = TEXT( "sourceMicrophone" );
      }
      else if ( Parameter2 == CMixerLine::sourceSynthesizer )
      {
         temp_string = TEXT( "sourceSynthesizer" );
      }
      else if ( Parameter2 == CMixerLine::sourceCompactDisc )
      {
         temp_string = TEXT( "sourceCompactDisc" );
      }
      else if ( Parameter2 == CMixerLine::sourceTelephone )
      {
         temp_string = TEXT( "sourceTelephone" );
      }
      else if ( Parameter2 == CMixerLine::sourcePCSpeaker )
      {
         temp_string = TEXT( "sourcePCSpeaker" );
      }
      else if ( Parameter2 == CMixerLine::sourceWaveOut )
      {
         temp_string = TEXT( "sourceWaveOut" );
      }
      else if ( Parameter2 == CMixerLine::sourceAuxillary )
      {
         temp_string = TEXT( "sourceAuxillary" );
      }
      else if ( Parameter2 == CMixerLine::sourceAnalog )
      {
         temp_string = TEXT( "sourceAnalog" );
      }
      else
      {
         temp_string = TEXT( "is invalid" );
      }

      dump_context << TEXT( " ( " ) << temp_string << TEXT( " )" );
   }

   dump_context << TEXT( "\n   Name is " ) << Name << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMixerControlDetailsData::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Empty()" ) );
   Parameter1 = 0;
   Parameter2 = 0;
   Name.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixerControlDetailsData::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Parameter1;
      archive << Parameter2;
      archive << Name;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Parameter1;
      archive >> Parameter2;
      archive >> Name;
   }
}

#endif // WFC_NO_SERIALIZATION

CMixerControlDetailsData& CMixerControlDetailsData::operator = ( const CMixerControlDetailsData& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::operator=( CMixerControlDetailsData )" ) );
   Copy( source );
   return( *this );
}

CMixerControlDetailsData& CMixerControlDetailsData::operator = ( const MIXERCONTROLDETAILS_LISTTEXT& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::operator=( MIXERCONTROLDETAILS_LISTTEXT )" ) );
   Copy( source );
   return( *this );
}

CMixerControlDetailsData& CMixerControlDetailsData::operator = ( const MIXERCONTROLDETAILS_BOOLEAN& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::operator=( MIXERCONTROLDETAILS_BOOLEAN )" ) );
   Copy( source );
   return( *this );
}

CMixerControlDetailsData& CMixerControlDetailsData::operator = ( const MIXERCONTROLDETAILS_SIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::operator=( MIXERCONTROLDETAILS_SIGNED )" ) );
   Copy( source );
   return( *this );
}

CMixerControlDetailsData& CMixerControlDetailsData::operator = ( const MIXERCONTROLDETAILS_UNSIGNED& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetailsData::operator=( MIXERCONTROLDETAILS_UNSIGNED )" ) );
   Copy( source );
   return( *this );
}

// End of source
