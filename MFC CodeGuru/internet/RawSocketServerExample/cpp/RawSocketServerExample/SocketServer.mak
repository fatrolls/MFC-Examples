# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SocketServer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SocketServer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SocketServer - Win32 Release" && "$(CFG)" !=\
 "SocketServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SocketServer.mak" CFG="SocketServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SocketServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SocketServer - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SocketServer - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "SocketServer - Win32 Release"

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

ALL : "$(OUTDIR)\SocketServer.exe"

CLEAN : 
	-@erase "$(INTDIR)\ClosingDialog.obj"
	-@erase "$(INTDIR)\CRITSECT.OBJ"
	-@erase "$(INTDIR)\RawSocket.obj"
	-@erase "$(INTDIR)\RawSocketServerWorker.obj"
	-@erase "$(INTDIR)\SocketServer.obj"
	-@erase "$(INTDIR)\SocketServer.pch"
	-@erase "$(INTDIR)\SocketServer.res"
	-@erase "$(INTDIR)\SocketServerDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ThreadDispatcher.obj"
	-@erase "$(OUTDIR)\SocketServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "." /I "CommonFiles\Library" /I "CommonFiles\Lib32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "." /I "CommonFiles\Library" /I\
 "CommonFiles\Lib32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/SocketServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SocketServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SocketServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/SocketServer.pdb" /machine:I386\
 /out:"$(OUTDIR)/SocketServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ClosingDialog.obj" \
	"$(INTDIR)\CRITSECT.OBJ" \
	"$(INTDIR)\RawSocket.obj" \
	"$(INTDIR)\RawSocketServerWorker.obj" \
	"$(INTDIR)\SocketServer.obj" \
	"$(INTDIR)\SocketServer.res" \
	"$(INTDIR)\SocketServerDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDispatcher.obj"

"$(OUTDIR)\SocketServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"

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

ALL : "$(OUTDIR)\SocketServer.exe" "$(OUTDIR)\SocketServer.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ClosingDialog.obj"
	-@erase "$(INTDIR)\ClosingDialog.sbr"
	-@erase "$(INTDIR)\CRITSECT.OBJ"
	-@erase "$(INTDIR)\CRITSECT.SBR"
	-@erase "$(INTDIR)\RawSocket.obj"
	-@erase "$(INTDIR)\RawSocket.sbr"
	-@erase "$(INTDIR)\RawSocketServerWorker.obj"
	-@erase "$(INTDIR)\RawSocketServerWorker.sbr"
	-@erase "$(INTDIR)\SocketServer.obj"
	-@erase "$(INTDIR)\SocketServer.pch"
	-@erase "$(INTDIR)\SocketServer.res"
	-@erase "$(INTDIR)\SocketServer.sbr"
	-@erase "$(INTDIR)\SocketServerDlg.obj"
	-@erase "$(INTDIR)\SocketServerDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\ThreadDispatcher.obj"
	-@erase "$(INTDIR)\ThreadDispatcher.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SocketServer.bsc"
	-@erase "$(OUTDIR)\SocketServer.exe"
	-@erase "$(OUTDIR)\SocketServer.ilk"
	-@erase "$(OUTDIR)\SocketServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "." /I "CommonFiles\Library" /I "CommonFiles\Lib32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "." /I "CommonFiles\Library" /I\
 "CommonFiles\Lib32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/SocketServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SocketServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SocketServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ClosingDialog.sbr" \
	"$(INTDIR)\CRITSECT.SBR" \
	"$(INTDIR)\RawSocket.sbr" \
	"$(INTDIR)\RawSocketServerWorker.sbr" \
	"$(INTDIR)\SocketServer.sbr" \
	"$(INTDIR)\SocketServerDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\ThreadDispatcher.sbr"

"$(OUTDIR)\SocketServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/SocketServer.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/SocketServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ClosingDialog.obj" \
	"$(INTDIR)\CRITSECT.OBJ" \
	"$(INTDIR)\RawSocket.obj" \
	"$(INTDIR)\RawSocketServerWorker.obj" \
	"$(INTDIR)\SocketServer.obj" \
	"$(INTDIR)\SocketServer.res" \
	"$(INTDIR)\SocketServerDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ThreadDispatcher.obj"

"$(OUTDIR)\SocketServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SocketServer - Win32 Release"
# Name "SocketServer - Win32 Debug"

!IF  "$(CFG)" == "SocketServer - Win32 Release"

!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SocketServer.cpp

!IF  "$(CFG)" == "SocketServer - Win32 Release"

DEP_CPP_SOCKE=\
	".\CommonFiles\Lib32\critsect.h"\
	".\CommonFiles\Library\RawSocket.h"\
	".\CommonFiles\Library\RawSocketServerWorker.h"\
	".\CommonFiles\Library\ThreadDispatcher.h"\
	".\SocketServer.h"\
	".\SocketServerDlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\SocketServer.obj" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"

DEP_CPP_SOCKE=\
	".\CommonFiles\Lib32\critsect.h"\
	".\CommonFiles\Library\RawSocket.h"\
	".\CommonFiles\Library\RawSocketServerWorker.h"\
	".\CommonFiles\Library\ThreadDispatcher.h"\
	".\SocketServer.h"\
	".\SocketServerDlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\SocketServer.obj" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"

"$(INTDIR)\SocketServer.sbr" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SocketServerDlg.cpp
DEP_CPP_SOCKET=\
	".\ClosingDialog.h"\
	".\CommonFiles\Lib32\critsect.h"\
	".\CommonFiles\Library\RawSocket.h"\
	".\CommonFiles\Library\RawSocketServerWorker.h"\
	".\CommonFiles\Library\ThreadDispatcher.h"\
	".\names.h"\
	".\SocketServer.h"\
	".\SocketServerDlg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"


"$(INTDIR)\SocketServerDlg.obj" : $(SOURCE) $(DEP_CPP_SOCKET) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"


"$(INTDIR)\SocketServerDlg.obj" : $(SOURCE) $(DEP_CPP_SOCKET) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"

"$(INTDIR)\SocketServerDlg.sbr" : $(SOURCE) $(DEP_CPP_SOCKET) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "." /I "CommonFiles\Library" /I\
 "CommonFiles\Lib32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/SocketServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SocketServer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /I "." /I "CommonFiles\Library" /I\
 "CommonFiles\Lib32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/SocketServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SocketServer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SocketServer.rc
DEP_RSC_SOCKETS=\
	".\res\SocketServer.ico"\
	".\res\SocketServer.rc2"\
	

"$(INTDIR)\SocketServer.res" : $(SOURCE) $(DEP_RSC_SOCKETS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClosingDialog.cpp
DEP_CPP_CLOSI=\
	".\ClosingDialog.h"\
	".\SocketServer.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"


"$(INTDIR)\ClosingDialog.obj" : $(SOURCE) $(DEP_CPP_CLOSI) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"


"$(INTDIR)\ClosingDialog.obj" : $(SOURCE) $(DEP_CPP_CLOSI) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"

"$(INTDIR)\ClosingDialog.sbr" : $(SOURCE) $(DEP_CPP_CLOSI) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CommonFiles\Library\ThreadDispatcher.cpp
DEP_CPP_THREA=\
	".\CommonFiles\Library\ThreadDispatcher.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"


"$(INTDIR)\ThreadDispatcher.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ThreadDispatcher.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

"$(INTDIR)\ThreadDispatcher.sbr" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CommonFiles\Library\RawSocketServerWorker.cpp
DEP_CPP_RAWSO=\
	".\CommonFiles\Library\RawSocket.h"\
	".\CommonFiles\Library\RawSocketServerWorker.h"\
	".\CommonFiles\Library\ThreadDispatcher.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"


"$(INTDIR)\RawSocketServerWorker.obj" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RawSocketServerWorker.obj" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

"$(INTDIR)\RawSocketServerWorker.sbr" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CommonFiles\Lib32\CRITSECT.CPP
DEP_CPP_CRITS=\
	".\CommonFiles\Lib32\critsect.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SocketServer - Win32 Release"


"$(INTDIR)\CRITSECT.OBJ" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CRITSECT.OBJ" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

"$(INTDIR)\CRITSECT.SBR" : $(SOURCE) $(DEP_CPP_CRITS) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CommonFiles\Library\RawSocket.cpp

!IF  "$(CFG)" == "SocketServer - Win32 Release"

DEP_CPP_RAWSOC=\
	".\CommonFiles\Library\RawSocket.h"\
	".\stdafx.h"\
	

"$(INTDIR)\RawSocket.obj" : $(SOURCE) $(DEP_CPP_RAWSOC) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SocketServer - Win32 Debug"

DEP_CPP_RAWSOC=\
	".\CommonFiles\Library\RawSocket.h"\
	".\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RawSocket.obj" : $(SOURCE) $(DEP_CPP_RAWSOC) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

"$(INTDIR)\RawSocket.sbr" : $(SOURCE) $(DEP_CPP_RAWSOC) "$(INTDIR)"\
 "$(INTDIR)\SocketServer.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
