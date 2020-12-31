#if ! defined( CRITICAL_SECTION_CLASS_HEADER )

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
** $Workfile: CCriticalSection.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:40a $
*/

#define CRITICAL_SECTION_CLASS_HEADER

#if defined( WFC_STL )

class CCriticalSection
{
   protected:

      CRITICAL_SECTION m_CriticalSection;

   public:

      // Construction

      inline CCriticalSection()
      {
         ::InitializeCriticalSection( &m_CriticalSection );
      }

      inline ~CCriticalSection()
      {
         ::DeleteCriticalSection( &m_CriticalSection );
      }

      /*
      ** Methods
      */

      inline void Enter( void )
      {
         ::EnterCriticalSection( &m_CriticalSection );
      }

      inline void Exit( void )
      {
         ::LeaveCriticalSection( &m_CriticalSection );
      }

      inline Lock( void ) { Enter(); }
      inline Unlock( void ) { Exit(); }

#if( _WIN32_WINNT >= 0x0400 )

      inline BOOL TryToEnter( void )
      {
         return( ( ::TryEnterCriticalSection( &m_CriticalSection ) == FALSE ) ? FALSE : TRUE );
      }

#endif // _WIN32_WINNT
};

#endif // WFC_STL

#endif // CRITICAL_SECTION_CLASS_HEADER
