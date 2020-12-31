# Microsoft Developer Studio Generated NMAKE File, Based on ThreadManager.dsp
!IF "$(CFG)" == ""
CFG=ThreadManager - Win32 Release
!MESSAGE No configuration specified. Defaulting to ThreadManager - Win32\
 Release.
!ENDIF 

!IF "$(CFG)" != "ThreadManager - Win32 Release" && "$(CFG)" !=\
 "ThreadManager - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ThreadManager.mak" CFG="ThreadManager - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ThreadManager - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ThreadManager - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ThreadManager - Win32 Release"

OUTDIR=.\.
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ThreadManager.dll" "$(OUTDIR)\Release\ThreadManager.pch"

!ELSE 

ALL : "$(OUTDIR)\ThreadManager.dll" "$(OUTDIR)\Release\ThreadManager.pch"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ThreadManager.obj"
	-@erase "$(INTDIR)\ThreadManager.pch"
	-@erase "$(INTDIR)\ThreadManager.res"
	-@erase "$(INTDIR)\ThreadManager_Instance.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ThreadManager.dll"
	-@erase "$(OUTDIR)\ThreadManager.exp"
	-@erase "$(OUTDIR)\ThreadManager.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G5 /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_THREADMANAGER"\
 /Fp"$(INTDIR)\ThreadManager.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\ThreadManager.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ThreadManager.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\ThreadManager.pdb" /machine:I386 /def:".\ThreadManager.def"\
 /out:"$(OUTDIR)\ThreadManager.dll" /implib:"$(OUTDIR)\ThreadManager.lib" 
DEF_FILE= \
	".\ThreadManager.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadManager.obj" \
	"$(INTDIR)\ThreadManager.res" \
	"$(INTDIR)\ThreadManager_Instance.obj"

"$(OUTDIR)\ThreadManager.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ThreadManager - Win32 Debug"

OUTDIR=.\.
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ThreadManagerD.dll" "$(OUTDIR)\Debug\ThreadManager.pch"\
 "$(OUTDIR)\ThreadManager.bsc"

!ELSE 

ALL : "$(OUTDIR)\ThreadManagerD.dll" "$(OUTDIR)\Debug\ThreadManager.pch"\
 "$(OUTDIR)\ThreadManager.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\ThreadManager.obj"
	-@erase "$(INTDIR)\ThreadManager.pch"
	-@erase "$(INTDIR)\ThreadManager.res"
	-@erase "$(INTDIR)\ThreadManager.sbr"
	-@erase "$(INTDIR)\ThreadManager_Instance.obj"
	-@erase "$(INTDIR)\ThreadManager_Instance.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ThreadManager.bsc"
	-@erase "$(OUTDIR)\ThreadManagerD.dll"
	-@erase "$(OUTDIR)\ThreadManagerD.exp"
	-@erase "$(OUTDIR)\ThreadManagerD.ilk"
	-@erase "$(OUTDIR)\ThreadManagerD.lib"
	-@erase "$(OUTDIR)\ThreadManagerD.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /G5 /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 "_BUILD_THREADMANAGER" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ThreadManager.pch"\
 /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\ThreadManager.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ThreadManager.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\ThreadManager.sbr" \
	"$(INTDIR)\ThreadManager_Instance.sbr"

"$(OUTDIR)\ThreadManager.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /version:2.10 /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\ThreadManagerD.pdb" /debug /machine:I386\
 /def:".\ThreadManagerD.def" /out:"$(OUTDIR)\ThreadManagerD.dll"\
 /implib:"$(OUTDIR)\ThreadManagerD.lib" 
DEF_FILE= \
	".\ThreadManagerD.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadManager.obj" \
	"$(INTDIR)\ThreadManager.res" \
	"$(INTDIR)\ThreadManager_Instance.obj"

"$(OUTDIR)\ThreadManagerD.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "ThreadManager - Win32 Release" || "$(CFG)" ==\
 "ThreadManager - Win32 Debug"
SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ThreadManager - Win32 Release"

CPP_SWITCHES=/nologo /G5 /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_THREADMANAGER"\
 /Fp"$(INTDIR)\ThreadManager.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ThreadManager.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ThreadManager - Win32 Debug"

CPP_SWITCHES=/nologo /G5 /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 "_BUILD_THREADMANAGER" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ThreadManager.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ThreadManager.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ThreadManager.cpp
DEP_CPP_THREA=\
	".\StdAfx.h"\
	".\ThreadManager.h"\
	

!IF  "$(CFG)" == "ThreadManager - Win32 Release"


"$(INTDIR)\ThreadManager.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ThreadManager - Win32 Debug"


"$(INTDIR)\ThreadManager.obj"	"$(INTDIR)\ThreadManager.sbr" : $(SOURCE)\
 $(DEP_CPP_THREA) "$(INTDIR)"


!ENDIF 

SOURCE=.\ThreadManager_Instance.cpp
DEP_CPP_THREAD=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ThreadManager - Win32 Release"


"$(INTDIR)\ThreadManager_Instance.obj" : $(SOURCE) $(DEP_CPP_THREAD)\
 "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ThreadManager - Win32 Debug"


"$(INTDIR)\ThreadManager_Instance.obj"	"$(INTDIR)\ThreadManager_Instance.sbr" :\
 $(SOURCE) $(DEP_CPP_THREAD) "$(INTDIR)"


!ENDIF 

SOURCE=.\ThreadManager.rc
DEP_RSC_THREADM=\
	".\res\ThreadManager.rc2"\
	

"$(INTDIR)\ThreadManager.res" : $(SOURCE) $(DEP_RSC_THREADM) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

