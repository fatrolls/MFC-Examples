; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFanView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fan.h"
LastPage=0

ClassCount=6
Class1=CFanApp
Class2=CFanDoc
Class3=CFanView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=Cddd
Resource3=IDD_DIALOG1

[CLS:CFanApp]
Type=0
HeaderFile=fan.h
ImplementationFile=fan.cpp
Filter=N

[CLS:CFanDoc]
Type=0
HeaderFile=fanDoc.h
ImplementationFile=fanDoc.cpp
Filter=N

[CLS:CFanView]
Type=0
HeaderFile=fanView.h
ImplementationFile=fanView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CFanView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=fan.cpp
ImplementationFile=fan.cpp
Filter=D

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
Class=CMainFrame
Command1=ID_STAR
Command2=ID_APP_EXIT
Command3=ID_1
Command4=ID_2
Command5=ID_3
Command6=ID_4
Command7=ID_5
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=Cddd
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:Cddd]
Type=0
HeaderFile=ddd.h
ImplementationFile=ddd.cpp
BaseClass=CDialog
Filter=D
LastObject=Cddd

