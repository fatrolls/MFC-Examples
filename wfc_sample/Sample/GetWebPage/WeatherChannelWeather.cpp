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
** $Workfile: WeatherChannelWeather.cpp $
** $Revision: 1 $
** $Modtime: 1/02/99 7:20a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

void convert_to_bytes( const CStringArray& strings, CByteArray& bytes )
{
   int loop_index        = 0;
   int number_of_strings = strings.GetSize();
   int string_index      = 0;
   int string_length     = 0;

   CString this_string;

   bytes.RemoveAll();

   while( loop_index < number_of_strings )
   {
      this_string = strings.GetAt( loop_index );

      string_index = 0;
      string_length = this_string.GetLength();

      while( string_index < string_length )
      {
         bytes.Add( (BYTE) this_string.GetAt( string_index ) );
         string_index++;
      }

      loop_index++;
   }
}

void parse_WeatherChannel_weather_page( const CStringArray& web_page, CWeather& weather )
{
   WFCTRACEINIT( TEXT( "parse_WeatherChannel_weather_page()" ) );

   CString text( TEXT( "" ) );

   // Start with an empty weather object

   weather.Empty();

   CByteArray bytes;

   convert_to_bytes( web_page, bytes );

   // CDataParser parser( bytes );

   CParsePoint point;

#if defined( _DEBUG )
   weather.Dump( afxDump );
#endif
}
