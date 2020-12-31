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
** $Workfile: CMixerControlDetails.cpp $
** $Revision: 13 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CMixerControlDetails, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

// Construction

CMixerControlDetails::CMixerControlDetails()
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::CMixerControlDetails()" ) );
   Empty();
}

CMixerControlDetails::CMixerControlDetails( const CMixerControlDetails& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::CMixerControlDetails( CMixerControlDetails )" ) );
   Copy( source );
}

CMixerControlDetails::CMixerControlDetails( const MIXERCONTROLDETAILS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::CMixerControlDetails( MIXERCONTROLDETAILS )" ) );
   Copy( source );
}

CMixerControlDetails::~CMixerControlDetails()
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::~CMixerControlDetails()" ) );
   Empty();
}

// Methods

void CMixerControlDetails::Copy( const CMixerControlDetails& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::Copy( CMixerControlDetails )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   ID                              = source.ID;
   NumberOfChannels                = source.NumberOfChannels;
   WindowHandleOfOwner             = source.WindowHandleOfOwner;
   NumberOfMultipleItemsPerChannel = source.NumberOfMultipleItemsPerChannel;
}

void CMixerControlDetails::Copy( const MIXERCONTROLDETAILS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::Copy( MIXERCONTROLDETAILS )" ) );
   ID                              = source.dwControlID;
   NumberOfChannels                = source.cChannels;
   WindowHandleOfOwner             = source.hwndOwner;
   NumberOfMultipleItemsPerChannel = source.cMultipleItems;
}

// Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerControlDetails::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerControlDetails at "             ) << (VOID *) this                   << TEXT( "\n{\n" );
   dump_context << TEXT( "   ID is                              " ) << ID                              << TEXT( "\n"    );
   dump_context << TEXT( "   NumberOfChannels is                " ) << NumberOfChannels                << TEXT( "\n"    );
   dump_context << TEXT( "   WindowHandleOfOwner is             " ) << WindowHandleOfOwner             << TEXT( "\n"    );
   dump_context << TEXT( "   NumberOfMultipleItemsPerChannel is " ) << NumberOfMultipleItemsPerChannel << TEXT( "\n"    );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMixerControlDetails::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::Empty()" ) );
   ID                              = 0;
   NumberOfChannels                = 0;
   WindowHandleOfOwner             = NULL;
   NumberOfMultipleItemsPerChannel = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixerControlDetails::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << ID;
      archive << NumberOfChannels;
      archive << (DWORD) WindowHandleOfOwner;
      archive << NumberOfMultipleItemsPerChannel;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> ID;
      archive >> NumberOfChannels;

      DWORD temp_dword = 0;

      archive >> temp_dword;
      WindowHandleOfOwner = (HWND) temp_dword;
      archive >> NumberOfMultipleItemsPerChannel;
   }
}

#endif // WFC_NO_SERIALIZATION

// Operators

CMixerControlDetails& CMixerControlDetails::operator=( const CMixerControlDetails& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::operator=( CMixerControlDetails )" ) );
   Copy( source );
   return( *this );
}

CMixerControlDetails& CMixerControlDetails::operator=( const MIXERCONTROLDETAILS& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlDetails::operator=( MIXERCONTROLDETAILS )" ) );
   Copy( source );
   return( *this );
}

// End of source
