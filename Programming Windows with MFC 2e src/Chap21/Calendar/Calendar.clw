; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCalendarCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Calendar.h"
CDK=Y

ClassCount=2
Class1=CCalendarCtrl
Class2=CCalendarPropPage

ResourceCount=2
Resource1=IDD_ABOUTBOX_CALENDAR
LastPage=0
Resource2=IDD_PROPPAGE_CALENDAR

[CLS:CCalendarCtrl]
Type=0
HeaderFile=CalendarCtl.h
ImplementationFile=CalendarCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC

[CLS:CCalendarPropPage]
Type=0
HeaderFile=CalendarPpg.h
ImplementationFile=CalendarPpg.cpp
Filter=D
BaseClass=COlePropertyPage
VirtualFilter=idWC

[DLG:IDD_ABOUTBOX_CALENDAR]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_CALENDAR]
Type=1
Class=CCalendarPropPage
ControlCount=1
Control1=IDC_REDSUNDAYS,button,1342242819

