; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CReportCtrlDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "reportctrldemo.h"
LastPage=0

ClassCount=6
Class1=CReportHeaderCtrl
Class2=CReportCtrl
Class3=CReportCtrlDemoApp
Class4=CAboutDlg
Class5=CReportCtrlDemoDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_REPORTCTRLDEMO_DIALOG
Resource3=IDD_STATESDLG
Class6=CStatesDlg
Resource4=IDR_MENU1

[CLS:CReportHeaderCtrl]
Type=0
BaseClass=CHeaderCtrl
HeaderFile=ReportCtrl.cpp
ImplementationFile=ReportCtrl.cpp

[CLS:CReportCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=ReportCtrl.h
ImplementationFile=ReportCtrl.cpp
Filter=W
VirtualFilter=FWC
LastObject=CReportCtrl

[CLS:CReportCtrlDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=ReportCtrlDemo.h
ImplementationFile=ReportCtrlDemo.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ReportCtrlDemoDlg.cpp
ImplementationFile=ReportCtrlDemoDlg.cpp
LastObject=CAboutDlg

[CLS:CReportCtrlDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=ReportCtrlDemoDlg.h
ImplementationFile=ReportCtrlDemoDlg.cpp
LastObject=IDC_CHECK
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_REPORTCTRLDEMO_DIALOG]
Type=1
Class=CReportCtrlDemoDlg
ControlCount=14
Control1=IDC_LIST1,SysListView32,1350631432
Control2=IDC_ALLOWSORT,button,1342242819
Control3=IDC_ALLOWEDIT,button,1342242819
Control4=IDC_GRIDLINES,button,1342242819
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHK_NONE,button,1342308361
Control7=IDC_CHK_NORMAL,button,1342177289
Control8=IDC_CHK_SINGLE,button,1342177289
Control9=IDC_CHK_DISABLED,button,1342177289
Control10=IDC_SELECT,button,1342242816
Control11=IDC_CHECK,button,1342242816
Control12=IDC_DELETE,button,1342242816
Control13=IDC_POSITION,button,1342242816
Control14=IDCANCEL,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_SELECTION_ALL
Command2=ID_SELECTION_UNALL
Command3=ID_SELECTION_INVERT
Command4=ID_CHECKBOX_ALL
Command5=ID_CHECKBOX_UNALL
Command6=ID_CHECKBOX_INVERT
Command7=ID_POSITION_UP
Command8=ID_POSITION_DOWN
Command9=ID_POSITION_TOP
Command10=ID_POSITION_BOTTOM
Command11=ID_POSITION_SWAP
CommandCount=11

[DLG:IDD_STATESDLG]
Type=1
Class=CStatesDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ALL,button,1342242819
Control3=IDC_SELECTED,button,1342242819
Control4=IDC_UNSELECTED,button,1342242819
Control5=IDC_CHECKED,button,1342242819
Control6=IDC_UNCHECKED,button,1342242819
Control7=IDC_FOCUSED,button,1342242819
Control8=IDC_UNFOCUSED,button,1342242819
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816

[CLS:CStatesDlg]
Type=0
HeaderFile=StatesDlg.h
ImplementationFile=StatesDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CStatesDlg

