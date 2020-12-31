# Microsoft Developer Studio Project File - Name="TEST" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TEST - Win32 STL Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TEST.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TEST.mak" CFG="TEST - Win32 STL Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TEST - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TEST - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "TEST - Win32 STL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "TEST - Win32 STL Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TEST - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /G4 /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Yc /FD /EHa /EHc /TP /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /map /machine:I386 /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TEST - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /FD /EHa /EHc /TP /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TEST - Win32 STL Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TEST___Win32_STL_Debug"
# PROP BASE Intermediate_Dir "TEST___Win32_STL_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TEST_Win32_STL_Debug"
# PROP Intermediate_Dir "TEST_Win32_STL_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /YX /FD /EHa /EHc /TP /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D WINVER=0x401 /D "WFC_STL" /YX /FD /EHa /EHc /TP /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TEST - Win32 STL Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TEST___Win32_STL_Release"
# PROP BASE Intermediate_Dir "TEST___Win32_STL_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Win32_STL_Release"
# PROP Intermediate_Dir ".\Win32_STL_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G4 /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Yc /FD /EHa /EHc /TP /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D WINVER=0x401 /D "WFC_STL" /YX /FD /EHa /EHc /TP /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /map /machine:I386 /FORCE:MULTIPLE
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /map /machine:I386 /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "TEST - Win32 Release"
# Name "TEST - Win32 Debug"
# Name "TEST - Win32 STL Debug"
# Name "TEST - Win32 STL Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CQueue_stress_test.cpp
# End Source File
# Begin Source File

SOURCE=.\REPERR.CPP
# End Source File
# Begin Source File

SOURCE=.\TCLZFile.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNet.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNetCon.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNetFil.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNetshs.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNetUSR.CPP
# End Source File
# Begin Source File

SOURCE=.\TCNSrc.cpp
# End Source File
# Begin Source File

SOURCE=.\TCRAS.CPP
# End Source File
# Begin Source File

SOURCE=.\TCREG.CPP
# End Source File
# Begin Source File

SOURCE=.\TCSess.CPP
# End Source File
# Begin Source File

SOURCE=.\TCSrvr.CPP
# End Source File
# Begin Source File

SOURCE=.\TCSvcMgr.CPP
# End Source File
# Begin Source File

SOURCE=.\TCTape.cpp
# End Source File
# Begin Source File

SOURCE=.\TEST.CPP
# End Source File
# Begin Source File

SOURCE=.\test_CBase64Coding.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CBitArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CByteArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CDataParser.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CDWordArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CFileTransferProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CJulianDate.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CNetwork.CPP
# End Source File
# Begin Source File

SOURCE=.\test_CPtrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CRandomNumberGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CReedSolomonErrorCorrectionCode.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CSerialFile.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CString.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CSystemTime.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CUIntArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CUUCoding.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CWordArray.cpp
# End Source File
# Begin Source File

SOURCE=.\test_CXMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\TEVNTLOG.CPP
# End Source File
# Begin Source File

SOURCE=.\TURL.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\TEST.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
