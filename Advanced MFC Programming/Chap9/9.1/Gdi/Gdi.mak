# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=GDI - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to GDI - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GDI - Win32 Release" && "$(CFG)" != "GDI - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gdi.mak" CFG="GDI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GDI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GDI - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "GDI - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "GDI - Win32 Release"

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

ALL : "$(OUTDIR)\Gdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\GDI.obj"
	-@erase "$(INTDIR)\Gdi.pch"
	-@erase "$(INTDIR)\GDI.res"
	-@erase "$(INTDIR)\GDIDoc.obj"
	-@erase "$(INTDIR)\GDIView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StyleDlg.obj"
	-@erase "$(OUTDIR)\Gdi.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Gdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GDI.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Gdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Gdi.pdb" /machine:I386 /out:"$(OUTDIR)/Gdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GDI.obj" \
	"$(INTDIR)\GDI.res" \
	"$(INTDIR)\GDIDoc.obj" \
	"$(INTDIR)\GDIView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StyleDlg.obj"

"$(OUTDIR)\Gdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GDI - Win32 Debug"

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

ALL : "$(OUTDIR)\Gdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\GDI.obj"
	-@erase "$(INTDIR)\Gdi.pch"
	-@erase "$(INTDIR)\GDI.res"
	-@erase "$(INTDIR)\GDIDoc.obj"
	-@erase "$(INTDIR)\GDIView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StyleDlg.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Gdi.exe"
	-@erase "$(OUTDIR)\Gdi.ilk"
	-@erase "$(OUTDIR)\Gdi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Gdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GDI.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Gdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Gdi.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Gdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GDI.obj" \
	"$(INTDIR)\GDI.res" \
	"$(INTDIR)\GDIDoc.obj" \
	"$(INTDIR)\GDIView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StyleDlg.obj"

"$(OUTDIR)\Gdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "GDI - Win32 Release"
# Name "GDI - Win32 Debug"

!IF  "$(CFG)" == "GDI - Win32 Release"

!ELSEIF  "$(CFG)" == "GDI - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\GDI.cpp

!IF  "$(CFG)" == "GDI - Win32 Release"

DEP_CPP_GDI_C=\
	".\GDI.h"\
	".\GDIDoc.h"\
	".\GDIView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\GDI.obj" : $(SOURCE) $(DEP_CPP_GDI_C) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


!ELSEIF  "$(CFG)" == "GDI - Win32 Debug"

DEP_CPP_GDI_C=\
	".\GDI.h"\
	".\GDIDoc.h"\
	".\GDIView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\GDI.obj" : $(SOURCE) $(DEP_CPP_GDI_C) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "GDI - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Gdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Gdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GDI - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Gdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Gdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\GDI.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GDIDoc.cpp
DEP_CPP_GDIDO=\
	".\GDI.h"\
	".\GDIDoc.h"\
	".\StdAfx.h"\
	".\StyleDlg.h"\
	

"$(INTDIR)\GDIDoc.obj" : $(SOURCE) $(DEP_CPP_GDIDO) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GDIView.cpp
DEP_CPP_GDIVI=\
	".\GDI.h"\
	".\GDIDoc.h"\
	".\GDIView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\GDIView.obj" : $(SOURCE) $(DEP_CPP_GDIVI) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GDI.rc
DEP_RSC_GDI_R=\
	".\res\GDI.ico"\
	".\res\GDI.rc2"\
	".\res\GDIDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\GDI.res" : $(SOURCE) $(DEP_RSC_GDI_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StyleDlg.cpp
DEP_CPP_STYLE=\
	".\GDI.h"\
	".\StdAfx.h"\
	".\StyleDlg.h"\
	

"$(INTDIR)\StyleDlg.obj" : $(SOURCE) $(DEP_CPP_STYLE) "$(INTDIR)"\
 "$(INTDIR)\Gdi.pch"


# End Source File
# End Target
# End Project
################################################################################
