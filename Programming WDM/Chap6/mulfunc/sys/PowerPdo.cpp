// Power request handler mulfunc driver for child device PDOs
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

static NTSTATUS DefaultPowerHandler(IN PDEVICE_OBJECT pdo, IN PIRP Irp);
									  
///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS DispatchPowerPdo(IN PDEVICE_OBJECT pdo, IN PIRP Irp)
	{							// DispatchPowerPdo
	PPDO_EXTENSION pdx = (PPDO_EXTENSION) pdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_POWER);
	NTSTATUS status;

	static NTSTATUS (*fcntab[])(IN PDEVICE_OBJECT pdo, IN PIRP Irp) = {
		DefaultPowerHandler,		// IRP_MN_WAIT_WAKE
		DefaultPowerHandler,		// IRP_MN_POWER_SEQUENCE
		DefaultPowerHandler,		// IRP_MN_SET_POWER
		DefaultPowerHandler,		// IRP_MN_QUERY_POWER
		};
	
	ULONG fcn = stack->MinorFunction;
	if (fcn >= arraysize(fcntab))
		{							// unknown function
		status = DefaultPowerHandler(pdo, Irp); // some function we don't know about
		return status;
		}							// unknown function

#if DBG
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

		POWER_STATE_TYPE type = stack->Parameters.Power.Type;

		KdPrint((DRIVERNAME " (PDO) - POWER Request (%s)", fcnname[fcn]));
		if (type == SystemPowerState)
			KdPrint((", SystemPowerState = %s\n", sysstate[stack->Parameters.Power.State.SystemState]));
		else
			KdPrint((", DevicePowerState = %s\n", devstate[stack->Parameters.Power.State.DeviceState]));
		}
	else
		KdPrint((DRIVERNAME " (PDO) - POWER Request (%s)\n", fcnname[fcn]));

#endif // DBG

	status = (*fcntab[fcn])(pdo, Irp);
	return status;
	}							// DispatchPowerPdo

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NTSTATUS DefaultPowerHandler(IN PDEVICE_OBJECT pdo, IN PIRP Irp)
	{							// DefaultPowerHandler
	PoStartNextPowerIrp(Irp);	// must be done while we own the IRP
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DefaultPowerHandler
