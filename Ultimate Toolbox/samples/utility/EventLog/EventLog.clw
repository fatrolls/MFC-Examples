; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEventLogApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EventLog.h"

ClassCount=2
Class1=CEventLogApp
Class2=CEventLogDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_EVENTLOG_DIALOG

[CLS:CEventLogApp]
Type=0
HeaderFile=EventLog.h
ImplementationFile=EventLog.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CEventLogApp

[CLS:CEventLogDlg]
Type=0
HeaderFile=EventLogDlg.h
ImplementationFile=EventLogDlg.cpp
Filter=D
LastObject=CEventLogDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_EVENTLOG_DIALOG]
Type=1
Class=CEventLogDlg
ControlCount=12
Control1=IDC_CREATE_BUTTON,button,1342242816
Control2=IDC_REG_BUTTON,button,1342373888
Control3=IDC_EVNT1_RADIO,button,1342308361
Control4=IDC_EVNT2_RADIO,button,1342177289
Control5=IDC_EVNT3_RADIO,button,1342177289
Control6=IDC_EVNT4_RADIO,button,1342177289
Control7=IDC_REP_BUTTON,button,1342373888
Control8=IDC_OPEN_BUTTON,button,1342373888
Control9=IDC_LIST_EVENTS,listbox,1352728835
Control10=IDC_RFR_BUTTON,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287

