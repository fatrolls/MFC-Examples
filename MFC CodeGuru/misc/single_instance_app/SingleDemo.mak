# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SingleDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SingleDemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SingleDemo - Win32 Release" && "$(CFG)" !=\
 "SingleDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SingleDemo.mak" CFG="SingleDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SingleDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SingleDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "SingleDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\SingleDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\SingleDemo.obj"
	-@erase "$(INTDIR)\SingleDemo.pch"
	-@erase "$(INTDIR)\SingleDemo.res"
	-@erase "$(INTDIR)\SingleDemoDoc.obj"
	-@erase "$(INTDIR)\SingleDemoView.obj"
	-@erase "$(INTDIR)\SingleInstanceApp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\SingleDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SingleDemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/SingleDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SingleDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SingleDemo.pdb" /machine:I386 /out:"$(OUTDIR)/SingleDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\SingleDemo.obj" \
	"$(INTDIR)\SingleDemo.res" \
	"$(INTDIR)\SingleDemoDoc.obj" \
	"$(INTDIR)\SingleDemoView.obj" \
	"$(INTDIR)\SingleInstanceApp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SingleDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SingleDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\SingleDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\SingleDemo.obj"
	-@erase "$(INTDIR)\SingleDemo.pch"
	-@erase "$(INTDIR)\SingleDemo.res"
	-@erase "$(INTDIR)\SingleDemoDoc.obj"
	-@erase "$(INTDIR)\SingleDemoView.obj"
	-@erase "$(INTDIR)\SingleInstanceApp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SingleDemo.exe"
	-@erase "$(OUTDIR)\SingleDemo.ilk"
	-@erase "$(OUTDIR)\SingleDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SingleDemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/SingleDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SingleDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SingleDemo.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SingleDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\SingleDemo.obj" \
	"$(INTDIR)\SingleDemo.res" \
	"$(INTDIR)\SingleDemoDoc.obj" \
	"$(INTDIR)\SingleDemoView.obj" \
	"$(INTDIR)\SingleInstanceApp.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SingleDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "SingleDemo - Win32 Release"
# Name "SingleDemo - Win32 Debug"

!IF  "$(CFG)" == "SingleDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "SingleDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "SingleDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "SingleDemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleDemo.cpp
DEP_CPP_SINGL=\
	".\MainFrm.h"\
	".\SingleDemo.h"\
	".\SingleDemoDoc.h"\
	".\SingleDemoView.h"\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SingleDemo.obj" : $(SOURCE) $(DEP_CPP_SINGL) "$(INTDIR)"\
 "$(INTDIR)\SingleDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "SingleDemo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SingleDemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SingleDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SingleDemo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SingleDemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SingleDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\SingleDemo.h"\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SingleDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleDemoDoc.cpp
DEP_CPP_SINGLE=\
	".\SingleDemo.h"\
	".\SingleDemoDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SingleDemoDoc.obj" : $(SOURCE) $(DEP_CPP_SINGLE) "$(INTDIR)"\
 "$(INTDIR)\SingleDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleDemoView.cpp
DEP_CPP_SINGLED=\
	".\SingleDemo.h"\
	".\SingleDemoDoc.h"\
	".\SingleDemoView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SingleDemoView.obj" : $(SOURCE) $(DEP_CPP_SINGLED) "$(INTDIR)"\
 "$(INTDIR)\SingleDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleDemo.rc
DEP_RSC_SINGLEDE=\
	".\res\SingleDemo.ico"\
	".\res\SingleDemo.rc2"\
	".\res\SingleDemoDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\SingleDemo.res" : $(SOURCE) $(DEP_RSC_SINGLEDE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SingleInstanceApp.cpp
DEP_CPP_SINGLEI=\
	".\SingleInstanceApp.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SingleInstanceApp.obj" : $(SOURCE) $(DEP_CPP_SINGLEI) "$(INTDIR)"\
 "$(INTDIR)\SingleDemo.pch"


# End Source File
# End Target
# End Project
################################################################################
