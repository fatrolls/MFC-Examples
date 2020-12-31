; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMCISampleDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MCISample.h"

ClassCount=5
Class1=CMCISampleApp
Class2=CMCISampleDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_PLAYSECTION_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_MCISAMPLE_DIALOG
Class4=CPlaySectionDlg
Class5=CHyperLink
Resource4=IDD_ABOUTBOX (English (U.S.))

[CLS:CMCISampleApp]
Type=0
HeaderFile=MCISample.h
ImplementationFile=MCISample.cpp
Filter=T
LastObject=CMCISampleApp

[CLS:CMCISampleDlg]
Type=0
HeaderFile=MCISampleDlg.h
ImplementationFile=MCISampleDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMCISampleDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=MCISampleDlg.h
ImplementationFile=MCISampleDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_PLAYSECTION_DIALOG]
Type=1
Class=CPlaySectionDlg
ControlCount=13
Control1=IDC_MINUTE_FROM,edit,1350631552
Control2=IDC_SECOND_FROM,edit,1350631552
Control3=IDC_FRAME_FROM,edit,1350631552
Control4=IDC_MINUTE_TO,edit,1350631552
Control5=IDC_SECOND_TO,edit,1350631552
Control6=IDC_FRAME_TO,edit,1350631552
Control7=IDCANCEL,button,1342242816
Control8=IDOK,button,1342242817
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:CPlaySectionDlg]
Type=0
HeaderFile=PlaySectionDlg.h
ImplementationFile=PlaySectionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CHyperLink]
Type=0
HeaderFile=hyperlink.h
ImplementationFile=hyperlink.cpp
BaseClass=CStatic
LastObject=CHyperLink

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_MAIL_LINK,static,1342308352

[DLG:IDD_MCISAMPLE_DIALOG]
Type=1
Class=CMCISampleDlg
ControlCount=8
Control1=IDC_TRACKSELECT,combobox,1344340227
Control2=IDC_PLAY,button,1342242816
Control3=IDC_PLAY_SECTION,button,1342242816
Control4=IDC_STOP,button,1342242816
Control5=IDC_PAUSE,button,1342242816
Control6=IDC_EJECT,button,1342242816
Control7=IDC_STATUS,static,1342312448
Control8=IDC_STATIC,static,1342308352

