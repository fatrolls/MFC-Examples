# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Monitor - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Monitor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Monitor - Win32 Release" && "$(CFG)" !=\
 "Monitor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "monitor.mak" CFG="Monitor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Monitor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Monitor - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Monitor - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Monitor - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\monitor.exe"

CLEAN : 
	-@erase ".\WinRel\monitor.exe"
	-@erase ".\WinRel\RequestLog.obj"
	-@erase ".\WinRel\Monitor.obj"
	-@erase ".\WinRel\ReqOptions.obj"
	-@erase ".\WinRel\Monitor.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/Monitor.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /G5 /Zp1 /MT /W3 /GX /O2 /I "..\RequestMonitor" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G5 /Zp1 /MT /W3 /GX /O2 /I "..\RequestMonitor" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/monitor.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Monitor.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/monitor.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/monitor.pdb" /machine:I386 /out:"$(OUTDIR)/monitor.exe" 
LINK32_OBJS= \
	"$(INTDIR)/RequestLog.obj" \
	"$(INTDIR)/Monitor.obj" \
	"$(INTDIR)/ReqOptions.obj" \
	"$(INTDIR)/Monitor.res"

"$(OUTDIR)\monitor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Monitor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\monitor.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\monitor.exe"
	-@erase ".\WinDebug\Monitor.obj"
	-@erase ".\WinDebug\RequestLog.obj"
	-@erase ".\WinDebug\ReqOptions.obj"
	-@erase ".\WinDebug\Monitor.res"
	-@erase ".\WinDebug\monitor.ilk"
	-@erase ".\WinDebug\monitor.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/Monitor.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /I "..\RequestMonitor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /Zp1 /MTd /W3 /Gm /GX /Zi /Od /I "..\RequestMonitor" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/monitor.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Monitor.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/monitor.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/monitor.pdb" /debug /machine:I386 /out:"$(OUTDIR)/monitor.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Monitor.obj" \
	"$(INTDIR)/RequestLog.obj" \
	"$(INTDIR)/ReqOptions.obj" \
	"$(INTDIR)/Monitor.res"

"$(OUTDIR)\monitor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Monitor - Win32 Release"
# Name "Monitor - Win32 Debug"

!IF  "$(CFG)" == "Monitor - Win32 Release"

!ELSEIF  "$(CFG)" == "Monitor - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Monitor.cpp
DEP_CPP_MONIT=\
	".\stdafx.h"\
	".\monitor.h"\
	".\reqmon.h"\
	".\reqoptions.h"\
	{$(INCLUDE)}"\Dcb.h"\
	{$(INCLUDE)}"\Blockdev.h"\
	{$(INCLUDE)}"\Drp.h"\
	{$(INCLUDE)}"\Vrp.h"\
	{$(INCLUDE)}"\Ida.h"\
	{$(INCLUDE)}"\Dvt.h"\
	{$(INCLUDE)}"\Ddb.h"\
	{$(INCLUDE)}"\Ivt.h"\
	".\requestlog.h"\
	{$(INCLUDE)}"\Debug.h"\
	

"$(INTDIR)\Monitor.obj" : $(SOURCE) $(DEP_CPP_MONIT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Monitor.rc

"$(INTDIR)\Monitor.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReqOptions.cpp

!IF  "$(CFG)" == "Monitor - Win32 Release"

DEP_CPP_REQOP=\
	".\stdafx.h"\
	".\monitor.h"\
	".\reqoptions.h"\
	{$(INCLUDE)}"\Dcb.h"\
	{$(INCLUDE)}"\Blockdev.h"\
	{$(INCLUDE)}"\Drp.h"\
	{$(INCLUDE)}"\Vrp.h"\
	{$(INCLUDE)}"\Ida.h"\
	{$(INCLUDE)}"\Dvt.h"\
	{$(INCLUDE)}"\Ddb.h"\
	{$(INCLUDE)}"\Ivt.h"\
	".\requestlog.h"\
	

"$(INTDIR)\ReqOptions.obj" : $(SOURCE) $(DEP_CPP_REQOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Monitor - Win32 Debug"

DEP_CPP_REQOP=\
	".\stdafx.h"\
	".\monitor.h"\
	".\reqoptions.h"\
	".\requestlog.h"\
	{$(INCLUDE)}"\Dcb.h"\
	{$(INCLUDE)}"\Blockdev.h"\
	{$(INCLUDE)}"\Drp.h"\
	{$(INCLUDE)}"\Vrp.h"\
	{$(INCLUDE)}"\Ida.h"\
	{$(INCLUDE)}"\Dvt.h"\
	{$(INCLUDE)}"\Ddb.h"\
	{$(INCLUDE)}"\Ivt.h"\
	

"$(INTDIR)\ReqOptions.obj" : $(SOURCE) $(DEP_CPP_REQOP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RequestLog.cpp
DEP_CPP_REQUE=\
	".\stdafx.h"\
	".\monitor.h"\
	".\reqmon.h"\
	{$(INCLUDE)}"\Dcb.h"\
	{$(INCLUDE)}"\Blockdev.h"\
	{$(INCLUDE)}"\Drp.h"\
	{$(INCLUDE)}"\Vrp.h"\
	{$(INCLUDE)}"\Ida.h"\
	{$(INCLUDE)}"\Dvt.h"\
	{$(INCLUDE)}"\Ddb.h"\
	{$(INCLUDE)}"\Ivt.h"\
	".\requestlog.h"\
	{$(INCLUDE)}"\Debug.h"\
	

"$(INTDIR)\RequestLog.obj" : $(SOURCE) $(DEP_CPP_REQUE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
