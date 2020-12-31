# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=Lpfs - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Lpfs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Lpfs - Win32 Release" && "$(CFG)" != "Lpfs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Lpfs.mak" CFG="Lpfs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Lpfs - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Lpfs - Win32 Debug" (based on "Win32 (x86) External Target")
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

!IF  "$(CFG)" == "Lpfs - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Lpfs.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Lpfs.exe"
# PROP BASE Bsc_Name "Lpfs.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f myvxd.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "lpfs.vxd"
# PROP Bsc_Name ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "Lpfs - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Lpfs.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Lpfs.exe"
# PROP BASE Bsc_Name "Lpfs.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f myvxd.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "lpfs.vxd"
# PROP Bsc_Name ""
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

# Name "Lpfs - Win32 Release"
# Name "Lpfs - Win32 Debug"

!IF  "$(CFG)" == "Lpfs - Win32 Release"

"$(OUTDIR)\lpfs.vxd" : 
   CD C:\vxdbook\chap16\Lpfs
   NMAKE /f myvxd.mak

!ELSEIF  "$(CFG)" == "Lpfs - Win32 Debug"

"$(OUTDIR)\lpfs.vxd" : 
   CD C:\vxdbook\chap16\Lpfs
   NMAKE /f myvxd.mak

!ENDIF 

# End Target
# End Project
################################################################################
