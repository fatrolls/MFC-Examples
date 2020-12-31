/*#############################################################################
# AGENTLIB.CPP
# 
# RUNTIME MONITORING AGENT
# Codor, 18.10.1997
#############################################################################*/

#include <windows.h>
#include "AgentLib.h"
#include "AgentDll.h"

typedef int (_stdcall *FSendMsg)(
            int fiber, 
            int process, 
            int system, 
            int type, 
            int len, 
            void *data);
typedef BOOL (_stdcall *FConvertToReadable)(
            char *buffer,
            int maxlen, 
            int radix);

static FSendMsg FuncSendMsg = NULL;
static FConvertToReadable FuncConvertToReadable = NULL;

static HINSTANCE DLLHandle = NULL;
static char *DLLName = "AGENTDLL.DLL";

static BOOL loadDll(void);

static BOOL loadDll(void)
{
  if (DLLHandle == NULL) {
    DLLHandle = ::LoadLibrary(DLLName);
    if (DLLHandle != NULL) {
      FuncSendMsg = (FSendMsg)::GetProcAddress(DLLHandle,"SendMsg");
      FuncConvertToReadable = (FConvertToReadable)::GetProcAddress(DLLHandle,
                                                    "ConvertToReadable");
    }
  }
  return (DLLHandle == NULL) ? FALSE : TRUE;
}

void _stdcall AgentDefineSystem(int systemId, const char *name)
{
  loadDll();
  TMtSystem data;
  data.Identifier = systemId;
  strncpy(data.Name,name,MAX_NAME_LENGTH);
  data.Name[MAX_NAME_LENGTH-1] = '\0';
  if (FuncSendMsg)
    FuncSendMsg(0,0,0,MT_SYSTEM,sizeof(TMtSystem),&data);
}

void _stdcall AgentDefineProcess(int systemId, int processId, const char *name)
{
  loadDll();
  TMtProcess data;
  data.System = systemId;
  data.Identifier = processId;
  strncpy(data.Name,name,MAX_NAME_LENGTH);
  data.Name[MAX_NAME_LENGTH-1] = '\0';
  if (FuncSendMsg)
    FuncSendMsg(0,0,0,MT_PROCESS,sizeof(TMtProcess),&data);
}

void _stdcall AgentDefineFiber(int processId, int fiberId, const char *name)
{
  loadDll();
  TMtFiber data;
  data.Process = processId;
  data.Identifier = fiberId;
  strncpy(data.Name,name,MAX_NAME_LENGTH);
  data.Name[MAX_NAME_LENGTH-1] = '\0';
  if (FuncSendMsg)
    FuncSendMsg(0,0,0,MT_FIBER,sizeof(TMtFiber),&data);
}

void _stdcall AgentSendText1A(int fiberId, int processId, int systemId, 
                           const char *text)
{
  loadDll();
  TMtText data;
  strcpy(data.Text,text);
  strncpy(data.Text,text,MAX_TEXT_LENGTH);
  data.Text[MAX_TEXT_LENGTH-1] = '\0';
  if (FuncSendMsg)
    FuncSendMsg(fiberId,processId,systemId,MT_TEXT,sizeof(TMtText),&data);
}

void _stdcall AgentSendText1B(int fiberId, const char *text)
{
  loadDll();
  TMtText data;
  strncpy(data.Text,text,MAX_TEXT_LENGTH);
  data.Text[MAX_TEXT_LENGTH-1] = '\0';
  if (FuncSendMsg)
    FuncSendMsg(fiberId,0,0,MT_TEXT,sizeof(TMtText),&data);
}

void _stdcall AgentSendText2A(int fiberId, int processId, int systemId, 
                           const char *filename, int linenum, 
                           const char *text, long errcode)
{
  loadDll();
  TMtExtText data;
  if (filename) {
    strncpy(data.Filename,filename,MAX_NAME_LENGTH);
    data.Filename[MAX_NAME_LENGTH-1] = '\0';
  }
  data.Linenum = linenum;
  strncpy(data.Text,text,MAX_TEXT_LENGTH);
  data.Text[MAX_TEXT_LENGTH-1] = '\0';
  data.ErrorCode = errcode;
  if (FuncSendMsg)
    FuncSendMsg(fiberId,processId,systemId,
                MT_EXTTEXT,sizeof(TMtExtText),&data);
}

void _stdcall AgentSendText2B(int fiberId, const char *filename, int linenum, 
                           const char *text, long errcode)
{
  loadDll();
  TMtExtText data;
  if (filename) {
    strncpy(data.Filename,filename,MAX_NAME_LENGTH);
    data.Filename[MAX_NAME_LENGTH-1] = '\0';
  }
  data.Linenum = linenum;
  strncpy(data.Text,text,MAX_TEXT_LENGTH);
  data.Text[MAX_TEXT_LENGTH-1] = '\0';
  data.ErrorCode = errcode;
  if (FuncSendMsg)
    FuncSendMsg(fiberId,0,0,MT_EXTTEXT,sizeof(TMtExtText),&data);
}

BOOL _stdcall AgentConvertToReadable(char *buffer, int maxlen, int radix)
{
  loadDll();
  if (FuncConvertToReadable)
    return FuncConvertToReadable(buffer,maxlen,radix);
  return FALSE;
}

/*#############################################################################
# End of file AGENTLIB.CPP
#############################################################################*/
