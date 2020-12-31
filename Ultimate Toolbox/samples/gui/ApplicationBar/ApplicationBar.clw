; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CApplicationBarApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ApplicationBar.h"

ClassCount=4
Class1=CApplicationBarApp
Class2=CApplicationBarDlg

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDR_MENU_POPUP
Class3=COXAppBar
Class4=COptionsDialog
Resource3=IDD_APPLICATIONBAR_DIALOG
Resource4=IDD_DIALOG_OPTIONS (English (U.S.))
Resource5=IDD_APPLICATIONBAR_DIALOG (English (U.S.))
Resource6=IDR_MENU_POPUP (English (Canada))

[CLS:CApplicationBarApp]
Type=0
HeaderFile=ApplicationBar.h
ImplementationFile=ApplicationBar.cpp
Filter=N
LastObject=CApplicationBarApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CApplicationBarDlg]
Type=0
HeaderFile=ApplicationBarDlg.h
ImplementationFile=ApplicationBarDlg.cpp
Filter=D
LastObject=ID_APP_ABOUT
BaseClass=COXAppBar<CDialog>
VirtualFilter=dWC



[DLG:IDD_APPLICATIONBAR_DIALOG]
Type=1
Class=CApplicationBarDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177294

[CLS:COptionsDialog]
Type=0
HeaderFile=OptionsDialog.h
ImplementationFile=OptionsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=COptionsDialog
VirtualFilter=dWC

[DLG:IDD_APPLICATIONBAR_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDOK,button,1342242817

[DLG:IDD_DIALOG_OPTIONS (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=ID_APPLY,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CHECK_ONTOP,button,1342242819
Control5=IDC_CHECK_AUTOHIDE,button,1342242819
Control6=IDC_RADIO_RIGHT,button,1342181385
Control7=IDC_RADIO_LEFT,button,1342181385
Control8=IDC_RADIO_TOP,button,1342181385
Control9=IDC_RADIO_BOTTOM,button,1342181385

[MNU:IDR_MENU_POPUP]
Type=1
Class=?
Command1=ID_AUTOHIDE
Command2=ID_ALWAYSONTOP
Command3=ID_FLOATDOCK
Command4=ID_LEFTDOCK
Command5=ID_TOPDOCK
Command6=ID_RIGHTDOCK
Command7=ID_BOTTOMDOCK
Command8=ID_HASCAPTION
Command9=IDOK
CommandCount=9

[MNU:IDR_MENU_POPUP (English (Canada))]
Type=1
Class=?
Command1=ID_AUTOHIDE
Command2=ID_ALWAYSONTOP
Command3=ID_FLOATDOCK
Command4=ID_LEFTDOCK
Command5=ID_TOPDOCK
Command6=ID_RIGHTDOCK
Command7=ID_BOTTOMDOCK
Command8=ID_REGISTER
Command9=ID_UNREGISTER
Command10=IDOK
Command11=ID_APP_ABOUT
CommandCount=11

