# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Wizard1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Wizard1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Wizard1 - Win32 Release" && "$(CFG)" !=\
 "Wizard1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wizard1.mak" CFG="Wizard1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wizard1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Wizard1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Wizard1 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Wizard1 - Win32 Release"

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

ALL : "$(OUTDIR)\Wizard1.exe"

CLEAN : 
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\Mainfram.obj"
	-@erase "$(INTDIR)\mainwnd.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\Page3.obj"
	-@erase "$(INTDIR)\Page4.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\Wizard1.obj"
	-@erase "$(INTDIR)\Wizard1.res"
	-@erase "$(OUTDIR)\Wizard1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Wizard1.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Wizard1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Wizard1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Wizard1.pdb" /machine:I386 /out:"$(OUTDIR)/Wizard1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\Mainfram.obj" \
	"$(INTDIR)\mainwnd.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\Page3.obj" \
	"$(INTDIR)\Page4.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\Wizard1.obj" \
	"$(INTDIR)\Wizard1.res"

"$(OUTDIR)\Wizard1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wizard1 - Win32 Debug"

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

ALL : "$(OUTDIR)\Wizard1.exe"

CLEAN : 
	-@erase "$(INTDIR)\IntroPg.obj"
	-@erase "$(INTDIR)\Mainfram.obj"
	-@erase "$(INTDIR)\mainwnd.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\Page3.obj"
	-@erase "$(INTDIR)\Page4.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\Wizard1.obj"
	-@erase "$(INTDIR)\Wizard1.res"
	-@erase "$(OUTDIR)\Wizard1.exe"
	-@erase "$(OUTDIR)\Wizard1.ilk"
	-@erase "$(OUTDIR)\Wizard1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Wizard1.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Wizard1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Wizard1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Wizard1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Wizard1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IntroPg.obj" \
	"$(INTDIR)\Mainfram.obj" \
	"$(INTDIR)\mainwnd.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\Page3.obj" \
	"$(INTDIR)\Page4.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\Wizard1.obj" \
	"$(INTDIR)\Wizard1.res"

"$(OUTDIR)\Wizard1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Wizard1 - Win32 Release"
# Name "Wizard1 - Win32 Debug"

!IF  "$(CFG)" == "Wizard1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Wizard1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Wizard1.rc
DEP_RSC_WIZAR=\
	".\doneflag.bmp"\
	".\food.bmp"\
	".\pc_earth.bmp"\
	".\question.bmp"\
	".\server.bmp"\
	".\wizard.bmp"\
	".\wizard1.ico"\
	

"$(INTDIR)\Wizard1.res" : $(SOURCE) $(DEP_RSC_WIZAR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.cpp
DEP_CPP_PAGE1=\
	".\Page1.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Page1.obj" : $(SOURCE) $(DEP_CPP_PAGE1) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.cpp
DEP_CPP_PAGE2=\
	".\page2.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Page2.obj" : $(SOURCE) $(DEP_CPP_PAGE2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page3.cpp
DEP_CPP_PAGE3=\
	".\page3.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Page3.obj" : $(SOURCE) $(DEP_CPP_PAGE3) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wizard1.cpp
DEP_CPP_WIZARD=\
	".\IntroPg.h"\
	".\mainwnd.h"\
	".\Page1.h"\
	".\page2.h"\
	".\page3.h"\
	".\Page4.h"\
	".\Wizard.h"\
	".\Wizard1.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\mainfram.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Wizard1.obj" : $(SOURCE) $(DEP_CPP_WIZARD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntroPg.cpp
DEP_CPP_INTRO=\
	".\IntroPg.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\IntroPg.obj" : $(SOURCE) $(DEP_CPP_INTRO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page4.cpp
DEP_CPP_PAGE4=\
	".\Page4.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Page4.obj" : $(SOURCE) $(DEP_CPP_PAGE4) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainwnd.cpp
DEP_CPP_MAINW=\
	".\IntroPg.h"\
	".\mainwnd.h"\
	".\Page1.h"\
	".\page2.h"\
	".\page3.h"\
	".\Page4.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\mainfram.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\mainwnd.obj" : $(SOURCE) $(DEP_CPP_MAINW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wizard.cpp
DEP_CPP_WIZARD_=\
	".\IntroPg.h"\
	".\mainwnd.h"\
	".\Page1.h"\
	".\page2.h"\
	".\page3.h"\
	".\Page4.h"\
	".\Wizard.h"\
	".\wizdata.h"\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\mainfram.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Wizard.obj" : $(SOURCE) $(DEP_CPP_WIZARD_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfram.cpp
DEP_CPP_MAINF=\
	{$(INCLUDE)}"\colors.h"\
	{$(INCLUDE)}"\mainfram.h"\
	{$(INCLUDE)}"\stdafx.h"\
	

"$(INTDIR)\Mainfram.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
