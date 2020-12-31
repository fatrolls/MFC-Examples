#if ! defined( WFC_UNDOCUMENTED_HEADER_FILE )

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
** $Workfile: wfc_undocumented.h $
** $Revision: 3 $
** $Modtime: 2/04/00 6:46p $
*/

#define WFC_UNDOCUMENTED_HEADER_FILE

/*
** Data structures and functions in this header file
** can go away at any time. Use them at your own risk.
*/

// This information came out of a Dr. Dobb's Journal article
// #305 November 1999, "Inside Windows NT System Data" by
// Sven B. Schreiber, pp 40-48
// MANY THANKS!!!!!! I renamed the structures to avoid any
// name collisions in the future.

typedef struct _wfc_client_id
{
   HANDLE ProcessHandle;
   HANDLE ThreadHandle;
}
WFC_CLIENT_ID;

typedef enum _WFC_KWAIT_REASON
{
   Executive,
   FreePage,
   PageIn,
   PoolAllocation,
   DelayExecution,
   Suspended,
   UserRequest,
   WrExecutive,
   WrFreePage,
   WrPageIn,
   WrPoolAllocation,
   WrDelayExecution,
   WrSuspended,
   WrUserRequest,
   WrEventPair,
   WrQueue,
   WrLpcReceive,
   WrLpcReply,
   WrVirtualMemory,
   WrPageOut,
   WrRendezvous,
   Spare2,
   Spare3,
   Spare4,
   Spare5,
   Spare6,
   WrKernel,
   MaximumWaitReason
}
WFC_KWAIT_REASON;

typedef struct _wfc_system_thread
{
   ULONGLONG        KernelTime;
   ULONGLONG        UserTime;
   ULONGLONG        CreateTime;
   DWORD            UnknownValueAtOffset18;
   VOID *           StartAddress;
   WFC_CLIENT_ID    ClientID;
   DWORD            Priority;
   DWORD            BasePriority;
   DWORD            ContextSwitches;
   DWORD            ThreadState;
   WFC_KWAIT_REASON WaitReason;
   DWORD            Reserved;
}
WFC_SYSTEM_THREAD;

typedef struct _wfc_vm_counters
{
   DWORD PeakVirtualSize;
   DWORD VirtualSize;
   DWORD PageFaultCount;
   DWORD PeakWorkingSetSize;
   DWORD WorkingSetSize;
   DWORD QuotaPeakPagedPoolUsage;
   DWORD QuotaPagedPoolUsage;
   DWORD QuotaPeakNonPagedPoolUsage;
   DWORD QuotaNonPagedPoolUsage;
   DWORD PagefileUsage;
   DWORD PeakPagefileUsage;
}
WFC_VM_COUNTERS;

typedef struct _wfc_unicode_string
{
   USHORT Length;
   USHORT MaximumLength;
   WCHAR  * Buffer;
}
WFC_UNICODE_STRING;

typedef struct _wfc_system_process_information
{
   DWORD              Next;
   DWORD              ThreadCount;
   DWORD              Reserved1;
   DWORD              Reserved2;
   DWORD              Reserved3;
   DWORD              Reserved4;
   DWORD              Reserved5;
   DWORD              Reserved6;
   ULONGLONG          CreateTime;
   ULONGLONG          UserTime;
   ULONGLONG          KernelTime;
   WFC_UNICODE_STRING Name;
   LONG               BasePriority;
   DWORD              UniqueProcessID;
   DWORD              InheritedFromUniqueProcessID;
   DWORD              HandleCount;
   DWORD              Reserved7;
   DWORD              Reserved8;
   WFC_VM_COUNTERS    VmCounters;
   DWORD              CommitChargeInBytes;
   WFC_SYSTEM_THREAD  Threads[ 1 ];
}
WFC_SYSTEM_PROCESS_INFORMATION;

typedef struct _wfc_system_handle_information
{
   DWORD  ProcessID;
   BYTE   ObjectType;
   BYTE   Flags;
   WORD   Value;
   VOID * Object;
}
WFC_SYSTEM_HANDLE_INFORMATION;

BOOL PASCAL wfc_undocumented_get_system_process_list( BYTE * buffer, DWORD size_of_buffer );

#endif // WFC_UNDOCUMENTED_HEADER_FILE
