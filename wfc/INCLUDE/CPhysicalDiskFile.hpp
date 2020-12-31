#if ! defined( PHYSICAL_DISK_FILE_CLASS_HEADER )

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
** $Workfile: CPhysicalDiskFile.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:52a $
*/

#define PHYSICAL_DISK_FILE_CLASS_HEADER

class CPhysicalDiskFile : public CFile
{
   private:

      // Don't allow canonical behavior...

      CPhysicalDiskFile( const CPhysicalDiskFile& ) {};
      CPhysicalDiskFile& operator=( const CPhysicalDiskFile& ) { return( *this ); };

   protected:

      DWORD m_BufferSize;
      DWORD m_BufferOffset;

      DISK_GEOMETRY m_DiskGeometry;

      BYTE * m_Buffer;

      virtual BOOL m_SetSectorSize( void );

   public:

      /*
      ** Constructors
      */

      CPhysicalDiskFile();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CPhysicalDiskFile();

      /*
      ** Methods
      */

      // CFile overrides
      virtual void  Close( void );
      virtual DWORD GetLength( void ) const;
      virtual UINT  Read( void * buffer, UINT count );
      virtual void  SetLength( DWORD );
      virtual void  Write( void * buffer, UINT count );

      // New Methods
      virtual DWORD GetMediaType( void ) const;
      virtual BOOL  GetSectorSize( DWORD& number_of_bytes_per_sector ) const;

#if ! defined( WFC_STL )
      virtual BOOL  Open( LPCTSTR filename, UINT open_flags, CFileException * error = NULL );
      virtual BOOL  Open( int physical_disk_number, UINT open_flags, CFileException * error = NULL );
#else // WFC_STL
      virtual BOOL  Open( LPCTSTR filename, UINT open_flags );
      virtual BOOL  Open( int physical_disk_number, UINT open_flags );
#endif // WFC_STL

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // PHYSICAL_DISK_FILE_CLASS_HEADER
