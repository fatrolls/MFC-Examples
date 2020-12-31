/////////////////////////////////////////////////////////////////////////////
//
//	Module:		disas.exe - Detours Test Program
//	File:		disas.cpp
//
//  Copyright 1999-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <detours.h>

//////////////////////////////////////////////////////////////////////////////
//	
struct BasicBlockLink
{
  public:
	BasicBlockLink *	m_pNext;
	PBYTE				m_pbEntry;
	PCHAR				m_pszName;

  public:
	BasicBlockLink(PBYTE pbEntry, PCHAR pszName = NULL)
	{
		m_pNext = NULL;
		m_pbEntry = pbEntry;
		m_pszName = pszName;

		*s_ppTail = this;
		s_ppTail = &m_pNext;
	}

	BasicBlockLink * Next()
	{
		return m_pNext;
	}
	
	static BasicBlockLink * GetHead()
	{
		return s_pHead;
	}
	
  protected:
	static BasicBlockLink *		s_pHead;
	static BasicBlockLink **	s_ppTail;
};

BasicBlockLink *	BasicBlockLink::s_pHead = NULL;
BasicBlockLink **	BasicBlockLink::s_ppTail = &BasicBlockLink::s_pHead;

//////////////////////////////////////////////////////////////////////////////
//
void DumpMemoryFragment(PBYTE pbData, ULONG cbData, ULONG cbSpace)
{
	for (ULONG n = 0; n < cbSpace; n++) {
		if (n < cbData) {
			printf("%02x", pbData[n]);
		}
		else {
			printf("  ");
		}
	}
	if (n < cbData) {
		printf(".");
	}
	else {
		printf(" ");
	}
}

BOOL IsTerminate(PBYTE pbSrc)
{
	if (0xC3 == pbSrc[0] ||								// RET
		0xCB == pbSrc[0] ||								// RETF
		0xC2 == pbSrc[0] ||								// RET dw
		0xCA == pbSrc[0] ||								// RETF dw
		0xEB == pbSrc[0] ||								// JMP ob
		0xE9 == pbSrc[0] ||								// JMP ol
		0xEA == pbSrc[0]) {								// JMP ol

		return TRUE;
	}
	if (0xff == pbSrc[0] && 0x25 == pbSrc[1])			// JMP [addr]
		return TRUE;
	return FALSE;
}

void TestDetourCopyInstruction(PBYTE pbSrcInstruction, PCHAR pszFunction)
{
	PBYTE pbSrc = pbSrcInstruction;

	if (pszFunction) {
		printf("%s:\n", pszFunction);
	}
	for (ULONG nIns = 0; nIns < 4096; nIns++) {
		BYTE rbDst[128];
		LONG lExtra = 0;
		PBYTE pbTarget = NULL;
		ULONG cbStep = DetourCopyInstructionEx(rbDst, pbSrc,
											   &pbTarget, &lExtra) - pbSrc;

		printf("    %8lx:", pbSrc);
		DumpMemoryFragment(rbDst, cbStep, 10);
		printf(" ");
		DumpMemoryFragment(rbDst, cbStep, 10);
		if (pbTarget) {
			if (pbTarget == DETOUR_INSTRUCTION_TARGET_DYNAMIC) {
				printf("  Dynamic\n");
			}
			else {
				printf(" %8lx\n", pbTarget);
			}
		}
		else {
			printf("\n");
		}
		
		if (pbTarget && pbTarget != DETOUR_INSTRUCTION_TARGET_DYNAMIC) {
			if (pbTarget > pbSrc) {
				(void) new BasicBlockLink(pbTarget, NULL);
			}
		}
		
		if (IsTerminate(pbSrc)) {
			break;
		}

		pbSrc += cbStep;
	}
}

static BOOL CALLBACK ExportCallback(PVOID pContext,
									DWORD nOrdinal,
									PCHAR pszSymbol,
									PBYTE pbTarget)
{
    (void)pContext;
    (void)nOrdinal;
    (void)pbTarget;
    
	(VOID) new BasicBlockLink(pbTarget, pszSymbol ? pszSymbol : "[NO NAME]");
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpszCmdLine, int nCmdShow)
{
    (void)hprev;
    (void)hinst;
    (void)lpszCmdLine;
    (void)nCmdShow;
    
	HINSTANCE hInst = LoadLibrary("user32.dll");
	printf("Loaded: user32.dll: %08lx\n", hInst);

	PBYTE pbEntry = DetourGetEntryPoint(hInst);
	(VOID) new BasicBlockLink(pbEntry, "user32.dll");
	
	DetourEnumerateExports(hInst, NULL, ExportCallback);
	
	for (BasicBlockLink *pLink = BasicBlockLink::GetHead();
		 pLink; pLink = pLink->Next()) {
		
		TestDetourCopyInstruction(pLink->m_pbEntry, pLink->m_pszName);
	}
	return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
