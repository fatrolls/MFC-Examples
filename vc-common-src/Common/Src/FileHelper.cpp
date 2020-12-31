/*
 * Copyright Bruce Liang (ldcsaa@gmail.com)
 *
 * Version	: 2.3.2
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Porject	: https://code.google.com/p/ldcsaa
 * Bolg		: http://www.cnblogs.com/ldcsaa
 * WeiBo	: http://weibo.com/u/1402935851
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "stdafx.h"
#include "FileHelper.h"

#ifndef VC_EXTRALEAN
	#define VC_EXTRALEAN			// 从 Windows 头中排除极少使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef _WIN32_WCE
	#ifndef _WIN32_WINNT			// 允许使用特定于 Windows NT 4 或更高版本的功能。
		#define _WIN32_WINNT 0x0500	// 将此更改为针对于 Windows 2000 或更高版本的合适的值。
	#endif
#endif

#ifndef _AFX
	#include <windows.h>
	#include <tchar.h>
	#include <atlstr.h>
#endif

#include <atlconv.h>
#include <atltime.h>
#include <atlfile.h>

#include <shellapi.h>
#include <Shlobj.h>

using namespace ATL;

#ifndef _WIN32_WCE
	#include <atlpath.h>
	using namespace ATLPath;
#else
	#pragma comment(lib, "Ceshell.lib")

	BOOL FileExists(LPCTSTR pszFile)
	{
		BOOL bExists = ::GetFileAttributes(pszFile) != INVALID_FILE_ATTRIBUTES;
		if(!bExists)
		{
			DWORD dwError	= ::GetLastError();
			bExists			= dwError != ERROR_FILE_NOT_FOUND && dwError != ERROR_PATH_NOT_FOUND;
		}

		return bExists;
	}
#endif

BOOL OperateDirFile(const TCHAR * pszSrc, const TCHAR * pszDest, int wFunc)
{
	TCHAR src[MAX_PATH]		= {0};
	TCHAR dest[MAX_PATH]	= {0};
	if(pszSrc)
		_tcscpy(src, pszSrc);
	if(pszDest)
		_tcscpy(dest, pszDest);

	SHFILEOPSTRUCT   filestruct;   
	filestruct.wFunc	= wFunc;
	filestruct.pFrom	= src;
	filestruct.pTo		= dest; 
	filestruct.fFlags	= FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_SILENT | FOF_NOERRORUI;

	return (SHFileOperation(&filestruct) == 0) ? TRUE : FALSE;
}

BOOL FHCopyFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists)
{
	if(bFailIfExists && ::FileExists(pszDestFile))
		return FALSE;

	return OperateDirFile(pszSrcFile, pszDestFile, FO_COPY);
}

BOOL FHMoveFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists)
{
	if(bFailIfExists && ::FileExists(pszDestFile))
		return FALSE;

	return OperateDirFile(pszSrcFile, pszDestFile, FO_MOVE);
}

BOOL FHRenameFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists)
{
	if(bFailIfExists && ::FileExists(pszDestFile))
		return FALSE;

	return OperateDirFile(pszSrcFile, pszDestFile, FO_RENAME);
}

BOOL FHDeleteFile(LPCTSTR pszFile, BOOL bSucceedIfNotExists)
{
	if(bSucceedIfNotExists && !::FileExists(pszFile))
		return TRUE;

	return OperateDirFile(pszFile, NULL, FO_DELETE);
}

#ifndef _WIN32_WCE
/**********************************************************************
* Function......: CreateShortcut
* Parameters....: lpszFileName - string that specifies a valid file name
*          lpszDesc - string that specifies a description for a 
                             shortcut
*          lpszShortcutPath - string that specifies a path and 
                                     file name of a shortcut
* Returns.......: S_OK on success, error code on failure
* Description...: Creates a Shell link object (shortcut)
**********************************************************************/
HRESULT CreateShortcut(LPCTSTR lpszFileName,  LPCTSTR lpszDesc,  LPCTSTR lpszShortcutPath, LPCTSTR lpszWorkDir, LPCTSTR pszArguments)
{
	USES_CONVERSION;

    HRESULT hRes = E_FAIL;

    LPTSTR lpszFilePart;    
    TCHAR szPath[MAX_PATH];    
	CComPtr<IShellLink> ipShellLink;

	if(::GetFullPathName(lpszFileName, MAX_PATH, szPath, &lpszFilePart))
		if(SUCCEEDED(hRes = ipShellLink.CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER)))
			if(SUCCEEDED(hRes = ipShellLink->SetPath(szPath)))
				if(SUCCEEDED(hRes = ipShellLink->SetDescription(lpszDesc)))
					if(SUCCEEDED(hRes = ipShellLink->SetWorkingDirectory(lpszWorkDir)))
						if(!pszArguments || SUCCEEDED(hRes = ipShellLink->SetArguments(pszArguments)))
						{
							CComQIPtr<IPersistFile> ipPersistFile(ipShellLink);
							hRes = ipPersistFile->Save(T2W((LPTSTR)lpszShortcutPath), TRUE);
						}

    return hRes;
}
#endif

BOOL CycleMoveDir(LPCTSTR pszSrc, LPCTSTR pszDest, LPCTSTR pszIgnoreFile)
{
	if(!::FileExists(pszDest) && !::CreateDirectory(pszDest, NULL))
		return FALSE;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR pszFind[MAX_PATH]			= {0};
	TCHAR newfilename[MAX_PATH]		= {0};
	TCHAR pszDestSubDir[MAX_PATH]	= {0};
	TCHAR pszRoot[MAX_PATH]			= {0};

	_tcscpy(pszRoot, pszSrc);

	if(pszRoot[_tcslen(pszRoot) - 1] != _T('\\'))
	{
		_stprintf(pszFind,_T("%s\\*.*"),pszRoot);
		_tcscat(pszRoot, _T("\\"));
	}
	else
		_stprintf(pszFind,_T("%s*.*"),pszRoot);


	hFind = ::FindFirstFile(pszFind, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	CString strIgnoreFile(pszIgnoreFile);
	if(strIgnoreFile.GetLength() > 0 && strIgnoreFile[strIgnoreFile.GetLength() - 1] != '|')
		strIgnoreFile += '|';
	strIgnoreFile.MakeLower();

	BOOL bIsOK					= TRUE;
	TCHAR filename[MAX_PATH]	= {0};

	do{
		if(_tcsicmp(FindFileData.cFileName, _T(".")) == 0 || _tcsicmp(FindFileData.cFileName, _T("..")) == 0)
			continue;
		if(strIgnoreFile.GetLength() > 0)
		{
			_stprintf(filename,_T("%s|"), CString(FindFileData.cFileName).MakeLower());
			if(strIgnoreFile.Find(filename) != -1)
				continue;
		}

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_stprintf(pszFind,_T("%s%s\\"),pszRoot,FindFileData.cFileName);
			_stprintf(pszDestSubDir, _T("%s\\%s\\"), pszDest, FindFileData.cFileName);

			if(::CreateDirectory(pszDestSubDir, NULL))
			{
				if(CycleMoveDir(pszFind, pszDestSubDir, _T("")))
					bIsOK = FHDeleteFile(pszFind);
				else
					bIsOK = FALSE;
			}
			else
				bIsOK = FALSE;
		}
		else
		{
			_stprintf(filename,_T("%s%s"), pszRoot, FindFileData.cFileName);
			_stprintf(newfilename, _T("%s\\%s"), pszDest, FindFileData.cFileName);
			
			bIsOK = FHMoveFile(filename, newfilename);
		}

		if(!bIsOK)
			break;

	} while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);

	if(bIsOK)
		bIsOK = FHDeleteFile(pszSrc);

	return bIsOK;
}

BOOL CycleMoveDirWithCheck(LPCTSTR pszSrc, LPCTSTR pszDest, LPCTSTR pszIgnoreFile)
{
	if(!::FileExists(pszDest) && !::CreateDirectory(pszDest, NULL))
		return FALSE;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR pszFind[MAX_PATH]			= {0};
	TCHAR newfilename[MAX_PATH]		= {0};
	TCHAR pszDestSubDir[MAX_PATH]	= {0};
	TCHAR pszRoot[MAX_PATH]			= {0};

	_tcscpy(pszRoot, pszSrc);

	if(pszRoot[_tcslen(pszRoot) - 1] != _T('\\'))
	{
		_stprintf(pszFind,_T("%s\\*.*"),pszRoot);
		_tcscat(pszRoot, _T("\\"));
	}
	else
		_stprintf(pszFind,_T("%s*.*"),pszRoot);


	hFind = ::FindFirstFile(pszFind, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	CString strIgnoreFile(pszIgnoreFile);
	if(strIgnoreFile.GetLength() > 0 && strIgnoreFile[strIgnoreFile.GetLength() - 1] != '|')
		strIgnoreFile += '|';
	strIgnoreFile.MakeLower();

	BOOL bIsOK					= TRUE;
	TCHAR filename[MAX_PATH]	= {0};

	do{
		if(_tcsicmp(FindFileData.cFileName, _T(".")) == 0 || _tcsicmp(FindFileData.cFileName, _T("..")) == 0)
			continue;
		if(strIgnoreFile.GetLength() > 0)
		{
			_stprintf(filename,_T("%s|"), CString(FindFileData.cFileName).MakeLower());
			if(strIgnoreFile.Find(filename) != -1)
				continue;
		}

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_stprintf(pszFind,_T("%s%s\\"), pszRoot,FindFileData.cFileName);
			_stprintf(pszDestSubDir, _T("%s\\%s\\"), pszDest, FindFileData.cFileName);

			if(::CreateDirectory(pszDestSubDir, NULL))
			{
				if(CycleMoveDirWithCheck(pszFind, pszDestSubDir, _T("")))
					bIsOK = FHDeleteFile(pszFind);
				else
					bIsOK = FALSE;
			}
			else
				bIsOK = FALSE;
		}
		else
		{
			_stprintf(filename,_T("%s%s"),pszRoot,FindFileData.cFileName);
			_stprintf(newfilename, _T("%s\\%s"), pszDest, FindFileData.cFileName);

			if(::FileExists(newfilename) && !FHDeleteFile(newfilename))
			{
				// 改变当前文件名，保证文件移动尽可能成功
				SYSTEMTIME st;
				::GetLocalTime(&st);
				CString strBKFileName;
				strBKFileName.Format(_T("%s.%04d%02d%02d%02d%02d%02d%03d.bk"), 
									 newfilename, st.wYear, st.wMonth, st.wDay, 
									 st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

				bIsOK = FHMoveFile(newfilename, strBKFileName);
			}

			if(bIsOK)
				bIsOK = FHMoveFile(filename, newfilename);
		}

		if(!bIsOK)
			break;

	} while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);

	if(bIsOK)
		bIsOK = FHDeleteFile(pszSrc);

	return bIsOK;
}

BOOL CycleRenameDir(LPCTSTR pszSrc, LPCTSTR pszDest)
{
	if(!::FileExists(pszDest) && !::CreateDirectory(pszDest, NULL))
		return FALSE;

	WIN32_FIND_DATA FindFileData;

	TCHAR pszFind[MAX_PATH]			= {0};
	TCHAR newfilename[MAX_PATH]		= {0};
	TCHAR pszDestSubDir[MAX_PATH]	= {0};
	TCHAR pszRoot[MAX_PATH]			= {0};

	_tcscpy(pszRoot, pszSrc);

	if(pszRoot[_tcslen(pszRoot) - 1] != _T('\\'))
	{
		_stprintf(pszFind,_T("%s\\*.*"),pszRoot);
		_tcscat(pszRoot, _T("\\"));
	}
	else
	{
		_stprintf(pszFind,_T("%s*.*"),pszRoot);
	}


	HANDLE hFind = ::FindFirstFile(pszFind, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	BOOL bIsOK					= TRUE;
	TCHAR filename[MAX_PATH]	= {0};

	do{
		if(_tcsicmp(FindFileData.cFileName, _T(".")) == 0 || _tcsicmp(FindFileData.cFileName, _T("..")) == 0)
			continue;
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_stprintf(pszFind,_T("%s%s\\"),pszRoot,FindFileData.cFileName);
			_stprintf(pszDestSubDir, _T("%s\\%s\\"), pszDest, FindFileData.cFileName);
			
			if(::CreateDirectory(pszDestSubDir, NULL))
			{
				if(CycleRenameDir(pszFind, pszDestSubDir))
					bIsOK = FHDeleteFile(pszFind);
				else
					bIsOK = FALSE;
			}
			else
				bIsOK = FALSE;
		}
		else
		{
			_stprintf(filename,_T("%s%s"),pszRoot,FindFileData.cFileName);
			_stprintf(newfilename, _T("%s\\%s"), pszDest, FindFileData.cFileName);

			bIsOK = FHMoveFile(filename, newfilename);
		}

		if(!bIsOK)
			break;

	} while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);

	if(bIsOK)
		bIsOK = FHDeleteFile(pszSrc);

	return bIsOK;
}

BOOL CycleDeleteDir(LPCTSTR pszSrc)
{
	WIN32_FIND_DATA FindFileData;

	TCHAR pszFind[MAX_PATH]			= {0};
	TCHAR newfilename[MAX_PATH]		= {0};
	TCHAR pszRoot[MAX_PATH]			= {0};

	_tcscpy(pszRoot, pszSrc);

	if(pszRoot[_tcslen(pszRoot) - 1] != _T('\\'))
	{
		_stprintf(pszFind,_T("%s\\*.*"),pszRoot);
		_tcscat(pszRoot, _T("\\"));
	}
	else
	{
		_stprintf(pszFind,_T("%s*.*"),pszRoot);
	}


	HANDLE hFind = ::FindFirstFile(pszFind, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	BOOL bIsOK					= TRUE;
	TCHAR filename[MAX_PATH]	= {0};

	do{
		if(_tcsicmp(FindFileData.cFileName, _T(".")) == 0 || _tcsicmp(FindFileData.cFileName, _T("..")) == 0)
			continue;
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_stprintf(pszFind,_T("%s%s\\"),pszRoot,FindFileData.cFileName);

			if(CycleDeleteDir(pszFind))
				bIsOK = FHDeleteFile(pszFind);
			else
				bIsOK = FALSE;
		}
		else
		{
			_stprintf(filename,_T("%s%s"),pszRoot,FindFileData.cFileName);

			bIsOK = FHDeleteFile(filename);
		}

		if(!bIsOK)
			break;

	} while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);

	if(bIsOK)
		bIsOK = FHDeleteFile(pszRoot);

	return bIsOK;
}

BOOL CycleCopyDir(LPCTSTR pszSrc, LPCTSTR pszDest)
{
	if(!::FileExists(pszDest) && !::CreateDirectory(pszDest, NULL))
		return FALSE;

	WIN32_FIND_DATA FindFileData;

	TCHAR pszFind[MAX_PATH]			= {0};
	TCHAR newfilename[MAX_PATH]		= {0};
	TCHAR pszDestSubDir[MAX_PATH]	= {0};
	TCHAR pszRoot[MAX_PATH]			= {0};

	_tcscpy(pszRoot, pszSrc);

	if(pszRoot[_tcslen(pszRoot) - 1] != _T('\\'))
	{
		_stprintf(pszFind,_T("%s\\*.*"),pszRoot);
		_tcscat(pszRoot, _T("\\"));
	}
	else
	{
		_stprintf(pszFind,_T("%s*.*"),pszRoot);
	}


	HANDLE hFind = ::FindFirstFile(pszFind, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	BOOL bIsOK					= TRUE;
	TCHAR filename[MAX_PATH]	= {0};

	do{
		if(_tcsicmp(FindFileData.cFileName, _T(".")) == 0 || _tcsicmp(FindFileData.cFileName, _T("..")) == 0)
			continue;
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_stprintf(pszFind,_T("%s%s\\"),pszRoot,FindFileData.cFileName);
			_stprintf(pszDestSubDir, _T("%s\\%s\\"), pszDest, FindFileData.cFileName);

			if(::CreateDirectory(pszDestSubDir, NULL))
				bIsOK = CycleCopyDir(pszFind, pszDestSubDir);
			else
				bIsOK = FALSE;
		}
		else
		{
			_stprintf(filename,_T("%s%s"), pszRoot, FindFileData.cFileName);
			_stprintf(newfilename, _T("%s\\%s"), pszDest, FindFileData.cFileName);

			bIsOK = FHCopyFile(filename, newfilename);
		}

		if(!bIsOK)
			break;

	} while(::FindNextFile(hFind, &FindFileData));

	::FindClose(hFind);

	return TRUE;
}

BOOL RenameDir(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir)
{
	if(bClearDestDir && ::FileExists(pszDest)) 
		RemoveAllDir(pszDest);

#ifndef _WIN32_WCE
	BOOL bRet = (_trename(pszSrc, pszDest) == NO_ERROR) ? TRUE : FALSE;
#else
	BOOL bRet = FHRenameFile(pszSrc, pszDest, TRUE);
#endif

	if(!bRet)
	{
		if(!::FileExists(pszDest))
			bRet = FHMoveFile(pszSrc, pszDest);
		else
		{
			CString strSrc = pszSrc;
			strSrc.TrimRight(_T("\\/ "));
			strSrc += _T("\\*.*");
			bRet = FHMoveFile(strSrc, pszDest);
			if(bRet)
				FHDeleteFile(pszSrc);
		}
	}

	if(!bRet)
		bRet = CycleRenameDir(pszSrc, pszDest);

	return bRet;
}

BOOL MoveDirWithCheck(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir)
{
	if(bClearDestDir && ::FileExists(pszDest)) 
		RemoveAllDir(pszDest);

	BOOL bRet = FALSE;
	if(!::FileExists(pszDest))
		bRet = FHMoveFile(pszSrc, pszDest);
	else
	{
		CString strSrc = pszSrc;
		strSrc.TrimRight(_T("\\/ "));
		strSrc += _T("\\*.*");
		bRet = FHMoveFile(strSrc, pszDest);
		if(bRet)
			FHDeleteFile(pszSrc);
	}

	if(!bRet)
		bRet = CycleMoveDirWithCheck(pszSrc, pszDest, NULL);

	return bRet;
}

BOOL CopyAllDir(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir)
{
	if(bClearDestDir && ::FileExists(pszDest)) 
		RemoveAllDir(pszDest);

	BOOL bRet = FALSE;
	if(!::FileExists(pszDest))
		bRet = FHCopyFile(pszSrc, pszDest);
	else
	{
		CString strSrc = pszSrc;
		strSrc.TrimRight(_T("\\/ "));
		strSrc += _T("\\*.*");
		bRet = FHCopyFile(strSrc, pszDest);
	}

	if(!bRet)
		bRet = CycleCopyDir(pszSrc, pszDest);

	return bRet;
}

BOOL RemoveAllDir(LPCTSTR pszPath)
{
	if(!FHDeleteFile(pszPath))
		return CycleDeleteDir(pszPath);
	else
		return TRUE;
}

BOOL GetParentPath(const CString& strPath, CString& strParentPath)
{
	CString strTemp = strPath;
	strTemp.Trim(_T("\\/ "));

	int iPos = strTemp.ReverseFind('\\');
	if(iPos == -1)
		iPos = strTemp.ReverseFind('/');
	if(iPos != -1)
		strParentPath = strTemp.Left(iPos);

	return (iPos != -1);
}

BOOL GetFileNameFromPath(const CString& strPath, CString& strFileName, BOOL isIncludeExternName, const CString& strExternName)
{
	CString strRealPath = strPath;
	strRealPath.Trim();

	int pos1	= strRealPath.ReverseFind('\\');
	int pos2	= strRealPath.ReverseFind('/');
	int begin	= max(pos1, pos2) + 1;

	strFileName	= strRealPath.Right(strRealPath.GetLength() - begin);
	int len		= strFileName.GetLength();
	if(len > 0 && !isIncludeExternName)
	{
		CString strRealExternName = strExternName;
		strRealExternName.Trim();
		if(strRealExternName.GetLength() > 0)
		{
			if(strRealExternName.GetAt(0) != '.')
				strRealExternName.Insert(0, '.');

			int exlen = strRealExternName.GetLength();
			if(len >= exlen)
			{
				if(strFileName.Right(exlen).CompareNoCase(strRealExternName) == 0)
					strFileName = strFileName.Left(len - exlen);
			}
		}
		else
		{
			int dot = strFileName.ReverseFind('.');
			if(dot != -1)
				strFileName = strFileName.Left(dot);
		}
	}

	return !strFileName.IsEmpty();
}

BOOL WaitFlagFile(LPCTSTR pszFile, DWORD dwWaitTime, BOOL bDeleteFlagFile, DWORD dwCheckInterval)
{
	BOOL bRet = FALSE;

	BOOL isInfine = (dwWaitTime == INFINITE);
	DWORD dwBeginTime = ::GetTickCount();
	while(isInfine || ::GetTickCount() - dwBeginTime < dwWaitTime)
	{
		CAtlFile f;
		if(SUCCEEDED(f.Create(pszFile, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING)))
		{
			if(bDeleteFlagFile)
				FHDeleteFile(pszFile);
			bRet = TRUE;
			break;
		}
		::Sleep(dwCheckInterval);
	}
	return bRet;
}
