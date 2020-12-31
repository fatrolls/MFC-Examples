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
 
#pragma once

BOOL OperateDirFile(const TCHAR * pszSrc, const TCHAR * pszDest, int);

BOOL FHCopyFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists = FALSE);

BOOL FHMoveFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists = FALSE);

BOOL FHRenameFile(LPCTSTR pszSrcFile, LPCTSTR pszDestFile, BOOL bFailIfExists);

BOOL FHDeleteFile(LPCTSTR pszFile, BOOL bSucceedIfNotExists = TRUE);

#ifndef _WIN32_WCE
HRESULT CreateShortcut(LPCTSTR lpszFileName,  LPCTSTR lpszDesc, LPCTSTR lpszShortcutPath, LPCTSTR lpszWorkDir, LPCTSTR pszArguments = NULL);
#else
BOOL FileExists(LPCTSTR pszFile);
#endif

BOOL CycleMoveDir(LPCTSTR pszSrc, LPCTSTR pszDest, LPCTSTR pszIgnoreFile);

BOOL CycleMoveDirWithCheck(LPCTSTR pszSrc, LPCTSTR pszDest, LPCTSTR pszIgnoreFile);

BOOL CycleCopyDir(LPCTSTR pszSrc, LPCTSTR pszDest);

BOOL CopyAllDir(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir = TRUE);

BOOL RenameDir(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir = TRUE);

BOOL MoveDirWithCheck(LPCTSTR pszSrc, LPCTSTR pszDest, BOOL bClearDestDir = TRUE);

BOOL RemoveAllDir(LPCTSTR pszPath);

BOOL GetParentPath(const CString& strPath, CString& strParentPath);

BOOL GetFileNameFromPath(const CString& strPath, CString& strFileName, BOOL isIncludeExternName = TRUE, const CString& strExternName = _T(""));

BOOL CycleRenameDir(LPCTSTR pszSrc, LPCTSTR pszDest);

BOOL CycleDeleteDir(LPCTSTR pszSrc);

BOOL WaitFlagFile(LPCTSTR pszFile, DWORD dwWaitTime, BOOL bDeleteFlagFile = FALSE, DWORD dwCheckInterval = 5000);

class CFindFile
{
public:
	CFindFile	(LPCTSTR pszFile)		{m_hFind = ::FindFirstFile(pszFile, &m_fData);}
	~CFindFile	()						{if(IsValid()) ::FindClose(m_hFind);}

	BOOL Next	()						{return ::FindNextFile(m_hFind, &m_fData);}

	BOOL IsValid()						{return (m_hFind != INVALID_HANDLE_VALUE);}

	DWORD		GetFileAttributes()		{return m_fData.dwFileAttributes;}
	FILETIME	GetCreationTime()		{return m_fData.ftCreationTime;}
	FILETIME	GetLastAccessTime()		{return m_fData.ftLastAccessTime;}
	FILETIME	GetLastWriteTime()		{return m_fData.ftLastWriteTime;}
	DWORD		GetFileSizeHigh()		{return m_fData.nFileSizeHigh;}
	DWORD		GetFileSizeLow()		{return m_fData.nFileSizeLow;}
	TCHAR*		GetFileName()			{return m_fData.cFileName;}
#ifndef _WIN32_WCE
	DWORD		GetReserved0()			{return m_fData.dwReserved0;}
	DWORD		GetReserved1()			{return m_fData.dwReserved1;}
	TCHAR*		GetAlternateFileName()	{return m_fData.cAlternateFileName;}
#endif
#ifdef _MAC
    DWORD		GetFileType()			{return m_fData.dwFileType;}
    DWORD		GetCreatorType()		{return m_fData.dwCreatorType;}
    WORD		GetFinderFlags()		{return m_fData.wFinderFlags;}
#endif

private:
	WIN32_FIND_DATA m_fData;
	HANDLE m_hFind;
};
