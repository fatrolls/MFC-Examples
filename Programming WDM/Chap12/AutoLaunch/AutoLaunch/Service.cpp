// SERVICE.CPP -- Implementation of CService class
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "service.h"

#ifndef NTSERVICE
	#error This file should only be used in the NT service build!
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CService::CService(DWORD type, DWORD ControlsAccepted)
	{							// CService::CService
	m_hService = NULL;
	memset(&m_status, 0, sizeof(m_status));
	m_hevDone = NULL;

	m_status.dwServiceType = type;
	m_status.dwControlsAccepted = ControlsAccepted;
	}							// CService::CService

CService::~CService()
	{							// CService::~CService
	if (m_hevDone)
		CloseHandle(m_hevDone);
	}							// CService::~CService

void __stdcall CService::HandlerThunk(CService* service, DWORD ctlcode)
	{							// CService::HandlerThunk
	service->Handler(ctlcode);
	}							// CService::HandlerThunk

void __stdcall CService::ServiceMainThunk(CService* service, DWORD argc, TCHAR* argv[])
	{							// CService::ServiceMainThunk
	service->ServiceMain(argc, argv);
	}							// CService::ServiceMainThunk

/////////////////////////////////////////////////////////////////////////////

void CService::Handler(DWORD ctlcode)
	{							// CService::Handler
	if (ctlcode == SERVICE_CONTROL_STOP)
		{						// stopping service
		SetEvent(m_hevDone);
		m_status.dwCurrentState = SERVICE_STOPPED;
		}						// stopping service

	UpdateStatus();
	}							// CService::Handler

/////////////////////////////////////////////////////////////////////////////

DWORD CService::HandleDeviceChange(DWORD evtype, _DEV_BROADCAST_HEADER* dbhdr)
	{							// CService::HandleDeviceChange
	return NO_ERROR;
	}							// CService::HandleDeviceChange

/////////////////////////////////////////////////////////////////////////////

DWORD CService::HandlePowerEvent(DWORD evtype, DWORD flags)
	{							// CService::HandlePowerEvent
	return NO_ERROR;
	}							// CService::HandlePowerEvent

/////////////////////////////////////////////////////////////////////////////

DWORD __stdcall CService::HandlerExThunk(CService* service, DWORD ctlcode, DWORD evtype, PVOID evdata)
	{							// CService::HandlerExThunk
	switch (ctlcode)
		{						// handle extended notification

	case SERVICE_CONTROL_DEVICEEVENT:
	case SERVICE_CONTROL_HARDWAREPROFILECHANGE:
		return service->HandleDeviceChange(evtype, (_DEV_BROADCAST_HEADER*) evdata);

	case SERVICE_CONTROL_POWEREVENT:
		return service->HandlePowerEvent(evtype, (DWORD) evdata);

	default:
		service->Handler(ctlcode);
		return NO_ERROR;
		}						// handle extended notification
	}							// CService::HandlerExThunk

/////////////////////////////////////////////////////////////////////////////

void CService::Run()
	{							// CService::Run
	WaitForSingleObject(m_hevDone, INFINITE);
	}							// CService::Run

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CService::ServiceMain(DWORD argc, TCHAR* argv[])
	{							// CService::ServiceMain
	if (!m_hService)
		{
		TRACE(_T("Error %d in RegisterServiceCtrlHandler\n"), GetLastError());
		return;
		}
	
	if (!(m_hevDone = CreateEvent(NULL, FALSE, FALSE, NULL)))
		{
		TRACE(_T("Error %d creating event\n"), GetLastError());
		return;
		}

	m_status.dwCheckPoint = 1;
	m_status.dwWaitHint = 10000;	// 10 seconds
	UpdateStatus(SERVICE_START_PENDING);

	DWORD code = InitService(argc, argv);
	if (code != 0)
		{						// error initializing
		TRACE(_T("Failing service startup with code %d\n"), code);
		UpdateStatus(SERVICE_STOPPED, code);
		return;
		}						// error initializing

	UpdateStatus(SERVICE_RUNNING);

	Run();

	ShutdownService();
	UpdateStatus(SERVICE_STOPPED);
	}							// CService::ServiceMain

///////////////////////////////////////////////////////////////////////////////

void CService::UpdateStatus()
	{							// CService::UpdateStatus
	SetServiceStatus(m_hService, &m_status);
	}							// CService::UpdateStatus

void CService::UpdateStatus(DWORD state, DWORD code /* = 0 */)
	{							// CService::UpdateStatus
	m_status.dwCurrentState = state;
	m_status.dwServiceSpecificExitCode = code;
	m_status.dwWin32ExitCode = code ? ERROR_SERVICE_SPECIFIC_ERROR : 0;

	SetServiceStatus(m_hService, &m_status);
	}							// CService::UpdateStatus
