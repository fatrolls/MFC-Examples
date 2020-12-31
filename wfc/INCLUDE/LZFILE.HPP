#if ! defined( DATA_DECOMPRESSION_CLASS_HEADER )

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
** $Workfile: lzfile.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:00a $
*/

#define DATA_DECOMPRESSION_CLASS_HEADER

class CLZFile : public CDummyFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CLZFile( const CLZFile& ) {};
      CLZFile& operator=( const CLZFile& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      INT m_LZFileHandle;

      COFStruct m_OpenFileStructure;
      
   public:

      CLZFile();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CLZFile();

      static void __stdcall TranslateErrorCode( int error_code, CString& error_message );

      /*
      ** The Win32 API
      */

      virtual void Close( void );
      virtual BOOL Copy( const CLZFile& source );
      virtual BOOL Copy( const CLZFile *source );
      virtual BOOL GetExpandedName( LPTSTR name_of_compressed_file, CString& original_file_name );
#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR channel_name, UINT style = OF_READ, CFileException* pError = NULL );
#else // WFC_STL
      virtual BOOL Open( LPCTSTR channel_name, UINT style = OF_READ );
#endif // WFC_STL
      virtual UINT Read( void* buffer, UINT size_of_buffer );
      virtual LONG Seek( LONG offset, UINT from );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // DATA_DECOMPRESSION_CLASS_HEADER
