# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dtime - Win32 (Ascii) Release
!MESSAGE No configuration specified.  Defaulting to Dtime - Win32 (Ascii)\
 Release.
!ENDIF 

!IF "$(CFG)" != "Dtime - Win32 (Ascii) Release" && "$(CFG)" !=\
 "Dtime - Win32 (Ascii) Debug" && "$(CFG)" != "Dtime - Win32 (Unicode) Debug" &&\
 "$(CFG)" != "Dtime - Win32 (Unicode) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dtime.mak" CFG="Dtime - Win32 (Ascii) Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dtime - Win32 (Ascii) Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dtime - Win32 (Ascii) Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dtime - Win32 (Unicode) Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dtime - Win32 (Unicode) Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dtime - Win32 (Unicode) Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "ReleaseA"
# PROP Target_Dir ""
OUTDIR=.\..\lib
INTDIR=.\ReleaseA

ALL : "..\bin\Dt100.dll"

CLEAN : 
	-@erase "..\bin\Dt100.dll"
	-@erase "..\lib\Dt100.exp"
	-@erase "..\lib\Dt100.lib"
	-@erase ".\ReleaseA\Datetime.obj"
	-@erase ".\ReleaseA\Dentry.obj"
	-@erase ".\ReleaseA\Dtime.obj"
	-@erase ".\ReleaseA\Dtime.pch"
	-@erase ".\ReleaseA\Dtime.res"
	-@erase ".\ReleaseA\dtwinver.obj"
	-@erase ".\ReleaseA\PushPin.obj"
	-@erase ".\ReleaseA\StdAfx.obj"
	-@erase ".\ReleaseA\win32sup.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dtime.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL" /d "_ASCIIRELEASE"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/Dtime.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "_ASCIIRELEASE" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\bin\Dt100.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dt100.pdb" /machine:I386 /out:"..\bin\Dt100.dll"\
 /implib:"$(OUTDIR)/Dt100.lib" 
LINK32_OBJS= \
	".\ReleaseA\Datetime.obj" \
	".\ReleaseA\Dentry.obj" \
	".\ReleaseA\Dtime.obj" \
	".\ReleaseA\Dtime.res" \
	".\ReleaseA\dtwinver.obj" \
	".\ReleaseA\PushPin.obj" \
	".\ReleaseA\StdAfx.obj" \
	".\ReleaseA\win32sup.obj"

"..\bin\Dt100.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "DebugA"
# PROP Target_Dir ""
OUTDIR=.\..\lib
INTDIR=.\DebugA

ALL : "..\bin\Dt100d.dll"

CLEAN : 
	-@erase "..\bin\Dt100d.dll"
	-@erase "..\bin\Dt100d.ilk"
	-@erase "..\lib\Dt100d.exp"
	-@erase "..\lib\Dt100d.lib"
	-@erase "..\lib\Dt100d.pdb"
	-@erase ".\DebugA\Datetime.obj"
	-@erase ".\DebugA\Dentry.obj"
	-@erase ".\DebugA\Dtime.obj"
	-@erase ".\DebugA\Dtime.pch"
	-@erase ".\DebugA\Dtime.res"
	-@erase ".\DebugA\dtwinver.obj"
	-@erase ".\DebugA\PushPin.obj"
	-@erase ".\DebugA\StdAfx.obj"
	-@erase ".\DebugA\vc40.idb"
	-@erase ".\DebugA\vc40.pdb"
	-@erase ".\DebugA\win32sup.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dtime.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL" /d "_ASCIIDEBUG"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/Dtime.res" /d "_DEBUG" /d "_AFXDLL" /d\
 "_ASCIIDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin\Dt100d.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Dt100d.pdb" /debug /machine:I386 /out:"..\bin\Dt100d.dll"\
 /implib:"$(OUTDIR)/Dt100d.lib" 
LINK32_OBJS= \
	".\DebugA\Datetime.obj" \
	".\DebugA\Dentry.obj" \
	".\DebugA\Dtime.obj" \
	".\DebugA\Dtime.res" \
	".\DebugA\dtwinver.obj" \
	".\DebugA\PushPin.obj" \
	".\DebugA\StdAfx.obj" \
	".\DebugA\win32sup.obj"

"..\bin\Dt100d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Dtime___"
# PROP BASE Intermediate_Dir "Dtime___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\..\lib
INTDIR=.\DebugU

ALL : "..\bin\Dt100du.dll"

CLEAN : 
	-@erase "..\bin\Dt100du.dll"
	-@erase "..\bin\Dt100du.ilk"
	-@erase "..\lib\Dt100du.exp"
	-@erase "..\lib\Dt100du.lib"
	-@erase "..\lib\Dt100du.pdb"
	-@erase ".\DebugU\Datetime.obj"
	-@erase ".\DebugU\Dentry.obj"
	-@erase ".\DebugU\Dtime.obj"
	-@erase ".\DebugU\Dtime.pch"
	-@erase ".\DebugU\Dtime.res"
	-@erase ".\DebugU\dtwinver.obj"
	-@erase ".\DebugU\PushPin.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\win32sup.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE"\
 /Fp"$(INTDIR)/Dtime.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL" /d "_UNICODEDEBUG"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/Dtime.res" /d "_DEBUG" /d "_AFXDLL" /d\
 "_UNICODEDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/Dtimed.dll"
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin\Dt100du.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Dt100du.pdb" /debug /machine:I386 /out:"..\bin\Dt100du.dll"\
 /implib:"$(OUTDIR)/Dt100du.lib" 
LINK32_OBJS= \
	".\DebugU\Datetime.obj" \
	".\DebugU\Dentry.obj" \
	".\DebugU\Dtime.obj" \
	".\DebugU\Dtime.res" \
	".\DebugU\dtwinver.obj" \
	".\DebugU\PushPin.obj" \
	".\DebugU\StdAfx.obj" \
	".\DebugU\win32sup.obj"

"..\bin\Dt100du.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Dtime__0"
# PROP BASE Intermediate_Dir "Dtime__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\..\lib
INTDIR=.\ReleaseU

ALL : "..\bin\Dt100u.dll"

CLEAN : 
	-@erase "..\bin\Dt100u.dll"
	-@erase "..\lib\Dt100u.exp"
	-@erase "..\lib\Dt100u.lib"
	-@erase ".\ReleaseU\Datetime.obj"
	-@erase ".\ReleaseU\Dentry.obj"
	-@erase ".\ReleaseU\Dtime.obj"
	-@erase ".\ReleaseU\Dtime.pch"
	-@erase ".\ReleaseU\Dtime.res"
	-@erase ".\ReleaseU\dtwinver.obj"
	-@erase ".\ReleaseU\PushPin.obj"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\win32sup.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE"\
 /Fp"$(INTDIR)/Dtime.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL" /d "_UNICODERELEASE"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/Dtime.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "_UNICODERELEASE" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtime.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"Release/Dtimer.dll"
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\bin\Dt100u.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dt100u.pdb" /machine:I386 /out:"..\bin\Dt100u.dll"\
 /implib:"$(OUTDIR)/Dt100u.lib" 
LINK32_OBJS= \
	".\ReleaseU\Datetime.obj" \
	".\ReleaseU\Dentry.obj" \
	".\ReleaseU\Dtime.obj" \
	".\ReleaseU\Dtime.res" \
	".\ReleaseU\dtwinver.obj" \
	".\ReleaseU\PushPin.obj" \
	".\ReleaseU\StdAfx.obj" \
	".\ReleaseU\win32sup.obj"

"..\bin\Dt100u.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dtime - Win32 (Ascii) Release"
# Name "Dtime - Win32 (Ascii) Debug"
# Name "Dtime - Win32 (Unicode) Debug"
# Name "Dtime - Win32 (Unicode) Release"

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dtime.cpp
DEP_CPP_DTIME=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\dtwinver.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\Dtime.obj" : $(SOURCE) $(DEP_CPP_DTIME) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\Dtime.obj" : $(SOURCE) $(DEP_CPP_DTIME) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\Dtime.obj" : $(SOURCE) $(DEP_CPP_DTIME) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\Dtime.obj" : $(SOURCE) $(DEP_CPP_DTIME) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dtime.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

".\ReleaseA\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\ReleaseA\Dtime.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dtime.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\DebugA\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\DebugA\Dtime.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE"\
 /Fp"$(INTDIR)/Dtime.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

".\DebugU\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\DebugU\Dtime.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_UNICODE"\
 /Fp"$(INTDIR)/Dtime.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

".\ReleaseU\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\ReleaseU\Dtime.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dtime.rc
DEP_RSC_DTIME_=\
	".\res\datentry.ico"\
	".\res\pushpind.bmp"\
	".\res\pushpinu.bmp"\
	
NODEP_RSC_DTIME_=\
	".\Dtime.rc2"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\Dtime.res" : $(SOURCE) $(DEP_RSC_DTIME_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\Dtime.res" : $(SOURCE) $(DEP_RSC_DTIME_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\Dtime.res" : $(SOURCE) $(DEP_RSC_DTIME_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\Dtime.res" : $(SOURCE) $(DEP_RSC_DTIME_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Datetime.cpp
DEP_CPP_DATET=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\Datetime.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\Datetime.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\Datetime.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\Datetime.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dentry.cpp

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"

DEP_CPP_DENTR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtimeres.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

".\ReleaseA\Dentry.obj" : $(SOURCE) $(DEP_CPP_DENTR) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"

DEP_CPP_DENTR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtimeres.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

".\DebugA\Dentry.obj" : $(SOURCE) $(DEP_CPP_DENTR) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"

DEP_CPP_DENTR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtimeres.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

".\DebugU\Dentry.obj" : $(SOURCE) $(DEP_CPP_DENTR) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"

DEP_CPP_DENTR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtimeres.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

".\ReleaseU\Dentry.obj" : $(SOURCE) $(DEP_CPP_DENTR) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPin.cpp
DEP_CPP_PUSHP=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\win32sup.cpp
DEP_CPP_WIN32=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\win32sup.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\win32sup.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\win32sup.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\win32sup.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dtwinver.cpp
DEP_CPP_DTWIN=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\dtwinver.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "Dtime - Win32 (Ascii) Release"


".\ReleaseA\dtwinver.obj" : $(SOURCE) $(DEP_CPP_DTWIN) "$(INTDIR)"\
 ".\ReleaseA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Ascii) Debug"


".\DebugA\dtwinver.obj" : $(SOURCE) $(DEP_CPP_DTWIN) "$(INTDIR)"\
 ".\DebugA\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Debug"


".\DebugU\dtwinver.obj" : $(SOURCE) $(DEP_CPP_DTWIN) "$(INTDIR)"\
 ".\DebugU\Dtime.pch"


!ELSEIF  "$(CFG)" == "Dtime - Win32 (Unicode) Release"


".\ReleaseU\dtwinver.obj" : $(SOURCE) $(DEP_CPP_DTWIN) "$(INTDIR)"\
 ".\ReleaseU\Dtime.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
