# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Pinger - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Pinger - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Pinger - Win32 Release" && "$(CFG)" != "Pinger - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pinger.mak" CFG="Pinger - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pinger - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Pinger - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "Pinger - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Pinger - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Pinger.exe" "$(OUTDIR)\Pinger.bsc"

CLEAN : 
	-@erase ".\Release\Pinger.bsc"
	-@erase ".\Release\Pinger.sbr"
	-@erase ".\Release\Pinger.exe"
	-@erase ".\Release\Pinger.obj"
	-@erase ".\Release\Pinger.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /G4 /MT /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /G4 /MT /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG"\
 /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Pinger.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Pinger.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Pinger.bsc" 
BSC32_SBRS= \
	".\Release\Pinger.sbr"

"$(OUTDIR)\Pinger.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib" /nodefaultlib:" libcmtd.lib" /nodefaultlib:" msvcrtd.lib" /FORCE:MULTIPLE
# SUBTRACT LINK32 /verbose /pdb:none
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Pinger.pdb" /machine:I386 /nodefaultlib:"libc.lib"\
 /nodefaultlib:" msvcrt.lib" /nodefaultlib:" libcd.lib"\
 /nodefaultlib:" libcmtd.lib" /nodefaultlib:" msvcrtd.lib"\
 /out:"$(OUTDIR)/Pinger.exe" /FORCE:MULTIPLE 
LINK32_OBJS= \
	".\Release\Pinger.obj" \
	".\Release\Pinger.res" \
	"..\..\LIB\WinRel\WFC.lib"

"$(OUTDIR)\Pinger.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Pinger - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Pinger.exe" "$(OUTDIR)\Pinger.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Pinger.bsc"
	-@erase ".\Debug\Pinger.sbr"
	-@erase ".\Debug\Pinger.exe"
	-@erase ".\Debug\Pinger.obj"
	-@erase ".\Debug\Pinger.res"
	-@erase ".\Debug\Pinger.ilk"
	-@erase ".\Debug\Pinger.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /O2 /I "\wfc\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W4 /Gm /GX /Zi /O2 /I "\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Pinger.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Pinger.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Pinger.bsc" 
BSC32_SBRS= \
	".\Debug\Pinger.sbr"

"$(OUTDIR)\Pinger.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Pinger.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Pinger.exe" 
LINK32_OBJS= \
	".\Debug\Pinger.obj" \
	".\Debug\Pinger.res" \
	"..\..\LIB\WinRel\WFC.lib"

"$(OUTDIR)\Pinger.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Pinger - Win32 Release"
# Name "Pinger - Win32 Debug"

!IF  "$(CFG)" == "Pinger - Win32 Release"

!ELSEIF  "$(CFG)" == "Pinger - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Pinger.cpp

!IF  "$(CFG)" == "Pinger - Win32 Release"

DEP_CPP_PINGE=\
	"\wfc\include\wfc.h"\
	".\messages.h"\
	".\..\..\include\samtf.h"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\Serial.hpp"\
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
	

"$(INTDIR)\Pinger.obj" : $(SOURCE) $(DEP_CPP_PINGE) "$(INTDIR)"

"$(INTDIR)\Pinger.sbr" : $(SOURCE) $(DEP_CPP_PINGE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Pinger - Win32 Debug"

DEP_CPP_PINGE=\
	"\wfc\include\wfc.h"\
	".\messages.h"\
	".\..\..\include\samtf.h"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	

"$(INTDIR)\Pinger.obj" : $(SOURCE) $(DEP_CPP_PINGE) "$(INTDIR)"

"$(INTDIR)\Pinger.sbr" : $(SOURCE) $(DEP_CPP_PINGE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\LIB\WinRel\WFC.lib

!IF  "$(CFG)" == "Pinger - Win32 Release"

!ELSEIF  "$(CFG)" == "Pinger - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pinger.rc
DEP_RSC_PINGER=\
	".\messages.rc"\
	".\MSG00001.bin"\
	

"$(INTDIR)\Pinger.res" : $(SOURCE) $(DEP_RSC_PINGER) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
