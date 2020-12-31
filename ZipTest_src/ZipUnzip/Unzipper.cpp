// Unzipper.cpp: implementation of the CUnzipper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Unzipper.h"

#include "zlib\unzip.h"
#include "zlib\iowin32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const UINT BUFFERSIZE = 2048;

CUnzipper::CUnzipper(LPCTSTR szFilePath) : m_uzFile(0)
{
	OpenZip(szFilePath);
}

CUnzipper::~CUnzipper()
{
	CloseZip();
}

bool CUnzipper::CloseZip()
{
	unzCloseCurrentFile(m_uzFile);

	int nRet = unzClose(m_uzFile);
	m_uzFile = NULL;
	m_szOutputFolder[0] = 0;

	return (nRet == UNZ_OK);
}

// simple interface
bool CUnzipper::Unzip(bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	return UnzipTo(m_szOutputFolder, bIgnoreFilePath);
}

bool CUnzipper::UnzipTo(LPCTSTR szFolder, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	if (!szFolder || !CreateFolder(szFolder))
		return FALSE;

	if (GetFileCount() == 0)
		return FALSE;

	if (!GotoFirstFile())
		return FALSE;

	// else
	do
	{
		if (!UnzipFile(szFolder, bIgnoreFilePath))
			return FALSE;
	}
	while (GotoNextFile());
	
	return TRUE;
}

// static version
bool CUnzipper::Unzip(LPCTSTR szFileName, LPCTSTR szFolder, bool bIgnoreFilePath)
{
	CUnzipper unz;

	if (!unz.OpenZip(szFileName))
		return FALSE;

	return unz.UnzipTo(szFolder, bIgnoreFilePath);
}

// extended interface
bool CUnzipper::OpenZip(LPCTSTR szFilePath)
{
	CloseZip();

	if (!szFilePath || !lstrlen(szFilePath))
		return false;

	// convert szFilePath to fully qualified path 
	char szFullPath[MAX_PATH];
	
	if (!GetFullPathName(szFilePath, MAX_PATH, szFullPath, NULL))
		return false;
	
	m_uzFile = unzOpen(szFullPath);
	
	if (m_uzFile)
	{
		char szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szFName[_MAX_FNAME];
		
		_splitpath(szFullPath, szDrive, szFolder, szFName, NULL);
		_makepath(m_szOutputFolder, szDrive, szFolder, szFName, NULL);
	}

	return (m_uzFile != NULL);
}

bool CUnzipper::SetOutputFolder(LPCTSTR szFolder)
{
	DWORD dwAttrib = GetFileAttributes(szFolder);

	if (dwAttrib != 0xffffffff && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		return FALSE;

	lstrcpy(m_szOutputFolder, szFolder);

	return CreateFolder(szFolder);
}

int CUnzipper::GetFileCount()
{
	if (!m_uzFile)
		return 0;

	unz_global_info info;

	if (unzGetGlobalInfo(m_uzFile, &info) == UNZ_OK)
	{
		return (int)info.number_entry;
	}

	return 0;
}

bool CUnzipper::GetFileInfo(int nFile, UZ_FileInfo& info)
{
	if (!m_uzFile)
		return FALSE;

	if (!GotoFile(nFile))
		return FALSE;

	return GetFileInfo(info);
}

bool CUnzipper::UnzipFile(int nFile, LPCTSTR szFolder, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	if (!szFolder)
		szFolder = m_szOutputFolder;

	if (!GotoFile(nFile))
		return FALSE;

	return UnzipFile(szFolder, bIgnoreFilePath);
}

bool CUnzipper::GotoFirstFile(LPCTSTR szExt)
{
	if (!m_uzFile)
		return FALSE;

	if (!szExt || !lstrlen(szExt))
		return (unzGoToFirstFile(m_uzFile) == UNZ_OK);

	// else
	if (unzGoToFirstFile(m_uzFile) == UNZ_OK)
	{
		UZ_FileInfo info;

		if (!GetFileInfo(info))
			return FALSE;

		// test extension
		char szFExt[_MAX_EXT];
		_splitpath(info.szFileName, NULL, NULL, NULL, szFExt);

		if (szFExt)
		{
			if (lstrcmpi(szExt, szFExt + 1) == 0)
				return TRUE;
		}

		return GotoNextFile(szExt);
	}

	return FALSE;
}

bool CUnzipper::GotoNextFile(LPCTSTR szExt)
{
	if (!m_uzFile)
		return FALSE;

	if (!szExt || !lstrlen(szExt))
		return (unzGoToNextFile(m_uzFile) == UNZ_OK);

	// else
	UZ_FileInfo info;

	while (unzGoToNextFile(m_uzFile) == UNZ_OK)
	{
		if (!GetFileInfo(info))
			return FALSE;

		// test extension
		char szFExt[_MAX_EXT];
		_splitpath(info.szFileName, NULL, NULL, NULL, szFExt);

		if (szFExt)
		{
			if (lstrcmpi(szExt, szFExt + 1) == 0)
				return TRUE;
		}
	}

	return FALSE;

}

bool CUnzipper::GetFileInfo(UZ_FileInfo& info)
{
	if (!m_uzFile)
		return FALSE;

	unz_file_info uzfi;

	ZeroMemory(&info, sizeof(info));
	ZeroMemory(&uzfi, sizeof(uzfi));

	if (UNZ_OK != unzGetCurrentFileInfo(m_uzFile, &uzfi, info.szFileName, MAX_PATH, NULL, 0, info.szComment, MAX_COMMENT))
		return FALSE;

	// copy across
	info.dwVersion = uzfi.version;	
	info.dwVersionNeeded = uzfi.version_needed;
	info.dwFlags = uzfi.flag;	
	info.dwCompressionMethod = uzfi.compression_method; 
	info.dwDosDate = uzfi.dosDate;  
	info.dwCRC = uzfi.crc;	 
	info.dwCompressedSize = uzfi.compressed_size; 
	info.dwUncompressedSize = uzfi.uncompressed_size;
	info.dwInternalAttrib = uzfi.internal_fa; 
	info.dwExternalAttrib = uzfi.external_fa; 

	// replace filename forward slashes with backslashes
	int nLen = lstrlen(info.szFileName);

	while (nLen--)
	{
		if (info.szFileName[nLen] == '/')
			info.szFileName[nLen] = '\\';
	}

	// is it a folder?
	info.bFolder = ((info.dwExternalAttrib & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

	return TRUE;
}

bool CUnzipper::UnzipFile(LPCTSTR szFolder, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	if (!szFolder)
		szFolder = m_szOutputFolder;

	if (!CreateFolder(szFolder))
		return FALSE;

	UZ_FileInfo info;
	GetFileInfo(info);

	// if the item is a folder then create it and return 'TRUE'
	if (info.bFolder)
	{
		char szFolderPath[MAX_PATH];
		_makepath(szFolderPath, NULL, m_szOutputFolder, info.szFileName, NULL);

		return CreateFolder(szFolderPath);
	}

	// build the output filename
	char szFilePath[MAX_PATH];

	if (bIgnoreFilePath)
	{
		char szFName[_MAX_FNAME], szExt[_MAX_EXT];

		_splitpath(info.szFileName, NULL, NULL, szFName, szExt);
		_makepath(info.szFileName, NULL, NULL, szFName, szExt);
	}

	_makepath(szFilePath, NULL, szFolder, info.szFileName, NULL);

	// open the input and output files
	if (!CreateFilePath(szFilePath))
		return FALSE;

	HANDLE hOutputFile = ::CreateFile(szFilePath, 
										GENERIC_WRITE,
										0,
										NULL,
										CREATE_ALWAYS,
										FILE_ATTRIBUTE_NORMAL,
										NULL);

	if (INVALID_HANDLE_VALUE == hOutputFile)
		return FALSE;

	if (unzOpenCurrentFile(m_uzFile) != UNZ_OK)
		return FALSE;

	// read the file and output
	int nRet = UNZ_OK;
	char pBuffer[BUFFERSIZE];

	do
	{
		nRet = unzReadCurrentFile(m_uzFile, pBuffer, BUFFERSIZE);

		if (nRet > 0)
		{
			// output
			DWORD dwBytesWritten = 0;

			if (!::WriteFile(hOutputFile, pBuffer, nRet, &dwBytesWritten, NULL) ||
				dwBytesWritten != (DWORD)nRet)
			{
				nRet = UNZ_ERRNO;
				break;
			}
		}
	}
	while (nRet > 0);

	CloseHandle(hOutputFile);
	unzCloseCurrentFile(m_uzFile);

	if (nRet == UNZ_OK)
		SetFileModTime(szFilePath, info.dwDosDate);

	return (nRet == UNZ_OK);
}

bool CUnzipper::GotoFile(int nFile)
{
	if (!m_uzFile)
		return FALSE;

	if (nFile < 0 || nFile >= GetFileCount())
		return FALSE;

	GotoFirstFile();

	while (nFile--)
	{
		if (!GotoNextFile())
			return FALSE;
	}

	return TRUE;
}

bool CUnzipper::GotoFile(LPCTSTR szFileName, bool bIgnoreFilePath)
{
	if (!m_uzFile)
		return FALSE;

	// try the simple approach
	if (unzLocateFile(m_uzFile, szFileName, 2) == UNZ_OK)
		return TRUE;

	else if (bIgnoreFilePath)
	{ 
		// brute force way
		if (unzGoToFirstFile(m_uzFile) != UNZ_OK)
			return FALSE;

		UZ_FileInfo info;

		do
		{
			if (!GetFileInfo(info))
				return FALSE;

			// test name
			char szFName[_MAX_FNAME], szName[_MAX_FNAME], szExt[_MAX_EXT];

			_splitpath(info.szFileName, NULL, NULL, szName, szExt);
			_makepath(szFName, NULL, NULL, szName, szExt);

			if (lstrcmpi(szFileName, szFName) == 0)
				return TRUE;
		}
		while (unzGoToNextFile(m_uzFile) == UNZ_OK);
	}

	// else
	return FALSE;
}

bool CUnzipper::CreateFolder(LPCTSTR szFolder)
{
	if (!szFolder || !lstrlen(szFolder))
		return FALSE;

	DWORD dwAttrib = GetFileAttributes(szFolder);

	// already exists ?
	if (dwAttrib != 0xffffffff)
		return ((dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);

	// recursively create from the top down
	char* szPath = _strdup(szFolder);
	char* p = strrchr(szPath, '\\');

	if (p) 
	{
		// The parent is a dir, not a drive
		*p = '\0';
			
		// if can't create parent
		if (!CreateFolder(szPath))
		{
			free(szPath);
			return FALSE;
		}
		free(szPath);

		if (!::CreateDirectory(szFolder, NULL)) 
			return FALSE;
	}
	
	return TRUE;
}

bool CUnzipper::CreateFilePath(LPCTSTR szFilePath)
{
	char* szPath = _strdup(szFilePath);
	char* p = strrchr(szPath,'\\');

	bool bRes = FALSE;

	if (p)
	{
		*p = '\0';

		bRes = CreateFolder(szPath);
	}

	free(szPath);

	return bRes;
}

bool CUnzipper::SetFileModTime(LPCTSTR szFilePath, DWORD dwDosDate)
{
	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (!hFile)
		return FALSE;
	
	FILETIME ftm, ftLocal, ftCreate, ftLastAcc, ftLastWrite;

	bool bRes = (GetFileTime(hFile, &ftCreate, &ftLastAcc, &ftLastWrite) == TRUE);

	if (bRes)
		bRes = (TRUE == DosDateTimeToFileTime((WORD)(dwDosDate >> 16), (WORD)dwDosDate, &ftLocal));

	if (bRes)
		bRes = (TRUE == LocalFileTimeToFileTime(&ftLocal, &ftm));

	if (bRes)
		bRes = (TRUE == SetFileTime(hFile, &ftm, &ftLastAcc, &ftm));

	CloseHandle(hFile);

	return bRes;
}

