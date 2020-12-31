
#include "stdafx.h"
#include "SystemHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRACE_ACCESSIBLE(x)


//===========================================================================
// CSystemVersion class
//===========================================================================

CSystemVersion::CSystemVersion()
{
	// zero memory and set struct size.
	::ZeroMemory((OSVERSIONINFO*)this, sizeof(OSVERSIONINFO));
	dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	// get the Windows OS version information.
	::GetVersionEx((OSVERSIONINFO*)this);
}

SKIN_CONTROLS_EXPORT CSystemVersion* AFXAPI SystemVersion()
{
	static CSystemVersion instance;
	return &instance;
}

bool CSystemVersion::IsWin31() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32s);
}

bool CSystemVersion::IsWin95() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		(dwMajorVersion == 4) && (dwMinorVersion < 10);
}

bool CSystemVersion::IsWin98() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		EqualTo(4, 10);
}

bool CSystemVersion::IsWin9x() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
}

bool CSystemVersion::IsWinME() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		EqualTo(4, 90);
}

bool CSystemVersion::IsWinNT4() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(4, 0);
}

bool CSystemVersion::IsWin2K() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(5, 0);
}

bool CSystemVersion::IsWinXP() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(5, 1);
}

bool CSystemVersion::IsWin95OrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		(dwMajorVersion >= 4);
}

bool CSystemVersion::IsWin98OrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		GreaterThanEqualTo(4, 10);
}

bool CSystemVersion::IsWinMEOrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		GreaterThanEqualTo(4, 90);
}

bool CSystemVersion::IsWinNT4OrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		(dwMajorVersion >= 4);
}

bool CSystemVersion::IsWin2KOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		(dwMajorVersion >= 5);
}

bool CSystemVersion::IsWinXPOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		GreaterThanEqualTo(5, 1);
}

bool CSystemVersion::IsWinVistaOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		GreaterThanEqualTo(6, 0);
}

bool CSystemVersion::IsWin7OrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		GreaterThanEqualTo(6, 1);
}

bool CSystemVersion::GreaterThanEqualTo(const DWORD maj, const DWORD min) const
{
	return (dwMajorVersion > maj) || (dwMajorVersion == maj &&
		dwMinorVersion >= min);
}

bool CSystemVersion::EqualTo(const DWORD maj, const DWORD min) const
{
	return (dwMajorVersion == maj) && (dwMinorVersion == min);
}

BOOL CSystemVersion::IsLayoutRTLSupported() const
{
	return IsWin2KOrGreater() || GetSystemMetrics(SM_MIDEASTENABLED);
}

BOOL CSystemVersion::IsClearTypeTextQualitySupported() const
{
	return IsWinXPOrGreater();
}

int CSystemVersion::GetMaxCharSize() const
{
#ifdef _UNICODE
	return 1;
#else
	static int nMaxCharSize = -1;
	if (nMaxCharSize == -1)
	{
		CPINFO info;
		GetCPInfo(GetOEMCP(), &info);
		nMaxCharSize = info.MaxCharSize;
	}
	return nMaxCharSize;
#endif
}
