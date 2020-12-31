#include "KernelExec.h"
#include "Process.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT  pDriverObject, PUNICODE_STRING  pRegistryPath)
{
	
	NTSTATUS NtStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT pDeviceObject = NULL;
	UNICODE_STRING usDriverName, usDosDeviceName;
	
	
	RtlInitUnicodeString(&usDriverName, L"\\Device\\KernelExec");
	
	
	NtStatus = IoCreateDevice(pDriverObject, 0, &usDriverName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	
	if(NtStatus == STATUS_SUCCESS)
	{
		pDriverObject->MajorFunction[IRP_MJ_CLEANUP]           = KE_Dispatch; 
		pDriverObject->MajorFunction[IRP_MJ_CLOSE]             = KE_Dispatch;
		pDriverObject->MajorFunction[IRP_MJ_CREATE]            = KE_Dispatch;
		pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]    = KE_Dispatch;
		pDriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = KE_Dispatch;
		pDriverObject->MajorFunction[IRP_MJ_READ]              = KE_Dispatch;
		pDriverObject->MajorFunction[IRP_MJ_WRITE]             = KE_Dispatch;
		pDriverObject->DriverUnload =  KE_Unload;
		
		DbgPrint("KernelExec -> Driver Loaded");
	}

	RunProcess("c:\\rawwrite.exe");
	
	return NtStatus;
}

VOID KE_Unload(PDRIVER_OBJECT  DriverObject)
{
    IoDeleteDevice(DriverObject->DeviceObject);
	DbgPrint("KernelExec -> Driver Unloaded");
}

NTSTATUS KE_Dispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//Nothing to do here, just complete the request and return
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	
	return STATUS_SUCCESS;
}
