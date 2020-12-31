# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DllTest1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DllTest1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DllTest1 - Win32 Release" && "$(CFG)" !=\
 "DllTest1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dlltest1.mak" CFG="DllTest1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DllTest1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DllTest1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DllTest1 - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DllTest1 - Win32 Release"

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

ALL : "$(OUTDIR)\Dlltest1.exe"

CLEAN : 
	-@erase "$(INTDIR)\Dlltest1.obj"
	-@erase "$(INTDIR)\DllTest1.res"
	-@erase "$(OUTDIR)\Dlltest1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dlltest1.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DllTest1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dlltest1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Dlltest1.pdb" /machine:I386 /out:"$(OUTDIR)/Dlltest1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dlltest1.obj" \
	"$(INTDIR)\DllTest1.res" \
	".\Dynlink2.lib" \
	".\Dynlink3.lib"

"$(OUTDIR)\Dlltest1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DllTest1 - Win32 Debug"

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

ALL : "$(OUTDIR)\Dlltest1.exe"

CLEAN : 
	-@erase "$(INTDIR)\Dlltest1.obj"
	-@erase "$(INTDIR)\DllTest1.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Dlltest1.exe"
	-@erase "$(OUTDIR)\Dlltest1.ilk"
	-@erase "$(OUTDIR)\Dlltest1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dlltest1.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DllTest1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dlltest1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Dlltest1.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Dlltest1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dlltest1.obj" \
	"$(INTDIR)\DllTest1.res" \
	".\Dynlink2.lib" \
	".\Dynlink3.lib"

"$(OUTDIR)\Dlltest1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DllTest1 - Win32 Release"
# Name "DllTest1 - Win32 Debug"

!IF  "$(CFG)" == "DllTest1 - Win32 Release"

!ELSEIF  "$(CFG)" == "DllTest1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dlltest1.cpp

!IF  "$(CFG)" == "DllTest1 - Win32 Release"

DEP_CPP_DLLTE=\
	"..\..\chap12\mainfram\mainfram.cpp"\
	"..\..\chap12\mainfram\mainfram.h"\
	".\Dlldlg.h"\
	".\Dlltest1.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Dlltest1.obj" : $(SOURCE) $(DEP_CPP_DLLTE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DllTest1 - Win32 Debug"

# PROP Exclude_From_Build 0
DEP_CPP_DLLTE=\
	"..\..\chap12\mainfram\mainfram.h"\
	".\Dlldlg.h"\
	".\Dlltest1.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Dlltest1.obj" : $(SOURCE) $(DEP_CPP_DLLTE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DllTest1.rc
DEP_RSC_DLLTES=\
	".\Chemical.ico"\
	

"$(INTDIR)\DllTest1.res" : $(SOURCE) $(DEP_RSC_DLLTES) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dynlink3.lib

!IF  "$(CFG)" == "DllTest1 - Win32 Release"

!ELSEIF  "$(CFG)" == "DllTest1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dynlink2.lib

!IF  "$(CFG)" == "DllTest1 - Win32 Release"

!ELSEIF  "$(CFG)" == "DllTest1 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
