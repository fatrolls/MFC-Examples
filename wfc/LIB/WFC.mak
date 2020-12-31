# Microsoft Developer Studio Generated NMAKE File, Based on WFC.dsp
!IF "$(CFG)" == ""
CFG=WFC - Win32 STL Unicode Debug
!MESSAGE No configuration specified. Defaulting to WFC - Win32 STL Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "WFC - Win32 Release" && "$(CFG)" != "WFC - Win32 Debug" && "$(CFG)" != "WFC - Win32 UnicodeDebug" && "$(CFG)" != "WFC - Win32 UnicodeRelease" && "$(CFG)" != "WFC - Win32 StaticDebug" && "$(CFG)" != "WFC - Win32 StaticRelease" && "$(CFG)" != "WFC - Win32 STL Debug" && "$(CFG)" != "WFC - Win32 STL Release" && "$(CFG)" != "WFC - Win32 STL Unicode Debug" && "$(CFG)" != "WFC - Win32 STL Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WFC - Win32 Release"

OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\WFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\WFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\WFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\WFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"

OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\DebugBuildOfWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\DebugBuildOfWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D WINVER=0x401 /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\DebugBuildOfWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\DebugBuildOfWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"

OUTDIR=.\UnicodeDebug
INTDIR=.\UnicodeDebug
# Begin Custom Macros
OutDir=.\UnicodeDebug
# End Custom Macros

ALL : ".\UnicodeDebugBuildOfWFC.lib" "$(OUTDIR)\WFC.bsc"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\ATCP.sbr"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBase64Coding.sbr"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBitArray.sbr"
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
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataArchive.sbr"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataFile.sbr"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataMemory.sbr"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataParser.sbr"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDataSocket.sbr"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDesktop.sbr"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CDragQuery.sbr"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEventLogRecord.sbr"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CEVNTLOG.SBR"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.sbr"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.sbr"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.sbr"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.sbr"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile.sbr"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFile64.sbr"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileDirectory.sbr"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTime.sbr"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.sbr"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CGarbageCollector.sbr"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CJulianDate.sbr"
	-@erase "$(INTDIR)\CMemoryFile.obj"
	-@erase "$(INTDIR)\CMemoryFile.sbr"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetScheduleJob.sbr"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetSess.sbr"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetShar.sbr"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetWkst.sbr"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetwork.sbr"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.sbr"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.sbr"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.sbr"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.sbr"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUser.sbr"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.sbr"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.sbr"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.sbr"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPing.sbr"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CPingRes.sbr"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CQueue.sbr"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.sbr"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.sbr"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRAS.SBR"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CRASADM.SBR"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.sbr"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CServer.sbr"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CService.sbr"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CServiceApplication.sbr"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.sbr"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSMTF.sbr"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSquigl.sbr"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.sbr"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSvcMgr.sbr"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CSystemTime.sbr"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTape.sbr"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.sbr"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CTimeEx.sbr"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CUNC.SBR"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CURL.SBR"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CUUCoding.sbr"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CVolume.sbr"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CWeather.sbr"
	-@erase "$(INTDIR)\CXMLArchive.obj"
	-@erase "$(INTDIR)\CXMLArchive.sbr"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CByteArray.sbr"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.sbr"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.sbr"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CString.sbr"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CStringArray.sbr"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.sbr"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.sbr"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\Structs.sbr"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\TALKSOCK.SBR"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\U2A_A2U.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_am_i_administrator.sbr"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.sbr"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.sbr"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_close_handle.sbr"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.sbr"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.sbr"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.sbr"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.sbr"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.sbr"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.sbr"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.sbr"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.sbr"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.sbr"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.sbr"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.sbr"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.sbr"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.sbr"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.sbr"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.sbr"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.sbr"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.sbr"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.sbr"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\WfcTrace.sbr"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.sbr"
	-@erase "$(OUTDIR)\WFC.bsc"
	-@erase ".\UnicodeDebugBuildOfWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D "_UNICODE" /D WINVER=0x401 /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATCP.sbr" \
	"$(INTDIR)\CBase64Coding.sbr" \
	"$(INTDIR)\CBitArray.sbr" \
	"$(INTDIR)\CBubble.sbr" \
	"$(INTDIR)\CConstellation.sbr" \
	"$(INTDIR)\CCryptographicAlgorithm.sbr" \
	"$(INTDIR)\CCryptographicHash.sbr" \
	"$(INTDIR)\CCryptographicKey.sbr" \
	"$(INTDIR)\CCryptographicProvider.sbr" \
	"$(INTDIR)\CCryptography.sbr" \
	"$(INTDIR)\CDataArchive.sbr" \
	"$(INTDIR)\CDataFile.sbr" \
	"$(INTDIR)\CDataMemory.sbr" \
	"$(INTDIR)\CDataParser.sbr" \
	"$(INTDIR)\CDataSocket.sbr" \
	"$(INTDIR)\CDesktop.sbr" \
	"$(INTDIR)\CDragQuery.sbr" \
	"$(INTDIR)\CEventLogRecord.sbr" \
	"$(INTDIR)\CEVNTLOG.SBR" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.sbr" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.sbr" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.sbr" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.sbr" \
	"$(INTDIR)\CFile.sbr" \
	"$(INTDIR)\CFile64.sbr" \
	"$(INTDIR)\CFileDirectory.sbr" \
	"$(INTDIR)\CFileTime.sbr" \
	"$(INTDIR)\CFileTransferProtocol.sbr" \
	"$(INTDIR)\CGarbageCollector.sbr" \
	"$(INTDIR)\CJulianDate.sbr" \
	"$(INTDIR)\CMemoryFile.sbr" \
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
	"$(INTDIR)\CNetScheduleJob.sbr" \
	"$(INTDIR)\CNetSess.sbr" \
	"$(INTDIR)\CNetShar.sbr" \
	"$(INTDIR)\CNetWkst.sbr" \
	"$(INTDIR)\CNetwork.sbr" \
	"$(INTDIR)\CNetworkConnectionInformation.sbr" \
	"$(INTDIR)\CNetworkFileInformation.sbr" \
	"$(INTDIR)\CNetworkResourceInformation.sbr" \
	"$(INTDIR)\CNetworkSessionInformation.sbr" \
	"$(INTDIR)\CNetworkUser.sbr" \
	"$(INTDIR)\CNetworkUserInformation.sbr" \
	"$(INTDIR)\CPasswordChangeFilter.sbr" \
	"$(INTDIR)\CPhysicalDiskFile.sbr" \
	"$(INTDIR)\CPing.sbr" \
	"$(INTDIR)\CPingRes.sbr" \
	"$(INTDIR)\CQueue.sbr" \
	"$(INTDIR)\CRandomNumberGenerator.sbr" \
	"$(INTDIR)\CRandomNumberGenerator2.sbr" \
	"$(INTDIR)\CRAS.SBR" \
	"$(INTDIR)\CRASADM.SBR" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.sbr" \
	"$(INTDIR)\CServer.sbr" \
	"$(INTDIR)\CService.sbr" \
	"$(INTDIR)\CServiceApplication.sbr" \
	"$(INTDIR)\CSharedMemoryObject.sbr" \
	"$(INTDIR)\CSMTF.sbr" \
	"$(INTDIR)\CSquigl.sbr" \
	"$(INTDIR)\CSuperRandomNumberGenerator.sbr" \
	"$(INTDIR)\CSvcMgr.sbr" \
	"$(INTDIR)\CSystemTime.sbr" \
	"$(INTDIR)\CTape.sbr" \
	"$(INTDIR)\CTapeGetMediaParameters.sbr" \
	"$(INTDIR)\CTimeEx.sbr" \
	"$(INTDIR)\CUNC.SBR" \
	"$(INTDIR)\CURL.SBR" \
	"$(INTDIR)\CUUCoding.sbr" \
	"$(INTDIR)\CVolume.sbr" \
	"$(INTDIR)\CWeather.sbr" \
	"$(INTDIR)\CXMLArchive.sbr" \
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
	"$(INTDIR)\STL_CByteArray.sbr" \
	"$(INTDIR)\STL_CDWordArray.sbr" \
	"$(INTDIR)\STL_CPtrArray.sbr" \
	"$(INTDIR)\STL_CString.sbr" \
	"$(INTDIR)\STL_CStringArray.sbr" \
	"$(INTDIR)\STL_CUIntArray.sbr" \
	"$(INTDIR)\STL_CWordArray.sbr" \
	"$(INTDIR)\Structs.sbr" \
	"$(INTDIR)\TALKSOCK.SBR" \
	"$(INTDIR)\U2A_A2U.sbr" \
	"$(INTDIR)\wfc_am_i_administrator.sbr" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.sbr" \
	"$(INTDIR)\wfc_append_text_to_edit_control.sbr" \
	"$(INTDIR)\wfc_close_handle.sbr" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.sbr" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr" \
	"$(INTDIR)\wfc_create_hard_link.sbr" \
	"$(INTDIR)\wfc_delete_oldest_file.sbr" \
	"$(INTDIR)\wfc_enable_all_privileges.sbr" \
	"$(INTDIR)\wfc_enable_privilege.sbr" \
	"$(INTDIR)\wfc_get_day_of_week.sbr" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.sbr" \
	"$(INTDIR)\wfc_get_error_string.sbr" \
	"$(INTDIR)\wfc_get_executable_directory.sbr" \
	"$(INTDIR)\wfc_get_filename_from_handle.sbr" \
	"$(INTDIR)\wfc_get_operating_system_version_string.sbr" \
	"$(INTDIR)\wfc_get_web_page.sbr" \
	"$(INTDIR)\wfc_move_file_at_reboot.sbr" \
	"$(INTDIR)\wfc_parse_iso_8601_string.sbr" \
	"$(INTDIR)\wfc_set_thread_name.sbr" \
	"$(INTDIR)\wfc_start_screen_saver.sbr" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.sbr" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.sbr" \
	"$(INTDIR)\WfcTrace.sbr" \
	"$(INTDIR)\xml_character_test_routines.sbr"

"$(OUTDIR)\WFC.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\UnicodeDebugBuildOfWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\UnicodeDebugBuildOfWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"

OUTDIR=.\UnicodeRelease
INTDIR=.\UnicodeRelease

ALL : ".\UnicodeWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\UnicodeWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D "_AFXDLL" /D "_UNICODE" /D WINVER=0x401 /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\UnicodeWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\UnicodeWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"

OUTDIR=.\StaticDebug
INTDIR=.\StaticDebug

ALL : ".\StaticDebugBuildOfWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\StaticDebugBuildOfWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\StaticDebugBuildOfWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\StaticDebugBuildOfWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"

OUTDIR=.\StaticRelease
INTDIR=.\StaticRelease

ALL : ".\StaticWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\StaticWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\StaticWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\StaticWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"

OUTDIR=.\WFC_STL_Debug
INTDIR=.\WFC_STL_Debug

ALL : ".\DebugBuildOfSTLWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\DebugBuildOfSTLWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /EHa /EHc /TP /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\DebugBuildOfSTLWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\DebugBuildOfSTLWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"

OUTDIR=.\WFC_Win32_STL_Release
INTDIR=.\WFC_Win32_STL_Release

ALL : ".\STLWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\STLWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\STLWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\STLWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"

OUTDIR=.\WFC_Win32_STL_Unicode_Debug
INTDIR=.\WFC_Win32_STL_Unicode_Debug

ALL : ".\DebugBuildOfUnicodeSTLWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\DebugBuildOfUnicodeSTLWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "WFC_STL" /D "_UNICODE" /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /EHa /EHc /TP /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\DebugBuildOfUnicodeSTLWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\DebugBuildOfUnicodeSTLWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"

OUTDIR=.\WFC_Win32_STL_Unicode_Release
INTDIR=.\WFC_Win32_STL_Unicode_Release

ALL : ".\UnicodeSTLWFC.lib"


CLEAN :
	-@erase "$(INTDIR)\ATCP.obj"
	-@erase "$(INTDIR)\CBase64Coding.obj"
	-@erase "$(INTDIR)\CBitArray.obj"
	-@erase "$(INTDIR)\CBubble.obj"
	-@erase "$(INTDIR)\CConstellation.obj"
	-@erase "$(INTDIR)\CCryptographicAlgorithm.obj"
	-@erase "$(INTDIR)\CCryptographicHash.obj"
	-@erase "$(INTDIR)\CCryptographicKey.obj"
	-@erase "$(INTDIR)\CCryptographicProvider.obj"
	-@erase "$(INTDIR)\CCryptography.obj"
	-@erase "$(INTDIR)\CDataArchive.obj"
	-@erase "$(INTDIR)\CDataFile.obj"
	-@erase "$(INTDIR)\CDataMemory.obj"
	-@erase "$(INTDIR)\CDataParser.obj"
	-@erase "$(INTDIR)\CDataSocket.obj"
	-@erase "$(INTDIR)\CDesktop.obj"
	-@erase "$(INTDIR)\CDragQuery.obj"
	-@erase "$(INTDIR)\CEventLogRecord.obj"
	-@erase "$(INTDIR)\CEVNTLOG.OBJ"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageElement.obj"
	-@erase "$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"
	-@erase "$(INTDIR)\CFile.obj"
	-@erase "$(INTDIR)\CFile64.obj"
	-@erase "$(INTDIR)\CFileDirectory.obj"
	-@erase "$(INTDIR)\CFileTime.obj"
	-@erase "$(INTDIR)\CFileTransferProtocol.obj"
	-@erase "$(INTDIR)\CGarbageCollector.obj"
	-@erase "$(INTDIR)\CJulianDate.obj"
	-@erase "$(INTDIR)\CMemoryFile.obj"
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
	-@erase "$(INTDIR)\CNetScheduleJob.obj"
	-@erase "$(INTDIR)\CNetSess.obj"
	-@erase "$(INTDIR)\CNetShar.obj"
	-@erase "$(INTDIR)\CNetWkst.obj"
	-@erase "$(INTDIR)\CNetwork.obj"
	-@erase "$(INTDIR)\CNetworkConnectionInformation.obj"
	-@erase "$(INTDIR)\CNetworkFileInformation.obj"
	-@erase "$(INTDIR)\CNetworkResourceInformation.obj"
	-@erase "$(INTDIR)\CNetworkSessionInformation.obj"
	-@erase "$(INTDIR)\CNetworkUser.obj"
	-@erase "$(INTDIR)\CNetworkUserInformation.obj"
	-@erase "$(INTDIR)\CPasswordChangeFilter.obj"
	-@erase "$(INTDIR)\CPhysicalDiskFile.obj"
	-@erase "$(INTDIR)\CPing.obj"
	-@erase "$(INTDIR)\CPingRes.obj"
	-@erase "$(INTDIR)\CQueue.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CRandomNumberGenerator2.obj"
	-@erase "$(INTDIR)\CRAS.OBJ"
	-@erase "$(INTDIR)\CRASADM.OBJ"
	-@erase "$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"
	-@erase "$(INTDIR)\CServer.obj"
	-@erase "$(INTDIR)\CService.obj"
	-@erase "$(INTDIR)\CServiceApplication.obj"
	-@erase "$(INTDIR)\CSharedMemoryObject.obj"
	-@erase "$(INTDIR)\CSMTF.obj"
	-@erase "$(INTDIR)\CSquigl.obj"
	-@erase "$(INTDIR)\CSuperRandomNumberGenerator.obj"
	-@erase "$(INTDIR)\CSvcMgr.obj"
	-@erase "$(INTDIR)\CSystemTime.obj"
	-@erase "$(INTDIR)\CTape.obj"
	-@erase "$(INTDIR)\CTapeGetMediaParameters.obj"
	-@erase "$(INTDIR)\CTimeEx.obj"
	-@erase "$(INTDIR)\CUNC.OBJ"
	-@erase "$(INTDIR)\CURL.OBJ"
	-@erase "$(INTDIR)\CUUCoding.obj"
	-@erase "$(INTDIR)\CVolume.obj"
	-@erase "$(INTDIR)\CWeather.obj"
	-@erase "$(INTDIR)\CXMLArchive.obj"
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
	-@erase "$(INTDIR)\STL_CByteArray.obj"
	-@erase "$(INTDIR)\STL_CDWordArray.obj"
	-@erase "$(INTDIR)\STL_CPtrArray.obj"
	-@erase "$(INTDIR)\STL_CString.obj"
	-@erase "$(INTDIR)\STL_CStringArray.obj"
	-@erase "$(INTDIR)\STL_CUIntArray.obj"
	-@erase "$(INTDIR)\STL_CWordArray.obj"
	-@erase "$(INTDIR)\Structs.obj"
	-@erase "$(INTDIR)\TALKSOCK.OBJ"
	-@erase "$(INTDIR)\U2A_A2U.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wfc_am_i_administrator.obj"
	-@erase "$(INTDIR)\wfc_append_string_to_CByteArray.obj"
	-@erase "$(INTDIR)\wfc_append_text_to_edit_control.obj"
	-@erase "$(INTDIR)\wfc_close_handle.obj"
	-@erase "$(INTDIR)\wfc_convert_double_null_terminated_string.obj"
	-@erase "$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"
	-@erase "$(INTDIR)\wfc_create_hard_link.obj"
	-@erase "$(INTDIR)\wfc_delete_oldest_file.obj"
	-@erase "$(INTDIR)\wfc_enable_all_privileges.obj"
	-@erase "$(INTDIR)\wfc_enable_privilege.obj"
	-@erase "$(INTDIR)\wfc_get_day_of_week.obj"
	-@erase "$(INTDIR)\wfc_get_directory_usage_percentage.obj"
	-@erase "$(INTDIR)\wfc_get_error_string.obj"
	-@erase "$(INTDIR)\wfc_get_executable_directory.obj"
	-@erase "$(INTDIR)\wfc_get_filename_from_handle.obj"
	-@erase "$(INTDIR)\wfc_get_operating_system_version_string.obj"
	-@erase "$(INTDIR)\wfc_get_web_page.obj"
	-@erase "$(INTDIR)\wfc_move_file_at_reboot.obj"
	-@erase "$(INTDIR)\wfc_parse_iso_8601_string.obj"
	-@erase "$(INTDIR)\wfc_set_thread_name.obj"
	-@erase "$(INTDIR)\wfc_start_screen_saver.obj"
	-@erase "$(INTDIR)\wfc_undocumented_get_system_process_list.obj"
	-@erase "$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"
	-@erase "$(INTDIR)\WfcTrace.obj"
	-@erase "$(INTDIR)\xml_character_test_routines.obj"
	-@erase ".\UnicodeSTLWFC.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "MAKING_WFC" /D WINVER=0x401 /D "_UNICODE" /D "WFC_STL" /Fp"$(INTDIR)\WFC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /TP /GF /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WFC.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:".\UnicodeSTLWFC.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ATCP.obj" \
	"$(INTDIR)\CBase64Coding.obj" \
	"$(INTDIR)\CBitArray.obj" \
	"$(INTDIR)\CBubble.obj" \
	"$(INTDIR)\CConstellation.obj" \
	"$(INTDIR)\CCryptographicAlgorithm.obj" \
	"$(INTDIR)\CCryptographicHash.obj" \
	"$(INTDIR)\CCryptographicKey.obj" \
	"$(INTDIR)\CCryptographicProvider.obj" \
	"$(INTDIR)\CCryptography.obj" \
	"$(INTDIR)\CDataArchive.obj" \
	"$(INTDIR)\CDataFile.obj" \
	"$(INTDIR)\CDataMemory.obj" \
	"$(INTDIR)\CDataParser.obj" \
	"$(INTDIR)\CDataSocket.obj" \
	"$(INTDIR)\CDesktop.obj" \
	"$(INTDIR)\CDragQuery.obj" \
	"$(INTDIR)\CEventLogRecord.obj" \
	"$(INTDIR)\CEVNTLOG.OBJ" \
	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" \
	"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" \
	"$(INTDIR)\CFile.obj" \
	"$(INTDIR)\CFile64.obj" \
	"$(INTDIR)\CFileDirectory.obj" \
	"$(INTDIR)\CFileTime.obj" \
	"$(INTDIR)\CFileTransferProtocol.obj" \
	"$(INTDIR)\CGarbageCollector.obj" \
	"$(INTDIR)\CJulianDate.obj" \
	"$(INTDIR)\CMemoryFile.obj" \
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
	"$(INTDIR)\CNetScheduleJob.obj" \
	"$(INTDIR)\CNetSess.obj" \
	"$(INTDIR)\CNetShar.obj" \
	"$(INTDIR)\CNetWkst.obj" \
	"$(INTDIR)\CNetwork.obj" \
	"$(INTDIR)\CNetworkConnectionInformation.obj" \
	"$(INTDIR)\CNetworkFileInformation.obj" \
	"$(INTDIR)\CNetworkResourceInformation.obj" \
	"$(INTDIR)\CNetworkSessionInformation.obj" \
	"$(INTDIR)\CNetworkUser.obj" \
	"$(INTDIR)\CNetworkUserInformation.obj" \
	"$(INTDIR)\CPasswordChangeFilter.obj" \
	"$(INTDIR)\CPhysicalDiskFile.obj" \
	"$(INTDIR)\CPing.obj" \
	"$(INTDIR)\CPingRes.obj" \
	"$(INTDIR)\CQueue.obj" \
	"$(INTDIR)\CRandomNumberGenerator.obj" \
	"$(INTDIR)\CRandomNumberGenerator2.obj" \
	"$(INTDIR)\CRAS.OBJ" \
	"$(INTDIR)\CRASADM.OBJ" \
	"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" \
	"$(INTDIR)\CServer.obj" \
	"$(INTDIR)\CService.obj" \
	"$(INTDIR)\CServiceApplication.obj" \
	"$(INTDIR)\CSharedMemoryObject.obj" \
	"$(INTDIR)\CSMTF.obj" \
	"$(INTDIR)\CSquigl.obj" \
	"$(INTDIR)\CSuperRandomNumberGenerator.obj" \
	"$(INTDIR)\CSvcMgr.obj" \
	"$(INTDIR)\CSystemTime.obj" \
	"$(INTDIR)\CTape.obj" \
	"$(INTDIR)\CTapeGetMediaParameters.obj" \
	"$(INTDIR)\CTimeEx.obj" \
	"$(INTDIR)\CUNC.OBJ" \
	"$(INTDIR)\CURL.OBJ" \
	"$(INTDIR)\CUUCoding.obj" \
	"$(INTDIR)\CVolume.obj" \
	"$(INTDIR)\CWeather.obj" \
	"$(INTDIR)\CXMLArchive.obj" \
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
	"$(INTDIR)\STL_CByteArray.obj" \
	"$(INTDIR)\STL_CDWordArray.obj" \
	"$(INTDIR)\STL_CPtrArray.obj" \
	"$(INTDIR)\STL_CString.obj" \
	"$(INTDIR)\STL_CStringArray.obj" \
	"$(INTDIR)\STL_CUIntArray.obj" \
	"$(INTDIR)\STL_CWordArray.obj" \
	"$(INTDIR)\Structs.obj" \
	"$(INTDIR)\TALKSOCK.OBJ" \
	"$(INTDIR)\U2A_A2U.obj" \
	"$(INTDIR)\wfc_am_i_administrator.obj" \
	"$(INTDIR)\wfc_append_string_to_CByteArray.obj" \
	"$(INTDIR)\wfc_append_text_to_edit_control.obj" \
	"$(INTDIR)\wfc_close_handle.obj" \
	"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" \
	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" \
	"$(INTDIR)\wfc_create_hard_link.obj" \
	"$(INTDIR)\wfc_delete_oldest_file.obj" \
	"$(INTDIR)\wfc_enable_all_privileges.obj" \
	"$(INTDIR)\wfc_enable_privilege.obj" \
	"$(INTDIR)\wfc_get_day_of_week.obj" \
	"$(INTDIR)\wfc_get_directory_usage_percentage.obj" \
	"$(INTDIR)\wfc_get_error_string.obj" \
	"$(INTDIR)\wfc_get_executable_directory.obj" \
	"$(INTDIR)\wfc_get_filename_from_handle.obj" \
	"$(INTDIR)\wfc_get_operating_system_version_string.obj" \
	"$(INTDIR)\wfc_get_web_page.obj" \
	"$(INTDIR)\wfc_move_file_at_reboot.obj" \
	"$(INTDIR)\wfc_parse_iso_8601_string.obj" \
	"$(INTDIR)\wfc_set_thread_name.obj" \
	"$(INTDIR)\wfc_start_screen_saver.obj" \
	"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" \
	"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" \
	"$(INTDIR)\WfcTrace.obj" \
	"$(INTDIR)\xml_character_test_routines.obj"

".\UnicodeSTLWFC.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WFC.dep")
!INCLUDE "WFC.dep"
!ELSE 
!MESSAGE Warning: cannot find "WFC.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WFC - Win32 Release" || "$(CFG)" == "WFC - Win32 Debug" || "$(CFG)" == "WFC - Win32 UnicodeDebug" || "$(CFG)" == "WFC - Win32 UnicodeRelease" || "$(CFG)" == "WFC - Win32 StaticDebug" || "$(CFG)" == "WFC - Win32 StaticRelease" || "$(CFG)" == "WFC - Win32 STL Debug" || "$(CFG)" == "WFC - Win32 STL Release" || "$(CFG)" == "WFC - Win32 STL Unicode Debug" || "$(CFG)" == "WFC - Win32 STL Unicode Release"
SOURCE=..\SRC\ATCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\ATCP.obj"	"$(INTDIR)\ATCP.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\ATCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CBase64Coding.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CBase64Coding.obj"	"$(INTDIR)\CBase64Coding.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CBase64Coding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CBitArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CBitArray.obj"	"$(INTDIR)\CBitArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CBitArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CBubble.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CBubble.obj"	"$(INTDIR)\CBubble.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CBubble.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CConstellation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CConstellation.obj"	"$(INTDIR)\CConstellation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CConstellation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CCryptographicAlgorithm.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CCryptographicAlgorithm.obj"	"$(INTDIR)\CCryptographicAlgorithm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CCryptographicAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CCryptographicHash.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CCryptographicHash.obj"	"$(INTDIR)\CCryptographicHash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CCryptographicHash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CCryptographicKey.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CCryptographicKey.obj"	"$(INTDIR)\CCryptographicKey.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CCryptographicKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CCryptographicProvider.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CCryptographicProvider.obj"	"$(INTDIR)\CCryptographicProvider.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CCryptographicProvider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CCryptography.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CCryptography.obj"	"$(INTDIR)\CCryptography.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CCryptography.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDataArchive.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDataArchive.obj"	"$(INTDIR)\CDataArchive.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDataArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDataFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDataFile.obj"	"$(INTDIR)\CDataFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDataFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDataMemory.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDataMemory.obj"	"$(INTDIR)\CDataMemory.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDataMemory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDataParser.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDataParser.obj"	"$(INTDIR)\CDataParser.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDataParser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDataSocket.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDataSocket.obj"	"$(INTDIR)\CDataSocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDataSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDesktop.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDesktop.obj"	"$(INTDIR)\CDesktop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDesktop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CDragQuery.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CDragQuery.obj"	"$(INTDIR)\CDragQuery.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CDragQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CEventLogRecord.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CEventLogRecord.obj"	"$(INTDIR)\CEventLogRecord.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CEventLogRecord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CEVNTLOG.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CEVNTLOG.OBJ"	"$(INTDIR)\CEVNTLOG.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CEVNTLOG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CExtensibleMarkupLanguageAttribute.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj"	"$(INTDIR)\CExtensibleMarkupLanguageAttribute.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CExtensibleMarkupLanguageAttribute.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CExtensibleMarkupLanguageDocument.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj"	"$(INTDIR)\CExtensibleMarkupLanguageDocument.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CExtensibleMarkupLanguageDocument.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CExtensibleMarkupLanguageElement.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj"	"$(INTDIR)\CExtensibleMarkupLanguageElement.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CExtensibleMarkupLanguageElement.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CExtensibleMarkupLanguageEntities.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj"	"$(INTDIR)\CExtensibleMarkupLanguageEntities.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CExtensibleMarkupLanguageEntities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CFile.obj"	"$(INTDIR)\CFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CFile64.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CFile64.obj"	"$(INTDIR)\CFile64.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CFile64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CFileDirectory.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CFileDirectory.obj"	"$(INTDIR)\CFileDirectory.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CFileDirectory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CFileTime.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CFileTime.obj"	"$(INTDIR)\CFileTime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CFileTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CFileTransferProtocol.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CFileTransferProtocol.obj"	"$(INTDIR)\CFileTransferProtocol.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CFileTransferProtocol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CGarbageCollector.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CGarbageCollector.obj"	"$(INTDIR)\CGarbageCollector.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CGarbageCollector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CJulianDate.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CJulianDate.obj"	"$(INTDIR)\CJulianDate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CJulianDate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMemoryFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMemoryFile.obj"	"$(INTDIR)\CMemoryFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMemoryFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMicrosoftTape.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMicrosoftTape.obj"	"$(INTDIR)\CMicrosoftTape.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMicrosoftTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixer.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixer.obj"	"$(INTDIR)\CMixer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerCapabilities.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerCapabilities.obj"	"$(INTDIR)\CMixerCapabilities.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerCapabilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerControl.obj"	"$(INTDIR)\CMixerControl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerControlDetails.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerControlDetails.obj"	"$(INTDIR)\CMixerControlDetails.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerControlDetails.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerControlDetailsData.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerControlDetailsData.obj"	"$(INTDIR)\CMixerControlDetailsData.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerControlDetailsData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerControlInstance.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerControlInstance.obj"	"$(INTDIR)\CMixerControlInstance.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerControlInstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerDestination.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerDestination.obj"	"$(INTDIR)\CMixerDestination.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerDestination.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerLine.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerLine.obj"	"$(INTDIR)\CMixerLine.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerLine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerSource.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerSource.obj"	"$(INTDIR)\CMixerSource.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerSourceSelector.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerSourceSelector.obj"	"$(INTDIR)\CMixerSourceSelector.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerSourceSelector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerSpeakers.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerSpeakers.obj"	"$(INTDIR)\CMixerSpeakers.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerSpeakers.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerSwitchControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerSwitchControl.obj"	"$(INTDIR)\CMixerSwitchControl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerSwitchControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerVolumeControl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerVolumeControl.obj"	"$(INTDIR)\CMixerVolumeControl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerVolumeControl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CMixerWaveIn.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CMixerWaveIn.obj"	"$(INTDIR)\CMixerWaveIn.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CMixerWaveIn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetConn.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetConn.obj"	"$(INTDIR)\CNetConn.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetConn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetFile.obj"	"$(INTDIR)\CNetFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetInfo.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetInfo.obj"	"$(INTDIR)\CNetInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetRsrc.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetRsrc.obj"	"$(INTDIR)\CNetRsrc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetRsrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetScheduleJob.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetScheduleJob.obj"	"$(INTDIR)\CNetScheduleJob.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetScheduleJob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetSess.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetSess.obj"	"$(INTDIR)\CNetSess.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetSess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetShar.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetShar.obj"	"$(INTDIR)\CNetShar.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetShar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetWkst.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetWkst.obj"	"$(INTDIR)\CNetWkst.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetWkst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetwork.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetwork.obj"	"$(INTDIR)\CNetwork.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetwork.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkConnectionInformation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkConnectionInformation.obj"	"$(INTDIR)\CNetworkConnectionInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkConnectionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkFileInformation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkFileInformation.obj"	"$(INTDIR)\CNetworkFileInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkFileInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkResourceInformation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkResourceInformation.obj"	"$(INTDIR)\CNetworkResourceInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkResourceInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkSessionInformation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkSessionInformation.obj"	"$(INTDIR)\CNetworkSessionInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkSessionInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkUser.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkUser.obj"	"$(INTDIR)\CNetworkUser.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CNetworkUserInformation.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CNetworkUserInformation.obj"	"$(INTDIR)\CNetworkUserInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CNetworkUserInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CPasswordChangeFilter.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CPasswordChangeFilter.obj"	"$(INTDIR)\CPasswordChangeFilter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CPasswordChangeFilter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CPhysicalDiskFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CPhysicalDiskFile.obj"	"$(INTDIR)\CPhysicalDiskFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CPhysicalDiskFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CPing.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CPing.obj"	"$(INTDIR)\CPing.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CPingRes.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CPingRes.obj"	"$(INTDIR)\CPingRes.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CPingRes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CQueue.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CQueue.obj"	"$(INTDIR)\CQueue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CRandomNumberGenerator.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CRandomNumberGenerator.obj"	"$(INTDIR)\CRandomNumberGenerator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CRandomNumberGenerator2.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CRandomNumberGenerator2.obj"	"$(INTDIR)\CRandomNumberGenerator2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CRandomNumberGenerator2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CRAS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CRAS.OBJ"	"$(INTDIR)\CRAS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CRAS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CRASADM.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CRASADM.OBJ"	"$(INTDIR)\CRASADM.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CRASADM.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CReedSolomonErrorCorrectionCode.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj"	"$(INTDIR)\CReedSolomonErrorCorrectionCode.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CReedSolomonErrorCorrectionCode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CServer.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CServer.obj"	"$(INTDIR)\CServer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CServer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CService.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CService.obj"	"$(INTDIR)\CService.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CService.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CServiceApplication.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CServiceApplication.obj"	"$(INTDIR)\CServiceApplication.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CServiceApplication.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSharedMemoryObject.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSharedMemoryObject.obj"	"$(INTDIR)\CSharedMemoryObject.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSharedMemoryObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSMTF.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSMTF.obj"	"$(INTDIR)\CSMTF.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSMTF.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSquigl.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSquigl.obj"	"$(INTDIR)\CSquigl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSquigl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSuperRandomNumberGenerator.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSuperRandomNumberGenerator.obj"	"$(INTDIR)\CSuperRandomNumberGenerator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSuperRandomNumberGenerator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSvcMgr.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSvcMgr.obj"	"$(INTDIR)\CSvcMgr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSvcMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CSystemTime.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CSystemTime.obj"	"$(INTDIR)\CSystemTime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CSystemTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CTape.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CTape.obj"	"$(INTDIR)\CTape.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CTape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CTapeGetMediaParameters.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CTapeGetMediaParameters.obj"	"$(INTDIR)\CTapeGetMediaParameters.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CTapeGetMediaParameters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CTimeEx.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CTimeEx.obj"	"$(INTDIR)\CTimeEx.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CTimeEx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CUNC.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CUNC.OBJ"	"$(INTDIR)\CUNC.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CURL.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CURL.OBJ"	"$(INTDIR)\CURL.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CURL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CUUCoding.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CUUCoding.obj"	"$(INTDIR)\CUUCoding.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CUUCoding.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CVolume.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CVolume.obj"	"$(INTDIR)\CVolume.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CVolume.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CWeather.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CWeather.obj"	"$(INTDIR)\CWeather.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CWeather.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\CXMLArchive.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\CXMLArchive.obj"	"$(INTDIR)\CXMLArchive.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\CXMLArchive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\DCB.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\DCB.OBJ"	"$(INTDIR)\DCB.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\DCB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\DrawGrid.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\DrawGrid.obj"	"$(INTDIR)\DrawGrid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\DrawGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\DrawObj.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\DrawObj.obj"	"$(INTDIR)\DrawObj.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\DrawObj.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\DumyFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\DumyFile.obj"	"$(INTDIR)\DumyFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\DumyFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\IPCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\IPCP.obj"	"$(INTDIR)\IPCP.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\IPCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\IPXCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\IPXCP.obj"	"$(INTDIR)\IPXCP.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\IPXCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\LMErr.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\LMErr.obj"	"$(INTDIR)\LMErr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\LMErr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\LSOCKETS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\LSOCKETS.OBJ"	"$(INTDIR)\LSOCKETS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\LSOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\LZFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\LZFile.obj"	"$(INTDIR)\LZFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\LZFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\Modem.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\Modem.obj"	"$(INTDIR)\Modem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\NAMDPIPE.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\NAMDPIPE.OBJ"	"$(INTDIR)\NAMDPIPE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\NAMDPIPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\NBFCP.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\NBFCP.obj"	"$(INTDIR)\NBFCP.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\NBFCP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\OVRLPD.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\OVRLPD.OBJ"	"$(INTDIR)\OVRLPD.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\OVRLPD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\Pager.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\Pager.obj"	"$(INTDIR)\Pager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\Pager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\PortInformation.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\PortInformation.obj"	"$(INTDIR)\PortInformation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\PortInformation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\RASCP.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\RASCP.OBJ"	"$(INTDIR)\RASCP.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\RASCP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\RASPPPCR.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\RASPPPCR.obj"	"$(INTDIR)\RASPPPCR.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\RASPPPCR.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\RASPSTAT.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\RASPSTAT.OBJ"	"$(INTDIR)\RASPSTAT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\RASPSTAT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\REGISTRY.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\REGISTRY.OBJ"	"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\RemoteAccessServicePort.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\RemoteAccessServicePort.obj"	"$(INTDIR)\RemoteAccessServicePort.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\RemoteAccessServicePort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\RemoteAccessServiceUser.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\RemoteAccessServiceUser.obj"	"$(INTDIR)\RemoteAccessServiceUser.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\RemoteAccessServiceUser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\Serial.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\Serial.obj"	"$(INTDIR)\Serial.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\Serial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\ServiceConfiguration.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\ServiceConfiguration.obj"	"$(INTDIR)\ServiceConfiguration.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\ServiceConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\SkyWord.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\SkyWord.obj"	"$(INTDIR)\SkyWord.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\SkyWord.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\SOCKETS.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\SOCKETS.OBJ"	"$(INTDIR)\SOCKETS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\SOCKETS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\SockFile.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\SockFile.obj"	"$(INTDIR)\SockFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\SockFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\SprintSpectrum.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\SprintSpectrum.obj"	"$(INTDIR)\SprintSpectrum.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\SprintSpectrum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CByteArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CByteArray.obj"	"$(INTDIR)\STL_CByteArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CDWordArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CDWordArray.obj"	"$(INTDIR)\STL_CDWordArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CDWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CPtrArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CPtrArray.obj"	"$(INTDIR)\STL_CPtrArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CPtrArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CString.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CString.obj"	"$(INTDIR)\STL_CString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CStringArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CStringArray.obj"	"$(INTDIR)\STL_CStringArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CStringArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CUIntArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CUIntArray.obj"	"$(INTDIR)\STL_CUIntArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CUIntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\STL_CWordArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\STL_CWordArray.obj"	"$(INTDIR)\STL_CWordArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\STL_CWordArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\Structs.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\Structs.obj"	"$(INTDIR)\Structs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\Structs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\TALKSOCK.CPP

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\TALKSOCK.OBJ"	"$(INTDIR)\TALKSOCK.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\TALKSOCK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\U2A_A2U.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\U2A_A2U.obj"	"$(INTDIR)\U2A_A2U.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\U2A_A2U.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_am_i_administrator.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_am_i_administrator.obj"	"$(INTDIR)\wfc_am_i_administrator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_am_i_administrator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_append_string_to_CByteArray.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj"	"$(INTDIR)\wfc_append_string_to_CByteArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_append_string_to_CByteArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_append_text_to_edit_control.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_append_text_to_edit_control.obj"	"$(INTDIR)\wfc_append_text_to_edit_control.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_append_text_to_edit_control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_close_handle.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_close_handle.obj"	"$(INTDIR)\wfc_close_handle.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_close_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_convert_double_null_terminated_string.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj"	"$(INTDIR)\wfc_convert_double_null_terminated_string.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_convert_double_null_terminated_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_convert_lpwstr_to_cstring.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj"	"$(INTDIR)\wfc_convert_lpwstr_to_cstring.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_convert_lpwstr_to_cstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_create_hard_link.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_create_hard_link.obj"	"$(INTDIR)\wfc_create_hard_link.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_create_hard_link.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_delete_oldest_file.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_delete_oldest_file.obj"	"$(INTDIR)\wfc_delete_oldest_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_delete_oldest_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_enable_all_privileges.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_enable_all_privileges.obj"	"$(INTDIR)\wfc_enable_all_privileges.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_enable_all_privileges.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_enable_privilege.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_enable_privilege.obj"	"$(INTDIR)\wfc_enable_privilege.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_enable_privilege.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_day_of_week.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_day_of_week.obj"	"$(INTDIR)\wfc_get_day_of_week.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_day_of_week.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_directory_usage_percentage.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj"	"$(INTDIR)\wfc_get_directory_usage_percentage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_directory_usage_percentage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_error_string.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_error_string.obj"	"$(INTDIR)\wfc_get_error_string.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_error_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_executable_directory.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_executable_directory.obj"	"$(INTDIR)\wfc_get_executable_directory.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_executable_directory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_filename_from_handle.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_filename_from_handle.obj"	"$(INTDIR)\wfc_get_filename_from_handle.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_filename_from_handle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_operating_system_version_string.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_operating_system_version_string.obj"	"$(INTDIR)\wfc_get_operating_system_version_string.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_operating_system_version_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_get_web_page.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_get_web_page.obj"	"$(INTDIR)\wfc_get_web_page.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_get_web_page.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_move_file_at_reboot.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_move_file_at_reboot.obj"	"$(INTDIR)\wfc_move_file_at_reboot.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_move_file_at_reboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_parse_iso_8601_string.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_parse_iso_8601_string.obj"	"$(INTDIR)\wfc_parse_iso_8601_string.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_parse_iso_8601_string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_set_thread_name.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_set_thread_name.obj"	"$(INTDIR)\wfc_set_thread_name.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_set_thread_name.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_start_screen_saver.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_start_screen_saver.obj"	"$(INTDIR)\wfc_start_screen_saver.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_start_screen_saver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_undocumented_get_system_process_list.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj"	"$(INTDIR)\wfc_undocumented_get_system_process_list.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_undocumented_get_system_process_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\wfc_UNICODE_floating_point_routines.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj"	"$(INTDIR)\wfc_UNICODE_floating_point_routines.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\wfc_UNICODE_floating_point_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\WfcTrace.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\WfcTrace.obj"	"$(INTDIR)\WfcTrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\WfcTrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\SRC\xml_character_test_routines.cpp

!IF  "$(CFG)" == "WFC - Win32 Release"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 Debug"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeDebug"


"$(INTDIR)\xml_character_test_routines.obj"	"$(INTDIR)\xml_character_test_routines.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 UnicodeRelease"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticDebug"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 StaticRelease"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Debug"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Release"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Debug"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WFC - Win32 STL Unicode Release"


"$(INTDIR)\xml_character_test_routines.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

