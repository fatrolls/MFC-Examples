# Microsoft Developer Studio Project File - Name="Model" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 50006
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Model - Win32 Local Server Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Model.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Model.mak" CFG="Model - Win32 Local Server Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Model - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Model - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Model - Win32 Local Server" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Model - Win32 Local Server Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Model - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Model___"
# PROP BASE Intermediate_Dir "Model___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /n
# ADD BSC32 /nologo /n
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
TargetPath=.\Release\Model.dll
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=regsvr32 -s -c  $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Model__0"
# PROP BASE Intermediate_Dir "Model__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /n
# ADD BSC32 /nologo /n
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Special Build Tool
TargetPath=.\Debug\Model.dll
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=regsvr32 -s -c  $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Model__1"
# PROP BASE Intermediate_Dir "Model__1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "LocalDbg"
# PROP Intermediate_Dir "LocalDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /n
# ADD BSC32 /nologo /n
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\LocalDbg\Model.exe
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=$(TargetPath) /RegServer	nmake -f proxy.mak
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Model___"
# PROP BASE Intermediate_Dir "Model___"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ModelRel"
# PROP Intermediate_Dir "ModelRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /O2 /D "WIN32" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /n
# ADD BSC32 /nologo /n
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
TargetPath=.\ModelRel\Model.exe
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=$(TargetPath) /RegServer	nmake -f proxy.mak
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Model - Win32 Release"
# Name "Model - Win32 Debug"
# Name "Model - Win32 Local Server"
# Name "Model - Win32 Local Server Release"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\CFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CFactory.h
# End Source File
# Begin Source File

SOURCE=..\Common\CUnknown.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CUnknown.h
# End Source File
# Begin Source File

SOURCE=.\outproc.cpp

!IF  "$(CFG)" == "Model - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Registry.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Registry.h
# End Source File
# Begin Source File

SOURCE=..\Common\util.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\util.h
# End Source File
# End Group
# Begin Group "IDL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\idl\Event_I.idl

!IF  "$(CFG)" == "Model - Win32 Release"

# Begin Custom Build
InputPath=..\idl\Event_I.idl
InputName=Event_I

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\Event_I.idl
InputName=Event_I

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# Begin Custom Build
InputPath=..\idl\Event_I.idl
InputName=Event_I

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# Begin Custom Build
InputPath=..\idl\Event_I.idl
InputName=Event_I

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\idl\model_c.idl

!IF  "$(CFG)" == "Model - Win32 Release"

# Begin Custom Build
InputPath=..\idl\model_c.idl
InputName=model_c

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  /tlb\
          ..\share\$(InputName).tlb $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\model_c.idl
InputName=model_c

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  /tlb\
          ..\share\$(InputName).tlb $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# Begin Custom Build
InputPath=..\idl\model_c.idl
InputName=model_c

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  /tlb\
          ..\share\$(InputName).tlb /dlldata dlldata_c.c $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# Begin Custom Build
InputPath=..\idl\model_c.idl
InputName=model_c

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  /tlb\
          ..\share\$(InputName).tlb /dlldata dlldata_c.c $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\idl\model_i.idl

!IF  "$(CFG)" == "Model - Win32 Release"

# Begin Custom Build
InputPath=..\idl\model_i.idl
InputName=model_i

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\model_i.idl
InputName=model_i

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# Begin Custom Build
InputPath=..\idl\model_i.idl
InputName=model_i

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# Begin Custom Build
InputPath=..\idl\model_i.idl
InputName=model_i

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\idl\tantype.idl

!IF  "$(CFG)" == "Model - Win32 Release"

# Begin Custom Build
InputPath=..\idl\tantype.idl
InputName=tantype

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\tantype.idl
InputName=tantype

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# Begin Custom Build
InputPath=..\idl\tantype.idl
InputName=tantype

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# Begin Custom Build
InputPath=..\idl\tantype.idl
InputName=tantype

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Share"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\share\Event_I.c
# End Source File
# Begin Source File

SOURCE=..\share\model_c.c
# End Source File
# Begin Source File

SOURCE=..\share\model_i.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\CntPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\CntPoint.h
# End Source File
# Begin Source File

SOURCE=.\ConData.cpp
# End Source File
# Begin Source File

SOURCE=.\Condata.h
# End Source File
# Begin Source File

SOURCE=.\EnumCon.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumCon.h
# End Source File
# Begin Source File

SOURCE=.\EnumCP.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumCP.h
# End Source File
# Begin Source File

SOURCE=.\icon1.ico

!IF  "$(CFG)" == "Model - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\model.def

!IF  "$(CFG)" == "Model - Win32 Release"

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "Model - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\server.cpp
# End Source File
# Begin Source File

SOURCE=.\server.rc

!IF  "$(CFG)" == "Model - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server"

!ELSEIF  "$(CFG)" == "Model - Win32 Local Server Release"

!ENDIF 

# End Source File
# End Target
# End Project
