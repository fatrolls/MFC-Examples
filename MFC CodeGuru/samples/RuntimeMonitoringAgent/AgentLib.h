/*#############################################################################
# AGENTLIB.H
# 
# RUNTIME MONITORING AGENT
# Codor, 18.10.1997
#############################################################################*/

#ifndef __AGENT_LIB__
#define __AGENT_LIB__

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

void _stdcall AgentDefineSystem(int systemId, const char *name);
void _stdcall AgentDefineProcess(int systemId, int processId, const char *name);
void _stdcall AgentDefineFiber(int processId, int fiberId, const char *name);
void _stdcall AgentSendText1A(int fiberId, int processId, int systemId, 
                           const char *text);
void _stdcall AgentSendText1B(int fiberId, const char *text);
void _stdcall AgentSendText2A(int fiberId, int processId, int systemId, 
                           const char *filename, int linenum, 
                           const char *text, long errcode);
void _stdcall AgentSendText2B(int fiberId, const char *filename, int linenum, 
                           const char *text, long errcode);
BOOL _stdcall AgentConvertToReadable(char *buffer, int maxlen, int radix);

/*
#ifdef __cplusplus
}
#endif
*/

#endif

/*#############################################################################
# End of file AGENTLIB.H
#############################################################################*/
