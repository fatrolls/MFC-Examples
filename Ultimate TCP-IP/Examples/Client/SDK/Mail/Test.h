
#ifndef TEST_H__INCLUDED
#define TEST_H__INCLUDED

#include "resource.h"

BOOL CALLBACK SMTPDlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK POP3DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK ATTACHDlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK AboutProc(HWND,UINT,WPARAM,LPARAM);

int SaveAttachment(HWND hwnd, CUT_Msg& theMessage, int iIndex);

// We want to see the progres of the message sent so we derive our own class
// an override OnSendMailProgress virtual function
//
class testSMTP : public CUT_SMTPClient
{
protected:
	virtual BOOL OnSendMailProgress(long bytesSent, long totalBytes);
};

#endif // TEST_H__INCLUDED





