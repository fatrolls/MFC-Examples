#if ! defined( DRAG_QUERY_CLASS_HEADER )

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
** $Workfile: CDragQuery.hpp $
** $Revision: 2 $
** $Modtime: 1/04/00 4:43a $
*/

#define DRAG_QUERY_CLASS_HEADER

class CDragQuery
{
   protected:

      HDROP m_Handle;

   public:

      CDragQuery( HDROP handle = (HDROP) NULL );
      CDragQuery( const CDragQuery& source );
      virtual ~CDragQuery();

      virtual void  Copy( const CDragQuery& source );
      virtual void  Finish( void );
      virtual void  GetFilenames( CStringArray& filenames ) const;
      virtual HDROP GetHandle( void ) const;
      virtual UINT  GetNumberOfFiles( void ) const;
      virtual BOOL  GetPoint( POINT& point ) const;
      virtual void  SetHandle( HDROP handle );

      virtual CDragQuery& operator=( const CDragQuery& source );
};

#endif // DRAG_QUERY_CLASS_HEADER
