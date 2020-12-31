#if ! defined( MEMORY_FILE_CLASS_HEADER )

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
** $Workfile: CMemoryFile.hpp $
** $Revision: 5 $
** $Modtime: 1/04/00 4:51a $
*/

#define MEMORY_FILE_CLASS_HEADER

class CMemoryFile
{
   private:

      // Don't allow canonical behavior

      CMemoryFile( const CMemoryFile& ) {};
      const CMemoryFile& operator=( const CMemoryFile& ) { return( *this ); };
      
   protected:

      SECURITY_ATTRIBUTES * m_SecurityAttributes_p;

      SECURITY_DESCRIPTOR * m_SecurityDescriptor_p;

      HANDLE m_MapHandle;

      void * m_MappedPointer;
      void * m_Pointer;

      CString m_Filename;

      DWORD m_AllocationGranularity;
      DWORD m_Length;
      DWORD m_MappedLength;

      ULONGLONG m_FileLength;

      virtual void m_Initialize( void );
      virtual void m_Uninitialize( void );

   public:

      // Construction

      CMemoryFile();

      virtual ~CMemoryFile();

      // Properties

      DWORD Size;

      // Methods

      virtual void      Close( void );
      virtual BOOL      Flush( void );
      inline  ULONGLONG GetFileLength( void ) const { return( m_FileLength ); }
      virtual void      GetFilename( CString& filename ) const;
      inline  DWORD     GetLength( void ) const { return( m_Length ); };
      inline  void *    GetPointer( void ) const { return( m_Pointer ); };
      virtual BOOL      Open( LPCTSTR filename,
                              UINT open_flags              = CFile::modeRead,
                              ULONGLONG beginning_at       = 0,
                              DWORD number_of_bytes_to_map = 0,
                              void * desired_address       = NULL );

      // Operators

      inline operator void * ( void ) const { return( m_Pointer ); };
};

#endif // MEMORY_FILE_CLASS_HEADER
