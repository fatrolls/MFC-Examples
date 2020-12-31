//_ **********************************************************
//_ 
//_ Name: driveinfo.cpp 
//_ Purpose: 
//_ Created: 15 September 1998 
//_ Author: D.R.Godson
//_ Modified By: 
//_ 
//_ Copyright (c) 1998 Brilliant Digital Entertainment Inc. 
//_ 
//_ **********************************************************

// CDriveInfo.cpp

#include "stdafx.h"
#include "driveinfo.h"

#include <direct.h>

float CDriveInfo::GetFreeBytes(int nDrive)
{
	CString sRoot;
	unsigned long totalClusters, freeClusters, sectors, bytes;
	float fSpace;

	ASSERT (nDrive > 0 && nDrive <= 26);

	if (IsDriveAvailable(nDrive))
	{
		sRoot = GetRoot(nDrive);
	
		::GetDiskFreeSpace(sRoot, &sectors, &bytes, &freeClusters, &totalClusters);
	
		// do maths like this to avoid truncation
		// errors
		fSpace = (float)sectors;
		fSpace *= bytes;
		fSpace *= freeClusters;
		fSpace /= 1048576;

		return fSpace;
	}
	
	return 0.0f;
}

CString CDriveInfo::GetVolume(int nDrive)
{
	CString sVolume, sRoot;

	ASSERT (nDrive > 0 && nDrive <= 26);

	if (IsDriveAvailable(nDrive))
	{
		sRoot = GetRoot(nDrive);

		GetVolumeInformation(sRoot, sVolume.GetBuffer(20), 20, NULL, NULL, NULL, NULL, 0);
		sVolume.ReleaseBuffer();
		FormatName(sVolume);

		return sVolume;
	}

	return "";
}

CString CDriveInfo::GetRoot(int nDrive)
{
	CString sRoot;

	sRoot = GetLetter(nDrive);
	sRoot += _T(":\\");

	return sRoot;
}

CString CDriveInfo::GetFullName(int nDrive)
{
	CString sFullName, sLetter, sVolume;

	ASSERT (nDrive > 0 && nDrive <= 26);

	if (IsDriveAvailable(nDrive))
	{
		sLetter = GetLetter(nDrive);
		sVolume = GetVolume(nDrive);

		sFullName = sVolume + " (" + sLetter + ":)";

		return sFullName;
	}

	return "";
}

float CDriveInfo::GetTotalBytes(int nDrive)
{
	CString sRoot;
	unsigned long totalClusters, freeClusters, sectors, bytes;
	float fSpace;

	ASSERT (nDrive > 0 && nDrive <= 26);

	if (IsDriveAvailable(nDrive))
	{
		sRoot = GetRoot(nDrive);
	
		::GetDiskFreeSpace(sRoot, &sectors, &bytes, &freeClusters, &totalClusters);
	
		// do maths like this to avoid truncation
		// errors
		fSpace = (float)sectors;
		fSpace *= bytes;
		fSpace *= totalClusters;
		fSpace /= 1048576;

		return fSpace;
	}
	
	return 0.0f;
}

char CDriveInfo::GetLetter(int nDrive)
{
	ASSERT (nDrive > 0 && nDrive <= 26);

	return (char)(nDrive + 'A' - 1);
}

int CDriveInfo::GetType(int nDrive)
{
	CString sVolume;

	ASSERT (nDrive > 0 && nDrive <= 26);

	// shortcut to avoid floppy access
	if (nDrive ==1 || nDrive == 2)
		return DRIVE_REMOVABLE;

	if (IsDriveAvailable(nDrive))
	{
		sVolume = GetVolume(nDrive);
		FormatName(sVolume);

		if (sVolume.Find(_T("Host")) >= 0)
			return DRIVE_HOST;
		else
			return ::GetDriveType(GetRoot(nDrive));
	}

	return DRIVE_UNKNOWN;
}

void CDriveInfo::FormatName(CString& sFilename) 
{
	CString sTemp, sChar;
	int nLen, nChar;
	char cChar, cLastChar = ' '; // space 

	// this function accepts pathnames and names with spaces
	sFilename.MakeLower();
	nLen = sFilename.GetLength();

	// for each word make the first letter upper case
	for (nChar = 0; nChar < nLen; nChar++)
	{
		cChar = sFilename[nChar];

		if (cLastChar == ' ' || cLastChar == '\\')
		{
			sChar = CString(cChar);
			sChar.MakeUpper();
			cChar = sChar[0];
		}

		sTemp += cChar;
		cLastChar = cChar;
	}

	sFilename = sTemp;
}

BOOL CDriveInfo::IsDriveAvailable(int nDrive)
{
	int nCurDrive;
	int nRes;

	// save cur drive and try to change to drive
	nCurDrive = _getdrive();
	nRes = _chdrive(nDrive);

	// if change successful change back before return
	if (nRes == 0)
		_chdrive(nCurDrive);

	return (nRes == 0) ? TRUE : FALSE;
}

int CDriveInfo::GetDrive(CString sPathName)
{
	char cDrive;
	int nDrive;

	if (sPathName.IsEmpty())
		return -1;

	// if its a UNC path return -1
	if (sPathName.Find("\\\\") == 0)
		return -1;

	// else
	cDrive = sPathName[0];
	cDrive = toupper(cDrive);
	nDrive = cDrive - 64;
	ASSERT (nDrive >= 1 && nDrive <= 26);

	if (nDrive < 1 || nDrive > 26)
		return -1;

	// else
	return nDrive;
}

BOOL CDriveInfo::IsMappedPath(CString sPathName)
{
	int nDrive;

	nDrive = GetDrive(sPathName);

	if (nDrive <= 0)
		return FALSE;

	return (GetType(nDrive) == DRIVE_REMOTE);
}

BOOL CDriveInfo::IsRemotePath(CString sPathName)
{
	if (sPathName.Find("\\NETHOOD\\") != -1) 
		return TRUE;

	return (GetDrive(sPathName) == -1 || IsMappedPath(sPathName));
}

BOOL CDriveInfo::IsFixedPath(CString sPathName)
{
	return (GetType(GetDrive(sPathName)) == DRIVE_FIXED);
}

BOOL CDriveInfo::IsReadonlyPath(CString sPathName)
{
	DWORD dwAttr = ::GetFileAttributes(sPathName);

	return (dwAttr == 0xffffffff || (dwAttr & FILE_ATTRIBUTE_READONLY));
}

DWORD CDriveInfo::GetSerialNumber(int nDrive)
{
	if (GetType(nDrive) != DRIVE_FIXED)
		return 0;

	DWORD dwHDSerialNum = 0;

	if (!GetVolumeInformation(GetRoot(nDrive), NULL, 0, &dwHDSerialNum, NULL, NULL, NULL, 0))
		return -1;

	return dwHDSerialNum;
}
