# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Help - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Help - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Help - Win32 Release" && "$(CFG)" != "Help - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Help.mak" CFG="Help - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Help - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Help - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Help - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Help - Win32 Release"

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

ALL : "$(OUTDIR)\Help.exe" "$(OUTDIR)\Help.hlp"

CLEAN : 
	-@erase "$(INTDIR)\Help.hlp"
	-@erase "$(INTDIR)\Help.obj"
	-@erase "$(INTDIR)\Help.pch"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\HelpDlg.obj"
	-@erase "$(INTDIR)\HelpDoc.obj"
	-@erase "$(INTDIR)\HelpView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Help.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Help.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Help.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Help.pdb" /machine:I386 /out:"$(OUTDIR)/Help.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Help.obj" \
	"$(INTDIR)\Help.res" \
	"$(INTDIR)\HelpDlg.obj" \
	"$(INTDIR)\HelpDoc.obj" \
	"$(INTDIR)\HelpView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Help.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

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

ALL : "$(OUTDIR)\Help.exe" "$(OUTDIR)\Help.hlp"

CLEAN : 
	-@erase "$(INTDIR)\Help.hlp"
	-@erase "$(INTDIR)\Help.obj"
	-@erase "$(INTDIR)\Help.pch"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\HelpDlg.obj"
	-@erase "$(INTDIR)\HelpDoc.obj"
	-@erase "$(INTDIR)\HelpView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Help.exe"
	-@erase "$(OUTDIR)\Help.ilk"
	-@erase "$(OUTDIR)\Help.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Help.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Help.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Help.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Help.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Help.obj" \
	"$(INTDIR)\Help.res" \
	"$(INTDIR)\HelpDlg.obj" \
	"$(INTDIR)\HelpDoc.obj" \
	"$(INTDIR)\HelpView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Help.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Help - Win32 Release"
# Name "Help - Win32 Debug"

!IF  "$(CFG)" == "Help - Win32 Release"

!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Help.cpp

!IF  "$(CFG)" == "Help - Win32 Release"

DEP_CPP_HELP_=\
	".\Help.h"\
	".\HelpDoc.h"\
	".\HelpView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Help.obj" : $(SOURCE) $(DEP_CPP_HELP_) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

DEP_CPP_HELP_=\
	".\Help.h"\
	".\HelpDoc.h"\
	".\HelpView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Help.obj" : $(SOURCE) $(DEP_CPP_HELP_) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Help - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Help.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Help.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Help.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Help.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Help - Win32 Release"

DEP_CPP_MAINF=\
	".\Help.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

DEP_CPP_MAINF=\
	".\Help.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HelpDoc.cpp

!IF  "$(CFG)" == "Help - Win32 Release"

DEP_CPP_HELPD=\
	".\Help.h"\
	".\HelpDlg.h"\
	".\HelpDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HelpDoc.obj" : $(SOURCE) $(DEP_CPP_HELPD) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

DEP_CPP_HELPD=\
	".\Help.h"\
	".\HelpDlg.h"\
	".\HelpDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HelpDoc.obj" : $(SOURCE) $(DEP_CPP_HELPD) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HelpView.cpp

!IF  "$(CFG)" == "Help - Win32 Release"

DEP_CPP_HELPV=\
	".\Help.h"\
	".\HelpDoc.h"\
	".\HelpView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HelpView.obj" : $(SOURCE) $(DEP_CPP_HELPV) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

DEP_CPP_HELPV=\
	".\Help.h"\
	".\HelpDoc.h"\
	".\HelpView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HelpView.obj" : $(SOURCE) $(DEP_CPP_HELPV) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Help.rc
DEP_RSC_HELP_R=\
	".\res\Help.ico"\
	".\res\Help.rc2"\
	".\res\HelpDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Help.res" : $(SOURCE) $(DEP_RSC_HELP_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\Help.hpj

!IF  "$(CFG)" == "Help - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Help
InputPath=.\hlp\Help.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "Help - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Help
InputPath=.\hlp\Help.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HelpDlg.cpp
DEP_CPP_HELPDL=\
	".\Help.h"\
	".\HelpDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\HelpDlg.obj" : $(SOURCE) $(DEP_CPP_HELPDL) "$(INTDIR)"\
 "$(INTDIR)\Help.pch"


# End Source File
# End Target
# End Project
################################################################################
