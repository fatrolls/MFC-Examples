; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSplitdlgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "splitdlg.h"
LastPage=0

ClassCount=4
Class1=CSplitdlgApp
Class2=CAboutDlg
Class3=CSplitdlgDlg
Class4=CSplitterBar

ResourceCount=2
Resource1=IDD_SPLITDLG_DIALOG
Resource2=IDD_ABOUTBOX

[CLS:CSplitdlgApp]
Type=0
BaseClass=CWinApp
HeaderFile=splitdlg.h
ImplementationFile=splitdlg.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=splitdlgDlg.cpp
ImplementationFile=splitdlgDlg.cpp
LastObject=CAboutDlg

[CLS:CSplitdlgDlg]
Type=0
BaseClass=CDialog
HeaderFile=splitdlgDlg.h
ImplementationFile=splitdlgDlg.cpp
LastObject=IDC_TREE
Filter=D
VirtualFilter=dWC

[CLS:CSplitterBar]
Type=0
BaseClass=CWnd
HeaderFile=SplitterBar.h
ImplementationFile=SplitterBar.cpp
Filter=W
VirtualFilter=WC
LastObject=CSplitterBar

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SPLITDLG_DIALOG]
Type=1
Class=CSplitdlgDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TREE,SysTreeView32,1350631424
Control3=IDC_LIST,SysListView32,1350631427

