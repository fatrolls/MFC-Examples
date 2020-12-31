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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CReedSolomonErrorCorrectionCode.cpp $
** $Revision: 16 $
** $Modtime: 1/17/00 9:12a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// Helper functions

#define CLEAR(a,n) {\
   int ci;\
   for(ci=(n)-1;ci >=0;ci--)\
      (a)[ci] = 0;\
   }

#define COPY(a,b,n) {\
   int ci;\
   for(ci=(n)-1;ci >=0;ci--)\
      (a)[ci] = (b)[ci];\
   }

#define COPYDOWN(a,b,n) {\
   int ci;\
   for(ci=(n)-1;ci >=0;ci--)\
      (a)[ci] = (b)[ci];\
   }

inline int CReedSolomonErrorCorrectionCode::m_Mod( int x )
{
   while ( x >= m_BlockSize )
   {
      x -= m_BlockSize;
      x = ( x >> m_NumberOfBitsPerSymbol ) + ( x & m_BlockSize );
   }

   return( x );
}

// The class

const int CReedSolomonErrorCorrectionCode::m_NumberOfBitsPerSymbol = 8;
const int CReedSolomonErrorCorrectionCode::m_BlockSize             = 255; // (1 << m_NumberOfBitsPerSymbol) - 1

CReedSolomonErrorCorrectionCode::CReedSolomonErrorCorrectionCode()
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::CReedSolomonErrorCorrectionCode()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_NumberOfSymbolsPerBlock = 0;
   m_Alpha_to                = NULL;
   m_GeneratorPolynomial     = NULL;
   m_Index_of                = NULL;

   /*
   ** Primitive polynomials - see Lin & Costello, Appendix A,
   ** and Lee & Messerschmitt, p. 453.
   */

   m_PrimitivePolynomials[ 0 ] = 1;
   m_PrimitivePolynomials[ 1 ] = 0;
   m_PrimitivePolynomials[ 2 ] = 1;
   m_PrimitivePolynomials[ 3 ] = 1;
   m_PrimitivePolynomials[ 4 ] = 1;
   m_PrimitivePolynomials[ 5 ] = 0;
   m_PrimitivePolynomials[ 6 ] = 0;
   m_PrimitivePolynomials[ 7 ] = 0;
   m_PrimitivePolynomials[ 8 ] = 1;

   m_Initialize( 223 );
}

CReedSolomonErrorCorrectionCode::~CReedSolomonErrorCorrectionCode()
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::~CReedSolomonErrorCorrectionCode()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_Alpha_to != NULL )
   {
      delete [] m_Alpha_to;
      m_Alpha_to = NULL;
   }

   if ( m_GeneratorPolynomial != NULL )
   {
      delete [] m_GeneratorPolynomial;
      m_GeneratorPolynomial = NULL;
   }

   if ( m_Index_of != NULL )
   {
      delete [] m_Index_of;
      m_Index_of = NULL;
   }
}

int CReedSolomonErrorCorrectionCode::Decode( const CByteArray& encoded_data, CByteArray& decoded_data )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::Decode()" ) );

   // Start with a virgin array

   decoded_data.RemoveAll();

   // Encoded data must be in 255 byte chunks
   ASSERT( ( encoded_data.GetSize() % 255 ) == 0 );

   if ( ( encoded_data.GetSize() % 255 ) != 0 )
   {
      WFCTRACE( TEXT( "Encoded data has an invalid length" ) );
      return( -1 );
   }

   CByteArray chunk;
   CUIntArray errors;

   int number_of_errors_corrected               = 0;
   int number_of_errors_corrected_in_this_chunk = 0;

   DWORD encoded_data_length = encoded_data.GetSize();
   DWORD encoded_data_index  = 0;

   DWORD chunk_index  = 0;
   BYTE  chunk_length = 0;

   chunk.SetSize( 255 );

   while( encoded_data_index < encoded_data_length )
   {
      chunk_index = 0;

      while( chunk_index < 255 )
      {
         chunk.SetAt( chunk_index, encoded_data.GetAt( encoded_data_index + chunk_index ) );
         chunk_index++;
      }

      number_of_errors_corrected_in_this_chunk = m_DecodeChunk( chunk, errors );

      if ( number_of_errors_corrected_in_this_chunk < 0 )
      {
         WFCTRACEVAL( TEXT( "Can't fix errors in chunk " ), ( encoded_data_index / 255 ) + 1 );
         return( -1 );
      }

      number_of_errors_corrected += number_of_errors_corrected_in_this_chunk;

      // Now pull out the data bytes

      chunk_length = chunk.GetAt( 0 );
      chunk_index  = 0;

      while( chunk_index < chunk_length )
      {
         decoded_data.Add( chunk.GetAt( chunk_index + 1 ) );
         chunk_index++;
      }

      encoded_data_index += 255;
   }

   return( number_of_errors_corrected );
}

BOOL CReedSolomonErrorCorrectionCode::Encode( const CByteArray& data, CByteArray& encoded_data )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::Encode()" ) );

   CByteArray chunk;
   CByteArray parity;

   // Start with a virgin array

   encoded_data.RemoveAll();

   // We must chunkify the data into 222 byte pieces. This leaves us room for
   // a one-byte data-length value and 1 bit per byte parity (255 bits == 32 bytes)

   DWORD data_length = data.GetSize();
   DWORD data_index       = 0;

   DWORD chunk_index  = 0;
   BYTE  chunk_length = 0;

   while( data_index < data_length )
   {
      chunk_index  = 0;
      chunk_length = 0;

      chunk.RemoveAll();
      parity.RemoveAll();

      chunk.Add( 0 ); // Place holder for packet length

      while( chunk_index < 222 )
      {
         if ( ( chunk_index + data_index ) < data_length )
         {
            chunk.Add( data.GetAt( chunk_index + data_index ) );
            chunk_length++;
         }
         else
         {
            chunk.Add( 0 ); // Filler byte
         }

         chunk_index++;
      }

      // Now set the number of user bytes in this packet

      chunk.SetAt( 0, chunk_length );

      // Now let's perform the old Reed & Solomon magic...

      if ( m_EncodeChunk( chunk, parity ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't encode chunk!" ) );
         return( FALSE );
      }

      encoded_data.Append( chunk  );
      encoded_data.Append( parity );

      data_index += 222;
   }

   return( TRUE );
}

/*
 * Performs ERRORS+ERASURES decoding of RS codes. If decoding is successful,
 * writes the codeword into data[] itself. Otherwise data[] is unaltered.
 *
 * Return number of symbols corrected, or -1 if codeword is illegal
 * or uncorrectable.
 * 
 * First "no_eras" erasures are declared by the calling program. Then, the
 * maximum # of errors correctable is t_after_eras = floor((m_BlockSize-m_NumberOfSymbolsPerBlock-no_eras)/2).
 * If the number of channel errors is not greater than "t_after_eras" the
 * transmitted codeword will be recovered. Details of algorithm can be found
 * in R. Blahut's "Theory ... of Error-Correcting Codes".
 */

int CReedSolomonErrorCorrectionCode::m_DecodeChunk( CByteArray& data, CUIntArray& eras_pos, int no_eras )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::m_DecodeBlock()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   WFCTRACEVAL( TEXT( "Number of bytes in block is " ), data.GetSize() );

   ASSERT( data.GetSize() == m_BlockSize );

   // During testing, this code GPF'd. Oh well.

   int deg_lambda                 = 0;
   int el                         = 0;
   int deg_omega                  = 0;
   int i                          = 0;
   int j                          = 0;
   int step_number                = 0;
   int u                          = 0;
   int q                          = 0;
   int tmp                        = 0;
   int num1                       = 0;
   int num2                       = 0;
   int denominator                = 0;
   int discrepancy_at_step_number = 0;
   int syndrome_error             = 0;
   int count                      = 0;

   int *recd   = NULL;
   int *lambda = NULL;
   int *s      = NULL;
   int *b      = NULL;
   int *t      = NULL;
   int *omega  = NULL;
   int *root   = NULL;
   int *reg    = NULL;
   int *loc    = NULL;

   try
   {
      recd   = new int[ m_BlockSize ];
      lambda = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      s      = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      /* Err+Eras Locator poly and syndrome poly */
      b      = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      t      = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      omega  = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      root   = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock     ];
      reg    = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
      loc    = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock     ];

      eras_pos.SetSize( m_BlockSize - m_NumberOfSymbolsPerBlock );

      /* data[] is in polynomial form, copy and convert to index form */
      for ( i = m_BlockSize-1; i >= 0; i-- )
      {
         recd[ i ] = m_Index_of[ data.GetAt( i ) ];
      }

      /* first form the syndromes; i.e., evaluate recd(x) at roots of g(x)
       * namely @**(1+i), i = 0, ... ,(m_BlockSize-m_NumberOfSymbolsPerBlock-1)
       */

      syndrome_error = 0;

      for ( i = 1; i <= m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
      {
         tmp = 0;

         for ( j = 0; j < m_BlockSize; j++ )
         {
            if ( recd[ j ] != m_BlockSize ) /* recd[j] in index form */
            {
               tmp ^= m_Alpha_to[ m_Mod( recd[ j ] + ( 1 + i - 1 ) * j ) ];
            }

            syndrome_error |= tmp; /* set flag if non-zero syndrome =>error store syndrome in index form  */
         }

         s[ i ] = m_Index_of[ tmp ];
      }

      if ( ! syndrome_error )
      {
         /*
          * if syndrome is zero, data[] is a codeword and there are no
          * errors to correct. So return data[] unmodified
          */

         delete [] recd;
         delete [] lambda;
         delete [] s;
         delete [] b;
         delete [] t;
         delete [] omega;
         delete [] root;
         delete [] reg;
         delete [] loc;

         return( 0 );
      }

      CLEAR( &lambda[ 1 ], m_BlockSize - m_NumberOfSymbolsPerBlock );

      lambda[ 0 ] = 1;

      if ( no_eras > 0 )
      {
         /* Init lambda to be the erasure locator polynomial */
         lambda[ 1 ] = m_Alpha_to[ eras_pos.GetAt( 0 ) ];

         for ( i = 1; i < no_eras; i++ )
         {
            u = eras_pos.GetAt( i );

            for ( j = i + 1; j > 0; j-- )
            {
               tmp = m_Index_of[ lambda[ j - 1 ] ];

               if( tmp != m_BlockSize )
               {
                  lambda[ j ] ^= m_Alpha_to[ m_Mod( u + tmp ) ];
               }
            }
         }
      }

      for( i = 0; i < m_BlockSize - m_NumberOfSymbolsPerBlock + 1; i++ )
      {
         b[ i ] = m_Index_of[ lambda[ i ] ];
      }

      /*
       * Begin Berlekamp-Massey algorithm to determine error+erasure
       * locator polynomial
       */

      step_number = no_eras;
      el = no_eras;

      while ( ++step_number <= m_BlockSize - m_NumberOfSymbolsPerBlock )
      {  /* r is the step number */
         /* Compute discrepancy at the r-th step in poly-form */

         discrepancy_at_step_number = 0;

         for ( i = 0; i < step_number; i++ )
         {
            if ( ( lambda[ i ] != 0 ) && ( s[ step_number - i ] != m_BlockSize ) )
            {
               discrepancy_at_step_number ^= m_Alpha_to[ m_Mod( m_Index_of[ lambda[ i ] ] + s[ step_number - i ] ) ];
            }
         }

         discrepancy_at_step_number = m_Index_of[ discrepancy_at_step_number ]; /* Index form */

         if ( discrepancy_at_step_number == m_BlockSize )
         {
            /* 2 lines below: B(x) <-- x*B(x) */
            COPYDOWN( &b[ 1 ], b, m_BlockSize - m_NumberOfSymbolsPerBlock );
            b[ 0 ] = m_BlockSize;
         }
         else
         {
            /* 7 lines below: T(x) <-- lambda(x) - discr_r*x*b(x) */
            t[ 0 ] = lambda[ 0 ];

            for ( i = 0 ; i < m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
            {
               if( b[ i ] != m_BlockSize )
               {
                  t[ i + 1 ] = lambda[ i + 1 ] ^ m_Alpha_to[ m_Mod( discrepancy_at_step_number + b[ i ] ) ];
               }
               else
               {
                  t[ i + 1 ] = lambda[ i + 1 ];
               }
            }

            if ( 2 * el <= step_number + no_eras - 1 )
            {
               el = step_number + no_eras - el;

               /*
                * 2 lines below: B(x) <-- inv(discrepancy_at_step_number) * lambda(x)
                */

                for ( i = 0; i <= m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
                {
                   b[ i ] = ( lambda[ i ] == 0 ) ? m_BlockSize : m_Mod( m_Index_of[ lambda[ i ] ] - discrepancy_at_step_number + m_BlockSize );
                }
            }
            else
            {
               /* 2 lines below: B(x) <-- x*B(x) */
               COPYDOWN( &b[ 1 ], b, m_BlockSize - m_NumberOfSymbolsPerBlock );
               b[ 0 ] = m_BlockSize;
            }

            // The code has been known to die here
            COPY( lambda, t, m_BlockSize - m_NumberOfSymbolsPerBlock + 1 );
         }
      }

      /* Convert lambda to index form and compute deg(lambda(x)) */

      deg_lambda = 0;

      for( i = 0; i < m_BlockSize - m_NumberOfSymbolsPerBlock + 1; i++ )
      {
         lambda[ i ] = m_Index_of[ lambda[ i ] ];

         if( lambda[ i ] != m_BlockSize )
         {
            deg_lambda = i;
         }
      }

      /*
       * Find roots of the error+erasure locator polynomial. By Chien
       * Search
       */

      COPY( &reg[ 1 ], &lambda[ 1 ], m_BlockSize - m_NumberOfSymbolsPerBlock );

      count = 0; /* Number of roots of lambda(x) */

      for ( i = 1; i <= m_BlockSize; i++ )
      {
         q = 1;

         for ( j = deg_lambda; j > 0; j-- )
         {
            if ( reg[ j ] != m_BlockSize )
            {
               reg[ j ] = m_Mod( reg[ j ] + j );
               q ^= m_Alpha_to[ reg[ j ] ];
            }
         }

         if ( ! q )
         {
            /* store root (index-form) and error location number */
            root[ count ] = i;
            loc[ count ] = m_BlockSize - i;
            count++;
         }
      }

#if defined( _DEBUG ) && ! defined( WFC_STL )
      TRACE( TEXT( "\n Final error positions:\t") );
      for ( i = 0; i < count; i++ )
      {
         TRACE( TEXT( "%d " ), loc[ i ] );
      }
      TRACE( TEXT( "\n" ) );
#endif

      if ( deg_lambda != count )
      {
         /*
          * deg(lambda) unequal to number of roots => uncorrectable
          * error detected
          */

         delete [] recd;
         delete [] lambda;
         delete [] s;
         delete [] b;
         delete [] t;
         delete [] omega;
         delete [] root;
         delete [] reg;
         delete [] loc;

         return( -1 );
      }

      /*
       * Compute err+eras evaluator poly omega(x) = s(x)*lambda(x) (modulo
       * x**(m_BlockSize-m_NumberOfSymbolsPerBlock)). in index form. Also find deg(omega).
       */

      deg_omega = 0;

      for ( i = 0; i < m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
      {
         tmp = 0;
         j = (deg_lambda < i) ? deg_lambda : i;

         for( ;j >= 0; j-- )
         {
            if ( ( s[ i + 1 - j ] != m_BlockSize ) && ( lambda[ j ] != m_BlockSize ) )
            {
               tmp ^= m_Alpha_to[ m_Mod( s[ i + 1 - j ] + lambda[ j ] ) ];
            }
         }

         if( tmp != 0 )
         {
            deg_omega = i;
         }

         omega[ i ] = m_Index_of[ tmp ];
      }

      omega[ m_BlockSize - m_NumberOfSymbolsPerBlock ] = m_BlockSize;

      /*
       * Compute error values in poly-form. num1 = omega(inv(X(l))), num2 =
       * inv(X(l))**(1-1) and den = lambda_pr(inv(X(l))) all in poly-form
       */

      for ( j = count - 1; j >= 0; j-- )
      {
         num1 = 0;

         for ( i = deg_omega; i >= 0; i-- )
         {
            if ( omega[ i ] != m_BlockSize )
            {
               num1  ^= m_Alpha_to[ m_Mod( omega[ i ] + i * root[ j ] ) ];
            }
         }

         num2 = m_Alpha_to[ m_Mod( root[ j ] * (1 - 1) + m_BlockSize ) ];
         denominator = 0;

         /* lambda[i+1] for i even is the formal derivative lambda_pr of lambda[i] */

         for ( i = min( deg_lambda, m_BlockSize - m_NumberOfSymbolsPerBlock - 1 ) & ~1; i >= 0; i -=2 )
         {
            if( lambda[ i + 1 ] != m_BlockSize )
            {
               denominator ^= m_Alpha_to[ m_Mod( lambda[ i + 1 ] + i * root[ j ] ) ];
            }
         }

         if ( denominator == 0 )
         {
            WFCTRACE( TEXT( "ERROR: denominator = 0" ) );
            delete [] recd;
            delete [] lambda;
            delete [] s;
            delete [] b;
            delete [] t;
            delete [] omega;
            delete [] root;
            delete [] reg;
            delete [] loc;

            return( -1 );
         }

         /* Apply error to data */

         if ( num1 != 0 )
         {
            data.ElementAt( loc[ j ] ) ^= m_Alpha_to[ m_Mod( m_Index_of[ num1 ] + m_Index_of[ num2 ] + m_BlockSize - m_Index_of[ denominator ] ) ];
         }
      }

      delete [] recd;
      delete [] lambda;
      delete [] s;
      delete [] b;
      delete [] t;
      delete [] omega;
      delete [] root;
      delete [] reg;
      delete [] loc;

      return( count );
   }
   catch( ... )
   {
      WFCTRACE( TEXT( "Exception caught\n" ) );

      try
      {
         delete [] recd;
         delete [] lambda;
         delete [] s;
         delete [] b;
         delete [] t;
         delete [] omega;
         delete [] root;
         delete [] reg;
         delete [] loc;
      }
      catch( ... )
      {
      }

      return( -1 );
   }
}

/*
 * take the string of symbols in data[i], i=0..(k-1) and encode
 * systematically to produce m_BlockSize-m_NumberOfSymbolsPerBlock parity symbols in parity[0]..parity[m_BlockSize-m_NumberOfSymbolsPerBlock-1] data[]
 * is input and parity[] is output in polynomial form. Encoding is done by using
 * a feedback shift register with appropriate connections specified by the
 * elements of m_GeneratorPolynomial[], which was generated above. Codeword is   c(X) =
 * data(X)*X**(m_BlockSize-m_NumberOfSymbolsPerBlock)+ b(X)
 */

// data.GetSize() must be equal to m_NumberOfSymbolsPerBlock

BOOL CReedSolomonErrorCorrectionCode::m_EncodeChunk( const CByteArray& data, CByteArray& parity )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::m_EncodeBlock()" ) );

   register int i = 0;
   register int j = 0;

   int feedback = 0;

   parity.SetSize( m_BlockSize - m_NumberOfSymbolsPerBlock );

   for ( i = m_NumberOfSymbolsPerBlock - 1; i >= 0; i-- )
   {
      feedback = m_Index_of[ data.GetAt( i ) ^ parity.GetAt( m_BlockSize - m_NumberOfSymbolsPerBlock - 1 ) ];

      if ( feedback != m_BlockSize )
      { /* feedback term is non-zero */
         for ( j = m_BlockSize - m_NumberOfSymbolsPerBlock - 1; j > 0; j-- )
         {
            if ( m_GeneratorPolynomial[ j ] != m_BlockSize )
            {
               parity.ElementAt( j ) = (BYTE) ( parity.GetAt( j - 1 ) ^ m_Alpha_to[ m_Mod( m_GeneratorPolynomial[ j ] + feedback ) ] );
            }
            else
            {
               parity.ElementAt( j ) = parity.GetAt( j - 1 );
            }
         }

         parity.ElementAt( 0 ) = (BYTE) ( m_Alpha_to[ m_Mod( m_GeneratorPolynomial[ 0 ] + feedback ) ] );
      }
      else
      { /* feedback term is zero. encoder becomes a single-byte shifter */
         for ( j = m_BlockSize - m_NumberOfSymbolsPerBlock - 1; j > 0; j-- )
         {
            parity.SetAt( j, parity.GetAt( j - 1 ) );
         }

         parity.SetAt( 0, 0 );
      }
   }

   return( TRUE );
}

/* generate GF(2**m) from the irreducible polynomial p(X) in p[0]..p[m]
   lookup tables:  index->polynomial form   alpha_to[] contains j=alpha**i;
                   polynomial form -> index form  index_of[j=alpha**i] = i
   alpha=2 is the primitive element of GF(2**m)
   HARI's COMMENT: (4/13/94) alpha_to[] can be used as follows:
        Let @ represent the primitive element commonly called "alpha" that
   is the root of the primitive polynomial p(x). Then in GF(2^m), for any
   0 <= i <= 2^m-2,
        @^i = a(0) + a(1) @ + a(2) @^2 + ... + a(m-1) @^(m-1)
   where the binary vector (a(0),a(1),a(2),...,a(m-1)) is the representation
   of the integer "alpha_to[i]" with a(0) being the LSB and a(m-1) the MSB. Thus for
   example the polynomial representation of @^5 would be given by the binary
   representation of the integer "alpha_to[5]".
                   Similarily, index_of[] can be used as follows:
        As above, let @ represent the primitive element of GF(2^m) that is
   the root of the primitive polynomial p(x). In order to find the power
   of @ (alpha) that has the polynomial representation
        a(0) + a(1) @ + a(2) @^2 + ... + a(m-1) @^(m-1)
   we consider the integer "i" whose binary representation with a(0) being LSB
   and a(m-1) MSB is (a(0),a(1),...,a(m-1)) and locate the entry
   "index_of[i]". Now, @^index_of[i] is that element whose polynomial 
    representation is (a(0),a(1),a(2),...,a(m-1)).
   NOTE:
        The element alpha_to[2^m-1] = 0 always signifying that the
   representation of "@^infinity" = 0 is (0,0,0,...,0).
        Similarily, the element index_of[0] = m_BlockSize always signifying
   that the power of alpha which has the polynomial representation
   (0,0,...,0) is "infinity".
*/

void CReedSolomonErrorCorrectionCode::m_GenerateGaloisField( void )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::m_GenerateGaloisField()" ) );

   register int loop_index = 0;
   register int mask       = 1;

   m_Alpha_to[ m_NumberOfBitsPerSymbol ] = 0;

   for ( loop_index = 0; loop_index < m_NumberOfBitsPerSymbol; loop_index++ )
   {
      m_Alpha_to[ loop_index ] = mask;
      m_Index_of[ m_Alpha_to[ loop_index ] ] = loop_index;

      /* If PrimitivePolynomials[loop_index] == 1 then, term @^loop_index occurs in poly-repr of @^m_NumberOfBitsPerSymbol */

      if ( m_PrimitivePolynomials[ loop_index ] != 0)
      {
         m_Alpha_to[ m_NumberOfBitsPerSymbol ] ^= mask; /* Bit-wise EXOR operation */
      }

      mask <<= 1; /* single left-shift */
   }

   m_Index_of[ m_Alpha_to[ m_NumberOfBitsPerSymbol ] ] = m_NumberOfBitsPerSymbol;

   /*
    * Have obtained poly-repr of @^m_NumberOfBitsPerSymbol. Poly-repr of @^(loop_index+1) is given by
    * poly-repr of @^loop_index shifted left one-bit and accounting for any @^m_NumberOfBitsPerSymbol
    * term that may occur when poly-repr of @^loop_index is shifted.
    */

   mask >>= 1;

   for ( loop_index = m_NumberOfBitsPerSymbol + 1; loop_index < m_BlockSize; loop_index++ )
   {
      if ( m_Alpha_to[ loop_index - 1 ] >= mask )
      {
         m_Alpha_to[ loop_index ] = m_Alpha_to[ m_NumberOfBitsPerSymbol ] ^ ( ( m_Alpha_to[ loop_index - 1 ] ^ mask ) << 1 );
      }
      else
      {
         m_Alpha_to[ loop_index ] = m_Alpha_to[ loop_index - 1 ] << 1;
      }

      m_Index_of[ m_Alpha_to[ loop_index ] ] = loop_index;
   }

   m_Index_of[ 0 ] = m_BlockSize;
   m_Alpha_to[ m_BlockSize ] = 0;
}

/*
 * Obtain the generator polynomial of the TT-error correcting, length
 * m_BlockSize=(2**m_NumberOfBitsPerSymbol -1) Reed Solomon code from the product of (X+@**(1+i)), i = 0,
 * ... ,(2*TT-1)
 *
 * Examples:
 *
 * If 1 = 1, TT = 1. deg(g(x)) = 2*TT = 2.
 * g(x) = (x+@) (x+@**2)
 *
 * If 1 = 0, TT = 2. deg(g(x)) = 2*TT = 4.
 * g(x) = (x+1) (x+@) (x+@**2) (x+@**3)
 */

void CReedSolomonErrorCorrectionCode::m_GeneratePolynomial( void )
{
   register int i = 0;
   register int j = 0;

   m_GeneratorPolynomial[ 0 ] = m_Alpha_to[ 1 ];
   m_GeneratorPolynomial[ 1 ] = 1;   /* g(x) = (X+@**1) initially */

   for ( i = 2; i <= m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
   {
      m_GeneratorPolynomial[ i ] = 1;

      /*
       * Below multiply (m_GeneratorPolynomial[0]+m_GeneratorPolynomial[1]*x + ... +m_GeneratorPolynomial[i]x^i) by
       * (@**(1+i-1) + x)
       */

      for ( j = i - 1; j > 0; j-- )
      {
         if ( m_GeneratorPolynomial[ j ] != 0 )
         {
            m_GeneratorPolynomial[ j ] = m_GeneratorPolynomial[ j - 1 ] ^ m_Alpha_to[ m_Mod( ( m_Index_of[ m_GeneratorPolynomial[ j ] ] ) + 1 + i - 1 ) ];
         }
         else
         {
            m_GeneratorPolynomial[ j ] = m_GeneratorPolynomial[ j - 1 ];
         }
      }

      /* m_GeneratorPolynomial[0] can never be zero */

      m_GeneratorPolynomial[ 0 ] = m_Alpha_to[ m_Mod( ( m_Index_of[ m_GeneratorPolynomial[ 0 ] ] ) + 1 + i - 1 ) ];
   }

   /* convert m_GeneratorPolynomial[] to index form for quicker encoding */

   for ( i = 0; i <= m_BlockSize - m_NumberOfSymbolsPerBlock; i++ )
   {
      m_GeneratorPolynomial[ i ] = m_Index_of[ m_GeneratorPolynomial[ i ] ];
   }
}

void CReedSolomonErrorCorrectionCode::m_Initialize( int number_of_symbols_per_block )
{
   WFCLTRACEINIT( TEXT( "CReedSolomonErrorCorrectionCode::m_Initialize()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( number_of_symbols_per_block == m_NumberOfSymbolsPerBlock )
   {
      // We don't need to initialize
      return;
   }

   m_NumberOfSymbolsPerBlock = number_of_symbols_per_block;

   if ( m_Alpha_to != NULL )
   {
      delete [] m_Alpha_to;
      m_Alpha_to = NULL;
   }

   if ( m_GeneratorPolynomial != NULL )
   {
      delete [] m_GeneratorPolynomial;
      m_GeneratorPolynomial = NULL;
   }

   if ( m_Index_of != NULL )
   {
      delete [] m_Index_of;
      m_Index_of = NULL;
   }

   ASSERT( m_NumberOfSymbolsPerBlock < m_BlockSize );

   if ( m_NumberOfSymbolsPerBlock >= m_BlockSize )
   {
      return;
   }

   // m_NumberOfSymbolsPerBlock = 223; // so you will have 255

   try
   {
      m_Alpha_to = new int[ m_BlockSize + 1 ];
   }
   catch( ... )
   {
      m_Alpha_to = NULL;
   }

   try
   {
      m_Index_of = new int[ m_BlockSize + 1 ];
   }
   catch( ... )
   {
      m_Index_of = NULL;
   }

   try
   {
      m_GeneratorPolynomial = new int[ m_BlockSize - m_NumberOfSymbolsPerBlock + 1 ];
   }
   catch( ... )
   {
      m_GeneratorPolynomial = NULL;
   }

   m_GenerateGaloisField();
   m_GeneratePolynomial();
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CReedSolomonErrorCorrectionCode</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code, FEC">
<META name="description" content="The C++ class that lets you add forward error correction (FEC) to data blocks. It automatically fixes data errors when it decodes the data.">
</HEAD>

<BODY>

<H1>CReedSolomonErrorCorrectionCode</H1>
$Revision: 16 $

<HR>

<H2>Description</H2>

This class makes it easy to add forward error correction (FEC) to
data. This classes uses the Reed-Solomon method.

<H2>Data Members</H2><B>None.</B><P>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>int <B>Decode</B>( const CByteArray&amp; encoded_data, CByteArray&amp; decoded_data )</PRE><DD>
Decodes the data and fixes any transmission errors. The return code will be
the number of errors corrected on success or -1 on failure.

<DT><PRE>BOOL <B>Encode</B>( const CByteArray&amp; data, CByteArray&amp; encoded_data )</PRE><DD>
Adds the Reed-Solomon encoding to the data.

</DL>

<H2>Notes</H2>

This algorithm generates a parity of 1 bit per byte. Output data is padded
to blocks of 255 bytes. The input is blocked into data chunks of 222 bytes.
This allows for a 1 byte block length. This given, if you need to add
forward error correction to a packet of data that is 250 bytes long, the
resulting encoded data packet will be 510 bytes long.

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CReedSolomonErrorCorrectionCode( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CReedSolomonErrorCorrectionCode()&quot; ) );

   <B>CReedSolomonErrorCorrectionCode</B> transmitter;

   CByteArray data;

   data.Add( 'A' );

   data.InsertAt( 0, 'A', 220 );

   CByteArray encoded_data;

   if ( transmitter.Encode( data, encoded_data ) == FALSE )
   {
      _tprintf( TEXT( &quot;Can't encode\n&quot; ) );
      return;
   }

   // We have encoded the data. Time to transmit it.

   // Now the parity for the data is computed. Let's muck with the data

   // Here's our sloppy communications path. It adds errors to the data

   <A HREF="CRandomNumberGenerator.htm">CRandomNumberGenerator</A> random_number;
   
   // Add some errors

   int number_of_errors_to_introduce = encoded_data.GetSize() / 16;
   int error_number = 0;

   _tprintf( TEXT( &quot;Adding %d errors to the data\n&quot; ), number_of_errors_to_introduce );

   int index = 0;

   BYTE random_value = 0;

   DWORD value = 0;

   while( error_number &lt; number_of_errors_to_introduce )
   {
      value = random_number.GetInteger();
      random_value = value % 256;

      // Make sure we're introducing an error

      while( random_value == 'A' )
      {
         value = random_number.GetInteger();
         random_value = value % 256;
      }

      index = random_number.GetInteger() % encoded_data.GetSize();

      _tprintf( TEXT( &quot;Setting data.ElementAt( %d ) to %02X\n&quot; ), index, (int) random_value );

      encoded_data.ElementAt( index ) = random_value;

      error_number++;
   }

   // We would now transmit data to the receiver

   <B>CReedSolomonErrorCorrectionCode</B> receiver;

   CByteArray decoded_data;

   int number_of_errors_corrected = receiver.Decode( encoded_data, decoded_data );

   if ( number_of_errors_corrected != (-1) )
   {
      // SUCCESS!

      _tprintf( TEXT( &quot;Decoded!\n&quot; ) );
   }

   _tprintf( TEXT( &quot;Number of errors corrected %d\n&quot; ), number_of_errors_corrected );
   _tprintf( TEXT( &quot;Number of bytes in decoded data %d\n&quot; ), decoded_data.GetSize() );

   if ( data.GetSize() != decoded_data.GetSize() )
   {
      _tprintf( TEXT( &quot;FAILED length test\n&quot; ) );
      _tprintf( TEXT( &quot;Original length was %d&quot; ), data.GetSize() );
      _tprintf( TEXT( &quot;Decoded length was %d\n&quot; ), decoded_data.GetSize() );
      return;
   }

   index = 0;

   while( index &lt; decoded_data.GetSize() )
   {
      if ( data.GetAt( index ) != decoded_data.GetAt( index ) )
      {
         WFCTRACEVAL( TEXT( &quot;Comparison failed at byte %d\n&quot; ), index );
      }

      index++;
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CReedSolomonErrorCorrectionCode.cpp $<BR>
$Modtime: 1/17/00 9:12a $
</BODY>

</HTML>
#endif
