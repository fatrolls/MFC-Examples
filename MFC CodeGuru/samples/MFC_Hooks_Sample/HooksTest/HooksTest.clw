; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHooksClientWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hookstest.h"
LastPage=0

ClassCount=5
Class1=CHooksClientThread
Class2=CHooksClientWnd
Class3=CHooksTestApp
Class4=CAboutDlg
Class5=CHooksTestDlg

ResourceCount=2
Resource1=IDD_HOOKSTEST_DIALOG (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))

[CLS:CHooksClientThread]
Type=0
BaseClass=CWinThread
HeaderFile=\Work\Applicad8\SwitchBoard\HooksClient\HooksClient.h
ImplementationFile=\Work\Applicad8\SwitchBoard\HooksClient\HooksClient.cpp
LastObject=CHooksClientThread

[CLS:CHooksClientWnd]
Type=0
BaseClass=CWnd
HeaderFile=\Work\Applicad8\SwitchBoard\HooksClient\HooksClient.h
ImplementationFile=\Work\Applicad8\SwitchBoard\HooksClient\HooksClient.cpp
Filter=W
VirtualFilter=WC
LastObject=CHooksClientWnd

[CLS:CHooksTestApp]
Type=0
BaseClass=CWinApp
HeaderFile=HooksTest.h
ImplementationFile=HooksTest.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=HooksTestDlg.cpp
ImplementationFile=HooksTestDlg.cpp
LastObject=CAboutDlg

[CLS:CHooksTestDlg]
Type=0
BaseClass=CDialog
HeaderFile=HooksTestDlg.h
ImplementationFile=HooksTestDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_HOOKSTEST_DIALOG]
Type=1
Class=CHooksTestDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HOOKSTEST_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEST,button,1342242816

