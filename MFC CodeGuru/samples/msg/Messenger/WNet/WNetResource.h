// WNetResource.h: interface for the CWNetResource class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WNET_RESOURCE_H
#define WNET_RESOURCE_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWNetResource : public NETRESOURCE
{
public:
	CWNetResource();
	CWNetResource(NETRESOURCE &x);
	~CWNetResource();

	// variable lpRemoteName; 
    LPTSTR RemoteName();

	// variable dwType
	bool IsAny();
	bool IsDisk();
	bool IsPrint();
	bool IsReserved();
	bool IsUnknown();
	
	// variable dwDisplayType
	bool IsDomain();
	bool IsGeneric();
	bool IsServer();
	bool IsShare();
	bool IsFile();
	bool IsGroup();
	bool IsNetwork();
	bool IsRoot();
	bool IsShareAdmin();
	bool IsDirectory();
	bool IsTree();
	bool IsNdsContainer();

	// variable dwUsage 
	bool IsConnectable();
	bool IsContainer();
	bool IsNoLocalDevice();
	bool IsSibling();
	bool IsAttached();
	bool IsAll();

};


#endif // !defined(AFX_WNETRESOURCE_H__3987ADD9_E657_11D1_B802_0060084C3BF4__INCLUDED_)
