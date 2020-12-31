; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "nettools.h"
LastPage=0

ClassCount=8
Class1=CMainFrame
Class2=CNbstatDlg
Class3=CNetstatDlg
Class4=CNettoolsApp
Class5=CAboutDlg
Class6=CPingThread
Class7=CTracertDlg

ResourceCount=7
Resource1=IDD_PING_DIALOG
Resource2=IDD_ABOUTBOX
Resource3=IDD_NETTOOLS_FORM
Resource4=IDD_NBSTAT_DIALOG
Resource5=IDD_DIALOGBAR
Resource6=IDD_NETSTAT_DIALOG
Class8=CPingDlg
Resource7=IDR_MAINFRAME

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CNbstatDlg]
Type=0
BaseClass=CDialog
HeaderFile=NbstatDlg.h
ImplementationFile=NbstatDlg.cpp

[CLS:CNetstatDlg]
Type=0
BaseClass=CDialog
HeaderFile=NetstatDlg.h
ImplementationFile=NetstatDlg.cpp
LastObject=CNetstatDlg
Filter=D
VirtualFilter=dWC

[CLS:CNettoolsApp]
Type=0
BaseClass=CWinApp
HeaderFile=nettools.h
ImplementationFile=nettools.cpp
LastObject=CNettoolsApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=nettools.cpp
ImplementationFile=nettools.cpp
LastObject=CAboutDlg

[CLS:CPingThread]
Type=0
BaseClass=CWinThread
HeaderFile=PingThread.h
ImplementationFile=PingThread.cpp
Filter=N
VirtualFilter=TC
LastObject=CPingThread

[CLS:CTracertDlg]
Type=0
BaseClass=CDialog
HeaderFile=TracertDlg.h
ImplementationFile=TracertDlg.cpp

[DLG:IDD_NBSTAT_DIALOG]
Type=1
Class=CNbstatDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NBSTAT_HOSTNAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_NBSTAT_HOSTADDR,edit,1350631552
Control7=IDC_NBSTAT_OPT_C,button,1342242819
Control8=IDC_NBSTAT_OPT_N,button,1342242819
Control9=IDC_NBSTAT_OPT_UR,button,1342242819
Control10=IDC_NBSTAT_OPT_LR,button,1342242819
Control11=IDC_NETSTAT_OPT_US,button,1342242819
Control12=IDC_NBSTAT_OPT_LS,button,1342242819

[DLG:IDD_NETSTAT_DIALOG]
Type=1
Class=CNetstatDlg
ControlCount=12
Control1=IDC_NETSTAT_OPT_CONNS,button,1342242819
Control2=IDC_NETSTAT_OPT_ROUTES,button,1342242819
Control3=IDC_NETSTAT_OPT_TCPSTATS,button,1342242819
Control4=IDC_NETSTAT_OPT_UDPSTATS,button,1342242819
Control5=IDC_NETSTAT_OPT_ICMPSTATS,button,1342242819
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_NETSTAT_OPT_IPSTATS,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_NETSTAT_OPT_IFSTATS,button,1342242819
Control11=IDC_NETSTAT_OPT_ALL,button,1342242819
Control12=IDC_NETSTAT_OPT_RESOLVE,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_COMMANDS_PING
Command3=ID_COMMANDS_NETSTAT
Command4=ID_COMMANDS_STOPPING
Command5=ID_COMMANDS_STOPSTAT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
Command7=ID_COMMANDS_PING
Command8=ID_COMMANDS_NETSTAT
Command9=ID_COMMANDS_STOPPING
Command10=ID_COMMANDS_STOPSTAT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_NETTOOLS_FORM]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST_UTILITY_OUTPUT,listbox,1352728833

[DLG:IDD_PING_DIALOG]
Type=1
Class=CPingDlg
ControlCount=28
Control1=IDC_PING_HOSTNAME,edit,1350631552
Control2=IDC_PING_OPT_T,button,1342242819
Control3=IDC_PING_OPT_A,button,1342242819
Control4=IDC_PING_OPT_F,button,1342242819
Control5=IDC_PING_OPT_N_VAL,edit,1350639616
Control6=IDC_PING_OPT_S_VAL,edit,1350639616
Control7=IDC_PING_OPT_L_VAL,edit,1350639616
Control8=IDC_PING_OPT_W_VAL,edit,1350639616
Control9=IDC_PING_OPT_I_VAL,edit,1350639616
Control10=IDC_PING_OPT_R_VAL,edit,1350639616
Control11=IDC_PING_OPT_RRLOOSE,button,1342242819
Control12=IDC_PING_OPT_RRSTRICT,button,1342242819
Control13=IDC_PING_OPT_TOS_NONE,button,1342242819
Control14=IDC_PING_OPT_TOS_LOW_DELAY,button,1342242819
Control15=IDC_PING_OPT_TOS_HIGH_THRU,button,1342242819
Control16=IDC_PING_OPT_TOS_HIGH_RELIAB,button,1342242819
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_PING_OPT_RROUTE_LRSR,edit,1350631552
Control28=IDC_PING_OPT_TRACERT,button,1342242819

[DLG:IDD_DIALOGBAR]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CPingDlg]
Type=0
HeaderFile=PingDlg.h
ImplementationFile=PingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PING_OPT_TRACERT
VirtualFilter=dWC

