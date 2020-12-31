# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MDrive - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MDrive - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MDrive - Win32 Release" && "$(CFG)" != "MDrive - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "mdrive.mak" CFG="MDrive - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDrive - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MDrive - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MDrive - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MDrive - Win32 Release"

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

ALL : "$(OUTDIR)\mdrive.exe"

CLEAN : 
	-@erase "$(INTDIR)\DriveDlg.obj"
	-@erase "$(INTDIR)\driver.obj"
	-@erase "$(INTDIR)\MDrive.obj"
	-@erase "$(INTDIR)\mdrive.pch"
	-@erase "$(INTDIR)\MDrive.res"
	-@erase "$(INTDIR)\premdriv.obj"
	-@erase "$(OUTDIR)\mdrive.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"premdriv.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mdrive.pch" /Yu"premdriv.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MDrive.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mdrive.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/mdrive.pdb" /machine:I386 /out:"$(OUTDIR)/mdrive.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DriveDlg.obj" \
	"$(INTDIR)\driver.obj" \
	"$(INTDIR)\MDrive.obj" \
	"$(INTDIR)\MDrive.res" \
	"$(INTDIR)\premdriv.obj"

"$(OUTDIR)\mdrive.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MDrive - Win32 Debug"

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

ALL : "$(OUTDIR)\mdrive.exe"

CLEAN : 
	-@erase "$(INTDIR)\DriveDlg.obj"
	-@erase "$(INTDIR)\driver.obj"
	-@erase "$(INTDIR)\MDrive.obj"
	-@erase "$(INTDIR)\mdrive.pch"
	-@erase "$(INTDIR)\MDrive.res"
	-@erase "$(INTDIR)\premdriv.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\mdrive.exe"
	-@erase "$(OUTDIR)\mdrive.ilk"
	-@erase "$(OUTDIR)\mdrive.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"premdriv.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mdrive.pch" /Yu"premdriv.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MDrive.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mdrive.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/mdrive.pdb" /debug /machine:I386 /out:"$(OUTDIR)/mdrive.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DriveDlg.obj" \
	"$(INTDIR)\driver.obj" \
	"$(INTDIR)\MDrive.obj" \
	"$(INTDIR)\MDrive.res" \
	"$(INTDIR)\premdriv.obj"

"$(OUTDIR)\mdrive.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MDrive - Win32 Release"
# Name "MDrive - Win32 Debug"

!IF  "$(CFG)" == "MDrive - Win32 Release"

!ELSEIF  "$(CFG)" == "MDrive - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MDrive.cpp
DEP_CPP_MDRIV=\
	"..\connect.h"\
	"..\connect_i.c"\
	".\DriveDlg.h"\
	".\MDrive.h"\
	".\premdriv.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	

"$(INTDIR)\MDrive.obj" : $(SOURCE) $(DEP_CPP_MDRIV) "$(INTDIR)"\
 "$(INTDIR)\mdrive.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDrive.rc
DEP_RSC_MDRIVE=\
	".\res\MDrive.ico"\
	".\res\MDrive.rc2"\
	

"$(INTDIR)\MDrive.res" : $(SOURCE) $(DEP_RSC_MDRIVE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DriveDlg.cpp
DEP_CPP_DRIVE=\
	"..\connect.h"\
	".\DriveDlg.h"\
	".\Driver.h"\
	".\MDrive.h"\
	".\premdriv.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	

"$(INTDIR)\DriveDlg.obj" : $(SOURCE) $(DEP_CPP_DRIVE) "$(INTDIR)"\
 "$(INTDIR)\mdrive.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\driver.cpp
DEP_CPP_DRIVER=\
	"..\connect.h"\
	".\Driver.h"\
	".\premdriv.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	

"$(INTDIR)\driver.obj" : $(SOURCE) $(DEP_CPP_DRIVER) "$(INTDIR)"\
 "$(INTDIR)\mdrive.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\premdriv.cpp
DEP_CPP_PREMD=\
	"..\connect.h"\
	".\premdriv.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	

!IF  "$(CFG)" == "MDrive - Win32 Release"

# ADD CPP /Yc"premdriv.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mdrive.pch" /Yc"premdriv.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\premdriv.obj" : $(SOURCE) $(DEP_CPP_PREMD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mdrive.pch" : $(SOURCE) $(DEP_CPP_PREMD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MDrive - Win32 Debug"

# ADD CPP /Yc"premdriv.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/mdrive.pch" /Yc"premdriv.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\premdriv.obj" : $(SOURCE) $(DEP_CPP_PREMD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mdrive.pch" : $(SOURCE) $(DEP_CPP_PREMD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
