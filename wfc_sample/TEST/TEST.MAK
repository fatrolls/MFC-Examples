# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=TEST - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TEST - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TEST - Win32 Release" && "$(CFG)" != "TEST - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TEST.MAK" CFG="TEST - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TEST - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TEST - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "TEST - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TEST - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\TEST.exe"

CLEAN : 
	-@erase "$(INTDIR)\REPERR.OBJ"
	-@erase "$(INTDIR)\TCLZFile.obj"
	-@erase "$(INTDIR)\TCNet.obj"
	-@erase "$(INTDIR)\TCNetCon.obj"
	-@erase "$(INTDIR)\TCNetFil.obj"
	-@erase "$(INTDIR)\TCNetshs.obj"
	-@erase "$(INTDIR)\TCNetUSR.obj"
	-@erase "$(INTDIR)\TCNSrc.obj"
	-@erase "$(INTDIR)\TCRAS.OBJ"
	-@erase "$(INTDIR)\TCREG.OBJ"
	-@erase "$(INTDIR)\TCSess.obj"
	-@erase "$(INTDIR)\TCSrvr.obj"
	-@erase "$(INTDIR)\TCSvcMgr.obj"
	-@erase "$(INTDIR)\TCTape.obj"
	-@erase "$(INTDIR)\TEST.OBJ"
	-@erase "$(INTDIR)\test_CNetwork.obj"
	-@erase "$(INTDIR)\test_CQueue.obj"
	-@erase "$(INTDIR)\test_CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\test_CSerialFile.obj"
	-@erase "$(INTDIR)\TEVNTLOG.OBJ"
	-@erase "$(INTDIR)\TURL.OBJ"
	-@erase "$(OUTDIR)\TEST.exe"
	-@erase "$(OUTDIR)\TEST.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TEST.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /G4 /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G4 /MD /W4 /GX /O2 /I "\wfc\include" /D "WIN32" /D "NDEBUG"\
 /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TEST.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TEST.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 \wfc\lib\WinRel\wfc.lib netapi32.lib rasapi32.lib mpr.lib lz32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=\wfc\lib\WinRel\wfc.lib netapi32.lib rasapi32.lib mpr.lib lz32.lib\
 wsock32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/TEST.pdb" /map:"$(INTDIR)/TEST.map" /machine:I386\
 /out:"$(OUTDIR)/TEST.exe" /FORCE:MULTIPLE 
LINK32_OBJS= \
	"$(INTDIR)\REPERR.OBJ" \
	"$(INTDIR)\TCLZFile.obj" \
	"$(INTDIR)\TCNet.obj" \
	"$(INTDIR)\TCNetCon.obj" \
	"$(INTDIR)\TCNetFil.obj" \
	"$(INTDIR)\TCNetshs.obj" \
	"$(INTDIR)\TCNetUSR.obj" \
	"$(INTDIR)\TCNSrc.obj" \
	"$(INTDIR)\TCRAS.OBJ" \
	"$(INTDIR)\TCREG.OBJ" \
	"$(INTDIR)\TCSess.obj" \
	"$(INTDIR)\TCSrvr.obj" \
	"$(INTDIR)\TCSvcMgr.obj" \
	"$(INTDIR)\TCTape.obj" \
	"$(INTDIR)\TEST.OBJ" \
	"$(INTDIR)\test_CNetwork.obj" \
	"$(INTDIR)\test_CQueue.obj" \
	"$(INTDIR)\test_CRandomNumberGenerator.obj" \
	"$(INTDIR)\test_CSerialFile.obj" \
	"$(INTDIR)\TEVNTLOG.OBJ" \
	"$(INTDIR)\TURL.OBJ"

"$(OUTDIR)\TEST.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TEST - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\TEST.exe"

CLEAN : 
	-@erase "$(INTDIR)\REPERR.OBJ"
	-@erase "$(INTDIR)\TCLZFile.obj"
	-@erase "$(INTDIR)\TCNet.obj"
	-@erase "$(INTDIR)\TCNetCon.obj"
	-@erase "$(INTDIR)\TCNetFil.obj"
	-@erase "$(INTDIR)\TCNetshs.obj"
	-@erase "$(INTDIR)\TCNetUSR.obj"
	-@erase "$(INTDIR)\TCNSrc.obj"
	-@erase "$(INTDIR)\TCRAS.OBJ"
	-@erase "$(INTDIR)\TCREG.OBJ"
	-@erase "$(INTDIR)\TCSess.obj"
	-@erase "$(INTDIR)\TCSrvr.obj"
	-@erase "$(INTDIR)\TCSvcMgr.obj"
	-@erase "$(INTDIR)\TCTape.obj"
	-@erase "$(INTDIR)\TEST.OBJ"
	-@erase "$(INTDIR)\test_CNetwork.obj"
	-@erase "$(INTDIR)\test_CQueue.obj"
	-@erase "$(INTDIR)\test_CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\test_CSerialFile.obj"
	-@erase "$(INTDIR)\TEVNTLOG.OBJ"
	-@erase "$(INTDIR)\TURL.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\TEST.exe"
	-@erase "$(OUTDIR)\TEST.ilk"
	-@erase "$(OUTDIR)\TEST.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /I "\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TEST.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TEST.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 \wfc\lib\WinDebug\wfc.lib netapi32.lib rasapi32.lib mpr.lib lz32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib" /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=\wfc\lib\WinDebug\wfc.lib netapi32.lib rasapi32.lib mpr.lib\
 lz32.lib wsock32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/TEST.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib"\
 /out:"$(OUTDIR)/TEST.exe" /FORCE:MULTIPLE 
LINK32_OBJS= \
	"$(INTDIR)\REPERR.OBJ" \
	"$(INTDIR)\TCLZFile.obj" \
	"$(INTDIR)\TCNet.obj" \
	"$(INTDIR)\TCNetCon.obj" \
	"$(INTDIR)\TCNetFil.obj" \
	"$(INTDIR)\TCNetshs.obj" \
	"$(INTDIR)\TCNetUSR.obj" \
	"$(INTDIR)\TCNSrc.obj" \
	"$(INTDIR)\TCRAS.OBJ" \
	"$(INTDIR)\TCREG.OBJ" \
	"$(INTDIR)\TCSess.obj" \
	"$(INTDIR)\TCSrvr.obj" \
	"$(INTDIR)\TCSvcMgr.obj" \
	"$(INTDIR)\TCTape.obj" \
	"$(INTDIR)\TEST.OBJ" \
	"$(INTDIR)\test_CNetwork.obj" \
	"$(INTDIR)\test_CQueue.obj" \
	"$(INTDIR)\test_CRandomNumberGenerator.obj" \
	"$(INTDIR)\test_CSerialFile.obj" \
	"$(INTDIR)\TEVNTLOG.OBJ" \
	"$(INTDIR)\TURL.OBJ"

"$(OUTDIR)\TEST.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TEST - Win32 Release"
# Name "TEST - Win32 Debug"

!IF  "$(CFG)" == "TEST - Win32 Release"

!ELSEIF  "$(CFG)" == "TEST - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TEST.CPP
DEP_CPP_TEST_=\
	".\TEST.H"\
	

"$(INTDIR)\TEST.OBJ" : $(SOURCE) $(DEP_CPP_TEST_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCREG.CPP
DEP_CPP_TCREG=\
	".\TEST.H"\
	

"$(INTDIR)\TCREG.OBJ" : $(SOURCE) $(DEP_CPP_TCREG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\REPERR.CPP
DEP_CPP_REPER=\
	".\TEST.H"\
	

"$(INTDIR)\REPERR.OBJ" : $(SOURCE) $(DEP_CPP_REPER) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCRAS.CPP
DEP_CPP_TCRAS=\
	".\TEST.H"\
	

"$(INTDIR)\TCRAS.OBJ" : $(SOURCE) $(DEP_CPP_TCRAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TEVNTLOG.CPP
DEP_CPP_TEVNT=\
	".\TEST.H"\
	

"$(INTDIR)\TEVNTLOG.OBJ" : $(SOURCE) $(DEP_CPP_TEVNT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCSvcMgr.CPP
DEP_CPP_TCSVC=\
	".\TEST.H"\
	

"$(INTDIR)\TCSvcMgr.obj" : $(SOURCE) $(DEP_CPP_TCSVC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCSrvr.CPP
DEP_CPP_TCSRV=\
	".\TEST.H"\
	

"$(INTDIR)\TCSrvr.obj" : $(SOURCE) $(DEP_CPP_TCSRV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCSess.CPP
DEP_CPP_TCSES=\
	".\TEST.H"\
	

"$(INTDIR)\TCSess.obj" : $(SOURCE) $(DEP_CPP_TCSES) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNSrc.cpp
DEP_CPP_TCNSR=\
	".\TEST.H"\
	

"$(INTDIR)\TCNSrc.obj" : $(SOURCE) $(DEP_CPP_TCNSR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TURL.CPP
DEP_CPP_TURL_=\
	".\TEST.H"\
	

"$(INTDIR)\TURL.OBJ" : $(SOURCE) $(DEP_CPP_TURL_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNet.CPP
DEP_CPP_TCNET=\
	".\TEST.H"\
	

"$(INTDIR)\TCNet.obj" : $(SOURCE) $(DEP_CPP_TCNET) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNetFil.CPP
DEP_CPP_TCNETF=\
	".\TEST.H"\
	

"$(INTDIR)\TCNetFil.obj" : $(SOURCE) $(DEP_CPP_TCNETF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNetCon.CPP
DEP_CPP_TCNETC=\
	".\TEST.H"\
	

"$(INTDIR)\TCNetCon.obj" : $(SOURCE) $(DEP_CPP_TCNETC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCLZFile.CPP
DEP_CPP_TCLZF=\
	".\TEST.H"\
	

"$(INTDIR)\TCLZFile.obj" : $(SOURCE) $(DEP_CPP_TCLZF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCTape.cpp
DEP_CPP_TCTAP=\
	".\TEST.H"\
	

"$(INTDIR)\TCTape.obj" : $(SOURCE) $(DEP_CPP_TCTAP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNetshs.CPP
DEP_CPP_TCNETS=\
	".\TEST.H"\
	

"$(INTDIR)\TCNetshs.obj" : $(SOURCE) $(DEP_CPP_TCNETS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TCNetUSR.CPP
DEP_CPP_TCNETU=\
	".\TEST.H"\
	

"$(INTDIR)\TCNetUSR.obj" : $(SOURCE) $(DEP_CPP_TCNETU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\test_CNetwork.CPP
DEP_CPP_TEST_C=\
	".\TEST.H"\
	

"$(INTDIR)\test_CNetwork.obj" : $(SOURCE) $(DEP_CPP_TEST_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\test_CRandomNumberGenerator.cpp
DEP_CPP_TEST_CR=\
	".\TEST.H"\
	

"$(INTDIR)\test_CRandomNumberGenerator.obj" : $(SOURCE) $(DEP_CPP_TEST_CR)\
 "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\test_CSerialFile.cpp
DEP_CPP_TEST_CS=\
	".\TEST.H"\
	

"$(INTDIR)\test_CSerialFile.obj" : $(SOURCE) $(DEP_CPP_TEST_CS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\test_CQueue.cpp
DEP_CPP_TEST_CQ=\
	".\TEST.H"\
	

"$(INTDIR)\test_CQueue.obj" : $(SOURCE) $(DEP_CPP_TEST_CQ) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
