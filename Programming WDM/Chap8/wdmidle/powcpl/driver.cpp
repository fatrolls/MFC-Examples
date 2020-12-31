// driver.cpp -- Dummy device interfaces for sample property page provider
// Copyright (C) 1998 by Walter Oney
// All rights reserved

// This module implements the CDriver class used in the sample power-management
// property page.
// and set parameter values.

#include "stdafx.h"
#include "driver.h"

// Include the declaration of the IOCTL codes used by the associated driver

#include <winioctl.h>
#include <initguid.h>
#include "GenericPower.h"

///////////////////////////////////////////////////////////////////////////////

CDriver::CDriver(CDeviceListEntry* device)
	{							// CDriver::CDriver
	m_changed = FALSE;
	m_name = device->m_linkname;
	m_friendlyname = device->m_friendlyname;
	m_wakeup = FALSE;
	m_itoPlugged = 0;
	m_itoUnplugged = 0;
	m_canidle = FALSE;
	m_canwake = FALSE;
	m_idle = FALSE;
	Refresh();
	}							// CDriver::CDriver

CDriver::~CDriver()
	{							// CDriver::~CDriver
	}							// CDriver::~CDriver

///////////////////////////////////////////////////////////////////////////////

void CDriver::IdleNow()
	{							// CDriver::IdleNow
	if (!CanIdle())
		return;
	HANDLE hDevice = CreateFile(m_name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return;
	DWORD junk;
	if (DeviceIoControl(hDevice, IOCTL_IDLENOW, NULL, 0, NULL, 0, &junk, NULL))
		m_idle = TRUE;
	CloseHandle(hDevice);
	}							// CDriver::IdleNow

///////////////////////////////////////////////////////////////////////////////

void CDriver::GetIdleTimeouts(PPOWER_DEVICE_TIMEOUTS ppdt)
	{							// CDriver::GetIdleTimeouts
	ppdt->ConservationIdleTime = m_itoUnplugged;
	ppdt->PerformanceIdleTime = m_itoPlugged;
	}							// CDriver::GetIdleTimeouts

///////////////////////////////////////////////////////////////////////////////

void CDriver::Refresh()
	{							// CDriver::Refresh
	HANDLE hDevice = CreateFile(m_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return;

	POWERINFO pi;
	DWORD junk;
	
	if (DeviceIoControl(hDevice, IOCTL_GET_POWERINFO, NULL, 0, &pi, sizeof(pi), &junk, NULL))
		{						// initialize settings
		m_responding = TRUE;
		m_itoPlugged = pi.ulPerformance;
		m_itoUnplugged = pi.ulConservation;
		m_wakeup = pi.bWakeup;
		m_canwake = pi.bCanWake;
		m_canidle = pi.bCanIdle;
		m_idle = pi.bIdle;
		}						// initialize settings
	else
		m_responding = FALSE;

	CloseHandle(hDevice);
	}							// CDriver::Refresh

///////////////////////////////////////////////////////////////////////////////

void CDriver::SaveChanges()
	{							// CDriver::SaveChanges
	if (!m_changed)
		return;

	m_changed = FALSE;

	HANDLE hDevice = CreateFile(m_name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return;

	POWERINFO pi;
	pi.ulConservation = m_itoUnplugged;
	pi.ulPerformance = m_itoPlugged;
	pi.bWakeup = m_wakeup == TRUE;
	pi.bCanWake = m_canwake;
	pi.bCanIdle = m_canidle;
	pi.bIdle = m_idle;

	DWORD junk;
	DeviceIoControl(hDevice, IOCTL_SET_POWERINFO, &pi, sizeof(pi), NULL, 0, &junk, NULL);
	CloseHandle(hDevice);
	}							// CDriver::SaveChanges

///////////////////////////////////////////////////////////////////////////////

void CDriver::SetIdleTimeouts(PPOWER_DEVICE_TIMEOUTS ppdt)
	{							// CDriver::SetIdleTimeouts
	if (m_itoUnplugged == ppdt->ConservationIdleTime
		&& m_itoPlugged == ppdt->PerformanceIdleTime)
		return;

	m_itoUnplugged = ppdt->ConservationIdleTime;
	m_itoPlugged = ppdt->PerformanceIdleTime;
	m_changed = TRUE;
	}							// CDriver::SetIdleTimeouts

///////////////////////////////////////////////////////////////////////////////

void CDriver::SetWakeupEnable(BOOL enable)
	{							// CDriver::SetWakeupEnable
	if (m_wakeup == enable)
		return;
	m_wakeup = enable;
	m_changed = TRUE;
	}							// CDriver::SetWakeupEnable
