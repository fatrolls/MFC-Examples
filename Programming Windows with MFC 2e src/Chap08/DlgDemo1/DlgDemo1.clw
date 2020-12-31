; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptionsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DlgDemo1.h"
LastPage=0

ClassCount=5
Class1=CDlgDemo1App
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class2=CChildView
Class5=COptionsDialog
Resource3=IDD_OPTIONS

[CLS:CDlgDemo1App]
Type=0
HeaderFile=DlgDemo1.h
ImplementationFile=DlgDemo1.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DlgDemo1.cpp
ImplementationFile=DlgDemo1.cpp
Filter=D
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
Class=CMainFrame
Command1=ID_FILE_OPTIONS
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_OPTIONS]
Type=1
Class=COptionsDialog
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WIDTH,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HEIGHT,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_INCHES,button,1342308361
Control7=IDC_CENTIMETERS,button,1342177289
Control8=IDC_PIXELS,button,1342177289
Control9=IDOK,button,1342373889
Control10=IDCANCEL,button,1342373888
Control11=IDC_RESET,button,1342373888

[CLS:COptionsDialog]
Type=0
HeaderFile=OptionsDialog.h
ImplementationFile=OptionsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=COptionsDialog
VirtualFilter=dWC

