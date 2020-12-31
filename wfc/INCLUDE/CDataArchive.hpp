#if ! defined( DATA_ARCHIVE_CLASS_HEADER )

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
** $Workfile: CDataArchive.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:40a $
*/

#define DATA_ARCHIVE_CLASS_HEADER

class CDataArchive
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CDataArchive( const CDataArchive& ) {};
      CDataArchive& operator=( const CDataArchive& ) { return( *this ); };

   protected:

      DWORD m_Position;

      BOOL m_AmIWriting;

      CDataChunk * m_DataChunk_p;

   public:

      CDataArchive();
      virtual ~CDataArchive();

      virtual BOOL IsLoading( void ) const;
      virtual BOOL IsStoring( void ) const;

      virtual void Read( char&    value );
      virtual void Read( BYTE&    value );
      virtual void Read( WORD&    value );
      virtual void Read( LONG&    value );
      virtual void Read( DWORD&   value );
      virtual void Read( float&   value );
      virtual void Read( double&  value );
      virtual void Read( CString& value );
      virtual void Read( CByteArray&   array );
      virtual void Read( CStringArray& array );
      virtual void Read( CDWordArray&  array );
      virtual void Read( CWordArray&   array );

      virtual void ReadFrom( CDataChunk * chunk_p );

      virtual void Write( char    value );
      virtual void Write( BYTE    value );
      virtual void Write( WORD    value );
      virtual void Write( LONG    value );
      virtual void Write( DWORD   value );
      virtual void Write( float   value );
      virtual void Write( double  value );
      virtual void Write( const CString& value );
      virtual void Write( const CByteArray&   array );
      virtual void Write( const CStringArray& array );
      virtual void Write( const CDWordArray&  array );
      virtual void Write( const CWordArray&   array );

      virtual void WriteTo( CDataChunk * chunk_p );
};

#endif // DATA_ARCHIVE_CLASS_HEADER
