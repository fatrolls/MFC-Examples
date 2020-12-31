; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "shapes.h"
LastPage=0

ClassCount=4
Class1=CChildView
Class2=CMainFrame
Class3=CShapesApp
Class4=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CShapesApp]
Type=0
BaseClass=CWinApp
HeaderFile=Shapes.h
ImplementationFile=Shapes.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Shapes.cpp
ImplementationFile=Shapes.cpp
LastObject=CAboutDlg

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
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_SHAPE_CIRCLE
Command2=ID_SHAPE_TRIANGLE
Command3=ID_SHAPE_SQUARE
CommandCount=3

