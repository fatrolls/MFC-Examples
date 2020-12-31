##############################################################################
##
##  Microsoft Research Detours Package, Version 1.5 (Build 46)
##
##  Copyright 1995-2001, Microsoft Corporation.
##
        
BUILDING:
=========
To build the sample applications, type "nmake" in the samples directory.
Note that you must build setdll and syslog in order to use many of the
other sample programs.

COMMENTS:
=========
Each of the sample directories has a shell script (Test.Bat) to demonstrate
the usage of the sample.  With very few exceptions, all of the executables
also accept a "/?" or "-?" command to display a usage message.

The trace* samples log their output through the syelogd.exe daemon and hook
CreateProcessW to inject themselves into any child processes.  For example,
typing "withdll -d:traceapi.dll cmd.exe" will create a command shell under
which all processes log their API calls through traceapi.dll.

The Detours package contains the following sample programs:

slept:    Simplest example of a Detours-based DLL which modifies and
          adds functionality to the API.  Replaced Sleep with a new
          API, which records the number of cycles spent sleeping.

cping:    Detours multiple functions in the DCOM/RPC stacks to measure
          the overhead of sending DCOM messages.

disas:    Tests the Detours disassembler.

dtest:    Detours the Win32 Sleep function and a private function.
          The private function is first detoured, then detoured recursively
          3 times using DetourFunctionWithEmptyTrampoline.

dumpe:    Dumps the list of all functions exported from a binary.

dumpi:    Dumps the list of all function imported by a binary.

einst:    Find payloads compiled into binary files.

excep:    Uses the first-chance exception filter to toggle VM permissions
          on a page; enabling writes after catching the first write to a
          page.

member:   Demostrates how to detour a class member function.

setdll:   Add a DLL to any binary (a .DLL or .EXE for example).  Use
          setdll.exe to attach one samples DLLs of an other application
          .EXE file.

withdll:  CreateProcessWithDll test program.  Effectively calls CreateProcess
          and injects a named DLL into the new process.

injdll:   Inject a DLL into a running process.

syelog:   System event logging library and service.  All of the tracing
          samples connect to syelogd.exe through a named pipe.  Syelogd
          outputs tracing information to the console.  You must syelogd.exe
          in a seperate window in order to see the output from any of the
          following tracing DLLs: traceapi, tracemem, tracereg, traceser,
          or tracetcp.
                    
traceapi: Win32 API tracing tool.  Contains a DLL which detours and prints
          tracing statements for 1401 Win32 API functions.  The traceapi
          program will attach to the DLL to any arbitrary Win32 binary.
          
tracemem: Traces all calls to HeapAlloc.

tracereg: Traces activity through the registry APIs.

traceser: Traces activity through the serial ports (com1 or com2).

tracetcp: Traces activity through WinSock TCP APIs.

