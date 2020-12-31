; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFormatRTFDlg
LastTemplate=CRichEditCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FormatRTF.h"

ClassCount=3
Class1=CFormatRTFApp
Class2=CFormatRTFDlg

ResourceCount=3
Resource2=IDD_FORMATRTF_DIALOG
Resource1=IDR_MAINFRAME
Class3=LRichEditCtrl
Resource3=IDD_FORMATRTF_DIALOG (German (Germany))

[CLS:CFormatRTFApp]
Type=0
HeaderFile=FormatRTF.h
ImplementationFile=FormatRTF.cpp
Filter=N

[CLS:CFormatRTFDlg]
Type=0
HeaderFile=FormatRTFDlg.h
ImplementationFile=FormatRTFDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PB_TOGGLE



[DLG:IDD_FORMATRTF_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CFormatRTFDlg

[DLG:IDD_FORMATRTF_DIALOG (German (Germany))]
Type=1
Class=CFormatRTFDlg
ControlCount=4
Control1=IDC_PB_TOGGLE,button,1342242816
Control2=IDC_PB_SHOW,button,1342242816
Control3=IDC_PB_HIDE,button,1342242816
Control4=IDOK,button,1342242817

[CLS:LRichEditCtrl]
Type=0
HeaderFile=LRTFCtrl.h
ImplementationFile=LRTFCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=LRichEditCtrl

