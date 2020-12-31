; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyToolTipCtrl
LastTemplate=CToolTipCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GridDemo.h"
LastPage=0

ClassCount=6
Class1=CGridDemoApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class2=CChildView
Class5=CSettingsDialog
Class6=CMyToolTipCtrl
Resource3=IDD_SETTINGDLG

[CLS:CGridDemoApp]
Type=0
HeaderFile=GridDemo.h
ImplementationFile=GridDemo.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=GridDemo.cpp
ImplementationFile=GridDemo.cpp
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

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_OPTIONS_GRID_SETTINGS
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[DLG:IDD_SETTINGDLG]
Type=1
Class=CSettingsDialog
ControlCount=13
Control1=IDC_STATIC,button,1342308359
Control2=IDC_SLIDER,msctls_trackbar32,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDITHORZ,edit,1350631552
Control8=IDC_SPINHORZ,msctls_updown32,1342177334
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDITVERT,edit,1350631552
Control11=IDC_SPINVERT,msctls_updown32,1342177334
Control12=IDOK,button,1342373889
Control13=IDCANCEL,button,1342373888

[CLS:CSettingsDialog]
Type=0
HeaderFile=SettingsDialog.h
ImplementationFile=SettingsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[CLS:CMyToolTipCtrl]
Type=0
HeaderFile=MyToolTipCtrl.h
ImplementationFile=MyToolTipCtrl.cpp
BaseClass=CToolTipCtrl
Filter=W

