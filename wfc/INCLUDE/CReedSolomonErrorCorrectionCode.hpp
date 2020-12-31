#if ! defined( REED_SOLOMON_ERROR_CORRECTION_CODE_CLASS_HEADER )

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
** $Workfile: CReedSolomonErrorCorrectionCode.hpp $
** $Revision: 5 $
** $Modtime: 1/04/00 4:54a $
*/

#define REED_SOLOMON_ERROR_CORRECTION_CODE_CLASS_HEADER

/*
** This class is derived from source code found at
** http://hideki.iis.u-tokyo.ac.jp/~robert/codes.html
**
** Specifically, the work done by Phil Karn KA9Q, September 1996
*/

/* Global definitions for Reed-Solomon encoder/decoder
 * Phil Karn KA9Q, September 1996
 *
 * The parameters m_NumberOfBitsPerSymbol and m_NumberOfSymbolsPerBlock specify the Reed-Solomon code parameters.
 *
 * Set m_NumberOfBitsPerSymbol to be the size of each code symbol in bits. The Reed-Solomon
 * block size will then be m_BlockSize = 2**M - 1 symbols. Supported values are
 * defined in rs.c.
 *
 * Set m_NumberOfSymbolsPerBlock to be the number of data symbols in each block, which must be
 * less than the block size. The code will then be able to correct up
 * to m_BlockSize-m_NumberOfSymbolsPerBlock erasures or (m_BlockSize-m_NumberOfSymbolsPerBlock)/2 errors, or combinations thereof with
 * each error counting as two erasures.
 */

class CReedSolomonErrorCorrectionCode
{
   protected:

      static const int m_NumberOfBitsPerSymbol; // 8 bits per symbol
      static const int m_BlockSize; // 255

      int  m_NumberOfSymbolsPerBlock;
      int *m_Alpha_to; // array of integers of size (m_BlockSize + 1) elements
      int *m_GeneratorPolynomial; // array of integers size (m_BlockSize - m_NumberOfSymbolsPerBlock + 1) elements
      int *m_Index_of; // array of integers of size (m_BlockSize + 1) elements

      int  m_PrimitivePolynomials[ 9 ]; // Array of integers

      virtual BOOL m_EncodeChunk( const CByteArray& input, CByteArray& parity );
      virtual int  m_DecodeChunk( CByteArray& chunk, CUIntArray& error_polynomials, int no_eras = 1 );
      virtual void m_GenerateGaloisField( void );
      virtual void m_GeneratePolynomial( void );
      virtual void m_Initialize( int number_of_symbols_per_block );
      inline  int  m_Mod( int x );

   public:

      CReedSolomonErrorCorrectionCode( );
      virtual ~CReedSolomonErrorCorrectionCode();

      virtual int  Decode( const CByteArray& encoded_data, CByteArray& decoded_data );
      virtual BOOL Encode( const CByteArray& data, CByteArray& encoded_data );
};

#endif // REED_SOLOMON_ERROR_CORRECTION_CODE_CLASS_HEADER
