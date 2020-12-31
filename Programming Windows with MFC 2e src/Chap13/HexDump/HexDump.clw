; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HexDump.h"
LastPage=0

ClassCount=9
Class1=CHexApp
Class2=CHexDoc
Class3=CHexView
Class4=CMainFrame
Class9=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CHexApp]
Type=0
HeaderFile=HexDump.h
ImplementationFile=HexDump.cpp
Filter=N

[CLS:CHexDoc]
Type=0
HeaderFile=HexDoc.h
ImplementationFile=HexDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CHexView]
Type=0
HeaderFile=HexView.h
ImplementationFile=HexView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=HexDump.cpp
ImplementationFile=HexDump.cpp
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
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
Command3=ID_FILE_PRINT_PREVIEW
Command4=ID_FILE_PRINT_SETUP
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
CommandCount=2

