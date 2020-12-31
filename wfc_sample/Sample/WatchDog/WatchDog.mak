# Microsoft Developer Studio Generated NMAKE File, Based on WatchDog.dsp
!IF "$(CFG)" == ""
CFG=WatchDog - Win32 Release
!MESSAGE No configuration specified. Defaulting to WatchDog - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "WatchDog - Win32 Release" && "$(CFG)" !=\
 "WatchDog - Win32 Debug" && "$(CFG)" != "WatchDog - Win32 UnicodeRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WatchDog.mak" CFG="WatchDog - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WatchDog - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "WatchDog - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "WatchDog - Win32 UnicodeRelease" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WatchDog - Win32 Release"

OUTDIR=.\WinRel
INTDIR=.\WinRel

!IF "$(RECURSE)" == "0" 

ALL : "c:\winnt\System32\WatchDog.exe"

!ELSE 

ALL : "c:\winnt\System32\WatchDog.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WatchDog.obj"
	-@erase "$(INTDIR)\WatchDog.res"
	-@erase "$(OUTDIR)\WatchDog.map"
	-@erase "c:\winnt\System32\WatchDog.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "E:\wfc\include" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WatchDog.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /EHc /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WatchDog.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WatchDog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\WatchDog.pdb" /map:"$(INTDIR)\WatchDog.map" /machine:I386\
 /out:"c:\winnt\System32\WatchDog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WatchDog.obj" \
	"$(INTDIR)\WatchDog.res"

"c:\winnt\System32\WatchDog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WatchDog - Win32 Debug"

OUTDIR=.\WinDebug
INTDIR=.\WinDebug

!IF "$(RECURSE)" == "0" 

ALL : "c:\winnt\System32\WatchDog.exe"

!ELSE 

ALL : "c:\winnt\System32\WatchDog.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\WatchDog.obj"
	-@erase "$(INTDIR)\WatchDog.res"
	-@erase "$(OUTDIR)\WatchDog.pdb"
	-@erase "c:\winnt\System32\WatchDog.exe"
	-@erase "c:\winnt\system32\WatchDog.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /I "E:\wfc\include" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WatchDog.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /EHc /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WatchDog.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WatchDog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\WatchDog.pdb" /debug /machine:I386\
 /out:"c:\winnt\system32\WatchDog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WatchDog.obj" \
	"$(INTDIR)\WatchDog.res"

"c:\winnt\System32\WatchDog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WatchDog - Win32 UnicodeRelease"

OUTDIR=.\WatchDog
INTDIR=.\WatchDog

!IF "$(RECURSE)" == "0" 

ALL : "c:\winnt\System32\WatchDog.exe"

!ELSE 

ALL : "c:\winnt\System32\WatchDog.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WatchDog.obj"
	-@erase "$(OUTDIR)\WatchDog.map"
	-@erase ".\WatchDog.res"
	-@erase "c:\winnt\System32\WatchDog.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "E:\wfc\include" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\WatchDog.pch"\
 /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /EHc /c 
CPP_OBJS=.\WatchDog/
CPP_SBRS=.
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WatchDog.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WatchDog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\WatchDog.pdb" /map:"$(INTDIR)\WatchDog.map" /machine:I386\
 /out:"c:\winnt\System32\WatchDog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\WatchDog.obj" \
	".\WatchDog.res"

"c:\winnt\System32\WatchDog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "WatchDog - Win32 Release" || "$(CFG)" ==\
 "WatchDog - Win32 Debug" || "$(CFG)" == "WatchDog - Win32 UnicodeRelease"
SOURCE=.\WatchDog.cpp

!IF  "$(CFG)" == "WatchDog - Win32 Release"

DEP_CPP_WATCH=\
	"..\..\include\cbase64coding.hpp"\
	"..\..\include\cbitarray.hpp"\
	"..\..\include\cbubble.hpp"\
	"..\..\include\cconstellation.hpp"\
	"..\..\include\ccrypto.hpp"\
	"..\..\include\cdataarchive.hpp"\
	"..\..\include\cdatachunk.hpp"\
	"..\..\include\cdatafile.hpp"\
	"..\..\include\cdatamemory.hpp"\
	"..\..\include\cdataparser.hpp"\
	"..\..\include\cdatasocket.hpp"\
	"..\..\include\cdesktop.hpp"\
	"..\..\include\ceventlogrecord.hpp"\
	"..\..\include\cevntlog.hpp"\
	"..\..\include\cextensiblemarkuplanguage.hpp"\
	"..\..\include\cfiletime.hpp"\
	"..\..\include\cfiletransferprotocol.hpp"\
	"..\..\include\cgarbagecollector.hpp"\
	"..\..\include\cmicrosofttape.hpp"\
	"..\..\include\cmixer.hpp"\
	"..\..\include\cnetconn.hpp"\
	"..\..\include\cnetfile.hpp"\
	"..\..\include\cnetinfo.hpp"\
	"..\..\include\cnetrsrc.hpp"\
	"..\..\include\cnetsess.hpp"\
	"..\..\include\cnetshar.hpp"\
	"..\..\include\cnetuser.hpp"\
	"..\..\include\cnetwkst.hpp"\
	"..\..\include\cnetwork.hpp"\
	"..\..\include\cnetworkschedulejob.hpp"\
	"..\..\include\cnmpipe.hpp"\
	"..\..\include\cparsepoint.hpp"\
	"..\..\include\cpasswordchangefilter.hpp"\
	"..\..\include\cping.hpp"\
	"..\..\include\cqueue.hpp"\
	"..\..\include\crandomnumbergenerator.hpp"\
	"..\..\include\cras.hpp"\
	"..\..\include\crasadm.hpp"\
	"..\..\include\crasport.hpp"\
	"..\..\include\creedsolomonerrorcorrectioncode.hpp"\
	"..\..\include\cregisty.hpp"\
	"..\..\include\cserver.hpp"\
	"..\..\include\cservice.hpp"\
	"..\..\include\csmtf.hpp"\
	"..\..\include\csquigl.hpp"\
	"..\..\include\csuperrandomnumbergenerator.hpp"\
	"..\..\include\csvcmgr.hpp"\
	"..\..\include\csystemtime.hpp"\
	"..\..\include\ctape.hpp"\
	"..\..\include\cunc.hpp"\
	"..\..\include\curl.hpp"\
	"..\..\include\cweather.hpp"\
	"..\..\include\cxmlarchive.hpp"\
	"..\..\include\dcb.hpp"\
	"..\..\include\drawgrid.hpp"\
	"..\..\include\drawobj.hpp"\
	"..\..\include\dumyfile.hpp"\
	"..\..\include\guards.hpp"\
	"..\..\include\lsockets.hpp"\
	"..\..\include\lzfile.hpp"\
	"..\..\include\modem.hpp"\
	"..\..\include\ovrlpd.hpp"\
	"..\..\include\pager.hpp"\
	"..\..\include\portinformation.hpp"\
	"..\..\include\samtf.h"\
	"..\..\include\serial.hpp"\
	"..\..\include\serviceconfiguration.hpp"\
	"..\..\include\skyword.hpp"\
	"..\..\include\sockets.hpp"\
	"..\..\include\sockfile.hpp"\
	"..\..\include\sprintspectrum.hpp"\
	"..\..\include\structs.hpp"\
	"..\..\include\tsockets.hpp"\
	"..\..\include\wfc.h"\
	"..\..\include\wfc_crypto.h"\
	"..\..\include\wfcfloat.h"\
	"..\..\include\wfctrace.hpp"\
	".\messages.h"\
	

"$(INTDIR)\WatchDog.obj" : $(SOURCE) $(DEP_CPP_WATCH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WatchDog - Win32 Debug"

DEP_CPP_WATCH=\
	"..\..\include\cbase64coding.hpp"\
	"..\..\include\cbitarray.hpp"\
	"..\..\include\cbubble.hpp"\
	"..\..\include\cconstellation.hpp"\
	"..\..\include\ccrypto.hpp"\
	"..\..\include\cdataarchive.hpp"\
	"..\..\include\cdatachunk.hpp"\
	"..\..\include\cdatafile.hpp"\
	"..\..\include\cdatamemory.hpp"\
	"..\..\include\cdataparser.hpp"\
	"..\..\include\cdatasocket.hpp"\
	"..\..\include\cdesktop.hpp"\
	"..\..\include\ceventlogrecord.hpp"\
	"..\..\include\cevntlog.hpp"\
	"..\..\include\cextensiblemarkuplanguage.hpp"\
	"..\..\include\cfiletime.hpp"\
	"..\..\include\cfiletransferprotocol.hpp"\
	"..\..\include\cgarbagecollector.hpp"\
	"..\..\include\cmicrosofttape.hpp"\
	"..\..\include\cmixer.hpp"\
	"..\..\include\cnetconn.hpp"\
	"..\..\include\cnetfile.hpp"\
	"..\..\include\cnetinfo.hpp"\
	"..\..\include\cnetrsrc.hpp"\
	"..\..\include\cnetsess.hpp"\
	"..\..\include\cnetshar.hpp"\
	"..\..\include\cnetuser.hpp"\
	"..\..\include\cnetwkst.hpp"\
	"..\..\include\cnetwork.hpp"\
	"..\..\include\cnetworkschedulejob.hpp"\
	"..\..\include\cnmpipe.hpp"\
	"..\..\include\cparsepoint.hpp"\
	"..\..\include\cpasswordchangefilter.hpp"\
	"..\..\include\cping.hpp"\
	"..\..\include\cqueue.hpp"\
	"..\..\include\crandomnumbergenerator.hpp"\
	"..\..\include\cras.hpp"\
	"..\..\include\crasadm.hpp"\
	"..\..\include\crasport.hpp"\
	"..\..\include\creedsolomonerrorcorrectioncode.hpp"\
	"..\..\include\cregisty.hpp"\
	"..\..\include\cserver.hpp"\
	"..\..\include\cservice.hpp"\
	"..\..\include\csmtf.hpp"\
	"..\..\include\csquigl.hpp"\
	"..\..\include\csuperrandomnumbergenerator.hpp"\
	"..\..\include\csvcmgr.hpp"\
	"..\..\include\csystemtime.hpp"\
	"..\..\include\ctape.hpp"\
	"..\..\include\cunc.hpp"\
	"..\..\include\curl.hpp"\
	"..\..\include\cweather.hpp"\
	"..\..\include\cxmlarchive.hpp"\
	"..\..\include\dcb.hpp"\
	"..\..\include\drawgrid.hpp"\
	"..\..\include\drawobj.hpp"\
	"..\..\include\dumyfile.hpp"\
	"..\..\include\guards.hpp"\
	"..\..\include\lsockets.hpp"\
	"..\..\include\lzfile.hpp"\
	"..\..\include\modem.hpp"\
	"..\..\include\ovrlpd.hpp"\
	"..\..\include\pager.hpp"\
	"..\..\include\portinformation.hpp"\
	"..\..\include\samtf.h"\
	"..\..\include\serial.hpp"\
	"..\..\include\serviceconfiguration.hpp"\
	"..\..\include\skyword.hpp"\
	"..\..\include\sockets.hpp"\
	"..\..\include\sockfile.hpp"\
	"..\..\include\sprintspectrum.hpp"\
	"..\..\include\structs.hpp"\
	"..\..\include\tsockets.hpp"\
	"..\..\include\wfc.h"\
	"..\..\include\wfc_crypto.h"\
	"..\..\include\wfcfloat.h"\
	"..\..\include\wfctrace.hpp"\
	".\messages.h"\
	

"$(INTDIR)\WatchDog.obj" : $(SOURCE) $(DEP_CPP_WATCH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WatchDog - Win32 UnicodeRelease"

DEP_CPP_WATCH=\
	"..\..\include\cbase64coding.hpp"\
	"..\..\include\cbitarray.hpp"\
	"..\..\include\cbubble.hpp"\
	"..\..\include\cconstellation.hpp"\
	"..\..\include\ccrypto.hpp"\
	"..\..\include\cdataarchive.hpp"\
	"..\..\include\cdatachunk.hpp"\
	"..\..\include\cdatafile.hpp"\
	"..\..\include\cdatamemory.hpp"\
	"..\..\include\cdataparser.hpp"\
	"..\..\include\cdatasocket.hpp"\
	"..\..\include\cdesktop.hpp"\
	"..\..\include\ceventlogrecord.hpp"\
	"..\..\include\cevntlog.hpp"\
	"..\..\include\cextensiblemarkuplanguage.hpp"\
	"..\..\include\cfiletime.hpp"\
	"..\..\include\cfiletransferprotocol.hpp"\
	"..\..\include\cgarbagecollector.hpp"\
	"..\..\include\cmicrosofttape.hpp"\
	"..\..\include\cmixer.hpp"\
	"..\..\include\cnetconn.hpp"\
	"..\..\include\cnetfile.hpp"\
	"..\..\include\cnetinfo.hpp"\
	"..\..\include\cnetrsrc.hpp"\
	"..\..\include\cnetsess.hpp"\
	"..\..\include\cnetshar.hpp"\
	"..\..\include\cnetuser.hpp"\
	"..\..\include\cnetwkst.hpp"\
	"..\..\include\cnetwork.hpp"\
	"..\..\include\cnetworkschedulejob.hpp"\
	"..\..\include\cnmpipe.hpp"\
	"..\..\include\cparsepoint.hpp"\
	"..\..\include\cpasswordchangefilter.hpp"\
	"..\..\include\cping.hpp"\
	"..\..\include\cqueue.hpp"\
	"..\..\include\crandomnumbergenerator.hpp"\
	"..\..\include\cras.hpp"\
	"..\..\include\crasadm.hpp"\
	"..\..\include\crasport.hpp"\
	"..\..\include\creedsolomonerrorcorrectioncode.hpp"\
	"..\..\include\cregisty.hpp"\
	"..\..\include\cserver.hpp"\
	"..\..\include\cservice.hpp"\
	"..\..\include\csmtf.hpp"\
	"..\..\include\csquigl.hpp"\
	"..\..\include\csuperrandomnumbergenerator.hpp"\
	"..\..\include\csvcmgr.hpp"\
	"..\..\include\csystemtime.hpp"\
	"..\..\include\ctape.hpp"\
	"..\..\include\cunc.hpp"\
	"..\..\include\curl.hpp"\
	"..\..\include\cweather.hpp"\
	"..\..\include\cxmlarchive.hpp"\
	"..\..\include\dcb.hpp"\
	"..\..\include\drawgrid.hpp"\
	"..\..\include\drawobj.hpp"\
	"..\..\include\dumyfile.hpp"\
	"..\..\include\guards.hpp"\
	"..\..\include\lsockets.hpp"\
	"..\..\include\lzfile.hpp"\
	"..\..\include\modem.hpp"\
	"..\..\include\ovrlpd.hpp"\
	"..\..\include\pager.hpp"\
	"..\..\include\portinformation.hpp"\
	"..\..\include\samtf.h"\
	"..\..\include\serial.hpp"\
	"..\..\include\serviceconfiguration.hpp"\
	"..\..\include\skyword.hpp"\
	"..\..\include\sockets.hpp"\
	"..\..\include\sockfile.hpp"\
	"..\..\include\sprintspectrum.hpp"\
	"..\..\include\structs.hpp"\
	"..\..\include\tsockets.hpp"\
	"..\..\include\wfc.h"\
	"..\..\include\wfc_crypto.h"\
	"..\..\include\wfcfloat.h"\
	"..\..\include\wfctrace.hpp"\
	".\messages.h"\
	

"$(INTDIR)\WatchDog.obj" : $(SOURCE) $(DEP_CPP_WATCH) "$(INTDIR)"


!ENDIF 

SOURCE=.\WatchDog.rc
DEP_RSC_WATCHD=\
	".\messages.rc"\
	".\MSG00001.bin"\
	".\WatchDog.ver"\
	

!IF  "$(CFG)" == "WatchDog - Win32 Release"


"$(INTDIR)\WatchDog.res" : $(SOURCE) $(DEP_RSC_WATCHD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WatchDog - Win32 Debug"


"$(INTDIR)\WatchDog.res" : $(SOURCE) $(DEP_RSC_WATCHD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WatchDog - Win32 UnicodeRelease"


".\WatchDog.res" : $(SOURCE) $(DEP_RSC_WATCHD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\messages.rc

!ENDIF 

