# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=nettools - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to nettools - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nettools - Win32 Release" && "$(CFG)" !=\
 "nettools - Win32 Debug" && "$(CFG)" != "nettools - Win32 Release with info "
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "nettools.mak" CFG="nettools - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nettools - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nettools - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "nettools - Win32 Release with info " (based on\
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
# PROP Target_Last_Scanned "nettools - Win32 Release"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "nettools - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\nettools.exe"

CLEAN : 
	-@erase "$(INTDIR)\InetThread.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NetstatDlg.obj"
	-@erase "$(INTDIR)\nettools.obj"
	-@erase "$(INTDIR)\nettools.pch"
	-@erase "$(INTDIR)\nettools.res"
	-@erase "$(INTDIR)\PingDlg.obj"
	-@erase "$(INTDIR)\PingThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\nettools.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Ot /Oi
CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/nettools.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/nettools.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib snmpapi.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=wsock32.lib snmpapi.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/nettools.pdb" /machine:I386 /out:"$(OUTDIR)/nettools.exe" 
LINK32_OBJS= \
	"$(INTDIR)\InetThread.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NetstatDlg.obj" \
	"$(INTDIR)\nettools.obj" \
	"$(INTDIR)\nettools.res" \
	"$(INTDIR)\PingDlg.obj" \
	"$(INTDIR)\PingThread.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\nettools.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\nettools.exe"

CLEAN : 
	-@erase "$(INTDIR)\InetThread.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NetstatDlg.obj"
	-@erase "$(INTDIR)\nettools.obj"
	-@erase "$(INTDIR)\nettools.pch"
	-@erase "$(INTDIR)\nettools.res"
	-@erase "$(INTDIR)\PingDlg.obj"
	-@erase "$(INTDIR)\PingThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\nettools.exe"
	-@erase "$(OUTDIR)\nettools.ilk"
	-@erase "$(OUTDIR)\nettools.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/nettools.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/nettools.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 wsock32.lib snmpapi.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=wsock32.lib snmpapi.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/nettools.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/nettools.exe" 
LINK32_OBJS= \
	"$(INTDIR)\InetThread.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NetstatDlg.obj" \
	"$(INTDIR)\nettools.obj" \
	"$(INTDIR)\nettools.res" \
	"$(INTDIR)\PingDlg.obj" \
	"$(INTDIR)\PingThread.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\nettools.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nettools"
# PROP BASE Intermediate_Dir "nettools"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "nettools"
# PROP Intermediate_Dir "nettools"
# PROP Target_Dir ""
OUTDIR=.\nettools
INTDIR=.\nettools

ALL : ".\Release\nettools.exe"

CLEAN : 
	-@erase "$(INTDIR)\InetThread.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NetstatDlg.obj"
	-@erase "$(INTDIR)\nettools.obj"
	-@erase "$(INTDIR)\nettools.pch"
	-@erase "$(INTDIR)\nettools.res"
	-@erase "$(INTDIR)\PingDlg.obj"
	-@erase "$(INTDIR)\PingThread.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\nettools.pdb"
	-@erase ".\Release\nettools.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Ot /Oi
# ADD CPP /nologo /MD /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Ot /Oi
CPP_PROJ=/nologo /MD /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\nettools/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/nettools.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/nettools.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 wsock32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib snmpapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Release/nettools.exe"
LINK32_FLAGS=wsock32.lib snmpapi.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/nettools.pdb" /debug /machine:I386 /out:"Release/nettools.exe" 
LINK32_OBJS= \
	"$(INTDIR)\InetThread.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NetstatDlg.obj" \
	"$(INTDIR)\nettools.obj" \
	"$(INTDIR)\nettools.res" \
	"$(INTDIR)\PingDlg.obj" \
	"$(INTDIR)\PingThread.obj" \
	"$(INTDIR)\StdAfx.obj"

".\Release\nettools.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "nettools - Win32 Release"
# Name "nettools - Win32 Debug"
# Name "nettools - Win32 Release with info "

!IF  "$(CFG)" == "nettools - Win32 Release"

!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"

!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "nettools - Win32 Release"

!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"

!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\nettools.cpp
DEP_CPP_NETTO=\
	".\InetThread.h"\
	".\InetThreadParms.h"\
	".\MainFrm.h"\
	".\nettools.h"\
	".\PingParmList.h"\
	".\PingThread.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\nettools.obj" : $(SOURCE) $(DEP_CPP_NETTO) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\nettools.obj" : $(SOURCE) $(DEP_CPP_NETTO) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\nettools.obj" : $(SOURCE) $(DEP_CPP_NETTO) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL"\
 /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\nettools.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\nettools.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Zi /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/nettools.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\nettools.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\InetThread.h"\
	".\InetThreadParms.h"\
	".\MainFrm.h"\
	".\NetstatDlg.h"\
	".\nettools.h"\
	".\PingDlg.h"\
	".\PingParmList.h"\
	".\PingThread.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\nettools.rc
DEP_RSC_NETTOO=\
	".\res\nettools.ico"\
	".\res\nettools.rc2"\
	".\res\nettoolsDoc.ico"\
	".\res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\nettools.res" : $(SOURCE) $(DEP_RSC_NETTOO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\nettools.res" : $(SOURCE) $(DEP_RSC_NETTOO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\nettools.res" : $(SOURCE) $(DEP_RSC_NETTOO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NetstatDlg.cpp
DEP_CPP_NETST=\
	".\InetThreadParms.h"\
	".\NetstatDlg.h"\
	".\nettools.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\NetstatDlg.obj" : $(SOURCE) $(DEP_CPP_NETST) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\NetstatDlg.obj" : $(SOURCE) $(DEP_CPP_NETST) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\NetstatDlg.obj" : $(SOURCE) $(DEP_CPP_NETST) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PingThread.cpp
DEP_CPP_PINGT=\
	".\ipexport.h"\
	".\nettools.h"\
	".\PingParmList.h"\
	".\PingThread.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\PingThread.obj" : $(SOURCE) $(DEP_CPP_PINGT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\PingThread.obj" : $(SOURCE) $(DEP_CPP_PINGT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\PingThread.obj" : $(SOURCE) $(DEP_CPP_PINGT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PingDlg.cpp
DEP_CPP_PINGD=\
	".\nettools.h"\
	".\PingDlg.h"\
	".\PingParmList.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\PingDlg.obj" : $(SOURCE) $(DEP_CPP_PINGD) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\PingDlg.obj" : $(SOURCE) $(DEP_CPP_PINGD) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\PingDlg.obj" : $(SOURCE) $(DEP_CPP_PINGD) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\InetThread.cpp
DEP_CPP_INETT=\
	".\InetThread.h"\
	".\InetThreadParms.h"\
	".\nettools.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "nettools - Win32 Release"


"$(INTDIR)\InetThread.obj" : $(SOURCE) $(DEP_CPP_INETT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Debug"


"$(INTDIR)\InetThread.obj" : $(SOURCE) $(DEP_CPP_INETT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ELSEIF  "$(CFG)" == "nettools - Win32 Release with info "


"$(INTDIR)\InetThread.obj" : $(SOURCE) $(DEP_CPP_INETT) "$(INTDIR)"\
 "$(INTDIR)\nettools.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
