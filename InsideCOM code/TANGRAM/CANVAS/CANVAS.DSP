# Microsoft Developer Studio Project File - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 50004
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Canvas - Win32 Debug
!MESSAGE "Canvas - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Canvas - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")

# Begin Project
# PROP Scc_ProjName ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Canvas - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Canvas__"
# PROP BASE Intermediate_Dir "Canvas__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# PROP Ignore_Export_Lib 0
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
TargetPath=.\Release\Canvas.dll
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=regsvr32 -s -c  $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Canvas - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Canvas_0"
# PROP BASE Intermediate_Dir "Canvas_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# PROP Ignore_Export_Lib 0
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
TargetPath=.\Debug\Canvas.dll
SOURCE=$(InputPath)
PostBuild_Desc=Register Server
PostBuild_Cmds=regsvr32 -s -c  $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Canvas - Win32 Release"
# Name "Canvas - Win32 Debug"
# Begin Source File

SOURCE=.\server.cpp
# End Source File
# Begin Source File

SOURCE=.\Canvas.h
# End Source File
# Begin Source File

SOURCE=.\Canvas.cpp
# End Source File
# Begin Source File

SOURCE=.\canvas.def
# End Source File
# Begin Group "IDL"

# Begin Source File

SOURCE=..\idl\Canvas_C.idl

!IF  "$(CFG)" == "Canvas - Win32 Release"

# Begin Custom Build
InputPath=..\idl\Canvas_C.idl
InputName=Canvas_C

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Canvas - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\Canvas_C.idl
InputName=Canvas_C

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).tlb" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\idl\canvas_i.idl

!IF  "$(CFG)" == "Canvas - Win32 Release"

# Begin Custom Build
InputPath=..\idl\canvas_i.idl
InputName=canvas_i

BuildCmds= \
	midl /h ..\share\$(InputName).h /iid ..\share\$(InputName).c  $(InputName).idl

"..\share\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\share\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Canvas - Win32 Debug"

# Begin Custom Build
InputPath=..\idl\canvas_i.idl
InputName=canvas_i

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

# Begin Source File

SOURCE=..\share\Canvas_C.c
# End Source File
# Begin Source File

SOURCE=..\share\canvas_i.c
# End Source File
# End Group
# Begin Group "Common"

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
# End Target
# End Project
