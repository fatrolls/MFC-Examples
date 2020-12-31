#include <wfc.h>
#pragma hdrstop

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CStockQuote
{
   public:

      CStockQuote();
     ~CStockQuote();

      CString Name;
      CString Symbol;
      CTime   Time;
      double  Price;
      double  Change;

      void Empty( void );
};

CStockQuote::CStockQuote()
{
   WFCTRACEINIT( TEXT( "CStockQuote::CStockQuote()" ) );
   Empty();
}

CStockQuote::~CStockQuote()
{
   WFCTRACEINIT( TEXT( "CStockQuote::~CStockQuote()" ) );
   Empty();
}

void CStockQuote::Empty( void )
{
   WFCTRACEINIT( TEXT( "CStockQuote::Empty()" ) );

   Name.Empty();
   Symbol.Empty();
   Price  = 0.0;
   Change = 0.0;
}

void get_stock_quote( const CString& symbol )
{
   WFCTRACEINIT( TEXT( "get_stock_quote()" ) );

   CStockQuote quote;

   CString temp_string( TEXT( "http://fast.quote.com/fq/quotecom/quote?symbols=" ) );

   temp_string += symbol;

   CUniformResourceLocator quote_url( temp_string );

   CStringArray web_page;

   wfc_get_web_page( quote_url, web_page );

   int index           = 0;
   int number_of_lines = web_page.GetSize();

   CString text( TEXT( "" ) );

   while( index < number_of_lines )
   {
      text += web_page.GetAt( index );
      index++;
   }

   CString field( TEXT( ">Volume</FONT></TH>" ) );

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

   // Now find the </FONT> tag that ends the symbol name

   field = TEXT( "</FONT>" );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   index = location_of_field;

   while( text.GetAt( index ) != TEXT( '>' ) && index > 0 )
   {
      index--;
   }

   quote.Symbol = text.Mid( index + 1, location_of_field - ( index + 1 ) );

   WFCTRACEVAL( TEXT( "Symbol is " ), quote.Symbol );

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   index = location_of_field;

   while( text.GetAt( index ) != TEXT( '>' ) && index > 0 )
   {
      index--;
   }

   temp_string = text.Mid( index + 1, location_of_field - ( index + 1 ) );

   WFCTRACEVAL( TEXT( "temp_string is " ), temp_string );

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   int month = _ttoi( temp_string );

   if ( month > 9 )
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 3 );
   }
   else
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 2 );
   }

   int day = _ttoi( temp_string );

   if ( day > 9 )
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 3 );
   }
   else
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 2 );
   }

   int year = 1900 + _ttoi( temp_string );

   // Now let's get the time

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   index = location_of_field;

   while( text.GetAt( index ) != TEXT( '>' ) && index > 0 )
   {
      index--;
   }

   temp_string = text.Mid( index + 1, location_of_field - ( index + 1 ) );

   WFCTRACEVAL( TEXT( "temp_string is " ), temp_string );

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   int hours = _ttoi( temp_string );

   if ( hours > 9 )
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 3 );
   }
   else
   {
      temp_string = temp_string.Right( temp_string.GetLength() - 2 );
   }

   int minutes = _ttoi( temp_string );

   quote.Time = CTime( year, month, day, hours, minutes, 0 );

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   // Trim off the "Open" price data

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   // Trim off the "High" price data

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   // Trim off the "Low" price data

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   // Now go to the </FONT> field immediately after "Last"

   location_of_field = text.Find( field );

   if ( location_of_field == (-1) )
   {
      WFCTRACEVAL( TEXT( "Can't find " ), field );
      WFCTRACEVAL( TEXT( "In " ), text );
      return;
   }

   index = location_of_field;

   while( text.GetAt( index ) != TEXT( '>' ) && index > 0 )
   {
      index--;
   }

   temp_string = text.Mid( index + 1, location_of_field - ( index + 1 ) );

   WFCTRACEVAL( TEXT( "temp_string is " ), temp_string );

   text = text.Right( text.GetLength() - ( location_of_field + field.GetLength() ) );
   WFCTRACEVAL( TEXT( "After " ), text );

   int whole_part = _ttoi( temp_string );

   quote.Price = (double) whole_part;

   location_of_field = temp_string.Find( TEXT( ' ' ) );

   if ( location_of_field != (-1) )
   {
      int top = 0;

      temp_string = temp_string.Right( temp_string.GetLength() - ( location_of_field + 1 ) );

      WFCTRACEVAL( TEXT( "temp_string is " ), temp_string );

      top = _ttoi( temp_string );

      location_of_field = temp_string.Find( TEXT( '/' ) );

      if ( location_of_field != (-1) )
      {
         int bottom = 0;

         temp_string = temp_string.Right( temp_string.GetLength() - ( location_of_field + 1 ) );

         WFCTRACEVAL( TEXT( "temp_string is " ), temp_string );

         bottom = _ttoi( temp_string );

         if ( bottom != 0 )
         {
            quote.Price += (double)( (double) top / (double) bottom );
         }
         else
         {
            WFCTRACE( TEXT( "Divide by zero avoided" ) );
         }
      }
   }

   WFCTRACEVAL( TEXT( "Price is " ), quote.Price );
}