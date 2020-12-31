; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPOPCheckerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "POPChecker.h"

ClassCount=4
Class1=CPOPCheckerApp
Class2=CPOPCheckerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CPopApp
Resource3=IDR_POPUP_MENU
Resource4=IDD_POPCHECKER_DIALOG

[CLS:CPOPCheckerApp]
Type=0
HeaderFile=POPChecker.h
ImplementationFile=POPChecker.cpp
Filter=N

[CLS:CPOPCheckerDlg]
Type=0
HeaderFile=POPCheckerDlg.h
ImplementationFile=POPCheckerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_EXIT

[CLS:CAboutDlg]
Type=0
HeaderFile=POPCheckerDlg.h
ImplementationFile=POPCheckerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_POPCHECKER_DIALOG]
Type=1
Class=CPOPCheckerDlg
ControlCount=14
Control1=IDC_USERNAME,edit,1350631552
Control2=IDC_PASSWORD,edit,1350631584
Control3=IDC_POPSERVER,edit,1350631552
Control4=IDC_DURATION,edit,1350631552
Control5=IDC_SPIN1,msctls_updown32,1342177334
Control6=ID_START,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC,static,1342308864
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_NO_MAIL,edit,1350641792

[CLS:CPopApp]
Type=0
HeaderFile=Pop.h
ImplementationFile=Pop.cpp
BaseClass=CWinApp

[MNU:IDR_POPUP_MENU]
Type=1
Command1=ID_CONFIGURATION
Command2=ID_EXIT
CommandCount=2

