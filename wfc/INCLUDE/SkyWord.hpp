#if ! defined( SKYWORD_CLASS_HEADER )

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
** $Workfile: SkyWord.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 5:00a $
*/

#define SKYWORD_CLASS_HEADER

class CSkyWord : public CPager
{
   protected:

      virtual BOOL m_Send( void );

   public:

      CSkyWord();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CSkyWord();
};

#endif // SKYWORD_CLASS_HEADER
