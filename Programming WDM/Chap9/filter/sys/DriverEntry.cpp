// Main program for filter driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);
VOID DriverUnload(IN PDRIVER_OBJECT fido);
NTSTATUS DispatchAny(IN PDEVICE_OBJECT fido, IN PIRP Irp);
NTSTATUS DispatchPower(IN PDEVICE_OBJECT fido, IN PIRP Irp);
NTSTATUS DispatchPnp(IN PDEVICE_OBJECT fido, IN PIRP Irp);
NTSTATUS DispatchWmi(IN PDEVICE_OBJECT fido, IN PIRP Irp);

BOOLEAN IsWin98();
BOOLEAN win98 = FALSE;

UNICODE_STRING servkey;

#if DBG
	NTSTATUS OnPnpComplete(PDEVICE_OBJECT fido, PIRP Irp, PDEVICE_EXTENSION pdx);
	VOID ReportAssignedResources(PCM_RESOURCE_LIST raw, PCM_RESOURCE_LIST translated);
	VOID ReportRequiredResources(PIO_RESOURCE_REQUIREMENTS_LIST list);
	VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list);

	static char* pnpname[] = {
		"IRP_MN_START_DEVICE",
		"IRP_MN_QUERY_REMOVE_DEVICE",
		"IRP_MN_REMOVE_DEVICE",
		"IRP_MN_CANCEL_REMOVE_DEVICE",
		"IRP_MN_STOP_DEVICE",
		"IRP_MN_QUERY_STOP_DEVICE",
		"IRP_MN_CANCEL_STOP_DEVICE",
		"IRP_MN_QUERY_DEVICE_RELATIONS",
		"IRP_MN_QUERY_INTERFACE",
		"IRP_MN_QUERY_CAPABILITIES",
		"IRP_MN_QUERY_RESOURCES",
		"IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
		"IRP_MN_QUERY_DEVICE_TEXT",
		"IRP_MN_FILTER_RESOURCE_REQUIREMENTS",
		"",
		"IRP_MN_READ_CONFIG",
		"IRP_MN_WRITE_CONFIG",
		"IRP_MN_EJECT",
		"IRP_MN_SET_LOCK",
		"IRP_MN_QUERY_ID",
		"IRP_MN_QUERY_PNP_DEVICE_STATE",
		"IRP_MN_QUERY_BUS_INFORMATION",
		"IRP_MN_DEVICE_USAGE_NOTIFICATION",
		"IRP_MN_SURPRISE_REMOVAL",
		"IRP_MN_QUERY_LEGACY_BUS_INFORMATION",
		};

	static char* restypes[] = {
		"CmResourceTypeNull",
		"CmResourceTypePort",
		"CmResourceTypeInterrupt",
		"CmResourceTypeMemory",
		"CmResourceTypeDma",
		"CmResourceTypeDeviceSpecific",
		"CmResourceTypeBusNumber",
		"CmResourceTypeDevicePrivate",
		"CmResourceTypeAssignedResource",
		"CmResourceTypeSubAllocateFrom",
		};

#endif // DBG

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	KdPrint((DRIVERNAME " - Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	// Insist that OS support at least the WDM level of the DDK we use

	if (!IoIsWdmVersionAvailable(1, 0))
		{
		KdPrint((DRIVERNAME " - Expected version of WDM (%d.%2.2d) not available\n", 1, 0));
		return STATUS_UNSUCCESSFUL;
		}

	// See if we're running under Win98 or NT:

	win98 = IsWin98();

#if DBG
	if (win98)
		KdPrint((DRIVERNAME " - Running under Windows 98\n"));
	else
		KdPrint((DRIVERNAME " - Running under NT\n"));
#endif

	// Save the name of the service key

	servkey.Buffer = (PWSTR) ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
	if (!servkey.Buffer)
		{
		KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of service key name\n", RegistryPath->Length + sizeof(WCHAR)));
		return STATUS_INSUFFICIENT_RESOURCES;
		}
	servkey.MaximumLength = RegistryPath->Length + sizeof(WCHAR);
	RtlCopyUnicodeString(&servkey, RegistryPath);

	// Initialize function pointers

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->DriverExtension->AddDevice = AddDevice;

	for (int i = 0; i < arraysize(DriverObject->MajorFunction); ++i)
		DriverObject->MajorFunction[i] = DispatchAny;

	DriverObject->MajorFunction[IRP_MJ_POWER] = DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP] = DispatchPnp;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = DispatchWmi;
	
	return STATUS_SUCCESS;
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
	{							// DriverUnload
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
	RtlFreeUnicodeString(&servkey);
	}							// DriverUnload

///////////////////////////////////////////////////////////////////////////////

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo)
	{							// AddDevice
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	NTSTATUS status;

	// Create a device object. Do *not* specify any device characteristics here because
	// some of them will get applied to all drivers in the stack, and it's not up to
	// us as a filter to control any of the propagated attributes (e.g., FILE_DEVICE_SECURE_OPEN).

	PDEVICE_OBJECT fido;
	status = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), NULL,
		FILE_DEVICE_UNKNOWN, 0, FALSE, &fido);
	if (!NT_SUCCESS(status))
		{						// can't create device object
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
		}						// can't create device object
	
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;

	// From this point forward, any error will have side effects that need to
	// be cleaned up. Using a try-finally block allows us to modify the program
	// easily without losing track of the side effects.

	__try
		{						// finish initialization
		IoInitializeRemoveLock(&pdx->RemoveLock, 0, 0, 0);
		pdx->DeviceObject = fido;
		pdx->Pdo = pdo;

		// Add our device object to the stack and propagate critical settings
		// from the immediately lower device object

		PDEVICE_OBJECT fdo = IoAttachDeviceToDeviceStack(fido, pdo);
		if (!fdo)
			{					// can't attach								 
			KdPrint((DRIVERNAME " - IoAttachDeviceToDeviceStack failed\n"));
			status = STATUS_DEVICE_REMOVED;
			__leave;
			}					// can't attach
		pdx->LowerDeviceObject = fdo;
		fido->Flags |= fdo->Flags & (DO_DIRECT_IO | DO_BUFFERED_IO | DO_POWER_PAGABLE | DO_POWER_INRUSH);
		fido->DeviceType = fdo->DeviceType;
		fido->Characteristics = fdo->Characteristics;

		// Clear the "initializing" flag so that we can get IRPs

		fido->Flags &= ~DO_DEVICE_INITIALIZING;
		}						// finish initialization
	__finally
		{						// cleanup side effects
		if (!NT_SUCCESS(status))
			{					// need to cleanup
			if (pdx->LowerDeviceObject)
				IoDetachDevice(pdx->LowerDeviceObject);
			IoDeleteDevice(fido);
			}					// need to cleanup
		}						// cleanup side effects

	return status;
	}							// AddDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE				// make no assumptions about pageability of dispatch fcns

NTSTATUS DispatchAny(IN PDEVICE_OBJECT fido, IN PIRP Irp)
	{							// DispatchAny
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

#if DBG
	static char* irpname[] = {
		"IRP_MJ_CREATE",
		"IRP_MJ_CREATE_NAMED_PIPE",
		"IRP_MJ_CLOSE",
		"IRP_MJ_READ",
		"IRP_MJ_WRITE",
		"IRP_MJ_QUERY_INFORMATION",
		"IRP_MJ_SET_INFORMATION",
		"IRP_MJ_QUERY_EA",
		"IRP_MJ_SET_EA",
		"IRP_MJ_FLUSH_BUFFERS",
		"IRP_MJ_QUERY_VOLUME_INFORMATION",
		"IRP_MJ_SET_VOLUME_INFORMATION",
		"IRP_MJ_DIRECTORY_CONTROL",
		"IRP_MJ_FILE_SYSTEM_CONTROL",
		"IRP_MJ_DEVICE_CONTROL",
		"IRP_MJ_INTERNAL_DEVICE_CONTROL",
		"IRP_MJ_SHUTDOWN",
		"IRP_MJ_LOCK_CONTROL",
		"IRP_MJ_CLEANUP",
		"IRP_MJ_CREATE_MAILSLOT",
		"IRP_MJ_QUERY_SECURITY",
		"IRP_MJ_SET_SECURITY",
		"IRP_MJ_POWER",
		"IRP_MJ_SYSTEM_CONTROL",
		"IRP_MJ_DEVICE_CHANGE",
		"IRP_MJ_QUERY_QUOTA",
		"IRP_MJ_SET_QUOTA",
		"IRP_MJ_PNP",
		};

	UCHAR type = stack->MajorFunction;
	if (type >= arraysize(irpname))
		KdPrint((DRIVERNAME " - Unknown IRP, major type %X\n", type));
	else
		KdPrint((DRIVERNAME " - %s\n", irpname[type]));
#endif

	// Pass request down without additional processing

	NTSTATUS status;
	status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	IoSkipCurrentIrpStackLocation(Irp);
	status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchAny

///////////////////////////////////////////////////////////////////////////////

NTSTATUS DispatchPower(IN PDEVICE_OBJECT fido, IN PIRP Irp)
	{							// DispatchPower

#if DBG
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;

	static char* fcnname[] = {
		"IRP_MN_WAIT_WAKE",
		"IRP_MN_POWER_SEQUENCE",
		"IRP_MN_SET_POWER",
		"IRP_MN_QUERY_POWER",
		};

	if (fcn == IRP_MN_SET_POWER || fcn == IRP_MN_QUERY_POWER)
		{
		static char* sysstate[] = {
			"PowerSystemUnspecified",
			"PowerSystemWorking",
			"PowerSystemSleeping1",
			"PowerSystemSleeping2",
			"PowerSystemSleeping3",
			"PowerSystemHibernate",
			"PowerSystemShutdown",
			"PowerSystemMaximum",
			};

		static char* devstate[] = {
			"PowerDeviceUnspecified",
			"PowerDeviceD0",
			"PowerDeviceD1",
			"PowerDeviceD2",
			"PowerDeviceD3",
			"PowerDeviceMaximum",
			};

		ULONG context = stack->Parameters.Power.SystemContext;
		POWER_STATE_TYPE type = stack->Parameters.Power.Type;

		KdPrint((DRIVERNAME " - IRP_MJ_POWER (%s)", fcnname[fcn]));
		if (type == SystemPowerState)
			KdPrint((", SystemPowerState = %s\n", sysstate[stack->Parameters.Power.State.SystemState]));
		else
			KdPrint((", DevicePowerState = %s\n", devstate[stack->Parameters.Power.State.DeviceState]));
		}
	else
		KdPrint((DRIVERNAME " - IRP_MJ_POWER (%s)\n", fcnname[fcn]));

#endif // DBG

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;
	PoStartNextPowerIrp(Irp);	// must be done while we own the IRP
	NTSTATUS status;
	status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	IoSkipCurrentIrpStackLocation(Irp);
	status = PoCallDriver(pdx->LowerDeviceObject, Irp);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchPower

///////////////////////////////////////////////////////////////////////////////

NTSTATUS DispatchPnp(IN PDEVICE_OBJECT fido, IN PIRP Irp)
	{							// DispatchPnp
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;

	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;
	status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

#if DBG

	KdPrint((DRIVERNAME " - IRP_MJ_PNP (%s)\n", pnpname[fcn]));

	BOOLEAN backend = FALSE;
	
	if (fcn == IRP_MN_START_DEVICE)
		{
		ReportAssignedResources(stack->Parameters.StartDevice.AllocatedResources,
			stack->Parameters.StartDevice.AllocatedResourcesTranslated);
		}
	else if (fcn == IRP_MN_FILTER_RESOURCE_REQUIREMENTS)
		{
		PIO_RESOURCE_REQUIREMENTS_LIST list = (PIO_RESOURCE_REQUIREMENTS_LIST) Irp->IoStatus.Information;
		if (!list)
			list = stack->Parameters.FilterResourceRequirements.IoResourceRequirementList;
		ReportRequiredResources(list);
		backend = TRUE;
		}
	else if (fcn == IRP_MN_QUERY_RESOURCE_REQUIREMENTS || fcn == IRP_MN_QUERY_RESOURCES)
		backend = TRUE;

	// Install a completion routine for diagnostic purposes. Note that using a completion
	// routine is not something that filter drivers necessarily have to do here -- I'm 
	// only doing it so this driver can print some interesting information about
	// resource requirements

	if (backend)
		{						// pass down with completion routine
		ASSERT(fcn != IRP_MN_REMOVE_DEVICE);
		IoCopyCurrentIrpStackLocationToNext(Irp);
		IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnPnpComplete, (PVOID) pdx, TRUE, TRUE, TRUE);
		return IoCallDriver(pdx->LowerDeviceObject, Irp);
		}						// pass down with completion routine
	else
		{						// pass down without completion routine
		IoSkipCurrentIrpStackLocation(Irp);
		status = IoCallDriver(pdx->LowerDeviceObject, Irp);

		if (fcn == IRP_MN_REMOVE_DEVICE)
			{
			IoReleaseRemoveLockAndWait(&pdx->RemoveLock, Irp);
			RemoveDevice(fido);
			}
		else
			IoReleaseRemoveLock(&pdx->RemoveLock, Irp);

		return status;
		}						// pass down without completion routine

#else // not DBG

	IoSkipCurrentIrpStackLocation(Irp);
	status = IoCallDriver(pdx->LowerDeviceObject, Irp);

	if (fcn == IRP_MN_REMOVE_DEVICE)
		{
		IoReleaseRemoveLockAndWait(&pdx->RemoveLock, Irp);
		RemoveDevice(fido);
		}
	else
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);

	return status;

#endif // not DBG
	}							// DispatchPnp

///////////////////////////////////////////////////////////////////////////////

NTSTATUS DispatchWmi(IN PDEVICE_OBJECT fido, IN PIRP Irp)
	{							// DispatchWmi
#if DBG
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;

	static char* fcnname[] = {
		"IRP_MN_QUERY_ALL_DATA",
		"IRP_MN_QUERY_SINGLE_INSTANCE",
		"IRP_MN_CHANGE_SINGLE_INSTANCE",
		"IRP_MN_CHANGE_SINGLE_ITEM",
		"IRP_MN_ENABLE_EVENTS",
		"IRP_MN_DISABLE_EVENTS",
		"IRP_MN_ENABLE_COLLECTION",
		"IRP_MN_DISABLE_COLLECTION",
		"IRP_MN_REGINFO",
		"IRP_MN_EXECUTE_METHOD",
		};

	KdPrint((DRIVERNAME " - IRP_MJ_SYSTEM_CONTROL (%s)\n", fcnname[fcn]));
#endif // DBG

	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;
	status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	IoSkipCurrentIrpStackLocation(Irp);
	status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchWmi

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID RemoveDevice(IN PDEVICE_OBJECT fido)
	{							// RemoveDevice
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fido->DeviceExtension;
	NTSTATUS status;

	if (pdx->LowerDeviceObject)
		IoDetachDevice(pdx->LowerDeviceObject);

	IoDeleteDevice(fido);
	}							// RemoveDevice

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

BOOLEAN IsWin98()
	{							// IsWin98
#ifdef _X86_
	return !IoIsWdmVersionAvailable(1, 0x10);
#else // not _X86_
	return FALSE;
#endif // not _X86_
	}							// IsWin98

#if DBG

///////////////////////////////////////////////////////////////////////////////

#ifdef _X86_

#pragma LOCKEDCODE

extern "C" void __declspec(naked) __cdecl _chkesp()
	{
	_asm je okay
	ASSERT(!DRIVERNAME " - Stack pointer mismatch!");
okay:
	_asm ret
	}

#endif // _X86_

///////////////////////////////////////////////////////////////////////////////

NTSTATUS OnPnpComplete(PDEVICE_OBJECT fido, PIRP Irp, PDEVICE_EXTENSION pdx)
	{							// OnPnpComplete

	if (Irp->PendingReturned)
		IoMarkIrpPending(Irp);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;
	DbgPrint(DRIVERNAME " - IRP_MN_PNP (%s) complete\n", pnpname[fcn]);

	switch (fcn)
		{						// select on subfunction

	case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:
	case IRP_MN_QUERY_RESOURCE_REQUIREMENTS: 
		ReportRequiredResources((PIO_RESOURCE_REQUIREMENTS_LIST) Irp->IoStatus.Information);
		break;

	case IRP_MN_QUERY_RESOURCES:
		ReportAssignedResources((PCM_RESOURCE_LIST) Irp->IoStatus.Information, NULL);
		break;
		}						// select on subfunction

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return STATUS_SUCCESS;
	}							// OnPnpComplete

///////////////////////////////////////////////////////////////////////////////

VOID ReportAssignedResources(PCM_RESOURCE_LIST raw, PCM_RESOURCE_LIST translated)
	{							// ReportAssignedResources
	if (KeGetCurrentIrql() >= DISPATCH_LEVEL)
		return;					// resource lists are in paged memory

	if (raw)
		{						// show untranslated resources
		DbgPrint(DRIVERNAME " - Resources:\n");
		ShowResources(&raw->List[0].PartialResourceList);
		}						// show untranslated resources

	if (translated)
		{						// show translated resources
		DbgPrint(DRIVERNAME " - Translated Resources:\n");
		ShowResources(&translated->List[0].PartialResourceList);
		}						// show translated resources

	}							// ReportAssignedResources

///////////////////////////////////////////////////////////////////////////////

VOID ReportRequiredResources(PIO_RESOURCE_REQUIREMENTS_LIST list)
	{							// ReportRequiredResources
	if (KeGetCurrentIrql() >= DISPATCH_LEVEL)
		return;					// resource lists are in paged memory

	if (!list)
		return;					// nothing to do

	ULONG numlists = list->AlternativeLists;
	PIO_RESOURCE_LIST reslist = list->List;
	while (numlists--)
		{						// for each list
		DbgPrint("  Requirements list:\n");
		PIO_RESOURCE_DESCRIPTOR resource = reslist->Descriptors;
		ULONG nres = reslist->Count;
		for (; nres; --nres, ++resource)
			{					// for each resource
			ULONG type = resource->Type;
			DbgPrint("    Type %s", type < arraysize(restypes) ? restypes[type] : "unknown");
			switch (type)
				{				// switch on resource type

			case CmResourceTypePort:
			case CmResourceTypeMemory:
				DbgPrint(" Length %d, Alignment %X, MinimumAddress %8X%8.8lX, MaximumAddress %8X%8.8lX\n",
					resource->u.Port.Length, resource->u.Port.Alignment,
					resource->u.Port.MinimumAddress, resource->u.Port.MaximumAddress);
				break;

			case CmResourceTypeInterrupt:
				DbgPrint(" MinimumVector %X, MaximumVector %X, shared %d\n",
					resource->u.Interrupt.MinimumVector, resource->u.Interrupt.MaximumVector,
					resource->ShareDisposition == CmResourceShareShared);
				break;

			case CmResourceTypeDma:
				DbgPrint(" MinimumChannel %d, MaximumChannel %d\n",
					resource->u.Dma.MinimumChannel, resource->u.Dma.MaximumChannel);
				break;

			default:
				DbgPrint(" %X %X %X\n", resource->u.DevicePrivate.Data[0],
					resource->u.DevicePrivate.Data[1], resource->u.DevicePrivate.Data[2]);
				break;
				}				// switch on resource type
			}					// for each resource

		reslist = (PIO_RESOURCE_LIST) resource;
		}						// for each list
	}							// ReportRequiredResources

///////////////////////////////////////////////////////////////////////////////	

VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list)
	{							// ShowResources
	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = list->PartialDescriptors;
	ULONG nres = list->Count;
	ULONG i;

	for (i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		ULONG type = resource->Type;

		KdPrint(("    Type %s", type < arraysize(restypes) ? restypes[type] : "unknown"));

		switch (type)
			{					// select on resource type
		case CmResourceTypePort:
		case CmResourceTypeMemory:
			KdPrint((" start %8X%8.8lX length %X\n",
				resource->u.Port.Start.HighPart, resource->u.Port.Start.LowPart,
				resource->u.Port.Length));
			break;
		
		case CmResourceTypeInterrupt:
			KdPrint(("  level %X, vector %X, affinity %X, shared %d\n",
				resource->u.Interrupt.Level, resource->u.Interrupt.Vector,
				resource->u.Interrupt.Affinity, resource->ShareDisposition == CmResourceShareShared));
			break;
	
		case CmResourceTypeDma:
			KdPrint(("  channel %d, port %X\n",
				resource->u.Dma.Channel, resource->u.Dma.Port));
			break;

		default:
			KdPrint(("\n"));
			break;
			}					// select on resource type
		}						// for each resource
	}							// ShowResources

#endif // DBG
