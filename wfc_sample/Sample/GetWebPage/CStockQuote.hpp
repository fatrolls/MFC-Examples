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