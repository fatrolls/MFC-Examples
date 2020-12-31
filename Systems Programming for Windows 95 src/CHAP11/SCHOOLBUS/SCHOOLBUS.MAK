# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=SchoolBus - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SchoolBus - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SchoolBus - Win32 Release" && "$(CFG)" !=\
 "SchoolBus - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SchoolBus.mak" CFG="SchoolBus - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SchoolBus - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "SchoolBus - Win32 Debug" (based on "Win32 (x86) External Target")
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

!IF  "$(CFG)" == "SchoolBus - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f school.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "school.exe"
# PROP BASE Bsc_Name "school.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f school.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "SchoolBus.exe"
# PROP Bsc_Name "SchoolBus.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "SchoolBus - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f school.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "school.exe"
# PROP BASE Bsc_Name "school.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f school.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "SchoolBus.exe"
# PROP Bsc_Name "SchoolBus.bsc"
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

# Name "SchoolBus - Win32 Release"
# Name "SchoolBus - Win32 Debug"

!IF  "$(CFG)" == "SchoolBus - Win32 Release"

".\SchoolBus.exe" : 
   CD C:\VXDBOOK\Chap11\SchoolBus
   NMAKE /f school.mak

!ELSEIF  "$(CFG)" == "SchoolBus - Win32 Debug"

".\SchoolBus.exe" : 
   CD C:\VXDBOOK\Chap11\SchoolBus
   NMAKE /f school.mak

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\school.mak

!IF  "$(CFG)" == "SchoolBus - Win32 Release"

!ELSEIF  "$(CFG)" == "SchoolBus - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
