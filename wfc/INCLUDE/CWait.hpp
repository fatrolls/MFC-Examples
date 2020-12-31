#if ! defined ( WAIT_CURSOR_CLASS_HEADER )

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
** Copyright, 1995, Samuel R. Blackburn
*/

#define WAIT_CURSOR_CLASS_HEADER

class CWaitCursor
{
   protected:

	   HCURSOR m_PreviousCursorHandle;

   public:

	   CWaitCursor( int cursor_number = 0 );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CWaitCursor();
};

#endif // WAIT_CURSOR_CLASS_HEADER
