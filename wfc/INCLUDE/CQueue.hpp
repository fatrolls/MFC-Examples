#if ! defined ( QUEUE_CLASS_HEADER )

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
** $Workfile: CQueue.hpp $
** $Revision: 17 $
** $Modtime: 5/16/00 6:39p $
*/

#define QUEUE_CLASS_HEADER

typedef BOOL (WINAPI *TRY_ENTER_CRITICAL_SECTION_FUNCTION)( LPCRITICAL_SECTION );

class CQueue
{
   private:

      // Don't allow these sorts of things

      inline CQueue( const CQueue& ) {};
      inline CQueue& operator = ( const CQueue& ){ return( *this ); };

   protected:

      // What we want to protect

      CRITICAL_SECTION m_AddCriticalSection;
      CRITICAL_SECTION m_GetCriticalSection;

      void * * m_Items;

      DWORD m_AddIndex;
      DWORD m_GetIndex;
      DWORD m_Size;

      HANDLE m_Heap;

      TRY_ENTER_CRITICAL_SECTION_FUNCTION m_TryEnterCriticalSection;

      inline void m_GrowBy( DWORD number_of_new_items );

   public:

      inline  CQueue( DWORD initial_size = 1024 );
      inline ~CQueue();

      inline BOOL  Add( DWORD new_item ) { return( Add( (void *) new_item ) ); };
      inline BOOL  Add( void * new_item );
      inline void  Empty( void ) { m_AddIndex = 0; m_GetIndex = 0; };
      inline BOOL  Get( DWORD& item );
      inline BOOL  Get( void * & item );
      inline DWORD GetLength( void ) const;
      inline DWORD GetMaximumLength( void ) const { return( m_Size ); };

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};   

inline CQueue::CQueue( DWORD initial_size )
{
   // TryEnterCriticalSection is snapped to NTDLL.RtlTryEnterCriticalSection but we
   // will stick to the published specification. We go to this trouble so programs
   // that were compiled for NT4 will work with NT3

   m_TryEnterCriticalSection = (TRY_ENTER_CRITICAL_SECTION_FUNCTION) GetProcAddress( GetModuleHandleW( L"Kernel32" ), "TryEnterCriticalSection" );

   m_AddIndex = 0;
   m_GetIndex = 0;
   m_Items    = NULL;

   if ( initial_size == 0 )
   {
      initial_size = 1;
   }

   /*
   ** 1999-11-05
   ** We create our own heap because all of the pointers used are allocated
   ** and freed be us. We don't have to worry about a non-serialized thread
   ** accessing something we allocated. Because of this, we can perform our
   ** memory allocations in a heap dedicated to queueing. This means when we
   ** have to allocate more memory, we don't have to wait for all other threads
   ** to pause while we allocate from the shared heap (like the C Runtime heap)
   */

   m_Heap = ::HeapCreate( HEAP_NO_SERIALIZE,
                          ( ( ( 2 * initial_size * sizeof( void * ) ) < 65536 ) ? 65536 : (2 * initial_size * sizeof( void * ) ) ),
                          0 );

   m_Items = (void **) ::HeapAlloc( m_Heap, HEAP_NO_SERIALIZE, initial_size * sizeof( void * ) );

   m_Size = ( m_Items == NULL ) ? 0 : initial_size;

   ::InitializeCriticalSection( &m_AddCriticalSection );
   ::InitializeCriticalSection( &m_GetCriticalSection );
}

inline CQueue::~CQueue()
{
   m_AddIndex = 0;
   m_GetIndex = 0;
   m_Size     = 0;

   if ( m_Items != NULL )
   {
      ::HeapFree( m_Heap, HEAP_NO_SERIALIZE, m_Items );
      m_Items = NULL;
   }

   ::HeapDestroy( m_Heap );
   m_Heap = NULL;

   ::DeleteCriticalSection( &m_AddCriticalSection );
   ::DeleteCriticalSection( &m_GetCriticalSection );
}

inline BOOL CQueue::Add( void * item )
{
   // Block other threads from entering Add();
   ::EnterCriticalSection( &m_AddCriticalSection );

   // Add the item

   m_Items[ m_AddIndex ] = item;

   // 1999-12-08
   // Many many thanks go to Lou Franco (lfranco@spheresoft.com)
   // for finding an bug here. It rare but recreatable situations,
   // m_AddIndex could be in an invalid state.

   // Make sure m_AddIndex is never invalid

   DWORD new_add_index = ( ( m_AddIndex + 1 ) >= m_Size ) ? 0 : m_AddIndex + 1;

   if ( new_add_index == m_GetIndex )
   {
      // The queue is full. We need to grow.
      // Stop anyone from getting from the queue
  		::EnterCriticalSection( &m_GetCriticalSection );

      m_AddIndex = new_add_index;

      // One last double-check.

      if ( m_AddIndex == m_GetIndex )
      {
         m_GrowBy( m_Size );
      }

		::LeaveCriticalSection( &m_GetCriticalSection );
   }
   else
   {
      m_AddIndex = new_add_index;
   }

#if defined( WFC_CQUEUE_STRESS_TEST )

   if ( m_Size > ( 1024 * 1024 * 2 ) )
   {
      while( m_Size > 1024 )
      {
         Sleep( 1000 );
      }
   }

#endif // WFC_CQUEUE_STRESS_TEST

   // Let other threads call Add() now.
   ::LeaveCriticalSection( &m_AddCriticalSection );

   return( TRUE );
}

inline BOOL CQueue::Get( DWORD& item )
{
   item = 0;

   void * pointer = NULL;

   if ( Get( pointer ) != FALSE )
   {
      item = reinterpret_cast< DWORD >( pointer );
      return( TRUE );
   }

   return( FALSE );
}

inline BOOL CQueue::Get( void * & item )
{
   // Prevent other threads from entering Get()
   ::EnterCriticalSection( &m_GetCriticalSection );

   if ( m_GetIndex == m_AddIndex )
   {
      // TryEnterCriticalSection() is available in NT 4.0 and up

      // Let's check to see if our queue has grown too big
      // If it has, then shrink it

      if ( m_Size > 1024 )
      {
         // Yup, we're too big for our britches

         if ( m_TryEnterCriticalSection != NULL )
         {
            if ( ::TryEnterCriticalSection( &m_AddCriticalSection ) != 0 )
            {
               // Now, no one can add to the queue

               if ( m_GetIndex == m_AddIndex )
               {
                  // See if we can just shrink it...

                  void * return_value = (void *) ::HeapReAlloc( m_Heap, HEAP_NO_SERIALIZE, m_Items, 1024 * sizeof( void *) );

                  if ( return_value != NULL )
                  {
                     m_Items = (void **) return_value;
                  }
                  else
                  {
                     // Looks like we'll have to do it the hard way
                     ::HeapFree( m_Heap, HEAP_NO_SERIALIZE, m_Items );
                     m_Items = (void **) ::HeapAlloc( m_Heap, HEAP_NO_SERIALIZE, 1024 * sizeof( void * ) );
                  }

                  m_Size     = ( m_Items == NULL ) ? 0 : 1024;
                  m_AddIndex = 0;
                  m_GetIndex = 0;
               }
               else
               {
                  // m_GetIndex != m_AddIndex, this means that someone added
                  // to the queue between the time we checked m_Size for being
                  // too big and the time we entered the add critical section.
                  // If this happened then we are too busy to shrink
               }

               // Let people add to the queue once again

               ::LeaveCriticalSection( &m_AddCriticalSection );
            }
         }
         else
         {
            // The version of NT we are running on doesn't have TryEnterCriticalSection

            // 1999-12-08
            // Thanks go to Lou Franco for adding code to shrink the queue
            // without the performance-friendly TryEnterCriticalSection

            ::LeaveCriticalSection( &m_GetCriticalSection );
            ::EnterCriticalSection( &m_AddCriticalSection );
            ::EnterCriticalSection( &m_GetCriticalSection );

            if ( m_GetIndex == m_AddIndex )
            {
               void * return_value = (void *) ::HeapReAlloc( m_Heap, HEAP_NO_SERIALIZE, m_Items, 1024 * sizeof( void *) );

               if ( return_value != NULL )
               {
                  m_Items = (void **) return_value;
               }
               else
               {
                  // Looks like we'll have to do it the hard way
                  ::HeapFree( m_Heap, HEAP_NO_SERIALIZE, m_Items );
                  m_Items = (void **) ::HeapAlloc( m_Heap, HEAP_NO_SERIALIZE, 1024 * sizeof( void * ) );
               }

               m_Size     = ( m_Items == NULL ) ? 0 : 1024;
               m_AddIndex = 0;
               m_GetIndex = 0;

               ::LeaveCriticalSection( &m_GetCriticalSection );
               ::LeaveCriticalSection( &m_AddCriticalSection );

               return( FALSE );
            }

            ::LeaveCriticalSection( &m_GetCriticalSection );
            ::LeaveCriticalSection( &m_AddCriticalSection );

            return( FALSE );
         }
      }

      // Let other threads call Get() now, we are empty
      ::LeaveCriticalSection( &m_GetCriticalSection );
      return( FALSE );
   }

   item = m_Items[ m_GetIndex ];

   // Make sure m_GetIndex is never invalid

   m_GetIndex = ( ( m_GetIndex + 1 ) >= m_Size ) ? 0 : m_GetIndex + 1;

   // Let other threads call Get() now
   ::LeaveCriticalSection( &m_GetCriticalSection );

   return( TRUE );
}

inline DWORD CQueue::GetLength( void ) const
{
   // This is a very expensive process!
   // No one can call Add() or Get() while we're computing this

   DWORD number_of_items_in_the_queue = 0;

   ::EnterCriticalSection( const_cast< CRITICAL_SECTION * >( &m_AddCriticalSection ) );
   ::EnterCriticalSection( const_cast< CRITICAL_SECTION * >( &m_GetCriticalSection ) );

   number_of_items_in_the_queue = ( m_AddIndex >= m_GetIndex ) ?
                                  ( m_AddIndex  - m_GetIndex ) :
                                  ( ( m_AddIndex + m_Size ) - m_GetIndex );

   ::LeaveCriticalSection( const_cast< CRITICAL_SECTION * >( &m_GetCriticalSection ) );
   ::LeaveCriticalSection( const_cast< CRITICAL_SECTION * >( &m_AddCriticalSection ) );

   return( number_of_items_in_the_queue );
}

inline void CQueue::m_GrowBy( DWORD number_of_new_items )
{
   // Prevent other threads from calling Get().
   // We don't need to enter the AddCriticalSection because
   // m_GrowBy() is only called from Add();

   void * * new_array       = NULL;
   void * * pointer_to_free = NULL;

   DWORD new_size = m_Size + number_of_new_items;

   // Prevent other threads from getting
   ::EnterCriticalSection( &m_GetCriticalSection );

   // 2000-05-16
   // Thanks go to Royce Mitchell III (royce3@aim-controls.com) for finding
   // a HUGE bug here. I was using HeapReAlloc as a short cut but my logic
   // was flawed. In certain circumstances, queue items were being dropped.

   new_array = (void **) ::HeapAlloc( m_Heap, HEAP_NO_SERIALIZE, new_size * sizeof( void * ) );

   // Now copy all of the old items from the old queue to the new one.

   // Get the entries from the get-index to the end of the array
   ::CopyMemory( new_array, &m_Items[ m_GetIndex ], ( m_Size - m_GetIndex ) * sizeof( void * ) );

   // Get the entries from the beginning of the array to the add-index
   ::CopyMemory( &new_array[ m_Size - m_GetIndex ], m_Items, m_AddIndex * sizeof( void * ) );

   m_AddIndex      = m_Size;
   m_GetIndex      = 0;
   m_Size          = new_size;
   pointer_to_free = m_Items;
   m_Items         = new_array;

   ::LeaveCriticalSection( &m_GetCriticalSection );
   ::HeapFree( m_Heap, HEAP_NO_SERIALIZE, pointer_to_free );
}

#endif // QUEUE_CLASS_HEADER
