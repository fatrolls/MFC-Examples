# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=datentry - Win32 (Unicode) Debug
!MESSAGE No configuration specified.  Defaulting to datentry - Win32 (Unicode)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "datentry - Win32 (Ascii) Release" && "$(CFG)" !=\
 "datentry - Win32 (Ascii) Debug" && "$(CFG)" !=\
 "datentry - Win32 (Unicode) Debug" && "$(CFG)" !=\
 "datentry - Win32 (Unicode) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Datentry.mak" CFG="datentry - Win32 (Unicode) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "datentry - Win32 (Ascii) Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "datentry - Win32 (Ascii) Debug" (based on "Win32 (x86) Application")
!MESSAGE "datentry - Win32 (Unicode) Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE "datentry - Win32 (Unicode) Release" (based on\
 "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "datentry - Win32 (Unicode) Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseA"
# PROP Intermediate_Dir "ReleaseA"
# PROP Target_Dir ""
OUTDIR=.\ReleaseA
INTDIR=.\ReleaseA

ALL : "$(OUTDIR)\Datentry.exe" "$(OUTDIR)\Datentry.pch"

CLEAN : 
	-@erase "$(INTDIR)\dateDlg.obj"
	-@erase "$(INTDIR)\datentry.obj"
	-@erase "$(INTDIR)\Datentry.pch"
	-@erase "$(INTDIR)\datentry.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Datentry.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W4 /Gi /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datentry.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/datentry.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datentry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dt100.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=dt100.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Datentry.pdb" /machine:I386 /out:"$(OUTDIR)/Datentry.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dateDlg.obj" \
	"$(INTDIR)\datentry.obj" \
	"$(INTDIR)\datentry.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Datentry.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugA"
# PROP Intermediate_Dir "DebugA"
# PROP Target_Dir ""
OUTDIR=.\DebugA
INTDIR=.\DebugA

ALL : "$(OUTDIR)\Datentry.exe" "$(OUTDIR)\Datentry.pch"

CLEAN : 
	-@erase "$(INTDIR)\dateDlg.obj"
	-@erase "$(INTDIR)\datentry.obj"
	-@erase "$(INTDIR)\Datentry.pch"
	-@erase "$(INTDIR)\datentry.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Datentry.exe"
	-@erase "$(OUTDIR)\Datentry.ilk"
	-@erase "$(OUTDIR)\Datentry.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datentry.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/datentry.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datentry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dt100d.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dt100d.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Datentry.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Datentry.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dateDlg.obj" \
	"$(INTDIR)\datentry.obj" \
	"$(INTDIR)\datentry.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Datentry.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "datentry"
# PROP BASE Intermediate_Dir "datentry"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU

ALL : "$(OUTDIR)\Datentry.exe" "$(OUTDIR)\Datentry.pch"

CLEAN : 
	-@erase "$(INTDIR)\dateDlg.obj"
	-@erase "$(INTDIR)\datentry.obj"
	-@erase "$(INTDIR)\Datentry.pch"
	-@erase "$(INTDIR)\datentry.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Datentry.exe"
	-@erase "$(OUTDIR)\Datentry.ilk"
	-@erase "$(OUTDIR)\Datentry.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Datentry.pch"\
 /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/datentry.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datentry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 dtimed.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Datentry.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Datentry.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dateDlg.obj" \
	"$(INTDIR)\datentry.obj" \
	"$(INTDIR)\datentry.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Datentry.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "datentr0"
# PROP BASE Intermediate_Dir "datentr0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU

ALL : "$(OUTDIR)\Datentry.exe" "$(OUTDIR)\Datentry.pch"

CLEAN : 
	-@erase "$(INTDIR)\dateDlg.obj"
	-@erase "$(INTDIR)\datentry.obj"
	-@erase "$(INTDIR)\Datentry.pch"
	-@erase "$(INTDIR)\datentry.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Datentry.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /YX /c
CPP_PROJ=/nologo /MD /W4 /Gi /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Datentry.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/datentry.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datentry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 dtimer.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
LINK32_FLAGS=dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Datentry.pdb" /machine:I386\
 /out:"$(OUTDIR)/Datentry.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dateDlg.obj" \
	"$(INTDIR)\datentry.obj" \
	"$(INTDIR)\datentry.res" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Datentry.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "datentry - Win32 (Ascii) Release"
# Name "datentry - Win32 (Ascii) Debug"
# Name "datentry - Win32 (Unicode) Debug"
# Name "datentry - Win32 (Unicode) Release"

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"

!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\datentry.cpp

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"

DEP_CPP_DATEN=\
	".\dateDlg.h"\
	".\DATENTRY.H"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\datentry.obj" : $(SOURCE) $(DEP_CPP_DATEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"

DEP_CPP_DATEN=\
	".\dateDlg.h"\
	".\DATENTRY.H"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\datentry.obj" : $(SOURCE) $(DEP_CPP_DATEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"

DEP_CPP_DATEN=\
	".\dateDlg.h"\
	".\DATENTRY.H"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\datentry.obj" : $(SOURCE) $(DEP_CPP_DATEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"

DEP_CPP_DATEN=\
	".\dateDlg.h"\
	".\DATENTRY.H"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\datentry.obj" : $(SOURCE) $(DEP_CPP_DATEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /Gi /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datentry.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Datentry.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datentry.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Datentry.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Datentry.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Datentry.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /Gi /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Datentry.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Datentry.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\datentry.rc
DEP_RSC_DATENT=\
	".\res\datentry.ico"\
	".\res\datentry.rc2"\
	

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"


"$(INTDIR)\datentry.res" : $(SOURCE) $(DEP_RSC_DATENT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"


"$(INTDIR)\datentry.res" : $(SOURCE) $(DEP_RSC_DATENT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"


"$(INTDIR)\datentry.res" : $(SOURCE) $(DEP_RSC_DATENT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"


"$(INTDIR)\datentry.res" : $(SOURCE) $(DEP_RSC_DATENT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dateDlg.cpp

!IF  "$(CFG)" == "datentry - Win32 (Ascii) Release"

DEP_CPP_DATED=\
	".\dateDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\dateDlg.obj" : $(SOURCE) $(DEP_CPP_DATED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Ascii) Debug"

DEP_CPP_DATED=\
	".\dateDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\dateDlg.obj" : $(SOURCE) $(DEP_CPP_DATED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Debug"

DEP_CPP_DATED=\
	".\dateDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\dateDlg.obj" : $(SOURCE) $(DEP_CPP_DATED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datentry - Win32 (Unicode) Release"

DEP_CPP_DATED=\
	".\dateDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dtime.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

"$(INTDIR)\dateDlg.obj" : $(SOURCE) $(DEP_CPP_DATED) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
