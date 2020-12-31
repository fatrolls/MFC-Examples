; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTaskBarDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TaskBar.h"

ClassCount=6
Class1=CTaskBarApp
Class2=CTaskBarDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDR_CONTEXTMENU
Resource2=IDR_MAINFRAME
Class4=CAppBarWnd
Resource3=IDD_ABOUTBOX
Class5=CAppBarDlg
Resource4=IDD_TASKBAR_DIALOG
Class6=CControlsDlg
Resource5=IDR_EPIC_BUTTON_MENU
Resource6=IDD_APPBAR

[CLS:CTaskBarApp]
Type=0
HeaderFile=TaskBar.h
ImplementationFile=TaskBar.cpp
Filter=N

[CLS:CTaskBarDlg]
Type=0
HeaderFile=TaskBarDlg.h
ImplementationFile=TaskBarDlg.cpp
Filter=D
LastObject=CTaskBarDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TaskBarDlg.h
ImplementationFile=TaskBarDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TASKBAR_DIALOG]
Type=1
Class=CTaskBarDlg
ControlCount=4
Control1=IDC_REGISTER,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_UNREGISTER,button,1342242816

[CLS:CAppBarWnd]
Type=0
HeaderFile=ApBarWnd.h
ImplementationFile=ApBarWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CAppBarWnd

[DLG:IDD_APPBAR]
Type=1
Class=CAppBarDlg
ControlCount=3
Control1=IDC_START,button,1342242816
Control2=IDC_AUTOHIDE,button,1342242816
Control3=IDC_ONTOP,button,1342242816

[CLS:CAppBarDlg]
Type=0
HeaderFile=ApBarDlg.h
ImplementationFile=ApBarDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAppBarDlg

[MNU:IDR_CONTEXTMENU]
Type=1
Command1=ID_PROPERTIES
Command2=ID_MENUITEM32772
Command3=ID_MENUITEM32773
Command4=ID_MENUITEM32774
Command5=ID_MENUITEM32775
Command6=ID_MENUITEM32776
Command7=ID_FILE_EXIT
CommandCount=7

[CLS:CControlsDlg]
Type=0
HeaderFile=Controls.h
ImplementationFile=Controls.cpp
BaseClass=CAppBarDlg
Filter=D
LastObject=CControlsDlg
VirtualFilter=dWC

[MNU:IDR_EPIC_BUTTON_MENU]
Type=1
Command1=ID_MENUITEM32771
CommandCount=1

