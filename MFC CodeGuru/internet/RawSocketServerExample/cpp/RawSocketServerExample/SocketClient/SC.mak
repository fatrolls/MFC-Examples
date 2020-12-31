# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=SC - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SC - Win32 Release" && "$(CFG)" != "SC - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SC.mak" CFG="SC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SC - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SC - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "SC - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "SC - Win32 Release"

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

ALL : "$(OUTDIR)\SC.exe"

CLEAN : 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\RawSocket.obj"
	-@erase "$(INTDIR)\SC.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\SC.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "CommonFiles\Library" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "CommonFiles\Library" /D "WIN32"\
 /D "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/SC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)/SC.pdb"\
 /machine:I386 /out:"$(OUTDIR)/SC.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\RawSocket.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SC___Win"
# PROP BASE Intermediate_Dir "SC___Win"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\SC.exe" "$(OUTDIR)\SC.bsc"

CLEAN : 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\RawSocket.obj"
	-@erase "$(INTDIR)\RawSocket.sbr"
	-@erase "$(INTDIR)\SC.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SC.bsc"
	-@erase "$(OUTDIR)\SC.exe"
	-@erase "$(OUTDIR)\SC.ilk"
	-@erase "$(OUTDIR)\SC.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /I "CommonFiles\Library" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /I "CommonFiles\Library" /D\
 "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SC.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SC.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\RawSocket.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SC.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/SC.pdb" /debug /machine:I386 /out:"$(OUTDIR)/SC.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\RawSocket.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SC - Win32 Release"
# Name "SC - Win32 Debug"

!IF  "$(CFG)" == "SC - Win32 Release"

!ELSEIF  "$(CFG)" == "SC - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SC - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MT /W3 /GX /O2 /Ob2 /I "CommonFiles\Library" /D "WIN32" /D\
 "NDEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/SC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SC.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SC - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /I "CommonFiles\Library" /D\
 "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SC.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SC.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	"..\..\SocketServer\names.h"\
	".\CommonFiles\Library\RawSocket.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "SC - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"


!ELSEIF  "$(CFG)" == "SC - Win32 Debug"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"

"$(INTDIR)\main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CommonFiles\Library\RawSocket.cpp
DEP_CPP_RAWSO=\
	".\CommonFiles\Library\RawSocket.h"\
	
NODEP_CPP_RAWSO=\
	".\CommonFiles\Library\stdafx.h"\
	

!IF  "$(CFG)" == "SC - Win32 Release"


"$(INTDIR)\RawSocket.obj" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RawSocket.obj" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"
   $(BuildCmds)

"$(INTDIR)\RawSocket.sbr" : $(SOURCE) $(DEP_CPP_RAWSO) "$(INTDIR)"\
 "$(INTDIR)\SC.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
