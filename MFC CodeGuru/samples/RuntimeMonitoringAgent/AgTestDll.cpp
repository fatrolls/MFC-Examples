/*#############################################################################
# AGTESTDLL.CPP
#
#############################################################################*/

#include <windows.h>
#include <stdio.h>
#include "agtestdll.h"
#include "agentlib.h"

#define MT_SYSTEM     200
#define MT_PROCESS    300
#define MT_FIBER      310

#define AGENT(x,y,z)    \
      ::AgentSendText2A(x,MT_PROCESS,MT_SYSTEM,__FILE__,__LINE__,y,z)

//
// Static functions
//

extern "C" int APIENTRY
DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved)
{
  if (reason == DLL_PROCESS_ATTACH) {
    AgentDefineSystem(MT_SYSTEM,"Test application for Runtime Monitoring Agent");
    AgentDefineProcess(MT_SYSTEM,MT_PROCESS,"Separate DLL exporting TestFunction()");
    AgentDefineFiber(MT_PROCESS,MT_FIBER,"TestFunction()");
  } else if (reason == DLL_PROCESS_DETACH) {
  } 
  return TRUE;
}

void TestFunction(void)
{
  AGENT(MT_FIBER,"TestFunction enter",0);
  // Do something here
  AGENT(MT_FIBER,"TestFunction exit",0);
}

/*#############################################################################
# End of file AGTESTDLL.CPP
#############################################################################*/
