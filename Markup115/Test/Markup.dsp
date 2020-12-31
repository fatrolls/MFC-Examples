# Microsoft Developer Studio Project File - Name="Markup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Markup - Win32 Unicode STL STDCONV Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Markup.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Markup.mak" CFG="Markup - Win32 Unicode STL STDCONV Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Markup - Win32 MFC Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MFC Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MSXML Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MSXML Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MFC Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MFC Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MSXML Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MSXML Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 STL Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 STL Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS MFC Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS MFC Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode STL Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode STL Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS STL Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS STL Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS STL STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS MFC STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS STL STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MBCS MFC STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MFC STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 MFC STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 STL STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 STL STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MFC STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode MFC STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode STL STDCONV Debug" (based on "Win32 (x86) Application")
!MESSAGE "Markup - Win32 Unicode STL STDCONV Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MFC_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MFC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MFC_Debug"
# PROP Intermediate_Dir "MFC_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MFC_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MFC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MFC_Release"
# PROP Intermediate_Dir "MFC_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "GNORE:4089" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_HUGEFILE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /incremental:yes /map /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MSXML_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MSXML_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MSXML_Debug"
# PROP Intermediate_Dir "MSXML_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_MSXML" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MSXML_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MSXML_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MSXML_Release"
# PROP Intermediate_Dir "MSXML_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_MSXML" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_Unicode_MFC_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MFC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_MFC_Debug"
# PROP Intermediate_Dir "Unicode_MFC_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_Unicode_MFC_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MFC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_MFC_Release"
# PROP Intermediate_Dir "Unicode_MFC_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_Unicode_MSXML_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MSXML_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_MSXML_Debug"
# PROP Intermediate_Dir "Unicode_MSXML_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MARKUP_MSXML" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_Unicode_MSXML_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MSXML_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_MSXML_Release"
# PROP Intermediate_Dir "Unicode_MSXML_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_MSXML" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_STL_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_STL_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "STL_Debug"
# PROP Intermediate_Dir "STL_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MARKUP_STL" /D "MARKUP_STDC" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_STL_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_STL_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "STL_Release"
# PROP Intermediate_Dir "STL_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MBCS_MFC_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_MFC_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MBCS_MFC_Debug"
# PROP Intermediate_Dir "MBCS_MFC_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MBCS_MFC_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_MFC_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MBCS_MFC_Release"
# PROP Intermediate_Dir "MBCS_MFC_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_Unicode_STL_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_STL_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_STL_Debug"
# PROP Intermediate_Dir "Unicode_STL_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MARKUP_STL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 uafxcwd.lib LIBCMTD.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"uafxcwd.lib LIBCMTD.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_Unicode_STL_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_STL_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_STL_Release"
# PROP Intermediate_Dir "Unicode_STL_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 uafxcw.lib LIBCMT.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"uafxcw.lib LIBCMT.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MBCS_STL_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_STL_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MBCS_STL_Debug"
# PROP Intermediate_Dir "MBCS_STL_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MBCS_STL_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_STL_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MBCS_STL_Release"
# PROP Intermediate_Dir "MBCS_STL_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MBCS_STL_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_STL_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MBCS_STL_STDCONV_Debug"
# PROP Intermediate_Dir "MBCS_STL_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /D "MARKUP_STDCONV" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept
# ADD LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MBCS_MFC_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_MFC_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MBCS_MFC_STDCONV_Debug"
# PROP Intermediate_Dir "MBCS_MFC_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MBCS_STL_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_STL_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MBCS_STL_STDCONV_Release"
# PROP Intermediate_Dir "MBCS_STL_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STL" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MBCS_MFC_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MBCS_MFC_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MBCS_MFC_STDCONV_Release"
# PROP Intermediate_Dir "MBCS_MFC_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_MFC_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_MFC_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MFC_STDCONV_Debug"
# PROP Intermediate_Dir "MFC_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_MFC_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_MFC_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MFC_STDCONV_Release"
# PROP Intermediate_Dir "MFC_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "GNORE:4089" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "GNORE:4089" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_STL_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_STL_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "STL_STDCONV_Debug"
# PROP Intermediate_Dir "STL_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MARKUP_STL" /D "MARKUP_STDC" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MARKUP_STL" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept
# ADD LINK32 Nafxcwd.lib Libcmtd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"Nafxcwd.lib Libcmtd.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_STL_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_STL_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "STL_STDCONV_Release"
# PROP Intermediate_Dir "STL_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MARKUP_STL" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 Nafxcw.lib Libcmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"Nafxcw.lib Libcmt.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_Unicode_MFC_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MFC_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_MFC_STDCONV_Debug"
# PROP Intermediate_Dir "Unicode_MFC_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_Unicode_MFC_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_MFC_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_MFC_STDCONV_Release"
# PROP Intermediate_Dir "Unicode_MFC_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Markup___Win32_Unicode_STL_STDCONV_Debug"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_STL_STDCONV_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_STL_STDCONV_Debug"
# PROP Intermediate_Dir "Unicode_STL_STDCONV_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MARKUP_STL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MARKUP_STL" /D "MARKUP_STDCONV" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 uafxcwd.lib LIBCMTD.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"uafxcwd.lib LIBCMTD.lib" /pdbtype:sept
# ADD LINK32 uafxcwd.lib LIBCMTD.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"uafxcwd.lib LIBCMTD.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Markup___Win32_Unicode_STL_STDCONV_Release"
# PROP BASE Intermediate_Dir "Markup___Win32_Unicode_STL_STDCONV_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_STL_STDCONV_Release"
# PROP Intermediate_Dir "Unicode_STL_STDCONV_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /D "MARKUP_STL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /D "MARKUP_STL" /D "MARKUP_STDCONV" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 uafxcw.lib LIBCMT.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"uafxcw.lib LIBCMT.lib" /IGNORE:4089
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 uafxcw.lib LIBCMT.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"uafxcw.lib LIBCMT.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Markup - Win32 MFC Debug"
# Name "Markup - Win32 MFC Release"
# Name "Markup - Win32 MSXML Debug"
# Name "Markup - Win32 MSXML Release"
# Name "Markup - Win32 Unicode MFC Debug"
# Name "Markup - Win32 Unicode MFC Release"
# Name "Markup - Win32 Unicode MSXML Debug"
# Name "Markup - Win32 Unicode MSXML Release"
# Name "Markup - Win32 STL Debug"
# Name "Markup - Win32 STL Release"
# Name "Markup - Win32 MBCS MFC Debug"
# Name "Markup - Win32 MBCS MFC Release"
# Name "Markup - Win32 Unicode STL Debug"
# Name "Markup - Win32 Unicode STL Release"
# Name "Markup - Win32 MBCS STL Debug"
# Name "Markup - Win32 MBCS STL Release"
# Name "Markup - Win32 MBCS STL STDCONV Debug"
# Name "Markup - Win32 MBCS MFC STDCONV Debug"
# Name "Markup - Win32 MBCS STL STDCONV Release"
# Name "Markup - Win32 MBCS MFC STDCONV Release"
# Name "Markup - Win32 MFC STDCONV Debug"
# Name "Markup - Win32 MFC STDCONV Release"
# Name "Markup - Win32 STL STDCONV Debug"
# Name "Markup - Win32 STL STDCONV Release"
# Name "Markup - Win32 Unicode MFC STDCONV Debug"
# Name "Markup - Win32 Unicode MFC STDCONV Release"
# Name "Markup - Win32 Unicode STL STDCONV Debug"
# Name "Markup - Win32 Unicode STL STDCONV Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Markup.cpp

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Markup.rc
# End Source File
# Begin Source File

SOURCE=.\MarkupApp.cpp

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MarkupDlg.cpp

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MarkupMSXML.cpp

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /W3

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MarkupTest.cpp

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\MarkupApp.h
# End Source File
# Begin Source File

SOURCE=.\MarkupDlg.h
# End Source File
# Begin Source File

SOURCE=.\MarkupMSXML.h

!IF  "$(CFG)" == "Markup - Win32 MFC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Debug"

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MSXML Release"

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MBCS MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode MFC STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Markup - Win32 Unicode STL STDCONV Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MarkupTest.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Markup.ico
# End Source File
# Begin Source File

SOURCE=.\res\Markup.rc2
# End Source File
# Begin Source File

SOURCE=.\res\testdlg.bmp
# End Source File
# End Group
# End Target
# End Project
