//////////////////////////////////////////////////////////////////////
//
//	Module:		sleepold.exe, sleepnew.exe, and slept.dll
//	Copyright:	1996-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package, Version 1.5 (Build 46)
//

#include <detours.h>

#if 0
PBYTE WINAPI DetourGetFinalCode(PBYTE pbCode, BOOL fSkipJmp);

PBYTE WINAPI DetourCopyInstruction(PBYTE pbDst, PBYTE pbSrc, PBYTE *ppbTarget);
PBYTE WINAPI DetourCopyInstructionEx(PBYTE pbDst,
                                     PBYTE pbSrc,
                                     PBYTE *ppbTarget,
                                     LONG *plExtra);
#endif

static VOID Dump(PBYTE pbBytes, LONG nBytes, PBYTE pbTarget)
{
    for (LONG n = 0; n < nBytes; n += 16) {
        printf("    %08x: ", pbBytes + n);
        for (LONG m = n; m < n + 16; m++) {
            if (m >= nBytes) {
                printf("   ");
            }
            else {
                printf("%02x ", pbBytes[m]);
            }
        }
        if (n == 0) {
            printf("[%08x]", pbTarget);
        }
        printf("\n");
    }
}

static VOID Decode(PCSTR pszDesc, PBYTE pbCode, PBYTE pbOther, LONG nInst) 
{
    printf("  %s = %08x\n", pszDesc, pbCode);

    if (pbCode == pbOther) {
        printf("    ... unchanged ...\n");
        return;
    }
    
    PBYTE pbSrc = pbCode;
    PBYTE pbEnd;
    PBYTE pbTarget;
    for (LONG n = 0; n < nInst; n++) {
        pbEnd = DetourCopyInstruction(NULL, pbSrc, &pbTarget);
        Dump(pbSrc, pbEnd - pbSrc, pbTarget);
        pbSrc = pbEnd;
    }
}


VOID WINAPI Verify(PBYTE pbCode)
{
    Decode("Original", pbCode, NULL, 3);
    Decode("DetourGetFinalCode w/ Skip JMP", DetourGetFinalCode(pbCode, TRUE), pbCode, 3);
    Decode("DetourGetFinalCode w/o Skip JMP", DetourGetFinalCode(pbCode, FALSE), pbCode, 3);
}

//
///////////////////////////////////////////////////////////////// End of File.
