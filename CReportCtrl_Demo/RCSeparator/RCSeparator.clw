; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSepDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RCSeparator.h"

ClassCount=3
Class1=CRCSeparatorApp
Class2=CRCSeparatorDlg

ResourceCount=4
Resource2=IDD_RCSEPARATOR_DIALOG
Resource3=IDD_DIALOG1
Resource1=IDR_MAINFRAME
Class3=CSepDlg
Resource4=IDD_RCSEPARATOR_DIALOG (English (U.S.))

[CLS:CRCSeparatorApp]
Type=0
HeaderFile=RCSeparator.h
ImplementationFile=RCSeparator.cpp
Filter=N

[CLS:CRCSeparatorDlg]
Type=0
HeaderFile=RCSeparatorDlg.h
ImplementationFile=RCSeparatorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1



[DLG:IDD_RCSEPARATOR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CRCSeparatorDlg

[DLG:IDD_RCSEPARATOR_DIALOG (English (U.S.))]
Type=1
Class=CRCSeparatorDlg
ControlCount=3
Control1=IDC_LIST1,SysListView32,1350631424
Control2=IDC_BUTTON1,button,1342242816
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CSepDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_CHECK1,button,1342242819
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816

[CLS:CSepDlg]
Type=0
HeaderFile=SepDlg.h
ImplementationFile=SepDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

