; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CRoundSliderCtrlDemoDlg
LastTemplate=CSliderCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RoundSliderCtrlDemo.h"

ClassCount=4
Class1=CRoundSliderCtrlDemoApp
Class2=CRoundSliderCtrlDemoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CRoundSliderCtrl
Resource3=IDD_ROUNDSLIDERCTRLDEMO_DIALOG
Resource4=IDD_ABOUTBOX (German (Germany))
Resource5=IDD_ROUNDSLIDERCTRLDEMO_DIALOG (German (Germany))

[CLS:CRoundSliderCtrlDemoApp]
Type=0
HeaderFile=RoundSliderCtrlDemo.h
ImplementationFile=RoundSliderCtrlDemo.cpp
Filter=N

[CLS:CRoundSliderCtrlDemoDlg]
Type=0
HeaderFile=RoundSliderCtrlDemoDlg.h
ImplementationFile=RoundSliderCtrlDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SLIDER1

[CLS:CAboutDlg]
Type=0
HeaderFile=RoundSliderCtrlDemoDlg.h
ImplementationFile=RoundSliderCtrlDemoDlg.cpp
Filter=D
LastObject=IDC_HYPERLINK
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_HYPERLINK,static,1342308352

[DLG:IDD_ROUNDSLIDERCTRLDEMO_DIALOG]
Type=1
Class=CRoundSliderCtrlDemoDlg
ControlCount=3
Control1=IDC_SLIDER1,msctls_trackbar32,1342242840
Control2=IDC_SLIDER2,msctls_trackbar32,1342242840
Control3=IDOK,button,1342242817

[CLS:CRoundSliderCtrl]
Type=0
HeaderFile=RoundSliderCtrl.h
ImplementationFile=RoundSliderCtrl.cpp
BaseClass=CSliderCtrl
Filter=W
VirtualFilter=KWC
LastObject=CRoundSliderCtrl

[DLG:IDD_ABOUTBOX (German (Germany))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_HYPERLINK,static,1342308352

[DLG:IDD_ROUNDSLIDERCTRLDEMO_DIALOG (German (Germany))]
Type=1
Class=?
ControlCount=3
Control1=IDC_SLIDER1,msctls_trackbar32,1342242840
Control2=IDC_SLIDER2,msctls_trackbar32,1342242840
Control3=IDOK,button,1342242817

