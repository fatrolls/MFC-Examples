# Microsoft Developer Studio Project File - Name="Main" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Main - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Main.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Main.mak" CFG="Main - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Main - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Main - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Main - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 HookApi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Main2.exe" /pdbtype:sept /libpath:"./debug"

!ENDIF 

# Begin Target

# Name "Main - Win32 Release"
# Name "Main - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\ComFilDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DriverTool.cpp
# End Source File
# Begin Source File

SOURCE=.\GMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupTalkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\HideProcessDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HookApi.cpp
# End Source File
# Begin Source File

SOURCE=.\HookApiCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\HookApiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HookDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\HookFirewallDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\initSock.cpp
# End Source File
# Begin Source File

SOURCE=.\IoCompletePortSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\IoCompletePortTalkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IpHlpMiscDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\iphookdriverfirewall.cpp
# End Source File
# Begin Source File

SOURCE=.\LSPDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LSPHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.rc
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetstatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetStatisticsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWakeHostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\P2pUDPCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\P2PUdpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\P2pUDPUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\PingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessThreadModule.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtocolTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\RawUdp.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RootDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Serial.cpp
# End Source File
# Begin Source File

SOURCE=.\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\SnifferDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StartServiceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysTrayIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\TaceRouteDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\ComFilDlg.h
# End Source File
# Begin Source File

SOURCE=.\DriverTool.h
# End Source File
# Begin Source File

SOURCE=.\DrvFltIp.h
# End Source File
# Begin Source File

SOURCE=.\GMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\GroupTalk.h
# End Source File
# Begin Source File

SOURCE=.\GroupTalkDlg.h
# End Source File
# Begin Source File

SOURCE=.\Helper.h
# End Source File
# Begin Source File

SOURCE=.\HideProcessDlg.h
# End Source File
# Begin Source File

SOURCE=.\HookApi.h
# End Source File
# Begin Source File

SOURCE=.\HookApiCommon.h
# End Source File
# Begin Source File

SOURCE=.\HookApiDlg.h
# End Source File
# Begin Source File

SOURCE=.\HookDriver.h
# End Source File
# Begin Source File

SOURCE=.\HookFirewallDlg.h
# End Source File
# Begin Source File

SOURCE=.\initSock.h
# End Source File
# Begin Source File

SOURCE=.\IoCompletePortSocket.h
# End Source File
# Begin Source File

SOURCE=.\IoCompletePortTalkDlg.h
# End Source File
# Begin Source File

SOURCE=.\IpHlpMiscDlg.h
# End Source File
# Begin Source File

SOURCE=.\IPHookDriverFirewall.h
# End Source File
# Begin Source File

SOURCE=.\LSPDlg.h
# End Source File
# Begin Source File

SOURCE=.\LSPHelper.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetstatDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetStatisticsDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetWakeHostDlg.h
# End Source File
# Begin Source File

SOURCE=.\P2PUDPCommon.h
# End Source File
# Begin Source File

SOURCE=.\P2PUdpDlg.h
# End Source File
# Begin Source File

SOURCE=.\P2pUDPUtility.h
# End Source File
# Begin Source File

SOURCE=.\PingDlg.h
# End Source File
# Begin Source File

SOURCE=.\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=.\ProcessThreadModule.h
# End Source File
# Begin Source File

SOURCE=.\ProtocolTypes.h
# End Source File
# Begin Source File

SOURCE=.\RawUdp.h
# End Source File
# Begin Source File

SOURCE=.\RemoteAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RootDlg.h
# End Source File
# Begin Source File

SOURCE=.\Serial.h
# End Source File
# Begin Source File

SOURCE=.\Service.h
# End Source File
# Begin Source File

SOURCE=.\SnifferDlg.h
# End Source File
# Begin Source File

SOURCE=.\StartServiceDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysTrayIcon.h
# End Source File
# Begin Source File

SOURCE=.\TaceRouteDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Comp2Comp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Firewall.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\IPHeader.ico
# End Source File
# Begin Source File

SOURCE=.\res\Machine.ico
# End Source File
# Begin Source File

SOURCE=.\res\machine_.ico
# End Source File
# Begin Source File

SOURCE=.\res\MachineOnNetwork.ico
# End Source File
# Begin Source File

SOURCE=.\res\Main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Main.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Sniffer.ico
# End Source File
# Begin Source File

SOURCE=.\res\TCPHeader.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\RemoteAdminService.exe
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
