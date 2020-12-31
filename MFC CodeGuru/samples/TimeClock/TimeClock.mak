# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TimeClock - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TimeClock - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TimeClock - Win32 Release" && "$(CFG)" !=\
 "TimeClock - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TimeClock.mak" CFG="TimeClock - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TimeClock - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TimeClock - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TimeClock - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TimeClock - Win32 Release"

# PROP BASE Use_MFC 6
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

ALL : "$(OUTDIR)\TimeClock.exe" "$(OUTDIR)\TimeClock.tlb"\
 "$(OUTDIR)\TimeClock.bsc"

CLEAN : 
	-@erase ".\Release\TimeClock.tlb"
	-@erase ".\Release\TimeClock.bsc"
	-@erase ".\Release\StdAfx.sbr"
	-@erase ".\Release\TimeClock.sbr"
	-@erase ".\Release\TimeClock.pch"
	-@erase ".\Release\TimeClockDlg.sbr"
	-@erase ".\Release\TimeClock.exe"
	-@erase ".\Release\TimeClockDlg.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\TimeClock.obj"
	-@erase ".\Release\TimeClock.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/TimeClock.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TimeClock.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TimeClock.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/TimeClock.sbr" \
	"$(INTDIR)/TimeClockDlg.sbr"

"$(OUTDIR)\TimeClock.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TimeClock.pdb" /machine:I386 /out:"$(OUTDIR)/TimeClock.exe" 
LINK32_OBJS= \
	"$(INTDIR)/TimeClockDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TimeClock.obj" \
	"$(INTDIR)/TimeClock.res"

"$(OUTDIR)\TimeClock.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"

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

ALL : "$(OUTDIR)\TimeClock.exe" "$(OUTDIR)\TimeClock.tlb"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\TimeClock.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\TimeClock.tlb"
	-@erase ".\Debug\TimeClock.exe"
	-@erase ".\Debug\TimeClock.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\TimeClockDlg.obj"
	-@erase ".\Debug\TimeClock.res"
	-@erase ".\Debug\TimeClock.ilk"
	-@erase ".\Debug\TimeClock.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TimeClock.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TimeClock.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TimeClock.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TimeClock.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/TimeClock.exe" 
LINK32_OBJS= \
	"$(INTDIR)/TimeClock.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TimeClockDlg.obj" \
	"$(INTDIR)/TimeClock.res"

"$(OUTDIR)\TimeClock.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TimeClock - Win32 Release"
# Name "TimeClock - Win32 Debug"

!IF  "$(CFG)" == "TimeClock - Win32 Release"

!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TimeClock - Win32 Release"

!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeClock.cpp
DEP_CPP_TIMEC=\
	".\StdAfx.h"\
	".\TimeClock.h"\
	".\TimeClockDlg.h"\
	

!IF  "$(CFG)" == "TimeClock - Win32 Release"


"$(INTDIR)\TimeClock.obj" : $(SOURCE) $(DEP_CPP_TIMEC) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"

"$(INTDIR)\TimeClock.sbr" : $(SOURCE) $(DEP_CPP_TIMEC) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"


!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"


"$(INTDIR)\TimeClock.obj" : $(SOURCE) $(DEP_CPP_TIMEC) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeClockDlg.cpp

!IF  "$(CFG)" == "TimeClock - Win32 Release"

DEP_CPP_TIMECL=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\TimeClock.h"\
	".\TimeClockDlg.h"\
	
NODEP_CPP_TIMECL=\
	".\{"\
	

"$(INTDIR)\TimeClockDlg.obj" : $(SOURCE) $(DEP_CPP_TIMECL) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"

"$(INTDIR)\TimeClockDlg.sbr" : $(SOURCE) $(DEP_CPP_TIMECL) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"


!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"

DEP_CPP_TIMECL=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\TimeClock.h"\
	".\TimeClockDlg.h"\
	

"$(INTDIR)\TimeClockDlg.obj" : $(SOURCE) $(DEP_CPP_TIMECL) "$(INTDIR)"\
 "$(INTDIR)\TimeClock.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeClock.odl

!IF  "$(CFG)" == "TimeClock - Win32 Release"


"$(OUTDIR)\TimeClock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/TimeClock.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"


"$(OUTDIR)\TimeClock.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/TimeClock.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TimeClock - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/TimeClock.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TimeClock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TimeClock.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TimeClock.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeClock.rc
DEP_RSC_TIMECLO=\
	".\res\TimeClock.ico"\
	".\res\in.ico"\
	".\res\out.ico"\
	".\res\icon1.ico"\
	".\res\TimeClock.rc2"\
	

!IF  "$(CFG)" == "TimeClock - Win32 Release"


"$(INTDIR)\TimeClock.res" : $(SOURCE) $(DEP_RSC_TIMECLO) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/TimeClock.res" /i "Release" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "TimeClock - Win32 Debug"


"$(INTDIR)\TimeClock.res" : $(SOURCE) $(DEP_RSC_TIMECLO) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/TimeClock.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
