; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAdvEditDemoDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AdvEditDemo.h"

ClassCount=4
Class1=CAdvEditDemoApp
Class2=CAdvEditDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CAdvEdit
Resource3=IDD_ADVEDITDEMO_DIALOG

[CLS:CAdvEditDemoApp]
Type=0
HeaderFile=AdvEditDemo.h
ImplementationFile=AdvEditDemo.cpp
Filter=N

[CLS:CAdvEditDemoDlg]
Type=0
HeaderFile=AdvEditDemoDlg.h
ImplementationFile=AdvEditDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAdvEditDemoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=AdvEditDemoDlg.h
ImplementationFile=AdvEditDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ADVEDITDEMO_DIALOG]
Type=1
Class=CAdvEditDemoDlg
ControlCount=10
Control1=IDC_EDIT1,edit,1342242976
Control2=IDC_EDIT2,edit,1342247044
Control3=IDC_EDIT3,edit,1342242944
Control4=IDC_EDIT4,edit,1342242944
Control5=IDC_STATIC,static,1342177294
Control6=IDC_EDIT5,edit,1342242944
Control7=IDC_EDIT6,edit,1342242944
Control8=IDC_EDIT7,edit,1342242944
Control9=IDC_EDIT8,edit,1342242944
Control10=IDC_EDIT9,edit,1342242944

[CLS:CAdvEdit]
Type=0
HeaderFile=AdvEdit.h
ImplementationFile=AdvEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CAdvEdit

