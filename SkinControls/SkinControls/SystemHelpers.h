
#ifndef SYSTEM_HELPERS_H_
#define SYSTEM_HELPERS_H_
#pragma once

#include "SkinControlsDefine.h"

#include <oleacc.h>

class CSystemVersion;
// -----------------------------------------------------------------------
// Summary:
//     The XTPSystemVersion function is used for access to the
//     CSystemVersion class.
// Remarks:
//     Call this function to access CSystemVersion members. Since
//     this class is designed as a single instance object you can only
//     access its members through this method. You cannot directly
//     instantiate an object of type CSystemVersion.
// Returns:
//     A pointer to the one and only CSystemVersion instance.
// Example:
//     The following example demonstrates the use of XTPSystemVersion.
// <code>
// bool bIsWinNT = XTPSystemVersion()-\>IsWinNT4();
// </code>
// See Also:
//     CSystemVersion
// -----------------------------------------------------------------------
SKIN_CONTROLS_EXPORT CSystemVersion* AFXAPI SystemVersion();

//===========================================================================
// Summary:
//     CSystemVersion is a OSVERSIONINFO derived class. This class
//     wraps the Win32 API GetVersionEx(...), used to get the current
//     Windows OS version. CSystemVersion is a single instance, or
//     "singleton" object, that is accessed with the Get() method.
//===========================================================================
class SKIN_CONTROLS_EXPORT CSystemVersion : public OSVERSIONINFO
{
private:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CSystemVersion object.
	//-----------------------------------------------------------------------
	CSystemVersion();

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 3.1.
	// Returns:
	//     true if the OS is Windows 3.1, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin31() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 95.
	// Returns:
	//     true if the OS is Windows 95, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin95() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 98.
	// Returns:
	//     true if the OS is Windows 98, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin98() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows ME.
	// Returns:
	//     true if the OS is Windows ME, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinME() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows NT 4.
	// Returns:
	//     true if the OS is Windows NT 4, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinNT4() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 2000.
	// Returns:
	//     true if the OS is Windows 2000, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin2K() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows XP.
	// Returns:
	//     true if the OS is Windows XP, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinXP() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is greater than or equal to Windows 3.1.
	// Returns:
	//     true if the OS is greater than or equal to Windows 3.1,
	//     otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin31OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//      Call this member function to check whether or not the
	//      operating system is of the Windows 9x family, and if it is
	//      Windows 95 or a later version.
	// Returns:
	//      true if the OS is of the Windows 9x family, and is Windows 95
	///     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin95OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family, and if it is
	//     Windows 98 or a later version.
	// Returns:
	//     true if the OS is of the Windows 9x family, and is Windows 98
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin98OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family
	// Returns:
	//     true if the OS is of the Windows 9x family
	//-----------------------------------------------------------------------
	bool IsWin9x() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family, and if it is
	//     Windows ME or a later version.
	// Returns:
	//     true if the OS is of the Windows 9x family, and is Windows ME
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinMEOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows NT 4 or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows NT
	//     4 or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinNT4OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows 2000 or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows
	//     2000 or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin2KOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows XP or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows XP
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinXPOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows Vista or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows Vista
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWinVistaOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows 7 or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows 7
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	bool IsWin7OrGreater() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Use this member function to return the version number of the
	//      comctl32.dll. The high-order word of the return
	//     value represents the major version number and the low-order
	//     word of the returned value represents the minor version number.
	// Returns:
	//     A DWORD value if successful, otherwise 0L.
	//-----------------------------------------------------------------------
	DWORD GetComCtlVersion() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if right-to-left (RTL) formatting is supported by current OS
	// Returns:
	//     TRUE if right-to-left (RTL) formatting is supported.
	//-----------------------------------------------------------------------
	BOOL IsLayoutRTLSupported() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if ClearType text is supported by current OS
	//-----------------------------------------------------------------------
	BOOL IsClearTypeTextQualitySupported() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if MBCS is enabled
	//-----------------------------------------------------------------------
	int GetMaxCharSize() const;

private:

	//-----------------------------------------------------------------------
	// Summary:
	//     Checks to see if the OS is greater or equal to the specified
	//     version number
	// Returns:
	//     true if the OS is greater than or equal to the specified
	//     version.
	//-----------------------------------------------------------------------
	bool GreaterThanEqualTo(const DWORD maj, const DWORD min) const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Checks to see if the OS is equal to the specified version
	//     number
	// Returns:
	//     true if the OS is equal to the specified version.
	//-----------------------------------------------------------------------
	bool EqualTo(const DWORD maj, const DWORD min) const;

private:

	friend SKIN_CONTROLS_EXPORT CSystemVersion* AFXAPI SystemVersion();
};

#endif // SYSTEM_HELPERS_H_
