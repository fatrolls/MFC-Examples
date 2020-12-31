#include "ListProcesses.h"
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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: list_processes.cpp $
** $Revision: 1 $
** $Modtime: 1/15/00 10:22a $
*/

void list_processes( void )
{
   WFCTRACEINIT( TEXT( "list_processes()" ) );

   // The first thing we need to do is get a buffer large
   // enough to hold the raw data. I like overkill so I choose
   // 128K

   int data_buffer_size = 128 * 1024;

   BYTE * data_buffer = (BYTE *) malloc( data_buffer_size );

   if ( data_buffer == NULL )
   {
      WFCTRACE( TEXT( "Out of memory." ) );
      return;
   }

   ZeroMemory( data_buffer, data_buffer_size );

   if ( wfc_undocumented_get_system_process_list( data_buffer, data_buffer_size ) == TRUE )
   {
      print_process_list( data_buffer );
   }

   free( data_buffer );
}
