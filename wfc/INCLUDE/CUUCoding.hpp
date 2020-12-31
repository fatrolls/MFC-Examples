#if ! defined( UU_CODING_CLASS_HEADER )

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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: CUUCoding.hpp $
** $Revision: 1 $
** $Modtime: 6/21/98 6:00a $
*/

#define UU_CODING_CLASS_HEADER

class CUUCoding
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CUUCoding( const CUUCoding& ) {};
      CUUCoding& operator=( const CUUCoding& ) { return( *this ); };

   public:

      // Construction

      CUUCoding();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CUUCoding();

      virtual BOOL Decode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Decode( const CString&    source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CString&    destination );
};

#endif // UU_CODING_CLASS_HEADER
