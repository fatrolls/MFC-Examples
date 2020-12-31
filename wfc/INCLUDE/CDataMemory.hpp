#if ! defined( DATA_MEMORY_CLASS_HEADER )

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
** $Workfile: CDataMemory.hpp $
** $Revision: 5 $
** $Modtime: 1/04/00 4:40a $
*/

#define DATA_MEMORY_CLASS_HEADER

class CDataMemory : public CDataFile
{
   protected:

      long m_Position;

      CByteArray m_Data;

   public:

      CDataMemory();
      CDataMemory( const CDataMemory& source );
      CDataMemory( const BYTE * buffer_p, DWORD number_of_bytes );
      CDataMemory( const CByteArray& source );
      virtual ~CDataMemory();

      virtual void  Append( const CByteArray&  source );
      virtual void  Append( const CDataMemory& source );
      virtual void  AppendTo( CByteArray& data );
      virtual void  Close( void );
      virtual void  Copy( const BYTE * buffer, DWORD number_of_bytes );
      virtual void  Copy( const CByteArray& source );
      virtual void  Copy( const CDataMemory& source );
      virtual void  CopyTo( CByteArray& data );
      virtual void  Empty( void );
      virtual void  Flush( void );
      virtual const BYTE * GetData( void ) const;
      virtual DWORD GetLength( void ) const;
      virtual DWORD GetPosition( void ) const;
      virtual BOOL  Open( LPCTSTR filename, UINT mode );
      virtual UINT  Read( void * buffer, UINT number_of_bytes_to_read );
      virtual long  Seek( long offset, UINT from );
      virtual void  Write( const void * buffer, UINT number_of_bytes_to_write );

      virtual const CDataMemory& operator=(  const CDataMemory& source );
      virtual const CDataMemory& operator=(  const CByteArray&  source );
      virtual const CDataMemory& operator+=( const CDataMemory& source );
      virtual const CDataMemory& operator+=( const CByteArray&  source );
};

#endif // DATA_FILE_CLASS_HEADER
