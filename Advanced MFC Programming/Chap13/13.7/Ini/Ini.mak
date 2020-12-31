# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Ini - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ini - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ini - Win32 Release" && "$(CFG)" != "Ini - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ini.mak" CFG="Ini - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ini - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ini - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Ini - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Ini - Win32 Release"

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

ALL : "$(OUTDIR)\Ini.exe"

CLEAN : 
	-@erase "$(INTDIR)\EditView.obj"
	-@erase "$(INTDIR)\Ini.obj"
	-@erase "$(INTDIR)\Ini.pch"
	-@erase "$(INTDIR)\Ini.res"
	-@erase "$(INTDIR)\IniDoc.obj"
	-@erase "$(INTDIR)\IniView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ToolBar.obj"
	-@erase "$(OUTDIR)\Ini.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ini.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ini.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ini.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Ini.pdb" /machine:I386 /out:"$(OUTDIR)/Ini.exe" 
LINK32_OBJS= \
	"$(INTDIR)\EditView.obj" \
	"$(INTDIR)\Ini.obj" \
	"$(INTDIR)\Ini.res" \
	"$(INTDIR)\IniDoc.obj" \
	"$(INTDIR)\IniView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ToolBar.obj"

"$(OUTDIR)\Ini.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

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

ALL : "$(OUTDIR)\Ini.exe"

CLEAN : 
	-@erase "$(INTDIR)\EditView.obj"
	-@erase "$(INTDIR)\Ini.obj"
	-@erase "$(INTDIR)\Ini.pch"
	-@erase "$(INTDIR)\Ini.res"
	-@erase "$(INTDIR)\IniDoc.obj"
	-@erase "$(INTDIR)\IniView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ToolBar.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Ini.exe"
	-@erase "$(OUTDIR)\Ini.ilk"
	-@erase "$(OUTDIR)\Ini.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ini.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ini.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ini.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Ini.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Ini.exe" 
LINK32_OBJS= \
	"$(INTDIR)\EditView.obj" \
	"$(INTDIR)\Ini.obj" \
	"$(INTDIR)\Ini.res" \
	"$(INTDIR)\IniDoc.obj" \
	"$(INTDIR)\IniView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ToolBar.obj"

"$(OUTDIR)\Ini.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Ini - Win32 Release"
# Name "Ini - Win32 Debug"

!IF  "$(CFG)" == "Ini - Win32 Release"

!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Ini.cpp

!IF  "$(CFG)" == "Ini - Win32 Release"

DEP_CPP_INI_C=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolBar.h"\
	

"$(INTDIR)\Ini.obj" : $(SOURCE) $(DEP_CPP_INI_C) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

DEP_CPP_INI_C=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolBar.h"\
	

"$(INTDIR)\Ini.obj" : $(SOURCE) $(DEP_CPP_INI_C) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Ini - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ini.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ini.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ini.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ini.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Ini - Win32 Release"

DEP_CPP_MAINF=\
	".\EditView.h"\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolBar.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

DEP_CPP_MAINF=\
	".\EditView.h"\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolBar.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IniDoc.cpp

!IF  "$(CFG)" == "Ini - Win32 Release"

DEP_CPP_INIDO=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IniDoc.obj" : $(SOURCE) $(DEP_CPP_INIDO) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

DEP_CPP_INIDO=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IniDoc.obj" : $(SOURCE) $(DEP_CPP_INIDO) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IniView.cpp

!IF  "$(CFG)" == "Ini - Win32 Release"

DEP_CPP_INIVI=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IniView.obj" : $(SOURCE) $(DEP_CPP_INIVI) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ELSEIF  "$(CFG)" == "Ini - Win32 Debug"

DEP_CPP_INIVI=\
	".\Ini.h"\
	".\IniDoc.h"\
	".\IniView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\IniView.obj" : $(SOURCE) $(DEP_CPP_INIVI) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ini.rc
DEP_RSC_INI_R=\
	".\res\Ini.ico"\
	".\res\Ini.rc2"\
	".\res\IniDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Ini.res" : $(SOURCE) $(DEP_RSC_INI_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditView.cpp
DEP_CPP_EDITV=\
	".\EditView.h"\
	".\Ini.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\EditView.obj" : $(SOURCE) $(DEP_CPP_EDITV) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToolBar.cpp
DEP_CPP_TOOLB=\
	".\Ini.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolBar.h"\
	

"$(INTDIR)\ToolBar.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Ini.pch"


# End Source File
# End Target
# End Project
################################################################################
