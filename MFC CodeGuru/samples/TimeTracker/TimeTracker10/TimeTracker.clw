; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgZeiten
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TimeTracker.h"
LastPage=0

ClassCount=5
Class1=CDlgZeiten
Class2=CMyListCrtl
Class3=CTimeTrackerApp
Class4=CWndNotify

ResourceCount=3
Resource1=IDD_PROJEKT
Resource2=IDD_DLGLISTE
Class5=CProjektNeu
Resource3=IDR_MAINFRAME

[CLS:CDlgZeiten]
Type=0
BaseClass=CDialog
HeaderFile=DlgZeiten.h
ImplementationFile=DlgZeiten.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_DELETE

[CLS:CMyListCrtl]
Type=0
BaseClass=CListCtrl
HeaderFile=MyListCrtl.h
ImplementationFile=MyListCrtl.cpp
LastObject=CMyListCrtl

[CLS:CTimeTrackerApp]
Type=0
BaseClass=CWinApp
HeaderFile=TimeTracker.h
ImplementationFile=TimeTracker.cpp
Filter=N
VirtualFilter=AC
LastObject=CTimeTrackerApp

[CLS:CWndNotify]
Type=0
BaseClass=CWnd
HeaderFile=WndNotify.h
ImplementationFile=WndNotify.cpp
Filter=W
VirtualFilter=WC
LastObject=CWndNotify

[DLG:IDD_DLGLISTE]
Type=1
Class=CDlgZeiten
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROJEKTE,combobox,1344340227
Control3=IDC_NEU,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDC_ZEITENLISTE,SysListView32,1350665217
Control7=IDC_STATIC,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=CWndNotify
Command1=ID_DATEI_ZEITENANZEIGEN
Command2=ID_APP_EXIT
CommandCount=2

[DLG:IDD_PROJEKT]
Type=1
Class=CProjektNeu
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROJEKT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DATEI,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CProjektNeu]
Type=0
HeaderFile=ProjektNeu.h
ImplementationFile=ProjektNeu.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProjektNeu

