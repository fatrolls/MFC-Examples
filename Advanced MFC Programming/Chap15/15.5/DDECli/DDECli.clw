; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDDECliDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DDECli.h"

ClassCount=3
Class1=CDDECliApp
Class2=CDDECliDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DDECLI_DIALOG

[CLS:CDDECliApp]
Type=0
HeaderFile=DDECli.h
ImplementationFile=DDECli.cpp
Filter=N

[CLS:CDDECliDlg]
Type=0
HeaderFile=DDEDlg.h
ImplementationFile=DDEDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_COMMAND

[CLS:CAboutDlg]
Type=0
HeaderFile=DDEDlg.h
ImplementationFile=DDEDlg.cpp
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

[DLG:IDD_DDECLI_DIALOG]
Type=1
Class=CDDECliDlg
ControlCount=16
Control1=IDC_BUTTON_CONNECT,button,1342242816
Control2=IDC_EDIT,edit,1350633604
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TOPICNAME,edit,1350631552
Control5=IDC_EDIT_TIMEITEM,edit,1350633600
Control6=IDC_BUTTON_REQUEST,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_TEXT,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON_ADVISE,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_POKE,edit,1350631552
Control13=IDC_BUTTON_POKE,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_COMMAND,edit,1350631552
Control16=IDC_BUTTON_COMMAND,button,1342242816

