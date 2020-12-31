//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


// WNet.cpp: implementation of the CWNetEnum class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WNetEnum.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// Perform autolink here:
#define _DIBAUTOLIBNAME "mpr.lib "
#pragma message( "WNetEnum will automatically link with " _DIBAUTOLIBNAME )
#pragma comment(lib, _DIBAUTOLIBNAME)

DWORD CWNetEnum::m_dwAllocNetResource = 512;
DWORD CWNetEnum::m_dwDeep = 8;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWNetEnum::CWNetEnum()
{
	m_lpNetResource = NULL;
	m_hEnum = NULL;
	m_dwNetResourceCount = 0;
}

CWNetEnum::~CWNetEnum()
{
	Close();
}

void CWNetEnum::Clear()
{
	if(m_lpNetResource != NULL)
	{
		delete []m_lpNetResource;
	}

	m_lpNetResource = NULL;
	m_hEnum = NULL;
	m_dwNetResourceCount = 0;
}


DWORD CWNetEnum::Open(LPNETRESOURCE lpNetResource,DWORD dwDeep)
{
	DWORD dwRet = ERROR_NOT_CONTAINER;

	if(m_hEnum != NULL || 
		dwDeep >= m_dwDeep)
	{
		return dwRet;
	}

	m_lpNetResource = new NETRESOURCE[m_dwAllocNetResource];

	dwRet = WNetOpenEnum(RESOURCE_GLOBALNET,  // scope of enumeration 
				RESOURCETYPE_ANY,  // resource types to list 
				0, // resource usage to list 
				lpNetResource, // pointer to resource structure 
				&m_hEnum // pointer to enumeration handle buffer 
				);

	if(dwRet != NO_ERROR)
	{
		Clear();
	}
	return dwRet;
}


DWORD CWNetEnum::Close()
{
	DWORD dwRet = NO_ERROR;

	if(m_hEnum != NULL)
	{
		dwRet = WNetCloseEnum(m_hEnum);
	}
	Clear();

	return dwRet;
}


DWORD CWNetEnum::Resource()
{
	DWORD size;
	DWORD dwRet = ERROR_NO_MORE_ITEMS;

	if(m_hEnum == NULL)
	{
		return dwRet;
	}

	m_dwNetResourceCount = (DWORD)-1;
	size = sizeof(NETRESOURCE) * m_dwAllocNetResource;
	dwRet = WNetEnumResource(m_hEnum,&m_dwNetResourceCount,m_lpNetResource,&size);

	return dwRet;
}

CWNetResource CWNetEnum::operator [](int index)
{
	CWNetResource empty;
	if(index < 0 || index > (int)m_dwNetResourceCount)
		return empty;

	return CWNetResource(m_lpNetResource[index]);
}

CWNetEnum::operator int()
{
	return m_dwNetResourceCount;
}
