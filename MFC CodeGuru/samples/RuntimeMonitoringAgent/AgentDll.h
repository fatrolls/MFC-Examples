/*#############################################################################
# AGENTDLL.H
#
# 15.10.1997. Codor
#############################################################################*/

#ifndef __AGENTDLL_H__
#define __AGENTDLL_H__

// Messages

#define MT_TEXT         0x1000
#define MT_EXTTEXT      0x1001
#define MT_SYSTEM       0x2000
#define MT_PROCESS      0x2001
#define MT_FIBER        0x2002

// Limitations

#define MAX_NAME_LENGTH   255
#define MAX_TEXT_LENGTH   500

// Message contains a plain text. Associated with MT_TEXT message type.
struct TMtText {
  char Text[MAX_TEXT_LENGTH];
};

// Message contains a *text* which is send to the Agent from source code file
// name *Filename*, line number *Linenum*. It may optionally also contain a
// *ErrorCode* which is converted to text representation by the Agent. 
// Associated with MT_EXTTEXT message type.
struct TMtExtText {
  char Filename[MAX_NAME_LENGTH];
  int Linenum;
  int ErrorCode;
  char Text[MAX_TEXT_LENGTH];
};

// Associated with MT_SYSTEM, MT_PROCESS and MT_FIBER message types. This 
// structure associates a name with a numeric value of mentioned identifiers.
struct TMtSystem {
  int Identifier;
  char Name[MAX_NAME_LENGTH];
};
struct TMtProcess {
  int System;
  int Identifier;
  char Name[MAX_NAME_LENGTH];
};
struct TMtFiber {
  int Process;
  int Identifier;
  char Name[MAX_NAME_LENGTH];
};

// This enum identifies the type of information contained in a TAgentMessage
// structure.
enum msgId {
  msgSend = 0,
};

// This structure is a fixed part (header) of a message which is sent to the
// Agent. It is implemented as a block of shared memory protected with synchro
// mechanisms.
struct TAgentMessage {
  msgId Id;           // One of msgId enums 
  int Fiber;          // Fiber this message belongs to
  int Process;        // Process sending the message
  int System;         // System sending the message
  int Type;           // Type of message
  int Length;         // Length of Data associated with a message
  int Day;
  int Month;
  int Year;
  int Hour;
  int Minute;
  int Second;
  int Milliseconds;
};

// Variable part of a message is a block of memory which can have any C-like
// structure. It is implemented as a separate shared memory object.
typedef void TAgentMessageData;

#define _EXPORT extern "C" __declspec(dllexport) 

_EXPORT int _stdcall SendMsg(
            int fiber, 
            int process, 
            int system, 
            int type, 
            int len, 
            void *data
            );
_EXPORT BOOL _stdcall ConvertToReadable(
            char *buffer, 
            int maxlen, 
            int radix
            );

#endif

/*#############################################################################
# End of file AGENTDLL.H
#############################################################################*/
