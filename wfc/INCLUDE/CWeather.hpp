#if ! defined( WEATHER_CLASS_HEADER_FILE )

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
** $Workfile: CWeather.hpp $
** $Revision: 6 $
** $Modtime: 1/04/00 4:58a $
*/

#define WEATHER_CLASS_HEADER_FILE

class CWeather
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CWeather )
#endif // WFC_NO_SERIALIZATION

   public:

      CWeather();
      CWeather( const CWeather& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CWeather();

      enum _TemperatureUnits
      {
         Farenheit,
         Celcius
      };

      enum _WindSpeedUnits
      {
         MilesPerHour,
         KilometersPerHour
      };

      enum _BarometricPressureUnits
      {
         Inches
      };

      /*
      ** Data
      */

      CString Location;
      CTime   Time;
      double  Temperature;
      int     TemperatureUnits;
      double  HumidityPercent;
      double  WindSpeed;
      int     WindSpeedUnits;
      CString WindDirection;
      double  BarometricPressure;
      int     BarometricPressureUnits;
      CString Description;

      /*
      ** Methods
      */

      virtual int  Compare( const CWeather& source ) const;
      virtual void Copy( const CWeather& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      /*
      ** Operators
      */

      virtual CWeather& operator = ( const CWeather& source );
      virtual BOOL operator == ( const CWeather& source ) const;
      virtual BOOL operator <  ( const CWeather& source ) const;
      virtual BOOL operator >  ( const CWeather& source ) const;
      virtual BOOL operator <= ( const CWeather& source ) const;
      virtual BOOL operator >= ( const CWeather& source ) const;

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

#endif // EVENT_LOG_CLASS
