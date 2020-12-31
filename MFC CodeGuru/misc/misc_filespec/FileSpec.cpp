/*
 *	$Version:$
 *
 *	$Log:$
 */
#include "stdafx.h"
#include <stdlib.h>

#include "FileSpec.h"

CFileSpec::CFileSpec(FS_BUILTINS spec)
{
	Initialise(spec);
}

CFileSpec::CFileSpec(LPCTSTR spec)
{
	SetFullSpec(spec);
}

void CFileSpec::Initialise()
{
	m_drive.GetBufferSetLength(_MAX_DRIVE);
	m_path.GetBufferSetLength(_MAX_PATH);
	m_fileName.GetBufferSetLength(_MAX_FNAME);
	m_ext.GetBufferSetLength(_MAX_EXT);
}

void CFileSpec::UnLock()
{
	m_drive.ReleaseBuffer();
	m_path.ReleaseBuffer();
	m_fileName.ReleaseBuffer();
	m_ext.ReleaseBuffer();

	m_drive.FreeExtra();
	m_path.FreeExtra();
	m_fileName.FreeExtra();
	m_ext.FreeExtra();
}

void CFileSpec::Initialise(FS_BUILTINS spec)
{
	TCHAR path[_MAX_PATH],
		  *ptr;

	Initialise();

	switch (spec)
	{
	case FS_EMPTY:								//	Nothing
		break;

	case FS_APP:								//	Full application path and name
		GetModuleFileName(NULL, path, sizeof(path));
		SetFullSpec((LPCTSTR) path);
		break;

	case FS_APPDIR:								//	Application folder
		GetModuleFileName(NULL, path, sizeof(path));
		SetFullSpec((LPCTSTR) path);
		m_ext = "";
		m_fileName = "";
		break;

	case FS_WINDIR:								//	Windows folder
		GetWindowsDirectory(path, sizeof(path));

		if (path[strlen((LPCTSTR) path)] != '\\')
			strcat(path, "\\");
		
		SetFullSpec((LPCTSTR) path);
		break;

	case FS_SYSDIR:								//	System folder
		GetSystemDirectory(path, sizeof(path));

		if (path[strlen((LPCTSTR) path)] != '\\')
			strcat(path, "\\");
		
		SetFullSpec((LPCTSTR) path);
		break;

	case FS_TMPDIR:								//	Temporary folder
		GetTempPath(sizeof(path), path);
		SetFullSpec((LPCTSTR) path);
		break;

	case FS_DESKTOP:							//	Desktop folder
		GetShellFolder("Desktop");
		break;

	case FS_FAVOURITES:							//	Favourites folder
		GetShellFolder("Favorites");
		break;

	case FS_TEMPNAME:
		GetTempPath(sizeof(path), path);
		strcpy(path, ptr = _tempnam(path, "~"));
		SetFullSpec((LPCTSTR) path);
		free(ptr);
		break;

	default:
#ifdef _DEBUG
		afxDump << "Invalid initialisation spec for CFileSpec, " << spec << "\n";
#endif
		ASSERT(NULL);
	}
}

void CFileSpec::GetShellFolder(LPCTSTR folder)
{
	HKEY  key;
	TCHAR path[_MAX_PATH];
	DWORD dataType,
		  dataSize = sizeof(path);

	if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(key, folder, NULL, &dataType, (UCHAR *) path, &dataSize) == ERROR_SUCCESS)
		{
			//	We need to append a \\ here to ensure we get the full path into the path member.  If not
			//	_splitpath will take the last part of the path and think it's a filename
			if (path[strlen((LPCTSTR) path)] != '\\')
				strcat(path, "\\");

			SetFullSpec((LPCTSTR) path);
		}

		RegCloseKey(key);
	}
}

//	Operations
BOOL CFileSpec::Exists()
{
	return _access(GetFullSpec(), 0) == 0;
}

//	Access functions
CString CFileSpec::GetFileNameEx()
{
	return m_fileName + m_ext;
}

void CFileSpec::SetFileNameEx(LPCTSTR spec)
{
	m_fileName.GetBufferSetLength(_MAX_FNAME);
	m_ext.GetBufferSetLength(_MAX_EXT);
	_splitpath(spec, NULL, NULL, (LPTSTR) (LPCTSTR) m_fileName, (LPTSTR) (LPCTSTR) m_ext);
	m_fileName.ReleaseBuffer();
	m_ext.ReleaseBuffer();
	m_fileName.FreeExtra();
	m_ext.FreeExtra();
}

CString	CFileSpec::FullPathNoExtension()
{
	return m_drive + m_path + m_fileName;
}

CString CFileSpec::GetFullSpec()
{
	return m_drive + m_path + m_fileName + m_ext;
}

void CFileSpec::SetFullSpec(FS_BUILTINS spec)
{
	Initialise(spec);
}

void CFileSpec::SetFullSpec(LPCTSTR spec)
{
	Initialise();
	_splitpath(spec, (LPTSTR) (LPCTSTR) m_drive, (LPTSTR) (LPCTSTR) m_path, (LPTSTR) (LPCTSTR) m_fileName, (LPTSTR) (LPCTSTR) m_ext);
	UnLock();
}
