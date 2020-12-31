; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx21bView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex21b.h"
LastPage=0

ClassCount=7
Class1=CEx21bApp
Class2=CEx21bDoc
Class3=CEx21bView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_EX21D
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CTest21cDialog
Resource3=IDD_ABOUTBOX
Class7=CTest21dDialog
Resource4=IDD_EX21C

[CLS:CEx21bApp]
Type=0
HeaderFile=ex21b.h
ImplementationFile=ex21b.cpp
Filter=N

[CLS:CEx21bDoc]
Type=0
HeaderFile=ex21bDoc.h
ImplementationFile=ex21bDoc.cpp
Filter=N

[CLS:CEx21bView]
Type=0
HeaderFile=ex21bView.h
ImplementationFile=ex21bView.cpp
Filter=C
LastObject=ID_TEST_EX21DDLL
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=ex21b.cpp
ImplementationFile=ex21b.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_TEST_EX21CDLL
Command15=ID_TEST_EX21DDLL
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_APP_ABOUT
CommandCount=18

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

[DLG:IDD_EX21C]
Type=1
Class=CTest21cDialog
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_INPUT,edit,1350631552
Control3=IDC_COMPUTE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OUTPUT,edit,1350566016
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816

[CLS:CTest21cDialog]
Type=0
HeaderFile=Test21cDialog.h
ImplementationFile=Test21cDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTest21cDialog

[DLG:IDD_EX21D]
Type=1
Class=CTest21dDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RYG,RYG,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CTest21dDialog]
Type=0
HeaderFile=Test21dDialog.h
ImplementationFile=Test21dDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CTest21dDialog

