#if ! defined( FILE_TRANSFER_CLASS_HEADER )

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
** $Workfile: CFileTransferProtocol.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 4:46a $
*/

#define FILE_TRANSFER_CLASS_HEADER

#if ! defined( WFC_STL )

class CFileTransferProtocol
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CFileTransferProtocol( const CFileTransferProtocol& ) {};
      CFileTransferProtocol& operator=( const CFileTransferProtocol& ) { return( *this ); };

   protected:

      CString m_UserName;
      CString m_Password;

   public:

      CFileTransferProtocol( LPCTSTR user_name = NULL, LPCTSTR password = NULL );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CFileTransferProtocol();

      virtual void GetDirectory( const CUniformResourceLocator& source, CStringArray& directory_contents, LPCTSTR filter = NULL );
      virtual void GetFile( const CUniformResourceLocator& source, CByteArray& file_contents );
      virtual void GetPassword( CString& password ) const;
      virtual void GetUserName( CString& account  ) const;
      virtual BOOL PutFile( const CUniformResourceLocator& url, const CByteArray& file_contents );
      virtual void SetPassword( const CString& password );
      virtual void SetUserName( const CString& account  );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // WFC_STL

#endif // FILE_TRANSFER_CLASS_HEADER
