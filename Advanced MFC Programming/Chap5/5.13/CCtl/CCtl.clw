; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MCTreeCtrl
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CCtl.h"

ClassCount=4
Class1=CCCtlApp
Class2=CCCtlDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=MCTreeCtrl
Resource3=IDD_CCTL_DIALOG

[CLS:CCCtlApp]
Type=0
HeaderFile=CCtl.h
ImplementationFile=CCtl.cpp
Filter=N

[CLS:CCCtlDlg]
Type=0
HeaderFile=CCtlDlg.h
ImplementationFile=CCtlDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TREE

[CLS:CAboutDlg]
Type=0
HeaderFile=CCtlDlg.h
ImplementationFile=CCtlDlg.cpp
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

[DLG:IDD_CCTL_DIALOG]
Type=1
Class=CCCtlDlg
ControlCount=1
Control1=IDC_TREE,SysTreeView32,1350631435

[CLS:MCTreeCtrl]
Type=0
HeaderFile=TreeCtrl.h
ImplementationFile=TreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=MCTreeCtrl

