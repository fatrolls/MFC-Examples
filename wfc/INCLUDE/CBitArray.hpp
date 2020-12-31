#if ! defined( BIT_ARRAY_CLASS_HEADER )

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
** $Workfile: CBitArray.hpp $
** $Revision: 7 $
** $Modtime: 1/04/00 4:39a $
*/

#define BIT_ARRAY_CLASS_HEADER

class CBitArray
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CBitArray )
#endif // WFC_NO_SERIALIZATION

   protected:

      static const int m_SizeOfBitRepresentation;
      static const int m_MostSignificantBitLocation;

      CDWordArray m_Bits;

      DWORD m_TotalNumberOfBits;
      DWORD m_IndexOfFirstBit;

#if ! defined( _DEBUG )

      inline

#endif // _DEBUG

      BOOL m_GetElementIndexOfBitLocation( const DWORD bit_location, DWORD& index, DWORD * bit_number_in_element = NULL ) const;

#if defined( _DEBUG )

      int m_NumberOfBitsPerGroup;
      int m_NumberOfGroupsPerLine;

#endif // _DEBUG

   public:

      // Construction

      CBitArray();
      CBitArray( DWORD initial_size );
      CBitArray( const CBitArray&  source );
      CBitArray( const CByteArray& source );

      virtual ~CBitArray();

      // Methods

      virtual void      Add( DWORD bit_to_add, DWORD count = 1 );
      virtual void      AddByte( BYTE byte_to_add );
      virtual void      AddValue( DWORD value_to_add, DWORD number_of_bits_in_value );
      virtual void      Append( const CBitArray& source );
      virtual void      Append( const BYTE * data, DWORD number_of_bytes );
      virtual void      Complement( void );
      virtual void      Copy( const CBitArray& source );
      virtual void      Copy( const CByteArray& source );
      virtual void      CopyTo( CByteArray& destination );
      virtual void      CopyTo( CDWordArray& destination );
      virtual BOOL      Find( const CBitArray& value, DWORD& found_at, DWORD starting_at = 0 ) const;
      virtual BOOL      Find( DWORD value, DWORD number_of_bits_in_value, DWORD& found_at_index, DWORD starting_at = 0 ) const;
      virtual void      FreeExtra( void );
      virtual DWORD     GetAt( DWORD index ) const;
      virtual DWORD     GetNumberOfOnes( void ) const;
      virtual DWORD     GetNumberOfZeroes( void ) const;
      virtual DWORD     GetSize( void ) const;
      virtual DWORD     GetUpperBound( void ) const;
      virtual DWORD     GetValue( DWORD index, DWORD length ) const;
      virtual void      InsertAt( DWORD index, DWORD value );
      virtual CBitArray Left( DWORD number_of_bits ) const;
      virtual void      LeftTrim( DWORD number_of_bits );
      virtual CBitArray Mid( DWORD starting_at_index, DWORD number_of_bits ) const;
      virtual void      RemoveAll( void );
      virtual void      RemoveAt( DWORD index );
      virtual CBitArray Right( DWORD number_of_bits ) const;
      virtual void      RightTrim( DWORD number_of_bits );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void      Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual void      SetAll( DWORD value );
      virtual void      SetAt( DWORD index, DWORD value );
      virtual void      SetSize( DWORD number_of_bits );
      virtual void      SetValue( DWORD index, DWORD value, DWORD length );

      // Operators

      virtual CBitArray& operator =  ( const CBitArray&  source );
      virtual CBitArray& operator =  ( const CByteArray& source );
      virtual CBitArray& operator += ( const CBitArray&  source );
      virtual CBitArray& operator += ( const CByteArray& source );
      virtual DWORD      operator [] ( int index ) const;

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;
      virtual void SetDumpOptions( int number_of_bits_per_group, int number_of_groups_per_line );

#endif // _DEBUG
};

#if ! defined( _DEBUG )

inline BOOL CBitArray::m_GetElementIndexOfBitLocation( const DWORD bit_location, DWORD& index, DWORD * bit_number_p ) const
{
   index = ( bit_location + m_IndexOfFirstBit ) / m_SizeOfBitRepresentation;

   if ( bit_number_p != NULL )
   {
      *bit_number_p = m_MostSignificantBitLocation - ( ( bit_location + m_IndexOfFirstBit ) % m_SizeOfBitRepresentation );
   }

   return( TRUE );
}

#endif // _DEBUG


#endif // BIT_ARRAY_CLASS_HEADER
