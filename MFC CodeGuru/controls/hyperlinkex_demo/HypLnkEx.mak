# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=HypLnkEx - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to HypLnkEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "HypLnkEx - Win32 Release" && "$(CFG)" !=\
 "HypLnkEx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "HypLnkEx.mak" CFG="HypLnkEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HypLnkEx - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HypLnkEx - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "HypLnkEx - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "HypLnkEx - Win32 Release"

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

ALL : "$(OUTDIR)\HypLnkEx.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\HypLnkEx.obj"
	-@erase "$(INTDIR)\HypLnkEx.pch"
	-@erase "$(INTDIR)\HypLnkEx.res"
	-@erase "$(INTDIR)\HypLnkExDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\HypLnkEx.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/HypLnkEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/HypLnkEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/HypLnkEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/HypLnkEx.pdb" /machine:I386 /out:"$(OUTDIR)/HypLnkEx.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\HypLnkEx.obj" \
	"$(INTDIR)\HypLnkEx.res" \
	"$(INTDIR)\HypLnkExDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HypLnkEx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HypLnkEx - Win32 Debug"

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

ALL : "$(OUTDIR)\HypLnkEx.exe"

CLEAN : 
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\HypLnkEx.obj"
	-@erase "$(INTDIR)\HypLnkEx.pch"
	-@erase "$(INTDIR)\HypLnkEx.res"
	-@erase "$(INTDIR)\HypLnkExDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\HypLnkEx.exe"
	-@erase "$(OUTDIR)\HypLnkEx.ilk"
	-@erase "$(OUTDIR)\HypLnkEx.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/HypLnkEx.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x410 /fo"$(INTDIR)/HypLnkEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/HypLnkEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/HypLnkEx.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/HypLnkEx.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\HypLnkEx.obj" \
	"$(INTDIR)\HypLnkEx.res" \
	"$(INTDIR)\HypLnkExDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HypLnkEx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "HypLnkEx - Win32 Release"
# Name "HypLnkEx - Win32 Debug"

!IF  "$(CFG)" == "HypLnkEx - Win32 Release"

!ELSEIF  "$(CFG)" == "HypLnkEx - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "HypLnkEx - Win32 Release"

!ELSEIF  "$(CFG)" == "HypLnkEx - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HypLnkExDlg.cpp

!IF  "$(CFG)" == "HypLnkEx - Win32 Release"

DEP_CPP_HYPLN=\
	".\hyperlink.h"\
	".\HypLnkEx.h"\
	".\HypLnkExDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HypLnkExDlg.obj" : $(SOURCE) $(DEP_CPP_HYPLN) "$(INTDIR)"\
 "$(INTDIR)\HypLnkEx.pch"


!ELSEIF  "$(CFG)" == "HypLnkEx - Win32 Debug"

DEP_CPP_HYPLN=\
	".\hyperlink.h"\
	".\HypLnkEx.h"\
	".\HypLnkExDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HypLnkExDlg.obj" : $(SOURCE) $(DEP_CPP_HYPLN) "$(INTDIR)"\
 "$(INTDIR)\HypLnkEx.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "HypLnkEx - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/HypLnkEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\HypLnkEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "HypLnkEx - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/HypLnkEx.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\HypLnkEx.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HypLnkEx.rc
DEP_RSC_HYPLNK=\
	".\res\bitmap1.bmp"\
	".\res\bitmap2.bmp"\
	".\res\HypLnkEx.ico"\
	".\res\HypLnkEx.rc2"\
	

"$(INTDIR)\HypLnkEx.res" : $(SOURCE) $(DEP_RSC_HYPLNK) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HypLnkEx.cpp
DEP_CPP_HYPLNKE=\
	".\hyperlink.h"\
	".\HypLnkEx.h"\
	".\HypLnkExDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HypLnkEx.obj" : $(SOURCE) $(DEP_CPP_HYPLNKE) "$(INTDIR)"\
 "$(INTDIR)\HypLnkEx.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HyperLink.cpp
DEP_CPP_HYPER=\
	".\hyperlink.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\HypLnkEx.pch"


# End Source File
# End Target
# End Project
################################################################################
