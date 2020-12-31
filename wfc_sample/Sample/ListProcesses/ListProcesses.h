#if ! defined( LIST_PROCESSES_HEADER_FILE )

#define LIST_PROCESSES_HEADER_FILE

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
** $Workfile: ListProcesses.h $
** $Revision: 1 $
** $Modtime: 1/15/00 10:22a $
*/

#include <wfc.h>

void list_processes( void );
void print_process_list( BYTE * data_buffer );

#endif // LIST_PROCESSES_HEADER_FILE