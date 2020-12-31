# Microsoft Developer Studio Generated NMAKE File, Based on Test_ThreadManager.dsp
!IF "$(CFG)" == ""
CFG=Test_ThreadManager - Win32 Release
!MESSAGE No configuration specified. Defaulting to Test_ThreadManager - Win32\
 Release.
!ENDIF 

!IF "$(CFG)" != "Test_ThreadManager - Win32 Release" && "$(CFG)" !=\
 "Test_ThreadManager - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Test_ThreadManager.mak"\
 CFG="Test_ThreadManager - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Test_ThreadManager - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "Test_ThreadManager - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Test_ThreadManager - Win32 Release"

OUTDIR=.\..\..\ThreadManager
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\..\ThreadManager
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test_ThreadManager.exe"

!ELSE 

ALL : "ThreadManager - Win32 Release" "$(OUTDIR)\Test_ThreadManager.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ThreadManager - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdCGI.obj"
	-@erase "$(INTDIR)\Test_ThreadManager.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Test_ThreadManager.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Test_ThreadManager.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test_ThreadManager.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\Test_ThreadManager.pdb" /machine:I386\
 /out:"$(OUTDIR)\Test_ThreadManager.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdCGI.obj" \
	"$(INTDIR)\Test_ThreadManager.obj" \
	"$(OUTDIR)\ThreadManager.lib"

"$(OUTDIR)\Test_ThreadManager.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Test_ThreadManager - Win32 Debug"

OUTDIR=.\..\..\ThreadManager
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\..\ThreadManager
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test_ThreadManagerD.exe"

!ELSE 

ALL : "ThreadManager - Win32 Debug" "$(OUTDIR)\Test_ThreadManagerD.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ThreadManager - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdCGI.obj"
	-@erase "$(INTDIR)\Test_ThreadManager.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Test_ThreadManagerD.exe"
	-@erase "$(OUTDIR)\Test_ThreadManagerD.ilk"
	-@erase "$(OUTDIR)\Test_ThreadManagerD.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Test_ThreadManager.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test_ThreadManager.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\Test_ThreadManagerD.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\Test_ThreadManagerD.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdCGI.obj" \
	"$(INTDIR)\Test_ThreadManager.obj" \
	"$(OUTDIR)\ThreadManagerD.lib"

"$(OUTDIR)\Test_ThreadManagerD.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "Test_ThreadManager - Win32 Release" || "$(CFG)" ==\
 "Test_ThreadManager - Win32 Debug"
SOURCE=.\StdCGI.cpp
DEP_CPP_STDCG=\
	".\StdCgi.h"\
	

"$(INTDIR)\StdCGI.obj" : $(SOURCE) $(DEP_CPP_STDCG) "$(INTDIR)"


SOURCE=.\Test_ThreadManager.cpp
DEP_CPP_TEST_=\
	"..\ThreadManager.h"\
	".\StdCgi.h"\
	

"$(INTDIR)\Test_ThreadManager.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!IF  "$(CFG)" == "Test_ThreadManager - Win32 Release"

"ThreadManager - Win32 Release" : 
   cd "\Development\CPA_Phase2\Gateway\ThreadManager"
   $(MAKE) /$(MAKEFLAGS) /F .\ThreadManager.mak\
 CFG="ThreadManager - Win32 Release" 
   cd ".\Test_ThreadManager"

"ThreadManager - Win32 ReleaseCLEAN" : 
   cd "\Development\CPA_Phase2\Gateway\ThreadManager"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\ThreadManager.mak\
 CFG="ThreadManager - Win32 Release" RECURSE=1 
   cd ".\Test_ThreadManager"

!ELSEIF  "$(CFG)" == "Test_ThreadManager - Win32 Debug"

"ThreadManager - Win32 Debug" : 
   cd "\Development\CPA_Phase2\Gateway\ThreadManager"
   $(MAKE) /$(MAKEFLAGS) /F .\ThreadManager.mak\
 CFG="ThreadManager - Win32 Debug" 
   cd ".\Test_ThreadManager"

"ThreadManager - Win32 DebugCLEAN" : 
   cd "\Development\CPA_Phase2\Gateway\ThreadManager"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\ThreadManager.mak\
 CFG="ThreadManager - Win32 Debug" RECURSE=1 
   cd ".\Test_ThreadManager"

!ENDIF 


!ENDIF 

