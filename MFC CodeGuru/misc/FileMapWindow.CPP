/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File FileMapWindow.cpp
// class CWizFileMapWindow
//
// 08/09/1996 14:00                             Author: Poul, Hadas & Oren
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "FileMapWindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////
// class CWizFileMapWindow
#ifdef _DEBUG
typedef CWizFileROFileMapping<CWizFileMapCritSectLocker> VOIDMAP;
typedef CWizTypedFileROFileMapping<CWizFileMapCritSectLocker, double> DOUBLEMAP;
static double Foo()
{
	 
	VOIDMAP	Map(_T("poul.txt"));
	VOIDMAP::Window w = 
		Map.Get(10,40);
	const void *pn = w.GetPtr (20,4);
	int n = *((int *)pn);

	DOUBLEMAP Map1(_T("poul.dat"));
	DOUBLEMAP::Wnd w1 = Map1.Get(0,10);
	double d = w1[3];

	return n*d;
}
#endif
