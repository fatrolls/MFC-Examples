#if ! defined( FILE_DIRECTORY_CLASS_HEADER )

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
** $Workfile: CFileDirectory.hpp $
** $Revision: 2 $
** $Modtime: 1/04/00 4:46a $
*/

#define FILE_DIRECTORY_CLASS_HEADER

typedef BOOL (*FILE_ACTION_FUNCTION)( void * parameter, const CString& filename );

class CFileDirectory
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CFileDirectory( const CFileDirectory& ) {};
      CFileDirectory& operator=( const CFileDirectory& ) { return( *this ); };

   protected:

      CString m_Name;

   public:

      // Construction

      CFileDirectory();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CFileDirectory();

      /*
      ** Methods
      */

      virtual void Close( void );
      virtual BOOL Open( const CString& directory_name );
      virtual BOOL Read( CStringArray& filenames );
      virtual BOOL Read( FILE_ACTION_FUNCTION action_to_take, void * action_parameter );
      virtual BOOL ReadRecursively( CStringArray& filenames );
      virtual BOOL ReadRecursively( FILE_ACTION_FUNCTION action_to_take, void * action_parameter );

      /*
      ** Operators
      */
};

#endif // FILE_DIRECTORY_CLASS_HEADER
