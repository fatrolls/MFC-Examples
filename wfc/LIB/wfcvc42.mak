# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=WFC - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WFC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WFC - Win32 Release" && "$(CFG)" != "WFC - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WFC.MAK" CFG="WFC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WFC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WFC - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "WFC - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "WFC - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\WFC.lib"

CLEAN : 
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CMicrosoftTape.obj"
	-@erase "$(INTDIR)\CMixer.obj"
	-@erase "$(INTDIR)\CMixerCapabilities.obj"
	-@erase "$(INTDIR)\CMixerControl.obj"
	-@erase "$(INTDIR)\CMixerControlDetails.obj"
	-@erase "$(INTDIR)\CMixerControlDetailsData.obj"
	-@erase "$(INTDIR)\CMixerControlInstance.obj"
	-@erase "$(INTDIR)\CMixerDestination.obj"
	-@erase "$(INTDIR)\CMixerLine.obj"
	-@erase "$(INTDIR)\CMixerSource.obj"
	-@erase "$(INTDIR)\CMixerSourceSelector.obj"
	-@erase "$(INTDIR)\CMixerSpeakers.obj"
	-@erase "$(INTDIR)\CMixerSwitchControl.obj"
	-@erase "$(INTDIR)\CMixerVolumeControl.obj"
	-@erase "$(INTDIR)\CMixerWaveIn.obj"
	-@erase "$(INTDIR)\CNetConn.obj"
	-@erase "$(INTDIR)\CNetFile.obj"
	-@erase "$(INTDIR)\CNetInfo.obj"
	-@erase "$(INTDIR)\CNetRsrc.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\DCB.OBJ"
	-@erase "$(INTDIR)\DrawGrid.obj"
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DumyFile.obj"
	-@erase "$(INTDIR)\IPCP.obj"
	-@erase "$(INTDIR)\IPXCP.obj"
	-@erase "$(INTDIR)\LMErr.obj"
	-@erase "$(INTDIR)\LSOCKETS.OBJ"
	-@erase "$(INTDIR)\LZFile.obj"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\NAMDPIPE.OBJ"
	-@erase "$(INTDIR)\NBFCP.obj"
	-@erase "$(INTDIR)\OVRLPD.OBJ"
	-@erase "$(INTDIR)\Pager.obj"
	-@erase "$(INTDIR)\PortInformation.obj"
	-@erase "$(INTDIR)\RASCP.OBJ"
	-@erase "$(INTDIR)\RASPPPCR.obj"
	-@erase "$(INTDIR)\RASPSTAT.OBJ"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\RemoteAccessServicePort.obj"
	-@erase "$(INTDIR)\RemoteAccessServiceUser.obj"
	-@erase "$(INTDIR)\Serial.obj"
	-@erase "$(INTDIR)\ServiceConfiguration.obj"
	-@erase "$(INTDIR)\SkyWord.obj"
	-@erase "$(INTDIR)\SOCKETS.OBJ"
	-@erase "$(INTDIR)\SockFile.obj"
	-@erase "$(INTDIR)\SprintSpectrum.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(OUTDIR)\WFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "\wfc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "\wfc\include" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /Fp"$(INTDIR)/WFC.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/WFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CMicrosoftTape.obj" \
	"$(INTDIR)\CMixer.obj" \
	"$(INTDIR)\CMixerCapabilities.obj" \
	"$(INTDIR)\CMixerControl.obj" \
	"$(INTDIR)\CMixerControlDetails.obj" \
	"$(INTDIR)\CMixerControlDetailsData.obj" \
	"$(INTDIR)\CMixerControlInstance.obj" \
	"$(INTDIR)\CMixerDestination.obj" \
	"$(INTDIR)\CMixerLine.obj" \
	"$(INTDIR)\CMixerSource.obj" \
	"$(INTDIR)\CMixerSourceSelector.obj" \
	"$(INTDIR)\CMixerSpeakers.obj" \
	"$(INTDIR)\CMixerSwitchControl.obj" \
	"$(INTDIR)\CMixerVolumeControl.obj" \
	"$(INTDIR)\CMixerWaveIn.obj" \
	"$(INTDIR)\CNetConn.obj" \
	"$(INTDIR)\CNetFile.obj" \
	"$(INTDIR)\CNetInfo.obj" \
	"$(INTDIR)\CNetRsrc.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\DCB.OBJ" \
	"$(INTDIR)\DrawGrid.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\DumyFile.obj" \
	"$(INTDIR)\IPCP.obj" \
	"$(INTDIR)\IPXCP.obj" \
	"$(INTDIR)\LMErr.obj" \
	"$(INTDIR)\LSOCKETS.OBJ" \
	"$(INTDIR)\LZFile.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\NAMDPIPE.OBJ" \
	"$(INTDIR)\NBFCP.obj" \
	"$(INTDIR)\OVRLPD.OBJ" \
	"$(INTDIR)\Pager.obj" \
	"$(INTDIR)\PortInformation.obj" \
	"$(INTDIR)\RASCP.OBJ" \
	"$(INTDIR)\RASPPPCR.obj" \
	"$(INTDIR)\RASPSTAT.OBJ" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\RemoteAccessServicePort.obj" \
	"$(INTDIR)\RemoteAccessServiceUser.obj" \
	"$(INTDIR)\Serial.obj" \
	"$(INTDIR)\ServiceConfiguration.obj" \
	"$(INTDIR)\SkyWord.obj" \
	"$(INTDIR)\SOCKETS.OBJ" \
	"$(INTDIR)\SockFile.obj" \
	"$(INTDIR)\SprintSpectrum.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\WfcTrace.obj"

"$(OUTDIR)\WFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\WFC.lib" "$(OUTDIR)\WFC.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\ATCP.sbr"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CBubble.sbr"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CConstellation.sbr"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.sbr"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicHash.sbr"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicKey.sbr"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.sbr"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CCryptography.sbr"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDesktop.sbr"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEventLogRecord.sbr"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CEVNTLOG.SBR"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTime.sbr"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CGarbageCollector.sbr"
	-@erase "$(INTDIR)\CMicrosoftTape.obj"
	-@erase "$(INTDIR)\CMicrosoftTape.sbr"
	-@erase "$(INTDIR)\CMixer.obj"
	-@erase "$(INTDIR)\CMixer.sbr"
	-@erase "$(INTDIR)\CMixerCapabilities.obj"
	-@erase "$(INTDIR)\CMixerCapabilities.sbr"
	-@erase "$(INTDIR)\CMixerControl.obj"
	-@erase "$(INTDIR)\CMixerControl.sbr"
	-@erase "$(INTDIR)\CMixerControlDetails.obj"
	-@erase "$(INTDIR)\CMixerControlDetails.sbr"
	-@erase "$(INTDIR)\CMixerControlDetailsData.obj"
	-@erase "$(INTDIR)\CMixerControlDetailsData.sbr"
	-@erase "$(INTDIR)\CMixerControlInstance.obj"
	-@erase "$(INTDIR)\CMixerControlInstance.sbr"
	-@erase "$(INTDIR)\CMixerDestination.obj"
	-@erase "$(INTDIR)\CMixerDestination.sbr"
	-@erase "$(INTDIR)\CMixerLine.obj"
	-@erase "$(INTDIR)\CMixerLine.sbr"
	-@erase "$(INTDIR)\CMixerSource.obj"
	-@erase "$(INTDIR)\CMixerSource.sbr"
	-@erase "$(INTDIR)\CMixerSourceSelector.obj"
	-@erase "$(INTDIR)\CMixerSourceSelector.sbr"
	-@erase "$(INTDIR)\CMixerSpeakers.obj"
	-@erase "$(INTDIR)\CMixerSpeakers.sbr"
	-@erase "$(INTDIR)\CMixerSwitchControl.obj"
	-@erase "$(INTDIR)\CMixerSwitchControl.sbr"
	-@erase "$(INTDIR)\CMixerVolumeControl.obj"
	-@erase "$(INTDIR)\CMixerVolumeControl.sbr"
	-@erase "$(INTDIR)\CMixerWaveIn.obj"
	-@erase "$(INTDIR)\CMixerWaveIn.sbr"
	-@erase "$(INTDIR)\CNetConn.obj"
	-@erase "$(INTDIR)\CNetConn.sbr"
	-@erase "$(INTDIR)\CNetFile.obj"
	-@erase "$(INTDIR)\CNetFile.sbr"
	-@erase "$(INTDIR)\CNetInfo.obj"
	-@erase "$(INTDIR)\CNetInfo.sbr"
	-@erase "$(INTDIR)\CNetRsrc.obj"
	-@erase "$(INTDIR)\CNetRsrc.sbr"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetSess.sbr"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetShar.sbr"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetWkst.sbr"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetwork.sbr"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUser.sbr"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPing.sbr"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CPingRes.sbr"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CQueue.sbr"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.sbr"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRAS.SBR"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CRASADM.SBR"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CServer.sbr"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CService.sbr"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSMTF.sbr"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSquigl.sbr"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSvcMgr.sbr"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CSystemTime.sbr"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTape.sbr"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.sbr"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CUNC.SBR"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CURL.SBR"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CWeather.sbr"
	-@erase "$(INTDIR)\DCB.OBJ"
	-@erase "$(INTDIR)\DCB.SBR"
	-@erase "$(INTDIR)\DrawGrid.obj"
	-@erase "$(INTDIR)\DrawGrid.sbr"
	-@erase "$(INTDIR)\DrawObj.obj"
	-@erase "$(INTDIR)\DrawObj.sbr"
	-@erase "$(INTDIR)\DumyFile.obj"
	-@erase "$(INTDIR)\DumyFile.sbr"
	-@erase "$(INTDIR)\IPCP.obj"
	-@erase "$(INTDIR)\IPCP.sbr"
	-@erase "$(INTDIR)\IPXCP.obj"
	-@erase "$(INTDIR)\IPXCP.sbr"
	-@erase "$(INTDIR)\LMErr.obj"
	-@erase "$(INTDIR)\LMErr.sbr"
	-@erase "$(INTDIR)\LSOCKETS.OBJ"
	-@erase "$(INTDIR)\LSOCKETS.SBR"
	-@erase "$(INTDIR)\LZFile.obj"
	-@erase "$(INTDIR)\LZFile.sbr"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\Modem.sbr"
	-@erase "$(INTDIR)\NAMDPIPE.OBJ"
	-@erase "$(INTDIR)\NAMDPIPE.SBR"
	-@erase "$(INTDIR)\NBFCP.obj"
	-@erase "$(INTDIR)\NBFCP.sbr"
	-@erase "$(INTDIR)\OVRLPD.OBJ"
	-@erase "$(INTDIR)\OVRLPD.SBR"
	-@erase "$(INTDIR)\Pager.obj"
	-@erase "$(INTDIR)\Pager.sbr"
	-@erase "$(INTDIR)\PortInformation.obj"
	-@erase "$(INTDIR)\PortInformation.sbr"
	-@erase "$(INTDIR)\RASCP.OBJ"
	-@erase "$(INTDIR)\RASCP.SBR"
	-@erase "$(INTDIR)\RASPPPCR.obj"
	-@erase "$(INTDIR)\RASPPPCR.sbr"
	-@erase "$(INTDIR)\RASPSTAT.OBJ"
	-@erase "$(INTDIR)\RASPSTAT.SBR"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\RemoteAccessServicePort.obj"
	-@erase "$(INTDIR)\RemoteAccessServicePort.sbr"
	-@erase "$(INTDIR)\RemoteAccessServiceUser.obj"
	-@erase "$(INTDIR)\RemoteAccessServiceUser.sbr"
	-@erase "$(INTDIR)\Serial.obj"
	-@erase "$(INTDIR)\Serial.sbr"
	-@erase "$(INTDIR)\ServiceConfiguration.obj"
	-@erase "$(INTDIR)\ServiceConfiguration.sbr"
	-@erase "$(INTDIR)\SkyWord.obj"
	-@erase "$(INTDIR)\SkyWord.sbr"
	-@erase "$(INTDIR)\SOCKETS.OBJ"
	-@erase "$(INTDIR)\SOCKETS.SBR"
	-@erase "$(INTDIR)\SockFile.obj"
	-@erase "$(INTDIR)\SockFile.sbr"
	-@erase "$(INTDIR)\SprintSpectrum.obj"
	-@erase "$(INTDIR)\SprintSpectrum.sbr"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\Structs.sbr"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\TALKSOCK.SBR"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\U2A_A2U.sbr"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.sbr"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.sbr"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\WfcTrace.sbr"
	-@erase "$(OUTDIR)\WFC.bsc"
	-@erase "$(OUTDIR)\WFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W4 /GX /Z7 /Od /I "\wfc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /Fr /YX /c
CPP_PROJ=/nologo /MDd /W4 /GX /Z7 /Od /I "\wfc\include" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/WFC.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WFC.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATCP.sbr" \
	"$(INTDIR)\CBubble.sbr" \
	"$(INTDIR)\CConstellation.sbr" \
	"$(INTDIR)\CCryptographicAlgorithm.sbr" \
	"$(INTDIR)\CCryptographicHash.sbr" \
	"$(INTDIR)\CCryptographicKey.sbr" \
	"$(INTDIR)\CCryptographicProvider.sbr" \
	"$(INTDIR)\CCryptography.sbr" \
	"$(INTDIR)\CDesktop.sbr" \
	"$(INTDIR)\CEventLogRecord.sbr" \
	"$(INTDIR)\CEVNTLOG.SBR" \
	"$(INTDIR)\CFileTime.sbr" \
	"$(INTDIR)\CGarbageCollector.sbr" \
	"$(INTDIR)\CMicrosoftTape.sbr" \
	"$(INTDIR)\CMixer.sbr" \
	"$(INTDIR)\CMixerCapabilities.sbr" \
	"$(INTDIR)\CMixerControl.sbr" \
	"$(INTDIR)\CMixerControlDetails.sbr" \
	"$(INTDIR)\CMixerControlDetailsData.sbr" \
	"$(INTDIR)\CMixerControlInstance.sbr" \
	"$(INTDIR)\CMixerDestination.sbr" \
	"$(INTDIR)\CMixerLine.sbr" \
	"$(INTDIR)\CMixerSource.sbr" \
	"$(INTDIR)\CMixerSourceSelector.sbr" \
	"$(INTDIR)\CMixerSpeakers.sbr" \
	"$(INTDIR)\CMixerSwitchControl.sbr" \
	"$(INTDIR)\CMixerVolumeControl.sbr" \
	"$(INTDIR)\CMixerWaveIn.sbr" \
	"$(INTDIR)\CNetConn.sbr" \
	"$(INTDIR)\CNetFile.sbr" \
	"$(INTDIR)\CNetInfo.sbr" \
	"$(INTDIR)\CNetRsrc.sbr" \
	"$(INTDIR)\CNetSess.sbr" \
	"$(INTDIR)\CNetShar.sbr" \
	"$(INTDIR)\CNetWkst.sbr" \
	"$(INTDIR)\CNetwork.sbr" \
	"$(INTDIR)\CNetworkUser.sbr" \
	"$(INTDIR)\CPing.sbr" \
	"$(INTDIR)\CPingRes.sbr" \
	"$(INTDIR)\CQueue.sbr" \
	"$(INTDIR)\CRandomNumberGenerator.sbr" \
	"$(INTDIR)\CRAS.SBR" \
	"$(INTDIR)\CRASADM.SBR" \
	"$(INTDIR)\CServer.sbr" \
	"$(INTDIR)\CService.sbr" \
	"$(INTDIR)\CSMTF.sbr" \
	"$(INTDIR)\CSquigl.sbr" \
	"$(INTDIR)\CSvcMgr.sbr" \
	"$(INTDIR)\CSystemTime.sbr" \
	"$(INTDIR)\CTape.sbr" \
	"$(INTDIR)\CTapeGetMediaParameters.sbr" \
	"$(INTDIR)\CUNC.SBR" \
	"$(INTDIR)\CURL.SBR" \
	"$(INTDIR)\CWeather.sbr" \
	"$(INTDIR)\DCB.SBR" \
	"$(INTDIR)\DrawGrid.sbr" \
	"$(INTDIR)\DrawObj.sbr" \
	"$(INTDIR)\DumyFile.sbr" \
	"$(INTDIR)\IPCP.sbr" \
	"$(INTDIR)\IPXCP.sbr" \
	"$(INTDIR)\LMErr.sbr" \
	"$(INTDIR)\LSOCKETS.SBR" \
	"$(INTDIR)\LZFile.sbr" \
	"$(INTDIR)\Modem.sbr" \
	"$(INTDIR)\NAMDPIPE.SBR" \
	"$(INTDIR)\NBFCP.sbr" \
	"$(INTDIR)\OVRLPD.SBR" \
	"$(INTDIR)\Pager.sbr" \
	"$(INTDIR)\PortInformation.sbr" \
	"$(INTDIR)\RASCP.SBR" \
	"$(INTDIR)\RASPPPCR.sbr" \
	"$(INTDIR)\RASPSTAT.SBR" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\RemoteAccessServicePort.sbr" \
	"$(INTDIR)\RemoteAccessServiceUser.sbr" \
	"$(INTDIR)\Serial.sbr" \
	"$(INTDIR)\ServiceConfiguration.sbr" \
	"$(INTDIR)\SkyWord.sbr" \
	"$(INTDIR)\SOCKETS.SBR" \
	"$(INTDIR)\SockFile.sbr" \
	"$(INTDIR)\SprintSpectrum.sbr" \
	"$(INTDIR)\Structs.sbr" \
	"$(INTDIR)\TALKSOCK.SBR" \
	"$(INTDIR)\U2A_A2U.sbr" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr" \
	"$(INTDIR)\wfc_get_operating_system_version_string.sbr" \
	"$(INTDIR)\wfc_get_web_page.sbr" \
	"$(INTDIR)\WfcTrace.sbr"

"$(OUTDIR)\WFC.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/WFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CMicrosoftTape.obj" \
	"$(INTDIR)\CMixer.obj" \
	"$(INTDIR)\CMixerCapabilities.obj" \
	"$(INTDIR)\CMixerControl.obj" \
	"$(INTDIR)\CMixerControlDetails.obj" \
	"$(INTDIR)\CMixerControlDetailsData.obj" \
	"$(INTDIR)\CMixerControlInstance.obj" \
	"$(INTDIR)\CMixerDestination.obj" \
	"$(INTDIR)\CMixerLine.obj" \
	"$(INTDIR)\CMixerSource.obj" \
	"$(INTDIR)\CMixerSourceSelector.obj" \
	"$(INTDIR)\CMixerSpeakers.obj" \
	"$(INTDIR)\CMixerSwitchControl.obj" \
	"$(INTDIR)\CMixerVolumeControl.obj" \
	"$(INTDIR)\CMixerWaveIn.obj" \
	"$(INTDIR)\CNetConn.obj" \
	"$(INTDIR)\CNetFile.obj" \
	"$(INTDIR)\CNetInfo.obj" \
	"$(INTDIR)\CNetRsrc.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\DCB.OBJ" \
	"$(INTDIR)\DrawGrid.obj" \
	"$(INTDIR)\DrawObj.obj" \
	"$(INTDIR)\DumyFile.obj" \
	"$(INTDIR)\IPCP.obj" \
	"$(INTDIR)\IPXCP.obj" \
	"$(INTDIR)\LMErr.obj" \
	"$(INTDIR)\LSOCKETS.OBJ" \
	"$(INTDIR)\LZFile.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\NAMDPIPE.OBJ" \
	"$(INTDIR)\NBFCP.obj" \
	"$(INTDIR)\OVRLPD.OBJ" \
	"$(INTDIR)\Pager.obj" \
	"$(INTDIR)\PortInformation.obj" \
	"$(INTDIR)\RASCP.OBJ" \
	"$(INTDIR)\RASPPPCR.obj" \
	"$(INTDIR)\RASPSTAT.OBJ" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\RemoteAccessServicePort.obj" \
	"$(INTDIR)\RemoteAccessServiceUser.obj" \
	"$(INTDIR)\Serial.obj" \
	"$(INTDIR)\ServiceConfiguration.obj" \
	"$(INTDIR)\SkyWord.obj" \
	"$(INTDIR)\SOCKETS.OBJ" \
	"$(INTDIR)\SockFile.obj" \
	"$(INTDIR)\SprintSpectrum.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\WfcTrace.obj"

"$(OUTDIR)\WFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "WFC - Win32 Release"
# Name "WFC - Win32 Debug"

!IF  "$(CFG)" == "WFC - Win32 Release"

!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\WFC\SRC\LSOCKETS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LSOCKETS.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\REGISTRY.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\SOCKETS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SOCKETS.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\TALKSOCK.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TALKSOCK.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CUNC.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CUNC.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CURL.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CURL.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CEVNTLOG.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CEVNTLOG.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CRAS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CRAS.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\OVRLPD.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OVRLPD.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\DCB.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DCB.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CService.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CService.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\SockFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SockFile.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CBubble.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CBubble.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\DrawGrid.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DrawGrid.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\DrawObj.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DrawObj.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\DumyFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DumyFile.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\Serial.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Serial.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\NAMDPIPE.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NAMDPIPE.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CSvcMgr.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CSvcMgr.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\U2A_A2U.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\U2A_A2U.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CServer.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CServer.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetSess.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetSess.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\LMErr.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LMErr.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetRsrc.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetRsrc.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetWkst.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetWkst.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\Structs.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Structs.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetwork.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetwork.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetFile.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetConn.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetConn.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetShar.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetShar.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CSquigl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CSquigl.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\LZFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LZFile.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CTape.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CTape.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetInfo.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetInfo.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CSMTF.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CSMTF.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CFileTime.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CFileTime.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CSystemTime.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CSystemTime.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\Modem.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Modem.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CPing.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CPing.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CPingRes.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CPingRes.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\Pager.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Pager.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\SkyWord.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SkyWord.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\ServiceConfiguration.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ServiceConfiguration.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\SprintSpectrum.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SprintSpectrum.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\WfcTrace.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WfcTrace.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMicrosoftTape.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMicrosoftTape.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\wfc_convert_lpwstr_to_cstring.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CNetworkUser.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CNetworkUser.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\PortInformation.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PortInformation.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\RemoteAccessServiceUser.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RemoteAccessServiceUser.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\RemoteAccessServicePort.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RemoteAccessServicePort.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CRASADM.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CRASADM.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CEventLogRecord.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CEventLogRecord.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixer.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixer.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerCapabilities.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerCapabilities.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerControl.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerControlInstance.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerControlInstance.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerControlDetails.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerControlDetails.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerControlDetailsData.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerControlDetailsData.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerDestination.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerDestination.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerSource.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerSource.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerLine.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerLine.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerSourceSelector.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerSourceSelector.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerSpeakers.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerSpeakers.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerSwitchControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerSwitchControl.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerVolumeControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerVolumeControl.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CMixerWaveIn.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CMixerWaveIn.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\wfc_get_web_page.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wfc_get_web_page.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\NBFCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NBFCP.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\RASCP.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RASCP.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\IPCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IPCP.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\IPXCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IPXCP.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\ATCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ATCP.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\RASPPPCR.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RASPPPCR.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\RASPSTAT.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RASPSTAT.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CCryptographicAlgorithm.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCryptographicAlgorithm.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CCryptographicProvider.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCryptographicProvider.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CCryptography.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCryptography.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CCryptographicKey.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCryptographicKey.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CCryptographicHash.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCryptographicHash.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CWeather.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CWeather.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CRandomNumberGenerator.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CRandomNumberGenerator.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\wfc_get_operating_system_version_string.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\wfc_get_operating_system_version_string.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CDesktop.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CDesktop.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CConstellation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CConstellation.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CQueue.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CQueue.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CGarbageCollector.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CGarbageCollector.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\WFC\SRC\CTapeGetMediaParameters.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CTapeGetMediaParameters.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
