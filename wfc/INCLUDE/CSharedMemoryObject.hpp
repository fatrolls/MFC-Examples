#if ! defined( SHARED_MEMORY_OBJECT_CLASS_HEADER )

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
** $Workfile: CSharedMemoryObject.hpp $
** $Revision: 3 $
** $Modtime: 1/04/00 4:54a $
*/

#define SHARED_MEMORY_OBJECT_CLASS_HEADER

class CSharedMemoryObject
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CSharedMemoryObject( const CSharedMemoryObject& ) {};
      CSharedMemoryObject& operator=( const CSharedMemoryObject& ) { return( *this ); };

   protected:

      HANDLE m_MapHandle;

      DWORD m_Size;

      void * m_Pointer;

      CString m_Name;

   public:

      CSharedMemoryObject();
     ~CSharedMemoryObject();

      void          Close( void );
      BOOL          Create( const CString& object_name, DWORD size_in_bytes );
      inline HANDLE GetHandle( void ) const        { return( m_MapHandle ); };
      inline void   GetName( CString& name ) const { name = m_Name; };
      inline void * GetPointer( void ) const       { return( m_Pointer ); };
      inline DWORD  GetSize( void ) const          { return( m_Size ); }
};

#endif // SHARED_MEMORY_OBJECT_CLASS_HEADER
