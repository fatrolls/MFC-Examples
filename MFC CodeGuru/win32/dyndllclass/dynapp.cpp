#include <windows.h>

#include "dynclass.h"

int	main	(	void)
{

PFNCREATEMYCLASS	pfnCreateMyClass	=	NULL;
PFNDELETEMYCLASS	pfnDeleteMyClass	=	NULL;
PFNGETCLASSMETHOD	pfnGetClassMethod	=	NULL;
PMYCLASSMETHOD		pDoSomethingUseful	=	NULL;
CMyClass*			pMyClass			=	NULL;

HANDLE				hDll				=	INVALID_HANDLE_VALUE;

	hDll	=	LoadLibrary (	"dynclass.dll");

	if	(	INVALID_HANDLE_VALUE	==	hDll)
			return	(	-1);

	pfnCreateMyClass	=	( PFNCREATEMYCLASS)		GetProcAddress	(	hDll, 
																		"CreateMyClass"
																	);

	pfnDeleteMyClass	=	( PFNDELETEMYCLASS)		GetProcAddress	(	hDll, 
																		"DeleteMyClass"
																	);

	pfnGetClassMethod	=	( PFNGETCLASSMETHOD)	GetProcAddress	(	hDll, 
																		"GetClassMethod"
																	);

	if	(		pfnDeleteMyClass	
			&&	pfnCreateMyClass
			&&	pfnGetClassMethod
		)
		{
			// et voila - an instance of CMyClass!
			pMyClass	=	( pfnCreateMyClass)	();

			pDoSomethingUseful	=	( pfnGetClassMethod	());

			( pMyClass->*pDoSomethingUseful)();

			( pfnDeleteMyClass	(	pMyClass));
		}

	FreeLibrary	(	hDll);

	return	(	0);
}