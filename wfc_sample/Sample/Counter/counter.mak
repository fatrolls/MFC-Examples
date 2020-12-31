# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=counter - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to counter - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "counter - Win32 Release" && "$(CFG)" !=\
 "counter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "counter.mak" CFG="counter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "counter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "counter - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "counter - Win32 Release"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "counter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\counter.exe"

CLEAN : 
	-@erase "$(INTDIR)\CPerformanceData.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(OUTDIR)\counter.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/counter.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/counter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/counter.pdb" /machine:I386 /out:"$(OUTDIR)/counter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CPerformanceData.obj" \
	"$(INTDIR)\test.obj" \
	"..\..\LIB\WINDEBUG\WFC.lib"

"$(OUTDIR)\counter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\counter.exe"

CLEAN : 
	-@erase "$(INTDIR)\CPerformanceData.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\counter.exe"
	-@erase "$(OUTDIR)\counter.ilk"
	-@erase "$(OUTDIR)\counter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/counter.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/counter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/counter.pdb" /debug /machine:I386 /out:"$(OUTDIR)/counter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CPerformanceData.obj" \
	"$(INTDIR)\test.obj" \
	"..\..\LIB\WINDEBUG\WFC.lib"

"$(OUTDIR)\counter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "counter - Win32 Release"
# Name "counter - Win32 Debug"

!IF  "$(CFG)" == "counter - Win32 Release"

!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CPerformanceData.cpp

!IF  "$(CFG)" == "counter - Win32 Release"

DEP_CPP_CPERF=\
	"..\..\include\wfctrace.hpp"\
	".\..\..\include\samtf.h"\
	".\counter.h"\
	".\CPCD.hpp"\
	".\CPerfDef.hpp"\
	".\CPerformanceData.hpp"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CFileTime.hpp"\
	"\wfc\include\CNetConn.hpp"\
	"\wfc\include\CNetFile.hpp"\
	"\wfc\include\CNetInfo.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	"\wfc\include\CNetSess.hpp"\
	"\wfc\include\CNetShar.hpp"\
	"\wfc\include\CNetWkst.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\CPing.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CService.hpp"\
	"\wfc\include\CSMTF.hpp"\
	"\wfc\include\CSquigl.hpp"\
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CSystemTime.hpp"\
	"\wfc\include\CTape.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\DrawGrid.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\Pager.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\SkyWord.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\SprintSpectrum.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\CPerformanceData.obj" : $(SOURCE) $(DEP_CPP_CPERF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

DEP_CPP_CPERF=\
	"..\..\include\wfctrace.hpp"\
	".\..\..\include\samtf.h"\
	".\counter.h"\
	".\CPCD.hpp"\
	".\CPerfDef.hpp"\
	".\CPerformanceData.hpp"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CFileTime.hpp"\
	"\wfc\include\CNetConn.hpp"\
	"\wfc\include\CNetFile.hpp"\
	"\wfc\include\CNetInfo.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	"\wfc\include\CNetSess.hpp"\
	"\wfc\include\CNetShar.hpp"\
	"\wfc\include\CNetWkst.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\CPing.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CService.hpp"\
	"\wfc\include\CSMTF.hpp"\
	"\wfc\include\CSquigl.hpp"\
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CSystemTime.hpp"\
	"\wfc\include\CTape.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\DrawGrid.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\Pager.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\SkyWord.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\SprintSpectrum.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\CPerformanceData.obj" : $(SOURCE) $(DEP_CPP_CPERF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\test.cpp

!IF  "$(CFG)" == "counter - Win32 Release"

DEP_CPP_TEST_=\
	"..\..\include\wfctrace.hpp"\
	".\..\..\include\samtf.h"\
	".\counter.h"\
	".\CPCD.hpp"\
	".\CPerfDef.hpp"\
	".\CPerformanceData.hpp"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CFileTime.hpp"\
	"\wfc\include\CNetConn.hpp"\
	"\wfc\include\CNetFile.hpp"\
	"\wfc\include\CNetInfo.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	"\wfc\include\CNetSess.hpp"\
	"\wfc\include\CNetShar.hpp"\
	"\wfc\include\CNetWkst.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\CPing.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CService.hpp"\
	"\wfc\include\CSMTF.hpp"\
	"\wfc\include\CSquigl.hpp"\
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CSystemTime.hpp"\
	"\wfc\include\CTape.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\DrawGrid.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\Pager.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\SkyWord.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\SprintSpectrum.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

DEP_CPP_TEST_=\
	"..\..\include\wfctrace.hpp"\
	".\..\..\include\samtf.h"\
	".\counter.h"\
	".\CPCD.hpp"\
	".\CPerfDef.hpp"\
	".\CPerformanceData.hpp"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
	"\wfc\include\CFileTime.hpp"\
	"\wfc\include\CNetConn.hpp"\
	"\wfc\include\CNetFile.hpp"\
	"\wfc\include\CNetInfo.hpp"\
	"\wfc\include\CNetRsrc.hpp"\
	"\wfc\include\CNetSess.hpp"\
	"\wfc\include\CNetShar.hpp"\
	"\wfc\include\CNetWkst.hpp"\
	"\wfc\include\CNetwork.hpp"\
	"\wfc\include\cnmpipe.hpp"\
	"\wfc\include\CPing.hpp"\
	"\wfc\include\CRAS.hpp"\
	"\wfc\include\CRegisty.hpp"\
	"\wfc\include\CServer.hpp"\
	"\wfc\include\CService.hpp"\
	"\wfc\include\CSMTF.hpp"\
	"\wfc\include\CSquigl.hpp"\
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CSystemTime.hpp"\
	"\wfc\include\CTape.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\DrawGrid.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\Pager.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\SkyWord.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\SprintSpectrum.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\test.obj" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\LIB\WINDEBUG\WFC.lib

!IF  "$(CFG)" == "counter - Win32 Release"

!ELSEIF  "$(CFG)" == "counter - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
