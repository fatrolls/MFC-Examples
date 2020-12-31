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


// WNetResource.cpp: implementation of the CWNetResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WNetResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWNetResource::CWNetResource()
{

}

CWNetResource::CWNetResource(NETRESOURCE &x)
{
    dwScope = x.dwScope;
    dwType = x.dwType;
    dwDisplayType = x.dwDisplayType;
    dwUsage = x.dwUsage;
    lpLocalName = x.lpLocalName;
    lpRemoteName = x.lpRemoteName;
    lpComment = x.lpComment ;
    lpProvider = x.lpProvider;
}


CWNetResource::~CWNetResource()
{

}

// variable dwDisplayType
bool CWNetResource::IsDomain()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN;
}

bool CWNetResource::IsGeneric()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_GENERIC;
}

bool CWNetResource::IsServer()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_SERVER;
}

bool CWNetResource::IsShare()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_SHARE;
}

bool CWNetResource::IsFile()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_FILE;
}

bool CWNetResource::IsGroup()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_GROUP;
}

bool CWNetResource::IsNetwork()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_NETWORK;
}

bool CWNetResource::IsRoot()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_ROOT;
}

bool CWNetResource::IsShareAdmin()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_SHAREADMIN;
}

bool CWNetResource::IsDirectory()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_DIRECTORY;
}

bool CWNetResource::IsTree()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_TREE;
}

bool CWNetResource::IsNdsContainer()
{
	return dwDisplayType == RESOURCEDISPLAYTYPE_NDSCONTAINER;
}

// variable dwType

bool CWNetResource::IsAny()
{
	return dwType == RESOURCETYPE_ANY;
}

bool CWNetResource::IsDisk()
{
	return dwType == RESOURCETYPE_DISK;
}

bool CWNetResource::IsPrint()
{
	return dwType == RESOURCETYPE_PRINT;
}

bool CWNetResource::IsReserved()
{
	return dwType == RESOURCETYPE_RESERVED;
}

bool CWNetResource::IsUnknown()
{
	return dwType == RESOURCETYPE_UNKNOWN;
}

// variable dwUsage 

bool CWNetResource::IsConnectable()
{
	return dwUsage & RESOURCEUSAGE_CONNECTABLE ? true : false;
}

bool CWNetResource::IsContainer()
{
	return dwUsage & RESOURCEUSAGE_CONTAINER ? true : false;
}

bool CWNetResource::IsNoLocalDevice()
{
	return dwUsage & RESOURCEUSAGE_NOLOCALDEVICE ? true : false;
}

bool CWNetResource::IsSibling()
{
	return dwUsage & RESOURCEUSAGE_SIBLING ? true : false;
}

bool CWNetResource::IsAttached()
{
	return dwUsage & RESOURCEUSAGE_ATTACHED ? true : false;
}

bool CWNetResource::IsAll()
{
	return dwUsage & RESOURCEUSAGE_ALL ? true : false;
}

// variable lpRemoteName; 
LPTSTR CWNetResource::RemoteName()
{
	int len = lstrlen(lpRemoteName);

	while(len > 0)
	{
		if(lpRemoteName[len - 1] == '\\')
			break;
		len --;
	}

	return lpRemoteName + len;
}
