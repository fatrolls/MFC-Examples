; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPathComboBox
LastTemplate=CComboBoxEx
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PathList.h"

ClassCount=3
Class1=CPathListApp
Class2=CPathListDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CPathComboBox
Resource2=IDD_PATHLIST_DIALOG

[CLS:CPathListApp]
Type=0
HeaderFile=PathList.h
ImplementationFile=PathList.cpp
Filter=N

[CLS:CPathListDlg]
Type=0
HeaderFile=PathListDlg.h
ImplementationFile=PathListDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CBEX



[DLG:IDD_PATHLIST_DIALOG]
Type=1
Class=CPathListDlg
ControlCount=1
Control1=IDC_CBEX,ComboBoxEx32,1344340227

[CLS:CPathComboBox]
Type=0
HeaderFile=PathComboBox.h
ImplementationFile=PathComboBox.cpp
BaseClass=CComboBoxEx
Filter=W
VirtualFilter=cWC
LastObject=CPathComboBox

