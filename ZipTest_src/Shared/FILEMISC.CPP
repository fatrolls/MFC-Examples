#include "stdafx.h"
#include "filemisc.h"
//#include "timemisc.h"

#include <sys/utime.h>
#include <sys/stat.h>
#include <direct.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// private helpers
void ProcessMsgLoop()
{
	MSG msg;

	while (::PeekMessage((LPMSG) &msg, NULL, 0, 0, PM_REMOVE))
	{
		if (IsDialogMessage(msg.hwnd, (LPMSG)&msg))
		{
			// do nothing - its already been done
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void TerminatePath(CString& sPath)
{
	sPath.TrimRight();

	if (sPath.ReverseFind('\\') != (sPath.GetLength() - 1))
		sPath += '\\';
}

void UnterminatePath(CString& sPath)
{
	sPath.TrimRight();

	int len = sPath.GetLength();

	if (sPath.ReverseFind('\\') == (len - 1))
		sPath = sPath.Left(len - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

time_t GetLastModified(const char* szPath)
{
	struct _stat st;

	if (_stat(szPath, &st) != 0)
		return 0;

	// files only
	if ((st.st_mode & _S_IFDIR) == _S_IFDIR)
		return 0;

	return st.st_mtime;
}

bool GetLastModified(const char* szPath, SYSTEMTIME& sysTime, bool bLocalTime)
{
	ZeroMemory(&sysTime, sizeof(SYSTEMTIME));

	DWORD dwAttr = ::GetFileAttributes(szPath);

	// files only
	if (dwAttr == 0xFFFFFFFF)
		return false;

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile((LPTSTR)szPath, &findFileData);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	FindClose(hFind);

	FILETIME ft = findFileData.ftLastWriteTime;

	if (bLocalTime)
		FileTimeToLocalFileTime(&findFileData.ftLastWriteTime, &ft);

	FileTimeToSystemTime(&ft, &sysTime);
	return true;
}

bool ResetLastModified(const char* szPath)
{
	::SetFileAttributes(szPath, FILE_ATTRIBUTE_NORMAL);

	return (_utime(szPath, NULL) == 0);
}

bool DeleteFolderContents(const char* szFolder, BOOL bIncludeSubFolders, const char* szFileMask, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	// if the dir does not exists just return
	DWORD dwAttr = GetFileAttributes(szFolder);

	if (dwAttr == 0xffffffff || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return false;

	// if a file mask has been specified with subfolders we need to do 2 passes on each folder, 
	// one for the files and one for the sub folders
	int nPasses = (bIncludeSubFolders && (szFileMask && lstrlen(szFileMask))) ? 2 : 1;
		
	bool bResult = true;
	bool bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);

	for (int nPass = 0; !bStopped && nPass < nPasses; nPass++)
	{
		CString sSearchSpec(szFolder), sMask(szFileMask);

		if (sMask.IsEmpty() || nPass == 1) // (nPass == 1) == 2nd pass (for folders)
			sMask = "*.*";

		TerminatePath(sSearchSpec);
		sSearchSpec += sMask;

		WIN32_FIND_DATA finfo;
		HANDLE hSearch = NULL;

		if ((hSearch = FindFirstFile(sSearchSpec, &finfo)) != INVALID_HANDLE_VALUE) 
		{
			do 
			{
				if (bProcessMsgLoop)
					ProcessMsgLoop();

				if (finfo.cFileName[0] != '.') 
				{
					CString sItem(szFolder);
					sItem += "\\";
					sItem += finfo.cFileName;

					if (finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if (bIncludeSubFolders && (nPass == 1 || nPasses == 1))
						{
							if (DeleteFolderContents(sItem, TRUE, szFileMask, hTerminate, bProcessMsgLoop))
							{
								if (!szFileMask || !lstrlen(szFileMask))
									bResult = (RemoveDirectory(sItem) == TRUE);
							}
						}
					}
					else 
						bResult = (DeleteFile(sItem) == TRUE);
				}

				bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);
			} 
			while (!bStopped && bResult && FindNextFile(hSearch, &finfo));
			
			FindClose(hSearch);
		}
	}

	return (!bStopped && bResult);
}

bool RemoveFolder(const char* szFolder, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	// if the dir does not exists just return
	DWORD dwAttr = GetFileAttributes(szFolder);

	if (dwAttr == 0xffffffff || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return true;

	if (DeleteFolderContents(szFolder, TRUE, NULL, hTerminate, bProcessMsgLoop))
	{
		::SetFileAttributes(szFolder, FILE_ATTRIBUTE_NORMAL);
		return (RemoveDirectory(szFolder) == TRUE);
	}

	return false;
}

double GetFolderSize(const char* szFolder, BOOL bIncludeSubFolders, const char* szFileMask, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	// if the dir does not exists just return
	DWORD dwAttr = GetFileAttributes(szFolder);

	if (dwAttr == 0xffffffff || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return 0;
	
	double dSize = 0;

	WIN32_FIND_DATA finfo;
	CString sSearchSpec(szFolder), sFileMask(szFileMask);

	if (sFileMask.IsEmpty())
		sFileMask = "*.*";

	TerminatePath(sSearchSpec);
	sSearchSpec += sFileMask;

	BOOL bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);
	HANDLE h = NULL;
		
	if (!bStopped && (h = FindFirstFile(sSearchSpec, &finfo)) != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			if (bProcessMsgLoop)
				ProcessMsgLoop();

			if (finfo.cFileName[0] != '.') 
			{
				if (finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bIncludeSubFolders)
					{
						CString sSubFolder(szFolder);
						sSubFolder += "\\";
						sSubFolder += finfo.cFileName;
						
						dSize += GetFolderSize(sSubFolder, TRUE, sFileMask, hTerminate, bProcessMsgLoop);
					}
				}
				else 
					dSize += (finfo.nFileSizeHigh * ((double)MAXDWORD + 1)) + finfo.nFileSizeLow;
			}

			bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);
		}
		while (!bStopped && FindNextFile(h, &finfo));
		
		FindClose(h);
	} 

	return bStopped ? -1 : dSize;
}

bool CreateFolder(const char* szFolder)
{
	// start from the highest level folder working to the lowest
	CString sFolder, sRemaining(szFolder);
	UnterminatePath(sRemaining);

	bool bDone = false;
	bool bResult = true;

	// pull off the :\ or \\ start
	int nFind = sRemaining.Find(":\\");

	if (nFind != -1)
	{
		sFolder += sRemaining.Left(nFind + 2);
		sRemaining = sRemaining.Mid(nFind + 2);
	}
	else
	{
		nFind = sRemaining.Find("\\\\");
		
		if (nFind != -1)
		{
			sFolder += sRemaining.Left(nFind + 2);
			sRemaining = sRemaining.Mid(nFind + 2);
		}
	}

	while (!bDone && bResult)
	{
		nFind = sRemaining.Find('\\', 1);

		if (nFind == -1)
		{
			bDone = TRUE;
			sFolder += sRemaining;
		}
		else
		{
			sFolder += sRemaining.Left(nFind);
			sRemaining = sRemaining.Mid(nFind);
		}

		if (GetFileAttributes(sFolder) == 0xffffffff && mkdir(sFolder) != 0)
			bResult = false;
	}

	return bResult;
}

bool MoveFolder(const char* szSrcFolder, const char* szDestFolder, BOOL bIncludeSubFolders, const char* szFileMask, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	if (CopyFolder(szSrcFolder, szDestFolder, bIncludeSubFolders, szFileMask, hTerminate, bProcessMsgLoop))
	{
		// don't pass on hTerminate to ensure the operation completes
		DeleteFolderContents(szSrcFolder, bIncludeSubFolders, szFileMask, NULL, bProcessMsgLoop);

		return true;
	}

	return false;
}

bool CopyFolder(const char* szSrcFolder, const char* szDestFolder, BOOL bIncludeSubFolders, const char* szFileMask, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	if (!CreateFolder(szDestFolder))
		return false;

	if (GetFileAttributes(szSrcFolder) == 0xffffffff)
		return false;

	// if a file mask has been specified with subfolders we need to do 2 passes on each folder, 
	// one for the files and one for the sub folders
	int nPasses = (bIncludeSubFolders && (szFileMask && lstrlen(szFileMask))) ? 2 : 1;
		
	bool bResult = true;
	bool bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);

	for (int nPass = 0; !bStopped && nPass < nPasses; nPass++)
	{
		CString sSearchSpec(szSrcFolder), sMask(szFileMask);

		if (sMask.IsEmpty() || nPass == 1) // (nPass == 1) == 2nd pass (for folders)
			sMask = "*.*";

		TerminatePath(sSearchSpec);
		sSearchSpec += sMask;

		WIN32_FIND_DATA finfo;
		HANDLE hSearch = NULL;

		if ((hSearch = FindFirstFile(sSearchSpec, &finfo)) != INVALID_HANDLE_VALUE) 
		{
			do 
			{
				if (bProcessMsgLoop)
					ProcessMsgLoop();

				if (finfo.cFileName[0] != '.') 
				{
					CString sSource(szSrcFolder);
					sSource += "\\";
					sSource += finfo.cFileName;
					
					CString sDest(szDestFolder);
					sDest += "\\";
					sDest += finfo.cFileName;
					
					if (finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if ((nPass == 1 || nPasses == 1) && bIncludeSubFolders)
							bResult = CopyFolder(sSource, sDest, hTerminate);
					}
					else if (nPass == 0) // files 
					{
						bResult = (TRUE == CopyFile(sSource, sDest, FALSE));
					}
				}

				bStopped = (WaitForSingleObject(hTerminate, 0) == WAIT_OBJECT_0);
			}
			while (!bStopped && bResult && FindNextFile(hSearch, &finfo));
			
			FindClose(hSearch);
		} 
	}

	return (!bStopped && bResult);
}

bool MoveFolder(const char* szSrcFolder, const char* szDestFolder, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	return MoveFolder(szSrcFolder, szDestFolder, TRUE, NULL, hTerminate, bProcessMsgLoop);
}

bool CopyFolder(const char* szSrcFolder, const char* szDestFolder, HANDLE hTerminate, BOOL bProcessMsgLoop)
{
	return CopyFolder(szSrcFolder, szDestFolder, TRUE, NULL, hTerminate, bProcessMsgLoop);
}

double GetFileSize(const char* szPath)
{
	HANDLE hFile = ::CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwHighSize = 0;
		DWORD dwLowSize = ::GetFileSize(hFile, &dwHighSize);
		
		::CloseHandle(hFile);
		
		if (dwLowSize != INVALID_FILE_SIZE)
		{
			return (dwHighSize * ((double)MAXDWORD + 1) + dwLowSize);
		}
	}

	// else
	return 0;
}
