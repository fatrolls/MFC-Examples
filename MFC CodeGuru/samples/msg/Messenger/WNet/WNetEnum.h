// WNet.h: interface for the CWNetEnum class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WNET_ENUM_H
#define WNET_ENUM_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef WNET_RESOURCE_H
	#include "WNetResource.h"
#endif

class CWNetEnum  
{
public:
	CWNetEnum();
	virtual ~CWNetEnum();

public:
	DWORD Open(LPNETRESOURCE lpNetResource = NULL,DWORD dwDeep = 0);
	DWORD Close();

	DWORD Resource();
	CWNetResource operator [](int index);
	operator int();

private:
	void Clear();

private:
	DWORD m_dwNetResourceCount;
 	LPNETRESOURCE m_lpNetResource; // pointer to resource structure 
	HANDLE m_hEnum; // pointer to enumeration handle buffer 

	static DWORD m_dwAllocNetResource;
	static DWORD m_dwDeep;
};

#endif // !defined(AFX_WNET_H__3987ADD8_E657_11D1_B802_0060084C3BF4__INCLUDED_)
