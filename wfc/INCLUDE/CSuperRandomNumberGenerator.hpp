class CSuperRandomNumberGenerator
{
   protected:

      int    m_IntegerSeeds[ 25 ];
      int    m_NextValue[ 25 ];
      double m_Seeds[ 25 ];

      double m_Carry;
      double m_TwoM12;
      double m_TwoM24;

      int m_Index_I24;
      int m_Index_J24;
      int m_Index24;

      void m_Initialize( void );

      enum
      {
         TWELVE_BIT_VALUE         = 4096,
         TWENTY_FOUR_BIT_VALUE    = 16777216,
         NUMBER_OF_VALUES_TO_SKIP = 365,
         DEFAULT_SEED_VALUE       = 314159265,
         ICONS                    = 2147483563,
      }
      constants;

   public:

      CSuperRandomNumberGenerator( DWORD seed = 0 );
     ~CSuperRandomNumberGenerator();

      double GetValue( void );
      DWORD  GetInteger( void );
      void SetSeed( DWORD seed );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};
