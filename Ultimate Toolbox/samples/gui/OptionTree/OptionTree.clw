; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptionTreeDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OptionTree.h"

ClassCount=3
Class1=COptionTreeApp
Class2=COptionTreeDlg
Class3=COXOptionTree

ResourceCount=4
Resource1=IDD_OPTIONTREE_DIALOG (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_OPTIONTREE_DIALOG

[CLS:COptionTreeApp]
Type=0
HeaderFile=OptionTree.h
ImplementationFile=OptionTree.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=COptionTreeApp

[CLS:COptionTreeDlg]
Type=0
HeaderFile=OptionTreeDlg.h
ImplementationFile=OptionTreeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=COptionTreeDlg

[DLG:IDD_OPTIONTREE_DIALOG]
Type=1
Class=COptionTreeDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_TREE_OPTION,SysTreeView32,1350631456
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SEPARATOR1,static,1342312448
Control5=IDC_SEPARATOR2,static,1342312448
Control6=IDC_UPDATE_INFO,static,1342308864

[DLG:IDD_OPTIONTREE_DIALOG (English (U.S.))]
Type=1
Class=COptionTreeDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TREE_OPTION,SysTreeView32,1350631424

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:COXOptionTree]
Type=0
HeaderFile=OXOptionTree.h
ImplementationFile=OXOptionTree.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=COXOptionTree

