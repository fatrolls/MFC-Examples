#if ! defined( SENDER_HEADER_FILE )

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
** $Workfile: wfc_thread_information_block.h $
** $Revision: 2 $
** $Modtime: 1/24/00 8:37p $
*/

#define SENDER_HEADER_FILE

#include <wfc.h>

void prepare_buffer( CRandomNumberGenerator2& random, DWORD *& buffer, DWORD size, DWORD& checksum );

#endif // SENDER_HEADER_FILE
