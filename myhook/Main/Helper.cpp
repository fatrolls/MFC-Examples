#include "stdafx.h"
#include "Helper.h"

bool GetErrorMessage(DWORD dwError, CString& strError)
{
    LPVOID lpMsgBuf;
    if (0 == FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPTSTR) &lpMsgBuf, 0, NULL ))
		return false;
	strError = (LPCTSTR)lpMsgBuf;
    LocalFree(lpMsgBuf);
	return true;
}

// string message allocator for posting messages between windows...
char* AllocBuffer(CString strMsg)
{
	int nLen = strMsg.GetLength();
	char *pBuffer = new char[nLen+1]; 
	
	strcpy(pBuffer,(const char*)strMsg);

	ASSERT(pBuffer != NULL);
	return pBuffer;
}

unsigned short ComputeChecksum(unsigned short *addr, int len)
{
	int nleft = len;
	unsigned short *w = addr;
	unsigned short answer;
	int sum = 0;
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}
	if( nleft == 1 ) {
		unsigned short	u = 0;

		*(unsigned char *)(&u) = *(unsigned char *)w ;
		sum += u;
	}
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}