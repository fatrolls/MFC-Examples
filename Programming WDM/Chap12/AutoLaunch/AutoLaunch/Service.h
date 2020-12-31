// SERVICE.H -- Interface to CService class
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef SERVICE_H
#define SERVICE_H

#include <winsvc.h>

/////////////////////////////////////////////////////////////////////////////

class CService
{							// class CService
public:
	CService(DWORD Type, DWORD ControlsAccepted);
	virtual ~CService();

	SERVICE_STATUS_HANDLE	m_hService; // must be public for ServiceMainXx access

	static void __stdcall HandlerThunk(CService* service, DWORD ctlcode);
	static DWORD __stdcall HandlerExThunk(CService* service, DWORD ctlcode, DWORD evtype, PVOID evdata);
	static void __stdcall ServiceMainThunk(CService* service, DWORD argc, TCHAR* argv[]);

protected:
	SERVICE_STATUS			m_status;
	HANDLE					m_hevDone;

	virtual void			Handler(DWORD ctlcode);
	virtual DWORD			HandleDeviceChange(DWORD evtype, _DEV_BROADCAST_HEADER* dbhdr);
	virtual DWORD			HandlePowerEvent(DWORD evtype, DWORD flags);
	virtual DWORD			InitService(DWORD argc, TCHAR* argv[]) = 0;
	virtual void			Run();
	void					ServiceMain(DWORD argc, TCHAR* argv[]);
	virtual void			ShutdownService() = 0;
	void					UpdateStatus();
	void					UpdateStatus(DWORD state, DWORD code = 0);
};							// class CService

#define DEFINE_SERVICE(id, service) \
	void __stdcall Handler##id(DWORD ctlcode) { \
		CService::HandlerThunk(&service, ctlcode);} \
	void __stdcall ServiceMain##id(DWORD argc, TCHAR* argv[]) { \
		service.m_hService = RegisterServiceCtrlHandler(argv[0], Handler##id); \
		CService::ServiceMainThunk(&service, argc, argv);}

#define DEFINE_SERVICE_EX(id, service) \
	void __stdcall HandlerEx##id(DWORD ctlcode, DWORD evtype, PVOID evdata, PVOID context) { \
		CService::HandlerExThunk((CService*) context, ctlcode, evtype, evdata);} \
	void __stdcall ServiceMain##id(DWORD argc, TCHAR* argv[]) { \
		service.m_hService = RegisterServiceCtrlHandlerEx(argv[0], (LPHANDLER_FUNCTION_EX) HandlerEx##id, (PVOID) &service); \
		CService::ServiceMainThunk(&service, argc, argv);}

#define BEGIN_SERVICE_TABLE(tabname) SERVICE_TABLE_ENTRY tabname[] = {
#define DEFINE_SERVICE_TABLE_ENTRY(id, name) {name, ServiceMain##id},
#define END_SERVICE_TABLE() {NULL, NULL}};

#endif