; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSampleDlg
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sample.h"

ClassCount=4
Class1=CSampleApp
Class2=CSampleDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CSampleView
Resource3=IDD_SAMPLE_DIALOG

[CLS:CSampleApp]
Type=0
HeaderFile=sample.h
ImplementationFile=sample.cpp
Filter=N

[CLS:CSampleDlg]
Type=0
HeaderFile=sampleDlg.h
ImplementationFile=sampleDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSampleDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=sampleDlg.h
ImplementationFile=sampleDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SAMPLE_DIALOG]
Type=1
Class=CSampleDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SPLITTERWND,static,1073872896

[CLS:CSampleView]
Type=0
HeaderFile=SampleView.h
ImplementationFile=SampleView.cpp
BaseClass=CView
Filter=C
LastObject=CSampleView

