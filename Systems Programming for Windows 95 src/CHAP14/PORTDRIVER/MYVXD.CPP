// myvxd.cpp -- Sample VCOMM port driver
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#include "stdvxd.h"
#pragma hdrstop

#include "serial.h"

///////////////////////////////////////////////////////////////////////////////
// Overrides for library new and delete operators.

void* ::operator new(unsigned int size)
	{							// operator new
	return _HeapAllocate(size, 0);
	}							// operator new

void ::operator delete(void* p)
	{							// operator delete
	if (p)
		_HeapFree(p, 0);
	}							// operator delete

///////////////////////////////////////////////////////////////////////////////

BOOL DriverControl(DWORD cf, DEVNODE devnode, DWORD refdata, ...);

///////////////////////////////////////////////////////////////////////////////

SYSCTL BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	return VCOMM_Register_Port_Driver((PFN) DriverControl);
	}							// OnSysDynamicDeviceInit

SYSCTL BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	CPort::DeleteAll();			// cleanup all allocated CPort's
	return TRUE;
	}							// OnSysDynamicDeviceExit

// VCOMM calls the DriverControl procedure once for each port

BOOL DriverControl(DWORD cf, DEVNODE devnode, DWORD refdata, ...)
	{							// DriverControl
	ASSERT(cf == DC_Initialize); // isn't supposed to be anything else
	ASSERT(devnode);			// should only work in PnP environment
	if (cf != DC_Initialize || !devnode)
		return FALSE;

	va_list ap;
	va_start(ap, refdata);

	// Note that PNP.DOC incorrectly says that the name is the 1st of
	// the variable args. It's really the 3d.

	DWORD iobase = va_arg(ap, DWORD);
	DWORD irq = va_arg(ap, DWORD);
	char *name = va_arg(ap, char *);

	va_end(ap);

	CSerialPort* port = new CSerialPort(name, iobase, irq, devnode);
	if (!port->AddPort(refdata))
		{						// unable to add port
		delete port;
		return FALSE;
		}						// unable to add port

	return TRUE;
	}							// DriverControl
