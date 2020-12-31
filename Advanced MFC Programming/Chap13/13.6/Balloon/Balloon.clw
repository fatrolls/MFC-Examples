; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBalloonDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Balloon.h"

ClassCount=3
Class1=CBalloonApp
Class2=CBalloonDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BALLOON_DIALOG

[CLS:CBalloonApp]
Type=0
HeaderFile=Balloon.h
ImplementationFile=Balloon.cpp
Filter=N

[CLS:CBalloonDlg]
Type=0
HeaderFile=Dlg.h
ImplementationFile=Dlg.cpp
Filter=W
LastObject=CBalloonDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=Dlg.h
ImplementationFile=Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BALLOON_DIALOG]
Type=1
Class=CBalloonDlg
ControlCount=0

