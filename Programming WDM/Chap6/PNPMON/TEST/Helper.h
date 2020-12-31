// Helper.h -- Declarations for helper driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef HELPER_H
#define HELPER_H

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#include <winsvc.h>

///////////////////////////////////////////////////////////////////////////////

class CHelper
{								// class CHelper
public:
	CHelper();
	~CHelper();

	BOOL		GetEvent(GUID& guid, GUID& event, CString& linkname, DWORD& datasize, LONG& textoffset, PBYTE data);
	BOOL		Initialize(LPCTSTR name);
	BOOL		Register(const GUID* guid, HANDLE hevent);
	VOID		Unregister(const GUID* guid);

protected:
	SC_HANDLE	m_hservice;		// handle to driver service
	HANDLE		m_hdriver;		// handle to device object
};								// class CHelper

extern CHelper theHelper;

#endif