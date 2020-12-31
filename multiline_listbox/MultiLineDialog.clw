; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMultiLineListBox
LastTemplate=CListBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MultiLineDialog.h"

ClassCount=4
Class1=CMultiLineDialogApp
Class2=CMultiLineDialogDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMultiLineListBox
Resource3=IDD_MULTILINEDIALOG_DIALOG

[CLS:CMultiLineDialogApp]
Type=0
HeaderFile=MultiLineDialog.h
ImplementationFile=MultiLineDialog.cpp
Filter=N

[CLS:CMultiLineDialogDlg]
Type=0
HeaderFile=MultiLineDialogDlg.h
ImplementationFile=MultiLineDialogDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMultiLineDialogDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=MultiLineDialogDlg.h
ImplementationFile=MultiLineDialogDlg.cpp
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

[DLG:IDD_MULTILINEDIALOG_DIALOG]
Type=1
Class=CMultiLineDialogDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,listbox,1352730722

[CLS:CMultiLineListBox]
Type=0
HeaderFile=multilinelistbox.h
ImplementationFile=multilinelistbox.cpp
BaseClass=CListBox
LastObject=CMultiLineListBox

