# Microsoft Developer Studio Generated NMAKE File, Based on MicroDelay.dsp
!IF "$(CFG)" == ""
CFG=MicroDelay - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MicroDelay - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MicroDelay - Win32 Release" && "$(CFG)" !=\
 "MicroDelay - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MicroDelay.mak" CFG="MicroDelay - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MicroDelay - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MicroDelay - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MicroDelay - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MicroDelay.exe"

!ELSE 

ALL : "$(OUTDIR)\MicroDelay.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MicroDelay.obj"
	-@erase "$(INTDIR)\MicroDelay.pch"
	-@erase "$(INTDIR)\MicroDelay.res"
	-@erase "$(INTDIR)\MicroDelayDlg.obj"
	-@erase "$(INTDIR)\MicroSecond.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MicroDelay.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /Fp"$(INTDIR)\MicroDelay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MicroDelay.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MicroDelay.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\MicroDelay.pdb" /machine:I386 /out:"$(OUTDIR)\MicroDelay.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MicroDelay.obj" \
	"$(INTDIR)\MicroDelay.res" \
	"$(INTDIR)\MicroDelayDlg.obj" \
	"$(INTDIR)\MicroSecond.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MicroDelay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MicroDelay - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MicroDelay.exe"

!ELSE 

ALL : "$(OUTDIR)\MicroDelay.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MicroDelay.obj"
	-@erase "$(INTDIR)\MicroDelay.pch"
	-@erase "$(INTDIR)\MicroDelay.res"
	-@erase "$(INTDIR)\MicroDelayDlg.obj"
	-@erase "$(INTDIR)\MicroSecond.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MicroDelay.exe"
	-@erase "$(OUTDIR)\MicroDelay.ilk"
	-@erase "$(OUTDIR)\MicroDelay.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\MicroDelay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MicroDelay.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MicroDelay.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\MicroDelay.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\MicroDelay.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MicroDelay.obj" \
	"$(INTDIR)\MicroDelay.res" \
	"$(INTDIR)\MicroDelayDlg.obj" \
	"$(INTDIR)\MicroSecond.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MicroDelay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "MicroDelay - Win32 Release" || "$(CFG)" ==\
 "MicroDelay - Win32 Debug"
SOURCE=.\MicroDelay.cpp
DEP_CPP_MICRO=\
	".\MicroDelay.h"\
	".\MicroDelayDlg.h"\
	".\MicroSecond.h"\
	

"$(INTDIR)\MicroDelay.obj" : $(SOURCE) $(DEP_CPP_MICRO) "$(INTDIR)"\
 "$(INTDIR)\MicroDelay.pch"


SOURCE=.\MicroDelay.rc
DEP_RSC_MICROD=\
	".\res\MicroDelay.ico"\
	".\res\MicroDelay.rc2"\
	

"$(INTDIR)\MicroDelay.res" : $(SOURCE) $(DEP_RSC_MICROD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MicroDelayDlg.cpp
DEP_CPP_MICRODE=\
	".\MicroDelay.h"\
	".\MicroDelayDlg.h"\
	".\MicroSecond.h"\
	

"$(INTDIR)\MicroDelayDlg.obj" : $(SOURCE) $(DEP_CPP_MICRODE) "$(INTDIR)"\
 "$(INTDIR)\MicroDelay.pch"


SOURCE=.\MicroSecond.cpp
DEP_CPP_MICROS=\
	".\MicroDelay.h"\
	".\MicroSecond.h"\
	

"$(INTDIR)\MicroSecond.obj" : $(SOURCE) $(DEP_CPP_MICROS) "$(INTDIR)"\
 "$(INTDIR)\MicroDelay.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MicroDelay - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\MicroDelay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MicroDelay.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MicroDelay - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\MicroDelay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MicroDelay.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

