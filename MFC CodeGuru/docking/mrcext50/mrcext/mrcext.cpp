// MRCEXT: Micro Focus Extension DLL for MFC 2.1+
// Copyright (C)1994-5	Micro Focus Inc, 2465 East Bayshore Rd, Palo Alto, CA 94303.
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation. In addition, you may also charge for any
//  application	using MRCEXT, and are under no obligation to supply source
//  code. You must accredit Micro Focus Inc in the "About Box", or banner
//  of your application. 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should also have received a copy of the GNU General Public License with this
//  software, also indicating additional rights you have when using MRCEXT.  
//
//
// MRCEXT.CPP
// $Date:   27 Jun 1997 12:13:36  $
// $Revision:   1.1  $
// $Author:   SJR  $
// mrcext.cpp : Defines the initialization routines for the DLL.
//

#include "mrcstafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE mrcextDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
        if (dwReason == DLL_PROCESS_ATTACH)
        {
                TRACE0("MRCEXT.DLL Initializing! - (C)1995 Micro Focus Ltd\n");

                // Extension DLL one-time initialization
                AfxInitExtensionModule(mrcextDLL, hInstance);

                // Insert this DLL into the resource chain
                new CDynLinkLibrary(mrcextDLL);
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
                TRACE0("MRCEXT.DLL Terminating!\n");
                AfxTermExtensionModule(mrcextDLL);
        }
        return 1;   // ok
}

static CMapPtrToPtr ObjExtDataMap;


void * AllocObjExtData(CObject * pObj, int cBytes)
{
	void * pVoid;
	ASSERT(ObjExtDataMap.Lookup(pObj, pVoid) == FALSE);
	pVoid = new BYTE[cBytes];
	ObjExtDataMap.SetAt(pObj, pVoid);
	return pVoid;
}


void * GetObjExtDataPtr(CObject * pObj)
{
	void * pVoid;
	VERIFY(ObjExtDataMap.Lookup(pObj, pVoid));
	return pVoid;	
}

void DeleteObjExtData(CObject * pObj)
{
	void * pVoid;
	VERIFY(ObjExtDataMap.Lookup(pObj, pVoid));
	delete[] pVoid;
}
