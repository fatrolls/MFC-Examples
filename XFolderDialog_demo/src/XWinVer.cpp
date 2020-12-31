#include "stdafx.h"
#include "XWinVer.h"


BOOL Is2000OrGreater()
{
	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osinfo);

	DWORD dwPlatformId   = osinfo.dwPlatformId;
	DWORD dwMajorVersion = osinfo.dwMajorVersion;

	return ((dwPlatformId == 2) && 
			(dwMajorVersion >= 5));
}

BOOL Is2000()
{
	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osinfo);

	DWORD dwPlatformId   = osinfo.dwPlatformId;
	DWORD dwMajorVersion = osinfo.dwMajorVersion;
	DWORD dwMinorVersion = osinfo.dwMinorVersion;

	return ((dwPlatformId == 2) && 
			(dwMajorVersion == 5) && 
			(dwMinorVersion == 0));
}

BOOL IsXP()
{
	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osinfo);

	DWORD dwPlatformId   = osinfo.dwPlatformId;
	DWORD dwMajorVersion = osinfo.dwMajorVersion;
	DWORD dwMinorVersion = osinfo.dwMinorVersion;

	return ((dwPlatformId == 2) && 
			(dwMajorVersion == 5) && 
			(dwMinorVersion >= 1));
}

BOOL IsVista()
{
	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osinfo);

	DWORD dwPlatformId   = osinfo.dwPlatformId;
	DWORD dwMajorVersion = osinfo.dwMajorVersion;

	return ((dwPlatformId == 2) && 
			(dwMajorVersion >= 6));
}
