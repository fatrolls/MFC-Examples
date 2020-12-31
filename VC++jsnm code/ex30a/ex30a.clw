; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx30aApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex30a.h"
LastPage=0

ClassCount=5
Class1=CEx30aApp
Class2=CEx30aDoc
Class3=CEx30aView
Class4=CMainFrame

ResourceCount=12
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource8=IDR_CONTEXT_MENU
Resource9=IDD_DIALOGBAR
Resource10=IDD_PROPPAGE_ADV
Resource11=IDD_PROPPAGE_CLIENT
Resource12=IDD_PROPPAGE_SERVER
Class5=CAboutDlg

[CLS:CEx30aApp]
Type=0
HeaderFile=ex30a.h
ImplementationFile=ex30a.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CEx30aApp

[CLS:CEx30aDoc]
Type=0
HeaderFile=ex30aDoc.h
ImplementationFile=ex30aDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CEx30aView]
Type=0
HeaderFile=ex30aView.h
ImplementationFile=ex30aView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=ex30a.cpp
ImplementationFile=ex30a.cpp
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
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_INTERNET_START_SERVER
Command17=ID_INTERNET_STOP_SERVER
Command18=ID_INTERNET_REQUEST_SOCK
Command19=ID_INTERNET_REQUEST_INET
Command20=ID_INTERNET_CONFIGURATION
Command21=ID_APP_ABOUT
CommandCount=21

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CONTEXT_MENU]
Type=1
Command1=ID_EDIT_CLEAR_ALL
CommandCount=1

[DLG:IDD_DIALOGBAR]
Type=1
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_URL,edit,1350631552
Control3=IDC_REQUEST,button,1342242817

[DLG:IDD_PROPPAGE_ADV]
Type=1
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPSERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IPCLIENT,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_CLIENT]
Type=1
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IPADDR,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PORT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_FILE,edit,1350631552
Control9=IDC_USEPROXY,button,1342242819
Control10=IDC_STATIC,static,1342308352
Control11=IDC_PROXY,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_SERVER]
Type=1
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DIRECT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PORTSERVER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DEFAULT,edit,1350631552

