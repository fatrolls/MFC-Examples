# Microsoft Developer Studio Project File - Name="Messenger" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Messenger - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Messenger.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Messenger.mak" CFG="Messenger - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Messenger - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Messenger - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Messenger - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "DAOExtensions" /I "PropertiesDlg" /I "ColourPicker" /I "." /I "ToolBarEx" /I "CoolMenu" /I "TreeCtrl" /I "WNet" /I "Tray" /I "ListCtrl" /I "Mailslot" /I "Persistence" /I "NetworkTreeCtrl" /I "TitledMenu" /I "StealthFrame" /I "Version" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "PropertiesRes" /i "PropertiesDlg" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Messenger - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "DAOExtensions" /I "PropertiesDlg" /I "ColourPicker" /I "." /I "ToolBarEx" /I "CoolMenu" /I "TreeCtrl" /I "WNet" /I "Tray" /I "ListCtrl" /I "Mailslot" /I "Persistence" /I "NetworkTreeCtrl" /I "TitledMenu" /I "StealthFrame" /I "Version" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "PropertiesDlg" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Messenger - Win32 Release"
# Name "Messenger - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppIdle.cpp
# End Source File
# Begin Source File

SOURCE=.\MailMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Messenger.cpp
# End Source File
# Begin Source File

SOURCE=.\Messenger.rc
# End Source File
# Begin Source File

SOURCE=.\MessengerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MessengerEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MessengerList.cpp
# End Source File
# Begin Source File

SOURCE=.\MessengerTree.cpp
# End Source File
# Begin Source File

SOURCE=.\PropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppIdle.h
# End Source File
# Begin Source File

SOURCE=.\MailMessage.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Messenger.h
# End Source File
# Begin Source File

SOURCE=.\MessengerDoc.h
# End Source File
# Begin Source File

SOURCE=.\MessengerEdit.h
# End Source File
# Begin Source File

SOURCE=.\MessengerList.h
# End Source File
# Begin Source File

SOURCE=.\MessengerTree.h
# End Source File
# Begin Source File

SOURCE=.\PropDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\computer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\domain.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Messenger.ico
# End Source File
# Begin Source File

SOURCE=.\res\Messenger.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MessengerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\mwn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\printer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\share.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smile1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "CoolMenu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CoolMenu\CaptionPainterEx.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\CaptionPainterEx.h
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\CoolMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\CoolMenu.h
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\PaintCap.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\PaintCap.h
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\PixLib.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\PixLib.h
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\Subclass.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolMenu\Subclass.h
# End Source File
# End Group
# Begin Group "ToolBarEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ToolBarEx\ToolBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarEx\ToolBarEx.h
# End Source File
# End Group
# Begin Group "TreeCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TreeCtrl\ColorTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\ColorTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\CustomTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\CustomTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\MultiSelTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\MultiSelTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\ToolTipsTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\ToolTipsTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\TreeCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\TreeCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\TreeCtrl\TreeCtrlEx.inl
# End Source File
# End Group
# Begin Group "WNet"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WNet\WNetEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\WNet\WNetEnum.h
# End Source File
# Begin Source File

SOURCE=.\WNet\WNetResource.cpp
# End Source File
# Begin Source File

SOURCE=.\WNet\WNetResource.h
# End Source File
# End Group
# Begin Group "Tray"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Tray\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\Tray\SystemTray.h
# End Source File
# End Group
# Begin Group "ListCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ListCtrl\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrl\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrl\ListCtrlEx.inl
# End Source File
# End Group
# Begin Group "MailSlot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MailSlot\MAILSLOT.CPP
# End Source File
# Begin Source File

SOURCE=.\MailSlot\MAILSLOT.H
# End Source File
# End Group
# Begin Group "Persistence"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Persistence\PersistentFrames.cpp
# End Source File
# Begin Source File

SOURCE=.\Persistence\PersistentFrames.h
# End Source File
# End Group
# Begin Group "NetworkTreeCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NetworkTreeCtrl\NetworkTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkTreeCtrl\NetworkTreeCtrl.h
# End Source File
# End Group
# Begin Group "TitledMenu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TitledMenu\TitledMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\TitledMenu\TitledMenu.h
# End Source File
# End Group
# Begin Group "DAOExtensions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DAOExtensions\DAOExtensions.cpp
# End Source File
# Begin Source File

SOURCE=.\DAOExtensions\DAOExtensions.h
# End Source File
# Begin Source File

SOURCE=.\DAOExtensions\DaoRecordsetCreate.cpp
# End Source File
# Begin Source File

SOURCE=.\DAOExtensions\DaoRecordsetCreate.h
# End Source File
# Begin Source File

SOURCE=.\DAOExtensions\StreamDib.cpp
# End Source File
# Begin Source File

SOURCE=.\DAOExtensions\StreamDib.h
# End Source File
# End Group
# Begin Group "StealthFrame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StealthFrame\StealthFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\StealthFrame\StealthFrame.h
# End Source File
# End Group
# Begin Group "PropertiesDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesRes.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesRes.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesDlg\PropertiesTreeCtrl.h
# End Source File
# End Group
# Begin Group "ColourPicker"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ColourPicker\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker\ColourPopup.h
# End Source File
# End Group
# Begin Group "Version"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Version\Version.cpp
# End Source File
# Begin Source File

SOURCE=.\Version\Version.h
# End Source File
# End Group
# End Target
# End Project
