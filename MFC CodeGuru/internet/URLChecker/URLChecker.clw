; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CURLCheckerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "URLChecker.h"

ClassCount=3
Class1=CURLCheckerApp
Class2=CURLCheckerDlg

ResourceCount=4
Resource2=IDR_POPUP_MENU
Resource3=IDD_URLCHECKER_DIALOG
Resource1=IDR_MAINFRAME
Class3=CAboutDlg
Resource4=IDD_ABOUTBOX

[CLS:CURLCheckerApp]
Type=0
HeaderFile=URLChecker.h
ImplementationFile=URLChecker.cpp
Filter=N

[CLS:CURLCheckerDlg]
Type=0
HeaderFile=URLCheckerDlg.h
ImplementationFile=URLCheckerDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_ABOUTDLG



[DLG:IDD_URLCHECKER_DIALOG]
Type=1
Class=CURLCheckerDlg
ControlCount=8
Control1=IDC_URL,edit,1350631552
Control2=IDC_DURATION,edit,1350639744
Control3=IDC_SPINDURATION,msctls_updown32,1342177334
Control4=IDC_STARTBTN,button,1342242816
Control5=ID_EXIT,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308864
Control8=ID_ABOUTDLG,button,1342242816

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_CONFIGURE
Command2=ID_EXIT
CommandCount=2

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,button,1342177287

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

