#if ! defined( CMSTF_CLASS_HEADER )

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
** $Workfile: csmtf.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 4:54a $
*/

#define CMSTF_CLASS_HEADER

#if ! defined( SAMS_MICROSOFT_TAPE_FORMAT_HEADER )
#include "samtf.h"
#endif

class CUINT64 : public ___SIXTY_FOUR_BIT_UNSIGNED_INTEGER
{
   public:

      // Construction

      CUINT64();
      CUINT64( const CUINT64& source );
      CUINT64( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER&  source );
      CUINT64( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER * source );
      virtual ~CUINT64();

      // Methods

      virtual void Copy( const CUINT64& source );
      virtual void Copy( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER * source );
      virtual void Copy( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER&  source );
      virtual void Empty( void );

      // Operators

      CUINT64& operator=( const CUINT64& source );
      CUINT64& operator=( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER&  source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMTFDateTime : public ___MTF_DATE_TIME
{
   public:

      // Construction

      CMTFDateTime();
      CMTFDateTime( const CMTFDateTime&   source );
      CMTFDateTime( const MTF_DATE_TIME * source );
      CMTFDateTime( const MTF_DATE_TIME&  source );
      CMTFDateTime( const CTime&          source );
      virtual ~CMTFDateTime();

      // Methods

      virtual void Convert( CTime& destination ) const;
      virtual void Copy( const CMTFDateTime& source );
      virtual void Copy( const MTF_DATE_TIME * source );
      virtual void Copy( const CTime& source );
      virtual void Empty( void );

      // Operators

      CMTFDateTime& operator=( const CMTFDateTime&  source );
      CMTFDateTime& operator=( const MTF_DATE_TIME& source );
      CMTFDateTime& operator=( const CTime&         source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMTFTapeAddress : public ___MTF_TAPE_ADDRESS
{
   public:

      // Construction

      CMTFTapeAddress();
      CMTFTapeAddress( const CMTFTapeAddress& source );
      CMTFTapeAddress( const MTF_TAPE_ADDRESS * source );
      virtual ~CMTFTapeAddress();

      // Methods

      virtual void Copy( const CMTFTapeAddress& source );
      virtual void Copy( const MTF_TAPE_ADDRESS * source );
      virtual void Empty( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMTFDataBlockHeader : public ___MTF_DB_HDR
{
   public:

      // Construction

      CMTFDataBlockHeader();
      CMTFDataBlockHeader( const CMTFDataBlockHeader& source );
      CMTFDataBlockHeader( const MTF_DB_HDR * source );
      virtual ~CMTFDataBlockHeader();

      // Methods

      virtual void Copy( const CMTFDataBlockHeader& source );
      virtual void Copy( const MTF_DB_HDR * source );
      virtual void Empty( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMTFTape : public ___MTF_TAPE
{
   public:

      // Construction

      CMTFTape();
      CMTFTape( const CMTFTape& source );
      CMTFTape( const MTF_TAPE * source );
      virtual ~CMTFTape();

      // Methods

      virtual void Copy( const CMTFTape& source );
      virtual void Copy( const MTF_TAPE * source );
      virtual void Empty( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

#endif // CMSTF_CLASS_HEADER
