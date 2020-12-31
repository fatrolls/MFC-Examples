; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTrickBtnDemoDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TrickBtnDemo.h"

ClassCount=4
Class1=CTrickBtnDemoApp
Class2=CTrickBtnDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_TRICKBTNDEMO_DIALOG
Resource2=IDR_MAINFRAME
Class4=CTrickButton
Resource3=IDD_ABOUTBOX

[CLS:CTrickBtnDemoApp]
Type=0
HeaderFile=TrickBtnDemo.h
ImplementationFile=TrickBtnDemo.cpp
Filter=N

[CLS:CTrickBtnDemoDlg]
Type=0
HeaderFile=TrickBtnDemoDlg.h
ImplementationFile=TrickBtnDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TRICKBUTTON

[CLS:CAboutDlg]
Type=0
HeaderFile=TrickBtnDemoDlg.h
ImplementationFile=TrickBtnDemoDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_TRICKBTNDEMO_DIALOG]
Type=1
Class=CTrickBtnDemoDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TRICKBUTTON,button,1342242816
Control3=IDC_STATIC,static,1342308353

[CLS:CTrickButton]
Type=0
HeaderFile=TrickButton.h
ImplementationFile=TrickButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CTrickButton

