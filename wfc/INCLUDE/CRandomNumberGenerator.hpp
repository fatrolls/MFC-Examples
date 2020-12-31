#if ! defined ( RANDOM_NUMBER_GENERATOR_CLASS_HEADER )

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
** $Workfile: CRandomNumberGenerator.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 4:52a $
*/

#define RANDOM_NUMBER_GENERATOR_CLASS_HEADER

class CRandomNumberGenerator
{
   protected:

      double m_Array[ 97 ];
      double m_C;
      double m_Cd;
      double m_Cm;

      int m_Index_1;
      int m_Index_2;

   public:

      CRandomNumberGenerator();
      CRandomNumberGenerator( DWORD new_seed );
     ~CRandomNumberGenerator();

      /*
      ** Methods
      */

      DWORD  GetInteger( void );
      double GetFloat( void );
      void   InitializeSeed( void );
      void   SetSeed( DWORD new_seed );

      operator char();
      operator unsigned char();
      operator int();
      operator unsigned int();
      operator short();
      operator unsigned short();
      operator long();
      operator unsigned long();
      operator float();
      operator double();

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // RANDOM_NUMBER_GENERATOR_CLASS_HEADER
