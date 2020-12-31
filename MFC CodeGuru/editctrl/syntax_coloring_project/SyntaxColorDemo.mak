# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SyntaxColorDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SyntaxColorDemo - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "SyntaxColorDemo - Win32 Release" && "$(CFG)" !=\
 "SyntaxColorDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SyntaxColorDemo.mak" CFG="SyntaxColorDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SyntaxColorDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SyntaxColorDemo - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SyntaxColorDemo - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "SyntaxColorDemo - Win32 Release"

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

ALL : "$(OUTDIR)\SyntaxColorDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\ColorEditWnd.obj"
	-@erase "$(INTDIR)\Colorize.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SyntaxColorDemo.obj"
	-@erase "$(INTDIR)\SyntaxColorDemo.pch"
	-@erase "$(INTDIR)\SyntaxColorDemo.res"
	-@erase "$(INTDIR)\SyntaxColorDemoDoc.obj"
	-@erase "$(INTDIR)\SyntaxColorDemoView.obj"
	-@erase "$(OUTDIR)\SyntaxColorDemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SyntaxColorDemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SyntaxColorDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SyntaxColorDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SyntaxColorDemo.pdb" /machine:I386\
 /out:"$(OUTDIR)/SyntaxColorDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ColorEditWnd.obj" \
	"$(INTDIR)\Colorize.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SyntaxColorDemo.obj" \
	"$(INTDIR)\SyntaxColorDemo.res" \
	"$(INTDIR)\SyntaxColorDemoDoc.obj" \
	"$(INTDIR)\SyntaxColorDemoView.obj"

"$(OUTDIR)\SyntaxColorDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SyntaxColorDemo - Win32 Debug"

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

ALL : "$(OUTDIR)\SyntaxColorDemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\ColorEditWnd.obj"
	-@erase "$(INTDIR)\Colorize.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SyntaxColorDemo.obj"
	-@erase "$(INTDIR)\SyntaxColorDemo.pch"
	-@erase "$(INTDIR)\SyntaxColorDemo.res"
	-@erase "$(INTDIR)\SyntaxColorDemoDoc.obj"
	-@erase "$(INTDIR)\SyntaxColorDemoView.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SyntaxColorDemo.exe"
	-@erase "$(OUTDIR)\SyntaxColorDemo.ilk"
	-@erase "$(OUTDIR)\SyntaxColorDemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SyntaxColorDemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SyntaxColorDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SyntaxColorDemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SyntaxColorDemo.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SyntaxColorDemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ColorEditWnd.obj" \
	"$(INTDIR)\Colorize.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SyntaxColorDemo.obj" \
	"$(INTDIR)\SyntaxColorDemo.res" \
	"$(INTDIR)\SyntaxColorDemoDoc.obj" \
	"$(INTDIR)\SyntaxColorDemoView.obj"

"$(OUTDIR)\SyntaxColorDemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SyntaxColorDemo - Win32 Release"
# Name "SyntaxColorDemo - Win32 Debug"

!IF  "$(CFG)" == "SyntaxColorDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "SyntaxColorDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "SyntaxColorDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "SyntaxColorDemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SyntaxColorDemo.cpp
DEP_CPP_SYNTA=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\SyntaxColorDemo.h"\
	".\SyntaxColorDemoDoc.h"\
	".\SyntaxColorDemoView.h"\
	

"$(INTDIR)\SyntaxColorDemo.obj" : $(SOURCE) $(DEP_CPP_SYNTA) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "SyntaxColorDemo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SyntaxColorDemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SyntaxColorDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SyntaxColorDemo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SyntaxColorDemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SyntaxColorDemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\MyMenu.h"\
	".\StdAfx.h"\
	".\SyntaxColorDemo.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SyntaxColorDemoDoc.cpp
DEP_CPP_SYNTAX=\
	".\StdAfx.h"\
	".\SyntaxColorDemo.h"\
	".\SyntaxColorDemoDoc.h"\
	

"$(INTDIR)\SyntaxColorDemoDoc.obj" : $(SOURCE) $(DEP_CPP_SYNTAX) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SyntaxColorDemoView.cpp
DEP_CPP_SYNTAXC=\
	".\ColorEditWnd.h"\
	".\Colorize.h"\
	".\StdAfx.h"\
	".\SyntaxColorDemo.h"\
	".\SyntaxColorDemoDoc.h"\
	".\SyntaxColorDemoView.h"\
	

"$(INTDIR)\SyntaxColorDemoView.obj" : $(SOURCE) $(DEP_CPP_SYNTAXC) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SyntaxColorDemo.rc
DEP_RSC_SYNTAXCO=\
	".\res\SyntaxColorDemo.ico"\
	".\res\SyntaxColorDemo.rc2"\
	".\res\SyntaxColorDemoDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\SyntaxColorDemo.res" : $(SOURCE) $(DEP_RSC_SYNTAXCO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colorize.cpp
DEP_CPP_COLOR=\
	".\Colorize.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Colorize.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorEditWnd.cpp
DEP_CPP_COLORE=\
	".\ColorEditWnd.h"\
	".\Colorize.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorEditWnd.obj" : $(SOURCE) $(DEP_CPP_COLORE) "$(INTDIR)"\
 "$(INTDIR)\SyntaxColorDemo.pch"


# End Source File
# End Target
# End Project
################################################################################
