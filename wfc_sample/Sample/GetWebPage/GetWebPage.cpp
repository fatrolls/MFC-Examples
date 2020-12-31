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
** $Workfile: GetWebPage.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:18p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

void parse_CNN_weather_page( const CStringArray& web_page, CWeather& weather );
void get_stock_quote( const CString& symbol );

void print_page( const CString& web_page_address )
{
   WFCTRACEINIT( TEXT( "print_page()" ) );

   CUniformResourceLocator url( web_page_address );

   CStringArray web_page;

   wfc_get_web_page( url, web_page );

   int index = 0;
   int number_of_lines_in_report = web_page.GetSize();

   while( index < number_of_lines_in_report )
   {
      WFCTRACE( web_page.GetAt( index ) );
      _tprintf( TEXT( "%s\n" ), (LPCTSTR) web_page.GetAt( index ) );
      index++;
   }
}

void get_pager_account_number( CString& account_number )
{
   WFCTRACEINIT( TEXT( "get_pager_account_number()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyCurrentUser ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to HKEY_CURRENT_USER" ) );
      _tprintf( TEXT( "Can't connect to current user key in registry\n" ) );
      return;
   }

   CString key_name( TEXT( "Environment" ) );

   if ( registry.Open( key_name ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open Environment key" ) );
      _tprintf( TEXT( "Can't open Environment key\n" ) );
      return;
   }

   registry.GetValue( TEXT( "PagerAccountNumber" ), account_number );
}

void print_maryland_weather( void )
{
   CUniformResourceLocator url( TEXT( "http://iwin.nws.noaa.gov/iwin/md/hourly.html" ) );

   CStringArray weather_report;

   wfc_get_web_page( url, weather_report );

   int index = 0;
   int number_of_lines_in_report = weather_report.GetSize();

   while( index < number_of_lines_in_report )
   {
      _tprintf( TEXT( "%s\n" ), (LPCTSTR) weather_report.GetAt( index ) );
      index++;
   }
}

void weather_page()
{
   WFCTRACEINIT( TEXT( "weather_page()" ) );

   CString string_to_send_to_pager;

   CRemoteAccessService ras;

   //WFCTRACELEVELON( 31 );

   if ( ras.Open( TEXT( "Erols" ) ) != FALSE )
   {
      CStringArray Baltimore_web_page;
      CStringArray Wilmington_web_page;
      CStringArray Alamagordo_web_page;

      CWeather Baltimore_weather;
      CWeather Wilmington_weather;
      CWeather Alamagordo_weather;

      CUniformResourceLocator Baltimore_url(  TEXT( "http://cnn.com/WEATHER/html/BaltimoreMD.html"  ) );
      CUniformResourceLocator Wilmington_url( TEXT( "http://cnn.com/WEATHER/html/WilmingtonNC.html" ) );
      CUniformResourceLocator Alamagordo_url( TEXT( "http://cnn.com/WEATHER/html/AlamogordoNM.html" ) );

      wfc_get_web_page( Baltimore_url,  Baltimore_web_page  );
      wfc_get_web_page( Wilmington_url, Wilmington_web_page );
      wfc_get_web_page( Alamagordo_url, Alamagordo_web_page );

      parse_CNN_weather_page( Baltimore_web_page,  Baltimore_weather  );
      parse_CNN_weather_page( Wilmington_web_page, Wilmington_weather );
      parse_CNN_weather_page( Alamagordo_web_page, Alamagordo_weather );

      string_to_send_to_pager.Format( TEXT( "BWI %s %s %d, ILM %s %s %d, ALM %s %s %d." ),
                                      (LPCTSTR) Baltimore_weather.Time.Format( TEXT( "%H" ) ),
                                      (LPCTSTR) Baltimore_weather.Description,
                                      (int)     Baltimore_weather.Temperature,
                                      (LPCTSTR) Wilmington_weather.Time.Format( TEXT( "%H" ) ),
                                      (LPCTSTR) Wilmington_weather.Description,
                                      (int)     Wilmington_weather.Temperature,
                                      (LPCTSTR) Alamagordo_weather.Time.Format( TEXT( "%H" ) ),
                                      (LPCTSTR) Alamagordo_weather.Description,
                                      (int)     Alamagordo_weather.Temperature );

      WFCTRACEVAL( TEXT( "Would send " ), string_to_send_to_pager );

      ras.HangUp( TEXT( "Erols" ) );
   }
   else
   {
      string_to_send_to_pager = TEXT( "Can't connect to Erols." );
   }

   CString account_number;

   get_pager_account_number( account_number );

   WFCTRACELEVELON( 31 );

   Sleep( 2000 );

   CSprintSpectrum pager;

   pager.SetSerialPort( TEXT( "COM2:9600,e,7,1" ) );
   pager.SetNumberOfRetries( 3 );
   pager.SetAccount( account_number );
   pager.SetMessage( string_to_send_to_pager );

   pager.Send();
}

void wait_for_ring( void )
{
   WFCTRACEINIT( TEXT( "wait_for_ring()" ) );
   CSerialFile serial;

   while( 1 )
   {
      _tprintf( TEXT( "Opening serial port\n" ) );
      WFCTRACE( TEXT( "Opening serial port" ) );

#if defined( _DEBUG )

      serial.Dump( afxDump );
#endif

      if ( serial.Open( TEXT( "COM2:57600,n,8,1" ) ) != FALSE )
      {
         BOOL return_value = FALSE;

         // First, find out how large a buffer we need for the configuration data...

         CCommunicationProperties properties;

         return_value = serial.GetProperties( properties );

         if ( return_value == FALSE )
         {
            return;
         }

#if defined( _DEBUG )

         properties.Dump( afxDump );

#endif // _DEBUG

         CCommunicationsConfiguration configuration;

         serial.GetConfiguration( configuration );

#if defined( _DEBUG )

         configuration.Dump( afxDump );

#endif // _DEBUG

         CString response;

         response = TEXT( "ATM0\r\n" );

         serial.Write( response );

         // See if the phone rang

         DWORD wait_condition = CSerialFile::waitRing;

         if ( serial.WaitFor( wait_condition ) != FALSE )
         {

#if 0
         while ( serial.WaitForString( TEXT( "RING" ), 2, &response ) == FALSE )
         {
            if ( response.GetLength() > 0 )
            {
               _tprintf( TEXT( "Didn't get RING, going to sleep \"%s\"\n" ), (LPCTSTR) response );
               WFCTRACEVAL( TEXT( "Didn't get RING, got " ), response );
            }

            ::Sleep( 10000 );
         }
#endif

            _tprintf( TEXT( "Received a RING, waiting for them to end\n" ) );
            WFCTRACE( TEXT( "Waiting for RINGs to stop" ) );

            while( serial.WaitForString( TEXT( "RING" ), 7 ) != FALSE )
            {
               // Do Nothing
            }

            _tprintf( TEXT( "Closing serial port\n" ) );

            serial.Close();

            ::Sleep( 1000 );

            weather_page();

            ::Sleep( 5000 );
         }
      }
      else
      {
         _tprintf( TEXT( "Can't open serial port\n" ) );
      }

      ::Sleep( 100000 );
   }
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEON();
   WFCTRACELEVELON( 0 );
   WFCTRACEINIT( TEXT( "main()" ) );

   CSystemTime the_time;

   the_time.Get();

   print_page( TEXT( "http://www.erols.com/dsdee/index2.html" ) );

   return( EXIT_SUCCESS );

//   weather_page();

   while( 1 )
   {
      the_time.Get();

#if defined( _DEBUG )

      the_time.Dump( afxDump );

#endif // _DEBUG

      if ( ( the_time.wHour == 19 && the_time.wMinute == 15 ) ||
           ( the_time.wHour == 0  && the_time.wMinute == 35 ) )
      {
         weather_page();
         Sleep( 62000 );
      }
      else
      {
         Sleep( 30000 );
      }
   }

   // wait_for_ring();

   //get_stock_quote( TEXT( "CSC" ) );

   return( EXIT_SUCCESS );
}
