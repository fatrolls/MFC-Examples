# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=WavTipSample - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WavTipSample - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WavTipSample - Win32 Release" && "$(CFG)" !=\
 "WavTipSample - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WavTipSample.mak" CFG="WavTipSample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WavTipSample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WavTipSample - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "WavTipSample - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "WavTipSample - Win32 Release"

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

ALL : "$(OUTDIR)\WavTipSample.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\WavTipCtrl.obj"
	-@erase "$(INTDIR)\WavTipSample.obj"
	-@erase "$(INTDIR)\WavTipSample.pch"
	-@erase "$(INTDIR)\WavTipSample.res"
	-@erase "$(INTDIR)\WavTipSampleDlg.obj"
	-@erase "$(OUTDIR)\WavTipSample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WavTipSample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/WavTipSample.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WavTipSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/WavTipSample.pdb" /machine:I386\
 /out:"$(OUTDIR)/WavTipSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WavTipCtrl.obj" \
	"$(INTDIR)\WavTipSample.obj" \
	"$(INTDIR)\WavTipSample.res" \
	"$(INTDIR)\WavTipSampleDlg.obj"

"$(OUTDIR)\WavTipSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WavTipSample - Win32 Debug"

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

ALL : "$(OUTDIR)\WavTipSample.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WavTipCtrl.obj"
	-@erase "$(INTDIR)\WavTipSample.obj"
	-@erase "$(INTDIR)\WavTipSample.pch"
	-@erase "$(INTDIR)\WavTipSample.res"
	-@erase "$(INTDIR)\WavTipSampleDlg.obj"
	-@erase "$(OUTDIR)\WavTipSample.exe"
	-@erase "$(OUTDIR)\WavTipSample.ilk"
	-@erase "$(OUTDIR)\WavTipSample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WavTipSample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/WavTipSample.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WavTipSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/WavTipSample.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/WavTipSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WavTipCtrl.obj" \
	"$(INTDIR)\WavTipSample.obj" \
	"$(INTDIR)\WavTipSample.res" \
	"$(INTDIR)\WavTipSampleDlg.obj"

"$(OUTDIR)\WavTipSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "WavTipSample - Win32 Release"
# Name "WavTipSample - Win32 Debug"

!IF  "$(CFG)" == "WavTipSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WavTipSample - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "WavTipSample - Win32 Release"

!ELSEIF  "$(CFG)" == "WavTipSample - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavTipSample.cpp
DEP_CPP_WAVTI=\
	".\StdAfx.h"\
	".\WavTipCtrl.h"\
	".\WavTipSample.h"\
	".\WavTipSampleDlg.h"\
	

"$(INTDIR)\WavTipSample.obj" : $(SOURCE) $(DEP_CPP_WAVTI) "$(INTDIR)"\
 "$(INTDIR)\WavTipSample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavTipSampleDlg.cpp
DEP_CPP_WAVTIP=\
	".\HyperLink.h"\
	".\StdAfx.h"\
	".\WavTipCtrl.h"\
	".\WavTipSample.h"\
	".\WavTipSampleDlg.h"\
	

"$(INTDIR)\WavTipSampleDlg.obj" : $(SOURCE) $(DEP_CPP_WAVTIP) "$(INTDIR)"\
 "$(INTDIR)\WavTipSample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "WavTipSample - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WavTipSample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WavTipSample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WavTipSample - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/WavTipSample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WavTipSample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavTipSample.rc
DEP_RSC_WAVTIPS=\
	".\res\Robotz - Popup di menu.wav"\
	".\res\Utopia - Popup di menu.wav"\
	".\res\WavTipSample.ico"\
	".\res\WavTipSample.rc2"\
	

"$(INTDIR)\WavTipSample.res" : $(SOURCE) $(DEP_RSC_WAVTIPS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WavTipCtrl.cpp
DEP_CPP_WAVTIPC=\
	".\StdAfx.h"\
	".\WavTipCtrl.h"\
	".\WavTipSample.h"\
	

"$(INTDIR)\WavTipCtrl.obj" : $(SOURCE) $(DEP_CPP_WAVTIPC) "$(INTDIR)"\
 "$(INTDIR)\WavTipSample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HyperLink.cpp
DEP_CPP_HYPER=\
	".\HyperLink.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\WavTipSample.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section WavTipSample : {30C51FB3-8FA3-11CF-B070-0020187210E2}
# 	2:16:CWavTipSampleDlg:1
# End Section
################################################################################
