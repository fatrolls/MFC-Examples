#if ! defined( DATA_CHUNK_CLASS_HEADER )

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
** $Workfile: CDataChunk.hpp $
** $Revision: 8 $
** $Modtime: 1/20/00 4:36p $
*/

#define DATA_CHUNK_CLASS_HEADER

#define MAKE_DATA_ID( byte_1, byte_2, byte_3, byte_4 ) \
   ( (DWORD) (BYTE) (byte_1)         | ( (DWORD) (BYTE) (byte_2) <<  8 ) | \
   ( (DWORD) (BYTE) (byte_3) << 16 ) | ( (DWORD) (BYTE) (byte_4) << 24 ) )

#define MAKE_DATA_DWORD( byte_1, byte_2, byte_3, byte_4 ) MAKE_DATA_ID( byte_1, byte_2, byte_3, byte_4 )

#define MAKE_DATA_LENGTH( byte_1, byte_2, byte_3, byte_4 ) MAKE_DATA_ID( byte_1, byte_2, byte_3, byte_4 )

class CDataChunk
{
   public:

      DWORD      Identifier;
      CByteArray Data;

      CDataChunk()
      {
         WFCLTRACEINIT( TEXT( "CDataChunk::CDataChunk()" ) );
         Identifier = 0;
      };

      CDataChunk( const CDataChunk& source )
      {
         WFCLTRACEINIT( TEXT( "CDataChunk::CDataChunk( source )" ) );
         Copy( source );
      };

     ~CDataChunk()
      {
         WFCLTRACEINIT( TEXT( "CDataChunk::CDataChunk( source )" ) );
         Identifier = 0;
      };

      static void GetIdentifier( DWORD identifier, CString& string );

      inline void Copy( const CDataChunk& source )
      {
         Identifier = source.Identifier;
         Data.Copy( source.Data );
      };

      inline void Copy( DWORD identifier, const CByteArray& source )
      {
         Identifier = identifier;
         Data.Copy( source );
      };

      inline void Empty( void )
      {
         Identifier = 0;
         Data.RemoveAll();
      };

      inline CDataChunk& operator=( const CDataChunk& source )
      {
         Copy( source );
         return( *this );
      };

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // DATA_CHUNK_CLASS_HEADER
