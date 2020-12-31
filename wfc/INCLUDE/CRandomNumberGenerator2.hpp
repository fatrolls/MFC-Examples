#if ! defined ( RANDOM_NUMBER_GENERATOR_2_CLASS_HEADER )

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
** $Workfile: CRandomNumberGenerator2.hpp $
** $Revision: 3 $
** $Modtime: 1/04/00 4:52a $
*/

#define RANDOM_NUMBER_GENERATOR_2_CLASS_HEADER

class CRandomNumberGenerator2
{
   protected:

      DWORD  m_State[ 625 ];
      DWORD *m_Next;
      long   m_Left;

      DWORD m_LoadMersenneTwister( void );

   public:

      CRandomNumberGenerator2();
      CRandomNumberGenerator2( DWORD new_seed );
     ~CRandomNumberGenerator2();

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

#endif // RANDOM_NUMBER_GENERATOR_2_CLASS_HEADER
