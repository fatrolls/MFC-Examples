// driver.h -- Declaration of dummy device interface
// Copyright (C) 1998 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H

#include <setupapi.h>
#include "DeviceList.h"

typedef struct _POWER_DEVICE_TIMEOUTS {
    DWORD   ConservationIdleTime;
    DWORD   PerformanceIdleTime;
} POWER_DEVICE_TIMEOUTS, *PPOWER_DEVICE_TIMEOUTS;

///////////////////////////////////////////////////////////////////////////////

class CDriver
{								// class CDriver
public:
	CDriver(CDeviceListEntry* device);
	~CDriver();

	CString m_name;				// name of device
	CString m_friendlyname;		// friendly name from registry

	BOOL CanIdle() const {return m_canidle;}
	BOOL CanWake() const {return m_canwake;}
	void GetIdleTimeouts(PPOWER_DEVICE_TIMEOUTS ppdt);
	void IdleNow();
	BOOL IsResponding() const {return m_responding;}
	BOOL IsWakeupEnabled() const {return m_wakeup != 0;}
	BOOL IsIdle() const {return m_idle != 0;}
	void Refresh();
	void SaveChanges();
	void SetIdleTimeouts(PPOWER_DEVICE_TIMEOUTS ppdt);
	void SetWakeupEnable(BOOL enable);

protected:
	BOOL m_wakeup;
	DWORD m_itoPlugged;
	DWORD m_itoUnplugged;
	BOOL m_changed;
	BOOL m_canidle;
	BOOL m_canwake;
	BOOL m_idle;
	BOOL m_responding;
};								// class CDriver

#endif