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
** $Workfile: CWeather.cpp $
** $Revision: 9 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CWeather, CObject, 1 );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CWeather::CWeather()
{
   WFCLTRACEINIT( TEXT( "CWeather::CWeather()" ) );
   Empty();
}

CWeather::CWeather( const CWeather& source )
{
   WFCLTRACEINIT( TEXT( "CWeather::CWeather( CWeather )" ) );
   Copy( source );
}

CWeather::~CWeather()
{
   WFCLTRACEINIT( TEXT( "CWeather::~CWeather()" ) );
   Empty();
}

int CWeather::Compare( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::Compare()" ) );

   if ( this == &source )
   {
      return( 0 );
   }

   int compare_result = 0;

   compare_result = Location.CompareNoCase( source.Location );

   if ( compare_result != 0 )
   {
      return( compare_result );
   }

   if ( Time < source.Time )
   {
      return( -1 );
   }
   else if ( Time > source.Time )
   {
      return( 1 );
   }

   if ( Temperature < source.Temperature )
   {
      return( -1 );
   }
   else if ( Temperature > source.Temperature )
   {
      return( 1 );
   }

   if ( HumidityPercent < source.HumidityPercent )
   {
      return( -1 );
   }
   else if ( HumidityPercent > source.HumidityPercent )
   {
      return( 1 );
   }

   if ( WindSpeed < source.WindSpeed )
   {
      return( -1 );
   }
   else if ( WindSpeed > source.WindSpeed )
   {
      return( 1 );
   }

   compare_result = WindDirection.CompareNoCase( source.WindDirection );

   if ( compare_result != 0 )
   {
      return( compare_result );
   }

   if ( BarometricPressure < source.BarometricPressure )
   {
      return( -1 );
   }
   else if ( BarometricPressure > source.BarometricPressure )
   {
      return( 1 );
   }

   compare_result = Description.CompareNoCase( source.Description );

   if ( compare_result != 0 )
   {
      return( compare_result );
   }

   return( 0 );
}

void CWeather::Copy( const CWeather& source )
{
   WFCLTRACEINIT( TEXT( "CWeather::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   Temperature             = source.Temperature;
   TemperatureUnits        = source.TemperatureUnits;
   HumidityPercent         = source.HumidityPercent;
   WindSpeed               = source.WindSpeed;
   WindSpeedUnits          = source.WindSpeedUnits;
   BarometricPressure      = source.BarometricPressure;
   BarometricPressureUnits = source.BarometricPressureUnits;
   Location                = source.Location;
   WindDirection           = source.WindDirection;
   Description             = source.Description;
   Time                    = source.Time;
}

void CWeather::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CWeather::Empty()" ) );

   Temperature             = 0;
   TemperatureUnits        = 0;
   HumidityPercent         = 0;
   WindSpeed               = 0;
   WindSpeedUnits          = 0;
   BarometricPressure      = 0;
   BarometricPressureUnits = 0;
   Location.Empty();
   WindDirection.Empty();
   Description.Empty();
   Time = CTime( 0 );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CWeather::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CWeather::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Location;
      archive << Time;
      archive << Temperature;
      archive << TemperatureUnits;
      archive << HumidityPercent;
      archive << WindSpeed;
      archive << WindSpeedUnits;
      archive << WindDirection;
      archive << BarometricPressure;
      archive << BarometricPressureUnits;
      archive << Description;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Location;
      archive >> Time;
      archive >> Temperature;
      archive >> TemperatureUnits;
      archive >> HumidityPercent;
      archive >> WindSpeed;
      archive >> WindSpeedUnits;
      archive >> WindDirection;
      archive >> BarometricPressure;
      archive >> BarometricPressureUnits;
      archive >> Description;
   }
}

#endif // WFC_NO_SERIALIZATION

CWeather& CWeather::operator = ( const CWeather& source )
{
   WFCLTRACEINIT( TEXT( "CWeather::operator =()" ) );
   Copy( source );
   return( *this );
}

BOOL CWeather::operator == ( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::operator ==()" ) );

   if ( Compare( source ) == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CWeather::operator < ( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::operator <()" ) );

   if ( Compare( source ) < 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CWeather::operator > ( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::operator >()" ) );

   if ( Compare( source ) > 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CWeather::operator <= ( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::operator <=()" ) );

   if ( Compare( source ) < 1 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CWeather::operator >= ( const CWeather& source ) const
{
   WFCLTRACEINIT( TEXT( "CWeather::operator >=()" ) );

   if ( Compare( source ) > (-1) )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CWeather::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Location is               \"" ) << Location                << TEXT( "\"\n" );
   dump_context << TEXT( "   Time is                    "  ) << Time                    << TEXT( "\n" );
   dump_context << TEXT( "   Temperature is             "  ) << Temperature             << TEXT( "\n" );
   dump_context << TEXT( "   TemperatureUnits is        "  );

   if ( TemperatureUnits == Farenheit )
   {
      dump_context << TEXT( "Farenheit\n" );
   }
   else if ( TemperatureUnits == Celcius )
   {
      dump_context << TEXT( "Celcius\n" );
   }
   else
   {
      dump_context << TEXT( "Unknown( " ) << TemperatureUnits << TEXT( ")\n" );
   }
      
   dump_context << TEXT( "   HumidityPercent is         "  ) << HumidityPercent         << TEXT( "\n" );
   dump_context << TEXT( "   WindSpeed is               "  ) << WindSpeed               << TEXT( "\n" );
   dump_context << TEXT( "   WindSpeedUnits is          "  );
   
   if ( WindSpeedUnits == MilesPerHour )
   {
      dump_context << TEXT( "MilesPerHour\n" );
   }
   else if ( WindSpeedUnits == KilometersPerHour )
   {
      dump_context << TEXT( "KilometersPerHour\n" );
   }
   else
   {
      dump_context << TEXT( "Unknown (" ) << WindSpeedUnits << TEXT( ")\n" );
   }

   dump_context << TEXT( "   WindDirection is           "  ) << WindDirection           << TEXT( "\n" );
   dump_context << TEXT( "   BarometricPressure is      "  ) << BarometricPressure      << TEXT( "\n" );
   dump_context << TEXT( "   BarometricPressureUnits is "  );
   
   if ( BarometricPressureUnits == Inches )
   {
      dump_context << TEXT( "Inches\n" );
   }
   else
   {
      dump_context << TEXT( "Unknown (" ) << BarometricPressureUnits << TEXT( ")\n" );
   }
      
   dump_context << TEXT( "   Description is             \"" ) << Description             << TEXT( "\"\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source
