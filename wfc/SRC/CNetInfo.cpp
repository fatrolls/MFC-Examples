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
** $Workfile: cnetinfo.cpp $
** $Revision: 18 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/*
** CNetInformation stuff
*/

CNetworkInformation::CNetworkInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::CNetworkInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CNetworkInformation::CNetworkInformation( const NETINFOSTRUCT *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::CNetworkInformation( NETINFOSTRUCT )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkInformation::CNetworkInformation( const CNetworkInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::CNetworkInformation( CNetworkInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkInformation::~CNetworkInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::~CNetworkInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CNetworkInformation::Copy( const NETINFOSTRUCT * source )
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      cbStructure       = source->cbStructure;
      dwProviderVersion = source->dwProviderVersion;
      dwStatus          = source->dwStatus;
      dwCharacteristics = source->dwCharacteristics;
      dwHandle          = source->dwHandle;
      wNetType          = source->wNetType;
      dwPrinters        = source->dwPrinters;
      dwDrives          = source->dwDrives;
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkInformation::Copy( const CNetworkInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Copy( (const NETINFOSTRUCT *) &source );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetworkInformation::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CNetworkInformation at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   cbStructure       = " ) << cbStructure       << TEXT( "\n" );
   dump_context << TEXT( "   dwProviderVersion = " ) << dwProviderVersion << TEXT( "\n" );
   dump_context << TEXT( "   dwStatus          = " ) << dwStatus          << TEXT( "\n" );
   dump_context << TEXT( "   dwCharacteristics = " ) << dwCharacteristics << TEXT( "\n" );
   dump_context << TEXT( "   dwHandle          = " ) << dwHandle          << TEXT( "\n" );
   dump_context << TEXT( "   wNetType          = " ) << wNetType          << TEXT( "\n" );
   dump_context << TEXT( "   dwPrinters        = " ) << dwPrinters        << TEXT( "\n" );
   dump_context << TEXT( "   dwDrives          = " ) << dwDrives          << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CNetworkInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkInformation::Empty()" ) );

   cbStructure       = sizeof( NETINFOSTRUCT );
   dwProviderVersion = 0;
   dwStatus          = 0;
   dwCharacteristics = 0;
   dwHandle          = 0;
   wNetType          = 0;
   dwPrinters        = 0;
   dwDrives          = 0;
}

const CNetworkInformation& CNetworkInformation::operator = ( const CNetworkInformation& source )
{
   ASSERT( this != &source );

   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

// End of source
