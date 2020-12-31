#if ! defined ( GARBAGE_COLLECTOR_CLASS_HEADER )

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
** $Workfile: CGarbageCollector.hpp $
** $Revision: 6 $
** $Modtime: 1/04/00 4:48a $
*/

#define GARBAGE_COLLECTOR_CLASS_HEADER

class CGarbageCollector
{
   protected:

      // Don't allow these sorts of things

      CGarbageCollector( const CGarbageCollector& ) {};
      virtual CGarbageCollector& operator = ( const CGarbageCollector& ){ return( *this ); };

      volatile long m_ReferenceCount;

      BOOL m_SelfDestruct;

   public:

      CGarbageCollector();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CGarbageCollector();

      virtual void AddReference( void );
      virtual long GetReferenceCount( void ) const;
      virtual BOOL GetSelfDestruct( void ) const;
      virtual void Release( BOOL * deleted = NULL );
      virtual void SetSelfDestruct( BOOL self_destruct = TRUE );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};   

#endif // GARBAGE_COLLECTOR_CLASS_HEADER
