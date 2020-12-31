# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=datetest - Win32 (Unicode) Debug
!MESSAGE No configuration specified.  Defaulting to datetest - Win32 (Unicode)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "datetest - Win32 (Unicode) Release" && "$(CFG)" !=\
 "datetest - Win32 (Unicode) Debug" && "$(CFG)" !=\
 "datetest - Win32 (Ascii) Debug" && "$(CFG)" !=\
 "datetest - Win32 (Ascii) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Datetest.mak" CFG="datetest - Win32 (Unicode) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "datetest - Win32 (Unicode) Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "datetest - Win32 (Unicode) Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "datetest - Win32 (Ascii) Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "datetest - Win32 (Ascii) Release" (based on\
 "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "datetest - Win32 (Ascii) Release"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "datetest - Win32 (Unicode) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU

ALL : ".\ReleaseU\Datetest.exe"

CLEAN : 
	-@erase ".\ReleaseU\Datetest.exe"
	-@erase ".\ReleaseU\datetest.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/datetest.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datetest.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datetest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console /machine:I386
LINK32_FLAGS=dt100u.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Datetest.pdb" /machine:I386\
 /out:"$(OUTDIR)/Datetest.exe" 
LINK32_OBJS= \
	".\ReleaseU\datetest.obj"

".\ReleaseU\Datetest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datetest - Win32 (Unicode) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
OUTDIR=.\DebugU
INTDIR=.\DebugU

ALL : ".\DebugU\Datetest.exe"

CLEAN : 
	-@erase ".\DebugU\Datetest.exe"
	-@erase ".\DebugU\Datetest.ilk"
	-@erase ".\DebugU\datetest.obj"
	-@erase ".\DebugU\Datetest.pdb"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/datetest.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datetest.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datetest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console /debug /machine:I386
LINK32_FLAGS=dt100du.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/Datetest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Datetest.exe" 
LINK32_OBJS= \
	".\DebugU\datetest.obj"

".\DebugU\Datetest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32__A"
# PROP BASE Intermediate_Dir "Win32__A"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugA"
# PROP Intermediate_Dir "DebugA"
OUTDIR=.\DebugA
INTDIR=.\DebugA

ALL : ".\DebugA\Datetest.exe"

CLEAN : 
	-@erase ".\DebugA\Datetest.exe"
	-@erase ".\DebugA\Datetest.ilk"
	-@erase ".\DebugA\datetest.obj"
	-@erase ".\DebugA\Datetest.pdb"
	-@erase ".\DebugA\vc40.idb"
	-@erase ".\DebugA\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/datetest.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datetest.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugA/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datetest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:console /debug /machine:I386
# ADD LINK32 dt100d.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console /debug /machine:I386
LINK32_FLAGS=dt100d.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/Datetest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Datetest.exe" 
LINK32_OBJS= \
	".\DebugA\datetest.obj"

".\DebugA\Datetest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32__0"
# PROP BASE Intermediate_Dir "Win32__0"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseA"
# PROP Intermediate_Dir "ReleaseA"
OUTDIR=.\ReleaseA
INTDIR=.\ReleaseA

ALL : ".\ReleaseA\Datetest.exe"

CLEAN : 
	-@erase ".\ReleaseA\Datetest.exe"
	-@erase ".\ReleaseA\datetest.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/datetest.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_UNICODE" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Datetest.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseA/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Datetest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:console /machine:I386
# ADD LINK32 dt100.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console /machine:I386
LINK32_FLAGS=dt100.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/Datetest.pdb" /machine:I386\
 /out:"$(OUTDIR)/Datetest.exe" 
LINK32_OBJS= \
	".\ReleaseA\datetest.obj"

".\ReleaseA\Datetest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "datetest - Win32 (Unicode) Release"
# Name "datetest - Win32 (Unicode) Debug"
# Name "datetest - Win32 (Ascii) Debug"
# Name "datetest - Win32 (Ascii) Release"

!IF  "$(CFG)" == "datetest - Win32 (Unicode) Release"

!ELSEIF  "$(CFG)" == "datetest - Win32 (Unicode) Debug"

!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Debug"

!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\datetest.cpp
DEP_CPP_DATET=\
	"..\Include\datetime.h"\
	"..\Include\dentry.h"\
	"..\Include\pushpin.h"\
	"..\Include\win32sup.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\dtime.h"\
	

!IF  "$(CFG)" == "datetest - Win32 (Unicode) Release"


".\ReleaseU\datetest.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datetest - Win32 (Unicode) Debug"


".\DebugU\datetest.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Debug"


".\DebugA\datetest.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "datetest - Win32 (Ascii) Release"


".\ReleaseA\datetest.obj" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
