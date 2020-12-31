# Microsoft Developer Studio Project File - Name="Communicator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Communicator - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Communicator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Communicator.mak" CFG="Communicator - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Communicator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Communicator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Communicator - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "Communicator - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "Communicator - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Communicator - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Communicator - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /debug /machine:I386 /out:"Communicator.exe" /section:.sdata,rws

!ELSEIF  "$(CFG)" == "Communicator - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Communic"
# PROP BASE Intermediate_Dir "Communic"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Communicator - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Communi0"
# PROP BASE Intermediate_Dir "Communi0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /profile /debug /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /profile /debug /machine:I386 /out:"Communicator.exe" /section:.sdata,rws

!ELSEIF  "$(CFG)" == "Communicator - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Communi1"
# PROP BASE Intermediate_Dir "Communi1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
# ADD RSC /l 0x813 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"Communicator.exe" /section:.sdata,rws
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Communicator - Win32 Release"
# Name "Communicator - Win32 Debug"
# Name "Communicator - Win32 Release_Shared"
# Name "Communicator - Win32 Unicode_Debug"
# Name "Communicator - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\OXBlob.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXCommMsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXCommunicator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXVariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Communicator.cpp
# End Source File
# Begin Source File

SOURCE=.\Communicator.odl
# End Source File
# Begin Source File

SOURCE=.\Communicator.rc
# End Source File
# Begin Source File

SOURCE=.\CommunicatorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CommunicatorView.cpp
# End Source File
# Begin Source File

SOURCE=.\HexView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OXDataCommunicator.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SendDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Communicator.h
# End Source File
# Begin Source File

SOURCE=.\CommunicatorDoc.h
# End Source File
# Begin Source File

SOURCE=.\CommunicatorView.h
# End Source File
# Begin Source File

SOURCE=.\HexView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OXDataCommunicator.h
# End Source File
# Begin Source File

SOURCE=.\SendDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Communicator.ico
# End Source File
# Begin Source File

SOURCE=.\res\Communicator.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CommunicatorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\CommunicatorInfo.rtf
# End Source File
# End Group
# End Target
# End Project
