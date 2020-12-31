#if ! defined( OVERLAPPED_CLASS_HEADER )

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
** $Workfile: ovrlpd.hpp $
** $Revision: 9 $
** $Modtime: 1/04/00 5:00a $
*/

#define OVERLAPPED_CLASS_HEADER

class COverlapped : public _OVERLAPPED
{
   protected:

      BOOL m_AutomaticallyDelete;

   public:

      // Construction

      COverlapped();
      COverlapped( const COverlapped& source );
      COverlapped( const OVERLAPPED&  source );
      COverlapped( const OVERLAPPED * source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~COverlapped();

      /*
      ** Methods
      */

      virtual void Copy( const COverlapped& source );
      virtual void Copy( const OVERLAPPED&  source );
      virtual void Copy( const OVERLAPPED * source );
      virtual void Empty( void );
      virtual void SetEvent( HANDLE event_handle );
      virtual void SetAutomaticallyDelete( BOOL automatically_delete = TRUE );

      /*
      ** Operators
      */

      COverlapped& operator=( const COverlapped& source );
      COverlapped& operator=( const OVERLAPPED&  source );
};

#endif // OVERLAPPED_CLASS_HEADER
