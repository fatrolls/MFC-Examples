#include "ntifs.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT  pDriverObject, PUNICODE_STRING  pRegistryPath); 

NTSTATUS KE_Dispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp);
VOID KE_Unload(PDRIVER_OBJECT  DriverObject);    
