//////////////////////////////////////////////////////////////////////////////
//
//	Module:		dtest.exe - Detours Test Program
//	File:		dtest.cpp
//
//  Copyright 1998-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
#include <stdio.h>
#include <windows.h>
#include <detours.h>

#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

////////////////////////////////////////////////////// Detour of API Function.
//
DETOUR_TRAMPOLINE(VOID WINAPI Trampoline_Sleep(DWORD dwMilliseconds),
				  Sleep);

static VOID WINAPI Detour_Sleep(DWORD dwMilliseconds)
{
	printf("  Starting to sleep for %d milliseconds.\n", dwMilliseconds);
	Trampoline_Sleep(dwMilliseconds);
	printf("  Done sleeping.\n");
}

////////////////////////////////////////////////// Detour of Private Function.
//
static VOID WINAPI Test(VOID)
{
    printf("      Test\n");
}

DETOUR_TRAMPOLINE(VOID WINAPI Trampoline_Test(VOID),
				  Test);

static VOID WINAPI Detour_Test(VOID)
{
    printf("     Starting Test.\n");
    Trampoline_Test();
    printf("     End test.\n");
}

/////////////////////////////////////////////////////////// Recursive Detours.
//
DETOUR_TRAMPOLINE_EMPTY(VOID WINAPI Trampoline_Test1(VOID));
DETOUR_TRAMPOLINE_EMPTY(VOID WINAPI Trampoline_Test2(VOID));
DETOUR_TRAMPOLINE_EMPTY(VOID WINAPI Trampoline_Test3(VOID));

static VOID WINAPI Detour_Test1(VOID)
{
    printf("    Starting Test1.\n");
    Trampoline_Test1();
    printf("    End Test1.\n");
}

static VOID WINAPI Detour_Test2(VOID)
{
    printf("   Starting Test2.\n");
    Trampoline_Test2();
    printf("   End Test2.\n");
}

static VOID WINAPI Detour_Test3(VOID)
{
    printf("  Starting Test3.\n");
    Trampoline_Test3();
    printf("  End Test3.\n");
}

//////////////////////////////////////////////////////////////////////////////
//
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpszCmdLine, int nCmdShow)
{
	DetourFunctionWithTrampoline((PBYTE)Trampoline_Sleep, (PBYTE)Detour_Sleep);
	DetourFunctionWithTrampoline((PBYTE)Trampoline_Test, (PBYTE)Detour_Test);
	
	printf("Calling Sleep.\n");
	Sleep(2);
    
	printf("Calling Test.\n");
	Test();

	DetourFunctionWithEmptyTrampoline((PBYTE)Trampoline_Test1,
                                      (PBYTE)Test,
                                      (PBYTE)Detour_Test1);
	DetourFunctionWithEmptyTrampoline((PBYTE)Trampoline_Test2,
                                      (PBYTE)Test,
                                      (PBYTE)Detour_Test2);
	DetourFunctionWithEmptyTrampoline((PBYTE)Trampoline_Test3,
                                      (PBYTE)Test,
                                      (PBYTE)Detour_Test3);

    printf("Calling test again with recursive detours.\n");
	Test();
    
	printf("Done.\n");
	
	return 0;
}

//
///////////////////////////////////////////////////////////////// End of File.
