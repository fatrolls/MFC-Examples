#define WFC_CQUEUE_STRESS_TEST
#include "test.h"
#pragma hdrstop

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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: CQueue_stress_test.cpp $
** $Revision: 2 $
** $Modtime: 5/16/00 7:01p $
*/

// If you don't have more than one CPU, don't bother
// to run this test. You will never get into a
// deadlock.

typedef struct _queue_workspace
{
   CQueue *       queue_p;
   ULARGE_INTEGER number_of_operations;
   bool           exit_thread;
}
QUEUE_WORKSPACE;

void queue_add_thread( void * p )
{
   QUEUE_WORKSPACE * workspace_p = (QUEUE_WORKSPACE *) p;

   if ( workspace_p == NULL )
   {
      return;
   }

   workspace_p->number_of_operations.QuadPart = 0;

   CQueue * queue_p = workspace_p->queue_p;

   void * item = (void *) 0xFFFFFFFF;

   while( workspace_p->exit_thread == false )
   {
      if ( queue_p->Add( item ) == TRUE )
      {
         workspace_p->number_of_operations.QuadPart++;
      }
   }
}

void queue_get_thread( void * p )
{
   QUEUE_WORKSPACE * workspace_p = (QUEUE_WORKSPACE *) p;

   if ( workspace_p == NULL )
   {
      return;
   }

   workspace_p->number_of_operations.QuadPart = 0;

   CQueue * queue_p = workspace_p->queue_p;

   void * item = NULL;

   while( workspace_p->exit_thread == false )
   {
      if ( queue_p->Get( item ) == TRUE )
      {
         workspace_p->number_of_operations.QuadPart++;
      }
   }
}

void CQueue_stress_test( void )
{
   WFCTRACEINIT( TEXT( "CQueue_stress_test()" ) );

   QUEUE_WORKSPACE get_workspace;
   QUEUE_WORKSPACE add_workspace;

   CQueue queue;

   get_workspace.queue_p = &queue;
   add_workspace.queue_p = &queue;

   get_workspace.exit_thread = false;
   add_workspace.exit_thread = false;

   DWORD start_time = time( NULL );

   SYSTEM_INFO system_information;

   ZeroMemory( &system_information, sizeof( system_information ) );

   GetSystemInfo( &system_information );

   HANDLE get_thread_handle = (HANDLE) _beginthread( queue_get_thread, 0, &get_workspace );
   HANDLE add_thread_handle = (HANDLE) _beginthread( queue_add_thread, 0, &add_workspace );

   // If we have more than one CPU, set the thread affinity masks for
   // the threads so they will stick to different CPUs and therefore
   // execute faster.

   if ( system_information.dwNumberOfProcessors > 1 )
   {
      SetThreadIdealProcessor( get_thread_handle, 0 );
      SetThreadIdealProcessor( add_thread_handle, 1 );
   }

   // Now run until the user presses the Enter key on the keyboard
   getchar();

   add_workspace.exit_thread = true;
   get_workspace.exit_thread = true;

   DWORD end_time = time( NULL );
   DWORD number_of_seconds_we_ran = end_time - start_time;

   // Now print the results

   _tprintf( TEXT( "We ran for %lu seconds.\n" ), number_of_seconds_we_ran );
   _tprintf( TEXT( "Added %I64u items (%lu operations per second)\n" ),
             add_workspace.number_of_operations.QuadPart,
             (DWORD) ( add_workspace.number_of_operations.QuadPart / number_of_seconds_we_ran ) );
   _tprintf( TEXT( "Got %I64u items (%lu operations per second)\n" ),
             get_workspace.number_of_operations.QuadPart,
             (DWORD) ( get_workspace.number_of_operations.QuadPart / number_of_seconds_we_ran ) );
   _tprintf( TEXT( "Left %lu items on the queue.\n" ), queue.GetLength() );
   _tprintf( TEXT( "Queue grew to %lu\n" ), queue.GetMaximumLength() );
}
