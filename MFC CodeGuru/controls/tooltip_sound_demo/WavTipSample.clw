; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWavTipSampleDlg
LastTemplate=CToolTipCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WavTipSample.h"

ClassCount=5
Class1=CWavTipSampleApp
Class2=CWavTipSampleDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CWavTipCtrl
Class5=CHyperLink
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_WAVTIPSAMPLE_DIALOG (English (U.S.))

[CLS:CWavTipSampleApp]
Type=0
HeaderFile=WavTipSample.h
ImplementationFile=WavTipSample.cpp
Filter=N

[CLS:CWavTipSampleDlg]
Type=0
HeaderFile=WavTipSampleDlg.h
ImplementationFile=WavTipSampleDlg.cpp
Filter=D
LastObject=IDCANCEL
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WavTipSampleDlg.h
ImplementationFile=WavTipSampleDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_MAIL_LINK,static,1342308352

[CLS:CWavTipCtrl]
Type=0
HeaderFile=WavTipCtrl.h
ImplementationFile=WavTipCtrl.cpp
BaseClass=CToolTipCtrl
Filter=W
LastObject=CWavTipCtrl
VirtualFilter=SWC

[CLS:CHyperLink]
Type=0
HeaderFile=hyperlink.h
ImplementationFile=hyperlink.cpp
BaseClass=CStatic
LastObject=CHyperLink

[DLG:IDD_WAVTIPSAMPLE_DIALOG (English (U.S.))]
Type=1
Class=CWavTipSampleDlg
ControlCount=5
Control1=IDC_CHECK_TIPSOUND,button,1342242819
Control2=IDC_COMBO_TIPSOUND,combobox,1344340227
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_MAIL_LINK,static,1342308352

