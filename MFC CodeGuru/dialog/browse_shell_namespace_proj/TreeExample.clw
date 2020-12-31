; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTreeExampleDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TreeExample.h"

ClassCount=3
Class1=CTreeExampleApp
Class2=CTreeExampleDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_TREEEXAMPLE_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX

[CLS:CTreeExampleApp]
Type=0
HeaderFile=TreeExample.h
ImplementationFile=TreeExample.cpp
Filter=N

[CLS:CTreeExampleDlg]
Type=0
HeaderFile=TreeExampleDlg.h
ImplementationFile=TreeExampleDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BROWSE_TREE

[CLS:CAboutDlg]
Type=0
HeaderFile=TreeExampleDlg.h
ImplementationFile=TreeExampleDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TREEEXAMPLE_DIALOG]
Type=1
Class=CTreeExampleDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BROWSE_TREE,SysTreeView32,1350631431
Control4=IDC_FILELIST,combobox,1344340290
Control5=IDC_SYNCH_FOLDERS,button,1342242816

