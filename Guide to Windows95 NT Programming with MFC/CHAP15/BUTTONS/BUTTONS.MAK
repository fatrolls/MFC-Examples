# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Buttons - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Buttons - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Buttons - Win32 Release" && "$(CFG)" !=\
 "Buttons - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Buttons.mak" CFG="Buttons - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Buttons - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Buttons - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Buttons - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Buttons - Win32 Release"

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

ALL : "$(OUTDIR)\Buttons.exe"

CLEAN : 
	-@erase "$(INTDIR)\Buttons.obj"
	-@erase "$(INTDIR)\buttons.res"
	-@erase "$(OUTDIR)\Buttons.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Buttons.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/buttons.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Buttons.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Buttons.pdb" /machine:I386 /out:"$(OUTDIR)/Buttons.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Buttons.obj" \
	"$(INTDIR)\buttons.res"

"$(OUTDIR)\Buttons.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Buttons - Win32 Debug"

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

ALL : "$(OUTDIR)\Buttons.exe"

CLEAN : 
	-@erase "$(INTDIR)\Buttons.obj"
	-@erase "$(INTDIR)\buttons.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Buttons.exe"
	-@erase "$(OUTDIR)\Buttons.ilk"
	-@erase "$(OUTDIR)\Buttons.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Buttons.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/buttons.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Buttons.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Buttons.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Buttons.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Buttons.obj" \
	"$(INTDIR)\buttons.res"

"$(OUTDIR)\Buttons.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Buttons - Win32 Release"
# Name "Buttons - Win32 Debug"

!IF  "$(CFG)" == "Buttons - Win32 Release"

!ELSEIF  "$(CFG)" == "Buttons - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Buttons.cpp

!IF  "$(CFG)" == "Buttons - Win32 Release"

DEP_CPP_BUTTO=\
	"..\..\CHAP12\MAINFRAM\colors.h"\
	"..\..\chap12\mainfram\mainfram.cpp"\
	"..\..\CHAP12\MAINFRAM\stdafx.h"\
	".\buttons.h"\
	".\resource.h"\
	{$(INCLUDE)}"\mainfram.h"\
	

"$(INTDIR)\Buttons.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Buttons - Win32 Debug"

DEP_CPP_BUTTO=\
	"..\..\CHAP12\MAINFRAM\colors.h"\
	"..\..\CHAP12\MAINFRAM\stdafx.h"\
	".\buttons.h"\
	".\resource.h"\
	{$(INCLUDE)}"\mainfram.h"\
	

"$(INTDIR)\Buttons.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\buttons.rc

!IF  "$(CFG)" == "Buttons - Win32 Release"

DEP_RSC_BUTTON=\
	".\bmp1dn.bmp"\
	".\bmp1up.bmp"\
	".\bmp2dn.bmp"\
	".\bmp2up.bmp"\
	".\bmp3dn.bmp"\
	".\bmp3up.bmp"\
	".\resource.h"\
	

"$(INTDIR)\buttons.res" : $(SOURCE) $(DEP_RSC_BUTTON) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Buttons - Win32 Debug"

DEP_RSC_BUTTON=\
	".\bmp1dn.bmp"\
	".\bmp1up.bmp"\
	".\bmp2dn.bmp"\
	".\bmp2up.bmp"\
	".\bmp3dn.bmp"\
	".\bmp3up.bmp"\
	

"$(INTDIR)\buttons.res" : $(SOURCE) $(DEP_RSC_BUTTON) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
