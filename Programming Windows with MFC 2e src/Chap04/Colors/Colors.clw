; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "colors.h"
LastPage=0

ClassCount=4
Class1=CChildView
Class2=CColorsApp
Class3=CAboutDlg
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDR_CONTEXTMENU
Resource3=IDD_ABOUTBOX

[CLS:CChildView]
Type=0
BaseClass=CWnd 
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=W
VirtualFilter=WC

[CLS:CColorsApp]
Type=0
BaseClass=CWinApp
HeaderFile=Colors.h
ImplementationFile=Colors.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Colors.cpp
ImplementationFile=Colors.cpp
LastObject=CAboutDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_SHAPE_CIRCLE
Command3=ID_SHAPE_TRIANGLE
Command4=ID_SHAPE_SQUARE
Command5=ID_COLOR_RED
Command6=ID_COLOR_YELLOW
Command7=ID_COLOR_GREEN
Command8=ID_COLOR_CYAN
Command9=ID_COLOR_BLUE
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_COLOR_BLUE
Command2=ID_COLOR_CYAN
Command3=ID_COLOR_GREEN
Command4=ID_COLOR_RED
Command5=ID_SHAPE_CIRCLE
Command6=ID_SHAPE_TRIANGLE
Command7=ID_SHAPE_SQUARE
Command8=ID_COLOR_YELLOW
CommandCount=8

[MNU:IDR_CONTEXTMENU]
Type=1
Class=?
Command1=ID_SHAPE_CIRCLE
Command2=ID_SHAPE_TRIANGLE
Command3=ID_SHAPE_SQUARE
Command4=ID_COLOR_RED
Command5=ID_COLOR_YELLOW
Command6=ID_COLOR_GREEN
Command7=ID_COLOR_CYAN
Command8=ID_COLOR_BLUE
CommandCount=8

