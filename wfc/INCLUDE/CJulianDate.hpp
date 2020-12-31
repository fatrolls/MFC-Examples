#if ! defined ( JULIAN_DATE_CLASS_HEADER )

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
** $Workfile: CJulianDate.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:48a $
*/

#define JULIAN_DATE_CLASS_HEADER

class CJulianDate // Don't use this, I'm not finished with it yet
{
   protected:

      double m_JulianDays;

   public:

      CJulianDate() { m_JulianDays = 0.0; };
      CJulianDate( const CJulianDate& source ) { m_JulianDays = source.m_JulianDays; };

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CJulianDate();

      /*
      ** Methods
      */

      inline  void   Copy( const CJulianDate& source ) { m_JulianDays = source.m_JulianDays; }; // Don't use this
      inline  double Get( void ) const { return( m_JulianDays ); }; // Don't use this
      virtual int    GetDayOfWeek( void ) const; // Don't use this
      virtual BOOL   Set( int year, int month, int day, int hours = 0, int minutes = 0, int seconds = 0 ); // Don't use this

      /*
      ** Operators
      */

      inline CJulianDate& operator=( const CJulianDate& source ) { m_JulianDays = source.m_JulianDays; return( *this ); };

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};   

#endif // JULIAN_DATE_CLASS_HEADER
