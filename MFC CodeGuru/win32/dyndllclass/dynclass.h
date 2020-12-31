#ifndef __DYNCLASS_H
#define __DYNCLASS_H

#include <windows.h>

#ifdef _DLL // assume this is defined when we build the dll
#define _DYNLINK __declspec( dllexport)
#else
#define _DYNLINK __declspec( dllimport)
#endif

class _DYNLINK CMyClass
{ 
public:
			CMyClass ();

	virtual	~CMyClass();

	void	DoSomethingUseful();
};

typedef void ( CMyClass::*PMYCLASSMETHOD)();

#ifndef _DLL
typedef CMyClass* ( *PFNCREATEMYCLASS)();
#else
_DYNLINK CMyClass* CreateMyClass() 
{ 
	return ( new CMyClass());
}
#endif

#ifndef _DLL
typedef void ( *PFNDELETEMYCLASS)( CMyClass*);
#else
_DYNLINK void DeleteMyClass ( CMyClass* pObj) 
{ 
	delete pObj;
}
#endif

#ifndef _DLL
typedef PMYCLASSMETHOD ( *PFNGETCLASSMETHOD)();
#else
_DYNLINK PMYCLASSMETHOD GetClassMethod () 
{ 
	return &CMyClass::DoSomethingUseful;
}
#endif



#endif	//	ndef __DYNCLASS_H