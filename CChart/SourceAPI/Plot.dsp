# Microsoft Developer Studio Project File - Name="Plot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Plot - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Plot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Plot.mak" CFG="Plot - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Plot - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Plot - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Plot - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Plot - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\Plotd.lib"

!ENDIF 

# Begin Target

# Name "Plot - Win32 Release"
# Name "Plot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Plot\Basics\Axis.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\AxisImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\BendingPlot\BendingPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\ColorControl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\Contour.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLinePlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ContourLInePlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\DblBufferPlot\DblBufferPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefAxisSettingDialogs.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefContextMenu.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefDataSettingDialogs.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefHandlers.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\DefHandlers\DefPlotSettingDialogs.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegend.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImageLegendImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ImagePlot\ImagePlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegend.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredLegendImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\LayeredPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Legend.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\LegendImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ContourLinePlot\ListContour.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\MyString\MyString.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\NlFit\NlFit.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\NlFit\NlFitFuction.cpp
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\ObjectPlot\ObjectPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Accessary\Numerical\Optimize\Optimize.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\OscilloPlot\OscilloPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PiePlot\PiePlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\Plot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\PlotControl\PlotControl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotData.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayerImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\PlotUtility.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimeDemoImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\RealtimePlot\RealtimePlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\Spline.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\SplinePlot\SplinePlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\StemPlot\StemPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlot.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlotImpl.cpp
# SUBTRACT CPP /YX /Yc /Yu
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

SOURCE=.\Plot\Basics\ErrorCode.h
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

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayer.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Extended\LayeredPlot\PlotLayerImpl.h
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

SOURCE=.\Plot\Basics\XYPlot.h
# End Source File
# Begin Source File

SOURCE=.\Plot\Basics\XYPlotImpl.h
# End Source File
# End Group
# End Target
# End Project
