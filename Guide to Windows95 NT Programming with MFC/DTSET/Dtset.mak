# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=dtset - Win32 (Unicode) Debug
!MESSAGE No configuration specified.  Defaulting to dtset - Win32 (Unicode)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "dtset - Win32 (Ascii) Release" && "$(CFG)" !=\
 "dtset - Win32 (Ascii) Debug" && "$(CFG)" != "dtset - Win32 (Unicode) Debug" &&\
 "$(CFG)" != "dtset - Win32 (Unicode) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dtset.mak" CFG="dtset - Win32 (Unicode) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dtset - Win32 (Ascii) Release" (based on "Win32 (x86) Application")
!MESSAGE "dtset - Win32 (Ascii) Debug" (based on "Win32 (x86) Application")
!MESSAGE "dtset - Win32 (Unicode) Debug" (based on "Win32 (x86) Application")
!MESSAGE "dtset - Win32 (Unicode) Release" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "dtset - Win32 (Unicode) Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"

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

ALL : ".\ReleaseA\Dtset.exe"

CLEAN : 
	-@erase ".\ReleaseA\Dtset.exe"
	-@erase ".\ReleaseA\dtset.obj"
	-@erase ".\ReleaseA\dtset.res"
	-@erase ".\ReleaseA\dtsetDlg.obj"
	-@erase ".\ReleaseA\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dtset.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/dtset.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtset.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dt100.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=dt100.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Dtset.pdb" /machine:I386 /out:"$(OUTDIR)/Dtset.exe" 
LINK32_OBJS= \
	".\ReleaseA\dtset.obj" \
	".\ReleaseA\dtset.res" \
	".\ReleaseA\dtsetDlg.obj" \
	".\ReleaseA\StdAfx.obj"

".\ReleaseA\Dtset.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"

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

ALL : ".\DebugA\Dtset.exe"

CLEAN : 
	-@erase ".\DebugA\Dtset.exe"
	-@erase ".\DebugA\Dtset.ilk"
	-@erase ".\DebugA\dtset.obj"
	-@erase ".\DebugA\Dtset.pdb"
	-@erase ".\DebugA\dtset.res"
	-@erase ".\DebugA\dtsetDlg.obj"
	-@erase ".\DebugA\StdAfx.obj"
	-@erase ".\DebugA\vc40.idb"
	-@erase ".\DebugA\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dtset.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugA/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/dtset.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtset.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dt100d.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dt100d.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Dtset.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Dtset.exe" 
LINK32_OBJS= \
	".\DebugA\dtset.obj" \
	".\DebugA\dtset.res" \
	".\DebugA\dtsetDlg.obj" \
	".\DebugA\StdAfx.obj"

".\DebugA\Dtset.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dtset"
# PROP BASE Intermediate_Dir "dtset"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU

ALL : ".\DebugU\Dtset.exe"

CLEAN : 
	-@erase ".\DebugU\Dtset.exe"
	-@erase ".\DebugU\Dtset.ilk"
	-@erase ".\DebugU\dtset.obj"
	-@erase ".\DebugU\Dtset.pdb"
	-@erase ".\DebugU\dtset.res"
	-@erase ".\DebugU\dtsetDlg.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Dtset.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/dtset.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtset.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 dtimed.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Dtset.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Dtset.exe" 
LINK32_OBJS= \
	".\DebugU\dtset.obj" \
	".\DebugU\dtset.res" \
	".\DebugU\dtsetDlg.obj" \
	".\DebugU\StdAfx.obj"

".\DebugU\Dtset.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"

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

ALL : ".\ReleaseU\Dtset.exe"

CLEAN : 
	-@erase ".\ReleaseU\Dtset.exe"
	-@erase ".\ReleaseU\dtset.obj"
	-@erase ".\ReleaseU\dtset.res"
	-@erase ".\ReleaseU\dtsetDlg.obj"
	-@erase ".\ReleaseU\StdAfx.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /YX /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)/Dtset.pch" /YX /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/dtset.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dtset.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 dtimer.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
LINK32_FLAGS=dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Dtset.pdb" /machine:I386\
 /out:"$(OUTDIR)/Dtset.exe" 
LINK32_OBJS= \
	".\ReleaseU\dtset.obj" \
	".\ReleaseU\dtset.res" \
	".\ReleaseU\dtsetDlg.obj" \
	".\ReleaseU\StdAfx.obj"

".\ReleaseU\Dtset.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "dtset - Win32 (Ascii) Release"
# Name "dtset - Win32 (Ascii) Debug"
# Name "dtset - Win32 (Unicode) Debug"
# Name "dtset - Win32 (Unicode) Release"

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"

!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"

!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"

!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"


".\ReleaseA\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"


".\DebugA\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"


".\DebugU\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"


".\ReleaseU\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dtset.rc
DEP_RSC_DTSET=\
	".\res\dtset.ico"\
	".\res\dtset.rc2"\
	

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"


".\ReleaseA\dtset.res" : $(SOURCE) $(DEP_RSC_DTSET) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"


".\DebugA\dtset.res" : $(SOURCE) $(DEP_RSC_DTSET) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"


".\DebugU\dtset.res" : $(SOURCE) $(DEP_RSC_DTSET) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"


".\ReleaseU\dtset.res" : $(SOURCE) $(DEP_RSC_DTSET) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dtsetDlg.cpp
DEP_CPP_DTSETD=\
	".\dtsetDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"


".\ReleaseA\dtsetDlg.obj" : $(SOURCE) $(DEP_CPP_DTSETD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"


".\DebugA\dtsetDlg.obj" : $(SOURCE) $(DEP_CPP_DTSETD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"


".\DebugU\dtsetDlg.obj" : $(SOURCE) $(DEP_CPP_DTSETD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"


".\ReleaseU\dtsetDlg.obj" : $(SOURCE) $(DEP_CPP_DTSETD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dtset.cpp
DEP_CPP_DTSET_=\
	".\dtset.h"\
	".\dtsetDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\datetime.h"\
	{$(INCLUDE)}"\dentry.h"\
	{$(INCLUDE)}"\Dtime.h"\
	{$(INCLUDE)}"\pushpin.h"\
	{$(INCLUDE)}"\win32sup.h"\
	

!IF  "$(CFG)" == "dtset - Win32 (Ascii) Release"


".\ReleaseA\dtset.obj" : $(SOURCE) $(DEP_CPP_DTSET_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Ascii) Debug"


".\DebugA\dtset.obj" : $(SOURCE) $(DEP_CPP_DTSET_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Debug"


".\DebugU\dtset.obj" : $(SOURCE) $(DEP_CPP_DTSET_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "dtset - Win32 (Unicode) Release"


".\ReleaseU\dtset.obj" : $(SOURCE) $(DEP_CPP_DTSET_) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
