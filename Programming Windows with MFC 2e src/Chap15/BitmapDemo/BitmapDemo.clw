; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BitmapDemo.h"
LastPage=0

ClassCount=3
Class1=CBitmapDemoApp
Class3=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class2=CChildView
Resource2=IDD_ABOUTBOX

[CLS:CBitmapDemoApp]
Type=0
HeaderFile=BitmapDemo.h
ImplementationFile=BitmapDemo.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=W
BaseClass=CWnd 
VirtualFilter=WC
LastObject=CChildView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_OPTIONS_DRAW_OPAQUE
Command2=ID_OPTIONS_DRAW_TRANSPARENT
Command3=ID_APP_EXIT
CommandCount=3

