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
** $Workfile: test_CQueue.cpp $
** $Revision: 4 $
** $Modtime: 5/16/00 6:27p $
*/

BOOL test_CQueue( CString& class_name, int& test_number_that_failed )
{
   WFCTRACEINIT( TEXT( "test_CQueue()" ) );

   class_name = TEXT( "CQueue" );

   CQueue queue( 1 ); // A really small queue

   if ( queue.Add( 1 ) == FALSE )
   {
      test_number_that_failed = 1;
      return( FALSE );
   }

   if ( queue.Add( 2 ) == FALSE )
   {
      test_number_that_failed = 2;
      return( FALSE );
   }

   if ( queue.Add( 3 ) == FALSE )
   {
      test_number_that_failed = 3;
      return( FALSE );
   }

   if ( queue.Add( 4 ) == FALSE )
   {
      test_number_that_failed = 4;
      return( FALSE );
   }

   if ( queue.Add( 5 ) == FALSE )
   {
      test_number_that_failed = 5;
      return( FALSE );
   }

   DWORD item = 0;

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 6;
      return( FALSE );
   }

   if ( item != 1 )
   {
      test_number_that_failed = 7;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 8;
      return( FALSE );
   }

   if ( item != 2 )
   {
      test_number_that_failed = 9;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 10;
      return( FALSE );
   }

   if ( item != 3 )
   {
      test_number_that_failed = 11;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 12;
      return( FALSE );
   }

   if ( item != 4 )
   {
      test_number_that_failed = 13;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 14;
      return( FALSE );
   }

   if ( item != 5 )
   {
      test_number_that_failed = 15;
      return( FALSE );
   }

   // Queue is now empty, it should not Get() anything

   if ( queue.Get( item ) == TRUE )
   {
      test_number_that_failed = 16;
      return( FALSE );
   }

   if ( queue.GetLength() != 0 )
   {
      test_number_that_failed = 17;
      return( FALSE );
   }

   if ( queue.Add( 6 ) == FALSE )
   {
      test_number_that_failed = 18;
      return( FALSE );
   }

   if ( queue.Add( 7 ) == FALSE )
   {
      test_number_that_failed = 19;
      return( FALSE );
   }

   if ( queue.Add( 8 ) == FALSE )
   {
      test_number_that_failed = 20;
      return( FALSE );
   }

   if ( queue.GetLength() != 3 )
   {
      test_number_that_failed = 21;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 22;
      return( FALSE );
   }

   if ( item != 6 )
   {
      test_number_that_failed = 23;
      return( FALSE );
   }

   if ( queue.Add( 9 ) == FALSE )
   {
      test_number_that_failed = 24;
      return( FALSE );
   }

   if ( queue.Add( 10 ) == FALSE )
   {
      test_number_that_failed = 25;
      return( FALSE );
   }

   if ( queue.GetLength() != 4 )
   {
      test_number_that_failed = 26;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 27;
      return( FALSE );
   }

   if ( item != 7 )
   {
      test_number_that_failed = 28;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 29;
      return( FALSE );
   }

   if ( item != 8 )
   {
      test_number_that_failed = 30;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 31;
      return( FALSE );
   }

   if ( item != 9 )
   {
      test_number_that_failed = 32;
      return( FALSE );
   }

   if ( queue.Get( item ) == FALSE )
   {
      test_number_that_failed = 33;
      return( FALSE );
   }

   if ( item != 10 )
   {
      test_number_that_failed = 34;
      return( FALSE );
   }

   // Queue is now empty, it should not Get() anything

   if ( queue.Get( item ) == TRUE )
   {
      test_number_that_failed = 35;
      return( FALSE );
   }

   if ( queue.GetLength() != 0 )
   {
      test_number_that_failed = 36;
      return( FALSE );
   }

   // OK, we passed the simple tests

   CQueue queue2( 5 );

   if ( queue2.Add( 1 ) == FALSE ) // m_AddIndex is now 1
   {
      test_number_that_failed = 37;
      return( FALSE );
   }

   if ( queue2.Add( 2 ) == FALSE ) // m_AddIndex is now 2
   {
      test_number_that_failed = 38;
      return( FALSE );
   }

   if ( queue2.Add( 3 ) == FALSE ) // m_AddIndex is now 3
   {
      test_number_that_failed = 39;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE ) // m_GetIndex is now 1
   {
      test_number_that_failed = 40;
      return( FALSE );
   }

   if ( item != 1 )
   {
      test_number_that_failed = 41;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE ) // m_GetIndex is now 2
   {
      test_number_that_failed = 42;
      return( FALSE );
   }

   if ( item != 2 )
   {
      test_number_that_failed = 43;
      return( FALSE );
   }

   if ( queue2.Add( 4 ) == FALSE )
   {
      test_number_that_failed = 44;
      return( FALSE );
   }

   if ( queue2.Add( 5 ) == FALSE )
   {
      test_number_that_failed = 45;
      return( FALSE );
   }

   if ( queue2.Add( 6 ) == FALSE )
   {
      test_number_that_failed = 46;
      return( FALSE );
   }

   if ( queue2.Add( 7 ) == FALSE ) // Should cause growth via the ReAlloc method
   {
      test_number_that_failed = 47;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE )
   {
      test_number_that_failed = 48;
      return( FALSE );
   }

   if ( item != 3 )
   {
      test_number_that_failed = 49;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE )
   {
      test_number_that_failed = 50;
      return( FALSE );
   }

   if ( item != 4 )
   {
      test_number_that_failed = 51;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE )
   {
      test_number_that_failed = 52;
      return( FALSE );
   }

   if ( item != 5 )
   {
      test_number_that_failed = 53;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE )
   {
      test_number_that_failed = 54;
      return( FALSE );
   }

   if ( item != 6 )
   {
      test_number_that_failed = 55;
      return( FALSE );
   }

   if ( queue2.Get( item ) == FALSE )
   {
      test_number_that_failed = 56;
      return( FALSE );
   }

   if ( item != 7 )
   {
      test_number_that_failed = 57;
      return( FALSE );
   }

   // Queue is now empty, it should not Get() anything

   if ( queue2.Get( item ) == TRUE )
   {
      test_number_that_failed = 58;
      return( FALSE );
   }

   if ( queue2.GetLength() != 0 )
   {
      test_number_that_failed = 59;
      return( FALSE );
   }

   test_number_that_failed = 59;
   return( TRUE );
}
