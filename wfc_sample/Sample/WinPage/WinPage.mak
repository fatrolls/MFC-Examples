# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=WinPage - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WinPage - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WinPage - Win32 Release" && "$(CFG)" !=\
 "WinPage - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinPage.mak" CFG="WinPage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinPage - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinPage - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "WinPage - Win32 Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "WinPage - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\WinPage.exe"

CLEAN : 
	-@erase "$(INTDIR)\WinPage.obj"
	-@erase "$(INTDIR)\WinPage.res"
	-@erase "$(INTDIR)\WinPageDlg.obj"
	-@erase "$(OUTDIR)\WinPage.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/WinPage.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinPage.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinPage.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \wfc\lib\WinRel\wfc.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=\wfc\lib\WinRel\wfc.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/WinPage.pdb" /machine:I386 /out:"$(OUTDIR)/WinPage.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WinPage.obj" \
	"$(INTDIR)\WinPage.res" \
	"$(INTDIR)\WinPageDlg.obj"

"$(OUTDIR)\WinPage.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WinPage - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\WinPage.exe"

CLEAN : 
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinPage.obj"
	-@erase "$(INTDIR)\WinPage.res"
	-@erase "$(INTDIR)\WinPageDlg.obj"
	-@erase "$(OUTDIR)\WinPage.exe"
	-@erase "$(OUTDIR)\WinPage.ilk"
	-@erase "$(OUTDIR)\WinPage.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/WinPage.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinPage.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinPage.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 \wfc\lib\WinDebug\wfc.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=\wfc\lib\WinDebug\wfc.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/WinPage.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/WinPage.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WinPage.obj" \
	"$(INTDIR)\WinPage.res" \
	"$(INTDIR)\WinPageDlg.obj"

"$(OUTDIR)\WinPage.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "WinPage - Win32 Release"
# Name "WinPage - Win32 Debug"

!IF  "$(CFG)" == "WinPage - Win32 Release"

!ELSEIF  "$(CFG)" == "WinPage - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "WinPage - Win32 Release"

!ELSEIF  "$(CFG)" == "WinPage - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinPage.cpp

!IF  "$(CFG)" == "WinPage - Win32 Release"

DEP_CPP_WINPA=\
	".\WinPage.h"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\WinPage.obj" : $(SOURCE) $(DEP_CPP_WINPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinPage - Win32 Debug"

DEP_CPP_WINPA=\
	"..\..\include\samtf.h"\
	"..\..\include\wfctrace.hpp"\
	".\WinPage.h"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
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
	"\wfc\include\CSvcMgr.hpp"\
	"\wfc\include\CUNC.hpp"\
	"\wfc\include\CURL.hpp"\
	"\wfc\include\dcb.hpp"\
	"\wfc\include\DrawObj.hpp"\
	"\wfc\include\DumyFile.hpp"\
	"\wfc\include\lsockets.hpp"\
	"\wfc\include\lzfile.hpp"\
	"\wfc\include\Modem.hpp"\
	"\wfc\include\Ovrlpd.hpp"\
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\WinPage.obj" : $(SOURCE) $(DEP_CPP_WINPA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinPageDlg.cpp

!IF  "$(CFG)" == "WinPage - Win32 Release"

DEP_CPP_WINPAG=\
	"..\..\include\samtf.h"\
	"..\..\include\wfctrace.hpp"\
	".\WinPage.h"\
	".\WinPageDlg.h"\
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
	

"$(INTDIR)\WinPageDlg.obj" : $(SOURCE) $(DEP_CPP_WINPAG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinPage - Win32 Debug"

DEP_CPP_WINPAG=\
	"..\..\include\samtf.h"\
	"..\..\include\wfctrace.hpp"\
	".\WinPage.h"\
	"\wfc\include\CBubble.hpp"\
	"\wfc\include\CEvntLog.hpp"\
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
	"\wfc\include\CSvcMgr.hpp"\
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
	"\wfc\include\Serial.hpp"\
	"\wfc\include\ServiceConfiguration.hpp"\
	"\wfc\include\sockets.hpp"\
	"\wfc\include\SockFile.hpp"\
	"\wfc\include\Structs.hpp"\
	"\wfc\include\tsockets.hpp"\
	"\wfc\include\wfc.h"\
	

"$(INTDIR)\WinPageDlg.obj" : $(SOURCE) $(DEP_CPP_WINPAG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinPage.rc
DEP_RSC_WINPAGE=\
	".\res\WinPage.ico"\
	".\res\WinPage.rc2"\
	

"$(INTDIR)\WinPage.res" : $(SOURCE) $(DEP_RSC_WINPAGE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
