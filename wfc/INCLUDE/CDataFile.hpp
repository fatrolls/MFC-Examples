#if ! defined( DATA_FILE_CLASS_HEADER )

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
** $Workfile: CDataFile.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:40a $
*/

#define DATA_FILE_CLASS_HEADER

class CDataFile : public CFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CDataFile( const CDataFile& ) {};
      CDataFile& operator=( const CDataFile& ) { return( *this ); };

   public:

      CDataFile();
      virtual ~CDataFile();

      virtual BOOL AddData( DWORD identifier, const CByteArray& data );
      virtual BOOL AddData( DWORD identifier, const BYTE * data, DWORD number_of_bytes );
      virtual BOOL AddData( const CDataChunk& data );
      virtual BOOL GetData( DWORD& identifier, CByteArray& data );
      virtual BOOL GetData( CDataChunk& data );
};

#endif // DATA_FILE_CLASS_HEADER
