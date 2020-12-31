; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTurboDragDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TurboDemo.h"

ClassCount=3
Class1=CTurboDemoApp
Class2=CTurboDemoDlg

ResourceCount=4
Resource2=IDD_TURBODEMO_DIALOG
Resource3=IDD_TURBODEMO_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=CTurboDragDlg
Resource4=IDD_TURBODRAG_DIALOG (English (U.S.))

[CLS:CTurboDemoApp]
Type=0
HeaderFile=TurboDemo.h
ImplementationFile=TurboDemo.cpp
Filter=N

[CLS:CTurboDemoDlg]
Type=0
HeaderFile=TurboDemoDlg.h
ImplementationFile=TurboDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTurboDemoDlg



[DLG:IDD_TURBODEMO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CTurboDemoDlg

[DLG:IDD_TURBODEMO_DIALOG (English (U.S.))]
Type=1
Class=CTurboDemoDlg
ControlCount=3
Control1=IDC_TREELIST,TurboDLL.TreeListCtrl,1342177280
Control2=IDC_STATIC,static,1342308865
Control3=IDC_BUTTON_DD,button,1342242816

[CLS:CTurboDragDlg]
Type=0
HeaderFile=TurboDragDlg.h
ImplementationFile=TurboDragDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTurboDragDlg

[DLG:IDD_TURBODRAG_DIALOG (English (U.S.))]
Type=1
Class=CTurboDragDlg
ControlCount=0

