#if ! defined( WFC_THREAD_INFORMATION_BLOCK_HEADER_FILE )

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

#define WFC_THREAD_INFORMATION_BLOCK_HEADER_FILE

/*
** This structure is derived from the TIB.H header
** file that Matt Peitrek published. I've renamed
** most things to avoid name collisions should
** Microsoft get around to documenting these things.
*/

#pragma pack( 1 )

typedef struct _WFC_EXCEPTION_RECORD
{
   struct _WFC_EXCEPTION_RECORD * Next;
   FARPROC                        Handler;
}
WFC_EXCEPTION_RECORD;

typedef struct _WFC_THREAD_INFORMATION_BLOCK
{
   WFC_EXCEPTION_RECORD * ExceptionRecordList;
   VOID * StackUserTop;
   VOID * StackUserBase;

   union
   {
      struct
      {
         WORD  TDB;
         WORD  SSSelectorForThunkingTo16Bits;
         DWORD Unknown1;
      }
      WIN95;

      struct
      {
         VOID * SubSystemThreadInformationBlock;
         DWORD  FiberData;
      }
      WINNT;
   }
   FIRST_UNION;

   VOID * Arbitrary;
   struct _WFC_THREAD_INFORMATION_BLOCK * Self;

   union
   {
      struct
      {
         WORD  ThreadInformationBlockFlags;
         WORD  Win16MutexCount;
         DWORD DebugContext;
         DWORD CurrentPriority;
         DWORD MessageQueueSelector;
      }
      WIN95;

      struct
      {
         DWORD Unknown1;
         DWORD ProcessID;
         DWORD ThreadID;
         DWORD Unknown2;
      }
      WINNT;
   }
   SECOND_UNION;

   VOID * ThreadLocalStorageArray;

   union
   {
      VOID * OwningProcessDatabase;
   }
   THIRD_UNION;
}
WFC_THREAD_INFORMATION_BLOCK;

#pragma pack()

#endif // WFC_THREAD_INFORMATION_BLOCK_HEADER_FILE
