; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPingDlg
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ping.h"

ClassCount=4
Class1=CPingApp
Class2=CPingDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=ICMPComEvents
Resource3=IDD_PING_DIALOG

[CLS:CPingApp]
Type=0
HeaderFile=ping.h
ImplementationFile=ping.cpp
Filter=N

[CLS:CPingDlg]
Type=0
HeaderFile=pingDlg.h
ImplementationFile=pingDlg.cpp
Filter=D
LastObject=CPingDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=pingDlg.h
ImplementationFile=pingDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:ICMPComEvents]
Type=0
HeaderFile=ICMPComEvents.h
ImplementationFile=ICMPComEvents.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=ICMPComEvents

[DLG:IDD_PING_DIALOG]
Type=1
Class=CPingDlg
ControlCount=26
Control1=IDC_TIMEOUT,edit,1350566016
Control2=IDC_TOS,edit,1350566016
Control3=IDC_NUMSTAMPS,edit,1350566016
Control4=IDC_RRNUM,edit,1350566016
Control5=IDC_TRACERT,button,1342177282
Control6=IDC_INTERRUPT,button,1342177282
Control7=IDC_NOFRAG,button,1342177282
Control8=IDC_RESOLVE,button,1342177282
Control9=IDC_NUMPACKETS,edit,1350566016
Control10=IDC_PACKETLEN,edit,1350566016
Control11=IDC_TTL,edit,1350566016
Control12=IDC_HOSTNAME,edit,1350566016
Control13=IDC_STOPICMP,button,1342177280
Control14=IDC_STOPPING,button,1342177280
Control15=IDC_RUNPING,button,1342177280
Control16=IDC_PINGOUTLB,listbox,1345323008
Control17=IDC_SETVARS,button,1342177280
Control18=IDC_STARTICMP,button,1342177280
Control19=IDC_STATIC,static,1342177280
Control20=IDC_STATIC,static,1342177280
Control21=IDC_STATIC,static,1342177280
Control22=IDC_STATIC,static,1342177280
Control23=IDC_STATIC,static,1342177280
Control24=IDC_STATIC,static,1342177280
Control25=IDC_STATIC,static,1342177280
Control26=IDC_STATIC,static,1342177280

