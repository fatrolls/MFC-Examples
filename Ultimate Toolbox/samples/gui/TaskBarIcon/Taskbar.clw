; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTaskbarApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "taskbar.h"
LastPage=0

ClassCount=3
Class1=CDemoTaskbarIcon
Class2=CTaskbarApp
Class3=CTaskbarDlg

ResourceCount=2
Resource1=IDD_TASKBAR_DIALOG
Resource2=IDR_POPUPMENU

[CLS:CDemoTaskbarIcon]
Type=0
BaseClass=COXTaskbarIcon
HeaderFile=DemoTaskbarIcon.h
ImplementationFile=demotaskbaricon.cpp
LastObject=CDemoTaskbarIcon

[CLS:CTaskbarApp]
Type=0
BaseClass=CWinApp
HeaderFile=Taskbar.h
ImplementationFile=Taskbar.cpp
Filter=N
VirtualFilter=AC
LastObject=CTaskbarApp

[CLS:CTaskbarDlg]
Type=0
BaseClass=CDialog
HeaderFile=TaskbarDlg.h
ImplementationFile=TaskbarDlg.cpp
LastObject=CTaskbarDlg

[DLG:IDD_TASKBAR_DIALOG]
Type=1
Class=CTaskbarDlg
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TOGGLE_SHOW,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ICON1,button,1342373897
Control6=IDC_ICON2,button,1342242825
Control7=IDC_STATIC,static,1342308355
Control8=IDC_STATIC,static,1342177283
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_TOOLTIP,edit,1350631552
Control11=IDC_SET_TOOLTIP,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_ROUTE_TO_ME,button,1342242819
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_CODES,edit,1350565892
Control16=IDC_MINIMIZE,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_EDIT_MOUSEMSG,edit,1350631552
Control19=IDC_STATIC,static,1342308352

[MNU:IDR_POPUPMENU]
Type=1
Class=?
Command1=ID_OPEN
Command2=ID_POPUP_MOUSEMSG
CommandCount=2

