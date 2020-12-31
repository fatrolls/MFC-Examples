# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=RawHtml - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to RawHtml - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "RawHtml - Win32 Release" && "$(CFG)" !=\
 "RawHtml - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rawhtml.mak" CFG="RawHtml - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RawHtml - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RawHtml - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "RawHtml - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "RawHtml - Win32 Release"

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

ALL : "$(OUTDIR)\Rawhtml.exe"

CLEAN : 
	-@erase "$(INTDIR)\Htmldlg.obj"
	-@erase "$(INTDIR)\Rawhtml.obj"
	-@erase "$(INTDIR)\Rawhtml.res"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(OUTDIR)\Rawhtml.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Rawhtml.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Rawhtml.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Rawhtml.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Rawhtml.pdb" /machine:I386 /out:"$(OUTDIR)/Rawhtml.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Htmldlg.obj" \
	"$(INTDIR)\Rawhtml.obj" \
	"$(INTDIR)\Rawhtml.res" \
	"$(INTDIR)\Stdafx.obj" \
	"D:\INetSDK\Lib\Wininet.lib"

"$(OUTDIR)\Rawhtml.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"

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

ALL : "$(OUTDIR)\Rawhtml.exe" "$(OUTDIR)\Rawhtml.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Htmldlg.obj"
	-@erase "$(INTDIR)\Htmldlg.sbr"
	-@erase "$(INTDIR)\Rawhtml.obj"
	-@erase "$(INTDIR)\Rawhtml.res"
	-@erase "$(INTDIR)\Rawhtml.sbr"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Stdafx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Rawhtml.bsc"
	-@erase "$(OUTDIR)\Rawhtml.exe"
	-@erase "$(OUTDIR)\Rawhtml.ilk"
	-@erase "$(OUTDIR)\Rawhtml.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Rawhtml.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Rawhtml.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Rawhtml.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Htmldlg.sbr" \
	"$(INTDIR)\Rawhtml.sbr" \
	"$(INTDIR)\Stdafx.sbr"

"$(OUTDIR)\Rawhtml.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Rawhtml.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Rawhtml.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Htmldlg.obj" \
	"$(INTDIR)\Rawhtml.obj" \
	"$(INTDIR)\Rawhtml.res" \
	"$(INTDIR)\Stdafx.obj" \
	"D:\INetSDK\Lib\Wininet.lib"

"$(OUTDIR)\Rawhtml.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "RawHtml - Win32 Release"
# Name "RawHtml - Win32 Debug"

!IF  "$(CFG)" == "RawHtml - Win32 Release"

!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Rawhtml.rc
DEP_RSC_RAWHT=\
	".\RawHtml.ico"\
	

"$(INTDIR)\Rawhtml.res" : $(SOURCE) $(DEP_RSC_RAWHT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rawhtml.cpp
DEP_CPP_RAWHTM=\
	".\HtmlDlg.h"\
	".\RawHtml.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "RawHtml - Win32 Release"


"$(INTDIR)\Rawhtml.obj" : $(SOURCE) $(DEP_CPP_RAWHTM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"


"$(INTDIR)\Rawhtml.obj" : $(SOURCE) $(DEP_CPP_RAWHTM) "$(INTDIR)"

"$(INTDIR)\Rawhtml.sbr" : $(SOURCE) $(DEP_CPP_RAWHTM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Htmldlg.cpp
DEP_CPP_HTMLD=\
	".\HtmlDlg.h"\
	".\RawHtml.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "RawHtml - Win32 Release"


"$(INTDIR)\Htmldlg.obj" : $(SOURCE) $(DEP_CPP_HTMLD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"


"$(INTDIR)\Htmldlg.obj" : $(SOURCE) $(DEP_CPP_HTMLD) "$(INTDIR)"

"$(INTDIR)\Htmldlg.sbr" : $(SOURCE) $(DEP_CPP_HTMLD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "RawHtml - Win32 Release"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=D:\INetSDK\Lib\Wininet.lib

!IF  "$(CFG)" == "RawHtml - Win32 Release"

!ELSEIF  "$(CFG)" == "RawHtml - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
