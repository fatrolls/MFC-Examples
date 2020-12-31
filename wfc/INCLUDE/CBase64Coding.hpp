#if ! defined( BASE_64_CODING_CLASS_HEADER )

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
** $Workfile: CBase64Coding.hpp $
** $Revision: 3 $
** $Modtime: 1/04/00 4:39a $
*/

#define BASE_64_CODING_CLASS_HEADER

class CBase64Coding
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CBase64Coding( const CBase64Coding& ) {};
      CBase64Coding& operator=( const CBase64Coding& ) { return( *this ); };

   protected:

      BYTE m_DecoderTable[ 256 ];

      virtual void m_InitializeDecoderTable( void );

   public:

      // Construction

      CBase64Coding();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CBase64Coding();

      virtual BOOL Decode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Decode( const CString&    source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CString&    destination );
};

#endif // BASE_64_CODING_CLASS_HEADER
