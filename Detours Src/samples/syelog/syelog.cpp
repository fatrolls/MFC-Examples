//////////////////////////////////////////////////////////////////////
//
//	File:		syelog.cpp
//	Module:		syelog.lib
//
//	Copyright 1999-2001, Microsoft Corporation. All rights reserved.
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
#include <windows.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include "detours.h"
#include "syelog.h"

//////////////////////////////////////////////////////////////////////
extern "C" {
    HANDLE WINAPI Real_CreateFileW(LPCWSTR a0,
                                   DWORD a1,
                                   DWORD a2,
                                   LPSECURITY_ATTRIBUTES a3,
                                   DWORD a4,
                                   DWORD a5,
                                   HANDLE a6);
    BOOL WINAPI Real_WriteFile(HANDLE hFile,
                               LPCVOID lpBuffer,
                               DWORD nNumberOfBytesToWrite,
                               LPDWORD lpNumberOfBytesWritten,
                               LPOVERLAPPED lpOverlapped);
    BOOL WINAPI Real_FlushFileBuffers(HANDLE hFile);
    BOOL WINAPI Real_CloseHandle(HANDLE hObject);

    BOOL WINAPI Real_WaitNamedPipeW(LPCWSTR lpNamedPipeName, DWORD nTimeOut);
    BOOL WINAPI Real_SetNamedPipeHandleState(HANDLE hNamedPipe,
                                             LPDWORD lpMode,
                                             LPDWORD lpMaxCollectionCount,
                                             LPDWORD lpCollectDataTimeout);

    DWORD WINAPI Real_GetCurrentProcessId(VOID);
    VOID WINAPI Real_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    VOID WINAPI Real_InitializeCriticalSection(LPCRITICAL_SECTION lpSection);
    VOID WINAPI Real_EnterCriticalSection(LPCRITICAL_SECTION lpSection);
    VOID WINAPI Real_LeaveCriticalSection(LPCRITICAL_SECTION lpSection);
}

///////////////////////////////////////////////////////////////////// VPrintf.
//
// Completely side-effect free printf replacement.
// BUGBUG: Doesn't do floating point numbers.
//
static PCHAR do_base(PCHAR pszOut, UINT64 nValue, UINT nBase, PCSTR pszDigits)
{
	CHAR szTmp[96];
	for (int nDigit = sizeof(szTmp)-2; nDigit >= 0; nDigit--) {
		szTmp[nDigit] = pszDigits[nValue % nBase];
		nValue /= nBase;
	}
	for (nDigit = 0; nDigit < sizeof(szTmp) - 2 && szTmp[nDigit] == '0'; nDigit++) {
		// skip leading zeros.
	}
	for (; nDigit < sizeof(szTmp) - 1; nDigit++) {
		*pszOut++ = szTmp[nDigit];
	}
    *pszOut = '\0';
	return pszOut;
}

static PCHAR do_str(PCHAR pszOut, PCSTR pszIn)
{
    while (*pszIn) {
        *pszOut++ = *pszIn++;
    }
    *pszOut = '\0';
    return pszOut;
}

static PCHAR do_wstr(PCHAR pszOut, PCWSTR pszIn)
{
    while (*pszIn) {
        *pszOut++ = (CHAR)*pszIn++;
    }
    *pszOut = '\0';
    return pszOut;
}

static VOID SafePrintf(PCSTR pszMsg, va_list args, PCHAR pszBuffer, LONG cbBuffer)
{
	PCHAR pszOut = pszBuffer;
	pszBuffer[0] = '\0';

	__try {
		while (*pszMsg) {
			if (*pszMsg == '%') {
                CHAR szTemp[1024];
                CHAR szHead[4] = "";
                INT nLen;
                INT nWidth = 0;
                INT nPrecision = 0;
                BOOL fLeft = FALSE;
                BOOL fPositive = FALSE;
                BOOL fPound = FALSE;
                BOOL fBlank = FALSE;
                BOOL fZero = FALSE;
                BOOL fDigit = FALSE;
                BOOL fSmall = FALSE;
				BOOL fLarge = FALSE;
                BOOL f64Bit = FALSE;
                BOOL fString = FALSE;
                PCSTR pszArg = pszMsg;
                
				pszMsg++;

                for (; (*pszMsg == '-' ||
                        *pszMsg == '+' ||
                        *pszMsg == '#' ||
                        *pszMsg == ' ' ||
                        *pszMsg == '0'); pszMsg++) {
                    switch (*pszMsg) {
                      case '-': fLeft = TRUE; break;
                      case '+': fPositive = TRUE; break;
                      case '#': fPound = TRUE; break;
                      case ' ': fBlank = TRUE; break;
                      case '0': fZero = TRUE; break;
                    }
                }

                if (*pszMsg == '*') {
                    nWidth = va_arg(args, INT);
                    pszMsg++;
                }
                else {
                    while (*pszMsg >= '0' && *pszMsg <= '9') {
                        nWidth = nWidth * 10 + (*pszMsg++ - '0');
                    }
                }
                if (*pszMsg == '.') {
                    pszMsg++;
                    fDigit = TRUE;
                    if (*pszMsg == '*') {
                        nPrecision = va_arg(args, INT);
                        pszMsg++;
                    }
                    else {
                        while (*pszMsg >= '0' && *pszMsg <= '9') {
                            nPrecision = nPrecision * 10 + (*pszMsg++ - '0');
                        }
                    }
                }
				
				if (*pszMsg == 'h') {
					fSmall = TRUE;
					pszMsg++;
				}
				else if (*pszMsg == 'l' || *pszMsg == 'L') {
					fLarge = TRUE;
					pszMsg++;
				}
                else if (*pszMsg == 'I' && pszMsg[1] == '6' && pszMsg[2] == '4') {
                    f64Bit = TRUE;
                    pszMsg += 3;
                }

				if (*pszMsg == 's' || *pszMsg == 'S' ||
                    *pszMsg == 'c' || *pszMsg == 'C')
                {
                    if (*pszMsg == 's' || *pszMsg == 'S')
                    {
                        PCHAR pszDst = szTemp;
                        PVOID pvData = va_arg(args, PVOID);
                    
                        if (*pszMsg == 'S') {
                            fLarge = TRUE;
                        }
                        pszMsg++;
                    
                        fString = TRUE;
                        if (fSmall) {
                            fLarge = FALSE;                        
                        }
					
                        __try {
                            if (pvData == NULL) {
                                pszDst = do_str(pszDst, "<NULL>");
                            }
                            else if (fLarge) {
                                pszDst = do_wstr(pszDst, (PWCHAR)pvData);
                            }
                            else {
                                pszDst = do_str(pszDst, (PCHAR)pvData);
                            }
                        } __except(EXCEPTION_EXECUTE_HANDLER) {
                            pszDst = szTemp;
                            *pszDst++ = '<';
                            pszDst = do_base(pszDst, (UINT64)pvData, 16,
                                             "0123456789ABCDEF");
                            *pszDst++ = '>';
                            *pszDst = '\0';
                        }
                        nLen = pszDst - szTemp;
                    }
                    else {
                        if (*pszMsg == 'S') {
                            fLarge = TRUE;
                        }
                        pszMsg++;
                    
                        fString = TRUE;
                    
                        szTemp[0] = (CHAR)va_arg(args, INT);
                        szTemp[1] = '\0';
                        nLen = 1;
                    }

                    if (nPrecision && nLen > nPrecision) {
                        nLen = nPrecision;
                        szTemp[nLen] = '\0';
                    }
                
                    if (fLeft) {
                        pszOut = do_str(pszOut, szTemp);
                        for (; nLen < nWidth; nLen++) {
                            *pszOut++ = ' ';
                        }
                    }
                    else {
                        for (; nLen < nWidth; nLen++) {
                            *pszOut++ = ' ';
                        }
                        pszOut = do_str(pszOut, szTemp);
                    }
                }
                else if (*pszMsg == 'd' || *pszMsg == 'i' || *pszMsg == 'o' ||
                         *pszMsg == 'x' || *pszMsg == 'X' || *pszMsg == 'b') {
                    UINT64 value;
                    if (f64Bit) {
                        value = va_arg(args, UINT64);
                    }
                    else {
                        value = va_arg(args, UINT);
                    }
                    
                    if (*pszMsg == 'x') {
                        pszMsg++;
                        nLen = do_base(szTemp, value, 16, "0123456789abcdef") - szTemp;
                        if (fPound && value) {
                            do_str(szHead, "0x");
                        }
                    }	
                    else if (*pszMsg == 'X') {
                        pszMsg++;
                        nLen = do_base(szTemp, value, 16, "0123456789ABCDEF") - szTemp;
                        if (fPound && value) {
                            do_str(szHead, "0X");
                        }
                    }	
                    else if (*pszMsg == 'd') {
                        pszMsg++;
                        if ((INT64)value < 0) {
                            value = -(INT64)value;
                            do_str(szHead, "-");
                        }
                        else if (fPositive) {
                            if (value > 0) {
                                do_str(szHead, "+");
                            }
                        }
                        else if (fBlank) {
                            if (value > 0) {
                                do_str(szHead, " ");
                            }
                        }
                        nLen = do_base(szTemp, value, 10, "0123456789") - szTemp;
                        nPrecision = 0;
                    }
                    else if (*pszMsg == 'u') {
                        pszMsg++;
                        nLen = do_base(szTemp, value, 10, "0123456789") - szTemp;
                        nPrecision = 0;
                    }
                    else if (*pszMsg == 'o') {
                        pszMsg++;
                        nLen = do_base(szTemp, value, 8, "01234567") - szTemp;
                        nPrecision = 0;
                        
                        if (fPound && value) {
                            do_str(szHead, "0");
                        }
                    }
                    else if (*pszMsg == 'b') {
                        pszMsg++;
                        nLen = do_base(szTemp, value, 2, "01") - szTemp;
                        nPrecision = 0;
                        
                        if (fPound && value) {
                            do_str(szHead, "0b");
                        }
                    }
                    else {
                        pszMsg++;
                        if ((INT64)value < 0) {
                            value = -(INT64)value;
                            do_str(szHead, "-");
                        }
                        else if (fPositive) {
                            if (value > 0) {
                                do_str(szHead, "+");
                            }
                        }
                        else if (fBlank) {
                            if (value > 0) {
                                do_str(szHead, " ");
                            }
                        }
                        nLen = do_base(szTemp, value, 10, "0123456789") - szTemp;
                        nPrecision = 0;
                    }

                    for (INT nHead = 0; szHead[nHead]; nHead++) {
                        // Count characters in head string.
                    }
                    
                    if (fLeft) {
                        if (nHead) {
                            pszOut = do_str(pszOut, szHead);
                            nLen += nHead;
                        }
                        pszOut = do_str(pszOut, szTemp);
                        for (; nLen < nWidth; nLen++) {
                            *pszOut++ = ' ';
                        }
                    }
                    else if (fZero) {
                        if (nHead) {
                            pszOut = do_str(pszOut, szHead);
                            nLen += nHead;
                        }
                        for (; nLen < nWidth; nLen++) {
                            *pszOut++ = '0';
                        }
                        pszOut = do_str(pszOut, szTemp);
                    }
                    else {
                        if (nHead) {
                            nLen += nHead;
                        }
                        for (; nLen < nWidth; nLen++) {
                            *pszOut++ = ' ';
                        }
                        if (nHead) {
                            pszOut = do_str(pszOut, szHead);
                        }
                        pszOut = do_str(pszOut, szTemp);
                    }
                }
				else {
                    pszMsg++;
                    while (pszArg < pszMsg) {
                        *pszOut++ = *pszArg++;
                    }
				}
			}
			else {
				*pszOut++ = *pszMsg++;
			}
		}
		*pszOut = '\0';
		pszBuffer[cbBuffer - 1] = '\0';
	} __except(EXCEPTION_EXECUTE_HANDLER) {
        PCHAR pszOut = pszBuffer;
        *pszOut = '\0';
        pszOut = do_str(pszOut, "<exception:");
        pszOut = do_base(pszOut, (UINT64)GetExceptionCode(), 10, "0123456789");
        pszOut = do_str(pszOut, ">");
	}
}

//////////////////////////////////////////////////////////////////////////////
//
static CRITICAL_SECTION s_csPipe;                       // Guards access to hPipe.
static HANDLE           s_hPipe = INVALID_HANDLE_VALUE;
static FILETIME         s_ftRetry = {0,0};
static BYTE             s_nFacility = SYELOG_FACILITY_APPLICATION;
static CHAR             s_szIdent[256] = "";
static DWORD            s_nProcessId = 0;

static inline INT syelogCompareTimes(CONST PFILETIME pft1, CONST PFILETIME pft2)
{
    INT64 ut1 = *(PINT64)pft1;
    INT64 ut2 = *(PINT64)pft2;

    if (ut1 < ut2) {
        return -1;
    }
    else if (ut1 > ut2) {
        return 1;
    }
    else {
        return 0;
    }
}

static inline VOID syelogAddMilliseconds(PFILETIME pft, DWORD nMilliseconds)
{
    *(PINT64&)pft += ((INT64)nMilliseconds * 10000);
}

//////////////////////////////////////////////////////////////////////////////
//
// Tries to insure that a named-pipe connection to the system log is open
// If the pipe closes, the next call will immediately try to re-open the pipe.
// If the pipe doesn't open again, we wait 5 minutes before trying again.
// We wait 5 minutes, because each attempt may take up to a full second to
// time out.
//
static BOOL syelogIsOpen(PFILETIME pftLog)
{
	if (s_hPipe != INVALID_HANDLE_VALUE) {
        return TRUE;
    }

    if (syelogCompareTimes(pftLog, &s_ftRetry) < 0) {
        return FALSE;
    }

    s_hPipe = Real_CreateFileW(SYELOG_PIPE_NAMEW,
                               GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        
    if (s_hPipe != INVALID_HANDLE_VALUE) {
        if (Real_WaitNamedPipeW(SYELOG_PIPE_NAMEW, 2000)) { // Wait 2 seconds.
            // Pipe connected, change to message-read mode.
            //
            DWORD dwMode = PIPE_READMODE_MESSAGE;
            if (Real_SetNamedPipeHandleState(s_hPipe, &dwMode, NULL, NULL)) {
                return TRUE;
            }
        }
        Real_CloseHandle(s_hPipe);
        s_hPipe = INVALID_HANDLE_VALUE;
    }

    // Couldn't open pipe.
    s_ftRetry = *pftLog;
    syelogAddMilliseconds(&s_ftRetry, 300000);           // Wait 5 minute before retry.

    return FALSE;
}

VOID SyelogOpen(PCSTR pszIdentifier, BYTE nFacility)
{
    Real_InitializeCriticalSection(&s_csPipe);
    
    if (pszIdentifier) {
        PCHAR pszOut = s_szIdent;
        pszOut = do_str(pszOut, pszIdentifier);
        pszOut = do_str(pszOut, ": ");
    }
    else {
        s_szIdent[0] = '\0';
    }

    s_nFacility = nFacility;
    s_nProcessId = Real_GetCurrentProcessId();
}

VOID Syelog(BYTE nSeverity, PCSTR pszMsgf, ...)
{
	va_list args;
	va_start(args, pszMsgf);
    SyelogV(nSeverity, pszMsgf, args);
	va_end(args);
}

VOID SyelogV(BYTE nSeverity, PCSTR pszMsgf, va_list args)
{
    SYELOG_MESSAGE Message;
    DWORD cbWritten = 0;
    
    Real_GetSystemTimeAsFileTime(&Message.ftOccurance);
    Message.nFacility = s_nFacility;
    Message.nSeverity = nSeverity;
    Message.nProcessId = s_nProcessId;
    PCHAR pszBuf = Message.szMessage;
    if (s_szIdent[0]) {
        pszBuf = do_str(pszBuf, s_szIdent);
    }
	SafePrintf(pszMsgf, args,
               pszBuf, Message.szMessage + sizeof(Message.szMessage) - pszBuf);
        
    for (PCHAR pszEnd = Message.szMessage; *pszEnd; pszEnd++) {
        // no internal contents.
    }

    // Insure that the message always ends with a '\n'
    //
    if (pszEnd > Message.szMessage) {
        if (pszEnd[-1] != '\n') {
            *pszEnd++ = '\n';
            *pszEnd++ = '\0';
        }
        else {
            *pszEnd++ = '\0';
        }
    }
    else {
        *pszEnd++ = '\n';
        *pszEnd++ = '\0';
    }
    Message.nBytes = (USHORT)(pszEnd - ((PCSTR)&Message));

    Real_EnterCriticalSection(&s_csPipe);
    
    if (!Real_WriteFile(s_hPipe, &Message, Message.nBytes, &cbWritten, NULL)) {
        if (s_hPipe != INVALID_HANDLE_VALUE) {
            Real_CloseHandle(s_hPipe);
            s_hPipe = INVALID_HANDLE_VALUE;
        }
        if (syelogIsOpen(&Message.ftOccurance)) {
            Real_WriteFile(s_hPipe, &Message, Message.nBytes, &cbWritten, NULL);
        }
    }
    
    Real_LeaveCriticalSection(&s_csPipe);
}

VOID SyelogClose(VOID)
{
    Real_EnterCriticalSection(&s_csPipe);
    
    if (s_hPipe != INVALID_HANDLE_VALUE) {
        Real_FlushFileBuffers(s_hPipe);
        Real_CloseHandle(s_hPipe);
        s_hPipe = INVALID_HANDLE_VALUE;
    }
    
    Real_LeaveCriticalSection(&s_csPipe);
}
//
///////////////////////////////////////////////////////////////// End of File.
