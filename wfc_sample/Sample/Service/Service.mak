# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Service - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Service - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Service - Win32 Release" && "$(CFG)" !=\
 "Service - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Service.mak" CFG="Service - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Service - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Service - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "Service - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Service - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\Service.exe"

CLEAN : 
	-@erase ".\WinRel\Service.exe"
	-@erase ".\WinRel\Service.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /G4 /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G4 /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG"\
 /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Service.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Service.pdb" /machine:I386 /out:"$(OUTDIR)/Service.exe"\
 /FORCE:MULTIPLE 
LINK32_OBJS= \
	".\WinRel\Service.obj" \
	"..\..\LIB\WinRel\WFC.lib"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Service - Win32 Debug"

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

ALL : "$(OUTDIR)\Service.exe" "$(OUTDIR)\Service.bsc"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\Service.bsc"
	-@erase ".\WinDebug\Service.sbr"
	-@erase ".\WinDebug\Service.exe"
	-@erase ".\WinDebug\Service.obj"
	-@erase ".\WinDebug\Service.ilk"
	-@erase ".\WinDebug\Service.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /ML /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
CPP_PROJ=/nologo /MLd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Service.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Service.bsc" 
BSC32_SBRS= \
	".\WinDebug\Service.sbr"

"$(OUTDIR)\Service.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Service.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Service.exe"\
 /FORCE:MULTIPLE 
LINK32_OBJS= \
	".\WinDebug\Service.obj" \
	"..\..\LIB\WinRel\WFC.lib"

"$(OUTDIR)\Service.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Service - Win32 Release"
# Name "Service - Win32 Debug"

!IF  "$(CFG)" == "Service - Win32 Release"

!ELSEIF  "$(CFG)" == "Service - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Service.cpp
DEP_CPP_SERVI=\
	"\wfc\include\wfc.h"\
	".\..\..\include\samtf.h"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	"\wfc\include\CNetSess.hpp"\
	"\wfc\include\CNetWkst.hpp"\
	"\wfc\include\CNetFile.hpp"\
	"\wfc\include\CNetConn.hpp"\
	"\wfc\include\CNetShar.hpp"\
	"\wfc\include\CNetInfo.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\CService.hpp"\
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DrawGrid.hpp"\
	"\wfc\include\CSquigl.hpp"\
	"\wfc\include\CSMTF.hpp"\
	"\wfc\include\CTape.hpp"\
	"\wfc\include\CFileTime.hpp"\
	"\wfc\include\CSystemTime.hpp"\
	

!IF  "$(CFG)" == "Service - Win32 Release"


"$(INTDIR)\Service.obj" : $(SOURCE) $(DEP_CPP_SERVI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Service - Win32 Debug"


"$(INTDIR)\Service.obj" : $(SOURCE) $(DEP_CPP_SERVI) "$(INTDIR)"

"$(INTDIR)\Service.sbr" : $(SOURCE) $(DEP_CPP_SERVI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\LIB\WinRel\WFC.lib

!IF  "$(CFG)" == "Service - Win32 Release"

!ELSEIF  "$(CFG)" == "Service - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
