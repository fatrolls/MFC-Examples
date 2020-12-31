# Microsoft Developer Studio Project File - Name="WFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WFC - Win32 STL Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WFC.mak" CFG="WFC - Win32 STL Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WFC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 UnicodeDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 UnicodeRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 StaticDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 StaticRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 STL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 STL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 STL Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 STL Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WFC - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\WFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# ADD BASE CPP /nologo /MT /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\DebugBuildOfWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WFC___Wi"
# PROP BASE Intermediate_Dir "WFC___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "UnicodeDebug"
# PROP Intermediate_Dir "UnicodeDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /GX /Z7 /Od /I "E:\wfc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /Fr /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MDd /W4 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D "_UNICODE" /D WINVER=0x401 /Fr /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\DebugBuildOfWFC.lib"
# ADD LIB32 /nologo /out:".\UnicodeDebugBuildOfWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WFC___W0"
# PROP BASE Intermediate_Dir "WFC___W0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "UnicodeRelease"
# PROP Intermediate_Dir "UnicodeRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "E:\wfc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D "_UNICODE" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\WFC.lib"
# ADD LIB32 /nologo /out:".\UnicodeWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WFC___Win32_StaticDebug"
# PROP BASE Intermediate_Dir "WFC___Win32_StaticDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "StaticDebug"
# PROP Intermediate_Dir "StaticDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MTd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\DebugBuildOfWFC.lib"
# ADD LIB32 /nologo /out:".\StaticDebugBuildOfWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WFC___Win32_StaticRelease"
# PROP BASE Intermediate_Dir "WFC___Win32_StaticRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "StaticRelease"
# PROP Intermediate_Dir "StaticRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\WFC.lib"
# ADD LIB32 /nologo /out:".\StaticWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WFC___Win32_STL_Debug"
# PROP BASE Intermediate_Dir "WFC___Win32_STL_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WFC_STL_Debug"
# PROP Intermediate_Dir "WFC_STL_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /YX /FD /EHa /TP /GF /EHa /EHc /TP /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\DebugBuildOfWFC.lib"
# ADD LIB32 /nologo /out:".\DebugBuildOfSTLWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WFC___Win32_STL_Release"
# PROP BASE Intermediate_Dir "WFC___Win32_STL_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WFC_Win32_STL_Release"
# PROP Intermediate_Dir "WFC_Win32_STL_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\WFC.lib"
# ADD LIB32 /nologo /out:".\STLWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WFC___Win32_STL_Unicode_Debug"
# PROP BASE Intermediate_Dir "WFC___Win32_STL_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WFC_Win32_STL_Unicode_Debug"
# PROP Intermediate_Dir "WFC_Win32_STL_Unicode_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /YX /FD /EHa /TP /GF /EHa /EHc /TP /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /D "_UNICODE" /YX /FD /EHa /TP /GF /EHa /EHc /TP /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\DebugBuildOSTLfWFC.lib"
# ADD LIB32 /nologo /out:".\DebugBuildOfUnicodeSTLWFC.lib"

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WFC___Win32_STL_Unicode_Release"
# PROP BASE Intermediate_Dir "WFC___Win32_STL_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WFC_Win32_STL_Unicode_Release"
# PROP Intermediate_Dir "WFC_Win32_STL_Unicode_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /YX /FD /EHa /TP /GF /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "_UNICODE" /D "WFC_STL" /YX /FD /EHa /TP /GF /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\STLWFC.lib"
# ADD LIB32 /nologo /out:".\UnicodeSTLWFC.lib"

!ENDIF 

# Begin Target

# Name "WFC - Win32 Release"
# Name "WFC - Win32 Debug"
# Name "WFC - Win32 UnicodeDebug"
# Name "WFC - Win32 UnicodeRelease"
# Name "WFC - Win32 StaticDebug"
# Name "WFC - Win32 StaticRelease"
# Name "WFC - Win32 STL Debug"
# Name "WFC - Win32 STL Release"
# Name "WFC - Win32 STL Unicode Debug"
# Name "WFC - Win32 STL Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\SRC\ATCP.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CBase64Coding.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CBitArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CBubble.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CConstellation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCryptographicAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCryptographicHash.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCryptographicKey.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCryptographicProvider.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CCryptography.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDataArchive.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDataFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDataMemory.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDataParser.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDataSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDesktop.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CDragQuery.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CEventLogRecord.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CEVNTLOG.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CExtensibleMarkupLanguageAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CExtensibleMarkupLanguageDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CExtensibleMarkupLanguageElement.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CExtensibleMarkupLanguageEntities.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFile64.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFileDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CFileTime.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CFileTransferProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CGarbageCollector.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CJulianDate.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMemoryFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMicrosoftTape.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixer.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerCapabilities.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerControl.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerControlDetails.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerControlDetailsData.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerControlInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerDestination.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerLine.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerSource.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerSourceSelector.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerSpeakers.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerSwitchControl.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerVolumeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CMixerWaveIn.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetConn.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetRsrc.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetScheduleJob.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetSess.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetShar.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetWkst.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetwork.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkConnectionInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkFileInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkResourceInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkSessionInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkUser.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CNetworkUserInformation.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CPasswordChangeFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CPhysicalDiskFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CPing.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CPingRes.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CRandomNumberGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CRandomNumberGenerator2.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CRAS.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CRASADM.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CReedSolomonErrorCorrectionCode.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CServer.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CService.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CServiceApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSharedMemoryObject.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSMTF.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSquigl.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSuperRandomNumberGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSvcMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CSystemTime.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CTape.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CTapeGetMediaParameters.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CTimeEx.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CUNC.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CURL.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\CUUCoding.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CWeather.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\CXMLArchive.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DCB.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\DrawGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DrawObj.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\DumyFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\IPCP.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\IPXCP.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\LMErr.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\LSOCKETS.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\LZFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\Modem.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\NAMDPIPE.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\NBFCP.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\OVRLPD.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\Pager.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\PortInformation.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\RASCP.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\RASPPPCR.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\RASPSTAT.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\REGISTRY.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\RemoteAccessServicePort.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\RemoteAccessServiceUser.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\Serial.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\ServiceConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SkyWord.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SOCKETS.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\SockFile.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\SprintSpectrum.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CByteArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CDWordArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CPtrArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CString.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CStringArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CUIntArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\STL_CWordArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\Structs.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\TALKSOCK.CPP
# End Source File
# Begin Source File

SOURCE=..\SRC\U2A_A2U.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_am_i_administrator.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_append_string_to_CByteArray.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_append_text_to_edit_control.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_close_handle.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_convert_double_null_terminated_string.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_convert_double_null_terminated_UNICODE_string.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_convert_lpwstr_to_cstring.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_create_hard_link.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_delete_oldest_file.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_enable_all_privileges.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_enable_privilege.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_day_of_week.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_directory_usage_percentage.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_error_string.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_executable_directory.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_filename_from_handle.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_operating_system_version_string.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_get_web_page.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_move_file_at_reboot.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_parse_iso_8601_string.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_set_thread_name.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_start_screen_saver.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_undocumented_get_system_process_list.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\wfc_UNICODE_floating_point_routines.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\WfcTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\SRC\xml_character_test_routines.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\INCLUDE\CBase64Coding.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CBitArray.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CBubble.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CConstellation.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CCriticalSection.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CCrypto.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataArchive.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataChunk.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataMemory.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataParser.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDataSocket.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDesktop.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CDragQuery.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CEventLogRecord.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CEVNTLOG.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CExtensibleMarkupLanguage.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CFile64.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CFileDirectory.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CFileTime.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CFileTransferProtocol.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CGarbageCollector.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CJulianDate.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CMemoryFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CMicrosoftTape.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CMixer.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetConn.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetRsrc.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetSess.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetShar.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetUser.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetWkst.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetwork.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNetworkScheduleJob.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CNMPIPE.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CParsePoint.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CPasswordChangeFilter.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CPhysicalDiskFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CPing.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CQueue.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CRandomNumberGenerator.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CRandomNumberGenerator2.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CRAS.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CRASADM.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CRASPORT.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CReedSolomonErrorCorrectionCode.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CREGISTY.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CServer.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CService.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CServiceApplication.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CSharedMemoryObject.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CSMTF.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CSquigl.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CSvcMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CSystemTime.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\ctape.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CTimeEx.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CUNC.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CURL.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CWeather.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\CXMLArchive.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\DCB.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\DrawGrid.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\DrawObj.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\DumyFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Guards.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\LSOCKETS.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\LZFILE.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Mfc2Stl.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Modem.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\OVRLPD.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Pager.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\PortInformation.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\samtf.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Serial.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\ServiceConfiguration.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\SkyWord.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\SOCKETS.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\SockFile.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\SprintSpectrum.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\Structs.hpp
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\TSOCKETS.HPP
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\WFC.H
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\wfc_crypto.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\wfc_linker_setup.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\wfc_thread_information_block.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\wfc_undocumented.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\wfcfloat.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\WFCTrace.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
