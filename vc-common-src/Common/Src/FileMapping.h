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

#include "GeneralHelper.h"

class CFileMapping
{
public:
	CFileMapping(	
					LPCTSTR lpszName,
					DWORD dwMaximumSizeLow,
					DWORD dwMaximumSizeHigh							= 0,
					HANDLE hFile									= INVALID_HANDLE_VALUE,
					DWORD flProtect									= PAGE_READWRITE,
					LPSECURITY_ATTRIBUTES lpFileMappingAttributes	= NULL
				)
	{
		m_hMap	= ::CreateFileMapping	(
											hFile,
											lpFileMappingAttributes,
											flProtect,
											dwMaximumSizeHigh,
											dwMaximumSizeLow,
											lpszName
										);
		ASSERT(IsValid());
	}

	~CFileMapping()
	{
		if(IsValid())
			VERIFY(::CloseHandle(m_hMap));
	}

	LPVOID ViewMap	(
						DWORD dwNumberOfBytesToMap,
						DWORD dwFileOffsetLow,
						DWORD dwFileOffsetHigh	= 0,
						DWORD dwDesiredAccess	= FILE_MAP_ALL_ACCESS
					)
	{
		return ::MapViewOfFile	(
									m_hMap,
									dwDesiredAccess,
									dwFileOffsetHigh,
									dwFileOffsetLow,
									dwNumberOfBytesToMap
								);
	}

	BOOL UnViewMap(LPCVOID lpBaseAddress)
	{
		return ::UnmapViewOfFile(lpBaseAddress);
	}

	operator HANDLE	()	{return m_hMap;}
	BOOL IsValid	()	{return m_hMap != NULL;}

private:
	HANDLE m_hMap;
};

class CShareMemory
{
public:
	CShareMemory(DWORD dwSize, LPCTSTR lpszName = NULL)
	: m_fm(lpszName, dwSize)
	{
		ASSERT(dwSize > 0);
	}

	~CShareMemory()
	{
		for(set<ULONG_PTR>::const_iterator it = m_set.begin(); it != m_set.end(); ++it)
		{
			LPVOID pV = (LPVOID)*it;
			ASSERT(pV);

			m_fm.UnViewMap(pV);
		}

		m_set.clear();
	}

	LPVOID Alloc(DWORD dwNumberOfBytesToMap, DWORD dwFileOffsetLow)
	{
		LPVOID pV = m_fm.ViewMap(dwNumberOfBytesToMap, dwFileOffsetLow);

		if(pV) m_set.insert((ULONG_PTR)pV);

		ASSERT(pV);
		return pV;
	}

	BOOL Free(LPCVOID lpBaseAddress)
	{
		ASSERT(lpBaseAddress);

		set<ULONG_PTR>::iterator it = m_set.find((ULONG_PTR)lpBaseAddress);

		if(it != m_set.end())
			m_set.erase(it);

		return m_fm.UnViewMap(lpBaseAddress);
	}

private:

	CFileMapping	m_fm;
	set<ULONG_PTR>	m_set;

	DECLARE_PRIVATE_COPY_CONSTRUCTOR(CShareMemory)
};
