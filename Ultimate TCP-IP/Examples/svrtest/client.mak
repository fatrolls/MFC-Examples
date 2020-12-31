# Microsoft Developer Studio Generated NMAKE File, Based on client.dsp
!IF "$(CFG)" == ""
CFG=client - Win32 Release
!MESSAGE No configuration specified. Defaulting to client - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "client - Win32 Release" && "$(CFG)" != "client - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="client - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "client - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "client - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "$(OUTDIR)\client.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\Test.res"
	-@erase "$(INTDIR)\uh_ctrl.obj"
	-@erase "$(INTDIR)\ut_clnt.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\client.pdb" /machine:I386 /out:"$(OUTDIR)\client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\Test.res" \
	"$(INTDIR)\uh_ctrl.obj" \
	"$(INTDIR)\ut_clnt.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "$(OUTDIR)\client.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\Test.res"
	-@erase "$(INTDIR)\uh_ctrl.obj"
	-@erase "$(INTDIR)\ut_clnt.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\client.exe"
	-@erase "$(OUTDIR)\client.ilk"
	-@erase "$(OUTDIR)\client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\client.pdb" /debug /machine:I386 /out:"$(OUTDIR)\client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\Test.res" \
	"$(INTDIR)\uh_ctrl.obj" \
	"$(INTDIR)\ut_clnt.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "client - Win32 Release" || "$(CFG)" == "client - Win32 Debug"
SOURCE=.\test.cpp
DEP_CPP_TEST_=\
	"..\..\include\uh_ctrl.h"\
	"..\..\include\ut_clnt.h"\
	".\test.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


SOURCE=.\Test.rc
DEP_RSC_TEST_R=\
	".\test.h"\
	

"$(INTDIR)\Test.res" : $(SOURCE) $(DEP_RSC_TEST_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\..\Source\uh_ctrl.cpp
DEP_CPP_UH_CT=\
	"..\..\include\uh_ctrl.h"\
	

"$(INTDIR)\uh_ctrl.obj" : $(SOURCE) $(DEP_CPP_UH_CT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Source\ut_clnt.cpp
DEP_CPP_UT_CL=\
	"..\..\include\ut_clnt.h"\
	{$(INCLUDE)}"stdafx.h"\
	
NODEP_CPP_UT_CL=\
	"..\..\Source\mem.h"\
	

"$(INTDIR)\ut_clnt.obj" : $(SOURCE) $(DEP_CPP_UT_CL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

