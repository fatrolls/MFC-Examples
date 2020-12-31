#ifndef _HELPER_FUNCTION_H__
#define _HELPER_FUNCTION_H__

bool GetErrorMessage(DWORD dwError, CString& strError);
// string message allocator for posting messages between windows...
char* AllocBuffer(CString strMsg);
unsigned short ComputeChecksum(unsigned short *addr, int len);

#endif