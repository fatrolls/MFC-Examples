#include <windows.h>
#include "dynclass.h"

HINSTANCE		g_hinstThisDll;

static	BOOL			g_bCrippledOS	=	FALSE;
static	OSVERSIONINFO	g_osviVerInfo;

extern "C" int APIENTRY	DllMain	(	HINSTANCE	hInstance, 
									DWORD		dwReason, 
									LPVOID		lpReserved
								)
{
	BOOL	bRC	=	TRUE;

    if	(	DLL_PROCESS_ATTACH	==	dwReason)
		{
		    // Extension DLL one-time initialization
	        g_hinstThisDll	=	hInstance;

			g_osviVerInfo.dwOSVersionInfoSize	=	sizeof	(	OSVERSIONINFO);
			
			GetVersionEx(	&g_osviVerInfo);
			
			if (	VER_PLATFORM_WIN32_WINDOWS	==	g_osviVerInfo.dwPlatformId)
					g_bCrippledOS	=	TRUE;

		}

	return	(	TRUE);
}

CMyClass::CMyClass ()
{
  OutputDebugString ( "This is CMyClass::CMyClass()\n");
}

CMyClass::~CMyClass()
{
  OutputDebugString ( "This is CMyClass::~CMyClass()\n");
}

void	CMyClass::DoSomethingUseful() 
{
  OutputDebugString ( "This is CMyClass::DoSomethingUseful()\n");
}
