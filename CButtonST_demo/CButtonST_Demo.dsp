# Microsoft Developer Studio Project File - Name="CButtonST_Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CButtonST_Demo - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CButtonST_Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CButtonST_Demo.mak" CFG="CButtonST_Demo - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CButtonST_Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CButtonST_Demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CButtonST_Demo - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "CButtonST_Demo - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CButtonST_Demo - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CButtonST_Demo - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "CButtonST_Demo - Win32 Debug Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug Unicode"
# PROP BASE Intermediate_Dir "Debug Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "CButtonST_Demo - Win32 Release Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release Unicode"
# PROP BASE Intermediate_Dir "Release Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "CButtonST_Demo - Win32 Release"
# Name "CButtonST_Demo - Win32 Debug"
# Name "CButtonST_Demo - Win32 Debug Unicode"
# Name "CButtonST_Demo - Win32 Release Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BkDialogST.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\CButtonST_Demo.cpp
# End Source File
# Begin Source File

SOURCE=.\CButtonST_Demo.rc
# End Source File
# Begin Source File

SOURCE=.\CButtonST_DemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAdvanced.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBasic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShadeButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransparent.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BkDialogST.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\CButtonST_Demo.h
# End Source File
# Begin Source File

SOURCE=.\CButtonST_DemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\DlgAdvanced.h
# End Source File
# Begin Source File

SOURCE=.\DlgBasic.h
# End Source File
# Begin Source File

SOURCE=.\DlgShadeButtonST.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransparent.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\About.ico
# End Source File
# Begin Source File

SOURCE=.\res\Baloon.ico
# End Source File
# Begin Source File

SOURCE=.\res\BmpBack.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Butterfly.ico
# End Source File
# Begin Source File

SOURCE=.\res\Button.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cancel1_32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cancel3_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cancel4_32x32x2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cannibal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CButtonST_Demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\CButtonST_Demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CDRom.ico
# End Source File
# Begin Source File

SOURCE=.\res\Classes1_32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Eagle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EOapp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Explorer.ico
# End Source File
# Begin Source File

SOURCE=.\res\Face.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Halloween1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Halloween2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\Help.ico
# End Source File
# Begin Source File

SOURCE=.\res\Help2_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\IEDocument_48x48x256.ico
# End Source File
# Begin Source File

SOURCE=".\res\JPEG Image.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Key manager.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Lamp1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Lamp2.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedOn.ico
# End Source File
# Begin Source File

SOURCE=.\res\Left2_32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Left6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\LogOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\No3_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\No4_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ok1_32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ok3_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ok4_32x32x2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Open.ico
# End Source File
# Begin Source File

SOURCE=.\res\Palette.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Razor_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Right2_32x32x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Right6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\Run.ico
# End Source File
# Begin Source File

SOURCE=.\res\Search.ico
# End Source File
# Begin Source File

SOURCE=.\res\Search1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Search2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sky.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sound.ico
# End Source File
# Begin Source File

SOURCE=.\res\STLogo_Small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tools4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Web2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Winzip1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Winzip2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Workgroup.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Hover.wav
# End Source File
# Begin Source File

SOURCE=.\res\Start.wav
# End Source File
# End Target
# End Project
