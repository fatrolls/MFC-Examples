//_ **********************************************************
//_ 
//_ Name: driveinfo.h 
//_ Purpose: 
//_ Created: 15 September 1998 
//_ Author: D.R.Godson
//_ Modified By: 
//_ 
//_ Copyright (c) 1998 Brilliant Digital Entertainment Inc. 
//_ 
//_ **********************************************************

// CDriveInfo : returns info about drives attached

#if !defined ( DRIVEINFO_H )
#define DRIVEINFO_H 

enum { DRIVE_HOST = 7 };

class CDriveInfo
{
public:
	static float GetFreeBytes(int nDrive); // in MB
	static float GetTotalBytes(int nDrive); // in MB

	static CString GetVolume(int nDrive);
	static CString GetRoot(int nDrive);
	static CString GetFullName(int nDrive);
	static char GetLetter(int nDrive);
	static int GetType(int nDrive);
	static BOOL IsDriveAvailable(int nDrive);
	static void FormatName(CString& sFileName);
	static int GetDrive(CString sPathName);
	static BOOL IsMappedPath(CString sPathName);
	static BOOL IsRemotePath(CString sPathName);
	static BOOL IsFixedPath(CString sPathName);
	static BOOL IsReadonlyPath(CString sPathName);
	static DWORD GetSerialNumber(int nDrive);
};

#endif
