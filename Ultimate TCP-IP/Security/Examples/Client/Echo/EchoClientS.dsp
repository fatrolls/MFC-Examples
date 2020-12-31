# Microsoft Developer Studio Project File - Name="EchoClientS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=EchoClientS - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EchoClientS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EchoClientS.mak" CFG="EchoClientS - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EchoClientS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "EchoClientS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "EchoClientS - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "EchoClientS - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EchoClientS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W4 /GX /O2 /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UT_DISPLAYSTATUS" /D "CUT_SECURE_SOCKET" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\..\Security\Lib\UTSecureLayer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "EchoClientS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UT_DISPLAYSTATUS" /D "CUT_SECURE_SOCKET" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\Security\Lib\UTSecureLayerD.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Lib"

!ELSEIF  "$(CFG)" == "EchoClientS - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "EchoClient___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "EchoClient___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UT_DISPLAYSTATUS" /D "CUT_SECURE_SOCKET" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "_UNICODE" /D "UNICODE" /D "UT_DISPLAYSTATUS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "CUT_SECURE_SOCKET" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\..\Security\Lib\UTSecureLayer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Lib"
# ADD LINK32 ..\..\..\..\Security\Lib\UTSecureLayerUD.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Lib"

!ELSEIF  "$(CFG)" == "EchoClientS - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "EchoClient___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "EchoClient___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UT_DISPLAYSTATUS" /D "CUT_SECURE_SOCKET" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W4 /GX /O2 /I "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\PlatformSDK\Include" /I ".\\" /I "..\..\..\..\include\\" /D "_UNICODE" /D "UNICODE" /D "UT_DISPLAYSTATUS" /D "CUT_SECURE_SOCKET" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\..\Security\Lib\UTSecureLayer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\..\Security\Lib\UTSecureLayer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "EchoClientS - Win32 Release"
# Name "EchoClientS - Win32 Debug"
# Name "EchoClientS - Win32 Unicode Debug"
# Name "EchoClientS - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\echo.rc
# End Source File
# Begin Source File

SOURCE=.\EchoClient.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\uh_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\ut_clnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\UT_StrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\UTDataSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\utfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\utstrlst.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\uh_ctrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\ut_clnt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\UTDataSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\uterr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\utfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\UTSecureSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\utstrlst.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
