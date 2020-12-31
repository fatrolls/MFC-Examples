; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MCNumEdit
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CCtl.h"

ClassCount=5
Class1=CCCtlApp
Class2=CCCtlDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_CCTL_DIALOG
Resource2=IDR_MAINFRAME
Class4=MCNumEdit
Class5=MCCharEdit
Resource3=IDD_ABOUTBOX

[CLS:CCCtlApp]
Type=0
HeaderFile=CCtl.h
ImplementationFile=CCtl.cpp
Filter=N

[CLS:CCCtlDlg]
Type=0
HeaderFile=CCtlDlg.h
ImplementationFile=CCtlDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CCCtlDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=CCtlDlg.h
ImplementationFile=CCtlDlg.cpp
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

[DLG:IDD_CCTL_DIALOG]
Type=1
Class=CCCtlDlg
ControlCount=6
Control1=IDC_COMBO_SIMPLE,combobox,1344340225
Control2=IDC_COMBO_DROPDOWN,combobox,1344340226
Control3=IDC_COMBO_DROPLIST,combobox,1344340227
Control4=IDC_STATIC_SIMPLE,static,1342308352
Control5=IDC_STATIC_DROPDOWN,static,1342308352
Control6=IDC_STATIC_DROPLIST,static,1342308352

[CLS:MCNumEdit]
Type=0
HeaderFile=NumEdit.h
ImplementationFile=NumEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=MCNumEdit

[CLS:MCCharEdit]
Type=0
HeaderFile=CharEdit.h
ImplementationFile=CharEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=MCCharEdit

