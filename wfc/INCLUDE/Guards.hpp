#if ! defined( GUARDS_CLASS_HEADER )

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
** $Workfile: Guards.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 5:00a $
*/

#define GUARDS_CLASS_HEADER

class CCriticalSectionGuard
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CCriticalSectionGuard( const CCriticalSectionGuard& ) {};
      CCriticalSectionGuard& operator=( const CCriticalSectionGuard& ) { return( *this ); };

   protected:

      CCriticalSection * m_CriticalSection;

   public:

      inline CCriticalSectionGuard( CCriticalSection * section )
      {
         m_CriticalSection = section;
         m_CriticalSection->Lock();
      };

      inline CCriticalSectionGuard( CCriticalSection& section )
      {
         m_CriticalSection = &section;
         m_CriticalSection->Lock();
      };

      inline ~CCriticalSectionGuard()
      {
         m_CriticalSection->Unlock();
      };
};

#endif // GUARDS_CLASS_HEADER
