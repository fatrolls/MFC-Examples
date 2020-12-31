# Microsoft Developer Studio Project File - Name="PukamSoftRes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PukamSoftRes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PukamSoftRes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PukamSoftRes.mak" CFG="PukamSoftRes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PukamSoftRes - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PukamSoftRes - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Vishal/Lathi Storage Services/PukamSoftRes", HTGAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PukamSoftRes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUKAMSOFTRES_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUKAMSOFTRES_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "PukamSoftRes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUKAMSOFTRES_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUKAMSOFTRES_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PukamSoftRes - Win32 Release"
# Name "PukamSoftRes - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PukamSoftRes.cpp
# End Source File
# Begin Source File

SOURCE=.\PukamSoftRes.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "MainMenu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\MainMenu\01_CI_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\01_CI_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\02_IT_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\02_IT_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\03_OT_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\03_OT_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\04_BI_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\04_BI_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\05_RE_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\05_RE_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\background.gif
# End Source File
# End Group
# Begin Group "MessageBox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\MessageBox\cancel.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\cancel_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\cancel_mo.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\confirm_icon.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\error_icon.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\info_icon.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\no.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\no_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\no_mo.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\ok.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\ok_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\ok_mo.gif
# End Source File
# Begin Source File

SOURCE=".\Gifs\MessageBox\top-band.gif"
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\warning_icon.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\YES.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\YES_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MessageBox\YES_mo.gif
# End Source File
# End Group
# Begin Group "CustomerInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\address1.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\address2.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\cell.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\companyName.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\contactPerson.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\customerID.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\email.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\fax.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\phoneO.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\phoneR.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\CustomerInfo\topband.gif
# End Source File
# End Group
# Begin Group "InwardTransactions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\category.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\customerID.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\date.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\quantity.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\serialNumber.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\size.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\storageLocation.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\topband.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\InwardTransactions\weight.gif
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\Common\CommonStrip.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\dropdown_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\dropdown_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\savedetails.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\savedetails_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\savedetails_mo.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\scroll.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\scroll_back.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\scroll_down.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\scroll_up.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\tick.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\wotick.gif
# End Source File
# End Group
# Begin Group "BillingInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\BillingInfo\billNumber.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\customerID.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\date.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\frequency.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\paymentMode.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\rate.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\serialNumber.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\BillingInfo\topband.gif
# End Source File
# End Group
# Begin Group "OutwardTransactions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\customerID.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\date.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\gatePassNumber.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\quantity.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\serialNumber.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\OutwardTransactions\topband.gif
# End Source File
# End Group
# Begin Group "TopBand"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\TopBand\close.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\pipe.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\subtitle_BI.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\subtitle_customer.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\subtitle_IT.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\subtitle_OT.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\subtitle_RE.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\title_main.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\TopBandStrip.gif
# End Source File
# End Group
# Begin Group "LeftNav"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\LeftNav\BI_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\BI_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\BI_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\CI_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\CI_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\CI_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\IT_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\IT_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\IT_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\LeftNavStrip.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\OT_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\OT_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\OT_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\RE_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\RE_hover.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\LeftNav\RE_normal.gif
# End Source File
# End Group
# Begin Group "Reports"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gifs\Reports\view_CI_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Reports\view_IT_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Reports\view_OT_normal.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\Gifs\Common\delete_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\delete_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\TopBand\icon_home.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\MainMenu\mainStrip.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\modify_hit.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Common\modify_normal.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Reports\view_CI_mo.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Reports\view_IT_mo.gif
# End Source File
# Begin Source File

SOURCE=.\Gifs\Reports\view_OT_mo.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
