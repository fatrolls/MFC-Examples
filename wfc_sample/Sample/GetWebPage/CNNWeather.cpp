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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: CNNWeather.cpp $
** $Revision: 4 $
** $Modtime: 3/08/98 3:18p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

void parse_CNN_weather_page( const CStringArray& web_page, CWeather& weather )
{
   WFCTRACEINIT( TEXT( "parse_CNN_weather_page()" ) );

   CString text( TEXT( "" ) );

   // Start with an empty weather object

   weather.Empty();

   int line_number     = 0;
   int number_of_lines = 0;

   number_of_lines = web_page.GetSize();

   while( line_number < number_of_lines )
   {
      text += web_page.GetAt( line_number );
      //WFCTRACE( web_page.GetAt( line_number ) );
      line_number++;
   }

   line_number = 0;

   // Look for the Heading 1 line...

   BOOL found = FALSE;

   CString line;
   CString field( TEXT( "<H1 ALIGN=CENTER>" ) );

   int location_of_field = 0;

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   // Trim off the uneeded text

   WFCTRACEVAL( TEXT( "Before " ), text );
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   // We should now be at the line that looks like this:
   // <H1 ALIGN=CENTER>Baltimore, MD</H1>
   // Let's pull out the location name

   field = TEXT( "</H1>" );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   weather.Location = text.Left( location_of_field );

   WFCTRACEVAL( TEXT( "weather.Location is " ), weather.Location );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   // Now let's get the time...

   field = TEXT( "A T &nbsp;" );

   location_of_field = text.Find( field );

   int hours = 0;

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   // We should be sitting at the hours now...

   hours = _ttoi( text );

   // Now let's see if we're AM or PM

   field = TEXT( "&nbsp; " );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "Testing first character of this for p:" ), text );

   if ( text.Left( 1 ) == TEXT( 'p' ) )
   {
      if ( hours != 12 )
      {
         hours += 12;
      }
   }

   field = TEXT( "day, " );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After 168 " ), text );

   location_of_field = text.Find( TEXT( " " ) );

   WFCTRACEVAL( TEXT( "Location of field is " ), location_of_field );


   CString month_name = text.Left( location_of_field );

   month_name.TrimLeft();
   month_name.TrimRight();

   WFCTRACEVAL( TEXT( "month name is " ), month_name );

   text = text.Right( text.GetLength() - location_of_field );
   WFCTRACEVAL( TEXT( "After 175 " ), text );

   int month_number = 0;

   if ( month_name.CompareNoCase( "January" ) == 0 )
   {
      month_number = 1;
   }
   else if ( month_name.CompareNoCase( "February" ) == 0 )
   {
      month_number = 2;
   }
   else if ( month_name.CompareNoCase( "March" ) == 0 )
   {
      month_number = 3;
   }
   else if ( month_name.CompareNoCase( "April" ) == 0 )
   {
      month_number = 4;
   }
   else if ( month_name.CompareNoCase( "May" ) == 0 )
   {
      month_number = 5;
   }
   else if ( month_name.CompareNoCase( "June" ) == 0 )
   {
      month_number = 6;
   }
   else if ( month_name.CompareNoCase( "July" ) == 0 )
   {
      month_number = 7;
   }
   else if ( month_name.CompareNoCase( "August" ) == 0 )
   {
      month_number = 8;
   }
   else if ( month_name.CompareNoCase( "September" ) == 0 )
   {
      month_number = 9;
   }
   else if ( month_name.CompareNoCase( "October" ) == 0 )
   {
      month_number = 10;
   }
   else if ( month_name.CompareNoCase( "November" ) == 0 )
   {
      month_number = 11;
   }
   else if ( month_name.CompareNoCase( "December" ) == 0 )
   {
      month_number = 12;
   }
   else
   {
      month_number = 1;
   }

   WFCTRACEVAL( TEXT( "month number is " ), month_number );

   // Trim of what we just parsed
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After 240 " ), text );

   int day = 0;

   day = _ttoi( text );

   WFCTRACEVAL( TEXT( "day is " ), day );

   field = TEXT( ", " );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   int year = 0;

   year = _ttoi( text );

   line.Format( TEXT( "Calling CTime( %d, %d, %d, %d, 0, 0 )" ), year, month_number, day, hours );
   WFCTRACE( line );

   weather.Time = CTime( year, month_number, day, hours, 0, 0 );

   field = TEXT( "Temp.:" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   field = TEXT( "<B>" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   weather.Temperature = _ttoi( text );

   WFCTRACEVAL( TEXT( "Temp is " ), weather.Temperature );

   // Now get the temperature units

   field = TEXT( "; " );

   location_of_field = text.Find( field );

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   if ( text.GetAt( 1 ) == TEXT( 'C' ) ||
        text.GetAt( 1 ) == TEXT( 'c' ) )
   {
      weather.TemperatureUnits = CWeather::Celcius;
   }
   else
   {
      weather.TemperatureUnits = CWeather::Farenheit;
   }

   field = TEXT( "Humid.:" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   field = TEXT( "<B>" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   weather.HumidityPercent = _ttoi( text );

   WFCTRACEVAL( TEXT( "Humidity is " ), weather.HumidityPercent );

   field = TEXT( "Wind:" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   field = TEXT( "<B>" );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   // Now let's get the wind direction

   field = TEXT( " " );

   location_of_field = text.Find( field );

   weather.WindDirection = text.Left( location_of_field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   field = TEXT( "at " );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   weather.WindSpeed = _ttoi( text );

   field = TEXT( " " );

   location_of_field = text.Find( field );

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

   field = TEXT( "</B>" );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      return;
   }

   field = text.Left( location_of_field );

   if ( field.CompareNoCase( TEXT( "mph" ) ) == 0 )
   {
      weather.WindSpeedUnits = CWeather::MilesPerHour;
   }
   else
   {
      weather.WindSpeedUnits = CWeather::KilometersPerHour;
   }

   // Trim of what we just parsed
   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   text.TrimLeft();

   WFCTRACEVAL( TEXT( "After " ), text );

#if defined( _DEBUG )
   weather.Dump( afxDump );
#endif
}
