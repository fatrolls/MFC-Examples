# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MCISample - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MCISample - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MCISample - Win32 Release" && "$(CFG)" !=\
 "MCISample - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MCISample.mak" CFG="MCISample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MCISample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MCISample - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MCISample - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "MCISample - Win32 Release"

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

ALL : "$(OUTDIR)\MCISample.exe"

CLEAN : 
	-@erase "$(INTDIR)\CdAudio.obj"
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\Mci.obj"
	-@erase "$(INTDIR)\MCISample.obj"
	-@erase "$(INTDIR)\MCISample.pch"
	-@erase "$(INTDIR)\MCISample.res"
	-@erase "$(INTDIR)\MCISampleDlg.obj"
	-@erase "$(INTDIR)\PlaySectionDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\MCISample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCISample.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MCISample.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MCISample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MCISample.pdb" /machine:I386 /out:"$(OUTDIR)/MCISample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CdAudio.obj" \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\Mci.obj" \
	"$(INTDIR)\MCISample.obj" \
	"$(INTDIR)\MCISample.res" \
	"$(INTDIR)\MCISampleDlg.obj" \
	"$(INTDIR)\PlaySectionDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MCISample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MCISample - Win32 Debug"

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

ALL : "$(OUTDIR)\MCISample.exe"

CLEAN : 
	-@erase "$(INTDIR)\CdAudio.obj"
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\Mci.obj"
	-@erase "$(INTDIR)\MCISample.obj"
	-@erase "$(INTDIR)\MCISample.pch"
	-@erase "$(INTDIR)\MCISample.res"
	-@erase "$(INTDIR)\MCISampleDlg.obj"
	-@erase "$(INTDIR)\PlaySectionDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MCISample.exe"
	-@erase "$(OUTDIR)\MCISample.ilk"
	-@erase "$(OUTDIR)\MCISample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCISample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MCISample.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MCISample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MCISample.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/MCISample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CdAudio.obj" \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\Mci.obj" \
	"$(INTDIR)\MCISample.obj" \
	"$(INTDIR)\MCISample.res" \
	"$(INTDIR)\MCISampleDlg.obj" \
	"$(INTDIR)\PlaySectionDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MCISample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MCISample - Win32 Release"
# Name "MCISample - Win32 Debug"

!IF  "$(CFG)" == "MCISample - Win32 Release"

!ELSEIF  "$(CFG)" == "MCISample - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MCISample - Win32 Release"

!ELSEIF  "$(CFG)" == "MCISample - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCISample.cpp
DEP_CPP_MCISA=\
	".\CdAudio.h"\
	".\mci.h"\
	".\MCISample.h"\
	".\MCISampleDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MCISample.obj" : $(SOURCE) $(DEP_CPP_MCISA) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCISampleDlg.cpp
DEP_CPP_MCISAM=\
	".\CdAudio.h"\
	".\hyperlink.h"\
	".\mci.h"\
	".\MCISample.h"\
	".\MCISampleDlg.h"\
	".\PlaySectionDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MCISampleDlg.obj" : $(SOURCE) $(DEP_CPP_MCISAM) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MCISample - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCISample.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MCISample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MCISample - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MCISample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MCISample.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MCISample.rc
DEP_RSC_MCISAMP=\
	".\idr_main.ico"\
	".\res\MCISample.rc2"\
	

"$(INTDIR)\MCISample.res" : $(SOURCE) $(DEP_RSC_MCISAMP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CdAudio.cpp
DEP_CPP_CDAUD=\
	".\CdAudio.h"\
	".\mci.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CdAudio.obj" : $(SOURCE) $(DEP_CPP_CDAUD) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mci.cpp
DEP_CPP_MCI_C=\
	".\mci.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mci.obj" : $(SOURCE) $(DEP_CPP_MCI_C) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PlaySectionDlg.cpp
DEP_CPP_PLAYS=\
	".\MCISample.h"\
	".\PlaySectionDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PlaySectionDlg.obj" : $(SOURCE) $(DEP_CPP_PLAYS) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HyperLink.cpp
DEP_CPP_HYPER=\
	".\hyperlink.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\MCISample.pch"


# End Source File
# End Target
# End Project
################################################################################
