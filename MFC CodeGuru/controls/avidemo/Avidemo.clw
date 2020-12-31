; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAvidemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Avidemo.h"

ClassCount=3
Class1=CAvidemoApp
Class2=CAvidemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_AVIDEMO_DIALOG

[CLS:CAvidemoApp]
Type=0
HeaderFile=Avidemo.h
ImplementationFile=Avidemo.cpp
Filter=N

[CLS:CAvidemoDlg]
Type=0
HeaderFile=AvidemoDlg.h
ImplementationFile=AvidemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PROG_BTN

[CLS:CAboutDlg]
Type=0
HeaderFile=AvidemoDlg.h
ImplementationFile=AvidemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AVIDEMO_DIALOG]
Type=1
Class=CAvidemoDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ANIMATE,SysAnimate32,1342242823
Control4=IDC_PROGRESS,msctls_progress32,1350565888
Control5=IDC_PROG_BTN,button,1342242816
Control6=IDC_PERCENT,static,1342308865

