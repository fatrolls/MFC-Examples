# Microsoft Developer Studio Project File - Name="TestAPI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestAPI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestAPI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestAPI.mak" CFG="TestAPI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestAPI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestAPI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestAPI - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestAPI - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestAPI - Win32 Release"
# Name "TestAPI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Plot\Basics\Axis.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\AxisImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\ColorControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\Contour.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLinePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLInePlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\DblBufferPlot\DblBufferPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefAxisSettingDialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefDataSettingDialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefHandlers.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefPlotSettingDialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegendImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegendImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Legend.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\LegendImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ListContour.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\MyString\MyString.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\NlFit\NlFit.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\NlFit\NlFitFuction.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\Optimize\Optimize.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Plot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PlotControl\PlotControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotData.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayerImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemoImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\Spline.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlotImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAPI.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAPI.rc
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlotImpl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Plot\Basics\Axis.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\AxisImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\ColorControl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\ColorTable.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\Contour.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLinePlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLinePlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\DblBufferPlot\DblBufferPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\DblBufferPlot\DblBufferPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefHandlers.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegend.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegendImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegend.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegendImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Legend.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\LegendImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ListContour.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\MyString\MyString.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\NlFit\NlFit.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\Optimize\Optimize.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Plot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PlotControl\PlotControl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotData.h
# End Source File
# Begin Source File

SOURCE=.\Plot\PlotHeaders.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\PlotInterface.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayer.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayerImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\PlotRedefinitions.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotUtility.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemo.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemoImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\Spline.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplitPlot\SplitPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplitPlot\SplitPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlotImpl.h
# End Source File
# Begin Source File

SOURCE=.\TestAPI.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYHandler.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlotImpl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\small.ico
# End Source File
# Begin Source File

SOURCE=.\TestAPI.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
