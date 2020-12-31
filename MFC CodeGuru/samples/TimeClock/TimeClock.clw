; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTimeClockDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "timeclock.h"
LastPage=0

ClassCount=3
Class1=CTimeClockApp
Class2=CTimeClockDlg

ResourceCount=3
Resource1=IDD_PRINT_PROPERTIES
Class3=CPrintPropertiesDlg
Resource2=IDD_TIMECLOCK_DIALOG
Resource3=IDD_ABOUT

[CLS:CTimeClockApp]
Type=0
BaseClass=CWinApp
HeaderFile=TimeClock.h
ImplementationFile=TimeClock.cpp
Filter=N

[CLS:CTimeClockDlg]
Type=0
BaseClass=CDialog
HeaderFile=TimeClockDlg.h
ImplementationFile=TimeClockDlg.cpp
LastObject=CTimeClockDlg
Filter=W
VirtualFilter=dWC

[DLG:IDD_TIMECLOCK_DIALOG]
Type=1
Class=CTimeClockDlg
ControlCount=23
Control1=IDC_STATIC,static,1342308354
Control2=IDC_TIMECARDFILE,static,1342312448
Control3=IDC_LOADTIMECARD,button,1342242816
Control4=IDC_STATIC,static,1342308354
Control5=IDC_NAME,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_WEEK,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDC_VACATION,edit,1350631552
Control10=IDC_STATIC,static,1342308354
Control11=IDC_SICK,edit,1350631552
Control12=IDC_STATIC,static,1342308354
Control13=IDC_OTHER,edit,1350631552
Control14=IDC_TIMECARD,SysListView32,1350666241
Control15=IDC_DAY,static,1342312448
Control16=IDC_HOURS,static,1342312448
Control17=IDC_STATIC,static,1342308352
Control18=IDC_MINUTES,static,1342312448
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SECONDS,static,1342312448
Control21=IDC_PUNCHINOUT,button,1342242817
Control22=IDC_PRINTREPORT,button,1342242816
Control23=IDC_STATIC,static,1342308352

[DLG:IDD_PRINT_PROPERTIES]
Type=1
Class=CPrintPropertiesDlg
ControlCount=17
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308354
Control3=IDC_MON,edit,1350631552
Control4=IDC_STATIC,static,1342308354
Control5=IDC_TUE,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDC_WED,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDC_THU,edit,1350631552
Control10=IDC_STATIC,static,1342308354
Control11=IDC_FRI,edit,1350631552
Control12=IDC_STATIC,static,1342308354
Control13=IDC_SAT,edit,1350631552
Control14=IDC_STATIC,static,1342308354
Control15=IDC_SUN,edit,1350631552
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816

[CLS:CPrintPropertiesDlg]
Type=0
HeaderFile=PrintPropertiesDlg.h
ImplementationFile=PrintPropertiesDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SUN
VirtualFilter=dWC

[DLG:IDD_ABOUT]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308352

