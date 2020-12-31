# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=IOSMonitor - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to IOSMonitor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IOSMonitor - Win32 Release" && "$(CFG)" !=\
 "IOSMonitor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOSMonitor.mak" CFG="IOSMonitor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOSMonitor - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "IOSMonitor - Win32 Debug" (based on "Win32 (x86) External Target")
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
# PROP Target_Last_Scanned "IOSMonitor - Win32 Debug"

!IF  "$(CFG)" == "IOSMonitor - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f IOSMonitor.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "IOSMonitor.exe"
# PROP BASE Bsc_Name "IOSMonitor.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f reqmon.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "IOSMonitor.exe"
# PROP Bsc_Name "IOSMonitor.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "IOSMonitor - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f IOSMonitor.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "IOSMonitor.exe"
# PROP BASE Bsc_Name "IOSMonitor.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f reqmon.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "IOSMonitor.exe"
# PROP Bsc_Name "IOSMonitor.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "IOSMonitor - Win32 Release"
# Name "IOSMonitor - Win32 Debug"

!IF  "$(CFG)" == "IOSMonitor - Win32 Release"

"$(OUTDIR)\IOSMonitor.exe" : 
   CD C:\oney\chap15\Iosmonitor
   NMAKE /f reqmon.mak

!ELSEIF  "$(CFG)" == "IOSMonitor - Win32 Debug"

"$(OUTDIR)\IOSMonitor.exe" : 
   CD C:\oney\chap15\Iosmonitor
   NMAKE /f reqmon.mak

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Reqmon.mak

!IF  "$(CFG)" == "IOSMonitor - Win32 Release"

!ELSEIF  "$(CFG)" == "IOSMonitor - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
