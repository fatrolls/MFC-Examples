#if ! defined( DUMMY_FILE_CLASS_HEADER )

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
** $Workfile: dumyfile.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:00a $
*/

#define DUMMY_FILE_CLASS_HEADER

class CDummyFile : public CFile
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CDummyFile )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CDummyFile( const CDummyFile& ) {};
      CDummyFile& operator=( const CDummyFile& ) { return( *this ); };

   protected:

      DWORD m_ErrorCode;

      HANDLE m_TemplateHandle;

#if defined( WFC_STL )
      HANDLE m_FileHandle;
#endif // WFC_STL

      virtual DWORD m_CreateDesiredAccess( void ) const;
      virtual DWORD m_CreateFlagsAndAttributes( void ) const;
      virtual DWORD m_CreateShareMode( void ) const;
      virtual LPSECURITY_ATTRIBUTES m_CreateSecurityAttributes( void ) const;
      virtual DWORD m_CreateCreationDistribution( void ) const;
      virtual HANDLE m_CreateTemplateHandle( void ) const;

   public:

      CDummyFile();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CDummyFile();

      /*
      ** Interception functions (would blow up if we let CFile get them)
      */

      virtual void  Abort( void );
      virtual void  Close( void );
      virtual void  Flush( void );
      virtual DWORD GetErrorCode( void ) const;
      virtual DWORD GetLength( void ) const;
      virtual DWORD GetPosition( void ) const;

#if ! defined( WFC_STL )
      virtual BOOL  GetStatus( CFileStatus& status );
      virtual BOOL  GetStatus( LPCTSTR name, CFileStatus& status );
#endif // WFC_STL

      virtual void  LockRange( DWORD position, DWORD count );
      virtual void  Remove( LPCTSTR name );
      virtual void  Rename( LPCTSTR OldName, LPCTSTR NewName );
      virtual LONG  Seek( LONG offset, UINT from );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual void  SetLength( DWORD length );

#if ! defined( WFC_STL )
      virtual void  SetStatus( LPCTSTR name, const CFileStatus& status );
#endif // WFC_STL

      virtual void  UnlockRange( DWORD position, DWORD count );

      /*
      ** A couple of utility functions to make life easier
      */

      virtual void Write( const CString& string_to_write  );
      virtual void Write( const CByteArray& data_to_write );

      // Abstraction Additions

      inline HANDLE GetHandle( void ) const { return( (HANDLE) m_hFile ); }
      inline void   SetHandle( HANDLE file_handle ) { m_hFile = (UINT) file_handle; }

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // DUMMY_FILE_CLASS_HEADER
