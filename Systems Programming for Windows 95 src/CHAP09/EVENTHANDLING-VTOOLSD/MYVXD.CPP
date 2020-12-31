// MYVXD.cpp - main module for VxD MYVXD

#define DEVICE_MAIN
#include "myvxd.h"
Declare_Virtual_Device(MYVXD)
#undef DEVICE_MAIN

MyvxdVM::MyvxdVM(VMHANDLE hVM) : VVirtualMachine(hVM) {}

MyvxdThread::MyvxdThread(THREADHANDLE hThread) : VThread(hThread) {}

class MyEvent : public VGlobalEvent
{
public:
   MyEvent(PVOID refData = 0) : VGlobalEvent(refData){}
   void handler(VMHANDLE hVM, CLIENT_STRUCT* pRegs,
      PVOID refData);
   BOOL CancelSafely();
};

BOOL MyEvent::CancelSafely()
   {                // MyEvent::CancelSafely
   _asm  mov  edx, this
   _asm  xor  eax, eax
   _asm  xchg eax, [edx]VEvent.m_handle
   #ifdef Cancel_Global_Event
      #undef Cancel_Global_Event
   #endif
   VMMcall(Cancel_Global_Event);
   BOOL result;
   _asm  mov result, eax
   if (result)
      delete this;
   return result != 0; // TRUE means actually cancelled
   }                // MyEvent::CancelSafely

void MyEvent::handler(VMHANDLE hVM, CLIENT_STRUCT* pRegs,
   PVOID refData)
   {                // MyEvent::handler
   _asm  mov  edx, this
   _asm  xor  eax, eax
   _asm  xchg eax, [edx]VEvent.m_handle
   BOOL not_cancelled;
   _asm  mov not_cancelled, eax
   if (!not_cancelled)
      return;       // event was cancelled, so abort callback
   }                // MyEvent::handler
