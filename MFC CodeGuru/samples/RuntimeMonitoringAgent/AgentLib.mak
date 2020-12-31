# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=AgentLib - Win32 Debug Static
!MESSAGE No configuration specified.  Defaulting to AgentLib - Win32 Debug\
 Static.
!ENDIF 

!IF "$(CFG)" != "AgentLib - Win32 Release" && "$(CFG)" !=\
 "AgentLib - Win32 Debug" && "$(CFG)" != "AgentLib - Win32 Debug Static" &&\
 "$(CFG)" != "AgentLib - Win32 Release Static"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "AgentLib.mak" CFG="AgentLib - Win32 Debug Static"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AgentLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AgentLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AgentLib - Win32 Debug Static" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "AgentLib - Win32 Release Static" (based on\
 "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "AgentLib - Win32 Release Static"
CPP=cl.exe

!IF  "$(CFG)" == "AgentLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Release

ALL : "$(OUTDIR)\AgMTDLL.lib"

CLEAN : 
	-@erase "$(INTDIR)\AgentLib.obj"
	-@erase "$(OUTDIR)\AgMTDLL.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /Zp1 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Gz /Zp1 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/AgentLib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AgentLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"AgMTDLL.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AgMTDLL.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AgentLib.obj"

"$(OUTDIR)\AgMTDLL.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Debug

ALL : "$(OUTDIR)\AgDMTDLL.lib"

CLEAN : 
	-@erase "$(INTDIR)\AgentLib.obj"
	-@erase "$(OUTDIR)\AgDMTDLL.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp1 /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/AgentLib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AgentLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"AgDMTDLL.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AgDMTDLL.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AgentLib.obj"

"$(OUTDIR)\AgDMTDLL.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AgentLib"
# PROP BASE Intermediate_Dir "AgentLib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Debug

ALL : "$(OUTDIR)\AgDMT.lib"

CLEAN : 
	-@erase "$(INTDIR)\AgentLib.obj"
	-@erase "$(OUTDIR)\AgDMT.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /Zp1 /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp1 /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/AgentLib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AgentLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"AgentDMT.lib"
# ADD LIB32 /nologo /out:"AgDMT.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AgDMT.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AgentLib.obj"

"$(OUTDIR)\AgDMT.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AgentLi0"
# PROP BASE Intermediate_Dir "AgentLi0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Release

ALL : "$(OUTDIR)\AgMT.lib"

CLEAN : 
	-@erase "$(INTDIR)\AgentLib.obj"
	-@erase "$(OUTDIR)\AgMT.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /Gz /Zp1 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Gz /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Gz /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/AgentLib.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AgentLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"AgentMT.lib"
# ADD LIB32 /nologo /out:"AgMT.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/AgMT.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AgentLib.obj"

"$(OUTDIR)\AgMT.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "AgentLib - Win32 Release"
# Name "AgentLib - Win32 Debug"
# Name "AgentLib - Win32 Debug Static"
# Name "AgentLib - Win32 Release Static"

!IF  "$(CFG)" == "AgentLib - Win32 Release"

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug"

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug Static"

!ELSEIF  "$(CFG)" == "AgentLib - Win32 Release Static"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AgentLib.cpp
DEP_CPP_AGENT=\
	{$(INCLUDE)}"\AgentDll.h"\
	{$(INCLUDE)}"\AgentLib.h"\
	

!IF  "$(CFG)" == "AgentLib - Win32 Release"


"$(INTDIR)\AgentLib.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug"


"$(INTDIR)\AgentLib.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AgentLib - Win32 Debug Static"


"$(INTDIR)\AgentLib.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AgentLib - Win32 Release Static"


"$(INTDIR)\AgentLib.obj" : $(SOURCE) $(DEP_CPP_AGENT) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
