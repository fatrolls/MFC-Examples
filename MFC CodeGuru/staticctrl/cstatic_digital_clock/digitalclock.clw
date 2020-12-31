; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDigitalclockDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "digitalclock.h"
LastPage=0

ClassCount=4
Class1=CDigitalclockApp
Class2=CAboutDlg
Class3=CDigitalclockDlg
Class4=CXJWDigitClock

ResourceCount=2
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_DIGITALCLOCK_DIALOG (English (U.S.))

[CLS:CDigitalclockApp]
Type=0
BaseClass=CWinApp
HeaderFile=digitalclock.h
ImplementationFile=digitalclock.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=digitalclockDlg.cpp
ImplementationFile=digitalclockDlg.cpp

[CLS:CDigitalclockDlg]
Type=0
BaseClass=CDialog
HeaderFile=digitalclockDlg.h
ImplementationFile=digitalclockDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

[CLS:CXJWDigitClock]
Type=0
BaseClass=CStatic
HeaderFile=EDClock.h
ImplementationFile=EDClock.cpp
LastObject=CXJWDigitClock

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DIGITALCLOCK_DIALOG]
Type=1
Class=CDigitalclockDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIGITALCLOCK_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_1,static,1342312448
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC_2,static,1342308352

