#if ! defined( TIME_EX_CLASS_HEADER_FILE )

#define TIME_EX_CLASS_HEADER_FILE

class CTimeSpan
{
   protected:

      time_t m_NumberOfSeconds;

   public:

      inline  CTimeSpan() { m_NumberOfSeconds = 0; }
      inline  CTimeSpan( unsigned long number_of_seconds ) { m_NumberOfSeconds = number_of_seconds; }
      inline  CTimeSpan( unsigned long days, unsigned long hours, unsigned long minutes, unsigned long number_of_seconds )
      {
         m_NumberOfSeconds  = number_of_seconds;
         m_NumberOfSeconds += ( minutes * 60L );
         m_NumberOfSeconds += ( 60L * 60L * hours );
         m_NumberOfSeconds += ( 24L * 60L * 60L * days );
      }
      inline CTimeSpan( const CTimeSpan& source ) { m_NumberOfSeconds = source.m_NumberOfSeconds; }
      inline ~CTimeSpan() { m_NumberOfSeconds = 0; }

      inline long   GetTotalHours( void ) const { return( m_NumberOfSeconds / 3600L ); }
      inline long   GetTotalMinutes( void ) const { return( m_NumberOfSeconds / 60L ); }
      inline time_t GetTotalSeconds( void ) const { return( m_NumberOfSeconds ); }
      inline long   GetDays( void ) const { return( m_NumberOfSeconds / 86400L ); }
      inline long   GetHours( void ) const { return( GetTotalHours() - ( GetDays() * 24L ) ); }
      inline long   GetMinutes( void ) const { return( GetTotalMinutes() - ( GetTotalHours() * 60L ) ); }
      inline long   GetSeconds( void ) const { return( GetTotalSeconds() - ( GetTotalMinutes() * 60L ) ); }
      inline CTimeSpan operator-( const CTimeSpan& source ) const { return( CTimeSpan( m_NumberOfSeconds - source.m_NumberOfSeconds ) ); }
      inline CTimeSpan operator+( const CTimeSpan& source ) const { return( CTimeSpan( m_NumberOfSeconds + source.m_NumberOfSeconds ) ); }
      inline const CTimeSpan& operator+=( const CTimeSpan& source ) { m_NumberOfSeconds += source.m_NumberOfSeconds; return( *this ); }
      inline const CTimeSpan& operator-=( const CTimeSpan& source ) { m_NumberOfSeconds -= source.m_NumberOfSeconds; return( *this ); }
      inline BOOL operator == ( const CTimeSpan& source ) const { return( m_NumberOfSeconds == source.m_NumberOfSeconds ); }
      inline BOOL operator != ( const CTimeSpan& source ) const { return( m_NumberOfSeconds != source.m_NumberOfSeconds ); }
      inline BOOL operator < ( const CTimeSpan& source ) const  { return( m_NumberOfSeconds <  source.m_NumberOfSeconds ); }
      inline BOOL operator > ( const CTimeSpan& source ) const  { return( m_NumberOfSeconds >  source.m_NumberOfSeconds ); }
      inline BOOL operator <= ( const CTimeSpan& source ) const { return( m_NumberOfSeconds <= source.m_NumberOfSeconds ); }
      inline BOOL operator >= ( const CTimeSpan& source ) const { return( m_NumberOfSeconds >= source.m_NumberOfSeconds ); }

      CString Format( LPCTSTR format_string ) const;
};

class CTimeEx
{
   protected:

      time_t m_Time;

      time_t m_Make_time_t( const struct tm * time_p );

   public:

      // Construction

      CTimeEx();
      CTimeEx( const CTimeEx&    source );
      CTimeEx( const CTimeEx *   source );
      CTimeEx( const time_t      source );
      CTimeEx( const struct tm * source );
      CTimeEx( const struct tm&  source );
      CTimeEx( int year, int month, int day, int hour, int minute, int second, int daylight_savings_time = -1 );
     ~CTimeEx();

      // Methods

      static void GetCurrentTheTime( CTimeEx& source );
      static void GreenwichMeanTime( const time_t * address_of_a_time_t, struct tm * address_of_a_tm_structure );

      int    Compare( const CTimeEx& source ) const;
      void   Copy( const CTimeEx&    source );
      void   Copy( const CTimeEx *   source );
      void   Copy( const time_t      source );
      void   Copy( const struct tm * source );
      void   Copy( const struct tm&  source );
      void   CopyModifiedJulianDate( double source );
      void   CopyTo( time_t&    destination ) const;
      void   CopyTo( struct tm& destination ) const;
      void   CopyTo( CString& iso_8601_date ) const;
      void   Empty( void );
      CString Format( LPCTSTR format_string ) const; // same as strftime
      int    GetDay( void ) const;
      int    GetDayOfWeek( void ) const;
      int    GetDayOfYear( void ) const;
      int    GetHour( void ) const;
      int    GetMinute( void ) const;
      int    GetMonth( void ) const;
      int    GetSecond( void ) const;
      void   GetTime( struct tm& time_structure ) const;
      time_t GetTotalSeconds( void ) const;
      int    GetYear( void ) const;
      void   Set( const CString& iso_8601_date );
      void   Set( int year, int month, int day, int hour, int minute, int second, int daylight_savings_time = -1 );

      // Operators

      inline                 operator time_t     ( void                     ) const { return( m_Time ); };
      inline       CTimeEx&  operator =          ( const CTimeEx&    source )       { Copy( source ); return( *this ); };
      inline       CTimeEx&  operator =          ( const time_t      source )       { Copy( source ); return( *this ); };
      inline       CTimeEx&  operator =          ( const struct tm&  source )       { Copy( source ); return( *this ); };
      inline       BOOL      operator ==         ( const CTimeEx&    source ) const { return( ( Compare( source ) == 0   ) ? TRUE  : FALSE ); };
      inline       BOOL      operator !=         ( const CTimeEx&    source ) const { return( ( Compare( source ) == 0   ) ? FALSE : TRUE  ); };
      inline       BOOL      operator >=         ( const CTimeEx&    source ) const { return( ( Compare( source ) > (-1) ) ? TRUE  : FALSE ); };
      inline       BOOL      operator <=         ( const CTimeEx&    source ) const { return( ( Compare( source ) < 1    ) ? TRUE  : FALSE ); };
      inline       BOOL      operator >          ( const CTimeEx&    source ) const { return( ( Compare( source ) > 0    ) ? TRUE  : FALSE ); };
      inline       BOOL      operator <          ( const CTimeEx&    source ) const { return( ( Compare( source ) < 0    ) ? TRUE  : FALSE ); };
      inline       CTimeSpan operator -          ( const CTimeEx&    source ) const { return( CTimeSpan( m_Time - source.m_Time ) ); };
      inline       CTimeEx   operator -          ( const CTimeSpan&  source ) const { return( CTimeEx( m_Time - source.GetTotalSeconds() ) ); };
      inline       CTimeEx   operator +          ( const CTimeSpan&  source ) const { return( CTimeEx( m_Time + source.GetTotalSeconds() ) ); };
      inline const CTimeEx&  operator +=         ( const CTimeSpan&  source )       { m_Time += source.GetTotalSeconds(); return( *this ); };
      inline const CTimeEx&  operator -=         ( const CTimeSpan&  source )       { m_Time -= source.GetTotalSeconds(); return( *this ); };
};

class CTime
{
   protected:

      CTimeEx m_Time;

   public:

      inline CTime(){};
      inline CTime( time_t the_time ) : m_Time( the_time ) {};
      inline CTime( int year, int month, int day, int hour, int minute, int second, int daylight_savings_time = -1 )
      {
         m_Time = CTimeEx( year, month, day, hour, minute, second, daylight_savings_time );
      }

      inline ~CTime() {};

      static CTime PASCAL GetCurrentTime() { CTimeEx the_time; CTimeEx::GetCurrentTheTime( the_time ); return( CTime( (time_t) the_time ) ); }

      // Snap all of the calls to CTimeEx

      inline CString Format( LPCTSTR format_string ) const { return( m_Time.Format( format_string ) ); }
      inline int GetDay(       void ) const { return( m_Time.GetDay()       ); }
      inline int GetDayOfWeek( void ) const { return( m_Time.GetDayOfWeek() ); }
      inline int GetHour(      void ) const { return( m_Time.GetHour()      ); }
      inline int GetMinute(    void ) const { return( m_Time.GetMinute()    ); }
      inline int GetMonth(     void ) const { return( m_Time.GetMonth()     ); }
      inline int GetSecond(    void ) const { return( m_Time.GetSecond()    ); }
      inline int GetYear(      void ) const { return( m_Time.GetYear()      ); }

      inline                 operator time_t     ( void                     ) const { return( m_Time.operator time_t() ); }
      inline       CTime&    operator =          ( const CTime&      source )       { m_Time.Copy( source.m_Time ); return( *this ); }
      inline       CTime&    operator =          ( const time_t      source )       { m_Time.Copy( source        ); return( *this ); }
      inline       CTime&    operator =          ( const struct tm&  source )       { m_Time.Copy( source        ); return( *this ); }
      inline       BOOL      operator ==         ( const CTime&      source ) const { return( m_Time.operator==( source.m_Time ) ); }
      inline       BOOL      operator !=         ( const CTime&      source ) const { return( m_Time.operator!=( source.m_Time ) ); }
      inline       BOOL      operator >=         ( const CTime&      source ) const { return( m_Time.operator>=( source.m_Time ) ); }
      inline       BOOL      operator <=         ( const CTime&      source ) const { return( m_Time.operator<=( source.m_Time ) ); }
      inline       BOOL      operator >          ( const CTime&      source ) const { return( m_Time.operator> ( source.m_Time ) ); }
      inline       BOOL      operator <          ( const CTime&      source ) const { return( m_Time.operator< ( source.m_Time ) ); }
      inline       CTimeSpan operator -          ( const CTime&      source ) const { return( m_Time.operator- ( source.m_Time ) ); }
      inline       CTime     operator -          ( const CTimeSpan&  source ) const { return( m_Time.operator- ( source        ) ); }
      inline       CTime     operator +          ( const CTimeSpan&  source ) const { return( m_Time.operator+ ( source        ) ); }
      inline const CTime&    operator +=         ( const CTimeSpan&  source )       { m_Time += source; return( *this ); }
      inline const CTime&    operator -=         ( const CTimeSpan&  source )       { m_Time -= source; return( *this ); }
};

#endif // TIME_EX_CLASS_HEADER_FILE
