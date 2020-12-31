// Setup.h -- Declaration of setup helper classes
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef SETUP_H
#define SETUP_H

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

///////////////////////////////////////////////////////////////////////////////

struct InstallStruct {
	CString devid;				// target device id
	CString mfgname;			// name of manufacturer
	CString devname;			// name of device
	BOOL done;					// TRUE when time to stop enumeration
	};

///////////////////////////////////////////////////////////////////////////////

class CInf;
typedef BOOL (*PENUMDEVCALLBACK)(CInf* inf, const CString& devname, const CString& instsecname, const CStringArray& devid, PVOID context, DWORD& code);
typedef BOOL (*PENUMMFGCALLBACK)(CInf* inf, const CString& mfgname, const CString& modelname, PVOID context, DWORD& code);

///////////////////////////////////////////////////////////////////////////////

class CInf
{								// class CInf
public:
	CInf();
	~CInf();

	CString		m_name;			// name of file
	CString		m_classname;	// name of device class
	HINF		m_hinf;			// open handle
	GUID		m_guid;			// class guid for this INF

	DWORD		EnumDevices(const CString& modelname, PENUMDEVCALLBACK callback, PVOID context);
	DWORD		EnumManufacturers(PENUMMFGCALLBACK callback, PVOID context);
	DWORD		Open(LPCTSTR name, BOOL defsearch = TRUE);
};								// class CInf

///////////////////////////////////////////////////////////////////////////////

class CDevInfoSet
{								// class CDevInfoSet
public:
	CDevInfoSet();
	~CDevInfoSet();

	HDEVINFO	m_hinfo;		// handle of device info set
	CInf*		m_inf;			// INF file descriptor
	HWND		m_hwnd;			// parent window of dialogs
	SP_DEVINFO_DATA	m_devinfo;	// information element for one device
	BOOL		m_registered;	// TRUE when devnode has been created
	CString		m_devid;		// id for the device we're installing

	DWORD		Create(CInf* inf, HWND hwnd);
	DWORD		CreateDeviceInfo(const CString& devid);
	DWORD		RegisterDevice();
	DWORD		UnregisterDevice();
	DWORD		UpdateDriver();

	inline operator HDEVINFO() {return m_hinfo;}
};								// class CDevInfoSet

#endif
