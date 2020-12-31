# Microsoft Developer Studio Generated NMAKE File, Based on ServiceSample.dsp
!IF "$(CFG)" == ""
CFG=ServiceSample - Win32 Win95 Debug
!MESSAGE No configuration specified. Defaulting to ServiceSample - Win32 Win95\
 Debug.
!ENDIF 

!IF "$(CFG)" != "ServiceSample - Win32 Release" && "$(CFG)" !=\
 "ServiceSample - Win32 Debug" && "$(CFG)" !=\
 "ServiceSample - Win32 Win95 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ServiceSample.mak" CFG="ServiceSample - Win32 Win95 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ServiceSample - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "ServiceSample - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "ServiceSample - Win32 Win95 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ServiceSample - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ELSE 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NTService.obj"
	-@erase "$(INTDIR)\NTServiceEventLogMsg.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ServiceSample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)\ServiceSample.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\NTServiceEventLogMsg.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServiceSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\ServiceSample.pdb" /machine:I386\
 /out:"$(OUTDIR)\ServiceSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\NTService.obj" \
	"$(INTDIR)\NTServiceEventLogMsg.res"

"$(OUTDIR)\ServiceSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ServiceSample - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ELSE 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NTService.obj"
	-@erase "$(INTDIR)\NTServiceEventLogMsg.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ServiceSample.exe"
	-@erase "$(OUTDIR)\ServiceSample.ilk"
	-@erase "$(OUTDIR)\ServiceSample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D\
 "_CONSOLE" /Fp"$(INTDIR)\ServiceSample.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

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

RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\NTServiceEventLogMsg.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServiceSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\ServiceSample.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\ServiceSample.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\NTService.obj" \
	"$(INTDIR)\NTServiceEventLogMsg.res"

"$(OUTDIR)\ServiceSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ServiceSample - Win32 Win95 Debug"

OUTDIR=.\Win95
INTDIR=.\Win95
# Begin Custom Macros
OutDir=.\Win95
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ELSE 

ALL : "$(OUTDIR)\ServiceSample.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NTService.obj"
	-@erase "$(INTDIR)\NTServiceEventLogMsg.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ServiceSample.exe"
	-@erase "$(OUTDIR)\ServiceSample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "NOMEMCHECK" /Fp"$(INTDIR)\ServiceSample.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Win95/
CPP_SBRS=.

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

RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\NTServiceEventLogMsg.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServiceSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\ServiceSample.pdb" /debug /debugtype:both /machine:I386\
 /out:"$(OUTDIR)\ServiceSample.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\NTService.obj" \
	"$(INTDIR)\NTServiceEventLogMsg.res"

"$(OUTDIR)\ServiceSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "ServiceSample - Win32 Release" || "$(CFG)" ==\
 "ServiceSample - Win32 Debug" || "$(CFG)" ==\
 "ServiceSample - Win32 Win95 Debug"
SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	".\NTService.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


SOURCE=.\NTService.cpp
DEP_CPP_NTSER=\
	".\NTService.h"\
	
NODEP_CPP_NTSER=\
	".\NTServiceEventLogMsg.h"\
	

"$(INTDIR)\NTService.obj" : $(SOURCE) $(DEP_CPP_NTSER) "$(INTDIR)"\
 ".\NTServiceEventLogMsg.h"


SOURCE=.\NTServiceEventLogMsg.mc

!IF  "$(CFG)" == "ServiceSample - Win32 Release"

InputPath=.\NTServiceEventLogMsg.mc
InputName=NTServiceEventLogMsg

"NTServiceEventLogMsg.rc"	"NTServiceEventLogMsg.h"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	mc -v -w $(InputName)

!ELSEIF  "$(CFG)" == "ServiceSample - Win32 Debug"

InputPath=.\NTServiceEventLogMsg.mc
InputName=NTServiceEventLogMsg

"NTServiceEventLogMsg.rc"	"NTServiceEventLogMsg.h"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	mc -v -w $(InputName)

!ELSEIF  "$(CFG)" == "ServiceSample - Win32 Win95 Debug"

InputPath=.\NTServiceEventLogMsg.mc
InputName=NTServiceEventLogMsg

"NTServiceEventLogMsg.rc"	"NTServiceEventLogMsg.h"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	mc -v -w $(InputName)

!ENDIF 

SOURCE=.\NTServiceEventLogMsg.rc

"$(INTDIR)\NTServiceEventLogMsg.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

