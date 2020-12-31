// AUTOLAUNCH.H -- Public definitions for AutoLaunch Service
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef AUTOLAUNCH_H
#define AUTOLAUNCH_H

// Interface GUID for triggering application launch (see commentary immediately below):
// {BA4EC740-DA8B-11d2-81B5-00C04FA330A6}
DEFINE_GUID(GUID_AUTOLAUNCH_NOTIFY, 0xba4ec740, 0xda8b, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);

///////////////////////////////////////////////////////////////////////////////
//
// A device driver that wants to trigger an application launch should do the
// following:
//
// 1. Include the following statements in the INF file (substitute the correct name 
//    of your own install section for INSTALLSECT).
//
//		[INSTALLSECT.AUTOLAUNCH]
//		HKR,,FriendlyName,,"Optional Friendly Name For Device"
//		HKR,,AutoLaunch,,"command-string"
//
//		[INSTALLSECT.HW]
//		AddReg=INSTALLSECT.AUTOLAUNCH
//
//		[INSTALLSECT.NT.HW]
//		AddReg=INSTALLSECT.AUTOLAUNCH
//
//    These statements will create registry entries the the AUTOLAUNCH service uses to
//	  launch the desired application when the system starts your device.
//
//	  The "command-string" can include two %s substitution indicators. The first
//	  will be replaced by the symbolic link name of the device which has been detected,
//	  and the second will be replaced by the friendly name or device description for
//	  the device (or with "" if neither value is in the registry). You can also
//	  put environment variable names in the string with surrounding percents.
//
//	  An example of a valid command-string is:
//
//		HKR,,AutoLaunch,,"%WINDIR%\myapp.exe %s %s"
// 
// 2. Declare a UNICODE_STRING to hold a registered interface symbolic name in
//    your device extension. E.g.:
//
//		typedef struct _DEVICE_EXTENSION {
//			. . .
//			UNICODE_STRING AutoLaunchInterfaceName;
//			. . .
//			} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//
// 3. Register a GUID_AUTOLAUNCH_NOTIFY interface in your AddDevice function (these are
//    only a few of the statements in a complete AddDevice function)
//
//		#include <initguid.h>
//		#include "AutoLaunch.h"				// i.e., this file
//
//		NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
//			{							// AddDevice
//			PDEVICE_OBJECT fdo;			// new FDO
//			NTSTATUS status = IoCreateDevice(. . ., sizeof(DEVICE_EXTENSION), . . ., &fdo);
//			PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
//			IoRegisterDeviceInterface(pdo, &GUID_AUTOLAUNCH_NOTIFY, NULL, &pdx->AutoLaunchInterfaceName);
//			return STATUS_SUCCESS;
//			}							// AddDevice
//
// 4. Enable the interface when you successfully process IRP_MN_START_DEVICE:
//
//		NTSTATUS StartDevice(PDEVICE_OBJECT fdo, . . .)
//			{							// StartDevice
//			. . .
//			IoSetDeviceInterfaceState(&pdx->AutoLaunchInterfaceName, TRUE);
//			return STATUS_SUCCESS;
//			}							// StopDevice
//
// 5. Disable the interface when you process IRP_MN_STOP_DEVICE, IRP_MN_REMOVE_DEVICE,
//    and IRP_MN_SURPRISE_REMOVAL:
//
//		void StopDevice(PDEVICE_OBJECT fdo)
//			{							// StopDevice
//			. . .
//			IoSetDeviceInterfaceState(&pdx->AutoLaunchInterfaceName, FALSE);
//			. . .
//			}							// StopDevice
//
// 6. Release the memory occupied by the interface's symbolic link name when you
//	  are about to destroy the device object in response to IRP_MN_REMOVE_DEVICE:
//
//		void RemoveDevice(PDEVICE_OBJECT fdo)
//			{							// RemoveDevice
//			. . .
//			RtlFreeUnicodeString(&pdx->AutoLaunchInterfaceName);
//			IoDeleteDevice(fdo);
//			}							// RemoveDevice



#endif