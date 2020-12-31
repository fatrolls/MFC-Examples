# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Hook - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Hook - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Hook - Win32 Release" && "$(CFG)" != "Hook - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Hook.mak" CFG="Hook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Hook - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Hook - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Hook - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Hook - Win32 Release"

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

ALL : "$(OUTDIR)\Hook.exe"

CLEAN : 
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Hook.pch"
	-@erase "$(INTDIR)\Hook.res"
	-@erase "$(INTDIR)\HookDoc.obj"
	-@erase "$(INTDIR)\HookView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Hook.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Hook.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Hook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\HookLib\Debug\HookLib.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=..\HookLib\Debug\HookLib.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Hook.pdb" /machine:I386\
 /out:"$(OUTDIR)/Hook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Hook.res" \
	"$(INTDIR)\HookDoc.obj" \
	"$(INTDIR)\HookView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Hook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

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

ALL : "$(OUTDIR)\Hook.exe"

CLEAN : 
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Hook.pch"
	-@erase "$(INTDIR)\Hook.res"
	-@erase "$(INTDIR)\HookDoc.obj"
	-@erase "$(INTDIR)\HookView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Hook.exe"
	-@erase "$(OUTDIR)\Hook.ilk"
	-@erase "$(OUTDIR)\Hook.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Hook.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Hook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\HookLib\Debug\HookLib.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=..\HookLib\Debug\HookLib.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Hook.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Hook.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Hook.res" \
	"$(INTDIR)\HookDoc.obj" \
	"$(INTDIR)\HookView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Hook.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Hook - Win32 Release"
# Name "Hook - Win32 Debug"

!IF  "$(CFG)" == "Hook - Win32 Release"

!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Hook.cpp

!IF  "$(CFG)" == "Hook - Win32 Release"

DEP_CPP_HOOK_=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\HookView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Hook.obj" : $(SOURCE) $(DEP_CPP_HOOK_) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

DEP_CPP_HOOK_=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\HookView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Hook.obj" : $(SOURCE) $(DEP_CPP_HOOK_) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Hook - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Hook.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Hook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Hook.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Hook - Win32 Release"

DEP_CPP_MAINF=\
	"..\HookLib\HookLib.h"\
	".\Hook.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

DEP_CPP_MAINF=\
	"..\HookLib\HookLib.h"\
	".\Hook.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HookDoc.cpp

!IF  "$(CFG)" == "Hook - Win32 Release"

DEP_CPP_HOOKD=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HookDoc.obj" : $(SOURCE) $(DEP_CPP_HOOKD) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

DEP_CPP_HOOKD=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HookDoc.obj" : $(SOURCE) $(DEP_CPP_HOOKD) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HookView.cpp

!IF  "$(CFG)" == "Hook - Win32 Release"

DEP_CPP_HOOKV=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\HookView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HookView.obj" : $(SOURCE) $(DEP_CPP_HOOKV) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ELSEIF  "$(CFG)" == "Hook - Win32 Debug"

DEP_CPP_HOOKV=\
	".\Hook.h"\
	".\HookDoc.h"\
	".\HookView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HookView.obj" : $(SOURCE) $(DEP_CPP_HOOKV) "$(INTDIR)"\
 "$(INTDIR)\Hook.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hook.rc
DEP_RSC_HOOK_R=\
	".\res\Hook.ico"\
	".\res\Hook.rc2"\
	".\res\HookDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Hook.res" : $(SOURCE) $(DEP_RSC_HOOK_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
