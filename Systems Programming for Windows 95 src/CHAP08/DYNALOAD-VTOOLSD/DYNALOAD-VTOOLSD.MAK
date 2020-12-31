# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=DynaLoad-VtoolsD - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DynaLoad-VtoolsD - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "DynaLoad-VtoolsD - Win32 Release" && "$(CFG)" !=\
 "DynaLoad-VtoolsD - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DynaLoad-VtoolsD.mak" CFG="DynaLoad-VtoolsD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DynaLoad-VtoolsD - Win32 Release" (based on\
 "Win32 (x86) External Target")
!MESSAGE "DynaLoad-VtoolsD - Win32 Debug" (based on\
 "Win32 (x86) External Target")
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

!IF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Myvxd.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Myvxd.exe"
# PROP BASE Bsc_Name "Myvxd.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Myvxd.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "DynaLoad-VtoolsD.exe"
# PROP Bsc_Name "DynaLoad-VtoolsD.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Myvxd.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Myvxd.exe"
# PROP BASE Bsc_Name "Myvxd.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Myvxd.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "DynaLoad-VtoolsD.exe"
# PROP Bsc_Name "DynaLoad-VtoolsD.bsc"
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

# Name "DynaLoad-VtoolsD - Win32 Release"
# Name "DynaLoad-VtoolsD - Win32 Debug"

!IF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Release"

"$(OUTDIR)\DynaLoad-VtoolsD.exe" : 
   CD C:\VXDBOOK\CHAP8\DynaLoad-VtoolsD
   NMAKE /f Myvxd.mak

!ELSEIF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Debug"

"$(OUTDIR)\DynaLoad-VtoolsD.exe" : 
   CD C:\VXDBOOK\CHAP8\DynaLoad-VtoolsD
   NMAKE /f Myvxd.mak

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Myvxd.mak

!IF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Release"

!ELSEIF  "$(CFG)" == "DynaLoad-VtoolsD - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
